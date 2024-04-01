#ifndef S21_STACK_H_
#define S21_STACK_H_

#include <iostream>
#include <limits>
namespace s21 {
template <typename T>
class stack {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  stack();
  stack(std::initializer_list<value_type> const& items);
  stack(const stack& other);
  stack(stack&& other);
  stack& operator=(const stack& other);
  stack& operator=(stack&& other);
  ~stack();

  const_reference top();
  void push(const_reference value);
  void pop();
  void swap(stack& other);

  bool empty();
  size_type size();
  void clear();

  template <typename... Args>
  void insert_many_front(Args&&... args);

 private:
  T* data_;
  size_type count_;
  size_type size_;
  void resize();
};
}  // namespace s21

#include "s21_stack.tpp"

#endif