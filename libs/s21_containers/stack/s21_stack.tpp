#include "s21_stack.h"

namespace s21 {

template <typename T>
stack<T>::stack() : data_(nullptr), count_(0), size_(0) {}

template <typename T>
stack<T>::stack(std::initializer_list<T> const& items)
    : data_(nullptr), count_(0), size_(0) {
  for (auto it = items.begin(); it != items.end(); it++) {
    push(*it);
  }
}

template <typename T>
stack<T>::stack(const stack& other)
    : data_(new value_type[other.size_]),
      count_(other.count_),
      size_(other.size_) {
  std::copy(other.data_, other.data_ + size_, data_);
}

template <typename T>
stack<T>::stack(stack&& other)
    : data_(other.data_), count_(other.count_), size_(other.size_) {
  other.data_ = nullptr;
  other.count_ = 0;
}

template <typename T>
stack<T>& stack<T>::operator=(const stack& other) {
  if (this != &other) {
    delete[] data_;
    size_ = other.size_;
    count_ = other.count_;
    data_ = new value_type[size_];
    std::copy(other.data_, other.data_ + size_, data_);
  }

  return *this;
}

template <typename T>
stack<T>& stack<T>::operator=(stack&& other) {
  if (this != &other) {
    delete[] data_;
    size_ = other.size_;
    count_ = other.count_;
    data_ = other.data_;
    other.data_ = nullptr;
    other.count_ = 0;
  }

  return *this;
}

template <typename T>
stack<T>::~stack() {
  delete[] data_;
  data_ = nullptr;
}

template <typename T>
typename stack<T>::const_reference stack<T>::top() {
  if (empty()) {
    throw std::out_of_range("stack::top(): Stack is empty");
  }
  return data_[count_ - 1];
}

template <typename T>
void stack<T>::push(const_reference value) {
  if (count_ == size_) {
    resize();
  }
  data_[count_++] = value;
}

template <typename T>
void stack<T>::pop() {
  if (!count_) {
    throw std::out_of_range("stack::pop(): Stack is empty");
  }
  count_--;
}

template <typename T>
void stack<T>::swap(stack& other) {
  std::swap(size_, other.size_);
  std::swap(count_, other.count_);
  std::swap(data_, other.data_);
}

template <typename T>
void stack<T>::resize() {
  if (!size_) size_ = 1;
  T* tmp = new T[size_ * 2];
  std::copy(data_, data_ + count_, tmp);
  delete[] data_;
  data_ = tmp;
  size_ *= 2;
}

template <typename T>
void stack<T>::clear() {
  for (size_type i = 0; i < count_; ++i) {
    data_[i].~T();
  }
  count_ = 0;
}

template <typename T>
bool stack<T>::empty() {
  return (count_ == 0);
}

template <typename T>
typename stack<T>::size_type stack<T>::size() {
  return count_;
}

template <typename T>
template <class... Args>
void stack<T>::insert_many_front(Args&&... args) {
  for (const auto& arg : {args...}) {
    push(arg);
  }
}
}  // namespace s21