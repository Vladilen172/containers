#include <limits>

#include "../../tree/include/s21_tree.h"
namespace s21 {
template <typename Key, typename T>
map<Key, T>::map() {
  tree_ = Tree<value_type>();
}
template <typename Key, typename T>
map<Key, T>::map(value_type pair) {
  tree_ = Tree<value_type>(pair);
}
template <typename Key, typename T>
map<Key, T>::map(std::initializer_list<value_type> const& items) {
  tree_ = Tree<value_type>();
  for (auto& item : items) {
    tree_.push(item);
  }
}
template <typename Key, typename T>
map<Key, T>::map(const map& m) : tree_(m.tree_) {}
template <typename Key, typename T>
map<Key, T>::map(map&& m) : map(m) {
  m.tree_.clear();
}
template <typename Key, typename T>
T& map<Key, T>::at(const Key& key) {
  return tree_.finding_search(pair(key, T())).second();
}
template <typename Key, typename T>
T& map<Key, T>::operator[](const Key& key) {
  return tree_.pushing_search(pair(key, T())).second();
}
template <typename Key, typename T>
map<Key, T>& map<Key, T>::operator=(const map<Key, T>& m) {
  if (this != &m) {
    tree_ = m.tree_;
  }
  return *this;
}
template <typename Key, typename T>
map<Key, T>& map<Key, T>::operator=(map<Key, T>&& m) {
  if (this != &m) {
    tree_ = m.tree_;
    m.tree_.clear();
  }
  return *this;
}
template <typename Key, typename T>
bool map<Key, T>::empty() {
  return tree_.size() == 0;
}
template <typename Key, typename T>
size_t map<Key, T>::size() {
  return tree_.size();
}
template <typename Key, typename T>
size_t map<Key, T>::max_size() {
  return std::numeric_limits<T>::max();
}
template <typename Key, typename T>
void map<Key, T>::clear() {
  tree_.clear();
}
template <typename Key, typename T>
void map<Key, T>::swap(map<Key, T>& other) {
  Tree<value_type> tmp1 = other.tree_;
  other.tree_ = tree_;
  tree_ = tmp1;
}
template <typename Key, typename T>
typename std::pair<typename map<Key, T>::MapIterator, bool> map<Key, T>::insert(
    const value_type& value) {
  size_t tmp = tree_.size();
  if (!(tree_.contains(value))) tree_.push(value);
  return std::make_pair(map<Key, T>::MapIterator(tree_.search(value)),
                        tree_.size() > tmp);
}
template <typename Key, typename T>
typename std::pair<typename map<Key, T>::MapIterator, bool> map<Key, T>::insert(
    const Key& key, const T& obj) {
  size_t tmp = tree_.Tree<value_type>::size();
  if (!(tree_.contains(pair(key, obj)))) tree_.push(pair(key, obj));
  return std::make_pair(
      map<Key, T>::MapIterator(tree_.Tree<value_type>::search(pair(key, obj))),
      tree_.Tree<value_type>::size() > tmp);
}
template <typename Key, typename T>
typename std::pair<typename map<Key, T>::MapIterator, bool>
map<Key, T>::insert_or_assign(const Key& key, const T& obj) {
  bool ret_val = !(tree_.contains(pair(key, obj)));
  tree_.push(pair(key, obj));
  return std::make_pair(
      map<Key, T>::MapIterator(tree_.Tree<value_type>::search(pair(key, obj))),
      ret_val);
}
template <typename Key, typename T>
void map<Key, T>::erase(map<Key, T>::MapIterator pos) {
  tree_.erase(*pos);
}
template <typename Key, typename T>
void map<Key, T>::merge(map<Key, T>& other) {
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
}
template <class Key, class T>
bool s21::map<Key, T>::contains(Key key) {
  return tree_.contains({key, T()});
}
}  // namespace s21