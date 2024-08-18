#include <limits>

#include "../s21_stack/s21_stack.h"
#ifndef TREE_CPP
#define TREE_CPP

namespace s21 {

template <typename Key, typename Value>
class Tree {
 public:
  class Iterator;
  class Const_Iterator;
  using key_type = Key;
  using value_type = Value;
  using pair_type = std::pair<key_type, value_type>;
  using reference = Value&;
  using const_reference = const Value&;
  using iterator = Tree<Key, Value>::Iterator;
  using const_iterator = Tree<Key, Value>::Const_Iterator;
  using size_type = std::size_t;

  struct Node {
    key_type key;
    value_type value;
    size_type height;
    Node* left;
    Node* right;
    // Node(key_type k, value_type v) {key = k; value = v; height = 1; left =
    // nullptr; right = nullptr;
    // };
    Node(key_type k, value_type v)
        : key(k), value(v), height(1), left(nullptr), right(nullptr){};
  };

  Tree();
  Tree(key_type k, value_type v);
  Tree(std::initializer_list<key_type> const& items);
  Tree(std::initializer_list<pair_type> const& items);
  Tree(const Tree& other);
  Tree(Tree&& other);
  ~Tree();

  void __insert(key_type k, value_type v);
  void remove(key_type k);
  Node* find(key_type k);
  void print();
  void clean();

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  value_type& at(const key_type& key);
  value_type& operator[](const key_type& key);

  bool contains(const key_type& key);
  void erase(iterator pos);
  bool empty();
  void swap(Tree& other);
  void merge(Tree& other);
  size_type size();
  size_type max_size();

  Tree& operator=(const Tree& other);
  Tree& operator=(Tree&& other);

  std::pair<iterator, bool> insert(const pair_type& value);
  std::pair<iterator, bool> insert(const key_type& key, const value_type& obj);
  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const value_type& obj);

 private:
  Node* root;
  size_type height(Node* p);
  size_type _size(Node* p);
  int balance_factor(Node* p);
  void update_height(Node* p);
  Node* rotate_right(Node* p);
  Node* rotate_left(Node* q);
  Node* balance(Node* p);
  Node* _insert(Node* p, key_type k, value_type v);
  Node* find_min(Node* p);
  Node* remove_min(Node* p);
  Node* _remove(Node* p, key_type k);
  Node* _find(Node* p, key_type k);
  void _clean(Node* p);
  void assign(const Tree& other);
  void print_tree(Node* p, Node* parent);
};

template <typename Key, typename Value>
Tree<Key, Value>::Tree() {
  root = nullptr;
}

template <typename Key, typename Value>
Tree<Key, Value>::Tree(key_type k, value_type v) {
  root = new Node(k, v);
}

template <typename Key, typename Value>
Tree<Key, Value>::Tree(std::initializer_list<pair_type> const& items)
    : root(nullptr) {
  for (auto i = items.begin(); i != items.end(); ++i)
    __insert(i->first, i->second);
}

template <typename Key, typename Value>
Tree<Key, Value>::Tree(std::initializer_list<key_type> const& items)
    : root(nullptr) {
  for (auto i = items.begin(); i != items.end(); ++i) __insert(*i, *i);
}

template <typename Key, typename Value>
Tree<Key, Value>::Tree(const Tree& other) {
  root = nullptr;
  assign(other);
}

template <typename Key, typename Value>
Tree<Key, Value>::Tree(Tree&& other) {
  assign(other);
  other.clean();
}

template <typename Key, typename Value>
Tree<Key, Value>::~Tree() {}

// public methods

template <typename Key, typename Value>
void Tree<Key, Value>::__insert(key_type k, value_type v) {
  root = _insert(root, k, v);
}

template <typename Key, typename Value>
void Tree<Key, Value>::remove(key_type k) {
  root = _remove(root, k);
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Node* Tree<Key, Value>::find(key_type k) {
  if (!root) return nullptr;
  Node* result = _find(root, k);
  if (result)
    return result;
  else
    return nullptr;
}

template <typename Key, typename Value>
inline void Tree<Key, Value>::print() {
  print_tree(root, nullptr);
}

// private methods

template <typename Key, typename Value>
typename Tree<Key, Value>::size_type Tree<Key, Value>::height(Node* p) {
  return p ? p->height : 0;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::size_type Tree<Key, Value>::_size(Node* p) {
  if (!p) return 0;
  size_type left = p->left ? _size(p->left) : 0;
  size_type right = p->right ? _size(p->right) : 0;
  return left + right + 1;
}

template <typename Key, typename Value>
inline int Tree<Key, Value>::balance_factor(Node* p) {
  return height(p->right) - height(p->left);
}

template <typename Key, typename Value>
inline void Tree<Key, Value>::update_height(Node* p) {
  size_type height_left = height(p->left);
  size_type height_right = height(p->right);
  p->height = (height_left > height_right ? height_left : height_right) + 1;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Node* Tree<Key, Value>::rotate_right(Node* p) {
  Node* q = p->left;
  p->left = q->right;
  q->right = p;
  update_height(p);
  update_height(q);
  return q;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Node* Tree<Key, Value>::rotate_left(Node* q) {
  Node* p = q->right;
  q->right = p->left;
  p->left = q;
  update_height(q);
  update_height(p);
  return p;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Node* Tree<Key, Value>::balance(Node* p) {
  update_height(p);
  if (balance_factor(p) == 2) {
    if (balance_factor(p->right) < 0) p->right = rotate_right(p->right);
    return rotate_left(p);
  }
  if (balance_factor(p) == -2) {
    if (balance_factor(p->left) > 0) p->left = rotate_left(p->left);
    return rotate_right(p);
  }
  return p;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Node* Tree<Key, Value>::_insert(Node* p, key_type k,
                                                           value_type v) {
  if (!p) return new Node(k, v);
  if (k < p->key) {
    p->left = _insert(p->left, k, v);
  } else {
    p->right = _insert(p->right, k, v);
  }
  return balance(p);
}

template <typename Key, typename Value>
inline void Tree<Key, Value>::print_tree(Node* p, Node* parent) {
  if (parent)
    std::cout << "Parent: " << parent->key << "; Key: " << p->key
              << "; Value: " << p->value << "; height: " << p->height
              << "; BF: " << balance_factor(p) << std::endl;
  else
    std::cout << "Key: " << p->key << "; Value: " << p->value
              << "; height: " << p->height << "; BF: " << balance_factor(p)
              << std::endl;
  if (p->left) print_tree(p->left, p);
  if (p->right) print_tree(p->right, p);
}

template <typename Key, typename Value>
inline void Tree<Key, Value>::clean() {
  // if (root) _clean(root);
  if (root) {
    if (root->left) _clean(root->left);
    if (root->right) _clean(root->right);
    delete root;
    root = nullptr;
  }
}

template <typename Key, typename Value>
typename Tree<Key, Value>::iterator Tree<Key, Value>::begin() {
  return iterator(root);
}

template <typename Key, typename Value>
typename Tree<Key, Value>::iterator Tree<Key, Value>::end() {
  iterator res(root);
  return res.to_end(root);
}

template <typename Key, typename Value>
typename Tree<Key, Value>::const_iterator Tree<Key, Value>::cbegin() const {
  return const_iterator(root);
}

template <typename Key, typename Value>
typename Tree<Key, Value>::const_iterator Tree<Key, Value>::cend() const {
  const_iterator res(root);
  return res.to_end(root);
}

template <typename Key, typename Value>
typename Tree<Key, Value>::value_type& Tree<Key, Value>::at(
    const key_type& key) {
  Node* tmp = find(key);
  if (!tmp) throw std::out_of_range("at(key): No key or tree is empty.");
  return tmp->value;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::value_type& Tree<Key, Value>::operator[](
    const key_type& key) {
  Node* node = find(key);
  if (node) {
    return node->value;
  } else {
    __insert(key, Value());  // Вставляем новый элемент с ключом и значением по
                             // умолчанию для типа Value
    return find(key)->value;  // Возвращаем ссылку на значение нового элемента
  }
}

template <typename Key, typename Value>
inline bool Tree<Key, Value>::contains(const key_type& key) {
  Node* tmp = find(key);
  return tmp ? true : false;
}

template <typename Key, typename Value>
void Tree<Key, Value>::erase(iterator pos) {
  key_type key = pos.get_node()->key;
  remove(key);
}

template <typename Key, typename Value>
inline bool Tree<Key, Value>::empty() {
  return root ? false : true;
}

template <typename Key, typename Value>
void Tree<Key, Value>::swap(Tree& other) {
  Tree tmp(other);
  other.clean();
  other.root = nullptr;
  other.assign(*this);
  clean();
  root = nullptr;
  assign(tmp);
  tmp.clean();
}

template <typename Key, typename Value>
void Tree<Key, Value>::merge(Tree& other) {
  assign(other);
}

template <typename Key, typename Value>
typename Tree<Key, Value>::size_type Tree<Key, Value>::size() {
  return _size(root);
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Tree& Tree<Key, Value>::operator=(
    const Tree& other) {
  if (this != &other) {
    this->clean();
    // clean();
    root = nullptr;
    new (this) Tree(other);
  }
  return *this;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Tree& Tree<Key, Value>::operator=(Tree&& other) {
  if (this != &other) {
    this->clean();
    root = nullptr;
    new (this) Tree(std::move(other));
  }
  return *this;
}

template <typename Key, typename Value>
std::pair<typename Tree<Key, Value>::iterator, bool> Tree<Key, Value>::insert(
    const pair_type& value) {
  Node* tmp = find(value.first);
  bool result = false;
  if (!tmp) {
    __insert(value.first, value.second);
    result = true;
  }
  auto iter = begin();
  auto it_end = end();
  while (iter != it_end) {
    if (iter.get_node()->key == value.first) break;
    ++iter;
  }
  return std::pair<iterator, bool>(iter, result);
}

template <typename Key, typename Value>
std::pair<typename Tree<Key, Value>::iterator, bool> Tree<Key, Value>::insert(
    const key_type& key, const value_type& obj) {
  Node* tmp = find(key);
  bool result = false;
  if (!tmp) {
    __insert(key, obj);
    result = true;
  }
  auto iter = begin();
  auto it_end = end();
  while (iter != it_end) {
    if (iter.get_node()->key == key) break;
    ++iter;
  }
  return std::pair<iterator, bool>(iter, result);
}

template <typename Key, typename Value>
std::pair<typename Tree<Key, Value>::iterator, bool>
Tree<Key, Value>::insert_or_assign(const key_type& key, const value_type& obj) {
  Node* tmp = find(key);
  bool result = false;
  if (!tmp) {
    __insert(key, obj);
    result = true;
  }
  if (!result) {
    find(key)->value = obj;
    result = true;
  }
  auto iter = begin();
  auto it_end = end();
  while (iter != it_end) {
    if (iter.get_node()->key == key) break;
    ++iter;
  }
  return std::pair<iterator, bool>(iter, result);
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Node* Tree<Key, Value>::find_min(Node* p) {
  return p->left ? find_min(p->left) : p;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Node* Tree<Key, Value>::remove_min(Node* p) {
  if (p->left == nullptr) return p->right;
  p->left = remove_min(p->left);
  return balance(p);
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Node* Tree<Key, Value>::_remove(Node* p,
                                                           key_type k) {
  if (!p) return 0;
  if (k < p->key) {
    p->left = _remove(p->left, k);
  } else if (k > p->key) {
    p->right = _remove(p->right, k);
  } else {
    Node* left = p->left;
    Node* right = p->right;
    delete p;
    if (right == nullptr) return left;
    Node* min = find_min(right);
    min->right = remove_min(right);
    min->left = left;
    return balance(min);
  }
  return balance(p);
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Node* Tree<Key, Value>::_find(Node* p, key_type k) {
  if (p->key == k) {
    return p;
  } else if (k > p->key && p->right) {
    return _find(p->right, k);
  } else if (k < p->key && p->left) {
    return _find(p->left, k);
  }
  return nullptr;
}

template <typename Key, typename Value>
void Tree<Key, Value>::_clean(Node* p) {
  if (p) {
    _clean(p->left);
    _clean(p->right);
    delete p;
  }
}

template <typename Key, typename Value>
inline void Tree<Key, Value>::assign(const Tree<Key, Value>& other) {
  for (auto i = other.cbegin(); i != other.cend(); ++i) {
    const Node* tmp = i.get_node();
    this->__insert(tmp->key, tmp->value);
  }
}

template <class Key, class Value>
size_t Tree<Key, Value>::max_size() {
  size_t max_size = 0;
  max_size = std::numeric_limits<size_t>::max() /
             sizeof(typename s21::Tree<Key, Value>::Node) * 1.2;

  return max_size;
}

//
//
//
//

template <typename Key, typename Value>
class Tree<Key, Value>::Iterator {
 private:
  Node* begin;
  Node* ptr;
  Node* end;

  s21::stack<Node*> stack;
  s21::stack<Node*> prev_stack;

 protected:
  void left_to_stack(Node* node);
  Node* next();
  Node* prev();

  Node* get_min(Node* node);
  Node* get_max(Node* node);

 public:
  Iterator() = default;
  Iterator(Node* node);
  Iterator(const Iterator& it);
  ~Iterator() = default;

  Iterator& operator++();
  Iterator& operator--();
  Iterator operator++(int);
  Iterator operator--(int);

  Value& operator*();
  const Value& operator*() const;
  Value* operator->();
  const Value* operator->() const;

  bool operator==(const Iterator& other) const;
  bool operator!=(const Iterator& other) const;

  Iterator& operator=(const Iterator& it);

  const Key& get_ckey() const;
  const Node* get_node() const;
  Iterator to_end(Node* node);
};

template <typename Key, typename Value>
typename Tree<Key, Value>::Node* Tree<Key, Value>::Iterator::get_min(
    Node* node) {
  if (!node) return nullptr;
  if (node->left)
    return get_min(node->left);
  else
    return node;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Node* Tree<Key, Value>::Iterator::get_max(
    Node* node) {
  if (!node) return nullptr;
  if (node->right)
    return get_max(node->right);
  else
    return node;
}

template <typename Key, typename Value>
inline const Key& Tree<Key, Value>::Iterator::get_ckey() const {
  return ptr->key;
}

template <typename Key, typename Value>
const typename Tree<Key, Value>::Node* Tree<Key, Value>::Iterator::get_node()
    const {
  return ptr;
}

template <typename Key, typename Value>
inline void Tree<Key, Value>::Iterator::left_to_stack(Node* node) {
  while (node) {
    stack.push(node);
    node = node->left;
  }
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Node* Tree<Key, Value>::Iterator::next() {
  if (stack.empty()) return nullptr;
  Node* node = stack.top();
  stack.pop();
  prev_stack.push(node);
  left_to_stack(node->right);
  return node;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Node* Tree<Key, Value>::Iterator::prev() {
  if (prev_stack.empty()) return nullptr;
  Node* node = prev_stack.top();
  prev_stack.pop();
  stack.push(node);
  return node;
}

template <typename Key, typename Value>
Tree<Key, Value>::Iterator::Iterator(Node* node) {
  left_to_stack(node);
  ptr = next();
}

template <typename Key, typename Value>
Tree<Key, Value>::Iterator::Iterator(const Iterator& it)
    : ptr(it.ptr), stack(it.stack), prev_stack(it.prev_stack) {}

template <typename Key, typename Value>
typename Tree<Key, Value>::Iterator& Tree<Key, Value>::Iterator::operator++() {
  ptr = next();
  return *this;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Iterator& Tree<Key, Value>::Iterator::operator--() {
  ptr = prev();
  return *this;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Iterator Tree<Key, Value>::Iterator::operator++(
    int) {
  iterator it(*this);
  ++(*this);
  return it;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Iterator Tree<Key, Value>::Iterator::operator--(
    int) {
  iterator it(*this);
  --(*this);
  return it;
}

//
//
//
//
template <typename Key, typename Value>
Value& Tree<Key, Value>::Iterator::operator*() {
  return ptr->value;
}

template <typename Key, typename Value>
const Value& Tree<Key, Value>::Iterator::operator*() const {
  return ptr->value;
}

template <typename Key, typename Value>
Value* Tree<Key, Value>::Iterator::operator->() {
  return &(ptr->value);
}

template <typename Key, typename Value>
const Value* Tree<Key, Value>::Iterator::operator->() const {
  return &(ptr->value);
}

//
//
//
//

template <typename Key, typename Value>
bool Tree<Key, Value>::Iterator::operator==(const Iterator& other) const {
  return ptr == other.ptr;
}

template <typename Key, typename Value>
bool Tree<Key, Value>::Iterator::operator!=(const Iterator& other) const {
  return ptr != other.ptr;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Iterator& Tree<Key, Value>::Iterator::operator=(
    const Iterator& it) {
  if (this != &it) {
    ptr = it.ptr;
    stack = it.stack;
    prev_stack = it.prev_stack;
  }
  return *this;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Iterator Tree<Key, Value>::Iterator::to_end(
    Node* node) {
  iterator res(node);
  res.end = get_max(node);
  while (res.ptr != res.end) {
    ++res;
  }
  res.ptr = nullptr;
  return res;
}

//
//
//
//

template <typename Key, typename Value>
class Tree<Key, Value>::Const_Iterator {
 private:
  Node* end;

  s21::stack<Node*> stack;
  s21::stack<Node*> prev_stack;
  void left_to_stack(Node* node);
  Node* get_max(Node* node);
  Node* next();
  Node* prev();

 public:
  Node* ptr;  // from private
  Const_Iterator() = default;
  Const_Iterator(Node* node);
  Const_Iterator(const Const_Iterator& it) = default;

  Const_Iterator& operator++();
  Const_Iterator& operator--();
  Const_Iterator operator++(int);
  Const_Iterator operator--(int);

  bool operator==(const Const_Iterator& other) const;
  bool operator!=(const Const_Iterator& other) const;

  const Node* get_node() const;
  Const_Iterator to_end(Node* node);

  const Value& operator*() const { return ptr->value; }

  const Value* operator->() const { return &ptr->value; }

  friend void Tree::assign(const Tree& other);
  friend void Tree::erase(iterator pos);
};

template <typename Key, typename Value>
inline Tree<Key, Value>::Const_Iterator::Const_Iterator(Node* node) {
  left_to_stack(node);
  ptr = next();
}

template <typename Key, typename Value>
inline void Tree<Key, Value>::Const_Iterator::left_to_stack(Node* node) {
  while (node) {
    stack.push(node);
    node = node->left;
  }
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Node* Tree<Key, Value>::Const_Iterator::get_max(
    Node* node) {
  if (!node) return nullptr;
  if (node->right)
    return get_max(node->right);
  else
    return node;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Node* Tree<Key, Value>::Const_Iterator::next() {
  if (stack.empty()) return nullptr;
  Node* node = stack.top();
  stack.pop();
  prev_stack.push(node);
  left_to_stack(node->right);
  return node;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Node* Tree<Key, Value>::Const_Iterator::prev() {
  if (prev_stack.empty()) return nullptr;
  Node* node = prev_stack.top();
  prev_stack.pop();
  stack.push(node);
  return node;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Const_Iterator&
Tree<Key, Value>::Const_Iterator::operator++() {
  ptr = next();
  return *this;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Const_Iterator&
Tree<Key, Value>::Const_Iterator::operator--() {
  ptr = prev();
  return *this;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Const_Iterator
Tree<Key, Value>::Const_Iterator::operator++(int) {
  const_iterator it(*this);
  ++(*this);
  return it;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Const_Iterator
Tree<Key, Value>::Const_Iterator::operator--(int) {
  const_iterator it(*this);
  --(*this);
  return it;
}

template <typename Key, typename Value>
bool Tree<Key, Value>::Const_Iterator::operator==(
    const Const_Iterator& other) const {
  return ptr == other.ptr;
}

template <typename Key, typename Value>
bool Tree<Key, Value>::Const_Iterator::operator!=(
    const Const_Iterator& other) const {
  return ptr != other.ptr;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Const_Iterator
Tree<Key, Value>::Const_Iterator::to_end(Node* node) {
  const_iterator res(node);
  res.end = get_max(node);
  while (res.ptr != res.end) {
    ++res;
  }
  res.ptr = nullptr;
  return res;
}

template <typename Key, typename Value>
const typename Tree<Key, Value>::Node*
Tree<Key, Value>::Const_Iterator::get_node() const {
  return ptr;
}

}  // namespace s21
#endif  // TREE_CPP