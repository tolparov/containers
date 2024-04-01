#include <set>

#include "tests_init.h"

TEST(set, DefaultContructor) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  EXPECT_EQ(s21_set.size(), std_set.size());
}

TEST(set, InitListConstructor) {
  s21::set<int> s21_set = {1, 2, 3, 3};
  std::set<int> std_set = {1, 2, 3, 3};
  EXPECT_EQ(s21_set.size(), std_set.size());

  auto s21_it = s21_set.begin();
  auto std_it = std_set.begin();
  for (; s21_it != s21_set.end(); ++s21_it, ++std_it) {
    EXPECT_TRUE(*s21_it == *std_it);
  }
}

TEST(set, CopyConstructor) {
  s21::set<int> s21_set = {1, 2, 3, 3};
  s21::set<int> s21_set_copy(s21_set);
  std::set<int> std_set = {1, 2, 3, 3};
  std::set<int> std_set_copy(std_set);

  EXPECT_EQ(s21_set_copy.size(), std_set_copy.size());

  auto s21_it = s21_set_copy.begin();
  auto std_it = std_set_copy.begin();

  for (; s21_it != s21_set_copy.end(); ++s21_it, ++std_it) {
    EXPECT_TRUE(*s21_it == *std_it);
  }
}

TEST(set, MoveConstructor) {
  s21::set<int> s21_set = {1, 2, 3, 3};
  s21::set<int> s21_set_copy(std::move(s21_set));
  std::set<int> std_set = {1, 2, 3, 3};
  std::set<int> std_set_copy(std::move(std_set));

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set_copy.size(), std_set_copy.size());

  auto s21_it = s21_set_copy.begin();
  auto std_it = std_set_copy.begin();

  for (; s21_it != s21_set_copy.end(); ++s21_it, ++std_it) {
    EXPECT_TRUE(*s21_it == *std_it);
  }
}

TEST(set, CopyAssignment) {
  s21::set<int> s21_set = {1, 2, 3, 3};
  s21::set<int> s21_set_copy = s21_set;
  std::set<int> std_set = {1, 2, 3, 3};
  std::set<int> std_set_copy = std_set;

  EXPECT_EQ(s21_set_copy.size(), std_set_copy.size());

  auto s21_it = s21_set_copy.begin();
  auto std_it = std_set_copy.begin();

  for (; s21_it != s21_set_copy.end(); ++s21_it, ++std_it) {
    EXPECT_TRUE(*s21_it == *std_it);
  }
}

TEST(set, MoveAssignment) {
  s21::set<int> s21_set = {1, 2, 3, 3};
  s21::set<int> s21_set_copy = std::move(s21_set);
  std::set<int> std_set = {1, 2, 3, 3};
  std::set<int> std_set_copy = std::move(std_set);

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set_copy.size(), std_set_copy.size());

  auto s21_it = s21_set_copy.begin();
  auto std_it = std_set_copy.begin();

  for (; s21_it != s21_set_copy.end(); ++s21_it, ++std_it) {
    EXPECT_TRUE(*s21_it == *std_it);
  }
}

TEST(set, Iterator) {
  s21::set<int> s21_set = {1, 2, 3, 4};
  auto s21_it = s21_set.begin();
  EXPECT_TRUE(*s21_it == 1);
  ++s21_it;
  EXPECT_TRUE(*s21_it == 2);
  ++s21_it;
  EXPECT_TRUE(*s21_it == 3);
  ++s21_it;
  EXPECT_TRUE(*s21_it == 4);
  ++s21_it;
  EXPECT_TRUE(s21_it == s21_set.end());
  --s21_it;
  EXPECT_TRUE(*s21_it == 4);
}

TEST(set, ConstIterator) {
  s21::set<int> s21_set = {1, 2, 3, 4};
  auto s21_it = s21_set.cbegin();
  EXPECT_TRUE(*s21_it == 1);
  ++s21_it;
  EXPECT_TRUE(*s21_it == 2);
  ++s21_it;
  EXPECT_TRUE(*s21_it == 3);
  ++s21_it;
  EXPECT_TRUE(*s21_it == 4);
  ++s21_it;
  EXPECT_TRUE(s21_it == s21_set.cend());
  --s21_it;
  EXPECT_TRUE(*s21_it == 4);
}

TEST(set, SizeFuncs) {
  s21::set<int> s21_set = {1, 2, 3, 4};
  std::set<int> std_set = {1, 2, 3, 4};
  EXPECT_EQ(s21_set.size(), std_set.size());
  s21_set.clear();
  std_set.clear();
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
  s21_set.insert(1);
  std_set.insert(1);
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(set, Insertion) {
  s21::set<int> s21_set = {3, 4};
  std::set<int> std_set = {3, 4};

  auto s21_res = s21_set.insert(1);
  auto std_res = std_set.insert(1);

  EXPECT_TRUE(*s21_res.first == *std_res.first);
  EXPECT_TRUE(s21_res.second == std_res.second);

  s21_res = s21_set.insert(4);
  std_res = std_set.insert(4);

  EXPECT_TRUE(*s21_res.first == *std_res.first);
  EXPECT_TRUE(s21_res.second == std_res.second);
}

TEST(set, Erase) {
  s21::set<int> s21_set = {1, 2, 3, 4};
  std::set<int> std_set = {1, 2, 3, 4};

  auto s21_it = s21_set.begin();
  auto std_it = std_set.begin();

  s21_set.erase(s21_it);
  std_set.erase(std_it);

  EXPECT_EQ(s21_set.size(), std_set.size());

  s21_it = s21_set.begin();
  std_it = std_set.begin();
  for (; s21_it != s21_set.end(); ++s21_it, ++std_it) {
    EXPECT_TRUE(*s21_it == *std_it);
  }
  EXPECT_EQ(s21_set.size(), std_set.size());
}

TEST(set, Swap) {
  s21::set<int> s21_set = {1, 2};
  s21::set<int> swap_set = {1, 2, 3, 4};

  s21_set.swap(swap_set);
  EXPECT_EQ(s21_set.size(), 4);
  EXPECT_EQ(swap_set.size(), 2);
  EXPECT_EQ(*s21_set.begin(), 1);
  EXPECT_EQ(*swap_set.begin(), 1);
}

TEST(set, Merge) {
  s21::set<int> s21_set = {1, 2};
  s21::set<int> merge_set = {6, 2, 3, 4};
  s21_set.merge(merge_set);

  std::set<int> std_set = {1, 2};
  std::set<int> std_merge_set = {6, 2, 3, 4};
  std_set.merge(std_merge_set);

  auto s21_it = s21_set.begin();
  auto std_it = std_set.begin();

  for (; s21_it != s21_set.end(); ++s21_it, ++std_it) {
    EXPECT_TRUE(*s21_it == *std_it);
  }
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(merge_set.size(), std_merge_set.size());
}

TEST(set, Find) {
  s21::set<int> s21_set = {1, 2, 3, 4};
  s21::set<int> s21_set_2 = {1, 2, 3, 4};

  auto s21_it = s21_set.find(2);
  auto s21_it_2 = s21_set_2.find(2);
  EXPECT_TRUE(*s21_it == *s21_it_2);
}

TEST(set, Contains) {
  s21::set<int> s21_set = {1, 2, 3, 4};
  EXPECT_TRUE(s21_set.contains(2));
  EXPECT_FALSE(s21_set.contains(5));
}

TEST(test, InsertMany) {
  s21::set<int> test_set;
  auto results = test_set.insert_many(1, 2, 3, 4, 5);

  EXPECT_EQ(results.size(), 5);

  for (const auto& result : results) {
    EXPECT_TRUE(result.second);
  }

  EXPECT_EQ(test_set.size(), 5);
  EXPECT_NE(test_set.find(1), test_set.end());
  EXPECT_NE(test_set.find(2), test_set.end());
  EXPECT_NE(test_set.find(3), test_set.end());
  EXPECT_NE(test_set.find(4), test_set.end());
  EXPECT_NE(test_set.find(5), test_set.end());
}