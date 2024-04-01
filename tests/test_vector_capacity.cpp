#include <vector>

#include "tests_init.h"


using namespace s21;

TEST(S21VectorcapacityTest, Capacity1) {
  vector<int> v;

  EXPECT_EQ(v.empty(), true);
  EXPECT_EQ(v.data(), nullptr);

  v.push_back(2);
  v.push_back(9);

  EXPECT_EQ(v.empty(), false);
  EXPECT_NE(v.data(), nullptr);

  v.clear();

  EXPECT_EQ(v.empty(), true);
}

TEST(S21VectorcapacityTest, Capacity2) {
  vector<int> v1(2);

  EXPECT_NE(v1.data(), nullptr);
  EXPECT_EQ(v1.max_size(), std::numeric_limits<long>::max() / sizeof(int));

  vector<wchar_t> v2(4);
  EXPECT_NE(v2.data(), nullptr);
  EXPECT_EQ(v2.max_size(), std::numeric_limits<long>::max() / sizeof(wchar_t));
}

TEST(S21VectorcapacityTest, Capacity3) {
  vector<int> v({7, 2, 5});

  v.push_back(4);

  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v.capacity(), 6);
  EXPECT_NE(v.data(), nullptr);

  v.shrink_to_fit();

  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v.capacity(), 4);

  v.clear();
  v.shrink_to_fit();

  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
}

TEST(S21VectorcapacityTest, Capacity4) {
  vector<int> v({7, 2, 5});

  v.reserve(9);

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.capacity(), 9);
  EXPECT_NE(v.data(), nullptr);

  EXPECT_EQ(v[0], 7);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 5);
}
