#include <gtest/gtest.h>

#include <stack>

#include "../include/s21_stack.h"

TEST(stackTest, TestDefaultConstructor1) {
  std::stack<int> stdStack;
  s21::stack<int> myStack;

  EXPECT_EQ(stdStack.size(), myStack.size());
  EXPECT_EQ(stdStack.empty(), myStack.empty());

  stdStack.push(12);
  myStack.push(12);

  EXPECT_EQ(stdStack.size(), myStack.size());
  EXPECT_EQ(stdStack.empty(), myStack.empty());
  EXPECT_EQ(stdStack.top(), myStack.top());

  stdStack.pop();
  myStack.pop();
  EXPECT_EQ(stdStack.size(), myStack.size());
}

TEST(stackTest, TestDefaultConstructor2) {
  s21::stack<int> myStack;
  EXPECT_TRUE(myStack.empty());
  EXPECT_EQ(myStack.size(), 0);
}

TEST(stackTest, TestDefaultConstructor3) {
  s21::stack<int> myStack;
  myStack.push(10);
  EXPECT_EQ(myStack.top(), 10);
  EXPECT_EQ(myStack.size(), 1);
}

TEST(stackTest, TestDefaultConstructor4) {
  s21::stack<int> myStack;
  myStack.push(20);
  myStack.push(30);
  EXPECT_EQ(myStack.top(), 30);
  EXPECT_EQ(myStack.size(), 2);
}

TEST(stackTest, TestDefaultConstructor5) {
  s21::stack<int> myStack;
  myStack.push(40);
  myStack.push(50);
  myStack.pop();
  EXPECT_EQ(myStack.top(), 40);
  EXPECT_EQ(myStack.size(), 1);
}

TEST(stackTest, TestDefaultConstructor6) {
  std::stack<int> stdStack;
  s21::stack<int> myStack;

  EXPECT_EQ(stdStack.size(), myStack.size());
  EXPECT_EQ(stdStack.empty(), myStack.empty());

  stdStack.push(12);
  myStack.push(12);

  EXPECT_EQ(stdStack.size(), myStack.size());
  EXPECT_EQ(stdStack.empty(), myStack.empty());
  EXPECT_EQ(stdStack.top(), myStack.top());

  stdStack.pop();
  myStack.pop();
  EXPECT_EQ(stdStack.size(), myStack.size());
}

TEST(stackTest, TestInitializerListConstructor2) {
  s21::stack<int> myStack = {10, 20, 30};
  EXPECT_EQ(myStack.size(), 3);
  EXPECT_EQ(myStack.top(), 30);
}

TEST(stackTest, TestInitializerListConstructor3) {
  s21::stack<int> myStack = {40, 50, 60, 70};
  EXPECT_EQ(myStack.size(), 4);
  EXPECT_EQ(myStack.top(), 70);
}

TEST(stackTest, TestInitializerListConstructor4) {
  s21::stack<int> myStack = {80, 90};
  EXPECT_EQ(myStack.size(), 2);
  EXPECT_EQ(myStack.top(), 90);
}

TEST(stackTest, TestInitializerListConstructor5) {
  s21::stack<int> myStack = {100};
  EXPECT_EQ(myStack.size(), 1);
  EXPECT_EQ(myStack.top(), 100);
}

TEST(stackTest, TestInitializerListConstructor6) {
  std::stack<int> stdStack;
  s21::stack<int> myStack = {1, 2, 3, 4, 5};

  for (int i = 1; i < 6; i++) {
    stdStack.push(i);
  }

  EXPECT_EQ(stdStack.size(), myStack.size());
  EXPECT_EQ(stdStack.empty(), myStack.empty());

  for (size_t i = 0; i < stdStack.size(); ++i) {
    EXPECT_EQ(stdStack.top(), myStack.top());
    stdStack.pop();
    myStack.pop();
  }

  EXPECT_EQ(stdStack.size(), myStack.size());
}

TEST(stackTest, TestInitializerListConstructor1) {
  std::vector<int> vec = {1, 2, 3, 4, 5};
  std::stack<int> stdStack(std::deque<int>(vec.begin(), vec.end()));
  s21::stack<int> myStack = {1, 2, 3, 4, 5};

  EXPECT_EQ(stdStack.size(), myStack.size());
  EXPECT_EQ(stdStack.empty(), myStack.empty());

  for (size_t i = 0; i < stdStack.size(); ++i) {
    EXPECT_EQ(stdStack.top(), myStack.top());
    stdStack.pop();
    myStack.pop();
  }

  EXPECT_EQ(stdStack.size(), myStack.size());
}

TEST(stackTest, TestCopyConstructor1) {
  s21::stack<int> originalStack = {1, 2, 3, 4, 5};
  s21::stack<int> copiedStack(originalStack);

  EXPECT_EQ(originalStack.size(), copiedStack.size());
  EXPECT_EQ(originalStack.empty(), copiedStack.empty());

  for (size_t i = 0; i < originalStack.size(); ++i) {
    EXPECT_EQ(originalStack.top(), copiedStack.top());
    originalStack.pop();
    copiedStack.pop();
  }

  EXPECT_EQ(originalStack.size(), copiedStack.size());
}

TEST(stackTest, TestCopyConstructor2) {
  s21::stack<int> originalStack = {10, 20, 30};
  s21::stack<int> copiedStack(originalStack);
  EXPECT_EQ(copiedStack.size(), 3);
  EXPECT_EQ(copiedStack.top(), 30);
}

TEST(stackTest, TestCopyConstructor3) {
  s21::stack<int> originalStack = {40, 50, 60, 70};
  s21::stack<int> copiedStack(originalStack);
  EXPECT_EQ(copiedStack.size(), 4);
  EXPECT_EQ(copiedStack.top(), 70);
}

TEST(stackTest, TestCopyConstructor4) {
  s21::stack<int> originalStack = {80, 90};
  s21::stack<int> copiedStack(originalStack);
  EXPECT_EQ(copiedStack.size(), 2);
  EXPECT_EQ(copiedStack.top(), 90);
}

TEST(stackTest, TestCopyConstructor5) {
  s21::stack<int> originalStack = {100};
  s21::stack<int> copiedStack(originalStack);
  EXPECT_EQ(copiedStack.size(), 1);
  EXPECT_EQ(copiedStack.top(), 100);
}

TEST(stackTest, TestCopyConstructor6) {
  s21::stack<int> originalStack = {1, 2, 3, 4, 5};
  s21::stack<int> copiedStack(originalStack);

  EXPECT_EQ(originalStack.size(), copiedStack.size());
  EXPECT_EQ(originalStack.empty(), copiedStack.empty());

  for (size_t i = 0; i < originalStack.size(); ++i) {
    EXPECT_EQ(originalStack.top(), copiedStack.top());
    originalStack.pop();
    copiedStack.pop();
  }

  EXPECT_EQ(originalStack.size(), copiedStack.size());
}

TEST(stackTest, TestMoveConstructor1) {
  s21::stack<int> originalStack = {1, 2, 3, 4, 5};
  s21::stack<int> movedStack(std::move(originalStack));

  EXPECT_EQ(movedStack.size(), 5);
  EXPECT_EQ(originalStack.size(), 0);

  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(movedStack.top(), 5 - i);
    movedStack.pop();
  }

  EXPECT_EQ(movedStack.size(), 0);
}

TEST(stackTest, TestMoveAssignment89) {
  s21::stack<int> originalStack = {1, 2, 3, 4, 5};
  s21::stack<int> movedStack;
  movedStack = std::move(originalStack);

  EXPECT_EQ(movedStack.size(), 5);
  EXPECT_EQ(originalStack.size(), 0);

  size_t size = movedStack.size();

  for (size_t i = 0; i < size; ++i) {
    EXPECT_EQ(movedStack.top(), 5 - i);
    movedStack.pop();
  }

  EXPECT_EQ(movedStack.size(), 0);
}

TEST(stackTest, TestMoveConstructor) {
  s21::stack<int> originalStack = {1, 2, 3, 4, 5};
  s21::stack<int> movedStack(std::move(originalStack));

  EXPECT_EQ(movedStack.size(), 5);
  EXPECT_EQ(originalStack.size(), 0);

  size_t size = movedStack.size();

  for (size_t i = 0; i < size; ++i) {
    EXPECT_EQ(movedStack.top(), 5 - i);
    movedStack.pop();
  }

  EXPECT_EQ(movedStack.size(), 0);
}

TEST(stackTest, TestMoveConstructor2) {
  s21::stack<int> originalStack = {10, 20, 30};
  s21::stack<int> movedStack(std::move(originalStack));
  EXPECT_EQ(movedStack.size(), 3);
  EXPECT_EQ(movedStack.top(), 30);
}

TEST(stackTest, TestMoveConstructor3) {
  s21::stack<int> originalStack = {40, 50, 60, 70};
  s21::stack<int> movedStack(std::move(originalStack));
  EXPECT_EQ(movedStack.size(), 4);
  EXPECT_EQ(movedStack.top(), 70);
}

TEST(stackTest, TestMoveConstructor4) {
  s21::stack<int> originalStack = {80, 90};
  s21::stack<int> movedStack(std::move(originalStack));
  EXPECT_EQ(movedStack.size(), 2);
  EXPECT_EQ(movedStack.top(), 90);
}

TEST(stackTest, TestMoveConstructor5) {
  s21::stack<int> originalStack = {100};
  s21::stack<int> movedStack(std::move(originalStack));
  EXPECT_EQ(movedStack.size(), 1);
  EXPECT_EQ(movedStack.top(), 100);
}

TEST(stackTest, TestMoveAssignment123) {
  s21::stack<int> originalStack = {1, 2, 3, 4, 5};
  s21::stack<int> movedStack;
  movedStack = std::move(originalStack);

  EXPECT_EQ(movedStack.size(), 5);
  EXPECT_EQ(originalStack.size(), 0);

  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(movedStack.top(), 5 - i);
    movedStack.pop();
  }

  EXPECT_EQ(movedStack.size(), 0);
}

TEST(stackTest, TestMoveAssignment2) {
  s21::stack<int> originalStack = {10, 20, 30};
  s21::stack<int> movedStack;
  movedStack = std::move(originalStack);
  EXPECT_EQ(movedStack.size(), 3);
  EXPECT_EQ(movedStack.top(), 30);
}

TEST(stackTest, TestMoveAssignment3) {
  s21::stack<int> originalStack = {40, 50, 60, 70};
  s21::stack<int> movedStack;
  movedStack = std::move(originalStack);
  EXPECT_EQ(movedStack.size(), 4);
  EXPECT_EQ(movedStack.top(), 70);
}

TEST(stackTest, TestMoveAssignment4) {
  s21::stack<int> originalStack = {80, 90};
  s21::stack<int> movedStack;
  movedStack = std::move(originalStack);
  EXPECT_EQ(movedStack.size(), 2);
  EXPECT_EQ(movedStack.top(), 90);
}

TEST(stackTest, TestMoveAssignment5) {
  s21::stack<int> originalStack = {100};
  s21::stack<int> movedStack;
  movedStack = std::move(originalStack);
  EXPECT_EQ(movedStack.size(), 1);
  EXPECT_EQ(movedStack.top(), 100);
}

TEST(stackTest, TestPushAndPop) {
  s21::stack<int> myStack;

  myStack.push(10);
  EXPECT_EQ(myStack.size(), 1);
  EXPECT_EQ(myStack.top(), 10);

  myStack.push(20);
  EXPECT_EQ(myStack.size(), 2);
  EXPECT_EQ(myStack.top(), 20);

  myStack.pop();
  EXPECT_EQ(myStack.size(), 1);
  EXPECT_EQ(myStack.top(), 10);

  myStack.pop();
  EXPECT_EQ(myStack.size(), 0);
  EXPECT_TRUE(myStack.empty());
}

TEST(stackTest, TestSwap) {
  s21::stack<int> stack1 = {1, 2, 3};
  s21::stack<int> stack2 = {4, 5, 6};

  stack1.swap(stack2);

  EXPECT_EQ(stack1.size(), 3);
  EXPECT_EQ(stack2.size(), 3);

  EXPECT_EQ(stack1.top(), 6);
  EXPECT_EQ(stack2.top(), 3);

  stack1.pop();
  stack2.pop();

  EXPECT_EQ(stack1.top(), 5);
  EXPECT_EQ(stack2.top(), 2);
}

TEST(stackTest, TestTop1) {
  s21::stack<int> myStack;
  myStack.push(10);
  EXPECT_EQ(myStack.top(), 10);
}

TEST(stackTest, TestTop2) {
  s21::stack<int> myStack;
  myStack.push(20);
  myStack.push(30);
  EXPECT_EQ(myStack.top(), 30);
}

TEST(stackTest, TestTop3) {
  s21::stack<int> myStack;
  myStack.push(40);
  myStack.push(50);
  myStack.pop();
  EXPECT_EQ(myStack.top(), 40);
}

TEST(stackTest, TestTop4) {
  s21::stack<int> myStack = {60, 70, 80};
  EXPECT_EQ(myStack.top(), 80);
}

TEST(stackTest, TestTop5) {
  s21::stack<int> myStack = {90};
  EXPECT_EQ(myStack.top(), 90);
}

TEST(stackTest, TestPush1) {
  s21::stack<int> myStack;
  myStack.push(10);
  EXPECT_EQ(myStack.size(), 1);
  EXPECT_EQ(myStack.top(), 10);
}

TEST(stackTest, TestPush2) {
  s21::stack<int> myStack;
  myStack.push(20);
  myStack.push(30);
  EXPECT_EQ(myStack.size(), 2);
  EXPECT_EQ(myStack.top(), 30);
}

TEST(stackTest, TestPush3) {
  s21::stack<int> myStack;
  myStack.push(40);
  myStack.push(50);
  myStack.push(60);
  EXPECT_EQ(myStack.size(), 3);
  EXPECT_EQ(myStack.top(), 60);
}

TEST(stackTest, TestPush4) {
  s21::stack<int> myStack = {70, 80};
  myStack.push(90);
  EXPECT_EQ(myStack.size(), 3);
  EXPECT_EQ(myStack.top(), 90);
}

TEST(stackTest, TestPush5) {
  s21::stack<int> myStack = {100};
  myStack.push(110);
  EXPECT_EQ(myStack.size(), 2);
  EXPECT_EQ(myStack.top(), 110);
}

TEST(stackTest, TestPop1) {
  s21::stack<int> myStack;
  myStack.push(10);
  myStack.pop();
  EXPECT_EQ(myStack.size(), 0);
  EXPECT_TRUE(myStack.empty());
}

TEST(stackTest, TestPop2) {
  s21::stack<int> myStack;
  myStack.push(20);
  myStack.push(30);
  myStack.pop();
  EXPECT_EQ(myStack.size(), 1);
  EXPECT_EQ(myStack.top(), 20);
}

TEST(stackTest, TestPop3) {
  s21::stack<int> myStack;
  myStack.push(40);
  myStack.push(50);
  myStack.push(60);
  myStack.pop();
  EXPECT_EQ(myStack.size(), 2);
  EXPECT_EQ(myStack.top(), 50);
}

TEST(stackTest, TestPop4) {
  s21::stack<int> myStack = {70, 80};
  myStack.pop();
  EXPECT_EQ(myStack.size(), 1);
  EXPECT_EQ(myStack.top(), 70);
}

TEST(stackTest, TestPop5) {
  s21::stack<int> myStack = {90};
  myStack.pop();
  EXPECT_EQ(myStack.size(), 0);
  EXPECT_TRUE(myStack.empty());
}

TEST(stackTest, TestSwap1) {
  s21::stack<int> stack1 = {1, 2, 3};
  s21::stack<int> stack2 = {4, 5, 6};

  stack1.swap(stack2);

  EXPECT_EQ(stack1.size(), 3);
  EXPECT_EQ(stack2.size(), 3);

  EXPECT_EQ(stack1.top(), 6);
  EXPECT_EQ(stack2.top(), 3);

  stack1.pop();
  stack2.pop();

  EXPECT_EQ(stack1.top(), 5);
  EXPECT_EQ(stack2.top(), 2);
}

TEST(stackTest, TestSwap2) {
  s21::stack<int> stack1 = {10, 20, 30};
  s21::stack<int> stack2 = {40, 50, 60};

  stack1.swap(stack2);

  EXPECT_EQ(stack1.size(), 3);
  EXPECT_EQ(stack2.size(), 3);

  EXPECT_EQ(stack1.top(), 60);
  EXPECT_EQ(stack2.top(), 30);

  stack1.pop();
  stack2.pop();

  EXPECT_EQ(stack1.top(), 50);
  EXPECT_EQ(stack2.top(), 20);
}

TEST(stackTest, TestSwap3) {
  s21::stack<int> stack1 = {70, 80};
  s21::stack<int> stack2 = {90, 100};

  stack1.swap(stack2);

  EXPECT_EQ(stack1.size(), 2);
  EXPECT_EQ(stack2.size(), 2);

  EXPECT_EQ(stack1.top(), 100);
  EXPECT_EQ(stack2.top(), 80);

  stack1.pop();
  stack2.pop();

  EXPECT_EQ(stack1.top(), 90);
  EXPECT_EQ(stack2.top(), 70);
}

TEST(stackTest, TestSwap4) {
  s21::stack<int> stack1 = {110};
  s21::stack<int> stack2 = {120};

  stack1.swap(stack2);

  EXPECT_EQ(stack1.size(), 1);
  EXPECT_EQ(stack2.size(), 1);

  EXPECT_EQ(stack1.top(), 120);
  EXPECT_EQ(stack2.top(), 110);
}

TEST(stackTest, TestSwap5) {
  s21::stack<int> stack1 = {130, 140, 150};
  s21::stack<int> stack2 = {160, 170};

  stack1.swap(stack2);

  EXPECT_EQ(stack1.size(), 2);
  EXPECT_EQ(stack2.size(), 3);

  EXPECT_EQ(stack1.top(), 170);
  EXPECT_EQ(stack2.top(), 150);

  stack1.pop();
  stack2.pop();

  EXPECT_EQ(stack1.top(), 160);
  EXPECT_EQ(stack2.top(), 140);
}

TEST(stackTest, PopOnEmptyStack) {
  s21::stack<int> stack;
  EXPECT_THROW(stack.pop(), std::out_of_range);
}

TEST(stackTest, TopOnEmptyStack) {
  s21::stack<int> stack;
  EXPECT_THROW(stack.top(), std::out_of_range);
}