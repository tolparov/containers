#ifndef S21_RBTREE_H_
#define S21_RBTREE_H_

#include <cstddef>
#include <iostream>
#include <limits>

namespace s21 {
enum Color { RED, BLACK };
template <typename K, typename V>
class RBTree {
 protected:
  struct Node {
    K key;
    V value;
    std::pair<const K, V> pair; /* for map */
    Color color;
    Node *parent, *left, *right;
    Node(const K &k, const V &v)
        : key(k),
          value(v),
          pair(std::make_pair(k, v)),
          color(RED),
          parent(nullptr),
          left(nullptr),
          right(nullptr){};
  };

 public:
  class Iterator;
  class ConstIterator;

  using key_type = K;
  using value_type = V;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using size_type = size_t;

  RBTree();
  RBTree(const RBTree &other);
  RBTree(RBTree &&other) noexcept;
  RBTree &operator=(const RBTree &other);
  RBTree &operator=(RBTree &&other) noexcept;

  ~RBTree();
  void clear();

  reference search(const key_type &key);
  std::pair<iterator, bool> insert(const key_type &key, const_reference val);
  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const_reference val);
  void remove(const key_type &key);
  void erase(iterator pos);
  void swap(RBTree &other) noexcept;
  void merge(RBTree &other);
  bool contains(const key_type &key) const;
  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;
  iterator find(const key_type &key);
  class Iterator {
   protected:
    Node *current_;
    Node *prev_;

   public:
    Iterator();
    Iterator(Node *node);
    Iterator(const Iterator &other);
    Iterator &operator=(const Iterator &other);
    iterator &operator++();
    iterator operator++(int);
    iterator &operator--();
    iterator operator--(int);
    reference operator*();
    value_type *operator->();
    bool operator==(const iterator &other) const;
    bool operator!=(const iterator &other) const;
    Node *successor(Node *node);
    Node *predecessor(Node *node);
    Node *getNode() const;
  };

  class ConstIterator : public Iterator {
   public:
    ConstIterator() : Iterator(){};
    ConstIterator(Node *node) : Iterator(node){};
    const_reference operator*() const { return this->current_->value; };
  };

 private:
  Node *root_;

  /* Red Black Tree struct fixers and helpers */
  void fixInsert(Node *z);
  void fixDelete(Node *x, Node *x_parent);

  Node *fixDeleteCaseLeft(Node *x, Node *x_parent);
  Node *fixDeleteCaseRight(Node *x, Node *x_parent);
  void recolorForLeftRotate(Node *x_parent, Node *w);
  void recolorForRightRotate(Node *x_parent, Node *w);
  Node *adjustBlackNodeLeft(Node *x, Node *x_parent, Node *w);
  Node *adjustBlackNodeRight(Node *x, Node *x_parent, Node *w);
  Node *rotateAtBlackNodeLeft(Node *w, Node *x_parent);
  Node *rotateAtBlackNodeRight(Node *w, Node *x_parent);
  void leftRotate(Node *x);
  void rightRotate(Node *y);

  /* Insert and Deletion */
  void insertNode(Node *z);
  Node *deleteNode(Node *z);
  void clearNode(Node *node);
  void transplant(Node *u, Node *v);

  /* Helpers */
  Node *search(Node *node, const K &key) const;
  Node *minimum(Node *node) const;
  Node *maximum(Node *node) const;

  size_type countNodes(Node *node) const;
  Node *copyTree(Node *node, Node *parent);

  Node *getRoot() const;
  const Node *cgetRoot() const;
  void setRoot(Node *root) noexcept;
  Color getColor(Node *node) const;
  void setColor(Node *node, Color color);
};
}  // namespace s21

#include "s21_rbtree.tpp"

#endif  // S21_RBTREE_H_