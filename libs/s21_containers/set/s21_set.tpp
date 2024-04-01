#include "s21_set.h"

namespace s21 {

template <typename V>
set<V>::set(std::initializer_list<value_type> const &items) {
  for (auto it = items.begin(); it != items.end(); it++) {
    RBTree<V, V>::insert(*it, *it);
  }
}

template <typename V>
set<V> &set<V>::operator=(const set &other) {
  if (this != &other) {
    RBTree<V, V>::operator=(other);
  }
  return *this;
}

template <typename V>
set<V> &set<V>::operator=(set &&other) noexcept {
  if (this != &other) {
    RBTree<V, V>::operator=(std::move(other));
  }
  return *this;
}

template <typename V>
std::pair<typename set<V>::iterator, bool> set<V>::insert(
    const value_type &value) {
  auto res = RBTree<V, V>::insert(value, value);
  return {iterator(res.first), res.second};
}

template <typename V>
template <class... Args>
std::vector<std::pair<typename set<V>::iterator, bool>> set<V>::insert_many(
    Args &&...args) {
  std::vector<std::pair<iterator, bool>> res;
  for (const auto &arg : {args...}) {
    res.push_back(RBTree<V, V>::insert(arg, arg));
  }
  return res;
}

}  // namespace s21