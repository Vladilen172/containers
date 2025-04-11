#include "../include/s21_list.h"

namespace s21 {
template <typename T>
Node<T>::Node() : data(), next(nullptr), prev(nullptr) {}

template <typename T>
Node<T>::Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}

}  // namespace s21