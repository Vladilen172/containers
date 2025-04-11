#include "../include/s21_list.h"

namespace s21 {
template <typename T>
ListIterator<T>::ListIterator() : current(nullptr), prev(nullptr) {}

template <typename T>
ListIterator<T>::ListIterator(Node<T>* ptr, Node<T>* prevPtr)
    : current(ptr), prev(prevPtr) {
  if (ptr) {
    prev = ptr->prev;
  }
}

template <typename T>
ListIterator<T>::ListIterator(const ListIterator& other)
    : current(other.current), prev(other.prev) {}

template <typename T>
Node<T>* ListIterator<T>::getCurrent() const {
  return current;
}

template <typename T>
ListIterator<T>& ListIterator<T>::operator=(const ListIterator& other) {
  if (this != &other) {
    current = other.current;
    prev = other.prev;
  }
  return *this;
}

template <typename T>
T& ListIterator<T>::operator*() const {
  if (!current) {
    if (!prev) {
      throw std::out_of_range("Iterator is invalid");
    }
    return prev->data;
  }
  return current->data;
}

template <typename T>
T* ListIterator<T>::operator->() const {
  if (!current) {
    throw std::out_of_range("Iterator is invalid");
  }
  return &current->data;
}

template <typename T>
ListIterator<T>& ListIterator<T>::operator++() {
  if (!current) {
    throw std::out_of_range("Cannot increment end() iterator");
  }
  prev = current;
  current = current->next;
  return *this;
}

template <typename T>
ListIterator<T> ListIterator<T>::operator++(int) {
  ListIterator temp = *this;
  ++(*this);
  return temp;
}

template <typename T>
ListIterator<T>& ListIterator<T>::operator--() {
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
ListIterator<T> ListIterator<T>::operator--(int) {
  ListIterator temp = *this;
  --(*this);
  return temp;
}

template <typename T>
bool ListIterator<T>::operator!=(const ListIterator& other) const {
  return current != other.current;
}

template <typename T>
bool ListIterator<T>::operator==(const ListIterator& other) const {
  return current == other.current;
}

}  // namespace s21