#include <gtest/gtest.h>

#include "../include/s21_array.h"

TEST(ArrayTest, DefaultConstructor_EmptyArray) {
  s21::array<int, 0> emptyArr;
  EXPECT_EQ(emptyArr.size(), 0);
}

TEST(ArrayTest, DefaultConstructor_SingleElement) {
  s21::array<int, 1> singleArr = {};
  EXPECT_EQ(singleArr.size(), 1);
}

TEST(ArrayTest, DefaultConstructor_LargeArray) {
  s21::array<int, 1000> largeArr = {};
  EXPECT_EQ(largeArr.size(), 1000);
}

TEST(ArrayTest, DefaultConstructor_SizeCheck) {
  s21::array<int, 5> arr = {};
  EXPECT_EQ(arr.size(), 5);
}

TEST(ArrayTest, DefaultConstructor_CompareWithEmpty) {
  s21::array<int, 5> arr1 = {};
  s21::array<int, 5> arr2 = {};
  EXPECT_EQ(arr1.size(), arr2.size());
}

TEST(ArrayTest, InitializerListConstructor_EmptyArray) {
  s21::array<int, 0> arr{};
  EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayTest, InitializerListConstructor_SingleElement) {
  s21::array<int, 1> arr{42};
  EXPECT_EQ(arr.size(), 1);
  EXPECT_EQ(arr[0], 42);
}

TEST(ArrayTest, InitializerListConstructor_FullArray) {
  s21::array<int, 3> arr{1, 2, 3};
  EXPECT_EQ(arr.size(), 3);
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTest, InitializerListConstructor_PartialArray) {
  s21::array<int, 3> arr{1, 2};
  EXPECT_EQ(arr.size(), 3);
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 0);
}

TEST(ArrayTest, CopyConstructor_EmptyArray) {
  s21::array<int, 0> original;
  s21::array<int, 0> copy(original);
  EXPECT_EQ(copy.size(), 0);
}

TEST(ArrayTest, CopyConstructor_SingleElement) {
  s21::array<int, 1> original{42};
  s21::array<int, 1> copy(original);
  EXPECT_EQ(copy.size(), 1);
  EXPECT_EQ(copy[0], 42);
}

TEST(ArrayTest, CopyConstructor_LargeArray) {
  s21::array<int, 1000> original;
  for (std::size_t i = 0; i < original.size(); ++i) {
    original[i] = static_cast<int>(i);
  }
  s21::array<int, 1000> copy(original);
  EXPECT_EQ(copy.size(), 1000);
  for (std::size_t i = 0; i < copy.size(); ++i) {
    EXPECT_EQ(copy[i], static_cast<int>(i));
  }
}

TEST(ArrayTest, CopyConstructor_Independence) {
  s21::array<int, 3> original{1, 2, 3};
  s21::array<int, 3> copy(original);
  copy[0] = 42;
  EXPECT_EQ(original[0], 1);
  EXPECT_EQ(copy[0], 42);
}

TEST(ArrayTest, CopyConstructor_UninitializedArray) {
  s21::array<int, 3> original = {};
  s21::array<int, 3> copy(original);
  EXPECT_EQ(copy.size(), 3);
  EXPECT_EQ(copy.size(), original.size());
}

TEST(ArrayTest, MoveConstructor_EmptyArray) {
  s21::array<int, 0> original;
  s21::array<int, 0> moved(std::move(original));
  EXPECT_EQ(moved.size(), 0);
  EXPECT_EQ(original.size(), 0);
}

TEST(ArrayTest, MoveConstructor_SingleElement) {
  s21::array<int, 1> original{42};
  s21::array<int, 1> moved(std::move(original));
  EXPECT_EQ(moved.size(), 1);
  EXPECT_EQ(moved[0], 42);
  EXPECT_EQ(original.size(), 1);
}

TEST(ArrayTest, MoveConstructor_LargeArray) {
  s21::array<int, 1000> original;
  for (std::size_t i = 0; i < original.size(); ++i) {
    original[i] = static_cast<int>(i);
  }
  s21::array<int, 1000> moved(std::move(original));
  EXPECT_EQ(moved.size(), 1000);
  for (std::size_t i = 0; i < moved.size(); ++i) {
    EXPECT_EQ(moved[i], static_cast<int>(i));
  }
  EXPECT_EQ(original.size(), 1000);
}

TEST(ArrayTest, MoveConstructor_Independence) {
  s21::array<int, 3> original{1, 2, 3};
  s21::array<int, 3> moved(std::move(original));
  moved[0] = 42;
  EXPECT_EQ(moved[0], 42);
  EXPECT_EQ(original.size(), 3);
}

TEST(ArrayTest, MoveConstructor_UninitializedArray) {
  s21::array<int, 3> original;
  s21::array<int, 3> moved(std::move(original));
  EXPECT_EQ(moved.size(), 3);
  EXPECT_EQ(original.size(), 3);
}

TEST(ArrayTest, MoveAssignment_EmptyArray) {
  s21::array<int, 0> original;
  s21::array<int, 0> assigned;
  assigned = std::move(original);
  EXPECT_EQ(assigned.size(), 0);
  EXPECT_EQ(original.size(), 0);
}

TEST(ArrayTest, MoveAssignment_SingleElement) {
  s21::array<int, 1> original{42};
  s21::array<int, 1> assigned;
  assigned = std::move(original);
  EXPECT_EQ(assigned.size(), 1);
  EXPECT_EQ(assigned[0], 42);
  EXPECT_EQ(original.size(), 1);
}

TEST(ArrayTest, MoveAssignment_FullArray) {
  s21::array<int, 3> original{1, 2, 3};
  s21::array<int, 3> assigned;
  assigned = std::move(original);
  EXPECT_EQ(assigned.size(), 3);
  EXPECT_EQ(assigned[0], 1);
  EXPECT_EQ(assigned[1], 2);
  EXPECT_EQ(assigned[2], 3);
  EXPECT_EQ(original.size(), 3);
}

TEST(ArrayTest, MoveAssignment_LargeArray) {
  s21::array<int, 1000> original;
  for (std::size_t i = 0; i < original.size(); ++i) {
    original[i] = static_cast<int>(i);
  }
  s21::array<int, 1000> assigned;
  assigned = std::move(original);
  EXPECT_EQ(assigned.size(), 1000);
  for (std::size_t i = 0; i < assigned.size(); ++i) {
    EXPECT_EQ(assigned[i], static_cast<int>(i));
  }
  EXPECT_EQ(original.size(), 1000);
}

TEST(ArrayTest, MoveAssignment_Independence) {
  s21::array<int, 3> original{1, 2, 3};
  s21::array<int, 3> assigned;
  assigned = std::move(original);
  assigned[0] = 42;
  EXPECT_EQ(assigned[0], 42);
  EXPECT_EQ(original[0], 1);
  EXPECT_EQ(original.size(), 3);
}

TEST(ArrayTest, MoveAssignment_UninitializedArray) {
  s21::array<int, 3> original{};
  s21::array<int, 3> assigned;
  assigned = std::move(original);
  EXPECT_EQ(assigned.size(), 3);
  for (std::size_t i = 0; i < assigned.size(); ++i) {
    EXPECT_EQ(assigned[i], 0);
  }
  EXPECT_EQ(original.size(), 3);
}

// Тесты для метода at
TEST(ArrayTest, At_ValidIndex) {
  s21::array<int, 3> arr{1, 2, 3};
  EXPECT_EQ(arr.at(0), 1);
  EXPECT_EQ(arr.at(1), 2);
  EXPECT_EQ(arr.at(2), 3);
}

TEST(ArrayTest, At_OutOfBounds) {
  s21::array<int, 3> arr{1, 2, 3};
  EXPECT_THROW(arr.at(3), std::out_of_range);
  EXPECT_THROW(arr.at(5), std::out_of_range);
}

TEST(ArrayTest, At_ConstArray) {
  s21::array<int, 3> arr{1, 2, 3};
  EXPECT_EQ(arr.at(0), 1);
  EXPECT_EQ(arr.at(1), 2);
  EXPECT_EQ(arr.at(2), 3);
  EXPECT_THROW(arr.at(3), std::out_of_range);
}

TEST(ArrayTest, At_EmptyArray) {
  s21::array<int, 0> arr;
  EXPECT_THROW(arr.at(0), std::out_of_range);
}

// Тесты для operator[]
TEST(ArrayTest, OperatorSquareBrackets_ValidIndex) {
  s21::array<int, 3> arr{1, 2, 3};
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTest, OperatorSquareBrackets_ModifyElement) {
  s21::array<int, 3> arr{1, 2, 3};
  arr[1] = 42;
  EXPECT_EQ(arr[1], 42);
}

TEST(ArrayTest, OperatorSquareBrackets_ConstArray) {
  s21::array<int, 3> arr{1, 2, 3};
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTest, OperatorSquareBrackets_UninitializedArray) {
  s21::array<int, 3> arr{};
  EXPECT_EQ(arr[0], 0);
  EXPECT_EQ(arr[1], 0);
  EXPECT_EQ(arr[2], 0);
}

// Тесты для front
TEST(ArrayTest, Front_NonEmptyArray) {
  s21::array<int, 3> arr{1, 2, 3};
  EXPECT_EQ(arr.front(), 1);
}

TEST(ArrayTest, Front_ConstArray) {
  const s21::array<int, 3> arr{1, 2, 3};
  EXPECT_EQ(arr.front(), 1);
}

TEST(ArrayTest, Front_SingleElementArray) {
  s21::array<int, 1> arr{42};
  EXPECT_EQ(arr.front(), 42);
}

TEST(ArrayTest, Back_NonEmptyArray) {
  s21::array<int, 3> arr{1, 2, 3};
  EXPECT_EQ(arr.back(), 3);
}

TEST(ArrayTest, Back_ConstArray) {
  const s21::array<int, 3> arr{1, 2, 3};
  EXPECT_EQ(arr.back(), 3);
}

TEST(ArrayTest, Back_SingleElementArray) {
  s21::array<int, 1> arr{42};
  EXPECT_EQ(arr.back(), 42);
}

// Тесты для data
TEST(ArrayTest, Data_NonEmptyArray) {
  s21::array<int, 3> arr{1, 2, 3};
  int* ptr = arr.data();
  EXPECT_EQ(ptr[0], 1);
  EXPECT_EQ(ptr[1], 2);
  EXPECT_EQ(ptr[2], 3);
}

TEST(ArrayTest, Data_ModifyThroughData) {
  s21::array<int, 3> arr{1, 2, 3};
  int* ptr = arr.data();
  ptr[1] = 42;
  EXPECT_EQ(arr[1], 42);
}

TEST(ArrayTest, Data_ConstArray) {
  s21::array<int, 3> arr{1, 2, 3};
  const int* ptr = arr.data();
  EXPECT_EQ(ptr[0], 1);
  EXPECT_EQ(ptr[1], 2);
  EXPECT_EQ(ptr[2], 3);
}

TEST(ArrayTest, Data_EmptyArray) {
  s21::array<int, 0> arr;
  EXPECT_EQ(arr.data(), nullptr);
}

TEST(ArrayTest, Data_UninitializedArray) {
  s21::array<int, 3> arr{};
  int* ptr = arr.data();
  EXPECT_EQ(ptr[0], 0);
  EXPECT_EQ(ptr[1], 0);
  EXPECT_EQ(ptr[2], 0);
}

// Тесты для begin
TEST(ArrayTest, Begin_NonEmptyArray) {
  s21::array<int, 3> arr{1, 2, 3};
  auto it = arr.begin();
  EXPECT_EQ(*it, 1);
}

TEST(ArrayTest, Begin_EmptyArray) {
  s21::array<int, 0> arr;
  auto it = arr.begin();
  EXPECT_EQ(it, arr.end());  // Для пустого массива begin() == end()
}

TEST(ArrayTest, Begin_ModifyThroughIterator) {
  s21::array<int, 3> arr{1, 2, 3};
  auto it = arr.begin();
  *it = 42;
  EXPECT_EQ(arr[0], 42);
}

TEST(ArrayTest, Begin_ConstArray) {
  s21::array<int, 3> arr{1, 2, 3};
  auto it = arr.begin();
  EXPECT_EQ(*it, 1);
}

TEST(ArrayTest, Begin_UninitializedArray) {
  s21::array<int, 3> arr{};
  auto it = arr.begin();
  EXPECT_EQ(*it, 0);
}

// Тесты для end
TEST(ArrayTest, End_NonEmptyArray) {
  s21::array<int, 3> arr{1, 2, 3};
  auto it = arr.end();
  EXPECT_EQ(*(it - 1), 3);
}

TEST(ArrayTest, End_EmptyArray) {
  s21::array<int, 0> arr;
  auto it = arr.end();
  EXPECT_EQ(it, arr.begin());
}

TEST(ArrayTest, End_ConstArray) {
  s21::array<int, 3> arr{1, 2, 3};
  auto it = arr.end();
  EXPECT_EQ(*(it - 1), 3);
}

TEST(ArrayTest, End_IterateToEnd) {
  s21::array<int, 3> arr{1, 2, 3};
  auto it = arr.begin();
  int count = 0;
  while (it != arr.end()) {
    ++it;
    ++count;
  }
  EXPECT_EQ(count, 3);
}

// Тесты для empty
TEST(ArrayTest, Empty_EmptyArray) {
  s21::array<int, 0> arr;
  EXPECT_TRUE(arr.empty());
}

TEST(ArrayTest, Empty_NonEmptyArray) {
  s21::array<int, 1> arr{1};
  EXPECT_FALSE(arr.empty());
}

TEST(ArrayTest, Empty_ConstArray) {
  const s21::array<int, 0> arr{};
  EXPECT_TRUE(arr.empty());
}

TEST(ArrayTest, Empty_UninitializedArray) {
  s21::array<int, 3> arr{};
  EXPECT_FALSE(
      arr.empty());  // Даже если элементы не инициализированы, массив не пуст
}

// Тесты для size
TEST(ArrayTest, Size_EmptyArray) {
  s21::array<int, 0> arr;
  EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayTest, Size_NonEmptyArray) {
  s21::array<int, 3> arr{1, 2, 3};
  EXPECT_EQ(arr.size(), 3);
}

TEST(ArrayTest, Size_ConstArray) {
  const s21::array<int, 3> arr{1, 2, 3};
  EXPECT_EQ(arr.size(), 3);
}

TEST(ArrayTest, Size_UninitializedArray) {
  s21::array<int, 3> arr{};
  EXPECT_EQ(arr.size(), 3);
}

// Тесты для max_size
TEST(ArrayTest, MaxSize_EmptyArray) {
  s21::array<int, 0> arr;
  EXPECT_EQ(arr.max_size(), 0);
}

TEST(ArrayTest, MaxSize_NonEmptyArray) {
  s21::array<int, 3> arr{1, 2, 3};
  EXPECT_EQ(arr.max_size(), 3);  // Для s21::array max_size() == size()
}

TEST(ArrayTest, MaxSize_ConstArray) {
  const s21::array<int, 3> arr{1, 2, 3};
  EXPECT_EQ(arr.max_size(), 3);
}

TEST(ArrayTest, MaxSize_UninitializedArray) {
  s21::array<int, 3> arr{};
  EXPECT_EQ(arr.max_size(), 3);
}

TEST(ArrayTest, MaxSize_LargeArray) {
  s21::array<int, 1000> arr{};
  EXPECT_EQ(arr.max_size(), 1000);
}

// Тесты для метода swap
TEST(ArrayTest, Swap_NonEmptyArrays) {
  s21::array<int, 3> arr1{1, 2, 3};
  s21::array<int, 3> arr2{4, 5, 6};
  arr1.swap(arr2);
  EXPECT_EQ(arr1[0], 4);
  EXPECT_EQ(arr1[1], 5);
  EXPECT_EQ(arr1[2], 6);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
}

TEST(ArrayTest, Swap_EmptyArrays) {
  s21::array<int, 0> arr1;
  s21::array<int, 0> arr2;
  arr1.swap(arr2);
  EXPECT_EQ(arr1.size(), 0);
  EXPECT_EQ(arr2.size(), 0);
}

TEST(ArrayTest, Swap_SelfSwap) {
  s21::array<int, 3> arr{1, 2, 3};
  arr.swap(arr);  // Самообмен
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTest, Swap_UninitializedArrays) {
  s21::array<int, 3> arr1{};
  s21::array<int, 3> arr2{};
  arr1.swap(arr2);
  for (std::size_t i = 0; i < arr1.size(); ++i) {
    EXPECT_EQ(arr1[i], 0);
    EXPECT_EQ(arr2[i], 0);
  }
}

TEST(ArrayTest, Swap_DifferentContents) {
  s21::array<int, 3> arr1{1, 2, 3};
  s21::array<int, 3> arr2{};
  arr1.swap(arr2);
  EXPECT_EQ(arr1[0], 0);
  EXPECT_EQ(arr1[1], 0);
  EXPECT_EQ(arr1[2], 0);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
}

TEST(ArrayTest, Swap_LargeArrays) {
  s21::array<int, 1000> arr1;
  s21::array<int, 1000> arr2;
  for (std::size_t i = 0; i < arr1.size(); ++i) {
    arr1[i] = static_cast<int>(i);
    arr2[i] = static_cast<int>(i + 1000);
  }
  arr1.swap(arr2);
  for (std::size_t i = 0; i < arr1.size(); ++i) {
    EXPECT_EQ(arr1[i], static_cast<int>(i + 1000));
    EXPECT_EQ(arr2[i], static_cast<int>(i));
  }
}

// Тесты для метода fill
TEST(ArrayTest, Fill_NonEmptyArray) {
  s21::array<int, 3> arr{1, 2, 3};
  arr.fill(42);
  EXPECT_EQ(arr[0], 42);
  EXPECT_EQ(arr[1], 42);
  EXPECT_EQ(arr[2], 42);
}

TEST(ArrayTest, Fill_EmptyArray) {
  s21::array<int, 0> arr;
  arr.fill(42);  // Ничего не должно произойти
  EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayTest, Fill_UninitializedArray) {
  s21::array<int, 3> arr{};
  arr.fill(42);
  EXPECT_EQ(arr[0], 42);
  EXPECT_EQ(arr[1], 42);
  EXPECT_EQ(arr[2], 42);
}

TEST(ArrayTest, Fill_ZeroValue) {
  s21::array<int, 3> arr{1, 2, 3};
  arr.fill(0);
  EXPECT_EQ(arr[0], 0);
  EXPECT_EQ(arr[1], 0);
  EXPECT_EQ(arr[2], 0);
}

TEST(ArrayTest, Fill_LargeArray) {
  s21::array<int, 1000> arr{};
  arr.fill(42);
  for (std::size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 42);
  }
}