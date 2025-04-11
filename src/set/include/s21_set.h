#ifndef S_21_SET
#define S_21_SET

#include <functional>
#include <initializer_list>
#include <limits>

#include "../../tree/include/s21_tree.h"

namespace s21 {
/// @brief Класс реализующий множество
/// @tparam Key - тип значения хранящегося в дереве

template <typename Key>
class set {
  using key_type = Key;  /// < псевдоним типа для ключа
  using value_type = Key;  /// < псевдоним типа для хранящегося значения
  Tree<value_type> tree_;  /// < экземпляр класса дерева

  /// @brief Класс реализующий итераторы множетсва
 public:
  class SetIterator {
   private:
    typename Tree<value_type>::TreeIterator it;  ///< итератор дерева
   public:
    /// @brief конструктор копирующий TreeIterator в поле it
    /// @param it Легальный TreeIterator
    SetIterator(typename Tree<value_type>::TreeIterator it) : it(it) {}
    /// @brief Копирующий конструктор
    /// @param other другой SetIterator
    SetIterator(SetIterator& other) noexcept : it(other.it) {}
    /// @brief Перемещающий конструктор
    /// @param other другой SetIterator
    SetIterator(SetIterator&& other) noexcept : it(std::move(other.it)) {}
    /// @brief Перемещающий оператор присваивания
    /// @param other другой SetIterator
    /// @return этот SetIterator
    SetIterator& operator=(SetIterator&& other) noexcept {
      if (this != &other) it = std::move(other.it);
      return *this;
    }
    /// @brief Копирующий оператор присваивания
    /// @param other другой SetIterator
    /// @return этот SetIterator
    SetIterator& operator=(const SetIterator& other) noexcept {
      it = other.it;
      return *this;
    }
    /// @brief Возвращает ключ хранящийся в данном итераторе
    /// @return Ключ
    value_type& operator*() const { return *it; }
    /// @brief Оператор получения указателя на итератор
    /// @return Возвращает указатель
    value_type* operator->() const { return it.operator->(); }
    /// @brief Инкремент с префиксной записью
    /// @return Возвращает ссылку на следующий элемент итератора, current_
    /// увеличивается
    SetIterator& operator++() {
      ++it;
      return *this;
    }
    /// @brief Инкремент с постфиксной записью
    /// @return Возвращает итератор текущего элемента, увеличивая current_
    SetIterator operator++(int) {
      SetIterator tmp = *this;
      ++it;
      return tmp;
    }
    /// @brief Декремент с префиксной записью
    /// @return Возвращает ссылку на предыдущий элемент итератора, current_
    /// увеличивается
    SetIterator& operator--() {
      --it;
      return *this;
    }
    /// @brief Декремент с постфиксной записью
    /// @return Возвращает итератор текущего элемента, уменьшая current_
    SetIterator operator--(int) {
      SetIterator tmp = *this;
      --it;
      return tmp;
    }
    /// @brief Оператор сравнения
    /// @return Возвращает true если итераторы равны
    bool operator==(const SetIterator& other) const { return it == other.it; }
    /// @brief Оператор сравнения
    /// @return Возвращает true если итераторы не равны
    bool operator!=(const SetIterator& other) const { return it != other.it; }
  };
  /// @brief Все тоже самое что и SetIterator только для конст
  class ConstSetIterator {
   private:
    typename Tree<value_type>::ConstTreeIterator it;  ///< конст итератор дерева

   public:
    /// @brief Копирующий конст конструктор
    /// @param other другой конст SetIterator
    ConstSetIterator(const SetIterator& other) : it(other.it) {}
    /// @brief конст конструктор копирующий конст TreeIterator в поле it
    /// @param it Легальный конст TreeIterator
    ConstSetIterator(typename Tree<value_type>::ConstTreeIterator it)
        : it(it) {}
    /// @brief Копирующий конст конструктор
    /// @param other другой конст SetIterator
    ConstSetIterator(const ConstSetIterator& other) noexcept : it(other.it) {}
    /// @brief Перемещающий конст конструктор
    /// @param other другой конст SetIterator
    ConstSetIterator(ConstSetIterator&& other) noexcept
        : it(std::move(other.it)) {}
    /// @brief Перемещающий конст оператор присваивания
    /// @param other другой конст SetIterator
    /// @return этот SetIterator
    ConstSetIterator& operator=(ConstSetIterator&& other) noexcept {
      if (this != &other) it = std::move(other.it);
      return *this;
    }
    /// @brief Копирующий конст оператор присваивания
    /// @param other другой конст SetIterator
    /// @return этот SetIterator
    ConstSetIterator& operator=(const ConstSetIterator& other) noexcept {
      it = other.it;
      return *this;
    }
    /// @brief Возвращает конст ключ хранящийся в данном итераторе
    /// @return Ключ
    const value_type& operator*() const { return *it; }
    /// @brief Оператор получения указателя на конст итератор
    /// @return Возвращает указатель
    const value_type* operator->() const { return it.operator->(); }
    /// @brief конст инкремент с префиксной записью
    /// @return Возвращает ссылку на следующий элемент конст итератора, current_
    /// увеличивается
    ConstSetIterator& operator++() {
      ++it;
      return *this;
    }
    /// @brief конст инкремент с постфиксной записью
    /// @return Возвращает конст итератор текущего элемента, увеличивая current_
    ConstSetIterator operator++(int) {
      ConstSetIterator tmp = *this;
      ++it;
      return tmp;
    }
    /// @brief конст декремент с префиксной записью
    /// @return Возвращает ссылку на предыдущий элемент конст итератора,
    /// current_ увеличивается
    ConstSetIterator& operator--() {
      --it;
      return *this;
    }
    /// @brief конст декремент с постфиксной записью
    /// @return Возвращает конст итератор текущего элемента, уменьшая current_
    ConstSetIterator operator--(int) {
      ConstSetIterator tmp = *this;
      --it;
      return tmp;
    }
    /// @brief конст оператор сравнения
    /// @return Возвращает true если конст итераторы равны
    bool operator==(const ConstSetIterator& other) const {
      return it == other.it;
    }
    /// @brief конст оператор сравнения
    /// @return Возвращает true если конст итераторы не равны
    bool operator!=(const ConstSetIterator& other) const {
      return it != other.it;
    }
  };
  using reference = Key&;  /// < псевдоним для ссылки на элемент Key
  using const_reference =
      const Key&;  /// < псевдоним для константно ссылки на Key
  using tree = Tree<key_type>;  /// < псевдоним для класса дерево
  using iterator = SetIterator;  /// < псевдоним для использованич итератора
  using const_iterator =
      ConstSetIterator;  /// < псевдоним для использованич конст итератора
  using size_type =
      size_t;  /// < псевдоним для представления размерности множетсва

  /// @brief Дефолтный конструктор set(инициализирует set)
  set() { tree_ = Tree<value_type>(); };
  /// @brief Конструктор инициализирующий set парами из списка items
  /// @param items initializer_list из пар ключ-значение
  set(std::initializer_list<value_type> const& items) {
    tree_ = Tree<value_type>();
    for (auto& item : items) {
      tree_.push(item);  // добавление элемента, или его замена
    }
  }
  /// @brief Конструктор инициализирующий set парами хранящимися в set
  /// @param m Другой объект set
  set(const set& other) noexcept : tree_(other.tree_) {}
  /// @brief Конструктор перемещающий значения из set в новое множество
  /// @param m Другой объект set
  set(set&& other) noexcept
      : tree_(std::move(other.tree_)) {}  // -||- перемещения
  /// @brief перемещающий оператор присваивания из другой пары
  /// @param other другая пара
  /// @return возвращает текущую пару
  set& operator=(set&& other) noexcept {
    if (this != &other) {
      tree_ = std::move(other.tree_);
    }
    return *this;
  }
  /// @brief копирующий оператор присваивания из другой пары
  /// @param other другая пара
  /// @return возвращает текущую пару
  set& operator=(const set& other) {  // присваивния с копированием
    tree_ = other.tree_;
    return *this;
  }
  /// @brief Очищает tree_
  void clear() { tree_.clear(); }  // удаление как и для дерева
  /// @brief Показывает есть ли элементы в set
  /// @return Возвращает true, если tree_.size() == 0
  bool empty() noexcept {
    return tree_.size() == 0;
  }  // проверка на пустоту, для мапа и для дерева одинаковые

  /// @brief Количество элементов в map
  /// @return Возвращает tree_.size()
  size_type size() noexcept {
    return tree_.size();
  }  // получение размерности для мапа и дерева одинаковые

  /// @brief максимальное количество элементов в set
  /// @return Возвращает максимальную размерность
  size_type max_size() noexcept {
    return std::numeric_limits<Key>::max();
  }  // получение размерности -||-

  /// @brief Вставляет пару ключ-значение value
  /// @param value пара ключ-значение
  /// @return Пара итератора вставленного элемента и переменной типа bool
  /// показывающей был ли вставлен элемент
  std::pair<iterator, bool> insert(
      const value_type& value) {  // добавляем в случае если есть поменет
                                  // значение на то которое было
    size_t tmp = tree_.size();
    if (!(tree_.contains(value))) tree_.push(value);
    return std::make_pair(SetIterator(tree_.search(value)), tree_.size() > tmp);
  }
  /// @brief Удаление элемента из set
  /// @param pos Удаление элемента по итератору
  void erase(iterator pos) { tree_.erase(*pos); }

  /// @brief Меняет значения текущего дерева tree_ и other.tree_
  /// @param other Другой объект map
  void swap(set& other) noexcept {
    Tree<value_type> tmp1 = other.tree_;
    other.tree_ = tree_;
    tree_ = tmp1;
  }  // для мапа и для жерева одинаковые
  /// @brief Слияние текущего set с другим и очистка его пар если пары с таким
  /// ключом не было в текущем set
  /// @param other другой set
  void merge(set& other) {
    auto it = other.begin();
    while (it != other.end()) {
      if (!(tree_.contains(*it))) {
        tree_.push(*it);
        auto tmp = it;
        it++;
        other.tree_.erase(*tmp);
      } else
        it++;
    }
  }  // обьединение двух

  /// @brief поиск node содержащей val
  /// @return возращает итератор содержащий значение
  iterator find(const Key& key) noexcept {
    return SetIterator(tree_.search(key));
  }  // поиск по дереву

  /// @brief конст поиск node содержащей val
  /// @return возращает итератор содержащий конст значение
  const_iterator find(const Key& key) const noexcept {
    return ConstSetIterator(tree_.csearch(key));
  }
  /// @brief проверка наличия элемента в множетсве
  /// @return true если содержит val, false если нет
  bool contains(const Key& key) noexcept {
    return SetIterator(tree_.search(key)) != end();
  }
  /// @brief итератор начала
  /// @return Возвращает итератор начала множетсва
  iterator begin() noexcept { return tree_.begin(); }  // итератор начала

  /// @brief конст итератор начала
  /// @return Возвращает итератор начала константного множества
  const_iterator cbegin() const noexcept { return tree_.cbegin(); }

  /// @brief итератор конца
  /// @return Возвращает итератор конца множетсва
  iterator end() noexcept { return tree_.end(); }

  /// @brief конст итератор конца
  /// @return Возвращает итератор конца константного множетсва
  const_iterator cend() const noexcept { return tree_.cend(); }
};

}  // namespace s21

#endif  // S_21_SET
