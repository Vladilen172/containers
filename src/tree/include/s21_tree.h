#ifndef S21_TREE_H
#define S21_TREE_H
#include <iostream>
namespace s21 {
/// @brief Класс реализующий дерево - вспомогательный класс для классов set и
/// map
/// @tparam T - тип значения хранящегося в дереве
/*!
    В данном случае реализовано красно-черное дерево, удовлетворяющее следующим
   правилам: 1) Корень всегда черный 2) Черная высота(количество черных узлов в
   ветке) с обеих сторон от узла одинакова 3) У красного узла могут быть только
   черные дети 4) У пустых узлов черный цвет
*/
template <typename T>
class Tree {
 private:
  /// @brief внутренняя структура, реализующая узел дерева и функции для работы
  /// с ним
  struct TreeNode {
   public:
    T value;  ///< значение хранящееся в узле дерева
    TreeNode* left;  ///< указатель на узел, находящийся слева от данного
    TreeNode* right;  ///< указатель на узел, находящийся справа от данного
    TreeNode* parent;  ///< указатель на родительский узел
    bool isRed;  ///< цвет узла(не было смысла в данном случае создавать enum)

    /// @brief Вспомогательная рекурсивная функция для копирования дерева из
    /// другого узла в текущий узел
    /// @param other другой узел содержащий в себе дерево
    void copy_tree(TreeNode* other);
    /// @brief Функция для рекурсивного удаления дерева по данному узлу
    void delete_tree();
    /// @brief Функция, нужная для более понятного представления сына деда для
    /// большей читаемости кода
    /// @return возвращает указатель на неродительского сына деда
    TreeNode* uncle();
    /// @brief Функция, нужная для более понятного представления деда для
    /// большей читаемости кода
    /// @return возвращает указатель на parent->parent
    TreeNode* grandparent();
    /// @brief обмен цветами между текущим указателем и other
    /// @param other указатель на другой узел
    void swap_color(TreeNode* other);
    /// @brief Функция, нужная для более понятного представления деда для
    /// большей читаемости кода
    /// @return возвращает указатель на другого сына родителя текущего элемента
    TreeNode* brother();
    /// @brief Поворот влево относительно текущего элемента(для него ничего не
    /// меняется, родитель становится на место деда, дед становится левым сыном
    /// родителя)
    void left_rotate();
    /// @brief Поворот вправо относительно текущего элемента(по аналогии с левым
    /// поворотом)
    void right_rotate();
    /// @brief Поворот влево, при котором текущий элемент становится на место
    /// родителя, а родитель становится левым сыном текущего элемента
    void small_left_rotate();
    /// @brief Поворот вправо по аналогии с small_left_rotate()
    void small_right_rotate();
    /// @brief Поворот с заменой цвета, вызывается при вставке элемента
    void rotate();
    /// @brief Балансировка при удалении текущего элемента с левым красным сыном
    /// брата(сам брат черный по правилу 3)
    void left_red();
    /// @brief Балансировка при удалении текущего элемента с правым красным
    /// сыном брата(сам брат черный по правилу 3)
    void right_red();
    /// @brief Балансировка при удалении текущего элемента с черными сыновьями
    /// брата
    void all_black();
    /// @brief Балансировка при удалении текущего элемента с красным братом
    void red_brother();
    /// @brief Балансировка при удалении текущего элемента без брата
    void null_brother();
    /// @brief Функция балансирующая дерево при удалении из него элемента
    void erase_fix();
    /// @brief Функция удаляющая элемент с одним/нулем детьми(лишающая текущий
    /// элемент всех связей)
    void erase_no_siblings();
    /// @brief Функция меняющая значение текущего элемента и другого(нужна при
    /// поиске элемента для удаления)
    /// @param tmp Указатель на другой элемент
    void swap_vals(TreeNode* tmp);
    /// @brief Функция балансирующая дерево при вставке элемента
    void insert_fix();
    /// @brief Конструктор инициализирующий новый узел(все связи nullptr,
    /// значение T())
    TreeNode();
    /// @brief Конструктор инициализирующий новый узел(все связи nullptr,
    /// значение val)
    /// @param val Значение вновь созданного узла
    TreeNode(T val);
    /// @brief Копирует дерево из узла other(с помощью функции copy_tree())
    /// @param other Узел в котором хранится дерево
    TreeNode(TreeNode& other);
    /// @brief То же самое что и копирование, только с лишением элемента other
    /// всех связей и удалением
    /// @param other Узел в котором хранится дерево
    TreeNode(const TreeNode&& other);
    /// @brief Деструктор TreeNode который рекурсивно удаляет все элементы,
    /// имеющие связи с данным
    ~TreeNode();
    /// @brief Копирование присваиванием
    /// @param other Узел в котором хранится дерево
    /// @return Ссылку на узел, в котором хранится новое дерево(скопированное с
    /// помощью copy_tree())
    TreeNode& operator=(TreeNode& other);
    /// @brief Вспомогательная функция нужная для большей читаемости
    /// @return Возвращает указатель на наиболее левый узел для текущего
    TreeNode* most_left();
    /// @brief Вспомогательная функция нужная для большей читаемости
    /// @return Возвращает указатель на наиболее правый узел для текущего
    TreeNode* most_right();
    /// @brief Засовывает значение в дерево
    /// @param val Значение которое нужно расположить в дереве
    /// @param size Ссылка на параметр size_ который будет увеличиваться если
    /// получилось положить в дерево новое значение
    void push(T val, size_t& size);
    /// @brief Вспомогательная функция требующаяся для функции at()(находит val
    /// и выкидывает exception если не нашла)
    /// @param val Значение которое нужно найти
    /// @return Возвращает ссылку на найденное значение
    T& finding_value_search(T val);
    /// @brief Удаление по значению
    /// @param val значение которое нужно удалить
    void erase(T val);
    /// @brief Удаление по указателю
    /// @param tmp Указатель на значение которое нужно удалить
    void erase(TreeNode* tmp);
    /// @brief Поиск узла в бинарном дереве(вспомогательная функция нужная для
    /// удаления и для функций at())
    /// @param val Значение которое нужно найти
    /// @return Возвращает nullptr, если ничего не найдено и указатель на узел,
    /// если в нем хранится val
    TreeNode* node_search(T val);
    /// @brief Вспомогательная функция для большей читаемости
    /// @return возвращает true если справа от текущего узла ненулевой указатель
    bool have_right();
    /// @brief Вспомогательная функция для большей читаемости
    /// @return возвращает true если слева от текущего узла ненулевой указатель
    bool have_left();
  };
  TreeNode* root_;  ///< указатель на корневой узел дерева
  size_t size_;  ///< количество элементов в дереве

  /// @brief функция позволяющая найти корень дерева
  void find_root();

 public:
  /// @brief итератор позволяющий проходить по дереву как по отсортированному
  /// массиву
  class TreeIterator {
   private:
    TreeNode* current_ = nullptr;  ///< указатель на текущий элемент
    TreeNode* root_ = nullptr;  ///< указатель на root_ дерева
   public:
    /// @brief Инкремент с префиксной записью
    /// @return Возвращает ссылку на следующий элемент итератора, current_
    /// увеличивается
    TreeIterator& operator++();
    /// @brief Инкремент с постфиксной записью
    /// @param
    /// @return Возвращает итератор текущего элемента, увеличивая current_
    TreeIterator operator++(int);
    /// @brief Декремент с префиксной записью
    /// @return Возвращает ссылку на предыдущий элемент итератора, current_
    /// увеличивается
    TreeIterator& operator--();
    /// @brief Декремент с постфиксной записью
    /// @param
    /// @return Возвращает итератор текущего элемента, уменьшая current_
    TreeIterator operator--(int);
    /// @brief Оператор присваивания копированием
    /// @param
    /// @return Возвращает ссылку на новый итератор
    TreeIterator& operator=(TreeIterator&);
    /// @brief Оператор присваивания перемещением
    /// @param
    /// @return Возвращает ссылку на новый итератор
    TreeIterator& operator=(TreeIterator&&);
    /// @brief Оператор сравнения
    /// @param
    /// @return Возвращает true при равенстве итераторов
    bool operator==(const TreeIterator&) const;
    /// @brief Оператор сравнения
    /// @param
    /// @return Возвращает true если итераторы не равны
    bool operator!=(const TreeIterator&) const;
    /// @brief Оператор получения ссылки из итератора
    /// @return Возвращает значение
    T& operator*() const;
    /// @brief Оператор получения указателя на итератор
    /// @return Возвращает указатель
    const T* operator->() const;
    /// @brief Инициализация всего nullptr
    TreeIterator();
    /// @brief Конструктор
    /// @param other Текущий элемент
    /// @param root Корень дерева
    TreeIterator(TreeNode* root, TreeNode* other = nullptr);
    /// @brief Конструктор копирующий
    /// @param other ссылка на другой итератор
    TreeIterator(TreeIterator& other);
    /// @brief Конструктор перемещающий
    /// @param other ссылка на другой итератор
    TreeIterator(TreeIterator&& other);
  };
  /// @brief Конструктор дерева без параметров
  Tree();
  /// @brief Конструктор дерева инициализирующий root_ значением val
  /// @param val значение в корне
  Tree(T val);
  /// @brief Конструктор дерева копирующий его рекурсивно из другого
  /// @param other другое дерево
  Tree(const Tree& other);
  /// @brief Конструктор дерева, перемещающий его рекурсивно из другого
  /// @param other другое дерево
  Tree(Tree&& other);
  /// @brief Деструктор рекурсивно уничтожающий дерево
  ~Tree();
  /// @brief Уничтожает дерево, при этом в него можно продолжать пушить
  void clear();
  /// @brief Присваивание копированием
  /// @param other другое дерево
  /// @return новое дерево
  Tree<T>& operator=(const Tree& other);
  /// @brief Присваивание перемещением
  /// @param other другое дерево
  /// @return новое дерево
  Tree<T>& operator=(Tree&& other);
  /// @brief Пуш по значению
  /// @param val значение
  void push(T val);
  /// @brief Удаление элемента из дерева
  /// @param val Удаляемое значение
  void erase(T val);
  /// @brief Удаление элемента по указателю
  /// @param node Указатель на ноду которую нужно удалить
  void erase(TreeNode* node);
  /// @brief Функция, которая если не находит val, пушит его увеличивая size
  /// @param val значение которое нужно найти
  /// @return возвращает ссылку на запушенное значение
  T& pushing_search(T val);
  /// @brief Функция которая если не находит val выкидывает exception
  /// @param val значение которое нужно найти
  /// @return возвращает ссылку на запушенное значение
  T& finding_search(T val);
  /// @brief Проверяет, содержится ли val в дереве
  /// @param val значение которое нужно проверить
  /// @return true если содержит val, false если нет
  bool contains(T val);
  /// @brief количество элементов содержащихся в дереве
  /// @return внутренний параметр size_
  size_t size();
  /// @brief
  /// @return возвращает true если дерево пустое
  bool empty();
  /// @brief поиск node содержащей val
  /// @param
  /// @return возращает итератор содержащий значение
  TreeIterator search(T val);
  /// @brief
  /// @return Возвращает итератор начала дерева
  TreeIterator begin();
  /// @brief
  /// @return Возвращает итератор конца дерева
  TreeIterator end();
  class ConstTreeIterator {
   private:
    TreeNode* current_ = nullptr;  ///< указатель на текущий элемент
    TreeNode* root_ = nullptr;  ///< указатель на root_ дерева
   public:
    /// @brief Инкремент с префиксной записью
    /// @return Возвращает ссылку на следующий элемент итератора, current_
    /// увеличивается
    ConstTreeIterator& operator++();
    /// @brief Инкремент с постфиксной записью
    /// @param
    /// @return Возвращает итератор текущего элемента, увеличивая current_
    ConstTreeIterator operator++(int);
    /// @brief Декремент с префиксной записью
    /// @return Возвращает ссылку на предыдущий элемент итератора, current_
    /// увеличивается
    ConstTreeIterator& operator--();
    /// @brief Декремент с постфиксной записью
    /// @param
    /// @return Возвращает итератор текущего элемента, уменьшая current_
    ConstTreeIterator operator--(int);
    /// @brief Оператор присваивания копированием
    /// @param
    /// @return Возвращает ссылку на новый итератор
    ConstTreeIterator& operator=(ConstTreeIterator&);
    /// @brief Оператор присваивания перемещением
    /// @param
    /// @return Возвращает ссылку на новый итератор
    ConstTreeIterator& operator=(ConstTreeIterator&&);
    /// @brief Оператор сравнения
    /// @param
    /// @return Возвращает true при равенстве итераторов
    bool operator==(const ConstTreeIterator&) const;
    /// @brief Оператор сравнения
    /// @param
    /// @return Возвращает true если итераторы не равны
    bool operator!=(const ConstTreeIterator&) const;
    /// @brief Оператор получения ссылки из итератора
    /// @return Возвращает значение
    const T& operator*() const;
    /// @brief Оператор получения указателя на итератор
    /// @return Возвращает указатель
    const T* operator->() const;
    /// @brief Инициализация всего nullptr
    ConstTreeIterator();
    /// @brief Конструктор
    /// @param other Текущий элемент
    /// @param root Корень дерева
    ConstTreeIterator(TreeNode* root, TreeNode* other = nullptr);
    /// @brief Конструктор копирующий
    /// @param other ссылка на другой итератор
    ConstTreeIterator(ConstTreeIterator& other);
    /// @brief Конструктор перемещающий
    /// @param other ссылка на другой итератор
    ConstTreeIterator(ConstTreeIterator&& other);
  };
  /// @brief
  /// @return Возвращает итератор начала дерева константного итератора
  ConstTreeIterator cbegin() const;
  /// @brief
  /// @return Возвращает итератор конца дерева константного итератора
  ConstTreeIterator cend() const;
  /// @brief
  /// @return возвращает итератор конкретной ноды со значением val либо end()
  /// если val нет
  ConstTreeIterator csearch(T val) const;
};
}  // namespace s21
#include "../templates/s21_tree.tpp"
#endif