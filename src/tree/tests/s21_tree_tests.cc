#include <gtest/gtest.h>

#include <string>

#include "../include/s21_tree.h"
TEST(TreeTest, EmptyTree) {
  s21::Tree<int> tree;
  EXPECT_TRUE(tree.empty());
  EXPECT_EQ(tree.size(), 0);
  EXPECT_EQ(tree.begin(), tree.end());
}

TEST(TreeTest, BasicInsert) {
  s21::Tree<int> tree;
  tree.push(5);
  EXPECT_FALSE(tree.empty());
  EXPECT_EQ(tree.size(), 1);
  EXPECT_EQ(*tree.begin(), 5);
}

TEST(TreeTest, MultipleInsert) {
  s21::Tree<int> tree;
  tree.push(5);
  tree.push(2);
  tree.push(8);
  tree.push(3);
  tree.push(9);
  EXPECT_EQ(tree.size(), 5);
  auto it = tree.begin();
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 5);
  EXPECT_EQ(*it++, 8);
  EXPECT_EQ(*it++, 9);
}

TEST(TreeTest, StringInsert) {
  s21::Tree<std::string> str_tree;
  str_tree.push("apple");
  str_tree.push("banana");
  str_tree.push("cherry");
  auto it = str_tree.begin();
  EXPECT_EQ(*it++, "apple");
  EXPECT_EQ(*it++, "banana");
  EXPECT_EQ(*it++, "cherry");
}

TEST(TreeTest, Erase) {
  s21::Tree<int> tree;
  tree.push(5);
  tree.push(2);
  tree.push(8);
  tree.erase(2);
  EXPECT_EQ(tree.size(), 2);
  auto it = tree.begin();
  EXPECT_EQ(*it++, 5);
  EXPECT_EQ(*it++, 8);
}

TEST(TreeTest, Contains) {
  s21::Tree<int> tree;
  tree.push(5);
  tree.push(2);
  tree.push(8);
  EXPECT_TRUE(tree.contains(5));
  EXPECT_TRUE(tree.contains(2));
  EXPECT_FALSE(tree.contains(3));
}

TEST(TreeTest, Iterator) {
  s21::Tree<int> tree;
  tree.push(5);
  tree.push(2);
  tree.push(8);
  auto it = tree.begin();
  EXPECT_EQ(*it++, 2);
  ++it;
  EXPECT_EQ(*it++, 8);
  EXPECT_EQ(it, tree.end());
}

TEST(TreeTest, ConstIterator) {
  s21::Tree<int> tree;
  tree.push(5);
  tree.push(2);
  tree.push(8);
  auto it = tree.cbegin();
  EXPECT_EQ(*it++, 2);
  ++it;
  EXPECT_EQ(*it++, 8);
  EXPECT_EQ(it, tree.cend());
}

TEST(TreeTest, Search) {
  s21::Tree<int> tree;
  tree.push(5);
  tree.push(2);
  tree.push(8);
  auto it = tree.search(2);
  EXPECT_NE(it, tree.end());
  EXPECT_EQ(*it, 2);
}

TEST(TreeTest, CopyConstructor) {
  s21::Tree<int> tree;
  tree.push(5);
  tree.push(2);
  tree.push(8);
  s21::Tree<int> copy_tree(tree);
  EXPECT_EQ(tree.size(), copy_tree.size());
  auto it1 = tree.begin();
  auto it2 = copy_tree.begin();
  while (it1 != tree.end()) {
    EXPECT_EQ(*it1++, *it2++);
  }
}

TEST(TreeTest, MoveConstructor) {
  s21::Tree<int> tree;
  tree.push(5);
  tree.push(2);
  tree.push(8);
  s21::Tree<int> moved_tree = std::move(tree);
  EXPECT_TRUE(tree.empty());
  EXPECT_EQ(moved_tree.size(), 3);
  auto it = moved_tree.begin();
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 5);
  EXPECT_EQ(*it++, 8);
}

TEST(TreeTest, Assignment) {
  s21::Tree<int> tree;
  tree.push(5);
  tree.push(2);
  tree.push(8);
  s21::Tree<int> other;
  other = tree;
  EXPECT_EQ(tree.size(), other.size());
  auto it1 = tree.begin();
  auto it2 = other.begin();
  while (it1 != tree.end()) {
    EXPECT_EQ(*it1++, *it2++);
  }
}

TEST(TreeTest, MoveAssignment) {
  s21::Tree<int> tree;
  tree.push(5);
  tree.push(2);
  tree.push(8);
  s21::Tree<int> other;
  other = std::move(tree);
  EXPECT_TRUE(tree.empty());
  EXPECT_EQ(other.size(), 3);
  auto it = other.begin();
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 5);
  EXPECT_EQ(*it++, 8);
}
TEST(TreeTest, BalanceTest) {
  s21::Tree<int> tree;
  tree.push(10);
  tree.push(20);
  tree.push(30);
  tree.push(40);
  tree.push(50);

  auto it = tree.begin();
  EXPECT_EQ(*it++, 10);
  EXPECT_EQ(*it++, 20);
  EXPECT_EQ(*it++, 30);
  EXPECT_EQ(*it++, 40);
  EXPECT_EQ(*it++, 50);
}
TEST(TreeTest, EraseRoot) {
  s21::Tree<int> tree;
  tree.push(5);
  tree.push(2);
  tree.push(8);
  tree.erase(5);
  EXPECT_EQ(tree.size(), 2);
  auto it = tree.begin();
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 8);
}

TEST(TreeTest, EraseLeaf) {
  s21::Tree<int> tree;
  tree.push(5);
  tree.push(2);
  tree.push(8);
  tree.erase(2);
  EXPECT_EQ(tree.size(), 2);
  auto it = tree.begin();
  EXPECT_EQ(*it++, 5);
  EXPECT_EQ(*it++, 8);
}

TEST(TreeTest, EraseInternal) {
  s21::Tree<int> tree;
  tree.push(5);
  tree.push(2);
  tree.push(8);
  tree.push(3);
  tree.push(7);
  tree.erase(5);
  EXPECT_EQ(tree.size(), 4);
  auto it = tree.begin();
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 7);
  EXPECT_EQ(*it++, 8);
}
TEST(TreeTest, NoConsecutiveRedsTest) {
  s21::Tree<int> tree;
  tree.push(10);
  tree.push(5);
  tree.push(15);
  tree.push(2);
  tree.push(7);

  auto it = tree.begin();
  int prev_value = *it++;
  while (it != tree.end()) {
    int curr_value = *it++;
    EXPECT_GT(curr_value, prev_value);
    prev_value = curr_value;
  }
}
TEST(TreeTest, IteratorRangeTest) {
  s21::Tree<int> tree;
  tree.push(5);
  tree.push(2);
  tree.push(8);

  int sum = 0;
  for (auto it = tree.begin(); it != tree.end(); ++it) {
    sum += *it;
  }
  EXPECT_EQ(sum, 15);
}
TEST(TreeTest, SearchNotFoundTest) {
  s21::Tree<int> tree;
  tree.push(5);
  auto it = tree.search(10);
  EXPECT_EQ(it, tree.end());
}

// Тесты смешанных операций
TEST(TreeTest, MixedOperationsTest) {
  s21::Tree<int> tree;
  tree.push(5);
  tree.push(2);
  tree.push(8);
  tree.erase(2);
  tree.push(3);
  tree.push(7);

  EXPECT_EQ(tree.size(), 4);
  auto it = tree.begin();
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 5);
  EXPECT_EQ(*it++, 7);
  EXPECT_EQ(*it++, 8);
}
TEST(TreeTest, LargeNumbersTest) {
  s21::Tree<int> tree;
  tree.push(1000000);
  tree.push(500000);
  tree.push(1500000);
  tree.push(250000);
  tree.push(750000);

  auto it = tree.begin();
  EXPECT_EQ(*it++, 250000);
  EXPECT_EQ(*it++, 500000);
  EXPECT_EQ(*it++, 750000);
  EXPECT_EQ(*it++, 1000000);
  EXPECT_EQ(*it++, 1500000);
}
// Тесты сложных сценариев удаления
TEST(TreeTest, ComplexEraseTest) {
  s21::Tree<int> tree;
  tree.push(10);
  tree.push(5);
  tree.push(15);
  tree.push(2);
  tree.push(7);
  tree.push(12);
  tree.push(17);

  tree.erase(5);  // Удаление узла с двумя детьми
  EXPECT_EQ(tree.size(), 6);
  auto it = tree.begin();
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 7);
  EXPECT_EQ(*it++, 10);
  EXPECT_EQ(*it++, 12);
  EXPECT_EQ(*it++, 15);
  EXPECT_EQ(*it++, 17);
}

TEST(TreeTest, RootEraseWithTwoChildrenTest) {
  s21::Tree<int> tree;
  tree.push(10);
  tree.push(5);
  tree.push(15);
  tree.push(2);
  tree.push(7);
  tree.push(12);
  tree.push(17);

  tree.erase(10);
  EXPECT_EQ(tree.size(), 6);
  auto it = tree.begin();
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 5);
  EXPECT_EQ(*it++, 7);
  EXPECT_EQ(*it++, 12);
  EXPECT_EQ(*it++, 15);
  EXPECT_EQ(*it++, 17);
}

TEST(TreeTest, LeftHeavyTreeTest) {
  s21::Tree<int> tree;
  tree.push(10);
  tree.push(5);
  tree.push(2);
  tree.push(1);
  tree.push(3);
  tree.push(4);

  auto it = tree.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 4);
  EXPECT_EQ(*it++, 5);
  EXPECT_EQ(*it++, 10);
}

TEST(TreeTest, RightHeavyTreeTest) {
  s21::Tree<int> tree;
  tree.push(1);
  tree.push(2);
  tree.push(3);
  tree.push(4);
  tree.push(5);
  tree.push(10);

  auto it = tree.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 4);
  EXPECT_EQ(*it++, 5);
  EXPECT_EQ(*it++, 10);
}

// Тесты с отрицательными числами
TEST(TreeTest, NegativeNumbersTest) {
  s21::Tree<int> tree;
  tree.push(-10);
  tree.push(-5);
  tree.push(0);
  tree.push(5);
  tree.push(10);

  auto it = tree.begin();
  EXPECT_EQ(*it++, -10);
  EXPECT_EQ(*it++, -5);
  EXPECT_EQ(*it++, 0);
  EXPECT_EQ(*it++, 5);
  EXPECT_EQ(*it++, 10);
}

TEST(TreeTest, MixedSignsTest) {
  s21::Tree<int> tree;
  tree.push(-10);
  tree.push(10);
  tree.push(-5);
  tree.push(5);
  tree.push(0);

  auto it = tree.begin();
  EXPECT_EQ(*it++, -10);
  EXPECT_EQ(*it++, -5);
  EXPECT_EQ(*it++, 0);
  EXPECT_EQ(*it++, 5);
  EXPECT_EQ(*it++, 10);
}

// Тесты с дубликатами
TEST(TreeTest, DuplicateInsertTest) {
  s21::Tree<int> tree;
  tree.push(5);
  tree.push(5);
  tree.push(5);
  EXPECT_EQ(tree.size(), 1);
  auto it = tree.begin();
  EXPECT_EQ(*it++, 5);
}

TEST(TreeTest, NearDuplicatesTest) {
  s21::Tree<int> tree;
  tree.push(5);
  tree.push(4);
  tree.push(6);
  tree.push(4);
  tree.push(6);

  EXPECT_EQ(tree.size(), 3);
  auto it = tree.begin();
  EXPECT_EQ(*it++, 4);
  EXPECT_EQ(*it++, 5);
  EXPECT_EQ(*it++, 6);
}

// Тесты с большими наборами данных
TEST(TreeTest, LargeDatasetTest) {
  s21::Tree<int> tree;
  for (int i = 0; i < 1000; i++) {
    tree.push(i);
  }
  EXPECT_EQ(tree.size(), 1000);

  auto it = tree.begin();
  for (int i = 0; i < 1000; i++) {
    EXPECT_EQ(*it++, i);
  }
}

TEST(TreeTest, ReverseOrderTest) {
  s21::Tree<int> tree;
  for (int i = 999; i >= 0; i--) {
    tree.push(i);
  }
  EXPECT_EQ(tree.size(), 1000);

  auto it = tree.begin();
  for (int i = 0; i < 1000; i++) {
    EXPECT_EQ(*it++, i);
  }
}
// Тесты с пользовательским типом
struct Person {
  std::string name;
  int age;

  bool operator<(const Person& other) const { return age < other.age; }
  bool operator>(const Person& other) const { return age > other.age; }
};

TEST(TreeTest, CustomTypeTest) {
  s21::Tree<Person> person_tree;
  person_tree.push({"John", 25});
  person_tree.push({"Alice", 30});
  person_tree.push({"Bob", 20});

  auto it = person_tree.begin();
  EXPECT_EQ(it->age, 20);
  ++it;
  EXPECT_EQ(it->age, 25);
  ++it;
  EXPECT_EQ(it->age, 30);
}