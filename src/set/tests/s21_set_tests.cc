#include <gtest/gtest.h>

#include "../include/s21_set.h"

using namespace s21;

TEST(SetTest, DefaultConstructor) {
  set<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

TEST(SetTest, InitializerListConstructor) {
  set<int> s = {1, 2, 3, 4, 5};
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.size(), 5);
}

TEST(SetTest, CopyConstructor) {
  set<int> s1 = {1, 2, 3};
  set<int> s2(s1);
  EXPECT_EQ(s1.size(), s2.size());
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  while (it1 != s1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(SetTest, MoveConstructor) {
  set<int> s1 = {1, 2, 3};
  set<int> s2(std::move(s1));
  EXPECT_TRUE(s1.empty());
  EXPECT_EQ(s2.size(), 3);
}

TEST(SetTest, CopyAssignmentOperator) {
  set<int> s1 = {1, 2, 3};
  set<int> s2;
  s2 = s1;
  EXPECT_EQ(s1.size(), s2.size());
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  while (it1 != s1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(SetTest, MoveAssignmentOperator) {
  set<int> s1 = {1, 2, 3};
  set<int> s2;
  s2 = std::move(s1);
  EXPECT_TRUE(s1.empty());
  EXPECT_EQ(s2.size(), 3);
}

TEST(SetTest, Clear) {
  set<int> s = {1, 2, 3};
  s.clear();
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

TEST(SetTest, Insert) {
  set<int> s;
  auto result = s.insert(1);
  EXPECT_TRUE(result.second);
  EXPECT_EQ(*result.first, 1);
  EXPECT_EQ(s.size(), 1);

  result = s.insert(1);
  EXPECT_FALSE(result.second);
  EXPECT_EQ(*result.first, 1);
  EXPECT_EQ(s.size(), 1);
}

TEST(SetTest, Erase) {
  set<int> s = {1, 2, 3};
  auto it = s.find(2);
  s.erase(it);
  EXPECT_EQ(s.size(), 2);
  EXPECT_FALSE(s.contains(2));
}

TEST(SetTest, Swap) {
  set<int> s1 = {1, 2, 3};
  set<int> s2 = {4, 5};
  s1.swap(s2);
  EXPECT_EQ(s1.size(), 2);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s2.contains(1));
}

TEST(SetTest, Merge) {
  set<int> s1 = {1, 2, 3};
  set<int> s2 = {3, 4, 5};
  s1.merge(s2);
  EXPECT_EQ(s1.size(), 5);
  EXPECT_EQ(s2.size(), 1);
  EXPECT_TRUE(s1.contains(4));
  EXPECT_FALSE(s2.contains(5));
}

TEST(SetTest, Find) {
  set<int> s = {1, 2, 3};
  auto it = s.find(2);
  EXPECT_NE(it, s.end());
  EXPECT_EQ(*it, 2);
  it = s.find(4);
  EXPECT_EQ(it, s.end());
}

TEST(SetTest, Contains) {
  set<int> s = {1, 2, 3};
  EXPECT_TRUE(s.contains(2));
  EXPECT_FALSE(s.contains(4));
}

TEST(SetTest, Iterators) {
  set<int> s = {1, 2, 3};
  auto it = s.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  --it;
  EXPECT_EQ(*it, 1);

  auto cit = s.cbegin();
  EXPECT_EQ(*cit, 1);
  ++cit;
  EXPECT_EQ(*cit, 2);
}

TEST(SetTest, ConstIterators) {
  const set<int> s = {1, 2, 3};
  auto it = s.cbegin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
}

TEST(SetTest, EmptyAndSize) {
  set<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);

  s.insert(1);
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.size(), 1);
}

TEST(SetTest, MaxSize) {
  set<int> s;
  EXPECT_GT(s.max_size(), 0);
}
