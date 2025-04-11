#include <iostream>

#include "../include/s21_tree.h"
namespace s21 {
template <typename T>
void Tree<T>::TreeNode::copy_tree(TreeNode* other) {
  if (other) {
    parent = other->parent;
    value = other->value;
    isRed = other->isRed;
    if (other->left) {
      left = new TreeNode;
      left->copy_tree(other->left);
    }
    if (other->right) {
      right = new TreeNode;
      right->copy_tree(other->right);
    }
  }
}
template <typename T>
void Tree<T>::TreeNode::delete_tree() {
  if (left) {
    delete left;
    left = nullptr;
  }
  if (right) {
    delete right;
    right = nullptr;
  }
  parent = nullptr;
}
template <typename T>
typename Tree<T>::TreeNode* Tree<T>::TreeNode::uncle() {
  if ((parent) && (parent->parent)) {
    if (parent->parent->left == parent)
      return parent->parent->right;
    else
      return parent->parent->left;
  }
  return nullptr;
}
template <typename T>
typename Tree<T>::TreeNode* Tree<T>::TreeNode::grandparent() {
  if (parent) return parent->parent;
  return nullptr;
}
template <typename T>
void Tree<T>::TreeNode::swap_color(TreeNode* other) {
  bool tmp = other->isRed;
  other->isRed = isRed;
  isRed = tmp;
}
template <typename T>
typename Tree<T>::TreeNode* Tree<T>::TreeNode::brother() {
  if (parent) {
    if (this == parent->right)
      return parent->left;
    else
      return parent->right;
  }
  return parent;
}
template <typename T>
void Tree<T>::TreeNode::left_rotate() {
  TreeNode* grandparent_ = grandparent();
  parent->parent = grandparent_->parent;

  grandparent_->right = parent->left;
  if (grandparent_->parent) {
    if (grandparent_->parent->right == grandparent_)
      grandparent_->parent->right = parent;
    else
      grandparent_->parent->left = parent;
  }
  grandparent_->parent = parent;
  if (parent->left) parent->left->parent = grandparent_;
  parent->left = grandparent_;
}
template <typename T>
void Tree<T>::TreeNode::right_rotate() {
  TreeNode* grandparent_ = grandparent();
  parent->parent = grandparent_->parent;
  grandparent_->left = parent->right;
  if (grandparent_->parent) {
    if (grandparent_->parent->right == grandparent_)
      grandparent_->parent->right = parent;
    else
      grandparent_->parent->left = parent;
  }
  grandparent_->parent = parent;
  if (parent->right) parent->right->parent = grandparent_;

  parent->right = grandparent_;
}
template <typename T>
void Tree<T>::TreeNode::small_left_rotate() {
  TreeNode* grandparent_ = grandparent();

  if (parent) {
    parent->parent = this;
    parent->right = left;
  }
  if (left) left->parent = parent;
  left = parent;

  parent = grandparent_;

  if (grandparent_->left == left)
    parent->left = this;
  else if (grandparent_->right == left)
    parent->right = this;
}
template <typename T>
void Tree<T>::TreeNode::small_right_rotate() {
  TreeNode* grandparent_ = grandparent();

  if (parent) {
    parent->parent = this;
    parent->left = right;
  }
  if (right) right->parent = parent;

  right = parent;
  parent = grandparent_;

  if (grandparent_->left == right)
    parent->left = this;
  else if (grandparent_->right == right)
    parent->right = this;
}
template <typename T>
void Tree<T>::TreeNode::rotate() {
  TreeNode* grandparent_ = grandparent();
  parent->swap_color(grandparent_);
  if (this == parent->right && parent == grandparent_->right) {
    left_rotate();
  } else if (this == parent->left && parent == grandparent_->left) {
    right_rotate();
  }
}
template <typename T>
void Tree<T>::TreeNode::left_red() {
  if (this == parent->left) {
    brother()->left->swap_color(brother());
    brother()->left->small_right_rotate();
    right_red();
  } else {
    parent->swap_color(brother());
    brother()->left->isRed = false;
    brother()->left->right_rotate();
  }
}
template <typename T>
void Tree<T>::TreeNode::right_red() {
  if (this == parent->left) {
    parent->swap_color(brother());
    brother()->right->isRed = false;
    brother()->right->left_rotate();
  } else {
    brother()->right->swap_color(brother());
    brother()->right->small_left_rotate();
    left_red();
  }
}
template <typename T>
void Tree<T>::TreeNode::all_black() {
  brother()->isRed = true;
  if (parent->isRed)
    parent->isRed = false;
  else
    parent->erase_fix();
}
template <typename T>
void Tree<T>::TreeNode::red_brother() {
  brother()->swap_color(parent);
  if (this == parent->left)
    brother()->right->left_rotate();
  else
    brother()->left->right_rotate();
  erase_fix();
}
template <typename T>
void Tree<T>::TreeNode::null_brother() {
  parent->isRed = false;
  parent->erase_fix();
}
template <typename T>
void Tree<T>::TreeNode::erase_fix() {
  if (parent && !isRed) {
    if (!brother()) {
      null_brother();
    } else {
      if (!(brother()->isRed)) {
        if (brother()->right && brother()->right->isRed) {
          right_red();
        } else if (brother()->left && brother()->left->isRed) {
          left_red();
        } else {
          all_black();
        }
      } else {
        red_brother();
      }
    }
  }
}
template <typename T>
void Tree<T>::TreeNode::erase_no_siblings() {
  if (!isRed) erase_fix();
  if (parent && (this == parent->left))
    parent->left = left ? left : right;
  else if (parent)
    parent->right = left ? left : right;
  if (left) {
    left->parent = parent;
    left = nullptr;
  } else if (right) {
    right->parent = parent;
    right = nullptr;
  }
  parent = nullptr;
}
template <typename T>
void Tree<T>::TreeNode::swap_vals(TreeNode* tmp) {
  T val = value;
  value = tmp->value;
  tmp->value = val;
}
template <typename T>
void Tree<T>::TreeNode::insert_fix() {
  isRed = true;
  if (parent == nullptr) {
    isRed = false;
  } else if (parent->isRed) {
    TreeNode* uncle_ = uncle();
    TreeNode* grandparent_ = grandparent();
    if ((uncle_) && (uncle_->isRed)) {
      parent->isRed = false;
      uncle_->isRed = false;
      grandparent_->isRed = true;
      grandparent_->insert_fix();
    } else {
      if ((this == parent->right) && (parent == grandparent_->left)) {
        small_left_rotate();
        left->rotate();
      } else if ((this == parent->left) && (parent == grandparent_->right)) {
        small_right_rotate();
        right->rotate();
      } else {
        rotate();
      }
    }
  }
}
template <typename T>
Tree<T>::TreeNode::TreeNode() {
  left = nullptr;
  right = nullptr;
  parent = nullptr;
  value = T();
  isRed = false;
}
template <typename T>
Tree<T>::TreeNode::TreeNode(T val) {
  left = nullptr;
  right = nullptr;
  parent = nullptr;
  value = val;
  isRed = false;
}
template <typename T>
Tree<T>::TreeNode::TreeNode(TreeNode& other) : TreeNode() {
  copy_tree(&other);
}
template <typename T>
Tree<T>::TreeNode::TreeNode(const TreeNode&& other) : TreeNode(other) {
  other.parent = nullptr;
  other.left = nullptr;
  other.right = nullptr;
  other.value = 0;
  other.isRed = false;
}
template <typename T>
Tree<T>::TreeNode::~TreeNode() {
  delete_tree();
}
template <typename T>
typename Tree<T>::TreeNode& Tree<T>::TreeNode::operator=(TreeNode& other) {
  copy_tree(other.left);
  return *this;
}
template <typename T>
typename Tree<T>::TreeNode* Tree<T>::TreeNode::most_left() {
  TreeNode* tmp = this;
  while (tmp->left) tmp = tmp->left;
  return tmp;
}
template <typename T>
typename Tree<T>::TreeNode* Tree<T>::TreeNode::most_right() {
  TreeNode* tmp = this;
  while (tmp->right) tmp = tmp->right;
  return tmp;
}
template <typename T>
void Tree<T>::TreeNode::push(T val, size_t& size) {
  if (val < value) {
    if (left)
      left->push(val, size);
    else {
      left = new TreeNode(val);
      left->parent = this;
      left->insert_fix();
      size++;
    }
  } else if (val > value) {
    if (right)
      right->push(val, size);
    else {
      right = new TreeNode(val);
      right->parent = this;
      right->insert_fix();
      size++;
    }
  } else {
    value = val;
  }
}
template <typename T>
T& Tree<T>::TreeNode::finding_value_search(T val) {
  TreeNode* tmp = node_search(val);
  if (tmp == nullptr) {
    throw std::out_of_range("no value");
  }
  return tmp->value;
}
template <typename T>
void Tree<T>::TreeNode::erase(T val) {
  TreeNode* tmp = node_search(val);
  erase(tmp);
}
template <typename T>
void Tree<T>::TreeNode::erase(TreeNode* tmp) {
  if (tmp == nullptr) throw std::out_of_range("No value on this key!");
  if ((tmp->left && tmp->right) || (tmp->left || tmp->right)) {
    TreeNode* min_right = tmp->right ? tmp->right->most_left() : nullptr;
    TreeNode* max_left = tmp->left ? tmp->left->most_right() : nullptr;
    TreeNode* erased_node = max_left && max_left->isRed ? max_left : min_right;
    if (!(erased_node)) {
      erased_node = min_right && min_right->isRed ? min_right : max_left;
    }
    tmp->swap_vals(erased_node);
    erased_node->erase_no_siblings();
    delete erased_node;
  } else {
    tmp->erase_no_siblings();
    delete tmp;
  }
}
template <typename T>
typename Tree<T>::TreeNode* Tree<T>::TreeNode::node_search(T val) {
  TreeNode* tmp = this;
  bool flag = false;
  while ((tmp) && (!flag)) {
    if (val < tmp->value)
      tmp = tmp->left;
    else if (val > tmp->value)
      tmp = tmp->right;
    else
      flag = true;
  }
  return tmp;
}
template <typename T>
bool Tree<T>::TreeNode::have_right() {
  return right != nullptr;
}
template <typename T>
bool Tree<T>::TreeNode::have_left() {
  return left != nullptr;
}
template <typename T>
void Tree<T>::find_root() {
  while (root_->parent) root_ = root_->parent;
}
template <typename T>
Tree<T>::Tree() : root_(nullptr), size_(0) {}
template <typename T>
Tree<T>::Tree(T val) : root_(new TreeNode(val)), size_(1) {}
template <typename T>
Tree<T>::Tree(const Tree& other) {
  if (other.root_)
    root_ = new TreeNode(*(other.root_));
  else
    root_ = nullptr;
  size_ = other.size_;
}
template <typename T>
Tree<T>::Tree(Tree&& other) : root_(other.root_), size_(other.size_) {
  other.root_ = nullptr;
  other.size_ = 0;
}
template <typename T>
Tree<T>::~Tree() {
  clear();
}
template <typename T>
void Tree<T>::clear() {
  delete root_;
  root_ = nullptr;
  size_ = 0;
}
template <typename T>
Tree<T>& Tree<T>::operator=(const Tree& other) {
  if (root_) {
    delete root_;
    root_ = nullptr;
  }
  if (other.root_)
    root_ = new TreeNode(*(other.root_));
  else
    root_ = nullptr;
  size_ = other.size_;
  return *this;
}
template <typename T>
Tree<T>& Tree<T>::operator=(Tree&& other) {
  if (this != &other) {
    root_ = other.root_;
    size_ = other.size_;
    other.root_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}
template <typename T>
void Tree<T>::push(T val) {
  if (size_ == 0) {
    root_ = new TreeNode(val);
    size_ = 1;
  } else
    root_->push(val, size_);
  find_root();
}
template <typename T>
void Tree<T>::erase(T val) {
  if (size_ == 1 && (val == root_->value)) {
    delete root_;
    root_ = nullptr;
    size_ = 0;
  } else if (root_) {
    root_->erase(val);
    find_root();
    size_--;
  }
}
template <typename T>
void Tree<T>::erase(typename Tree<T>::TreeNode* node) {
  if (node) erase(node->value);
}
template <typename T>
T& Tree<T>::pushing_search(T val) {
  if (root_) {
    TreeNode* tmp = root_->node_search(val);
    if (tmp == nullptr) {
      push(val);
      return (root_->node_search(val))->value;
    }
    return tmp->value;
  } else {
    root_ = new TreeNode(val);
    size_++;
    return root_->value;
  }
}
template <typename T>
typename Tree<T>::TreeIterator Tree<T>::search(T val) {
  return TreeIterator(root_, root_->node_search(val));
}
template <typename T>
T& Tree<T>::finding_search(T val) {
  return root_->finding_value_search(val);
}
template <typename T>
Tree<T>::TreeIterator::TreeIterator(typename Tree<T>::TreeNode* root,
                                    typename Tree<T>::TreeNode* other)
    : current_(other), root_(root){};
template <typename T>
Tree<T>::TreeIterator::TreeIterator(typename Tree<T>::TreeIterator& other)
    : current_(other.current_), root_(other.root_){};
template <typename T>
Tree<T>::TreeIterator::TreeIterator() : current_(nullptr), root_(nullptr){};
template <typename T>
T& Tree<T>::TreeIterator::operator*() const {
  if (current_ == nullptr) {
    throw std::out_of_range("Iterator is invalid");
  }
  return current_->value;
}
template <typename T>
const T* Tree<T>::TreeIterator::operator->() const {
  if (current_ == nullptr) {
    throw std::out_of_range("Iterator is invalid");
  }
  return &current_->value;
}
template <typename T>
typename Tree<T>::TreeIterator& Tree<T>::TreeIterator::operator++() {
  if (current_ == nullptr) return *this;
  if (current_->right) {
    current_ = current_->right;
    while (current_->left) current_ = current_->left;
  } else {
    while ((current_->parent) && (current_ == current_->parent->right))
      current_ = current_->parent;
    current_ = current_->parent;
  }
  return *this;
}

template <typename T>
typename Tree<T>::TreeIterator& Tree<T>::TreeIterator::operator--() {
  if (current_ == root_->most_left()) {
    current_ = nullptr;
    return *this;
  }
  if (current_ == nullptr && root_) {
    current_ = root_->most_right();
    return *this;
  }
  if (current_->left) {
    current_ = current_->left;
    while (current_->right) current_ = current_->right;
  } else {
    while (current_ == current_->parent->left) current_ = current_->parent;
    current_ = current_->parent;
  }
  return *this;
}
template <typename T>
bool Tree<T>::contains(T val) {
  return root_->node_search(val) != nullptr;
}
template <typename T>
size_t Tree<T>::size() {
  return size_;
}
template <typename T>
bool Tree<T>::empty() {
  return size_ == 0;
}
template <typename T>
typename Tree<T>::TreeIterator Tree<T>::begin() {
  if (root_ == nullptr) return TreeIterator(root_);
  return TreeIterator(root_, root_->most_left());
}
template <typename T>
typename Tree<T>::TreeIterator Tree<T>::end() {
  return TreeIterator(root_);
}
template <typename T>
bool Tree<T>::TreeIterator::operator==(
    const Tree<T>::TreeIterator& other) const {
  return current_ == other.current_ && root_ == other.root_;
}
template <typename T>
bool Tree<T>::TreeIterator::operator!=(
    const Tree<T>::TreeIterator& other) const {
  return current_ != other.current_ || root_ != other.root_;
}
template <typename T>
typename Tree<T>::TreeIterator& Tree<T>::TreeIterator::operator=(
    typename Tree<T>::TreeIterator& other) {
  if (this != &other) {
    current_ = other.current_;
    root_ = other.root_;
  }
  return *this;
}
template <typename T>
typename Tree<T>::TreeIterator& Tree<T>::TreeIterator::operator=(
    typename Tree<T>::TreeIterator&& other) {
  if (this != &other) {
    current_ = other.current_;
    root_ = other.root_;
  }
  other.current_ = nullptr;
  other.root_ = nullptr;
  return *this;
}
template <typename T>
Tree<T>::TreeIterator::TreeIterator(typename Tree<T>::TreeIterator&& other) {
  current_ = other.current_;
  root_ = other.root_;
  other.current_ = nullptr;
  other.root_ = nullptr;
}
template <typename T>
typename Tree<T>::TreeIterator Tree<T>::TreeIterator::operator++(int) {
  TreeIterator temp(root_, current_);
  ++(*this);
  return temp;
}
template <typename T>
typename Tree<T>::TreeIterator Tree<T>::TreeIterator::operator--(int) {
  TreeIterator temp(root_, current_);
  --(*this);
  return temp;
}
template <typename T>
Tree<T>::ConstTreeIterator::ConstTreeIterator(typename Tree<T>::TreeNode* root,
                                              typename Tree<T>::TreeNode* other)
    : current_(other), root_(root){};
template <typename T>
Tree<T>::ConstTreeIterator::ConstTreeIterator(
    typename Tree<T>::ConstTreeIterator& other)
    : current_(other.current_), root_(other.root_){};
template <typename T>
Tree<T>::ConstTreeIterator::ConstTreeIterator()
    : current_(nullptr), root_(nullptr){};
template <typename T>
typename Tree<T>::ConstTreeIterator Tree<T>::cbegin() const {
  if (root_ == nullptr) return ConstTreeIterator(root_);
  return ConstTreeIterator(root_, root_->most_left());
}
template <typename T>
typename Tree<T>::ConstTreeIterator Tree<T>::cend() const {
  return ConstTreeIterator(root_);
}
template <typename T>
bool Tree<T>::ConstTreeIterator::operator==(
    const Tree<T>::ConstTreeIterator& other) const {
  return current_ == other.current_ && root_ == other.root_;
}
template <typename T>
bool Tree<T>::ConstTreeIterator::operator!=(
    const Tree<T>::ConstTreeIterator& other) const {
  return current_ != other.current_ || root_ != other.root_;
}
template <typename T>
typename Tree<T>::ConstTreeIterator& Tree<T>::ConstTreeIterator::operator=(
    typename Tree<T>::ConstTreeIterator& other) {
  if (this != &other) {
    current_ = other.current_;
    root_ = other.root_;
  }
  return *this;
}
template <typename T>
typename Tree<T>::ConstTreeIterator& Tree<T>::ConstTreeIterator::operator=(
    typename Tree<T>::ConstTreeIterator&& other) {
  if (this != &other) {
    current_ = other.current_;
    root_ = other.root_;
  }
  other.current_ = nullptr;
  other.root_ = nullptr;
  return *this;
}
template <typename T>
Tree<T>::ConstTreeIterator::ConstTreeIterator(
    typename Tree<T>::ConstTreeIterator&& other) {
  current_ = other.current_;
  root_ = other.root_;
  other.current_ = nullptr;
  other.root_ = nullptr;
}
template <typename T>
typename Tree<T>::ConstTreeIterator& Tree<T>::ConstTreeIterator::operator++() {
  if (current_ == nullptr) return *this;
  if (current_->right) {
    current_ = current_->right;
    while (current_->left) current_ = current_->left;
  } else {
    while ((current_->parent) && (current_ == current_->parent->right))
      current_ = current_->parent;
    current_ = current_->parent;
  }
  return *this;
}
template <typename T>
typename Tree<T>::ConstTreeIterator Tree<T>::ConstTreeIterator::operator++(
    int) {
  ConstTreeIterator temp(root_, current_);
  ++(*this);
  return temp;
}
template <typename T>
typename Tree<T>::ConstTreeIterator& Tree<T>::ConstTreeIterator::operator--() {
  if (current_ == root_->most_left()) {
    current_ = nullptr;
    return *this;
  }
  if (current_ == nullptr && root_) {
    current_ = root_->most_right();
    return *this;
  }
  if (current_->left) {
    current_ = current_->left;
    while (current_->right) current_ = current_->right;
  } else {
    while (current_ == current_->parent->left) current_ = current_->parent;
    current_ = current_->parent;
  }
  return *this;
}
template <typename T>
typename Tree<T>::ConstTreeIterator Tree<T>::ConstTreeIterator::operator--(
    int) {
  ConstTreeIterator temp(root_, current_);
  --(*this);
  return temp;
}
template <typename T>
const T& Tree<T>::ConstTreeIterator::operator*() const {
  if (current_ == nullptr) {
    throw std::out_of_range("Iterator is invalid");
  }
  return current_->value;
}
template <typename T>
const T* Tree<T>::ConstTreeIterator::operator->() const {
  if (current_ == nullptr) {
    throw std::out_of_range("Iterator is invalid");
  }
  return &current_->value;
}
template <typename T>
typename Tree<T>::ConstTreeIterator Tree<T>::csearch(T val) const {
  auto it = Tree<T>::ConstTreeIterator(cbegin());
  while (it != cend()) {
    if (*it == val) break;
    it++;
  }
}
}  // namespace s21