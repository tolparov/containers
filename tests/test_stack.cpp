#include <stack>

#include "tests_init.h"

using namespace s21;

TEST(S21StackTest, Initialize1) {
  stack<int> s1;
  stack<bool> s2;

  EXPECT_EQ(s1.size(), 0);
  EXPECT_EQ(s2.size(), 0);
}

TEST(S21StackTest, Initialize2) {
  stack<int> s1;

  s1.push(4);
  s1.push(5);
  s1.push(6);

  EXPECT_EQ(s1.empty(), false);

  stack<int> s2(s1);

  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.top(), 6);
}

TEST(S21StackTest, Initialize3) {
  stack<char> s1;
  s1.push('a');

  stack<char> s2(std::move(s1));

  EXPECT_EQ(s2.size(), 1);
  EXPECT_EQ(s2.top(), 'a');
  EXPECT_THROW(s1.top(), std::out_of_range);
}

TEST(S21StackTest, Initialize4) {
  stack<int> s1;

  for (int i = 0; i < 10; i++) s1.push(i);

  EXPECT_EQ(s1.size(), 10);

  stack<int> s2 = s1;

  EXPECT_EQ(s2.size(), 10);
  EXPECT_EQ(s2.top(), 9);

  s1.pop();
  s1.pop();

  s2 = std::move(s1);

  EXPECT_EQ(s2.size(), 8);
  EXPECT_EQ(s2.top(), 7);
  EXPECT_THROW(s1.top(), std::out_of_range);
}

TEST(S21StackTest, Initialize5) {
  stack<int> s({55, 40});

  EXPECT_EQ(s.size(), 2);
  EXPECT_EQ(s.top(), 40);
}

TEST(S21StackTest, Initialize6) {
  stack<int> s = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

  EXPECT_EQ(s.size(), 10);

  s.pop();
  s.pop();

  s.push(999);

  EXPECT_EQ(s.size(), 9);
  EXPECT_EQ(s.top(), 999);
}

TEST(S21StackTest, StorageTest) {
  stack<long> s;

  for (int i = 0; i < 100; i++) s.push(1000);

  EXPECT_EQ(s.size(), 100);
  EXPECT_EQ(s.top(), 1000);

  s.clear();

  EXPECT_EQ(s.size(), 0);

  for (int i = 0; i < 50; i++) s.push(7);

  EXPECT_EQ(s.size(), 50);
  EXPECT_EQ(s.top(), 7);

  for (int i = 0; i < 50; i++) s.pop();

  EXPECT_EQ(s.size(), 0);
  EXPECT_THROW(s.top(), std::out_of_range);
}

TEST(S21StackTest, SwapTest) {
  stack<char> s1;

  s1.push('a');
  s1.push('b');
  s1.push('c');
  s1.push('d');
  s1.push('e');
  s1.push('f');

  stack<char> s2;

  s2.push('a');
  s2.push('b');
  s2.push('c');

  s1.swap(s2);

  EXPECT_EQ(s1.size(), 3);
  EXPECT_EQ(s2.size(), 6);
  EXPECT_EQ(s1.top(), 'c');
  EXPECT_EQ(s2.top(), 'f');
}

TEST(S21StackTest, InsertMany1) {
  stack<std::string> s;

  s.insert_many_front("Hello", "World", "!");

  EXPECT_EQ(s.size(), 3);
  EXPECT_EQ(s.top(), "!");
}

TEST(S21StackTest, InsertMany2) {
  stack<short int> s({1, 2, 3, 4, 5, 6, 7, 8, 9});

  s.insert_many_front(9, 8, 7, 6, 5, 4, 3, 2, 1);

  s.pop();
  s.push(0);

  EXPECT_EQ(s.size(), 18);
  EXPECT_EQ(s.top(), 0);
}
