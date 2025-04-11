#include <iostream>

#include "../include/s21_map.h"
namespace s21 {
template <typename T, typename K>
map<T, K>::pair::pair() : val1(T()), val2(K()){};
template <typename T, typename K>
map<T, K>::pair::pair(const T v1, K v2) : val1(v1), val2(v2){};
template <typename T, typename K>
map<T, K>::pair::pair(const map<T, K>::pair& other)
    : val1(other.val1), val2(other.val2){};
template <typename T, typename K>
map<T, K>::pair::pair(pair&& other) : pair(other) {
  other.val1 = T();
  other.val2 = K();
}
template <typename T, typename K>
typename map<T, K>::pair& map<T, K>::pair::operator=(
    const map<T, K>::pair& other) {
  if (this != &other) {
    val1 = other.val1;
    val2 = other.val2;
  }
  return *this;
}
template <typename T, typename K>
typename map<T, K>::pair& map<T, K>::pair::operator=(map<T, K>::pair&& other) {
  if (this != &other) {
    val1 = std::move(other.val1);
    val2 = std::move(other.val2);
  }
  return *this;
}
template <typename T, typename K>
map<T, K>::pair::pair(std::initializer_list<std::pair<T, K>> init) {
  if (init.size() != 1) {
    throw std::invalid_argument(
        "pair initializer must contain exactly one element");
  }
  auto it = init.begin();
  val1 = it->first;
  val2 = it->second;
}
template <typename T, typename K>
bool map<T, K>::pair::operator<(const map<T, K>::pair& other) {
  return (val1 < other.val1);
}
template <typename T, typename K>
bool map<T, K>::pair::operator>(const map<T, K>::pair& other) {
  return (val1 > other.val1);
}
template <typename T, typename K>
bool map<T, K>::pair::operator==(const map<T, K>::pair& other) const {
  return (val1 == other.val1);
}
template <typename T, typename K>
const T& map<T, K>::pair::first() const {
  return val1;
}
template <typename T, typename K>
const K& map<T, K>::pair::second() const {
  return val2;
}
template <typename T, typename K>
K& map<T, K>::pair::second() {
  return val2;
}
}  // namespace s21