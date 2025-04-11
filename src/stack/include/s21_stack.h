#include <iostream>

#include "../../list/include/s21_list.h"

namespace s21 {
/**
 * @brief Шаблонный класс stack, представляющий стек на основе списка.
 *
 * Этот класс предоставляет функциональность стека, используя внутренний список
 * для хранения элементов. Стек поддерживает операции добавления и удаления
 * элементов с вершины стека.
 *
 * @tparam T Тип элементов стека.
 */
template <typename T>
class stack {
 private:
  s21::list<T> head;  ///< Внутренний список для хранения элементов стека.

 public:
  using value_type = T;  ///< Тип элементов стека.
  using reference = T&;  ///< Ссылка на элемент стека.
  using const_reference = const T&;  ///< Константная ссылка на элемент стека.
  using size_type = std::size_t;  ///< Тип для представления размера.

  /**
   * @brief Конструктор по умолчанию.
   *
   * Создает пустой стек.
   */
  stack() = default;

  /**
   * @brief Конструктор с использованием списка инициализации.
   *
   * @param items Список элементов для инициализации стека.
   */
  stack(std::initializer_list<value_type> const& items) : head(items) {}

  /**
   * @brief Конструктор копирования.
   *
   * @param s Другой стек, из которого будут скопированы элементы.
   */
  stack(const stack& s) : head(s.head) {}

  /**
   * @brief Конструктор перемещения.
   *
   * @param s Временный стек, из которого будут перемещены элементы.
   */
  stack(stack&& s) noexcept : head(std::move(s.head)) { s.head.clear(); }

  /**
   * @brief Деструктор.
   */
  ~stack() = default;

  /**
   * @brief Оператор присваивания перемещением.
   *
   * @param s Временный стек, из которого будут перемещены элементы.
   * @return Ссылка на текущий стек.
   */
  stack& operator=(stack&& s) noexcept {
    while (!empty()) {
      this->pop();
    }

    if (this != &s) {
      head = std::move(s.head);
    }

    return *this;
  }

  /**
   * @brief Возвращает ссылку на верхний элемент стека.
   *
   * @return Константная ссылка на верхний элемент.
   * @throws std::out_of_range Если стек пуст.
   */
  const_reference top() const {
    if (head.empty()) {
      throw std::out_of_range("Stack is empty");
    }
    return head.back();
  }

  /**
   * @brief Добавляет элемент на вершину стека.
   *
   * @param value Значение для добавления.
   */
  void push(const_reference value) { head.push_back(value); }

  /**
   * @brief Удаляет верхний элемент стека.
   *
   * @throws std::out_of_range Если стек пуст.
   */
  void pop() {
    if (head.empty()) {
      throw std::out_of_range("Stack is empty");
    }
    head.pop_back();
  }

  /**
   * @brief Обменивает содержимое с другим стеком.
   *
   * @param other Другой стек для обмена.
   */
  void swap(stack& other) { head.swap(other.head); }

  /**
   * @brief Проверяет, пуст ли стек.
   *
   * @return true, если стек пуст, иначе false.
   */
  bool empty() const { return head.empty(); }

  /**
   * @brief Возвращает количество элементов в стеке.
   *
   * @return Размер стека.
   */
  size_type size() const { return head.size(); }
};
}  // namespace s21
