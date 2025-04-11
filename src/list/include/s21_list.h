#ifndef S21_LIST_H
#define S21_LIST_H

#include <iostream>
#include <limits>

namespace s21 {

/**
 * @brief Класс Node представляет узел двусвязного списка.
 *
 * @tparam T Тип данных, хранимых в узле.
 */
template <typename T>
class Node {
 public:
  T data;      ///< Данные, хранимые в узле.
  Node* next;  ///< Указатель на следующий узел.
  Node* prev;  ///< Указатель на предыдущий узел.

  /**
   * @brief Конструктор по умолчанию.
   */
  Node();

  /**
   * @brief Конструктор с параметром.
   *
   * @param value Значение для инициализации узла.
   */
  Node(const T& value);
};

/**
 * @brief Класс ListIterator представляет итератор для двусвязного списка.
 *
 * @tparam T Тип данных, хранимых в списке.
 */
template <typename T>
class ListIterator {
 private:
  Node<T>* current;  ///< Текущий узел.
  Node<T>* prev;     ///< Предыдущий узел.

 public:
  /**
   * @brief Конструктор по умолчанию.
   */
  ListIterator();

  /**
   * @brief Конструктор с параметром.
   *
   * @param ptr Указатель на текущий узел.
   * @param prevPtr Указатель на предыдущий узел.
   */
  ListIterator(Node<T>* ptr, Node<T>* prevPtr = nullptr);

  /**
   * @brief Конструктор копирования.
   *
   * @param other Другой итератор для копирования.
   */
  ListIterator(const ListIterator& other);

  /**
   * @brief Возвращает текущий узел.
   *
   * @return Указатель на текущий узел.
   */
  Node<T>* getCurrent() const;

  /**
   * @brief Оператор присваивания.
   *
   * @param other Другой итератор для присваивания.
   * @return Ссылка на текущий итератор.
   */
  ListIterator& operator=(const ListIterator& other);

  /**
   * @brief Оператор разыменования.
   *
   * @return Ссылка на данные текущего узла.
   */
  T& operator*() const;

  /**
   * @brief Оператор доступа к членам.
   *
   * @return Указатель на данные текущего узла.
   */
  T* operator->() const;

  /**
   * @brief Префиксный оператор инкремента.
   *
   * @return Ссылка на текущий итератор.
   */
  ListIterator& operator++();

  /**
   * @brief Постфиксный оператор инкремента.
   *
   * @return Копия текущего итератора до инкремента.
   */
  ListIterator operator++(int);

  /**
   * @brief Префиксный оператор декремента.
   *
   * @return Ссылка на текущий итератор.
   */
  ListIterator& operator--();

  /**
   * @brief Постфиксный оператор декремента.
   *
   * @return Копия текущего итератора до декремента.
   */
  ListIterator operator--(int);

  /**
   * @brief Оператор неравенства.
   *
   * @param other Другой итератор для сравнения.
   * @return true, если итераторы не равны, иначе false.
   */
  bool operator!=(const ListIterator& other) const;

  /**
   * @brief Оператор равенства.
   *
   * @param other Другой итератор для сравнения.
   * @return true, если итераторы равны, иначе false.
   */
  bool operator==(const ListIterator& other) const;
};

/**
 * @brief Класс ListConstIterator представляет константный итератор для
 * двусвязного списка.
 *
 * @tparam T Тип данных, хранимых в списке.
 */
template <typename T>
class ListConstIterator {
 private:
  Node<T>* current;  ///< Текущий узел.
  Node<T>* prev;     ///< Предыдущий узел.

 public:
  /**
   * @brief Конструктор по умолчанию.
   */
  ListConstIterator();

  /**
   * @brief Конструктор с параметром.
   *
   * @param ptr Указатель на текущий узел.
   * @param prevPtr Указатель на предыдущий узел.
   */
  ListConstIterator(Node<T>* ptr, Node<T>* prevPtr = nullptr);

  /**
   * @brief Конструктор копирования.
   *
   * @param other Другой итератор для копирования.
   */
  ListConstIterator(const ListConstIterator& other);

  /**
   * @brief Конструктор копирования из ListIterator.
   *
   * @param other Другой итератор для копирования.
   */
  ListConstIterator(const ListIterator<T>& other);

  /**
   * @brief Оператор присваивания.
   *
   * @param other Другой итератор для присваивания.
   * @return Ссылка на текущий итератор.
   */
  ListConstIterator& operator=(const ListConstIterator& other);

  /**
   * @brief Оператор разыменования.
   *
   * @return Константная ссылка на данные текущего узла.
   */
  const T& operator*() const;

  /**
   * @brief Оператор доступа к членам.
   *
   * @return Константный указатель на данные текущего узла.
   */
  const T* operator->() const;

  /**
   * @brief Префиксный оператор инкремента.
   *
   * @return Ссылка на текущий итератор.
   */
  ListConstIterator& operator++();

  /**
   * @brief Постфиксный оператор инкремента.
   *
   * @return Копия текущего итератора до инкремента.
   */
  ListConstIterator operator++(int);

  /**
   * @brief Префиксный оператор декремента.
   *
   * @return Ссылка на текущий итератор.
   */
  ListConstIterator& operator--();

  /**
   * @brief Постфиксный оператор декремента.
   *
   * @return Копия текущего итератора до декремента.
   */
  ListConstIterator operator--(int);

  /**
   * @brief Оператор равенства.
   *
   * @param other Другой итератор для сравнения.
   * @return true, если итераторы равны, иначе false.
   */
  bool operator==(const ListConstIterator& other) const;

  /**
   * @brief Оператор неравенства.
   *
   * @param other Другой итератор для сравнения.
   * @return true, если итераторы не равны, иначе false.
   */
  bool operator!=(const ListConstIterator& other) const;

  /**
   * @brief Возвращает текущий узел.
   *
   * @return Указатель на текущий узел.
   */
  Node<T>* getCurrent() const;
};

/**
 * @brief Шаблонный класс list, представляющий двусвязный список.
 *
 * @tparam T Тип данных, хранимых в списке.
 */
template <typename T>
class list {
 private:
  Node<T>* head;  ///< Указатель на первый узел.
  Node<T>* tail;  ///< Указатель на последний узел.
  size_t length;  ///< Количество элементов в списке.

 public:
  using value_type = T;  ///< Тип данных, хранимых в списке.
  using reference = T&;  ///< Ссылка на элемент списка.
  using const_reference = const T&;  ///< Константная ссылка на элемент списка.
  using iterator = ListIterator<T>;  ///< Итератор для списка.
  using const_iterator =
      ListConstIterator<T>;  ///< Константный итератор для списка.
  using size_type = std::size_t;  ///< Тип для представления размера.

  /**
   * @brief Конструктор по умолчанию.
   */
  list();

  /**
   * @brief Конструктор с заданным количеством элементов.
   *
   * @param n Количество элементов для инициализации.
   */
  list(size_type n);

  /**
   * @brief Конструктор с заданным количеством элементов и значением.
   *
   * @param count Количество элементов для инициализации.
   * @param value Значение для инициализации элементов.
   */
  list(size_type count, const_reference value);

  /**
   * @brief Конструктор с использованием списка инициализации.
   *
   * @param initList Список элементов для инициализации.
   */
  list(std::initializer_list<value_type> initList);

  /**
   * @brief Конструктор копирования.
   *
   * @param other Другой список для копирования.
   */
  list(const list& other);

  /**
   * @brief Конструктор перемещения.
   *
   * @param other Временный список для перемещения.
   */
  list(list&& other);

  /**
   * @brief Деструктор.
   */
  ~list();

  /**
   * @brief Оператор присваивания перемещением.
   *
   * @param other Временный список для присваивания.
   * @return Ссылка на текущий список.
   */
  list& operator=(list&& other) noexcept;

  /**
   * @brief Добавляет элемент в конец списка.
   *
   * @param value Значение для добавления.
   */
  void push_back(const_reference value);

  /**
   * @brief Добавляет элемент в начало списка.
   *
   * @param value Значение для добавления.
   */
  void push_front(const_reference value);

  /**
   * @brief Удаляет последний элемент списка.
   */
  void pop_back();

  /**
   * @brief Удаляет первый элемент списка.
   */
  void pop_front();

  /**
   * @brief Возвращает ссылку на первый элемент списка.
   *
   * @return Константная ссылка на первый элемент.
   */
  const_reference front() const;

  /**
   * @brief Возвращает ссылку на последний элемент списка.
   *
   * @return Константная ссылка на последний элемент.
   */
  const_reference back() const;

  /**
   * @brief Вставляет элемент в заданную позицию.
   *
   * @param pos Позиция для вставки.
   * @param val Значение для вставки.
   * @return Итератор на вставленный элемент.
   */
  iterator insert(iterator pos, const_reference val);

  /**
   * @brief Вставляет несколько элементов в заданную позицию.
   *
   * @param pos Позиция для вставки.
   * @param n Количество элементов для вставки.
   * @param val Значение для вставки.
   * @return Итератор на первый вставленный элемент.
   */
  iterator insert(iterator pos, size_type n, const_reference val);

  /**
   * @brief Вставляет элементы из диапазона в заданную позицию.
   *
   * @param pos Позиция для вставки.
   * @param begin Начало диапазона.
   * @param end Конец диапазона.
   * @return Итератор на первый вставленный элемент.
   */
  iterator insert(iterator pos, iterator begin, iterator end);

  /**
   * @brief Удаляет элемент в заданной позиции.
   *
   * @param pos Позиция для удаления.
   * @return Итератор на следующий элемент.
   */
  iterator erase(iterator pos);

  /**
   * @brief Возвращает итератор на начало списка.
   *
   * @return Итератор на начало списка.
   */
  iterator begin();

  /**
   * @brief Возвращает итератор на конец списка.
   *
   * @return Итератор на конец списка.
   */
  iterator end();

  /**
   * @brief Очищает список.
   */
  void clear();

  /**
   * @brief Возвращает константный итератор на начало списка.
   *
   * @return Константный итератор на начало списка.
   */
  const_iterator cbegin() const;

  /**
   * @brief Возвращает константный итератор на конец списка.
   *
   * @return Константный итератор на конец списка.
   */
  const_iterator cend() const;

  /**
   * @brief Проверяет, пуст ли список.
   *
   * @return true, если список пуст, иначе false.
   */
  bool empty() const;

  /**
   * @brief Возвращает количество элементов в списке.
   *
   * @return Размер списка.
   */
  size_type size() const;

  /**
   * @brief Возвращает максимальный размер списка.
   *
   * @return Максимальный размер списка.
   */
  size_type max_size() const;

  /**
   * @brief Изменяет размер списка.
   *
   * @param n Новый размер списка.
   * @param value Значение для инициализации новых элементов.
   */
  void resize(size_type n, value_type value = value_type());

  /**
   * @brief Обменивает содержимое с другим списком.
   *
   * @param other Другой список для обмена.
   */
  void swap(list& other);

  /**
   * @brief Сортирует элементы списка.
   */
  void sort();

  /**
   * @brief Удаляет дубликаты из списка.
   */
  void unique();

  /**
   * @brief Объединяет два отсортированных списка.
   *
   * @param other Другой список для объединения.
   */
  void merge(list& other);

  /**
   * @brief Обращает порядок элементов в списке.
   */
  void reverse();

  /**
   * @brief Вставляет элементы из другого списка в заданную позицию.
   *
   * @param pos Позиция для вставки.
   * @param other Другой список для вставки.
   */
  void splice(const_iterator pos, list& other);

 private:
  /**
   * @brief Вспомогательная функция для сортировки слиянием.
   *
   * @param array Массив для сортировки.
   * @param left Левая граница.
   * @param right Правая граница.
   */
  void merge_sort(value_type* array, int left, int right);

  /**
   * @brief Вспомогательная функция для слияния двух отсортированных массивов.
   *
   * @param array Массив для слияния.
   * @param left Левая граница.
   * @param middle Средняя граница.
   * @param right Правая граница.
   */
  void merge(value_type* array, int left, int middle, int right);
};
}  // namespace s21

#include "../templates/s21_list.tpp"
#include "../templates/s21_list_const_iterator.tpp"
#include "../templates/s21_list_iterator.tpp"
#include "../templates/s21_node.tpp"

#endif  // S21_LIST_H
