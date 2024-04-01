#include <iostream>
#include <vector>

#include "s21_vector.h"

namespace s21 {
template <typename T>
vector<T>::vector(size_type n)
    : _size(n), _capacity(n), _obj(new value_type[n]) {
  for (size_type i = 0; i < _size; i++) _obj[i] = value_type();
}

template <typename T>
vector<T>::vector(std::initializer_list<T> const& items)
    : _size(items.size()),
      _capacity(items.size()),
      _obj(new value_type[items.size()]) {
  std::copy(items.begin(), items.end(), _obj);
}

template <typename T>
vector<T>::vector(const vector& v)
    : _size(v._size), _capacity(v._capacity), _obj(new T[v._size]) {
  for (size_type i = 0; i < _size; i++) _obj[i] = v._obj[i];
}

template <typename T>
vector<T>::vector(vector&& v)
    : _size(v._size), _capacity(v._capacity), _obj(v._obj) {
  v._obj = nullptr;
}

template <typename T>
vector<T>::~vector() {
  delete[] _obj;
}

template <typename T>
vector<T>& vector<T>::operator=(vector<T>&& v) {
  if (this != &v) {
    swap(v);

    delete[] v._obj;
    v._size = 0;
    v._capacity = 0;
    v._obj = nullptr;
  }

  return *this;
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  if (pos >= _size) throw std::out_of_range("Index out of range");

  return _obj[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::operator[](size_type pos) const {
  if (pos >= _size) throw std::out_of_range("Index out of range");

  return _obj[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= _size) throw std::out_of_range("Index out of range");

  return _obj[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() const {
  if (_size == 0) throw std::out_of_range("Vector is empty");

  return _obj[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() const {
  if (_size == 0) throw std::out_of_range("Vector is empty");

  return _obj[_size - 1];
}

template <typename T>
typename vector<T>::iterator_pointer vector<T>::data() noexcept {
  return _obj;
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return iterator(_obj);
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return iterator(_obj + _size);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cbegin() const {
  return const_iterator(_obj);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cend() const {
  return const_iterator(_obj + _size);
}

template <typename T>
bool vector<T>::empty() const {
  return (_size == 0);
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const {
  return _size;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() const {
  return std::numeric_limits<long>::max() / sizeof(T);
  ;
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() {
  return _capacity;
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size < _capacity) return;

  if (size > max_size())
    throw std::out_of_range("Too large size for a new capacity");

  iterator_pointer tmp = new T[size];
  std::copy(_obj, _obj + _size, tmp);
  delete[] _obj;
  _obj = tmp;
  _capacity = size;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (_size == _capacity) return;

  iterator_pointer tmp = new value_type[_size];
  std::copy(_obj, _obj + _size, tmp);
  delete[] _obj;
  _obj = tmp;
  _capacity = _size;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (_size == _capacity) reserve(_capacity ? _capacity * 2 : 1);

  _obj[_size++] = value;
}

template <typename T>
void vector<T>::pop_back() {
  if (_size > 0) _size--;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  if ((size_type)(pos - _obj) > _size)
    throw std::out_of_range("Index out of range");

  for (iterator it = pos; it != end() - 1; it++) *it = *(it + 1);

  _size--;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type idx = pos - begin();

  if (idx > _size) throw std::out_of_range("Position is out of range");

  if (_size == _capacity) reserve(_capacity ? _capacity * 2 : 1);

  iterator new_pos = begin() + idx;

  for (iterator it = end(); it != new_pos; --it) *it = *(it - 1);

  *new_pos = value;
  _size++;

  return new_pos;
}

template <typename T>
void vector<T>::clear() {
  _size = 0;
}

template <typename T>
void vector<T>::swap(vector& other) {
  std::swap(_capacity, other._capacity);
  std::swap(_size, other._size);
  std::swap(_obj, other._obj);
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args&&... args) {
  vector<value_type> tmp{args...};
  iterator current = begin() + (pos - cbegin());

  for (size_type i = 0; i < tmp.size(); i++) {
    current = insert(current, tmp[i]);
    ++current;
  }

  return current;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args&&... args) {
  insert_many(cend(), args...);
}
}  // namespace s21