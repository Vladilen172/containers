
#ifndef INCLUDE_S21_MAP_H
#define INCLUDE_S21_MAP_H
#include <iostream>
#include <limits>

#include "../../tree/include/s21_tree.h"
/// @brief Пространство имен
namespace s21 {
/// @brief класс map, содержащий дерево Tree
/// @tparam Key ключ
/// @tparam T значение
template <typename Key, typename T>
class map {
 private:
  /// @brief класс обозначающий ключ-значение(сравнение двух объектов ведется по
  /// ключу)
  class pair {
   private:
    Key val1;  ///< ключ
    T val2;    ///< значение
   public:
    /// @brief дефолтный конструктор инициализирующий оба значения дефолтными
    /// конструкторами
    pair();
    /// @brief конструктор инициализирующий ключ значением v1, значение
    /// значением v2
    /// @param v1 ключ новой пары
    /// @param v2 значение новой пары
    pair(const Key v1, T v2);
    /// @brief конструктор копирующий другую пару в новую
    /// @param other другая пара
    pair(const pair& other);
    /// @brief конструктор перемещающий другую пару в новую
    /// @param other другая пара
    pair(pair&& other);
    /// @brief копирующий оператор присваивания из другой пары
    /// @param other другая пара
    /// @return возвращает текущую пару
    pair& operator=(const pair& other);
    /// @brief перемещающий оператор присваивания из другой пары
    /// @param other другая пара
    /// @return возвращает текущую пару
    pair& operator=(pair&& other);
    /// @brief конструктор инициализирующий данный класс из initializer_list
    /// @param init лист содержащий одну пару, иначе exception
    pair(std::initializer_list<std::pair<Key, T>> init);
    /// @brief сравнение двух пар по ключу
    /// @param other другая пара
    /// @return true, если ключ первой пары меньше второй
    bool operator<(const pair& other);
    /// @brief сравнение двух пар по ключу
    /// @param other другая пара
    /// @return true, если ключ первой пары больше второй
    bool operator>(const pair& other);
    /// @brief сравнение двух пар по ключу
    /// @param other другая пара
    /// @return true, если ключ первой пары равен второй
    bool operator==(const pair& other) const;
    /// @brief константная ссылка на ключ
    /// @return
    const Key& first() const;
    /// @brief константная ссылка на значение
    /// @return
    const T& second() const;
    /// @brief ссылка на значение
    /// @return
    T& second();
  };
  using value_type = map<Key, T>::pair;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;
  /// @brief Дерево, содержащее пары ключ-значение
  s21::Tree<value_type> tree_;

 public:
  /// @brief Дефолтный конструктор map(инициализирует дерево)
  map();
  /// @brief Конструктор инициализирующий дерево одной парой
  /// @param pair ключ-значение
  map(value_type pair);
  /// @brief Конструктор инициализирующий дерево парами из списка items
  /// @param items initializer_list из пар ключ-значение
  map(std::initializer_list<value_type> const& items);
  /// @brief Конструктор инициализирующий дерево парами хранящимися в map
  /// @param m Другой объект map
  map(const map& m);
  /// @brief Конструктор перемещающий значения из m в новое дерево
  /// @param m Другой объект map
  map(map&& m);
  /// @brief Функция возвращающая ссылку на значение или exception если ключа
  /// key в дереве нет
  /// @param key Ключ для поиска
  /// @return Возвращает ссылку на значение или выкидывает exception
  T& at(const Key& key);
  /// @brief Функция возвращающая ссылку на значение или создающая новый узел в
  /// дереве с ключом key
  /// @param key Ключ для поиска
  /// @return Ссылка на значение(даже если ключа не было до вызова данного
  /// оператора)
  T& operator[](const Key& key);
  /// @brief Копирующий оператор присваивания
  /// @param m Другой объект map
  /// @return Возвращает текущий объект map с измененными полями
  map& operator=(const map& m);
  /// @brief Перемещающий оператор присваивания
  /// @param m Другой объект map
  /// @return Возвращает текущий объект map с измененными полями
  map& operator=(map&& m);
  /// @brief Показывает есть ли элементы в map
  /// @return Возвращает true, если tree_.size() == 0
  bool empty();
  /// @brief Количество элементов в map
  /// @return Возвращает tree_.size()
  size_type size();
  size_type max_size();
  /// @brief Очищает tree_
  void clear();
  /// @brief Меняет значения текущего дерева tree_ и other.tree_
  /// @param other Другой объект map
  void swap(map& other);
  /// @brief Показывает есть ли значение по данному ключу
  /// @param key ключ
  /// @return Возвращает true если ключ уже есть в дереве
  bool contains(const Key key);
  /// @brief Итератор map внутри которого спрятан итератор tree
  class MapIterator {
   private:
    typename Tree<value_type>::TreeIterator it;  ///< итератор дерева
   public:
    /// @brief конструктор копирующий TreeIterator в поле it
    /// @param it Легальный TreeIterator
    MapIterator(typename Tree<value_type>::TreeIterator it) : it(it) {}
    /// @brief Копирующий конструктор
    /// @param other другой MapIterator
    MapIterator(MapIterator& other) noexcept : it(other.it) {}
    /// @brief Перемещающий конструктор
    /// @param other другой MapIterator
    MapIterator(MapIterator&& other) noexcept : it(std::move(other.it)) {}
    /// @brief Перемещающий оператор присваивания
    /// @param other другой MapIterator
    /// @return этот MapIterator
    MapIterator& operator=(MapIterator&& other) noexcept {
      if (this != &other) it = std::move(other.it);
      return *this;
    }
    /// @brief Копирующий оператор присваивания
    /// @param other другой MapIterator
    /// @return этот MapIterator
    MapIterator& operator=(MapIterator& other) noexcept {
      it = other.it;
      return *this;
    }
    /// @brief Возвращает пару ключ-значение хранящуюся в данном итераторе
    /// @return Пара ключ значение если итератор it легален
    value_type& operator*() const { return *it; }
    /// @brief Оператор получения указателя на итератор
    /// @return Возвращает указатель
    value_type* operator->() const { return it.operator->(); }
    /// @brief Инкремент с префиксной записью
    /// @return Возвращает ссылку на следующий элемент итератора, current_
    /// увеличивается
    MapIterator& operator++() {
      ++it;
      return *this;
    }
    /// @brief Инкремент с постфиксной записью
    /// @param
    /// @return Возвращает итератор текущего элемента, увеличивая current_
    MapIterator operator++(int) {
      MapIterator tmp = *this;
      ++it;
      return tmp;
    }
    /// @brief Декремент с префиксной записью
    /// @return Возвращает ссылку на предыдущий элемент итератора, current_
    /// увеличивается
    MapIterator& operator--() {
      --it;
      return *this;
    }
    /// @brief Декремент с постфиксной записью
    /// @param
    /// @return Возвращает итератор текущего элемента, уменьшая current_
    MapIterator operator--(int) {
      MapIterator tmp = *this;
      --it;
      return tmp;
    }
    /// @brief Оператор сравнения
    /// @param
    /// @return Возвращает true если итераторы равны
    bool operator==(const MapIterator& other) const { return it == other.it; }
    /// @brief Оператор сравнения
    /// @param
    /// @return Возвращает true если итераторы не равны
    bool operator!=(const MapIterator& other) const { return it != other.it; }
  };
  /// @brief Все тоже самое что и MapIterator
  class ConstMapIterator {
   private:
    typename Tree<value_type>::ConstTreeIterator it;

   public:
    ConstMapIterator(const MapIterator& other) : it(other.it) {}
    ConstMapIterator(typename Tree<value_type>::ConstTreeIterator it)
        : it(it) {}
    ConstMapIterator(const ConstMapIterator& other) noexcept : it(other.it) {}
    ConstMapIterator(ConstMapIterator&& other) noexcept
        : it(std::move(other.it)) {}
    ConstMapIterator& operator=(ConstMapIterator&& other) noexcept {
      if (this != &other) it = std::move(other.it);
      return *this;
    }
    ConstMapIterator& operator=(const ConstMapIterator& other) noexcept {
      it = other.it;
      return *this;
    }
    const value_type& operator*() const { return *it; }
    const value_type* operator->() const { return it.operator->(); }
    ConstMapIterator& operator++() {
      ++it;
      return *this;
    }
    ConstMapIterator operator++(int) {
      ConstMapIterator tmp = *this;
      ++it;
      return tmp;
    }
    ConstMapIterator& operator--() {
      --it;
      return *this;
    }
    ConstMapIterator operator--(int) {
      ConstMapIterator tmp = *this;
      --it;
      return tmp;
    }
    bool operator==(const ConstMapIterator& other) const {
      return it == other.it;
    }
    bool operator!=(const ConstMapIterator& other) const {
      return it != other.it;
    }
  };
  using iterator = map<Key, T>::MapIterator;
  using const_iterator = map<Key, T>::ConstMapIterator;
  /// @brief Вставляет пару ключ-значение value
  /// @param value пара ключ-значение
  /// @return Пара итератора вставленного элемента и переменной типа bool
  /// показывающей был ли вставлен элемент
  std::pair<MapIterator, bool> insert(const value_type& value);
  /// @brief Вставляет пару ключ-значение {key, obj}
  /// @param key ключ
  /// @param obj значение
  /// @return Пара итератора вставленного элемента и переменной типа bool
  /// показывающей был ли вставлен элемент
  std::pair<MapIterator, bool> insert(const Key& key, const T& obj);
  /// @brief Вставляет пару ключ-значение {key, obj}
  /// @param key ключ
  /// @param obj значение
  /// @return Пара итератора вставленного элемента и переменной типа bool
  /// показывающей был ли вставлен элемент
  std::pair<MapIterator, bool> insert_or_assign(const Key& key, const T& obj);
  /// @brief Удаление элемента из map
  /// @param pos Удаление элемента по итератору
  void erase(MapIterator pos);
  /// @brief Слияние текущей map с другой и очистка его пар если пары с таким
  /// ключом не было в текущей map
  /// @param other другая map
  void merge(map& other);
  /// @brief Начало текущей map
  /// @return начальный итератор текущей map
  MapIterator begin() { return MapIterator(tree_.begin()); }
  /// @brief Конец текущей map
  /// @return конечный итератор текущей map
  MapIterator end() { return MapIterator(tree_.end()); }
  /// @brief Начало текущей map
  /// @return начальный итератор текущей map
  const_iterator cbegin() const { return const_iterator(tree_.cbegin()); }
  /// @brief Конец текущей map
  /// @return конечный итератор текущей map
  const_iterator cend() const { return const_iterator(tree_.cend()); }
};
}  // namespace s21
#include "../templates/s21_map.tpp"
#include "../templates/s21_pair.tpp"
#endif