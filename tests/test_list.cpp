#include <list>

#include "tests_init.h"

TEST(list, DefaultConstructor) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(list, SizeConstructor) {
  s21::list<int> s21_list(5);
  std::list<int> std_list(5);
  EXPECT_EQ(s21_list.size(), std_list.size());
}

TEST(list, CopyConstructor) {
  s21::list<int> s21_list = {1, 2, 3};
  s21::list<int> s21_list_copy(s21_list);

  EXPECT_EQ(s21_list.size(), s21_list_copy.size());
  EXPECT_EQ(s21_list.front(), s21_list_copy.front());
}

TEST(list, MoveConstructor) {
  s21::list<int> s21_list = {1, 2, 3};
  s21::list<int> s21_list_moved(std::move(s21_list));
  EXPECT_TRUE(s21_list.empty());
  EXPECT_EQ(s21_list_moved.size(), 3);
}

TEST(list, InitializerListConstructor) {
  s21::list<int> s21_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  EXPECT_EQ(s21_list.size(), std_list.size());
}

TEST(list, CopyAssignment) {
  s21::list<int> s21_list = {1, 2, 3};
  s21::list<int> s21_list_copy = s21_list;

  EXPECT_EQ(s21_list_copy.size(), 3);
}

TEST(list, MoveAssignment) {
  s21::list<int> s21_list = {1, 2, 3};
  s21::list<int> s21_list_moved = std::move(s21_list);
  EXPECT_TRUE(s21_list.empty());
  EXPECT_EQ(s21_list_moved.size(), 3);
}

TEST(list, FrontBackPushPop) {
  s21::list<int> s21_list;
  std::list<int> std_list;

  s21_list.push_front(1);
  std_list.push_front(1);
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());

  s21_list.push_back(2);
  std_list.push_back(2);
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());

  s21_list.pop_front();
  std_list.pop_front();
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());

  s21_list.pop_back();
  std_list.pop_back();
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(list, Clear) {
  s21::list<int> s21_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};

  s21_list.clear();
  std_list.clear();
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(list, Swap) {
  s21::list<int> s21_list1 = {1, 2, 3};
  s21::list<int> s21_list2 = {4, 5};
  std::list<int> std_list1 = {1, 2, 3};
  std::list<int> std_list2 = {4, 5};

  s21_list1.swap(s21_list2);
  std_list1.swap(std_list2);
  EXPECT_EQ(s21_list1.size(), std_list1.size());
  EXPECT_EQ(s21_list2.size(), std_list2.size());
}

TEST(list, Merge) {
  s21::list<int> s21_list1 = {1, 3, 5};
  s21::list<int> s21_list2 = {2, 4};

  std::list<int> std_list1 = {1, 3, 5};
  std::list<int> std_list2 = {2, 4};

  s21_list1.merge(s21_list2);
  std_list1.merge(std_list2);
  EXPECT_EQ(s21_list1.size(), std_list1.size());
  EXPECT_TRUE(s21_list2.empty());
  EXPECT_TRUE(std_list2.empty());
}

TEST(list, Splice) {
  s21::list<int> s21_list1 = {1, 2, 3};
  s21::list<int> s21_list2 = {4, 5, 6};
  std::list<int> std_list1 = {1, 2, 3};
  std::list<int> std_list2 = {4, 5, 6};

  auto it = s21_list1.begin();
  ++it;

  s21_list1.splice(it, s21_list2);
  std_list1.splice(std_list1.begin(), std_list2);
  EXPECT_EQ(s21_list1.size(), std_list1.size());
  EXPECT_TRUE(s21_list2.empty());
  EXPECT_TRUE(std_list2.empty());
}

TEST(list, Reverse) {
  s21::list<int> s21_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};

  s21_list.reverse();
  std_list.reverse();

  auto s21_it = s21_list.begin();
  auto std_it = std_list.begin();

  while (s21_it != s21_list.end() && std_it != std_list.end()) {
    EXPECT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
}

TEST(list, Unique) {
  s21::list<int> s21_list = {1, 1, 2, 2, 3, 3, 4, 4};
  std::list<int> std_list = {1, 1, 2, 2, 3, 3, 4, 4};

  s21_list.unique();
  std_list.unique();

  auto s21_it = s21_list.begin();
  auto std_it = std_list.begin();

  while (s21_it != s21_list.end() && std_it != std_list.end()) {
    EXPECT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
}

TEST(list, Sort) {
  s21::list<int> s21_list = {3, 2, 5, 1, 4};
  std::list<int> std_list = {3, 2, 5, 1, 4};

  s21_list.sort();
  std_list.sort();

  auto s21_it = s21_list.begin();
  auto std_it = std_list.begin();

  while (s21_it != s21_list.end() && std_it != std_list.end()) {
    EXPECT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
}

TEST(list, MergeSorted) {
  s21::list<int> s21_list_left = {1, 3, 5};
  s21::list<int> s21_list_right = {2, 4};
  s21::list<int> s21_list_result;

  std::list<int> std_list_left = {1, 3, 5};
  std::list<int> std_list_right = {2, 4};
  std::list<int> std_list_result;

  s21_list_result.merge_sorted(s21_list_left, s21_list_right);
  std_list_result.merge(std_list_left);
  std_list_result.merge(std_list_right);

  auto s21_it = s21_list_result.begin();
  auto std_it = std_list_result.begin();

  while (s21_it != s21_list_result.end() && std_it != std_list_result.end()) {
    EXPECT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
}

TEST(list, Erase) {
  s21::list<int> s21_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};

  auto s21_it = s21_list.begin();
  s21_list.erase(s21_it);

  auto std_it = std_list.begin();
  std_list.erase(std_it);

  EXPECT_EQ(s21_list.size(), std_list.size());

  auto s21_list_it = s21_list.begin();
  auto std_list_it = std_list.begin();
  while (s21_list_it != s21_list.end() && std_list_it != std_list.end()) {
    EXPECT_EQ(*s21_list_it, *std_list_it);
    ++s21_list_it;
    ++std_list_it;
  }
}

TEST(list, Insert_many) {
  s21::list<int> test_list;
  test_list.push_back(1);
  test_list.push_back(3);
  auto pos = test_list.begin();

  ++pos;

  test_list.insert_many(pos, 2, 4, 5);

  s21::list<int> expected_list;
  expected_list.push_back(1);
  expected_list.push_back(2);
  expected_list.push_back(4);
  expected_list.push_back(5);
  expected_list.push_back(3);

  auto it_test = test_list.begin();
  auto it_expected = expected_list.begin();

  for (; it_test != test_list.end() && it_expected != expected_list.end();
       ++it_test, ++it_expected) {
    EXPECT_EQ(*it_test, *it_expected);
  }

  EXPECT_EQ(test_list.size(), expected_list.size());
}

TEST(list, InsertManyBack) {
  s21::list<int> test_list;
  test_list.push_back(1);
  test_list.push_back(2);

  test_list.insert_many_back(3, 4, 5);

  s21::list<int> expected_list{1, 2, 3, 4, 5};

  auto it_test = test_list.begin();
  auto it_expected = expected_list.begin();

  for (; it_test != test_list.end() && it_expected != expected_list.end();
       ++it_test, ++it_expected) {
    EXPECT_EQ(*it_test, *it_expected);
  }

  EXPECT_EQ(it_test, test_list.end());
  EXPECT_EQ(it_expected, expected_list.end());

  EXPECT_EQ(test_list.size(), expected_list.size());
}

TEST(list, InsertManyFront) {
  s21::list<int> test_list;
  test_list.push_back(3);
  test_list.push_back(4);

  test_list.insert_many_front(1, 2);

  s21::list<int> expected_list{2, 1, 3, 4};

  auto it_test = test_list.begin();
  auto it_expected = expected_list.begin();

  for (; it_test != test_list.end() && it_expected != expected_list.end();
       ++it_test, ++it_expected) {
    EXPECT_EQ(*it_test, *it_expected);
  }

  EXPECT_EQ(it_test, test_list.end());
  EXPECT_EQ(it_expected, expected_list.end());

  EXPECT_EQ(test_list.size(), expected_list.size());
}
