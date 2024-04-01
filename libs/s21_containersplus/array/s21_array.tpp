#include "s21_array.h"

namespace s21 {

/* CONTRUCTORS / COPY / MOVE*/
template <typename T, std::size_t N>
array<T, N>::array() : size_(N) {}

template <typename T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) {
  std::copy(items.begin(), items.end(), data());
}

template <typename T, std::size_t N>
array<T, N>::array(const array<T, N> &other) {
  std::copy(other.data_, other.data_ + N, data_);
}

template <typename T, std::size_t N>
array<T, N>::array(array<T, N> &&other) noexcept {
  std::move(other.data_, other.data_ + N, data_);
}

template <typename T, std::size_t N>
array<T, N> &array<T, N>::operator=(const array &other) {
  if (this != &other) {
    std::copy(other.data(), other.data() + N, data());
  }
  return *this;
}

template <typename T, std::size_t N>
array<T, N> &array<T, N>::operator=(array &&other) {
  if (this != &other) {
    std::move(other.data(), other.data() + N, data());
  }
  return *this;
}

/* ARRAY ELEMENT ACCESS */

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  return (*this)[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  if (pos >= N) {
    throw std::out_of_range("Index out of range");
  }
  return data()[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() const {
  return data_[0];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() const {
  return data_[N - 1];
}

/* ITERATOR */
template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::data() {
  return data_;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() {
  return data();
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() {
  return data() + N;
}

/* CONST ITERATOR */
template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::cdata() const {
  return data_;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::cbegin() const {
  return cdata();
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::cend() const {
  return cdata() + N;
}

/* SIZE */
template <typename T, std::size_t N>
bool array<T, N>::empty() const {
  return !size_;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() const {
  return size_;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() {
  return size();
}

/* OTHER */

template <typename T, std::size_t N>
void array<T, N>::swap(array &other) {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
}

template <typename T, std::size_t N>
void array<T, N>::fill(const_reference val) {
  std::fill(data(), data() + N, val);
}

}  // namespace s21