#ifndef S21_LIST_H
#define S21_LIST_H

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
class list {
 private:
  struct Node {
    T value;
    Node* prev;
    Node* next;
    Node(T val) : value(val), prev(nullptr), next(nullptr) {}
  };

  Node* head_;
  Node* tail_;
  size_t size_;

 public:
  class ListIterator;
  class ListConstIterator;

  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = std::size_t;

  list();
  list(size_type n);
  list(const list& other);
  list(list&& other) noexcept;
  list(std::initializer_list<T> const& init);
  list<T>& operator=(const list& other);
  list<T>& operator=(list&& other);

  ~list();

  bool empty() const;
  size_t size() const;
  size_t max_size() const;

  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;

  void push_front(const_reference value);
  void push_back(const_reference value);
  void pop_front();
  void pop_back();
  void clear();
  void swap(list& other);
  void merge(list& other);
  void splice(iterator pos, list& other);
  void reverse();
  void unique();
  void sort();
  void merge_sorted(list& left, list& right);

  iterator insert(iterator pos, const_reference value);
  iterator begin();
  iterator end();
  iterator erase(iterator pos);

  template <class... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <class... Args>
  void insert_many_back(Args&&... args);
  template <class... Args>
  void insert_many_front(Args&&... args);

  class ListIterator {
   public:
    ListIterator(Node* ptr) : current(ptr){};
    T& operator*() const;
    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;
    Node* getNode();

   protected:
    Node* current;
  };

  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator(Node* ptr) : iterator(ptr){};
    ListConstIterator(const ListIterator& other) : ListIterator(other){};
    const_reference operator*() const { iterator::operator*(); };
  };
};
}  // namespace s21

#include "s21_list.tpp"
#endif