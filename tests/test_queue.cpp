#include <queue>

#include "tests_init.h"

TEST(queue, DefaultConstructor) {
  s21::queue<int> q;
  EXPECT_TRUE(q.empty());
}


TEST(queue, InitializerListConstructor) {
  s21::queue<int> q({1, 2, 3});
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);
}


TEST(queue, CopyConstructor) {
  s21::queue<int> q1({1, 2, 3});
  s21::queue<int> q2(q1);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}


TEST(queue, MoveConstructor) {
  s21::queue<int> q1({1, 2, 3});
  s21::queue<int> q2(std::move(q1));
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}


TEST(queue, CopyAssignmentOperator) {
  s21::queue<int> q1({1, 2, 3});
  s21::queue<int> q2;
  q2 = q1;
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}


TEST(queue, MoveAssignmentOperator) {
  s21::queue<int> q1({1, 2, 3});
  s21::queue<int> q2;
  q2 = std::move(q1);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}


TEST(queue, FrontFunction) {
  s21::queue<int> q({1, 2, 3});
  EXPECT_EQ(q.front(), 1);
}


TEST(queue, BackFunction) {
  s21::queue<int> q({1, 2, 3});
  EXPECT_EQ(q.back(), 3);
}


TEST(queue, PushFunction) {
  s21::queue<int> q;
  q.push(1);
  EXPECT_EQ(q.back(), 1);
}


TEST(queue, PopFunction) {
  s21::queue<int> q({1, 2, 3});
  q.pop();
  EXPECT_EQ(q.front(), 2);
}


TEST(queue, SwapFunction) {
  s21::queue<int> q1({1, 2, 3});
  s21::queue<int> q2({4, 5});
  q1.swap(q2);
  EXPECT_EQ(q1.front(), 4);
  EXPECT_EQ(q2.front(), 1);
}


TEST(queue, EmptyFunction) {
  s21::queue<int> q;
  EXPECT_TRUE(q.empty());
}


TEST(queue, SizeFunction) {
  s21::queue<int> q({1, 2, 3});
  EXPECT_EQ(q.size(), 3);
}


TEST(queue, InsertManyBackFunction) {
  s21::queue<int> q;
  q.insert_many_back(1, 2, 3, 4);
  EXPECT_EQ(q.size(), 4);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 4);
}