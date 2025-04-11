#include <gtest/gtest.h>

#include <list>

#include "../include/s21_list.h"

TEST(S21ListTest, ConstructorDefault) {
  s21::list<int> myList;
  std::list<int> stdList;

  EXPECT_EQ(myList.size(), stdList.size());
  EXPECT_EQ(myList.empty(), stdList.empty());
}

TEST(S21ListTest, ConstructorWithSize) {
  s21::list<int> myList(5);
  std::list<int> stdList(5);
  s21::list<std::string> myListStrings(5);
  std::list<std::string> stdListString(5);
  s21::list<char> myListChar(5);
  std::list<char> stdListChar(5);

  EXPECT_FALSE(myList.empty());
  EXPECT_EQ(myList.size(), 5);

  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(myList.front(), stdList.front());
    myList.pop_front();
    stdList.pop_front();
  }

  EXPECT_TRUE(myList.empty());
  EXPECT_TRUE(stdList.empty());

  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(myListStrings.front(), stdListString.front());
    myListStrings.pop_front();
    stdListString.pop_front();
  }

  EXPECT_TRUE(myListStrings.empty());
  EXPECT_TRUE(stdListString.empty());

  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(myListChar.front(), stdListChar.front());
    myListChar.pop_front();
    stdListChar.pop_front();
  }

  EXPECT_TRUE(myListChar.empty());
  EXPECT_TRUE(stdListChar.empty());

  EXPECT_EQ(myList.size(), stdList.size());
  EXPECT_EQ(myListStrings.size(), stdListString.size());
  EXPECT_EQ(myListChar.size(), stdListChar.size());
}

TEST(S21ListTest, ConstructorWithSizeAndValue) {
  s21::list<int> myListInt(15, 69);
  std::list<int> stdListInt(15, 69);
  s21::list<double> myListDouble(5, 69.0);
  std::list<double> stdListDouble(5, 69.0);
  s21::list<std::string> myListStrings(5, "Hello");
  std::list<std::string> stdListString(5, "Hello");

  EXPECT_FALSE(myListInt.empty());
  EXPECT_EQ(myListInt.size(), 15);

  for (size_t i = 0; i < 15; ++i) {
    EXPECT_EQ(myListInt.front(), stdListInt.front());
    myListInt.pop_front();
    stdListInt.pop_front();
  }

  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(myListDouble.front(), stdListDouble.front());
    myListDouble.pop_front();
    stdListDouble.pop_front();
  }

  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(myListStrings.front(), stdListString.front());
    myListStrings.pop_front();
    stdListString.pop_front();
  }

  EXPECT_EQ(myListInt.size(), 0);
  EXPECT_EQ(myListDouble.size(), 0);
  EXPECT_EQ(myListStrings.size(), 0);
  EXPECT_EQ(myListInt.size(), stdListInt.size());
  EXPECT_EQ(myListDouble.size(), stdListDouble.size());
  EXPECT_EQ(myListStrings.size(), stdListString.size());
}

TEST(S21ListTest, ConstructorWithArray) {
  s21::list<int> myList = {1, 2, 3, 4, 5, 6, 7};

  for (int i = 1; i < 8; i++) {
    EXPECT_EQ(myList.front(), i);
    myList.pop_front();
  }

  EXPECT_EQ(myList.size(), 0);
}

TEST(S21ListTest, CopyConstructor) {
  s21::list<int> originalList = {1, 2, 3, 4, 5};
  s21::list<int> copiedList(originalList);

  EXPECT_EQ(copiedList.size(), originalList.size());

  auto originalIt = originalList.begin();
  auto copiedIt = copiedList.begin();
  for (; originalIt != originalList.end(); ++originalIt, ++copiedIt) {
    EXPECT_EQ(*originalIt, *copiedIt);
  }

  originalList.push_back(6);
  EXPECT_EQ(copiedList.size(), 5);
  EXPECT_EQ(originalList.size(), 6);
}

TEST(S21ListTest, CunstructorMove) {
  double array[] = {1.64, 38.3, 69.69, 3.0};
  s21::list<double> originalList = {1.64, 38.3, 69.69, 3.0};
  s21::list<double> movedList = std::move(originalList);

  EXPECT_EQ(originalList.size(), 0);
  EXPECT_EQ(movedList.size(), 4);

  auto beginMovedArray = movedList.end();

  for (int i = 0; beginMovedArray != movedList.end(); beginMovedArray++, i++) {
    EXPECT_EQ(*beginMovedArray, array[i]);
  }
}

TEST(S21ListTest, PushBackAndPopBackAndBack) {
  s21::list<int> myList;
  std::list<int> stdList;

  for (int i = 0; i < 10; i++) {
    myList.push_back(i * 134);
    stdList.push_back(i * 134);
  }

  EXPECT_EQ(myList.size(), 10);
  EXPECT_EQ(myList.size(), stdList.size());

  for (int i = 9; i >= 0; i--) {
    EXPECT_EQ(myList.back(), i * 134);
    EXPECT_EQ(myList.back(), stdList.back());
    myList.pop_back();
    stdList.pop_back();
  }

  EXPECT_EQ(myList.size(), 0);
  EXPECT_THROW(myList.back(), std::out_of_range);
  EXPECT_THROW(myList.pop_back(), std::out_of_range);
}

TEST(S21ListTest, PushFrontAndPopFrontAndFront) {
  s21::list<int> myList;
  std::list<int> stdList;

  for (int i = 0; i < 10; i++) {
    myList.push_front(i * 134);
    stdList.push_front(i * 134);
  }

  EXPECT_EQ(myList.size(), 10);
  EXPECT_EQ(myList.size(), stdList.size());

  for (int i = 9; i >= 0; i--) {
    EXPECT_EQ(myList.front(), i * 134);
    EXPECT_EQ(myList.front(), stdList.front());
    myList.pop_front();
    stdList.pop_front();
  }

  EXPECT_EQ(myList.size(), 0);
  EXPECT_THROW(myList.front(), std::out_of_range);
  EXPECT_THROW(myList.pop_front(), std::out_of_range);
}

TEST(S21ListTest, InsertPosAndValue) {
  std::list<int> numbers1{1, 2, 3, 4, 5};
  s21::list<int> numbers2{1, 2, 3, 4, 5};

  auto iter1 = numbers1.begin();
  auto iter2 = numbers2.begin();
  iter1++;
  iter2++;

  auto iter3 = numbers1.end();
  auto iter4 = numbers2.end();

  numbers1.insert(iter1, 0);
  numbers1.insert(iter3, 38);
  numbers2.insert(iter2, 0);
  numbers2.insert(iter4, 38);

  for (int i = 0; i < 7; i++) {
    EXPECT_EQ(numbers1.front(), numbers2.front());
    numbers1.pop_front();
    numbers2.pop_front();
  }

  EXPECT_EQ(numbers1.size(), numbers2.size());
}

TEST(S21ListTest, InsertAtBeginning) {
  s21::list<int> numbers1{1, 2, 3, 4, 5};
  std::list<int> numbers2{1, 2, 3, 4, 5};

  numbers1.insert(numbers1.begin(), 0);
  numbers2.insert(numbers2.begin(), 0);

  for (int i = 0; i < 6; i++) {
    EXPECT_EQ(numbers1.front(), numbers2.front());
    numbers1.pop_front();
    numbers2.pop_front();
  }

  EXPECT_EQ(numbers1.size(), numbers2.size());
}

TEST(S21ListTest, InsertAtEnd) {
  s21::list<int> numbers1{1, 2, 3, 4, 5};
  std::list<int> numbers2{1, 2, 3, 4, 5};

  numbers1.insert(numbers1.end(), 38);
  numbers2.insert(numbers2.end(), 38);

  for (int i = 0; i < 6; i++) {
    EXPECT_EQ(numbers1.front(), numbers2.front());
    numbers1.pop_front();
    numbers2.pop_front();
  }

  EXPECT_EQ(numbers1.size(), numbers2.size());
}

TEST(S21ListTest, InsertInMiddle) {
  s21::list<int> numbers1{1, 2, 3, 4, 5};
  std::list<int> numbers2{1, 2, 3, 4, 5};

  auto iter1 = numbers1.begin();
  auto iter2 = numbers2.begin();
  ++iter1;
  ++iter2;

  numbers1.insert(iter1, 10);
  numbers2.insert(iter2, 10);

  for (int i = 0; i < 6; i++) {
    EXPECT_EQ(numbers1.front(), numbers2.front());
    numbers1.pop_front();
    numbers2.pop_front();
  }

  EXPECT_EQ(numbers1.size(), numbers2.size());
}

TEST(S21ListTest, InsertIntoEmptyList2) {
  s21::list<int> numbers1;
  std::list<int> numbers2;

  numbers1.insert(numbers1.begin(), 10);
  numbers2.insert(numbers2.begin(), 10);

  EXPECT_EQ(numbers1.front(), numbers2.front());
  numbers1.pop_front();
  numbers2.pop_front();

  EXPECT_EQ(numbers1.size(), numbers2.size());
}

TEST(S21ListTest, InsertAtBeginningOfSingleElementList) {
  s21::list<int> numbers1{1};
  std::list<int> numbers2{1};

  numbers1.insert(numbers1.begin(), 0);
  numbers2.insert(numbers2.begin(), 0);

  for (int i = 0; i < 2; i++) {
    EXPECT_EQ(numbers1.front(), numbers2.front());
    numbers1.pop_front();
    numbers2.pop_front();
  }

  EXPECT_EQ(numbers1.size(), numbers2.size());
}

TEST(S21ListTest, InsertPosAndValueAndCount) {
  s21::list<int> numbers1{1, 2, 3, 4, 5};
  std::list<int> numbers2{1, 2, 3, 4, 5};

  auto iter1 = numbers1.begin();
  auto iter2 = numbers2.begin();

  numbers1.insert(++iter1, 3, 4);
  numbers2.insert(++iter2, 3, 4);

  for (int i = 0; i < 8; i++) {
    EXPECT_EQ(numbers1.front(), numbers2.front());
    numbers1.pop_front();
    numbers2.pop_front();
  }

  EXPECT_EQ(numbers1.size(), numbers2.size());
}

TEST(S21ListTest, InsertCountAtBeginning) {
  s21::list<int> numbers1{1, 2, 3, 4, 5};
  std::list<int> numbers2{1, 2, 3, 4, 5};

  numbers1.insert(numbers1.begin(), 3, 0);
  numbers2.insert(numbers2.begin(), 3, 0);

  for (int i = 0; i < 8; i++) {
    EXPECT_EQ(numbers1.front(), numbers2.front());
    numbers1.pop_front();
    numbers2.pop_front();
  }

  EXPECT_EQ(numbers1.size(), numbers2.size());
}

TEST(S21ListTest, InsertCountInMiddle) {
  s21::list<int> numbers1{1, 2, 3, 4, 5};
  std::list<int> numbers2{1, 2, 3, 4, 5};

  auto iter1 = numbers1.begin();
  auto iter2 = numbers2.begin();
  ++iter1;
  ++iter2;

  numbers1.insert(iter1, 3, 10);
  numbers2.insert(iter2, 3, 10);

  for (int i = 0; i < 8; i++) {
    EXPECT_EQ(numbers1.front(), numbers2.front());
    numbers1.pop_front();
    numbers2.pop_front();
  }

  EXPECT_EQ(numbers1.size(), numbers2.size());
}

TEST(S21ListTest, InsertCountAtEnd) {
  s21::list<int> numbers1{1, 2, 3, 4, 5};
  std::list<int> numbers2{1, 2, 3, 4, 5};

  numbers1.insert(numbers1.end(), 3, 20);
  numbers2.insert(numbers2.end(), 3, 20);

  for (int i = 0; i < 8; i++) {
    EXPECT_EQ(numbers1.front(), numbers2.front());
    numbers1.pop_front();
    numbers2.pop_front();
  }

  EXPECT_EQ(numbers1.size(), numbers2.size());
}

TEST(S21ListTest, InsertZeroCount) {
  s21::list<int> numbers1{1, 2, 3, 4, 5};
  std::list<int> numbers2{1, 2, 3, 4, 5};

  auto iter1 = numbers1.begin();
  auto iter2 = numbers2.begin();
  ++iter1;
  ++iter2;

  numbers1.insert(iter1, 0, 10);
  numbers2.insert(iter2, 0, 10);

  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(numbers1.front(), numbers2.front());
    numbers1.pop_front();
    numbers2.pop_front();
  }

  EXPECT_EQ(numbers1.size(), numbers2.size());
}

TEST(S21ListTest, InsertIntoEmptyList) {
  s21::list<int> numbers1;
  std::list<int> numbers2;

  numbers1.insert(numbers1.begin(), 5, 10);
  numbers2.insert(numbers2.begin(), 5, 10);

  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(numbers1.front(), numbers2.front());
    numbers1.pop_front();
    numbers2.pop_front();
  }

  EXPECT_EQ(numbers1.size(), numbers2.size());
}

TEST(S21ListTest, InsertRange) {
  std::list<int> numbers1{1, 2, 3, 4, 5};
  s21::list<int> numbers2{1, 2, 3, 4, 5};

  std::list<int> toInsert{10, 20, 30};
  s21::list<int> toInsertS21{10, 20, 30};

  auto iter1 = numbers1.begin();
  auto iter2 = numbers2.begin();
  iter1++;
  iter2++;

  numbers1.insert(iter1, toInsert.begin(), toInsert.end());
  numbers2.insert(iter2, toInsertS21.begin(), toInsertS21.end());

  for (int i = 0; i < 8; i++) {
    EXPECT_EQ(numbers1.front(), numbers2.front());
    numbers1.pop_front();
    numbers2.pop_front();
  }

  EXPECT_EQ(numbers1.size(), numbers2.size());
}

TEST(S21ListTest, InsertEmptyRange) {
  std::list<int> numbers1{1, 2, 3, 4, 5};
  s21::list<int> numbers2{1, 2, 3, 4, 5};

  std::list<int> toInsert;
  s21::list<int> toInsertS21;

  auto iter1 = numbers1.begin();
  auto iter2 = numbers2.begin();
  iter1++;
  iter2++;

  numbers1.insert(iter1, toInsert.begin(), toInsert.end());
  numbers2.insert(iter2, toInsertS21.begin(), toInsertS21.end());

  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(numbers1.front(), numbers2.front());
    numbers1.pop_front();
    numbers2.pop_front();
  }

  EXPECT_EQ(numbers1.size(), numbers2.size());
}

TEST(S21ListTest, InsertRangeAtEnd) {
  std::list<int> numbers1{1, 2, 3, 4, 5};
  s21::list<int> numbers2{1, 2, 3, 4, 5};

  std::list<int> toInsert{10, 20, 30};
  s21::list<int> toInsertS21{10, 20, 30};

  numbers1.insert(numbers1.end(), toInsert.begin(), toInsert.end());
  numbers2.insert(numbers2.end(), toInsertS21.begin(), toInsertS21.end());

  for (int i = 0; i < 8; i++) {
    EXPECT_EQ(numbers1.front(), numbers2.front());
    numbers1.pop_front();
    numbers2.pop_front();
  }

  EXPECT_EQ(numbers1.size(), numbers2.size());
}

TEST(S21ListTest, ResizeLarger) {
  s21::list<int> numbers1{1, 2, 3};
  std::list<int> numbers2{1, 2, 3};

  numbers1.resize(5, 4);
  numbers2.resize(5, 4);

  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(numbers1.front(), numbers2.front());
    numbers1.pop_front();
    numbers2.pop_front();
  }

  EXPECT_EQ(numbers1.size(), numbers2.size());
}

TEST(S21ListTest, ResizeSmaller) {
  s21::list<int> numbers1{1, 2, 3, 4, 5};
  std::list<int> numbers2{1, 2, 3, 4, 5};

  numbers1.resize(3);
  numbers2.resize(3);

  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(numbers1.front(), numbers2.front());
    numbers1.pop_front();
    numbers2.pop_front();
  }

  EXPECT_EQ(numbers1.size(), numbers2.size());
}

TEST(S21ListTest, ResizeToZero) {
  s21::list<int> numbers1{1, 2, 3, 4, 5};
  std::list<int> numbers2{1, 2, 3, 4, 5};

  numbers1.resize(0);
  numbers2.resize(0);

  EXPECT_EQ(numbers1.size(), numbers2.size());
}

TEST(S21ListTest, ResizeEmptyList) {
  s21::list<int> numbers1;
  std::list<int> numbers2;

  numbers1.resize(5, 10);
  numbers2.resize(5, 10);

  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(numbers1.front(), numbers2.front());
    numbers1.pop_front();
    numbers2.pop_front();
  }

  EXPECT_EQ(numbers1.size(), numbers2.size());
}

TEST(S21ListTest, ResizeNoChange) {
  s21::list<int> numbers1{1, 2, 3};
  std::list<int> numbers2{1, 2, 3};

  numbers1.resize(3);
  numbers2.resize(3);

  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(numbers1.front(), numbers2.front());
    numbers1.pop_front();
    numbers2.pop_front();
  }

  EXPECT_EQ(numbers1.size(), numbers2.size());
}

TEST(S21ListTest, Erase) {
  std::list<int> numbers1{1, 2, 3, 4, 5, 6, 7};
  s21::list<int> numbers2{1, 2, 3, 4, 5, 6, 7};

  auto iter1 = numbers1.begin();
  auto iter2 = numbers2.begin();

  numbers1.erase(iter1);
  numbers2.erase(iter2);

  for (int i = 0; i < 6; i++) {
    EXPECT_EQ(numbers1.front(), numbers2.front());
    numbers1.pop_front();
    numbers2.pop_front();
  }
}

TEST(S21ListTest, EraseSingleElement) {
  s21::list<int> numbers1 = {1, 2, 3, 4, 5};
  std::list<int> numbers2 = {1, 2, 3, 4, 5};

  auto iter1 = numbers1.begin();
  auto iter2 = numbers2.begin();

  ++iter1;
  ++iter2;

  iter1 = numbers1.erase(iter1);
  iter2 = numbers2.erase(iter2);

  while (iter1 != numbers1.end() && iter2 != numbers2.end()) {
    EXPECT_EQ(*iter1, *iter2);
    ++iter1;
    ++iter2;
  }

  EXPECT_EQ(numbers1.size(), numbers2.size());
}

TEST(S21ListTest, EraseFirstElement) {
  s21::list<int> numbers1 = {1, 2, 3, 4, 5};
  std::list<int> numbers2 = {1, 2, 3, 4, 5};

  auto iter1 = numbers1.begin();
  auto iter2 = numbers2.begin();

  iter1 = numbers1.erase(iter1);
  iter2 = numbers2.erase(iter2);

  for (size_t i = 0; i < numbers1.size(); i++) {
    EXPECT_EQ(*iter1, *iter2);
    ++iter1;
    ++iter2;
  }

  EXPECT_EQ(numbers1.size(), numbers2.size());
}

TEST(S21ListTest, EraseLastElement) {
  s21::list<int> numbers1 = {1, 2, 3, 4, 5};
  std::list<int> numbers2 = {1, 2, 3, 4, 5};

  auto iter1 = numbers1.end();
  auto iter2 = numbers2.end();

  --iter1;
  --iter2;

  iter1 = numbers1.erase(iter1);
  iter2 = numbers2.erase(iter2);

  EXPECT_EQ(iter1, numbers1.end());
  EXPECT_EQ(iter2, numbers2.end());

  auto it1 = numbers1.begin();
  auto it2 = numbers2.begin();
  for (size_t i = 0; i < numbers1.size(); i++) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }

  EXPECT_EQ(numbers1.size(), numbers2.size());
}

TEST(S21ListTest, EraseFromEmptyList) {
  s21::list<int> numbers1;
  std::list<int> numbers2;

  auto iter1 = numbers1.begin();
  auto iter2 = numbers2.begin();

  EXPECT_EQ(iter1, numbers1.end());
  EXPECT_EQ(iter2, numbers2.end());

  EXPECT_EQ(numbers1.size(), numbers2.size());
}

TEST(S21ListTest, EraseSingleElementList) {
  s21::list<int> numbers1 = {42};
  std::list<int> numbers2 = {42};

  auto iter1 = numbers1.begin();
  auto iter2 = numbers2.begin();

  iter1 = numbers1.erase(iter1);
  iter2 = numbers2.erase(iter2);

  EXPECT_EQ(iter1, numbers1.end());
  EXPECT_EQ(iter2, numbers2.end());

  EXPECT_EQ(numbers1.size(), numbers2.size());
}

TEST(S21ListTest, TestSwap) {
  s21::list<int> numbers1 = {1, 4, 38, 9, 495, 237, 10, 23};
  s21::list<int> numbers2 = {1, 2, 3, 4};

  std::list<int> numbers3 = {1, 4, 38, 9, 495, 237, 10, 23};
  std::list<int> numbers4 = {1, 2, 3, 4};

  numbers1.swap(numbers2);
  numbers3.swap(numbers4);

  EXPECT_EQ(numbers1.size(), numbers3.size());
  EXPECT_EQ(numbers2.size(), numbers4.size());

  for (size_t i = 0; i < numbers1.size(); i++) {
    EXPECT_EQ(numbers1.front(), numbers3.front());
    numbers1.pop_front();
    numbers3.pop_front();
  }

  for (size_t i = 0; i < numbers2.size(); i++) {
    EXPECT_EQ(numbers2.front(), numbers4.front());
    numbers2.pop_front();
    numbers4.pop_front();
  }

  EXPECT_EQ(numbers1.size(), numbers3.size());
  EXPECT_EQ(numbers2.size(), numbers4.size());
}

TEST(S21ListTest, TestSwapEmptyLists) {
  s21::list<int> numbers1;
  s21::list<int> numbers2;

  std::list<int> numbers3;
  std::list<int> numbers4;

  numbers1.swap(numbers2);
  numbers3.swap(numbers4);

  EXPECT_EQ(numbers1.size(), numbers3.size());
  EXPECT_EQ(numbers2.size(), numbers4.size());
}

TEST(S21ListTest, TestSwapWithSelf) {
  s21::list<int> numbers1 = {1, 2, 3, 4};
  std::list<int> numbers2 = {1, 2, 3, 4};

  numbers1.swap(numbers1);
  numbers2.swap(numbers2);

  EXPECT_EQ(numbers1.size(), numbers2.size());

  auto iter1 = numbers1.begin();
  auto iter2 = numbers2.begin();
  for (size_t i = 0; i < numbers1.size(); i++) {
    EXPECT_EQ(*iter1, *iter2);
    ++iter1;
    ++iter2;
  }
}

TEST(S21ListTest, TestSwapDifferentSizes) {
  s21::list<int> numbers1 = {1, 2, 3};
  s21::list<int> numbers2 = {4, 5, 6, 7, 8};

  std::list<int> numbers3 = {1, 2, 3};
  std::list<int> numbers4 = {4, 5, 6, 7, 8};

  numbers1.swap(numbers2);
  numbers3.swap(numbers4);

  EXPECT_EQ(numbers1.size(), numbers3.size());
  EXPECT_EQ(numbers2.size(), numbers4.size());

  auto iter1 = numbers1.begin();
  auto iter3 = numbers3.begin();
  for (size_t i = 0; i < numbers1.size(); i++) {
    EXPECT_EQ(*iter1, *iter3);
    ++iter1;
    ++iter3;
  }

  auto iter2 = numbers2.begin();
  auto iter4 = numbers4.begin();
  for (size_t i = 0; i < numbers2.size(); i++) {
    EXPECT_EQ(*iter2, *iter4);
    ++iter2;
    ++iter4;
  }
}

TEST(S21ListItest, TestUnique) {
  s21::list<int> numbers1 = {1, 5, 5, 834, 3, 4, 5, 3, 5, 5, 5, 5};
  std::list<int> numbers2 = {1, 5, 5, 834, 3, 4, 5, 3, 5, 5, 5, 5};
  numbers1.unique();
  numbers2.unique();

  auto iter1 = numbers1.begin();
  auto iter2 = numbers2.begin();

  for (size_t i = 0; i < numbers1.size(); i++) {
    EXPECT_EQ(*iter1, *iter2);
    iter1++;
    iter2++;
  }
}

TEST(S21ListTest, UniqueEmptyList) {
  s21::list<int> s21_list;
  std::list<int> std_list;

  s21_list.unique();
  std_list.unique();

  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(S21ListTest, UniqueSingleElement) {
  s21::list<int> s21_list = {1};
  std::list<int> std_list = {1};

  s21_list.unique();
  std_list.unique();

  EXPECT_EQ(s21_list.size(), std_list.size());
  auto s21_it = s21_list.begin();
  auto std_it = std_list.begin();
  for (; s21_it != s21_list.end() && std_it != std_list.end();
       ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(S21ListTest, UniqueConsecutiveDuplicates) {
  s21::list<int> s21_list = {1, 2, 2, 2, 3, 3, 4, 5, 5, 5};
  std::list<int> std_list = {1, 2, 2, 2, 3, 3, 4, 5, 5, 5};

  s21_list.unique();
  std_list.unique();

  EXPECT_EQ(s21_list.size(), std_list.size());
  auto s21_it = s21_list.begin();
  auto std_it = std_list.begin();
  for (; s21_it != s21_list.end() && std_it != std_list.end();
       ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(S21ListTest, UniqueNoDuplicates) {
  s21::list<int> s21_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};

  s21_list.unique();
  std_list.unique();

  EXPECT_EQ(s21_list.size(), std_list.size());
  auto s21_it = s21_list.begin();
  auto std_it = std_list.begin();
  for (; s21_it != s21_list.end() && std_it != std_list.end();
       ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(S21ListTest, UniqueNonConsecutiveDuplicates) {
  s21::list<int> s21_list = {1, 2, 1, 3, 2, 4, 1, 5};
  std::list<int> std_list = {1, 2, 1, 3, 2, 4, 1, 5};

  s21_list.unique();
  std_list.unique();

  EXPECT_EQ(s21_list.size(), std_list.size());
  auto s21_it = s21_list.begin();
  auto std_it = std_list.begin();
  for (; s21_it != s21_list.end() && std_it != std_list.end();
       ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(S21ListTest, UniqueAllSameElements) {
  s21::list<int> s21_list = {2, 2, 2, 2, 2};
  std::list<int> std_list = {2, 2, 2, 2, 2};

  s21_list.unique();
  std_list.unique();

  EXPECT_EQ(s21_list.size(), std_list.size());
  auto s21_it = s21_list.begin();
  auto std_it = std_list.begin();
  for (; s21_it != s21_list.end() && std_it != std_list.end();
       ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(S21ListTest, UniqueAlternatingDuplicates) {
  s21::list<int> s21_list = {1, 1, 2, 2, 1, 1, 3, 3};
  std::list<int> std_list = {1, 1, 2, 2, 1, 1, 3, 3};

  s21_list.unique();
  std_list.unique();

  EXPECT_EQ(s21_list.size(), std_list.size());
  auto s21_it = s21_list.begin();
  auto std_it = std_list.begin();
  for (; s21_it != s21_list.end() && std_it != std_list.end();
       ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(S21ListTest, UniqueLargeList) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  for (int i = 0; i < 100; ++i) {
    s21_list.push_back(i % 10);
    std_list.push_back(i % 10);
  }

  s21_list.unique();
  std_list.unique();

  EXPECT_EQ(s21_list.size(), std_list.size());
  auto s21_it = s21_list.begin();
  auto std_it = std_list.begin();
  for (; s21_it != s21_list.end() && std_it != std_list.end();
       ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(S21ListTest, UniqueDuplicatesAtEdges) {
  s21::list<int> s21_list = {1, 1, 1, 2, 3, 4, 5, 5, 5};
  std::list<int> std_list = {1, 1, 1, 2, 3, 4, 5, 5, 5};

  s21_list.unique();
  std_list.unique();

  EXPECT_EQ(s21_list.size(), std_list.size());
  auto s21_it = s21_list.begin();
  auto std_it = std_list.begin();
  for (; s21_it != s21_list.end() && std_it != std_list.end();
       ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(S21ListTest, UniqueIteratorValidity) {
  s21::list<int> s21_list = {1, 2, 2, 3, 3, 4, 5, 5};
  std::list<int> std_list = {1, 2, 2, 3, 3, 4, 5, 5};

  s21_list.unique();
  std_list.unique();

  size_t s21_size = 0;
  for (auto it = s21_list.begin(); it != s21_list.end(); ++it) {
    ++s21_size;
  }
  size_t std_size = 0;
  for (auto it = std_list.begin(); it != std_list.end(); ++it) {
    ++std_size;
  }

  EXPECT_EQ(s21_size, std_size);
  EXPECT_EQ(s21_list.size(), s21_size);
}

TEST(S21ListTest, MergeTwoSortedLists) {
  std::list<int> stdList1 = {1, 3, 5, 7};
  std::list<int> stdList2 = {2, 4, 6, 8};

  s21::list<int> s21List1 = {1, 3, 5, 7};
  s21::list<int> s21List2 = {2, 4, 6, 8};

  stdList1.merge(stdList2);
  s21List1.merge(s21List2);

  auto stdIt = stdList1.begin();
  auto s21It = s21List1.begin();
  for (; stdIt != stdList1.end() && s21It != s21List1.end(); ++stdIt, ++s21It) {
    EXPECT_EQ(*stdIt, *s21It);
  }

  EXPECT_EQ(stdList1.size(), s21List1.size());
  EXPECT_EQ(stdList2.size(), s21List2.size());
  EXPECT_EQ(stdList2.size(), 0);
  EXPECT_EQ(s21List2.size(), 0);
}

TEST(S21ListTest, MergeEmptyWithNonEmpty) {
  std::list<int> stdList1;
  std::list<int> stdList2 = {1, 2, 3};

  s21::list<int> s21List1;
  s21::list<int> s21List2 = {1, 2, 3};

  stdList1.merge(stdList2);
  s21List1.merge(s21List2);

  auto stdIt = stdList1.begin();
  auto s21It = s21List1.begin();
  for (; stdIt != stdList1.end() && s21It != s21List1.end(); ++stdIt, ++s21It) {
    EXPECT_EQ(*stdIt, *s21It);
  }

  EXPECT_EQ(stdList1.size(), s21List1.size());
  EXPECT_EQ(stdList2.size(), s21List2.size());
  EXPECT_EQ(stdList2.size(), 0);
  EXPECT_EQ(s21List2.size(), 0);
}

TEST(S21ListTest, MergeNonEmptyWithEmpty) {
  std::list<int> stdList1 = {1, 2, 3};
  std::list<int> stdList2;

  s21::list<int> s21List1 = {1, 2, 3};
  s21::list<int> s21List2;

  stdList1.merge(stdList2);
  s21List1.merge(s21List2);

  auto stdIt = stdList1.begin();
  auto s21It = s21List1.begin();
  for (; stdIt != stdList1.end() && s21It != s21List1.end(); ++stdIt, ++s21It) {
    EXPECT_EQ(*stdIt, *s21It);
  }

  EXPECT_EQ(stdList1.size(), s21List1.size());
  EXPECT_EQ(stdList2.size(), s21List2.size());
  EXPECT_EQ(stdList2.size(), 0);
  EXPECT_EQ(s21List2.size(), 0);
}

TEST(S21ListTest, MergeTwoEmptyLists) {
  std::list<int> stdList1;
  std::list<int> stdList2;

  s21::list<int> s21List1;
  s21::list<int> s21List2;

  stdList1.merge(stdList2);
  s21List1.merge(s21List2);

  EXPECT_EQ(stdList1.size(), s21List1.size());
  EXPECT_EQ(stdList2.size(), s21List2.size());
  EXPECT_EQ(stdList1.size(), 0);
  EXPECT_EQ(s21List1.size(), 0);
  EXPECT_EQ(stdList2.size(), 0);
  EXPECT_EQ(s21List2.size(), 0);
}

TEST(S21ListTest, MergeListsWithDuplicates) {
  std::list<int> stdList1 = {1, 2, 2, 3};
  std::list<int> stdList2 = {2, 3, 4};

  s21::list<int> s21List1 = {1, 2, 2, 3};
  s21::list<int> s21List2 = {2, 3, 4};

  stdList1.merge(stdList2);
  s21List1.merge(s21List2);

  auto stdIt = stdList1.begin();
  auto s21It = s21List1.begin();
  for (; stdIt != stdList1.end() && s21It != s21List1.end(); ++stdIt, ++s21It) {
    EXPECT_EQ(*stdIt, *s21It);
  }

  EXPECT_EQ(stdList1.size(), s21List1.size());
  EXPECT_EQ(stdList2.size(), s21List2.size());
  EXPECT_EQ(stdList2.size(), 0);
  EXPECT_EQ(s21List2.size(), 0);
}

TEST(S21ListTest, MergeSingleElementLists) {
  std::list<int> stdList1 = {1};
  std::list<int> stdList2 = {2};

  s21::list<int> s21List1 = {1};
  s21::list<int> s21List2 = {2};

  stdList1.merge(stdList2);
  s21List1.merge(s21List2);

  auto stdIt = stdList1.begin();
  auto s21It = s21List1.begin();
  for (; stdIt != stdList1.end() && s21It != s21List1.end(); ++stdIt, ++s21It) {
    EXPECT_EQ(*stdIt, *s21It);
  }

  EXPECT_EQ(stdList1.size(), s21List1.size());
  EXPECT_EQ(stdList2.size(), s21List2.size());
  EXPECT_EQ(stdList2.size(), 0);
  EXPECT_EQ(s21List2.size(), 0);
}

TEST(S21ListTest, SpliceSelf) {
  s21::list<int> numbers1 = {1, 2, 3, 4};

  auto pos1 = numbers1.begin();
  ++pos1;
  numbers1.splice(pos1, numbers1);

  EXPECT_EQ(numbers1.size(), 0);
  EXPECT_TRUE(numbers1.empty());
}

TEST(S21ListTest, SpliceFromEmpty) {
  s21::list<int> numbers1 = {1, 2, 3, 4};
  s21::list<int> empty_list;
  std::list<int> numbers2 = {1, 2, 3, 4};
  std::list<int> empty_list_std;

  auto pos1 = numbers1.begin();
  ++pos1;
  numbers1.splice(pos1, empty_list);

  auto pos2 = numbers2.begin();
  ++pos2;
  numbers2.splice(pos2, empty_list_std);

  EXPECT_EQ(numbers1.size(), numbers2.size());
  EXPECT_EQ(empty_list.size(), empty_list_std.size());

  auto iter1 = numbers1.begin();
  auto iter2 = numbers2.begin();
  for (size_t i = 0; i < numbers1.size(); i++) {
    EXPECT_EQ(*iter1, *iter2);
    ++iter1;
    ++iter2;
  }
}

TEST(S21ListTest, SpliceToEmpty) {
  s21::list<int> empty_list;
  s21::list<int> numbers1 = {1, 2, 3};
  std::list<int> empty_list_std;
  std::list<int> numbers2 = {1, 2, 3};

  empty_list.splice(empty_list.begin(), numbers1);
  empty_list_std.splice(empty_list_std.begin(), numbers2);

  EXPECT_EQ(empty_list.size(), empty_list_std.size());
  EXPECT_EQ(numbers1.size(), numbers2.size());

  auto iter1 = empty_list.begin();
  auto iter2 = empty_list_std.begin();
  for (size_t i = 0; i < empty_list.size(); i++) {
    EXPECT_EQ(*iter1, *iter2);
    ++iter1;
    ++iter2;
  }
}

TEST(S21ListTest, SpliceToMiddle) {
  s21::list<int> numbers1 = {1, 2, 3};
  s21::list<int> numbers2 = {4, 5, 6};
  std::list<int> numbers1_std = {1, 2, 3};
  std::list<int> numbers2_std = {4, 5, 6};

  auto pos1 = numbers1.begin();
  ++pos1;
  numbers1.splice(pos1, numbers2);

  auto pos2 = numbers1_std.begin();
  ++pos2;
  numbers1_std.splice(pos2, numbers2_std);

  EXPECT_EQ(numbers1.size(), numbers1_std.size());
  EXPECT_EQ(numbers2.size(), numbers2_std.size());

  auto iter1 = numbers1.begin();
  auto iter2 = numbers1_std.begin();
  for (size_t i = 0; i < numbers1.size(); i++) {
    EXPECT_EQ(*iter1, *iter2);
    ++iter1;
    ++iter2;
  }
}

TEST(S21ListTest, SpliceToBegin) {
  s21::list<int> numbers1 = {1, 2, 3};
  s21::list<int> numbers2 = {4, 5, 6};
  std::list<int> numbers1_std = {1, 2, 3};
  std::list<int> numbers2_std = {4, 5, 6};

  numbers1.splice(numbers1.begin(), numbers2);
  numbers1_std.splice(numbers1_std.begin(), numbers2_std);

  EXPECT_EQ(numbers1.size(), numbers1_std.size());
  EXPECT_EQ(numbers2.size(), numbers2_std.size());

  auto iter1 = numbers1.begin();
  auto iter2 = numbers1_std.begin();
  for (size_t i = 0; i < numbers1.size(); i++) {
    EXPECT_EQ(*iter1, *iter2);
    ++iter1;
    ++iter2;
  }
}

TEST(S21ListTest, SpliceToEnd) {
  s21::list<int> numbers1 = {1, 2, 3};
  s21::list<int> numbers2 = {4, 5, 6};
  std::list<int> numbers1_std = {1, 2, 3};
  std::list<int> numbers2_std = {4, 5, 6};

  numbers1.splice(numbers1.end(), numbers2);
  numbers1_std.splice(numbers1_std.end(), numbers2_std);

  EXPECT_EQ(numbers1.size(), numbers1_std.size());
  EXPECT_EQ(numbers2.size(), numbers2_std.size());

  auto iter1 = numbers1.begin();
  auto iter2 = numbers1_std.begin();
  for (size_t i = 0; i < numbers1.size(); i++) {
    EXPECT_EQ(*iter1, *iter2);
    ++iter1;
    ++iter2;
  }
}

TEST(S21ListTest, BeginEndEmptyList) {
  s21::list<int> list1;
  std::list<int> list2;

  EXPECT_EQ(list1.begin(), list1.end());
  EXPECT_EQ(list2.begin(), list2.end());

  auto iter1 = list1.begin();
  auto iter2 = list2.begin();
  EXPECT_TRUE(iter1 == list1.end());
  EXPECT_TRUE(iter2 == list2.end());
}

TEST(S21ListTest, BeginEndSingleElement) {
  s21::list<int> list1 = {42};
  std::list<int> list2 = {42};

  EXPECT_EQ(*list1.begin(), 42);
  EXPECT_EQ(*list2.begin(), 42);

  EXPECT_NE(list1.begin(), list1.end());
  EXPECT_NE(list2.begin(), list2.end());

  auto iter1 = list1.begin();
  auto iter2 = list2.begin();
  ++iter1;
  ++iter2;
  EXPECT_EQ(iter1, list1.end());
  EXPECT_EQ(iter2, list2.end());
}

TEST(S21ListTest, BeginEndMultipleElements) {
  s21::list<int> list1 = {1, 2, 3, 4};
  std::list<int> list2 = {1, 2, 3, 4};

  EXPECT_EQ(*list1.begin(), 1);
  EXPECT_EQ(*list2.begin(), 1);

  EXPECT_NE(list1.begin(), list1.end());
  EXPECT_NE(list2.begin(), list2.end());

  auto iter1 = list1.begin();
  auto iter2 = list2.begin();
  for (size_t i = 0; i < list1.size(); ++i) {
    EXPECT_EQ(*iter1, *iter2);
    ++iter1;
    ++iter2;
  }
  EXPECT_EQ(iter1, list1.end());
  EXPECT_EQ(iter2, list2.end());
}

TEST(S21ListTest, EndDecrement) {
  s21::list<int> list1 = {1, 2, 3, 4};
  std::list<int> list2 = {1, 2, 3, 4};

  auto iter1 = list1.end();
  auto iter2 = list2.end();
  --iter1;
  --iter2;
  EXPECT_EQ(*iter1, 4);
  EXPECT_EQ(*iter2, 4);

  for (size_t i = 0; i < list2.size(); ++i) {
    EXPECT_EQ(*iter1, *iter2);
    --iter1;
    --iter2;
  }
}

TEST(S21ListTest, BeginEndAfterModification) {
  s21::list<int> list1 = {1, 2, 3};
  std::list<int> list2 = {1, 2, 3};

  list1.pop_front();
  list2.pop_front();

  EXPECT_EQ(*list1.begin(), 2);
  EXPECT_EQ(*list2.begin(), 2);

  auto iter1 = list1.begin();
  auto iter2 = list2.begin();
  for (size_t i = 0; i < list2.size(); ++i) {
    EXPECT_EQ(*iter1, *iter2);
    ++iter1;
    ++iter2;
  }
  EXPECT_EQ(iter1, list1.end());
  EXPECT_EQ(iter2, list2.end());

  list1.push_front(0);
  list2.push_front(0);

  EXPECT_EQ(*list1.begin(), 0);
  EXPECT_EQ(*list2.begin(), 0);

  iter1 = list1.begin();
  iter2 = list2.begin();
  for (size_t i = 0; i < list2.size(); ++i) {
    EXPECT_EQ(*iter1, *iter2);
    ++iter1;
    ++iter2;
  }
  EXPECT_EQ(iter1, list1.end());
  EXPECT_EQ(iter2, list2.end());
}
