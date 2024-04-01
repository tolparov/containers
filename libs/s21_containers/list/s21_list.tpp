#include "s21_list.h"

namespace s21 {
template <typename T>
list<T>::list() {
  head_ = nullptr;
  tail_ = nullptr;
  size_ = 0;
}

template <typename T>
list<T>::list(size_type n) : list() {
  if (n > 0) {
    for (size_type i = 0; i < n; ++i) {
      push_front(value_type());
    }
  }
}

template <typename T>
list<T>& list<T>::operator=(const list& other) {
  if (this != &other) {
    clear();
    Node* current = other.head_;
    while (current) {
      push_back(current->value);
      current = current->next;
    }
  }
  return *this;
}

template <typename T>
list<T>& list<T>::operator=(list&& other) {
  if (this != &other) {
    clear();

    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;

    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <typename T>
list<T>::list(const list& other) : list() {
  Node* currrent = other.head_;
  while (currrent) {
    push_back(currrent->value);
    currrent = currrent->next;
  }
}

template <typename T>
list<T>::list(list&& other) noexcept {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;
}

template <typename T>
list<T>::list(std::initializer_list<T> const& init)
    : head_(nullptr), tail_(nullptr), size_(0) {
  for (const T& value : init) {
    push_back(value);
  }
}

template <typename T>
list<T>::~list() {
  clear();
}

template <typename T>
bool list<T>::empty() const {
  return size_ == 0;
}

template <typename T>
size_t list<T>::size() const {
  return size_;
}

template <typename T>
size_t list<T>::max_size() const {
  return std::numeric_limits<size_t>::max() / sizeof(T);
}

template <typename T>
void list<T>::clear() {
  Node* current = head_;
  while (current != nullptr) {
    Node* next = current->next;
    delete current;
    current = next;
  }
  head_ = nullptr;
  tail_ = nullptr;
  size_ = 0;
}

template <typename T>
T& list<T>::front() {
  return head_->value;
}

template <typename T>
const T& list<T>::front() const {
  return head_->value;
}

template <typename T>
T& list<T>::back() {
  return tail_->value;
}

template <typename T>
const T& list<T>::back() const {
  return tail_->value;
}

template <typename T>
void list<T>::push_front(const_reference value) {
  Node* new_node = new Node(value);
  new_node->next = head_;
  if (head_) {
    head_->prev = new_node;
  }
  head_ = new_node;
  if (!tail_) {
    tail_ = new_node;
  }
  size_++;
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  Node* new_node = new Node(value);
  new_node->prev = pos.getNode()->prev;
  new_node->next = pos.getNode();

  if (pos.getNode()->prev != nullptr) {
    pos.getNode()->prev->next = new_node;
  } else {
    head_ = new_node;
  }

  pos.getNode()->prev = new_node;
  ++size_;
  return iterator(new_node);
}

template <typename T>
void list<T>::push_back(const_reference value) {
  Node* new_node = new Node(value);
  new_node->prev = tail_;
  new_node->next = nullptr;

  if (tail_) {
    tail_->next = new_node;
  }

  tail_ = new_node;

  if (!head_) {
    head_ = new_node;
  }
  ++size_;
}

template <typename T>
void list<T>::pop_front() {
  if (head_) {
    Node* tmp = head_;
    head_ = head_->next;
    if (head_) {
      head_->prev = nullptr;
    } else {
      tail_ = nullptr;
    }
    delete tmp;
    --size_;
  }
}
template <typename T>
void list<T>::pop_back() {
  if (tail_) {
    Node* tmp = tail_;
    tail_ = tail_->prev;
    if (tail_) {
      tail_->next = nullptr;
    } else {
      head_ = nullptr;
    }
    delete tmp;
    --size_;
  }
}

template <typename T>
T& list<T>::ListIterator::operator*() const {
  return current->value;
}

template <typename T>
typename list<T>::iterator& list<T>::ListIterator::operator++() {
  current = current->next;
  return *this;
}

template <typename T>
typename list<T>::iterator list<T>::ListIterator::operator++(int) {
  iterator tmp = *this;
  ++(*this);
  return tmp;
}

template <typename T>
typename list<T>::iterator& list<T>::ListIterator::operator--() {
  current = current->prev;
  return *this;
}

template <typename T>
typename list<T>::iterator list<T>::ListIterator::operator--(int) {
  iterator tmp = *this;
  --(*this);
  return tmp;
}

template <typename T>
bool list<T>::ListIterator::operator==(const iterator& other) const {
  return current == other.current;
}

template <typename T>
bool list<T>::ListIterator::operator!=(const iterator& other) const {
  return current != other.current;
}

template <typename T>
typename list<T>::Node* list<T>::ListIterator::getNode() {
  return current;
}

template <typename T>
typename list<T>::iterator list<T>::begin() {
  return iterator(head_);
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  return iterator(nullptr);
}

template <typename T>
typename list<T>::iterator list<T>::erase(iterator pos) {
  if (*pos == tail_->value) {
    return iterator(tail_);
  }

  Node* nodeToRemove = pos.getNode();
  iterator nextIter = ++pos;

  if (nodeToRemove->prev != nullptr) {
    nodeToRemove->prev->next = nodeToRemove->next;
  } else {
    head_ = nodeToRemove->next;
  }

  if (nodeToRemove->next != nullptr) {
    nodeToRemove->next->prev = nodeToRemove->prev;
  } else {
    head_ = nodeToRemove->prev;
  }

  delete nodeToRemove;

  --size_;

  return nextIter;
}

template <typename T>
void list<T>::swap(list& other) {
  std::swap(*this, other);
}

template <typename T>
void list<T>::merge(list& other) {
  merge_sorted(*this, other);
}

template <typename T>
void list<T>::reverse() {
  if (size_ > 1) {
    Node* current = head_;
    Node* prevNode = nullptr;
    Node* nextNode = nullptr;

    while (current != nullptr) {
      nextNode = current->next;  // b
      current->next = prevNode;  // a
      current->prev = nextNode;
      prevNode = current;
      current = nextNode;
    }
    std::swap(head_, tail_);
  }
}
template <typename T>
void list<T>::merge_sorted(list& left, list& right) {
  Node* left_node = left.head_;
  Node* right_node = right.head_;
  Node* node = nullptr;

  Node* thisHead = nullptr;
  Node* thistail = nullptr;
  size_t thisSize = 0;

  while (left_node != nullptr || right_node != nullptr) {
    Node* next_node;
    bool choose_left =
        right_node == nullptr ||
        (left_node != nullptr && left_node->value <= right_node->value);

    if (choose_left) {
      next_node = left_node;
      left_node = left_node->next;
    } else {
      next_node = right_node;
      right_node = right_node->next;
    }

    if (node != nullptr) {
      node->next = next_node;
      next_node->prev = node;
    } else {
      thisHead = next_node;
      next_node->prev = nullptr;
    }

    node = next_node;
  }

  thistail = node;
  thisSize = left.size_ + right.size_;

  left.head_ = nullptr;
  left.tail_ = nullptr;
  left.size_ = 0;

  right.head_ = nullptr;
  right.tail_ = nullptr;
  right.size_ = 0;

  head_ = thisHead;
  tail_ = thistail;
  size_ = thisSize;
}

template <typename T>
void list<T>::unique() {
  if (size_ <= 1) {
    return;
  }

  Node* current = head_;
  Node* nextNode = nullptr;
  Node* prevNode = nullptr;

  while (current != nullptr) {
    nextNode = current->next;

    if (nextNode != nullptr && current->value == nextNode->value) {
      if (prevNode == nullptr) {
        head_ = nextNode;
      } else {
        prevNode->next = nextNode;
      }
      delete current;
      current = nextNode;
    } else {
      prevNode = current;
      current = nextNode;
    }
  }
  tail_ = prevNode;
}

template <typename T>
void list<T>::splice(iterator pos, list& other) {
  if (other.empty()) {
    return;
  }

  Node* before = (pos == begin()) ? nullptr : pos.getNode()->prev;
  Node* after = (pos == end()) ? nullptr : pos.getNode();

  if (before != nullptr) {
    before->next = other.head_;
  } else {
    head_ = other.head_;
  }
  other.head_->prev = before;

  if (after != nullptr) {
    after->prev = other.tail_;
  } else {
    tail_ = other.tail_;
  }
  other.tail_->next = after;

  size_ += other.size_;
  other.size_ = 0;
  other.head_ = nullptr;
  other.tail_ = nullptr;
}

template <typename T>
void list<T>::sort() {
  if (size_ <= 1) {
    return;
  }

  list<T> left_half;
  list<T> right_half;

  Node* middle = head_;
  Node* current = head_;

  while (current != nullptr && current->next != nullptr) {
    current = current->next->next;
    if (current != nullptr) {
      middle = middle->next;
    }
  }

  right_half.head_ = middle->next;
  right_half.tail_ = tail_;
  right_half.size_ = size_ / 2;

  left_half.head_ = head_;
  left_half.tail_ = middle;
  left_half.size_ = size_ - right_half.size_;

  middle->next = nullptr;
  right_half.head_->prev = nullptr;

  left_half.sort();
  right_half.sort();

  merge_sorted(left_half, right_half);
}

template <typename T>
template <class... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args&&... args) {
  for (const auto& arg : {args...}) {
    insert(pos, arg);
  }
  return pos;
}

template <typename T>
template <class... Args>
void list<T>::insert_many_back(Args&&... args) {
  for (const auto& arg : {args...}) {
    push_back(arg);
  }
}

template <typename T>
template <class... Args>
void list<T>::insert_many_front(Args&&... args) {
  for (const auto& arg : {args...}) {
    push_front(arg);
  }
}

}  // namespace s21