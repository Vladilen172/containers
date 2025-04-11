
#include <gtest/gtest.h>

#include "../include/s21_vector.h"
TEST(Vector, Constructors) {
  s21::vector<int> v;
  EXPECT_TRUE(v.size() == 0);

  s21::vector<int> v1(5);
  EXPECT_TRUE(v1.size() == 5);

  s21::vector<int> v2(v1);
  EXPECT_TRUE(v2.size() == 5);

  s21::vector<int> v3 = std::move(v2);
  EXPECT_TRUE(v3.size() == 5);
  s21::vector<int> v4({1, 2, 3, 4, 5});
  EXPECT_TRUE(v4.size() == 5 && v4.front() == 1 && v4.back() == 5);

  s21::vector<int> v5 = v4;
  EXPECT_TRUE(v5.size() == v4.size());
}

TEST(Vector, ElementAccess) {
  s21::vector<int> v({1, 2, 3, 4, 5});
  EXPECT_TRUE(v.at(0) == 1 && v.at(3) == 4);
  EXPECT_TRUE(v[1] == 2 && v[4] == 5);
  EXPECT_TRUE(v.front() == 1 && v.back() == 5);
  EXPECT_TRUE(*(v.data() + 1) == 2);
  s21::vector<int> v3;
  EXPECT_THROW(v3.data(), std::runtime_error);
  EXPECT_THROW(v.at(7), std::out_of_range);
  // EXPECT_THROW(v[7], std::out_of_range);

  s21::vector<int> v1;
  EXPECT_THROW(v1.front(), std::out_of_range);
  EXPECT_THROW(v1.back(), std::out_of_range);
}

TEST(Vector, Iterator) {
  s21::vector<int> v({1, 2, 3, 4, 5});
  auto it = v.begin();
  EXPECT_TRUE(*it == 1);
  auto it1 = v.end();
  EXPECT_TRUE(*(it1 - 1) == 5);
  EXPECT_TRUE(*(++it) == 2);
  EXPECT_TRUE(*(it++) == 2 && *it == 3);
  EXPECT_TRUE(*(--it) == 2);
  EXPECT_TRUE(*(it--) == 2 && *it == 1);

  auto it2 = v.begin();
  EXPECT_TRUE(it2 == it);

  EXPECT_TRUE(it2 != it1);

  EXPECT_TRUE(it2 + 5 == it1);
  EXPECT_TRUE(it2 == it1 - 5);
  EXPECT_TRUE(it1 - it2 == 5);
}

TEST(Vector, Capacity) {
  s21::vector<int> v({1, 2, 3, 4, 5});
  EXPECT_FALSE(v.empty());
  s21::vector<int> v1;
  EXPECT_TRUE(v1.empty());
  EXPECT_TRUE(v.size() == 5);
  v.reserve(20);
  EXPECT_TRUE(v.capacity() == 20);
  v.shrink_to_fit();
  EXPECT_TRUE(v.capacity() == 5);
}

TEST(Vector, Modifiers) {
  s21::vector<int> v({1, 2, 3, 4, 5});
  v.clear();
  EXPECT_TRUE(v.size() == 0);

  // std::initializer_list list = {1, 2, 3, 10, 4, 5};
  s21::vector<int> v1({1, 2, 3, 4, 5});
  auto it = v1.begin();
  v1.insert(it + 3, 10);
  EXPECT_TRUE(v1[3] == 10);
  v1.erase(it + 3);
  EXPECT_TRUE(v1[3] == 4);
  v1.push_back(6);
  EXPECT_TRUE(v1[5] == 6 && v1.size() == 6);
  v1.pop_back();
  EXPECT_TRUE(v1.size() == 5);
  v1.swap(v);
  EXPECT_TRUE(v1.size() == 0 && v.size() == 5);
  s21::vector<int> v2;
  EXPECT_THROW(v1.insert(it + 10, 10), std::out_of_range);
  EXPECT_THROW(v1.erase(it + 10), std::out_of_range);
  EXPECT_THROW(v2.pop_back(), std::out_of_range);
}