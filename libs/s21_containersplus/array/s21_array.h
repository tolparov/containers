#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <iostream>
#include <limits>

namespace s21 {
template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  array();
  array(std::initializer_list<value_type> const &items);
  array(const array &other);
  array(array &&other) noexcept;
  array &operator=(const array &other);
  array &operator=(array &&other);
  ~array() = default;

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() const;
  const_reference back() const;

  iterator data();
  iterator begin();
  iterator end();
  
  const_iterator cdata() const;
  const_iterator cbegin() const;
  const_iterator cend() const;

  bool empty() const;
  size_type size() const;
  size_type max_size();

  void swap(array &other);
  void fill(const_reference val);

 private:
  value_type data_[N] = {};
  size_type size_ = N;
};
}  // namespace s21
#include "s21_array.tpp"

#endif