#ifndef S21_ARRAY
#define S21_ARRAY

#include <iostream>

namespace s21 {
/**
 * @brief Шаблонный класс array, представляющий массив фиксированного размера.
 *
 * Этот класс предоставляет функциональность, аналогичную стандартному массиву,
 * с дополнительными методами и удобствами для работы с элементами.
 *
 * @tparam T Тип элементов массива.
 * @tparam N Размер массива.
 */
template <typename T, std::size_t N>
class array {
 private:
  T values[N];

 public:
  using value_type = T;   ///< Тип элементов массива.
  using reference = T &;  ///< Ссылка на элемент массива.
  using const_reference =
      const T &;  ///< Константная ссылка на элемент массива.
  using iterator = T *;  ///< Итератор для массива.
  using const_iterator = const T *;  ///< Константный итератор для массива.
  using size_type = std::size_t;  ///< Тип для представления размера.

  /**
   * @brief Конструктор по умолчанию.
   *
   * Создает массив с элементами, инициализированными по умолчанию.
   */
  array() = default;

  /**
   * @brief Конструктор с использованием списка инициализации.
   *
   * @param items Список элементов для инициализации массива.
   */
  array(std::initializer_list<value_type> const &items) {
    std::copy(items.begin(), items.end(), values);
    std::fill(values + items.size(), values + N, T());
  }

  /**
   * @brief Конструктор копирования.
   *
   * @param a Другой массив, из которого будут скопированы элементы.
   */
  array(const array &a) { std::copy(a.values, a.values + N, values); };

  /**
   * @brief Конструктор перемещения.
   *
   * @param a Временный массив, из которого будут перемещены элементы.
   */
  array(array &&a) { std::move(a.values, a.values + N, values); }

  /**
   * @brief Деструктор.
   */
  ~array() = default;

  /**
   * @brief Оператор присваивания перемещением.
   *
   * @param a Временный массив, из которого будут перемещены элементы.
   * @return Ссылка на текущий массив.
   */
  array &operator=(array &&a) noexcept {
    if (this != &a) {
      std::move(a.values, a.values + N, values);
    }
    return *this;
  }

  /**
   * @brief Возвращает ссылку на элемент по индексу.
   *
   * @param pos Индекс элемента.
   * @return Ссылка на элемент.
   * @throws std::out_of_range Если индекс выходит за пределы массива.
   */
  reference at(size_type pos) {
    if (pos >= N) {
      throw std::out_of_range("Index out of range");
    }

    return values[pos];
  }

  /**
   * @brief Оператор доступа к элементу по индексу.
   *
   * @param pos Индекс элемента.
   * @return Ссылка на элемент.
   * @throws std::out_of_range Если индекс выходит за пределы массива.
   */
  reference operator[](size_type pos) {
    if (pos >= N) {
      throw std::out_of_range("Index out of range");
    }

    return values[pos];
  }

  /**
   * @brief Возвращает первый элемент массива.
   *
   * @return Константная ссылка на первый элемент.
   */
  const_reference front() const { return values[0]; }

  /**
   * @brief Возвращает последний элемент массива.
   *
   * @return Константная ссылка на последний элемент.
   */
  const_reference back() const { return values[N - 1]; }

  /**
   * @brief Возвращает указатель на данные массива.
   *
   * @return Указатель на начало массива.
   */
  iterator data() { return (N == 0) ? nullptr : values; }

  /**
   * @brief Возвращает итератор на начало массива.
   *
   * @return Итератор на начало массива.
   */
  iterator begin() { return values; }

  /**
   * @brief Возвращает итератор на конец массива.
   *
   * @return Итератор на конец массива.
   */
  iterator end() { return values + N; }

  /**
   * @brief Проверяет, пуст ли массив.
   *
   * @return Всегда возвращает false, так как массив фиксированного размера.
   */
  bool empty() const { return N == 0; }

  /**
   * @brief Возвращает размер массива.
   *
   * @return Размер массива.
   */
  size_type size() const { return N; }

  /**
   * @brief Возвращает максимальный размер массива.
   *
   * @return Максимальный размер массива.
   */
  size_type max_size() const { return N; }

  /**
   * @brief Обменивает содержимое с другим массивом.
   *
   * @param other Другой массив для обмена.
   */
  void swap(array &other) {
    std::swap_ranges(values, values + N, other.values);
  }

  /**
   * @brief Заполняет массив заданным значением.
   *
   * @param value Значение для заполнения.
   */
  void fill(const_reference value) {
    for (auto &elem : values) {
      elem = value;
    }
  }
};
}  // namespace s21

#endif