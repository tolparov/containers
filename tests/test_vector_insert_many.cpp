#include <vector>

#include "tests_init.h"
using namespace s21;

TEST(S21VectorInsertManyTest, Test) {
  vector<int> v;

  v.insert_many_back(1, 2, 3, 4, 5);

  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v.capacity(), 8);
  EXPECT_NE(v.data(), nullptr);

  for (int i = 1; i < 5; i++) {
    EXPECT_EQ(v[i - 1], i);
    i++;
  }

  v.insert_many_back(77);

  EXPECT_EQ(v.back(), 77);

  v.insert_many(v.cbegin(), 10, 10, 21, 89);

  EXPECT_EQ(v.size(), 10);
  EXPECT_EQ(v.capacity(), 16);
}
