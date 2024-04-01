#include <array>

#include "tests_init.h"

TEST(array, Constuctor) {
  s21::array<int, 5> s21_array;

  EXPECT_EQ(s21_array.size(), 5);

  for (size_t i = 0; i < s21_array.size(); i++) {
    EXPECT_EQ(s21_array[i], 0);
  }
}

TEST(array, InitListConstructor) {
  s21::array<size_t, 5> s21_array = {1, 2, 3, 4, 5};

  EXPECT_EQ(s21_array.size(), 5);

  for (size_t i = 0; i < s21_array.size(); i++) {
    EXPECT_EQ(s21_array[i], i + 1);
  }
}

TEST(array, CopyConstructor) {
  s21::array<int, 5> s21_array = {1, 2, 3, 4, 5};
  s21::array<int, 5> s21_array_copy(s21_array);

  EXPECT_EQ(s21_array_copy.size(), s21_array.size());

  for (size_t i = 0; i < s21_array.size(); i++) {
    EXPECT_EQ(s21_array[i], s21_array_copy[i]);
  }
}

TEST(array, MoveConstructor) {
  s21::array<size_t, 5> s21_array = {1, 2, 3, 4, 5};
  s21::array<size_t, 5> s21_array_copy(std::move(s21_array));

  EXPECT_EQ(s21_array_copy.size(), 5);

  for (size_t i = 0; i < s21_array_copy.size(); i++) {
    EXPECT_EQ(s21_array_copy[i], i + 1);
  }
}

TEST(array, CopyAssignment) {
  s21::array<int, 5> s21_array = {1, 2, 3, 4, 5};
  s21::array<int, 5> s21_array_copy = s21_array;

  EXPECT_EQ(s21_array_copy.size(), s21_array.size());

  for (size_t i = 0; i < s21_array.size(); i++) {
    EXPECT_EQ(s21_array[i], s21_array_copy[i]);
  }
}

TEST(array, MoveAssignment) {
  s21::array<size_t, 5> s21_array = {1, 2, 3, 4, 5};
  s21::array<size_t, 5> s21_array_copy = std::move(s21_array);

  EXPECT_EQ(s21_array_copy.size(), 5);

  for (size_t i = 0; i < s21_array_copy.size(); i++) {
    EXPECT_EQ(s21_array_copy[i], i + 1);
  }
}

TEST(array, Iterator) {
  s21::array<int, 5> s21_array = {1, 2, 3, 4, 5};
  std::array<int, 5> std_array = {1, 2, 3, 4, 5};

  auto s21_it = s21_array.begin();
  auto std_it = std_array.begin();

  for (; s21_it != s21_array.end(); ++s21_it, ++std_it) {
    EXPECT_TRUE(*s21_it == *std_it);
  }
}

TEST(array, ConstIterator) {
  s21::array<int, 5> s21_array = {1, 2, 3, 4, 5};
  std::array<int, 5> std_array = {1, 2, 3, 4, 5};

  auto s21_it = s21_array.cbegin();
  auto std_it = std_array.cbegin();

  for (; s21_it != s21_array.cend(); ++s21_it, ++std_it) {
    EXPECT_TRUE(*s21_it == *std_it);
  }
}

TEST(array, AtValid) {
  s21::array<int, 5> s21_array = {1, 2, 3, 4, 5};

  EXPECT_EQ(s21_array.at(0), 1);
  EXPECT_EQ(s21_array.at(2), 3);
  EXPECT_EQ(s21_array.at(3), 4);
}

TEST(array, AtOutOfRange) {
  s21::array<int, 5> s21_array = {1, 2, 3, 4, 5};
  EXPECT_THROW(s21_array.at(5), std::out_of_range);
}

TEST(array, AtOperator) {
  s21::array<int, 5> s21_array = {1, 2, 3, 4, 5};

  EXPECT_EQ(s21_array[0], 1);
  s21_array[0] = 135;
  EXPECT_EQ(s21_array[0], 135);
}

TEST(array, FrontAndBack) {
  s21::array<int, 5> s21_array = {1, 2, 3, 4, 5};
  EXPECT_EQ(s21_array.front(), 1);
  EXPECT_EQ(s21_array.back(), 5);
}

TEST(array, Data) {
  s21::array<int, 5> s21_array = {1, 2, 3, 4, 5};
  int *data = s21_array.data();
  EXPECT_EQ(data[0], 1);
  EXPECT_EQ(data[1], 2);
  EXPECT_EQ(data[2], 3);
  EXPECT_EQ(data[3], 4);
  EXPECT_EQ(data[4], 5);
}

TEST(array, Size) {
  s21::array<int, 5> s21_array = {1, 2, 3, 4, 5};
  EXPECT_EQ(s21_array.size(), 5);
  EXPECT_FALSE(s21_array.empty());
  EXPECT_EQ(s21_array.max_size(), 5);
}

TEST(array, swap) {
  s21::array<size_t, 5> s21_array = {1, 2, 3, 4, 5};
  s21::array<size_t, 5> s21_array_copy = {6, 7, 8, 9, 10};

  s21_array.swap(s21_array_copy);

  for (size_t i = 0; i < s21_array.size(); i++) {
    EXPECT_EQ(s21_array[i], i + 6);
  }

  for (size_t i = 0; i < s21_array_copy.size(); i++) {
    EXPECT_EQ(s21_array_copy[i], i + 1);
  }
}

TEST(array, Fill) {
  s21::array<int, 5> s21_array;

  s21_array.fill(5);

  for (size_t i = 0; i < s21_array.size(); i++) {
    EXPECT_EQ(s21_array[i], 5);
  }

  s21_array.fill(10);

  for (size_t i = 0; i < s21_array.size(); i++) {
    EXPECT_EQ(s21_array[i], 10);
  }
}