// #include "../include/s21_vector.h"

namespace s21 {

template <typename T>
vector<T>::vector() : data_(nullptr), size_(0), capacity_(0){};

template <typename T>
vector<T>::vector(size_type n) {
  if (n >= max_size()) {
    throw std::length_error("Vector has reached maximum size");
  }
  size_ = n;
  capacity_ = n + 1;
  data_ = new T[capacity_];
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const& items) {
  if (items.size() >= max_size()) {
    throw std::length_error("Vector has reached maximum size");
  }
  size_ = items.size();

  capacity_ = size_ + 1;
  data_ = new value_type[capacity_];
  std::copy(items.begin(), items.end(), data_);
}

template <typename T>
vector<T>::~vector() {
  delete[] data_;
  size_ = 0;
  capacity_ = 0;
  data_ = nullptr;
}

template <typename T>
vector<T>::vector(vector&& other) {
  data_ = other.data_;
  size_ = other.size_;
  capacity_ = other.capacity_;
  other.data_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

template <typename T>
vector<T>::vector(vector& other) : data_(nullptr), size_(0), capacity_(0) {
  data_ = new T[other.capacity_];
  for (size_t i = 0; i < other.size_; i++) {
    data_[i] = other.data_[i];
  }

  size_ = other.size_;
  capacity_ = other.capacity_;
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_t index) {
  if (index >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return data_[index];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() {
  if (this->empty()) {
    throw std::out_of_range("Vector is empty");
  }
  return data_[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() {
  if (this->empty()) {
    throw std::out_of_range("Vector is empty");
  }
  return data_[size_ - 1];
}

template <typename T>
typename vector<T>::iterator_pointer vector<T>::data() {
  if (!data_) {
    throw std::runtime_error("Vector pointer is null");
  }
  return data_;
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return iterator(data_);
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return iterator(data_ + size_);
}

template <typename T>
bool vector<T>::empty() {
  if (data_ == nullptr) {
    return true;
  }

  return size_ == 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() {
  return size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() {
  return std::numeric_limits<std::size_t>::max();
  ;
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size < capacity_) return;

  if (size > max_size()) {
    std::out_of_range("Too large size for a new capacity");
  }

  T* temp = new T[size];
  for (size_t i = 0; i < size_; i++) {
    temp[i] = data_[i];
  }
  delete[] data_;
  data_ = temp;
  capacity_ = size;
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() {
  return capacity_;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (size_ == 0) {
    delete[] data_;
    data_ = nullptr;
    capacity_ = 0;
    return;
  }
  T* temp = new T[size_];
  for (size_t i = 0; i < size_; i++) {
    temp[i] = data_[i];
  }
  delete[] data_;
  data_ = temp;
  capacity_ = size_;
}

template <typename T>
void vector<T>::clear() {
  for (size_t i = 0; i < size_; i++) {
    data_[i].~T();
  }
  size_ = 0;
  reserve(2);
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  auto beg = begin();
  auto en = end();
  if (pos - beg < 0 || en - pos < 0) {
    throw std::out_of_range("Position out of bounds");
  }
  this->push_back(this->back());
  VectorIterator iter = beg + size_ - 2;
  for (; iter - pos >= 0; iter--) {
    *(iter + 1) = *(iter);
  }
  *(pos) = value;
  size_++;
  return iter;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  auto beg = begin();
  auto en = end();
  if (pos - beg < 0 || en - pos < 0) {
    throw std::out_of_range("Position out of bounds");
  }

  while (pos - (data_ + size_ - 2) != 0) {
    *(pos) = *(pos + 1);
    pos++;
  }
  size_--;
  pop_back();
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (data_ == nullptr) {
    data_ = new T[2];
    size_ = 0;
    capacity_ = 2;
  }

  if (size_ == capacity_) {
    size_t cap = capacity_ * 2;
    reserve(cap);
  }

  data_[++size_ - 1] = value;
}

template <typename T>
void vector<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range("No elements left to pop");
  }
  data_[size_ - 1].~T();

  size_--;

  reserve(size_ + 1);
}

template <typename T>
void vector<T>::swap(vector& other) {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}
}  // namespace s21
