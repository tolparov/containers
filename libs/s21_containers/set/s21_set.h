#ifndef S21_SET_H_
#define S21_SET_H_

#include <vector>

#include "../RBTree/s21_rbtree.h"

namespace s21 {
template <typename V>
class set : public RBTree<V, V> {
 public:
  using key_type = V;
  using value_type = V;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename RBTree<V, V>::Iterator;
  using const_iterator = typename RBTree<V, V>::ConstIterator;
  using size_type = size_t;

  set() : RBTree<V, V>() {}
  set(std::initializer_list<value_type> const &items);
  set(const set &other) : RBTree<V, V>(other) {}
  set(set &&other) noexcept : RBTree<V, V>(std::move(other)) {}
  set &operator=(const set &other);
  set &operator=(set &&other) noexcept;

  ~set() = default;

  std::pair<iterator, bool> insert(const value_type &value);
  iterator find(const key_type &key) { return RBTree<V, V>::find(key); };
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};
}  // namespace s21
#include "s21_set.tpp"

#endif