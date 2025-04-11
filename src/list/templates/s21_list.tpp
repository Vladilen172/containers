#include "../include/s21_list.h"

namespace s21 {
template <typename T>
list<T>::list() : head(nullptr), tail(nullptr), length(0) {}

template <typename T>
list<T>::list(size_type n) : list() {
  for (size_type i = 0; i < n; i++) {
    push_back(value_type());
  }
}

template <typename T>
list<T>::list(size_type count, const_reference value) : list() {
  for (size_type i = 0; i < count; i++) {
    push_back(value);
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> initList) : list() {
  for (const auto& elem : initList) {
    push_back(elem);
  }
}

template <typename T>
list<T>::list(const list& other) : head(nullptr), tail(nullptr), length(0) {
  Node<value_type>* tmp = other.head;
  while (tmp) {
    push_back(tmp->data);
    tmp = tmp->next;
  }
}

template <typename T>
list<T>::list(list&& other)
    : head(other.head), tail(other.tail), length(other.length) {
  other.head = other.tail = nullptr;
  other.length = 0;
}

template <typename T>
list<T>::~list() {
  clear();
}

template <typename T>
list<T>& list<T>::operator=(list<T>&& other) noexcept {
  if (this != &other) {
    clear();

    head = other.head;
    tail = other.tail;
    length = other.length;

    other.head = nullptr;
    other.tail = nullptr;
    other.length = 0;
  }
  return *this;
}

template <typename T>
void list<T>::push_back(const_reference value) {
  Node<T>* newNode = new Node<T>(value);
  if (!empty()) {
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
  } else {
    head = tail = newNode;
  }
  length++;
}

template <typename T>
void list<T>::push_front(const_reference value) {
  Node<T>* newNode = new Node<T>(value);
  if (!empty()) {
    head->prev = newNode;
    newNode->next = head;
    head = newNode;
  } else {
    head = tail = newNode;
  }
  length++;
}

template <typename T>
void list<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range("List is empty");
  }

  Node<T>* lastElement = tail;

  if (length == 1) {
    head = nullptr;
    tail = nullptr;
  } else {
    tail = tail->prev;
    tail->next = nullptr;
  }

  delete lastElement;
  length--;
}

template <typename T>
void list<T>::pop_front() {
  if (empty()) {
    throw std::out_of_range("List is empty");
  }

  Node<T>* firstElement = head;
  if (length == 1) {
    head = nullptr;
    tail = nullptr;
  } else {
    head = head->next;
    head->prev = nullptr;
  }

  delete firstElement;
  length--;
}

template <typename T>
typename list<T>::const_reference list<T>::front() const {
  if (empty()) {
    throw std::out_of_range("List is empty");
  }
  return head->data;
}

template <typename T>
typename list<T>::const_reference list<T>::back() const {
  if (empty()) {
    throw std::out_of_range("List is empty");
  }
  return tail->data;
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos, const_reference val) {
  Node<T>* current = pos.getCurrent();
  if (!current && pos != end()) {
    throw std::out_of_range("Invalid iterator position");
  }

  if (pos == begin()) {
    push_front(val);
    return begin();
  } else if (pos == end()) {
    push_back(val);
    return iterator(tail);
  } else {
    Node<T>* newNode = new Node<T>(val);
    newNode->next = current;
    newNode->prev = current->prev;
    if (current->prev) {
      current->prev->next = newNode;
    }
    current->prev = newNode;
    if (current == head) {
      head = newNode;
    }
    length++;

    return iterator(newNode);
  }
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos, size_type n,
                                           const_reference val) {
  if (n == 0) {
    return pos;
  }

  iterator firstInserted = pos;

  Node<T>* current = pos.getCurrent();

  for (size_type i = 0; i < n; i++) {
    Node<T>* newNode = new Node<T>(val);
    if (pos == begin()) {
      newNode->next = head;
      newNode->prev = nullptr;
      if (head) {
        head->prev = newNode;
      }
      head = newNode;
      if (tail == nullptr) {
        tail = newNode;
      }
      if (i == 0) {
        firstInserted = iterator(newNode);
      }
      pos = begin();
    } else if (pos == end()) {
      newNode->next = nullptr;
      newNode->prev = tail;
      if (tail) {
        tail->next = newNode;
      }
      tail = newNode;
      if (head == nullptr) {
        head = newNode;
      }
      if (i == 0) {
        firstInserted = iterator(newNode);
      }
    } else {
      newNode->next = current;
      newNode->prev = current->prev;
      if (current->prev) {
        current->prev->next = newNode;
      }
      current->prev = newNode;
      if (current == head) {
        head = newNode;
      }
      if (i == 0) {
        firstInserted = iterator(newNode);
      }
    }
    length++;
  }

  return firstInserted;
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos, iterator begin,
                                           iterator end) {
  if (begin == end) {
    return pos;
  }

  iterator firstInserted = pos;

  for (iterator it = begin; it != end; ++it) {
    if (it == begin) {
      firstInserted = insert(firstInserted, *it);
    } else {
      firstInserted = insert(++firstInserted, *it);
    }
  }

  return firstInserted;
}

template <typename T>
typename list<T>::iterator list<T>::erase(iterator pos) {
  if (pos == end()) {
    if (empty()) {
      throw std::out_of_range("List is empty");
    }
    pop_back();
    return end();
  } else if (pos == begin()) {
    pop_front();
    return begin();
  } else {
    Node<T>* current = pos.getCurrent();
    Node<T>* prev = current->prev;
    Node<T>* next = current->next;

    prev->next = next;
    if (next != nullptr) {
      next->prev = prev;
    } else {
      tail = prev;
    }

    delete current;
    length--;

    return iterator(next);
  }
}

template <typename T>
void list<T>::clear() {
  while (!empty()) {
    pop_front();
  }
}

template <typename T>
typename list<T>::iterator list<T>::begin() {
  return iterator(head, nullptr);
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  return iterator(nullptr, tail);
}

template <typename T>
typename list<T>::const_iterator list<T>::cbegin() const {
  return const_iterator(head, nullptr);
}

template <typename T>
typename list<T>::const_iterator list<T>::cend() const {
  return const_iterator(nullptr, tail);
}

template <typename T>
bool list<T>::empty() const {
  return head == nullptr;
}

template <typename T>
typename list<T>::size_type list<T>::size() const {
  return length;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(Node<T>) / 2;
}

template <typename T>
void list<T>::resize(size_type n, value_type value) {
  while (length > n) {
    pop_back();
  }

  while (length < n) {
    push_back(value);
  }
}

template <typename T>
void list<T>::swap(list<T>& other) {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(length, other.length);
}

template <typename T>
void list<T>::sort() {
  if (head == nullptr || head->next == nullptr) {
    return;
  }

  Node<T>* current = head;
  value_type* values = new value_type[length];

  for (size_type i = 0; i < length; ++i) {
    values[i] = current->data;
    current = current->next;
  }

  merge_sort(values, 0, length - 1);

  current = head;
  for (size_type i = 0; i < length; ++i) {
    current->data = values[i];
    current = current->next;
  }

  delete[] values;
}

template <typename T>
void list<T>::unique() {
  if (empty() || length == 1) {
    return;
  }

  iterator current = begin();
  iterator next = current;
  ++next;

  while (next != end()) {
    if (*current == *next) {
      next = erase(next);
    } else {
      current = next;
      ++next;
    }
  }
}

template <typename T>
void list<T>::merge(list<T>& other) {
  if (this == &other) {
    return;
  }

  if (empty()) {
    head = other.head;
    tail = other.tail;
    length = other.length;
    other.head = nullptr;
    other.tail = nullptr;
    other.length = 0;
    return;
  }

  if (other.empty()) {
    return;
  }

  iterator current = begin();
  iterator currentOther = other.begin();

  while (current != end() && currentOther != other.end()) {
    if (*currentOther < *current) {
      Node<T>* nodeToInsert = currentOther.getCurrent();
      currentOther++;

      if (nodeToInsert->prev) {
        nodeToInsert->prev->next = nodeToInsert->next;
      } else {
        other.head = nodeToInsert->next;
      }
      if (nodeToInsert->next) {
        nodeToInsert->next->prev = nodeToInsert->prev;
      } else {
        other.tail = nodeToInsert->prev;
      }
      other.length--;

      Node<T>* currentNode = current.getCurrent();
      nodeToInsert->next = currentNode;
      nodeToInsert->prev = currentNode->prev;
      if (currentNode->prev) {
        currentNode->prev->next = nodeToInsert;
      } else {
        head = nodeToInsert;
      }
      currentNode->prev = nodeToInsert;
      length++;
    } else {
      ++current;
    }
  }

  while (!other.empty()) {
    push_back(other.front());
    other.pop_front();
  }
}

template <typename T>
void list<T>::reverse() {
  if (empty() || length == 1) {
    return;
  }

  Node<T>* current = head;
  Node<T>* temp = nullptr;

  while (current != nullptr) {
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;
    current = current->prev;
  }

  temp = head;
  head = tail;
  tail = temp;
}

template <typename T>
void list<T>::splice(const_iterator pos, list& other) {
  if (this == &other) {
    clear();
    return;
  }
  if (other.empty()) {
    return;
  }

  if (empty()) {
    head = other.head;
    tail = other.tail;
    length = other.length;
    other.head = nullptr;
    other.tail = nullptr;
    other.length = 0;
    return;
  }

  Node<value_type>* pos_node = pos.getCurrent();
  if (pos == end()) {
    tail->next = other.head;
    other.head->prev = tail;
    tail = other.tail;
  } else if (pos == begin()) {
    other.tail->next = head;
    head->prev = other.tail;
    head = other.head;
  } else {
    Node<value_type>* prev_node = pos_node->prev;
    prev_node->next = other.head;
    other.head->prev = prev_node;
    other.tail->next = pos_node;
    pos_node->prev = other.tail;
  }

  length += other.length;

  other.head = nullptr;
  other.tail = nullptr;
  other.length = 0;
}

template <typename T>
void list<T>::merge_sort(value_type* array, int left, int right) {
  if (left < right) {
    int middle = left + (right - left) / 2;

    merge_sort(array, left, middle);
    merge_sort(array, middle + 1, right);

    merge(array, left, middle, right);
  }
}

template <typename T>
void list<T>::merge(value_type* array, int left, int middle, int right) {
  int n1 = middle - left + 1;
  int n2 = right - middle;

  value_type* leftArray = new value_type[n1];
  value_type* rightArray = new value_type[n2];

  for (int i = 0; i < n1; ++i) leftArray[i] = array[left + i];
  for (int j = 0; j < n2; ++j) rightArray[j] = array[middle + 1 + j];

  int i = 0;
  int j = 0;
  int k = left;

  while (i < n1 && j < n2) {
    if (leftArray[i] <= rightArray[j]) {
      array[k] = leftArray[i];
      i++;
    } else {
      array[k] = rightArray[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    array[k] = leftArray[i];
    i++;
    k++;
  }

  while (j < n2) {
    array[k] = rightArray[j];
    j++;
    k++;
  }

  delete[] leftArray;
  delete[] rightArray;
}
}  // namespace s21
