#include "s21_map.h"
namespace s21 {
template <typename K, typename T>
map<K, T>::map(std::initializer_list<value_type> const &items) {
  for (auto it = items.begin(); it != items.end(); ++it) {
    insert(*it);
  }
}

template <typename K, typename T>
map<K, T> &map<K, T>::operator=(const map &other) {
  if (this != &other) {
    RBTree<K, T>::operator=(other);
  }
  return *this;
}

template <typename K, typename T>
map<K, T> &map<K, T>::operator=(map &&other) noexcept {
  if (this != &other) {
    RBTree<K, T>::operator=(std::move(other));
  }
  return *this;
}

template <typename K, typename T>
T &map<K, T>::at(const K &key) {
  if (!RBTree<K, T>::contains(key)) {
    throw std::out_of_range("map<K, T>::at(): key not found");
  }
  return RBTree<K, T>::search(key);
}

template <typename K, typename T>
T &map<K, T>::operator[](const K &key) {
  if (!RBTree<K, T>::contains(key)) {
    insert(key, T());
  }
  return RBTree<K, T>::search(key);
}

template <typename K, typename T>
std::pair<typename map<K, T>::iterator, bool> map<K, T>::insert(
    const value_type &value) {
  return insert(value.first, value.second);
}

template <typename K, typename T>
std::pair<typename map<K, T>::iterator, bool> map<K, T>::insert(const K &key,
                                                                const T &obj) {
  auto res = RBTree<K, T>::insert(key, obj);
  return {iterator(res.first), res.second};
}

template <typename K, typename T>
std::pair<typename map<K, T>::iterator, bool> map<K, T>::insert_or_assign(
    const K &key, const T &obj) {
  auto res = RBTree<K, T>::insert_or_assign(key, obj);
  return {iterator(res.first), res.second};
}

template <typename K, typename T>
template <class... Args>
std::vector<std::pair<typename map<K, T>::iterator, bool>>
map<K, T>::insert_many(Args &&...args) {
  std::vector<std::pair<iterator, bool>> res;
  for (const auto &arg : {args...}) {
    res.push_back(insert(arg));
  }
  return res;
}

template <typename K, typename T>
typename map<K, T>::iterator map<K, T>::begin() {
  return iterator(RBTree<K, T>::begin());
}

template <typename K, typename T>
typename map<K, T>::iterator map<K, T>::end() {
  return iterator(RBTree<K, T>::end());
}

template <typename K, typename T>
typename map<K, T>::const_iterator map<K, T>::cbegin() const {
  return const_iterator(RBTree<K, T>::cbegin());
}

template <typename K, typename T>
typename map<K, T>::const_iterator map<K, T>::cend() const {
  return const_iterator(RBTree<K, T>::cend());
}

template <typename K, typename T>
typename map<K, T>::value_type &map<K, T>::MapIterator::operator*() {
  typename RBTree<K, T>::Node *node = RBTree<K, T>::Iterator::getNode();

  if (!node) {
    throw std::out_of_range(
        "map<K, T>::MapIterator::operator*(): iterator out of range");
  }
  return node->pair;
}

}  // namespace s21