#include "../include/s21_list.h"

namespace s21 {
template <typename T>
ListConstIterator<T>::ListConstIterator() : current(nullptr), prev(nullptr) {}

template <typename T>
ListConstIterator<T>::ListConstIterator(Node<T>* ptr, Node<T>* prevPtr)
    : current(ptr), prev(prevPtr) {
  if (ptr) {
    prev = ptr->prev;
  }
}

template <typename T>
ListConstIterator<T>::ListConstIterator(const ListConstIterator& other)
    : current(other.current), prev(other.prev) {}

template <typename T>
ListConstIterator<T>::ListConstIterator(const ListIterator<T>& other)
    : current(other.getCurrent()),
      prev(other.getCurrent() ? other.getCurrent()->prev : nullptr) {}

template <typename T>
ListConstIterator<T>& ListConstIterator<T>::operator=(
    const ListConstIterator& other) {
  if (this != &other) {
    current = other.current;
    prev = other.prev;
  }
  return *this;
}

template <typename T>
const T& ListConstIterator<T>::operator*() const {
  if (!current) {
    if (!prev) {
      throw std::out_of_range("Iterator is invalid");
    }
    return prev->data;
  }
  return current->data;
}

template <typename T>
const T* ListConstIterator<T>::operator->() const {
  if (!current) {
    throw std::out_of_range("Iterator is invalid");
  }
  return &current->data;
}

template <typename T>
ListConstIterator<T>& ListConstIterator<T>::operator++() {
  if (!current) {
    throw std::out_of_range("Cannot increment end() iterator");
  }
  prev = current;
  current = current->next;
  return *this;
}

template <typename T>
ListConstIterator<T> ListConstIterator<T>::operator++(int) {
  ListConstIterator temp = *this;
  ++(*this);
  return temp;
}

template <typename T>
ListConstIterator<T>& ListConstIterator<T>::operator--() {
  if (!current) {
    if (!prev) {
      throw std::out_of_range("Cannot decrement end() iterator of empty list");
    }
    current = prev;
    prev = current->prev;
    return *this;
  }

  Node<T>* old_current = current;
  current = current->prev;
  if (current) {
    prev = current->prev;
  } else {
    prev = old_current;
  }
  return *this;
}

template <typename T>
ListConstIterator<T> ListConstIterator<T>::operator--(int) {
  ListConstIterator temp = *this;
  --(*this);
  return temp;
}

template <typename T>
bool ListConstIterator<T>::operator==(const ListConstIterator& other) const {
  return current == other.current;
}

template <typename T>
bool ListConstIterator<T>::operator!=(const ListConstIterator& other) const {
  return current != other.current;
}

template <typename T>
Node<T>* ListConstIterator<T>::getCurrent() const {
  return current;
}
}  // namespace s21