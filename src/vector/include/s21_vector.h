#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class vector {
 private:
  T *data_;
  size_t size_;
  size_t capacity_;

 public:
  class VectorIterator;
  class VectorConstIterator;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator_pointer = T *;
  using const_iterator_pointer = const T *;
  using iterator = vector<T>::VectorIterator;
  using const_iterator = vector<T>::VectorConstIterator;
  using size_type = size_t;

  /// @brief Конструктор вектора без аргументов, создающий пустой вектор
  /// @tparam T Тип хранимых данных
  vector();

  /// @brief Конструктор вектора с n элементами
  /// @tparam T Тип хранимых данных
  /// @param n Размер вектора
  vector(size_type n);

  /// @brief Конструктор вектора, создающий вектор из списка
  /// @tparam T Тип хранимых данных
  /// @param items Список элементов
  vector(std::initializer_list<value_type> const &items);

  /// @brief Деструктор вектора
  /// @tparam T Тип хранимых данных
  ~vector();

  /// @brief Создает новый вектор, перемещая содержимое из другого вектора
  /// @tparam T Тип хранимых данных
  /// @param other Другой вектора
  vector(vector &&other);

  /// @brief Копирует в новый вектор другой
  /// @tparam T Тип хранимых данных
  /// @param other Другой вектор
  vector(vector &other);

  /// @brief Оператор присваения другого вектора текущему
  /// @param other Другой векитор
  /// @return Объект класса
  vector<T> &operator=(vector &&other) {
    if (this != &other.data_) {
      delete[] data_;
      capacity_ = other.capacity_;
      size_ = other.size_;
      data_ = new T[capacity_];

      for (size_t i = 0; i < size_; i++) {
        data_[i] = other.data_[i];
      }
    }
    return *this;
  }

  /// @brief Возвращает элемент вектора на позиции index
  /// @tparam T Тип хранимых данных
  /// @param index Номер элемента
  /// @return Элемент вектора
  reference at(size_t index);

  /// @brief Оператор обращения к элемету по индексу
  /// @param index Номер элемента
  /// @return Элемент вектора
  reference operator[](size_t index) { return data_[index]; }

  /// @brief Возвращает первый элемент вектора
  /// @tparam T Тип хранимых данных
  /// @return Первый элемент вектора
  const_reference front();

  /// @brief Возвращает последний элемент вектора
  /// @tparam T Тип хранимых данных
  /// @return Последний элемент вектора
  const_reference back();

  /// @brief Возвращает ссылку на массив вектора
  /// @tparam T Тип хранимых данных
  /// @return Ссылка на массив вектора
  iterator_pointer data();

  /// @brief Возвращает итератор, указывающий на начало вектора
  /// @tparam T Тип хранимых данных
  /// @return Итератор, указывающий на начало вектора
  iterator begin();

  /// @brief Возвращает итератор, указывающий на конец вектора
  /// @tparam T Тип хранимых данных
  /// @return Итератор, указывающий на конец вектора
  iterator end();

  /// @brief Проверяет если вектор пуст
  /// @tparam T Тип хранимых данных
  /// @return Истина, если вектор пуст, ложь иначе
  bool empty();

  /// @brief Возвращает размер вектора
  /// @tparam T Тип хранимых данных
  /// @return Размер вектора
  size_type size();

  /// @brief Возвращает максимально возможный размер вектора
  /// @tparam T Тип хранимых данных
  /// @return максимально возможный размер вектора
  size_type max_size();

  /// @brief Выделяет память размером size и копирует элементы текущего вектора
  /// в новый вектор
  /// @param size
  void reserve(size_type size);

  /// @brief Возвращает текущую емкость вектора
  /// @return Текущая емкость вектора
  size_type capacity();

  /// @brief Уменьшает выделенную память до размера вектора
  void shrink_to_fit();

  /// @brief Очищает осдердимое вектора
  void clear();

  /// @brief Вставить лемент на заданную позицию
  /// @param pos Итератор, указывающий на позицию, куда надо вставить новое
  /// Элемент
  /// @param value Новое элемент
  /// @return Итератор, указывающий на вставленнный элемент
  iterator insert(iterator pos, const_reference value);

  /// @brief Убирает элемент на позиции
  /// @param pos Итератор, указывающий на позицию
  void erase(iterator pos);

  /// @brief Добавляет элемент в конец вектора
  /// @param value Добавляемый элемент
  void push_back(const_reference value);

  /// @brief Убирает элемент в конце вектора
  void pop_back();

  /// @brief Меняет содержимое текущего вектора
  /// @param other Другой вектор
  void swap(vector &other);
};
}  // namespace s21
#include "../templates/s21_vector.tpp"
#include "vector_iterator.h"
#endif
