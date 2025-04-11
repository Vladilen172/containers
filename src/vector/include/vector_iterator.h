#ifndef VECTOR_ITERATOR_H
#define VECTOR_ITERATOR_H

#include "s21_vector.h"

namespace s21 {

template <typename T>
class vector<T>::VectorIterator {
 public:
  /// @brief Дефолтный конструктор итератора
  VectorIterator();
  /// @brief Конструктор итератора по ссылке
  /// @param ptr Ссылка на элемент
  VectorIterator(iterator_pointer ptr);

  /// @brief Оператор разыменовывания
  /// @return Элемент вектора, куда указывает итератор
  reference operator*();

  /// @brief Оператор постинкремента
  /// @param
  /// @return Итератор до инкрементирования
  VectorIterator operator++(int);

  /// @brief Оператор постдекремента
  /// @param
  /// @return Итератор до декрментирования
  VectorIterator operator--(int);

  /// @brief Оператор инкремента
  /// @return Итератор после инкрементирования
  VectorIterator& operator++();

  /// @brief Оператор декремента
  /// @return Итератор после декрементирования
  VectorIterator& operator--();

  /// @brief Оператор тождественности между двумя векторами
  /// @param other Другой вектор
  /// @return Истина, если векторы равны, ложь иначе
  bool operator==(const VectorIterator& other) const;

  /// @brief Оператор неравенства между двумя векторами
  /// @param other Другой вектор
  /// @return Истина, если вектора неравны, ложь иначе
  bool operator!=(const VectorIterator& other) const;

  /// @brief Оператор сложения итератора и числа
  /// @param n Насколько элементов итератор перешагнет
  /// @return Новый итератор, указывающий на элемент через n позиций после
  /// текущего
  VectorIterator operator+(int n) const;

  /// @brief Оператор вычитания числа из итератора
  /// @param n Насколько элементов итератор перешагнет
  /// @return Новый итератор, указывающий на элемент через n позиций до текущего
  VectorIterator operator-(int n) const;
  /// @brief Оператор вычитания итератора из итератора
  /// @param other другой итератор
  /// @return Разница в позициях между двуимя итераторами
  ptrdiff_t operator-(const VectorIterator& other) const;

 private:
  iterator_pointer ptr_;
};

template <typename T>
class vector<T>::VectorConstIterator {
 public:
  /// @brief Дефолтный конструктор итератора
  VectorConstIterator();

  /// @brief Конструктор итератора по ссылке
  /// @param ptr Ссылка на элемент
  VectorConstIterator(const_iterator_pointer ptr);

  /// @brief Оператор разыменовывания
  /// @return Элемент вектора, куда указывает итератор
  reference operator*() const;

  /// @brief Оператор постинкремента
  /// @param
  /// @return Итератор до инкрементирования
  VectorConstIterator operator++(int);

  /// @brief Оператор постдекремента
  /// @param
  /// @return Итератор до декрментирования
  VectorConstIterator operator--(int);

  /// @brief Оператор инкремента
  /// @return Итератор после инкрементирования
  VectorConstIterator& operator++();

  /// @brief Оператор декремента
  /// @return Итератор после декрементирования
  VectorConstIterator& operator--();

  /// @brief Оператор тождественности между двумя векторами
  /// @param other Другой вектор
  /// @return Истина, если векторы равны, ложь иначе
  bool operator==(const VectorConstIterator& other) const;

  /// @brief Оператор неравенства между двумя векторами
  /// @param other Другой вектор
  /// @return Истина, если вектора неравны, ложь иначе
  bool operator!=(const VectorConstIterator& other) const;

  /// @brief Оператор сложения итератора и числа
  /// @param n Насколько элементов итератор перешагнет
  /// @return Новый итератор, указывающий на элемент через n позиций после
  /// текущего
  VectorConstIterator operator+(int n) const;

  /// @brief Оператор вычитания числа из итератора
  /// @param n Насколько элементов итератор перешагнет
  /// @return Новый итератор, указывающий на элемент через n позиций до текущего
  VectorConstIterator operator-(int n) const;

  /// @brief Оператор вычитания итератора из итератора
  /// @param other другой итератор
  /// @return Разница в позициях между двуимя итераторами
  ptrdiff_t operator-(const VectorConstIterator& other) const;

 private:
  const_iterator_pointer ptr_;
};

}  // namespace s21

#include "../templates/vector_iterator.tpp"
#endif