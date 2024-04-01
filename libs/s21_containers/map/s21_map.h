#ifndef S21_MAP_H_
#define S21_MAP_H_

#include <vector>

#include "../RBTree/s21_rbtree.h"

namespace s21 {
template <typename K, typename T>
class map : public RBTree<K, T> {
 public:
  class MapIterator;
  class ConstMapIterator;

  using key_type = K;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const reference;
  using iterator = MapIterator;
  using const_iterator = ConstMapIterator;
  using size_type = size_t;

  map() : RBTree<K, T>(){};
  map(std::initializer_list<value_type> const &items);
  map(const map &other) : RBTree<K, T>(other){};
  map(map &&other) noexcept : RBTree<K, T>(std::move(other)){};
  map &operator=(const map &other);
  map &operator=(map &&other) noexcept;

  ~map() = default;

  T &at(const K &key);
  T &operator[](const K &key);
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const K &key, const T &obj);
  std::pair<iterator, bool> insert_or_assign(const K &key, const T &obj);

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  class MapIterator : public RBTree<K, T>::Iterator {
   public:
    MapIterator() : RBTree<K, T>::Iterator() {}
    MapIterator(const typename RBTree<K, T>::Iterator &other)
        : RBTree<K, T>::Iterator(other) {}
    value_type &operator*();
  };

  class ConstMapIterator : public RBTree<K, T>::ConstIterator {
   public:
    ConstMapIterator() : RBTree<K, T>::ConstIterator() {}
    ConstMapIterator(const typename RBTree<K, T>::ConstIterator &other)
        : RBTree<K, T>::ConstIterator(other) {}
  };
};
}  // namespace s21
#include "s21_map.tpp"

#endif