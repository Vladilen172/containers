#include <gtest/gtest.h>

#include <map>

#include "../include/s21_map.h"
TEST(MapConstructors, NoParams) {
  s21::map<int, double> map;
  ASSERT_TRUE(map.size() == 0);
}
TEST(MapConstructors, Params) {
  s21::map<int, double> map({10, 0.1});
  ASSERT_TRUE(map.size() == 1);
  ASSERT_DOUBLE_EQ(map[10], 0.1);
}
TEST(MapConstructors, InitializerList) {
  s21::map<int, double> map({{10, 0.1}, {2, 0.3}, {5, 0.4}, {7, 0.8}});
  ASSERT_TRUE(map.size() == 4);
  ASSERT_DOUBLE_EQ(map.at(2), 0.3);
  ASSERT_DOUBLE_EQ(map.at(10), 0.1);
  ASSERT_DOUBLE_EQ(map.at(5), 0.4);
  ASSERT_DOUBLE_EQ(map.at(7), 0.8);
}
TEST(MapConstructors, CopyConstructor) {
  s21::map<int, double> map2({{10, 0.1}, {2, 0.3}, {5, 0.4}, {7, 0.8}});
  s21::map<int, double> map(map2);
  ASSERT_TRUE(map.size() == 4);
  ASSERT_DOUBLE_EQ(map.at(2), 0.3);
  ASSERT_DOUBLE_EQ(map.at(10), 0.1);
  ASSERT_DOUBLE_EQ(map.at(5), 0.4);
  ASSERT_DOUBLE_EQ(map.at(7), 0.8);
}
TEST(MapConstructors, MoveConstructor) {
  s21::map<int, double> map2({{10, 0.1}, {5, 0.4}, {2, 0.3}, {7, 0.8}});
  s21::map<int, double> map = std::move(map2);
  map[20] = 0.1;
  ASSERT_TRUE(map2.size() == 0);
  ASSERT_TRUE(map.size() == 5);
  ASSERT_DOUBLE_EQ(map.at(2), 0.3);
  ASSERT_DOUBLE_EQ(map.at(10), 0.1);
  ASSERT_DOUBLE_EQ(map.at(5), 0.4);
  ASSERT_DOUBLE_EQ(map.at(7), 0.8);
  ASSERT_DOUBLE_EQ(map.at(20), 0.1);
  map2[10] = 0;
  ASSERT_DOUBLE_EQ(map2.at(10), 0);
  ASSERT_TRUE(map2.size() == 1);
}
TEST(MapConstructors, ContainerAsTemplateType) {
  s21::map<int, s21::map<int, double>> map(
      {1, {{10, 0.1}, {5, 0.4}, {2, 0.3}, {7, 0.8}}});
  ASSERT_TRUE(map.size() == 1);
  ASSERT_DOUBLE_EQ(map.at(1).at(10), 0.1);
}
TEST(MapInsert, InsertFunction1) {
  s21::map<int, double> map;
  for (int i = 0; i < 100000; i++) {
    map.insert({i, 0.1 * i});
  }
  ASSERT_TRUE(map.size() == 100000);
}
TEST(MapInsert, InsertFunction2) {
  s21::map<int, double> map;
  for (int i = 0; i < 100000; i++) {
    map[i] = 0.1 * i;
  }
  ASSERT_TRUE(map.size() == 100000);
}
TEST(MapInsert, InsertFunction3) {
  s21::map<int, std::string> map;
  for (int i = 0; i < 100000; i++) {
    std::string str;
    str.append("%lf", 0.1 * i);
    map.insert(i, str);
  }
  ASSERT_FALSE(map.insert(1, "0.1").second);
  ASSERT_TRUE(map.size() == 100000);
}
TEST(MapInsert, InsertFunction4) {
  s21::map<int, double> map;
  for (int i = 0; i < 100000; i++) {
    map.insert(i, 0.1 * i);
  }
  ASSERT_FALSE(map.insert_or_assign(1, 0.2).second);
  ASSERT_TRUE(map.insert_or_assign(100000, 2).second);
  ASSERT_TRUE((*(map.insert_or_assign(100000, 3).first)).second() == 3);
  ASSERT_TRUE(map.size() == 100001);
}
TEST(MapErase, EraseTest1) {
  s21::map<int, double> map;
  for (int i = 0; i < 100000; i++) {
    map.insert(i, 0.1 * i);
  }
  for (int i = 0; i < 100000; i++) {
    s21::map<int, double>::iterator it = map.begin();
    map.erase(it);
  }
  ASSERT_TRUE(map.size() == 0);
}
TEST(MapErase, EraseTest2) {
  s21::map<int, double> map;
  for (int i = 0; i < 100000; i++) {
    map.insert(i, 0.1 * i);
  }
  for (int i = 0; i < 100000; i++) {
    s21::map<int, double>::iterator it = --map.end();
    map.erase(it);
  }
  ASSERT_TRUE(map.size() == 0);
}
TEST(MapIterators, IteratorOperations) {
  s21::map<int, double> map({{1, 1.0}, {2, 2.0}, {3, 3.0}});
  auto it = map.begin();
  ASSERT_DOUBLE_EQ((*it).second(), 1.0);
  ++it;
  ASSERT_DOUBLE_EQ((*it).second(), 2.0);
  --it;
  ASSERT_DOUBLE_EQ((*it).second(), 1.0);
  ++it;
  ++it;
  ASSERT_DOUBLE_EQ((*it).second(), 3.0);
}
TEST(MapIterators, ConstIteratorOperations) {
  const s21::map<int, double> map({{1, 1.0}, {2, 2.0}, {3, 3.0}});
  auto it = map.cbegin();
  ASSERT_DOUBLE_EQ((*it).second(), 1.0);
  ++it;
  ASSERT_DOUBLE_EQ((*it).second(), 2.0);
}
TEST(MapOperations, ExceptionHandling) {
  s21::map<int, double> map;
  ASSERT_THROW(map.at(10), std::out_of_range);
}
TEST(MapOperations, Swap) {
  s21::map<int, double> map1({{1, 1.0}, {2, 2.0}});
  s21::map<int, double> map2({{3, 3.0}, {4, 4.0}});
  map1.swap(map2);
  ASSERT_DOUBLE_EQ(map1.at(3), 3.0);
  ASSERT_DOUBLE_EQ(map2.at(1), 1.0);
}
TEST(MapOperations, Clear) {
  s21::map<int, double> map({{1, 1.0}, {2, 2.0}, {3, 3.0}});
  map.clear();
  ASSERT_TRUE(map.empty());
  ASSERT_TRUE(map.begin() == map.end());
}
TEST(MapOperations, Merge) {
  s21::map<int, double> map1({{1, 1.0}, {2, 2.0}});
  s21::map<int, double> map2({{2, 3.0}, {3, 3.0}});
  map1.merge(map2);
  ASSERT_DOUBLE_EQ(map1.at(1), 1.0);
  ASSERT_DOUBLE_EQ(map1.at(2), 2.0);
  ASSERT_DOUBLE_EQ(map1.at(3), 3.0);
  ASSERT_TRUE(map2.size() == 1);
}
TEST(MapOperations, SubscriptOperator) {
  s21::map<int, double> map;
  map[1] = 1.0;
  ASSERT_DOUBLE_EQ(map[1], 1.0);
  ASSERT_EQ(map.size(), 1);
  map[1] = 2.0;
  ASSERT_DOUBLE_EQ(map[1], 2.0);
  double value = map[2];
  ASSERT_EQ(value, 0.0);
  ASSERT_EQ(map.size(), 2);
}
TEST(MapOperations, AtFunction) {
  s21::map<int, double> map;
  ASSERT_THROW(map.at(1), std::out_of_range);
  map.insert({1, 1.0});
  map.insert({2, 2.0});
  ASSERT_DOUBLE_EQ(map.at(1), 1.0);
  ASSERT_DOUBLE_EQ(map.at(2), 2.0);
}
TEST(MapOperations, DifferentTypes) {
  s21::map<std::string, double> m;
  m["one"] = 1.0;
  m["two"] = 2.0;
  EXPECT_EQ(m["one"], 1.0);
  EXPECT_EQ(m["two"], 2.0);
  EXPECT_THROW(m.at("three"), std::out_of_range);
}
TEST(MapOperations, DefaultConstructors) {
  s21::map<int, double> m;
  std::map<int, double> m2;
  m2[10];
  m[10];
  ASSERT_DOUBLE_EQ(m.at(10), m2.at(10));
}
TEST(MapOperations, Exception) {
  s21::map<int, double> m;
  EXPECT_THROW(*(m.end()), std::out_of_range);
}
TEST(MapOperations, RandomValues) {
  s21::map<int, double> map;
  srand(time(NULL));
  std::set<int> set;
  for (int i = 0; i < 100; i++) {
    int tmp = rand() % 100000;
    set.insert(tmp);
    map.insert(tmp, 0.1 * tmp);
  }
  for (size_t i = 0; i < set.size(); i++) map.erase(map.begin());
  ASSERT_TRUE(map.empty());
}