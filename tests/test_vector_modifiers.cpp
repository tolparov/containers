#include <vector>

#include "tests_init.h"

using namespace s21;

TEST(S21VectorModifyTest, Modify1) {
  vector<int> v{1, 2, 3, 4};
  v.pop_back();
  v.push_back(9);

  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v.capacity(), 4);
  EXPECT_NE(v.data(), nullptr);
  EXPECT_EQ(v[3], 9);
}

TEST(S21VectorModifyTest, Modify2) {
  vector<double> v;

  v.push_back(2.1);
  v.push_back(8.7);
  v.push_back(4.0);

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.capacity(), 4);
  EXPECT_NE(v.data(), nullptr);

  EXPECT_EQ(v[0], 2.1);
  EXPECT_EQ(v[1], 8.7);
  EXPECT_EQ(v[2], 4.0);
}

TEST(S21VectorModifyTest, Modify3) {
  vector<int> v({1, 2});

  vector<int>::iterator it = v.end();

  it = v.insert(it, 33);
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.capacity(), 4);
  EXPECT_NE(v.data(), nullptr);

  EXPECT_EQ(*it, 33);
  EXPECT_EQ(v[2], 33);
}

TEST(S21VectorModifyTest, Modify4) {
  vector<char> v({'a', 'a', 'a', 'a', 'a'});

  vector<char>::iterator it = v.begin();

  it = it + 2;
  it = v.insert(it, 'h');
  EXPECT_EQ(v.size(), 6);
  EXPECT_EQ(v.capacity(), 10);
  EXPECT_NE(v.data(), nullptr);

  EXPECT_EQ(*it, 'h');
  EXPECT_EQ(v[2], 'h');
}

TEST(S21VectorModifyTest, Modify5) {
  vector<int> v({1, 1, 1, 1});

  vector<int>::iterator it = v.begin();

  v.erase(it);
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.capacity(), 4);
  EXPECT_NE(v.data(), nullptr);
}

TEST(S21VectorModifyTest, Modify6) {
  vector<int> v({1, 2, 3});

  vector<int>::iterator it = v.end();

  it--;

  v.erase(it);
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v.capacity(), 3);
  EXPECT_NE(v.data(), nullptr);

  v.clear();
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 3);
  EXPECT_NE(v.data(), nullptr);
}

TEST(S21VectorModifyTest, Modify7) {
  vector<int> v1({1});
  vector<int> v2({10, 10, 10});

  v1.swap(v2);

  EXPECT_EQ(v1.size(), 3);
  EXPECT_EQ(v1.capacity(), 3);
  EXPECT_NE(v1.data(), nullptr);

  EXPECT_EQ(v2.size(), 1);
  EXPECT_EQ(v2.capacity(), 1);
  EXPECT_NE(v2.data(), nullptr);

  EXPECT_EQ(v2[0], 1);

  v2.insert(v2.begin(), 19);

  EXPECT_EQ(v2.front(), 19);
  EXPECT_EQ(v2.back(), 1);
}
