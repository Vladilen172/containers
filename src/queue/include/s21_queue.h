#include <iostream>

#include "../../list/include/s21_list.h"

namespace s21 {

/**
 * @brief Шаблонный класс queue, представляющий очередь на основе списка.
 *
 * Этот класс предоставляет функциональность очереди, используя внутренний
 * список для хранения элементов. Очередь поддерживает операции добавления
 * элементов в конец и удаления элементов из начала.
 *
 * @tparam T Тип элементов очереди.
 */
template <typename T>
class queue {
 private:
  s21::list<T> list;  ///< Внутренний список для хранения элементов очереди.

 public:
  using value_type = T;  ///< Тип элементов очереди.
  using reference = T&;  ///< Ссылка на элемент очереди.
  using const_reference = const T&;  ///< Константная ссылка на элемент очереди.
  using size_type = std::size_t;  ///< Тип для представления размера.

  /**
   * @brief Конструктор по умолчанию.
   *
   * Создает пустую очередь.
   */
  queue() = default;

  /**
   * @brief Конструктор с использованием списка инициализации.
   *
   * @param items Список элементов для инициализации очереди.
   */
  queue(std::initializer_list<value_type> const& items) : list(items) {}

  /**
   * @brief Конструктор копирования.
   *
   * @param q Другая очередь, из которой будут скопированы элементы.
   */
  queue(const queue& q) : list(q.list) {}

  /**
   * @brief Конструктор перемещения.
   *
   * @param q Временная очередь, из которой будут перемещены элементы.
   */
  queue(queue&& q) noexcept : list(std::move(q.list)) { q.list.clear(); }

  /**
   * @brief Деструктор.
   */
  ~queue() = default;

  /**
   * @brief Оператор присваивания копированием.
   *
   * @param other Другая очередь, из которой будут скопированы элементы.
   * @return Ссылка на текущую очередь.
   */
  queue& operator=(queue& other) {
    if (this != &other) {
      while (!empty()) {
        this->pop();
      }
      for (const auto& item : other.list) {
        this->push(item);
      }
    }
    return *this;
  }

  /**
   * @brief Оператор присваивания перемещением.
   *
   * @param q Временная очередь, из которой будут перемещены элементы.
   * @return Ссылка на текущую очередь.
   */
  queue& operator=(queue&& q) noexcept {
    while (!empty()) {
      this->pop();
    }

    if (this != &q) {
      list = std::move(q.list);
    }
    return *this;
  }

  /**
   * @brief Возвращает ссылку на первый элемент очереди.
   *
   * @return Константная ссылка на первый элемент.
   * @throws std::out_of_range Если очередь пуста.
   */
  const_reference front() {
    if (list.empty()) {
      throw std::out_of_range("Queue is empty");
    }
    return list.front();
  }

  /**
   * @brief Возвращает ссылку на последний элемент очереди.
   *
   * @return Константная ссылка на последний элемент.
   * @throws std::out_of_range Если очередь пуста.
   */
  const_reference back() {
    if (list.empty()) {
      throw std::out_of_range("Queue is empty");
    }
    return list.back();
  }

  /**
   * @brief Проверяет, пуста ли очередь.
   *
   * @return true, если очередь пуста, иначе false.
   */
  bool empty() { return list.empty(); }

  /**
   * @brief Возвращает количество элементов в очереди.
   *
   * @return Размер очереди.
   */
  size_type size() { return list.size(); }

  /**
   * @brief Добавляет элемент в конец очереди.
   *
   * @param value Значение для добавления.
   */
  void push(const_reference value) { list.push_back(value); }

  /**
   * @brief Удаляет первый элемент очереди.
   *
   * @throws std::out_of_range Если очередь пуста.
   */
  void pop() {
    if (list.empty()) {
      throw std::out_of_range("Queue is empty");
    }
    list.pop_front();
  }

  /**
   * @brief Обменивает содержимое с другой очередью.
   *
   * @param other Другая очередь для обмена.
   */
  void swap(queue& other) { list.swap(other.list); }
};
}  // namespace s21
