#include "s21_queue.h"

namespace s21 {

template <class T, class Container>
queue<T, Container>::queue() : list_() {}

template <class T, class Container>
queue<T, Container>::queue(std::initializer_list<value_type> const& items)
    : list_(items) {}

template <class T, class Container>
queue<T, Container>::queue(const queue& q) : list_(q.list_) {}

template <class T, class Container>
queue<T, Container>::queue(queue&& q) : list_(std::move(q.list_)) {}

template <class T, class Container>
queue<T, Container>& queue<T, Container>::operator=(const queue& q) {
  list_ = q.list_;
  return *this;
}

template <class T, class Container>
queue<T, Container>& queue<T, Container>::operator=(queue&& q) noexcept {
  list_ = std::move(q.list_);
  return *this;
}

template <class T, class Container>
queue<T, Container>::~queue() {}

template <class T, class Container>
typename queue<T, Container>::const_reference queue<T, Container>::front() {
  return list_.front();
}

template <class T, class Container>
typename queue<T, Container>::const_reference queue<T, Container>::back() {
  return list_.back();
}

template <class T, class Container>
void queue<T, Container>::push(const_reference value) {
  list_.push_back(value);
}

template <class T, class Container>
void queue<T, Container>::pop() {
  list_.pop_front();
}

template <class T, class Container>
void queue<T, Container>::swap(queue& other) {
  list_.swap(other.list_);
}

template <typename T, class Container>
bool queue<T, Container>::empty() {
  return list_.empty();
}

template <typename T, class Container>
typename queue<T, Container>::size_type queue<T, Container>::size() {
  return list_.size();
}

template <class T, class Container>
template <class... Args>
void queue<T, Container>::insert_many_back(Args&&... args) {
  for (const auto& arg : {args...}) {
    list_.push_back(arg);
  }
}

}  // namespace s21