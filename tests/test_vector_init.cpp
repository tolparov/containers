#include <vector>

#include "tests_init.h"

using namespace s21;

TEST(S21VectorInitializeTest, Initialize1) {
  vector<int> v;

  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
  EXPECT_EQ(v.data(), nullptr);
}

TEST(S21VectorInitializeTest, Initialize2) {
  vector<double> v;

  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
  EXPECT_EQ(v.data(), nullptr);
}

TEST(S21VectorInitializeTest, Initialize3) {
  vector<int> v(4);

  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v.capacity(), 4);
  EXPECT_NE(v.data(), nullptr);
}

TEST(S21VectorInitializeTest, Initialize4) {
  vector<char> v(25);

  EXPECT_EQ(v.size(), 25);
  EXPECT_EQ(v.capacity(), 25);
  EXPECT_NE(v.data(), nullptr);
}

TEST(S21VectorInitializeTest, Initialize5) {
  vector<int> v({1, 2, 3});

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.capacity(), 3);
  EXPECT_NE(v.data(), nullptr);

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_THROW(v[3], std::out_of_range);
}

TEST(S21VectorInitializeTest, Initialize6) {
  vector<char> v({'a', 'b', 'c', 'd', 'e', 'f'});

  EXPECT_EQ(v.size(), 6);
  EXPECT_EQ(v.capacity(), 6);
  EXPECT_NE(v.data(), nullptr);

  EXPECT_EQ(v[0], 'a');
  EXPECT_EQ(v[1], 'b');
  EXPECT_EQ(v[2], 'c');
  EXPECT_EQ(v[3], 'd');
  EXPECT_EQ(v[4], 'e');
  EXPECT_EQ(v[5], 'f');
}

TEST(S21VectorInitializeTest, Initialize7) {
  vector<int> v1({55});
  vector<int> v2(v1);

  EXPECT_EQ(v2.size(), 1);
  EXPECT_EQ(v2.capacity(), 1);
  EXPECT_NE(v2.data(), nullptr);

  EXPECT_EQ(v2[0], 55);
}

TEST(S21VectorInitializeTest, Initialize8) {
  vector<std::string> v1({"Hello", "World", "!"});
  vector<std::string> v2(v1);

  EXPECT_EQ(v2.size(), 3);
  EXPECT_EQ(v2.capacity(), 3);
  EXPECT_NE(v2.data(), nullptr);

  EXPECT_EQ(v2[0], "Hello");
  EXPECT_EQ(v2[1], "World");
  EXPECT_EQ(v2[2], "!");
}

TEST(S21VectorInitializeTest, Initialize9) {
  vector<long> v1({100, 200, 300, 400});
  vector<long> v2(std::move(v1));

  EXPECT_EQ(v2.size(), 4);
  EXPECT_EQ(v2.capacity(), 4);
  EXPECT_NE(v2.data(), nullptr);
  EXPECT_EQ(v1.data(), nullptr);

  EXPECT_EQ(v2[0], 100);
  EXPECT_EQ(v2[1], 200);
  EXPECT_EQ(v2[2], 300);
  EXPECT_EQ(v2[3], 400);
}

TEST(S21VectorInitializeTest, Initialize10) {
  vector<long> v1({100});
  vector<long> v2 = std::move(v1);

  EXPECT_EQ(v2.size(), 1);
  EXPECT_EQ(v2.capacity(), 1);
  EXPECT_NE(v2.data(), nullptr);
  EXPECT_EQ(v1.data(), nullptr);

  EXPECT_EQ(v2.at(0), 100);
}

TEST(S21VectorInitializeTest, Initialize11) {
  vector<int> v({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});

  EXPECT_EQ(v.size(), 12);
  EXPECT_EQ(v.capacity(), 12);
  EXPECT_NE(v.data(), nullptr);

  EXPECT_EQ(v.front(), 1);
  EXPECT_EQ(v.back(), 12);

  EXPECT_EQ(*v.cbegin(), 1);
  EXPECT_EQ(*(v.cend() - 1), 12);

  int i = 0;
  for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
    EXPECT_EQ(*it, v[i]);
    i++;
  }
}
