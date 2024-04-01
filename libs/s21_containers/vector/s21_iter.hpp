#ifndef S21_ITER_HPP
#define S21_ITER_HPP

#include "s21_vector.h"

namespace s21 {
template <typename T>
class vector<T>::vectorIter {
 public:
  vectorIter() = default;
  vectorIter(iterator_pointer ptr) : _ptr(ptr) {}

  reference operator*() { return *_ptr; }

  vectorIter operator++(int) {
    vectorIter tmp(*this);
    _ptr++;
    return tmp;
  }

  vectorIter operator--(int) {
    vectorIter tmp(*this);
    _ptr--;
    return tmp;
  }

  vectorIter& operator++() {
    _ptr++;
    return *this;
  }

  vectorIter& operator--() {
    _ptr--;
    return *this;
  }

  bool operator==(const vectorIter& other) const { return _ptr == other._ptr; }

  bool operator!=(const vectorIter& other) const { return _ptr != other._ptr; }

  vectorIter operator+(int n) const {
    vectorIter tmp(*this);
    for (int i = 0; i < n; i++) tmp++;

    return tmp;
  }

  vectorIter operator-(int n) const {
    vectorIter tmp(*this);
    for (int i = 0; i < n; i++) tmp--;

    return tmp;
  }

  ptrdiff_t operator-(const vectorIter& other) const {
    return _ptr - other._ptr;
  }

 private:
  iterator_pointer _ptr;
};

template <typename T>
class vector<T>::vectorConstIter : public vectorIter {
 public:
  vectorConstIter() = default;
  vectorConstIter(const_iterator_pointer ptr) : _ptr(ptr) {}

  const_reference operator*() const { return *_ptr; }

  vectorConstIter operator++(int) {
    vectorConstIter tmp(*this);
    _ptr++;
    return tmp;
  }

  vectorConstIter operator--(int) {
    vectorConstIter tmp(*this);
    _ptr--;
    return tmp;
  }

  vectorConstIter& operator++() {
    _ptr++;
    return *this;
  }

  vectorConstIter& operator--() {
    _ptr--;
    return *this;
  }

  bool operator==(const vectorConstIter& other) const {
    return _ptr == other._ptr;
  }

  bool operator!=(const vectorConstIter& other) const {
    return _ptr != other._ptr;
  }

  vectorConstIter operator+(int n) const {
    vectorConstIter tmp(*this);
    for (int i = 0; i < n; i++) tmp++;

    return tmp;
  }

  vectorConstIter operator-(int n) const {
    vectorConstIter tmp(*this);
    for (int i = 0; i < n; i++) tmp--;

    return tmp;
  }

  ptrdiff_t operator-(const vectorConstIter& other) const {
    return _ptr - other._ptr;
  }

 private:
  const_iterator_pointer _ptr;
};

}  // namespace s21

#endif /* S21_ITER_HPP */