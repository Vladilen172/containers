#include <gtest/gtest.h>

#include <queue>
#include <vector>

#include "../include/s21_queue.h"

TEST(queueTest, TestDefaultConstructor) {
  s21::queue<int> myQueue;
  std::queue<int> stdQueue;

  EXPECT_EQ(myQueue.empty(), stdQueue.empty());
  EXPECT_EQ(myQueue.size(), stdQueue.size());

  EXPECT_TRUE(myQueue.empty());

  EXPECT_EQ(myQueue.size(), 0);

  s21::queue<double> myDoubleQueue;
  std::queue<double> stdDoubleQueue;
  EXPECT_EQ(myDoubleQueue.empty(), stdDoubleQueue.empty());

  myQueue.push(1);
  myQueue.pop();
  EXPECT_TRUE(myQueue.empty());
}

TEST(queueTest, TestInitializerListConstructor) {
  std::queue<int> stdQueue;
  s21::queue<int> myQueue = {1, 2, 3, 4, 5};

  for (int i = 1; i < 6; i++) {
    stdQueue.push(i);
  }

  EXPECT_EQ(myQueue.empty(), stdQueue.empty());
  EXPECT_EQ(myQueue.size(), stdQueue.size());

  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(myQueue.front(), stdQueue.front());
    myQueue.pop();
    stdQueue.pop();
  }

  EXPECT_EQ(myQueue.empty(), stdQueue.empty());
  EXPECT_EQ(myQueue.size(), stdQueue.size());

  s21::queue<int> myEmptyQueue = {};
  std::queue<int> stdEmptyQueue;
  EXPECT_TRUE(myEmptyQueue.empty());
  EXPECT_EQ(myEmptyQueue.size(), stdEmptyQueue.size());

  s21::queue<int> mySingleQueue = {42};
  std::queue<int> stdSingleQueue;
  stdSingleQueue.push(42);
  EXPECT_EQ(mySingleQueue.front(), stdSingleQueue.front());
  EXPECT_EQ(mySingleQueue.size(), 1);

  s21::queue<int> myBigQueue = {1000000, 2000000, 3000000};
  EXPECT_EQ(myBigQueue.front(), 1000000);
  myBigQueue.pop();
  EXPECT_EQ(myBigQueue.front(), 2000000);

  s21::queue<int> myNegQueue = {-1, -2, -3};
  std::queue<int> stdNegQueue;
  stdNegQueue.push(-1);
  stdNegQueue.push(-2);
  stdNegQueue.push(-3);
  EXPECT_EQ(myNegQueue.front(), stdNegQueue.front());
}

TEST(queueTest, TestCopyConstructor) {
  std::queue<int> stdQueue;
  s21::queue<int> originalQueue = {1, 2, 3, 4, 5};
  s21::queue<int> copiedQueue(originalQueue);

  for (int i = 1; i < 6; i++) {
    stdQueue.push(i);
  }

  EXPECT_EQ(copiedQueue.empty(), stdQueue.empty());
  EXPECT_EQ(copiedQueue.size(), stdQueue.size());

  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(copiedQueue.front(), stdQueue.front());
    copiedQueue.pop();
    stdQueue.pop();
  }

  EXPECT_EQ(copiedQueue.empty(), stdQueue.empty());
  EXPECT_EQ(copiedQueue.size(), stdQueue.size());
}

TEST(queueTest, TestMoveConstructor) {
  std::queue<int> stdQueue;
  s21::queue<int> originalQueue = {1, 2, 3, 4, 5};
  s21::queue<int> movedQueue(std::move(originalQueue));

  for (int i = 1; i < 6; i++) {
    stdQueue.push(i);
  }

  EXPECT_EQ(movedQueue.empty(), stdQueue.empty());
  EXPECT_EQ(movedQueue.size(), stdQueue.size());

  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(movedQueue.front(), stdQueue.front());
    movedQueue.pop();
    stdQueue.pop();
  }

  EXPECT_EQ(movedQueue.empty(), stdQueue.empty());
  EXPECT_EQ(movedQueue.size(), stdQueue.size());

  EXPECT_TRUE(originalQueue.empty());
}

TEST(queueTest, TestMoveAssignment) {
  s21::queue<int> originalQueue = {1, 2, 3, 4, 5};
  s21::queue<int> targetQueue;

  targetQueue = std::move(originalQueue);

  EXPECT_EQ(targetQueue.size(), 5);
  EXPECT_FALSE(targetQueue.empty());

  int expectedValues[] = {1, 2, 3, 4, 5};
  for (int value : expectedValues) {
    EXPECT_EQ(targetQueue.front(), value);
    targetQueue.pop();
  }

  EXPECT_TRUE(originalQueue.empty());
}

TEST(queueTest, TestMoveAssignmentSelf) {
  s21::queue<int> queue = {1, 2, 3, 4, 5};
  std::queue<int> stdQueue;

  for (int i = 1; i < 6; i++) {
    stdQueue.push(i);
  }

  EXPECT_EQ(queue.size(), stdQueue.size());

  queue = queue;
  stdQueue = stdQueue;

  EXPECT_EQ(queue.size(), stdQueue.size());

  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(queue.front(), stdQueue.front());
    queue.pop();
    stdQueue.pop();
  }
}

TEST(queueTest, TestFront) {
  std::queue<int> stdQueue;
  s21::queue<int> myQueue = {1, 2, 3, 4, 5};

  for (int i = 1; i < 6; i++) {
    stdQueue.push(i);
  }

  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(myQueue.front(), stdQueue.front());
    myQueue.pop();
    stdQueue.pop();
  }

  s21::queue<int> mySingleQueue;
  mySingleQueue.push(42);
  EXPECT_EQ(mySingleQueue.front(), 42);

  s21::queue<int> myPushQueue;
  myPushQueue.push(1);
  myPushQueue.push(2);
  EXPECT_EQ(myPushQueue.front(), 1);

  s21::queue<int> myNegQueue;
  myNegQueue.push(-5);
  EXPECT_EQ(myNegQueue.front(), -5);

  s21::queue<long long> myBigQueue;
  myBigQueue.push(1000000000LL);
  EXPECT_EQ(myBigQueue.front(), 1000000000LL);
}

TEST(queueTest, TestBack) {
  std::queue<int> stdQueue;
  s21::queue<int> myQueue = {1, 2, 3, 4, 5};

  for (int i = 1; i < 6; i++) {
    stdQueue.push(i);
  }
  EXPECT_EQ(stdQueue.back(), myQueue.back());

  stdQueue.push(69);
  myQueue.push(69);
  EXPECT_EQ(stdQueue.back(), myQueue.back());

  EXPECT_EQ(myQueue.empty(), stdQueue.empty());
  EXPECT_EQ(myQueue.size(), stdQueue.size());

  s21::queue<int> mySingleQueue;
  mySingleQueue.push(42);
  EXPECT_EQ(mySingleQueue.back(), 42);

  s21::queue<int> myPushQueue;
  myPushQueue.push(1);
  myPushQueue.push(2);
  EXPECT_EQ(myPushQueue.back(), 2);

  s21::queue<int> myNegQueue;
  myNegQueue.push(-5);
  myNegQueue.push(-10);
  EXPECT_EQ(myNegQueue.back(), -10);

  s21::queue<long long> myBigQueue;
  myBigQueue.push(1000000000LL);
  myBigQueue.push(2000000000LL);
  EXPECT_EQ(myBigQueue.back(), 2000000000LL);
}

TEST(s21queueTest, TestPush) {
  std::queue<int> stdQueue;
  s21::queue<int> myQueue;

  for (int i = 1; i < 6; i++) {
    stdQueue.push(i);
    myQueue.push(i);
  }

  EXPECT_EQ(stdQueue.front(), myQueue.front());
  EXPECT_EQ(stdQueue.back(), myQueue.back());
  EXPECT_EQ(myQueue.empty(), stdQueue.empty());
  EXPECT_EQ(myQueue.size(), stdQueue.size());

  s21::queue<int> myEmptyQueue;
  myEmptyQueue.push(1);
  EXPECT_EQ(myEmptyQueue.front(), 1);
  EXPECT_EQ(myEmptyQueue.size(), 1);

  s21::queue<int> myMultiQueue;
  myMultiQueue.push(1);
  myMultiQueue.push(2);
  myMultiQueue.push(3);
  EXPECT_EQ(myMultiQueue.back(), 3);
  EXPECT_EQ(myMultiQueue.size(), 3);

  s21::queue<int> myNegQueue;
  myNegQueue.push(-1);
  myNegQueue.push(-2);
  EXPECT_EQ(myNegQueue.front(), -1);
  EXPECT_EQ(myNegQueue.back(), -2);

  s21::queue<long long> myBigQueue;
  myBigQueue.push(1000000000LL);
  myBigQueue.push(2000000000LL);
  EXPECT_EQ(myBigQueue.front(), 1000000000LL);
  EXPECT_EQ(myBigQueue.back(), 2000000000LL);
}

TEST(queueTest, TestPop) {
  std::queue<int> stdQueue;
  s21::queue<int> myQueue;

  for (int i = 1; i < 45; i++) {
    stdQueue.push(i);
    myQueue.push(i);
  }

  for (int i = 1; i < 45; i++) {
    EXPECT_EQ(stdQueue.front(), myQueue.front());
    stdQueue.pop();
    myQueue.pop();
  }

  EXPECT_EQ(myQueue.empty(), stdQueue.empty());
  EXPECT_EQ(myQueue.size(), stdQueue.size());
}

TEST(queueTest, TestSwap) {
  std::queue<int> stdQueue1;
  std::queue<int> stdQueue2;
  s21::queue<int> myQueue1;
  s21::queue<int> myQueue2;

  for (int i = 1; i < 6; i++) {
    stdQueue1.push(i);
    myQueue1.push(i);
  }

  for (int i = 6; i < 11; i++) {
    stdQueue2.push(i);
    myQueue2.push(i);
  }

  stdQueue1.swap(stdQueue2);
  myQueue1.swap(myQueue2);

  EXPECT_EQ(stdQueue1.front(), myQueue1.front());
  EXPECT_EQ(stdQueue1.back(), myQueue1.back());
  EXPECT_EQ(myQueue1.empty(), stdQueue1.empty());
  EXPECT_EQ(myQueue1.size(), stdQueue1.size());

  EXPECT_EQ(stdQueue2.front(), myQueue2.front());
  EXPECT_EQ(stdQueue2.back(), myQueue2.back());
  EXPECT_EQ(myQueue2.empty(), stdQueue2.empty());
  EXPECT_EQ(myQueue2.size(), stdQueue2.size());
}
TEST(queueTest, AssignmentOperator) {
  s21::queue<int> q1({1, 2, 3, 4, 5});
  s21::queue<int> q2 = q1;
  EXPECT_EQ(q2.size(), 5);
  EXPECT_EQ(q2.front(), 1);
  q2.pop();
  EXPECT_EQ(q2.front(), 2);
  q2.pop();
  EXPECT_EQ(q2.front(), 3);
}
TEST(queueTest, SelfAssignment) {
  s21::queue<int> q1({1, 2, 3, 4, 5});
  q1 = q1;
  EXPECT_EQ(q1.size(), 5);
  EXPECT_EQ(q1.front(), 1);
  q1.pop();
  EXPECT_EQ(q1.front(), 2);
  q1.pop();
  EXPECT_EQ(q1.front(), 3);
}
TEST(queueTest, ClearOldState) {
  s21::queue<int> q1;
  s21::queue<int> q3;
  q3.push(10);
  q3.push(20);
  q1 = q3;
  EXPECT_EQ(q1.size(), 2);
  EXPECT_EQ(q1.front(), 10);
  q1.pop();
  EXPECT_EQ(q1.front(), 20);
}
TEST(queueTest, MoveState) {
  s21::queue<int> q1;
  s21::queue<int> q3;
  q3.push(10);
  q3.push(20);
  q1 = std::move(q3);
  EXPECT_EQ(q1.size(), 2);
  EXPECT_EQ(q1.front(), 10);
  q1.pop();
  EXPECT_EQ(q1.front(), 20);
  EXPECT_EQ(q3.size(), 0);
}
TEST(queueTest, Exceptions) {
  s21::queue<int> q1({1, 2, 3});
  s21::queue<int> q2;
  EXPECT_THROW(q2.front(), std::out_of_range);
  EXPECT_THROW(q2.back(), std::out_of_range);
  q2 = q1;
  q2 = std::move(q1);
  EXPECT_THROW(q1.pop(), std::out_of_range);
}