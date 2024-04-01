#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include "../list/s21_list.h"

namespace s21 {
template <class T, class Container = list<T>>
class queue {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  queue();
  queue(std::initializer_list<value_type> const& items);
  queue(const queue& q);
  queue(queue&& q);
  queue& operator=(const queue& q);
  queue& operator=(queue&& q) noexcept;
  ~queue();

  const_reference front();
  const_reference back();

  void push(const_reference value);
  void pop();
  void swap(queue& other);
  bool empty();
  size_type size();

  template <class... Args>
  void insert_many_back(Args&&... args);

 private:
  Container list_;
};

}  // namespace s21

#include "s21_queue.tpp"

#endif