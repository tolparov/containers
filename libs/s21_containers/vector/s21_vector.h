#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <limits>

namespace s21 {
template <typename T>
class vector {
 public:
  class vectorIter;
  class vectorConstIter;

  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator_pointer = T*;
  using const_iterator_pointer = const T*;
  using iterator = vector<T>::vectorIter;
  using const_iterator = vector<T>::vectorConstIter;
  using size_type = std::size_t;

  vector() : _size(0), _capacity(0), _obj(0) {}
  vector(size_type n);
  vector(std::initializer_list<T> const& items);
  vector(const vector& v);
  vector(vector&& v);
  ~vector();

  vector& operator=(vector<T>&& v);
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;

  reference at(size_type pos);
  const_reference front() const;
  const_reference back() const;
  iterator_pointer data() noexcept;

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  size_type capacity();
  void reserve(size_type size);
  void shrink_to_fit();

  void push_back(const_reference value);
  void pop_back();
  void erase(iterator pos);
  iterator insert(iterator pos, const_reference value);
  void clear();
  void swap(vector& other);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);

 private:
  size_type _size;
  size_type _capacity;
  iterator_pointer _obj;
};
}  // namespace s21

#include "s21_iter.hpp"
#include "s21_vector.tpp"

#endif /* S21_VECTOR_H */