#include "s21_rbtree.h"

namespace s21 {

/* CONSTRUCTORS */
template <typename K, typename V>
RBTree<K, V>::RBTree() : root_(nullptr) {}

template <typename K, typename V>
RBTree<K, V>::RBTree(const RBTree &other) {
  root_ = copyTree(other.root_, nullptr);
}

template <typename K, typename V>
RBTree<K, V>::RBTree(RBTree &&other) noexcept {
  root_ = other.root_;
  other.root_ = nullptr;
}

template <typename K, typename V>
RBTree<K, V> &RBTree<K, V>::operator=(const RBTree &other) {
  if (this != &other) {
    clear();
    root_ = copyTree(other.root_, nullptr);
  }
  return *this;
}

template <typename K, typename V>
RBTree<K, V> &RBTree<K, V>::operator=(RBTree &&other) noexcept {
  if (this != &other) {
    clear();
    root_ = other.getRoot();
    other.root_ = nullptr;
  }
  return *this;
}

/* DESTRUCTOR AND CLEARING METHODS */
template <typename K, typename V>
RBTree<K, V>::~RBTree() {
  clear();
}

template <typename K, typename V>
void RBTree<K, V>::clear() {
  clearNode(getRoot());
  root_ = nullptr;
}

template <typename K, typename V>
void RBTree<K, V>::clearNode(Node *node) {
  if (node) {
    clearNode(node->left);
    clearNode(node->right);
    delete node;
  }
}

/* RBTREE STRUCT FIXERS AND HELPERS */
template <typename K, typename V>
void RBTree<K, V>::leftRotate(Node *x) {
  Node *y = x->right;
  x->right = y->left;

  if (y->left) {
    y->left->parent = x;
  }

  y->parent = x->parent;

  if (!x->parent) {
    root_ = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }

  y->left = x;
  x->parent = y;
}

template <typename K, typename V>
void RBTree<K, V>::rightRotate(Node *y) {
  Node *x = y->left;
  y->left = x->right;

  if (x->right != nullptr) {
    x->right->parent = y;
  }

  x->parent = y->parent;

  if (y->parent == nullptr) {
    root_ = x;
  } else if (y == y->parent->right) {
    y->parent->right = x;
  } else {
    y->parent->left = x;
  }

  x->right = y;
  y->parent = x;
}

template <typename K, typename V>
void RBTree<K, V>::fixInsert(Node *z) {
  Node *y = nullptr;

  while (z != getRoot() && z->parent && z->parent->color == RED) {
    bool leftSide = false;

    if (z->parent && z->parent->parent) {
      leftSide = z->parent == z->parent->parent->left;
      y = leftSide ? z->parent->parent->right : z->parent->parent->left;
    }

    if (y && y->color == RED) {
      z->parent->color = BLACK;
      y->color = BLACK;
      z->parent->parent->color = RED;
      z = z->parent->parent;
    } else {
      if ((leftSide && z == z->parent->right) ||
          (!leftSide && z == z->parent->left)) {
        z = z->parent;
        leftSide ? leftRotate(z) : rightRotate(z);
      }
      if (z->parent) z->parent->color = BLACK;
      if (z->parent->parent) {
        z->parent->parent->color = RED;
        leftSide ? rightRotate(z->parent->parent)
                 : leftRotate(z->parent->parent);
      }
    }
    root_->color = BLACK;
  }
}

/* INSERTION AND DELETION LOGIC + HELPERS */
template <typename K, typename V>
void RBTree<K, V>::insertNode(Node *z) {
  Node *y = nullptr;
  Node *x = getRoot();

  while (x != nullptr) {
    y = x;
    if (z->key < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }

  z->parent = y;
  if (!y) {
    root_ = z;
  } else if (z->key < y->key) {
    y->left = z;
  } else {
    y->right = z;
  }

  z->color = RED;
}

template <typename K, typename V>
typename RBTree<K, V>::Node *RBTree<K, V>::deleteNode(Node *z) {
  if (!z) return nullptr;

  Node *y = z;
  Node *x = nullptr;
  Node *x_parent = nullptr;
  Color yOriginalColor = y->color;

  if (!z->left) {
    x = z->right;  // x could be nullptr if z has no children
    transplant(z, z->right);
    x_parent = z->parent;
  } else if (!z->right) {
    x = z->left;  // x could be nullptr if z has no children
    transplant(z, z->left);
    x_parent = z->parent;
  } else {
    y = minimum(z->right);
    yOriginalColor = y->color;
    x = y->right;  // x might be nullptr if y has no children
    x_parent = y->parent;
    if (y->parent == z) {
      x_parent = y;  // x's parent is y if y is a child of z
    } else {
      transplant(y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    transplant(z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }

  if (yOriginalColor == BLACK) {
    fixDelete(x, x_parent);
  }

  delete z;
  return nullptr;
}

template <typename K, typename V>
void RBTree<K, V>::fixDelete(Node *x, Node *x_parent) {
  while (x != getRoot() && (x == nullptr || getColor(x) == BLACK)) {
    if (x == x_parent->left || (x == nullptr && x_parent->left == nullptr)) {
      x = fixDeleteCaseLeft(x, x_parent);
    } else {
      x = fixDeleteCaseRight(x, x_parent);
    }
    if (x == getRoot()) break;
  }
  if (x) setColor(x, BLACK);
}

template <typename K, typename V>
typename RBTree<K, V>::Node *RBTree<K, V>::fixDeleteCaseLeft(Node *x,
                                                             Node *x_parent) {
  Node *w = x_parent->right;
  if (getColor(w) == RED) {
    recolorForLeftRotate(x_parent, w);
    w = x_parent->right;
  }
  return adjustBlackNodeLeft(x, x_parent, w);
}

template <typename K, typename V>
typename RBTree<K, V>::Node *RBTree<K, V>::fixDeleteCaseRight(Node *x,
                                                              Node *x_parent) {
  Node *w = x_parent->left;
  if (getColor(w) == RED) {
    recolorForRightRotate(x_parent, w);
    w = x_parent->left;
  }
  return adjustBlackNodeRight(x, x_parent, w);
}

template <typename K, typename V>
void RBTree<K, V>::recolorForLeftRotate(Node *x_parent, Node *w) {
  setColor(w, BLACK);
  setColor(x_parent, RED);
  leftRotate(x_parent);
}

template <typename K, typename V>
void RBTree<K, V>::recolorForRightRotate(Node *x_parent, Node *w) {
  setColor(w, BLACK);
  setColor(x_parent, RED);
  rightRotate(x_parent);
}

template <typename K, typename V>
typename RBTree<K, V>::Node *RBTree<K, V>::adjustBlackNodeLeft(Node *x,
                                                               Node *x_parent,
                                                               Node *w) {
  if (getColor(w->left) == BLACK && getColor(w->right) == BLACK) {
    setColor(w, RED);
    x = x_parent;
    x_parent = x_parent->parent;
  } else {
    x = rotateAtBlackNodeLeft(w, x_parent);
  }
  return x;
}

template <typename K, typename V>
typename RBTree<K, V>::Node *RBTree<K, V>::adjustBlackNodeRight(Node *x,
                                                                Node *x_parent,
                                                                Node *w) {
  if (getColor(w->right) == BLACK && getColor(w->left) == BLACK) {
    setColor(w, RED);
    x = x_parent;
    x_parent = x_parent->parent;
  } else {
    x = rotateAtBlackNodeRight(w, x_parent);
  }
  return x;
}

template <typename K, typename V>
typename RBTree<K, V>::Node *RBTree<K, V>::rotateAtBlackNodeLeft(
    Node *w, Node *x_parent) {
  if (getColor(w->right) == BLACK) {
    setColor(w->left, BLACK);
    setColor(w, RED);
    rightRotate(w);
    w = x_parent->right;
  }
  setColor(w, getColor(x_parent));
  setColor(x_parent, BLACK);
  setColor(w->right, BLACK);
  leftRotate(x_parent);
  return getRoot();
}

template <typename K, typename V>
typename RBTree<K, V>::Node *RBTree<K, V>::rotateAtBlackNodeRight(
    Node *w, Node *x_parent) {
  if (getColor(w->left) == BLACK) {
    setColor(w->right, BLACK);
    setColor(w, RED);
    leftRotate(w);
    w = x_parent->left;
  }
  setColor(w, getColor(x_parent));
  setColor(x_parent, BLACK);
  setColor(w->left, BLACK);
  rightRotate(x_parent);
  return getRoot();
}

template <typename K, typename V>
void RBTree<K, V>::transplant(Node *u, Node *v) {
  if (!u->parent) {
    root_ = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }

  if (v) v->parent = u->parent;
}

template <typename K, typename V>
typename RBTree<K, V>::Node *RBTree<K, V>::minimum(Node *node) const {
  while (node->left) {
    node = node->left;
  }
  return node;
}

template <typename K, typename V>
typename RBTree<K, V>::Node *RBTree<K, V>::maximum(Node *node) const {
  while (node->right) {
    node = node->right;
  }
  return node;
}

/* SEARCH LOGIC */
template <typename K, typename V>
typename RBTree<K, V>::Node *RBTree<K, V>::search(Node *node,
                                                  const K &key) const {
  while (node && key != node->key) {
    node = (key < node->key) ? node->left : node->right;
  }
  return node;
}

/* ACCESSORS AND MUTATORS */
template <typename K, typename V>
typename RBTree<K, V>::Node const *RBTree<K, V>::cgetRoot() const {
  return root_;
}
template <typename K, typename V>
typename RBTree<K, V>::Node *RBTree<K, V>::getRoot() const {
  return root_;
}

template <typename K, typename V>
void RBTree<K, V>::setRoot(Node *root) noexcept {
  root_ = root;
}

template <typename K, typename V>
Color RBTree<K, V>::getColor(Node *node) const {
  return node ? node->color : BLACK;
}

template <typename K, typename V>
void RBTree<K, V>::setColor(Node *node, Color color) {
  if (node) node->color = color;
}

/* ITERATOR */
template <typename K, typename V>
typename RBTree<K, V>::Iterator RBTree<K, V>::begin() {
  return iterator(minimum(getRoot()));
}

template <typename K, typename V>
typename RBTree<K, V>::Iterator RBTree<K, V>::end() {
  return iterator(nullptr);
}

template <typename K, typename V>
typename RBTree<K, V>::ConstIterator RBTree<K, V>::cbegin() const {
  return const_iterator(minimum(getRoot()));
}

template <typename K, typename V>
typename RBTree<K, V>::ConstIterator RBTree<K, V>::cend() const {
  return const_iterator(nullptr);
}

template <typename K, typename V>
typename RBTree<K, V>::Iterator RBTree<K, V>::find(const key_type &key) {
  return iterator(search(getRoot(), key));
}

/* ITERATOR CLASS */
template <typename K, typename V>
RBTree<K, V>::Iterator::Iterator() : current_(nullptr), prev_(nullptr) {}

template <typename K, typename V>
RBTree<K, V>::Iterator::Iterator(Node *node) : current_(node) {
  if (current_) {
    prev_ = predecessor(current_);
  }
}

template <typename K, typename V>
RBTree<K, V>::Iterator::Iterator(const Iterator &other)
    : current_(other.current_), prev_(other.prev_) {}

template <typename K, typename V>
typename RBTree<K, V>::iterator &RBTree<K, V>::Iterator::operator++() {
  if (current_) {
    prev_ = current_;
    current_ = successor(current_);
  }
  return *this;
}

template <typename K, typename V>
typename RBTree<K, V>::Iterator &RBTree<K, V>::Iterator::operator=(
    const Iterator &other) {
  if (this != &other) {
    this->current_ = other.current_;
    this->prev_ = other.prev_;
  }
  return *this;
}

template <typename K, typename V>
typename RBTree<K, V>::iterator &RBTree<K, V>::Iterator::operator--() {
  if (current_) {
    Node *pred = predecessor(current_);
    if (pred) {
      current_ = pred;
      prev_ = predecessor(current_);
    }
  } else {
    current_ = prev_;
  }
  return *this;
}

template <typename K, typename V>
typename RBTree<K, V>::iterator RBTree<K, V>::Iterator::operator++(int) {
  Iterator tmp = *this;
  ++(*this);
  return tmp;
}

template <typename K, typename V>
typename RBTree<K, V>::iterator RBTree<K, V>::Iterator::operator--(int) {
  Iterator tmp = *this;
  --(*this);
  return tmp;
}

template <typename K, typename V>
typename RBTree<K, V>::reference RBTree<K, V>::Iterator::operator*() {
  if (!current_) {
    throw std::logic_error("Dereferencing nullptr");
  }
  return current_->value;
}

template <typename K, typename V>
typename RBTree<K, V>::value_type *RBTree<K, V>::Iterator::operator->() {
  if (!current_) {
    throw std::logic_error("Dereferencing nullptr");
  }
  return &(current_->value);
}

template <typename K, typename V>
bool RBTree<K, V>::Iterator::operator==(const iterator &other) const {
  return current_ == other.current_;
}

template <typename K, typename V>
bool RBTree<K, V>::Iterator::operator!=(const iterator &other) const {
  return current_ != other.current_;
}

/* ITERATOR HELPERS */
template <typename K, typename V>
typename RBTree<K, V>::Node *RBTree<K, V>::Iterator::successor(Node *node) {
  if (!node) return nullptr;

  Node *res;

  if (node->right) {
    Node *succ = node->right;
    while (succ->left) {
      succ = succ->left;
    }
    res = succ;
  } else {
    Node *p = node->parent;
    while (p && node == p->right) {
      node = p;
      p = p->parent;
    }
    res = p;
  }

  return res;
}

template <typename K, typename V>
typename RBTree<K, V>::Node *RBTree<K, V>::Iterator::predecessor(Node *node) {
  if (!node) return nullptr;

  Node *res;

  if (node->left) {
    Node *pred = node->left;
    while (pred->right) {
      pred = pred->right;
    }
    res = pred;
  } else {
    Node *p = node->parent;
    while (p && node == p->left) {
      node = p;
      p = p->parent;
    }
    res = p;
  }

  return res;
}

template <typename K, typename V>
typename RBTree<K, V>::Node *RBTree<K, V>::Iterator::getNode() const {
  return current_;
}

/* OTHER HELPERS */
template <typename K, typename V>
typename RBTree<K, V>::size_type RBTree<K, V>::countNodes(Node *node) const {
  if (!node) return 0;
  return 1 + countNodes(node->left) + countNodes(node->right);
}

template <typename K, typename V>
typename RBTree<K, V>::Node *RBTree<K, V>::copyTree(Node *node, Node *parent) {
  if (!node) return nullptr;
  Node *newNode = new Node(node->key, node->value);
  newNode->parent = parent;
  newNode->left = copyTree(node->left, newNode);
  newNode->right = copyTree(node->right, newNode);
  return newNode;
}

/* PUBLIC METHODS */
template <typename K, typename V>
typename RBTree<K, V>::reference RBTree<K, V>::search(const key_type &key) {
  Node *node = search(getRoot(), key);
  if (!node) {
    throw std::out_of_range("RBTree::search(): Key not found");
  }
  return node->value;
}

template <typename K, typename V>
std::pair<typename RBTree<K, V>::iterator, bool> RBTree<K, V>::insert(
    const key_type &key, const_reference val) {
  std::pair<iterator, bool> res;

  if (!getRoot()) {
    setRoot(new Node(key, val));
    res = std::make_pair(iterator(getRoot()), true);
  } else if (contains(key)) {
    res = std::make_pair(iterator(search(getRoot(), key)), false);
  } else {
    Node *z = new Node(key, val);
    insertNode(z);
    fixInsert(z);
    res = std::make_pair(iterator(z), true);
  }

  return res;
}

template <typename K, typename V>
std::pair<typename RBTree<K, V>::iterator, bool> RBTree<K, V>::insert_or_assign(
    const key_type &key, const_reference val) {
  Node *z = search(getRoot(), key);
  if (z) deleteNode(z);
  return insert(key, val);
}

template <typename K, typename V>
void RBTree<K, V>::remove(const key_type &key) {
  Node *z = search(getRoot(), key);
  if (z) deleteNode(z);
}

template <typename K, typename V>
void RBTree<K, V>::erase(iterator pos) {
  Node *z = pos.getNode();
  if (z) deleteNode(z);
}

template <typename K, typename V>
void RBTree<K, V>::swap(RBTree &other) noexcept {
  std::swap(root_, other.root_);
}

template <typename K, typename V>
void RBTree<K, V>::merge(RBTree &other) {
  if (this == &other) {
    throw std::invalid_argument("RBTree::merge(): Cannot merge with itself");
  }

  RBTree tmp = other;

  for (auto it = tmp.begin(); it != tmp.end(); ++it) {
    std::pair<iterator, bool> res =
        insert(it.getNode()->key, it.getNode()->value);
    if (res.second) other.remove(it.getNode()->key);
  }
}

template <typename K, typename V>
bool RBTree<K, V>::contains(const key_type &key) const {
  return search(getRoot(), key) != nullptr;
}

template <typename K, typename V>
bool RBTree<K, V>::empty() const {
  return getRoot() == nullptr;
}

template <typename K, typename V>
size_t RBTree<K, V>::size() const {
  return countNodes(getRoot());
}

template <typename K, typename V>
size_t RBTree<K, V>::max_size() const {
  return std::numeric_limits<size_t>::max() /
         sizeof(typename RBTree<K, V>::Node);
}
}  // namespace s21