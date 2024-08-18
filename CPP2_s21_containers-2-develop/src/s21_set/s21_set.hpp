#include <tuple>
#include <vector>

#include "../s21_tree/s21_tree.hpp"
#include "../s21_vector/s21_vector.h"

namespace s21 {
template <typename Key>
class set {
 public:
  class Set_Iterator;
  class Const_Set_Iterator;
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = set<Key>::Set_Iterator;
  using const_iterator = Const_Set_Iterator;
  using size_type = std::size_t;

 private:
  Tree<key_type, value_type> _tree;

 public:
  set();
  set(std::initializer_list<value_type> const& items);
  set(const set& other);
  set(set&& other);
  ~set();

  set& operator=(const set& s);
  set& operator=(set&& s) noexcept;

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  template <typename... Args>
  vector<std::pair<typename set<Key>::iterator, bool>> insert_many(
      Args&&... args);

  bool empty();
  size_type size();
  size_type max_size();

  void clear();

  std::pair<iterator, bool> insert(const value_type& value);
  void erase(iterator pos);
  void swap(set& other);
  void merge(set& other);

  iterator find(const Key& key);
  bool contains(const Key& key);

  class Set_Iterator {
   public:
    using iterator = set<Key>::Set_Iterator;
    using tree_iterator = typename Tree<key_type, value_type>::Iterator;
    using const_tree_iterator =
        typename Tree<key_type, value_type>::Const_Iterator;
    Set_Iterator() = default;
    Set_Iterator(tree_iterator it);
    Set_Iterator(const_tree_iterator it);
    ~Set_Iterator() = default;

    Set_Iterator& operator++();
    Set_Iterator& operator--();
    Set_Iterator operator++(int);
    Set_Iterator operator--(int);

    Set_Iterator& operator=(const Set_Iterator& other);

    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;

    const_reference operator*() const;
    const value_type* operator->() const;

   private:
    tree_iterator it;
    friend void set<Key>::erase(iterator pos);
  };

  class Const_Set_Iterator {
   public:
    using tree_iterator = typename Tree<key_type, value_type>::Iterator;
    using const_iterator = Const_Set_Iterator;
    using const_tree_iterator =
        typename Tree<key_type, value_type>::Const_Iterator;
    Const_Set_Iterator() = default;
    Const_Set_Iterator(tree_iterator it);
    Const_Set_Iterator(const_tree_iterator it);
    ~Const_Set_Iterator() = default;

    Const_Set_Iterator& operator++();
    Const_Set_Iterator& operator--();
    Const_Set_Iterator operator++(int);
    Const_Set_Iterator operator--(int);

    bool operator==(const const_iterator& other) const;
    bool operator!=(const const_iterator& other) const;

    const_reference operator*() const;
    value_type* operator->() const;

   private:
    const_tree_iterator it;
  };
};

template <typename Key>
set<Key>::set() : _tree() {}

template <typename Key>
set<Key>::set(std::initializer_list<value_type> const& items) {
  _tree = Tree<key_type, value_type>();
  for (const value_type& item : items) {
    if (!contains(item)) insert(item);
  }
  // _tree = Tree<key_type, value_type>(items);
}

template <typename Key>
set<Key>::set(const set& other) {
  _tree = Tree<key_type, value_type>(other._tree);
}

template <typename Key>
set<Key>::set(set&& other) {
  _tree = std::move(other._tree);
}

template <typename Key>
set<Key>::~set() {
  // std::cout  <<  "Set destructor!" << std::endl;
  _tree.clean();
}

template <typename Key>
set<Key>& set<Key>::operator=(const set& s) {
  if (this == &s) {
    return *this;
  }
  _tree = s._tree;
  return *this;
}

template <typename Key>
set<Key>& set<Key>::operator=(set&& s) noexcept {
  if (this == &s) {
    return *this;
  }
  _tree = std::move(s._tree);
  return *this;
}

template <typename Key>
inline bool s21::set<Key>::empty() {
  return _tree.empty();
}

template <typename Key>
typename set<Key>::size_type set<Key>::size() {
  return _tree.size();
}

template <typename Key>
typename set<Key>::size_type set<Key>::max_size() {
  return _tree.max_size();
}

template <typename Key>
void set<Key>::clear() {
  _tree.clean();
  // _tree = Tree<key_type, value_type>();
}

template <typename Key>
void set<Key>::swap(set& other) {
  if (this == &other) throw std::invalid_argument("swap");
  _tree.swap(other._tree);
}

template <typename Key>
void set<Key>::merge(set& other) {
  // _tree.merge(other._tree);
  if (this == &other) throw std::invalid_argument("merge");
  for (auto it = other.begin(); it != other.end(); ++it) {
    if (!contains(*it)) insert(*it);
  }
}

template <typename Key>
void set<Key>::erase(iterator pos) {
  _tree.erase(pos.it);
}

template <typename Key>
typename set<Key>::iterator set<Key>::find(const Key& key) {
  auto node = _tree.find(key);
  if (node == nullptr) return end();
  auto iter = _tree.begin();
  auto it_end = _tree.end();
  while (iter != it_end) {
    if (iter.get_node()->key == key) break;
    ++iter;
  }
  return iterator(iter);
}

template <typename Key>
bool set<Key>::contains(const Key& key) {
  return _tree.contains(key);
}

template <typename Key>
inline set<Key>::Set_Iterator::Set_Iterator(tree_iterator it) : it(it) {}

//
//
//
//

template <typename Key>
inline set<Key>::Set_Iterator::Set_Iterator(const_tree_iterator it) : it(it) {}

template <typename Key>
typename set<Key>::Set_Iterator& set<Key>::Set_Iterator::operator++() {
  ++it;
  return *this;
}

template <typename Key>
typename set<Key>::Set_Iterator& set<Key>::Set_Iterator::operator--() {
  --it;
  return *this;
}

template <typename Key>
typename set<Key>::Set_Iterator set<Key>::Set_Iterator::operator++(int) {
  return it++;
}

template <typename Key>
typename set<Key>::Set_Iterator set<Key>::Set_Iterator::operator--(int) {
  return it--;
}

template <typename Key>
typename set<Key>::Set_Iterator& set<Key>::Set_Iterator::operator=(
    const Set_Iterator& other) {
  if (this != &other) {
    it = other.it;
  }
  return *this;
}

template <typename Key>
bool set<Key>::Set_Iterator::operator==(const iterator& other) const {
  return it == other.it;
}

template <typename Key>
inline bool set<Key>::Set_Iterator::operator!=(const iterator& other) const {
  return it != other.it;
}

template <typename Key>
typename set<Key>::const_reference set<Key>::Set_Iterator::operator*() const {
  if (it.get_node() == nullptr)
    throw std::out_of_range("Set_Iterator::operator*()");
  return *it;
}

template <typename Key>
const typename set<Key>::value_type* set<Key>::Set_Iterator::operator->()
    const {
  return &(it->value);
}

template <typename Key>
typename std::pair<typename set<Key>::iterator, bool> set<Key>::insert(
    const value_type& value) {
  if (contains(value)) {
    auto it = find(value);
    return std::make_pair(it, false);
  }
  auto res = _tree.insert(value, value);
  return std::make_pair(iterator(res.first), res.second);
}

template <typename Key>
typename set<Key>::iterator set<Key>::begin() {
  return iterator(_tree.begin());
}

template <typename Key>
typename set<Key>::iterator set<Key>::end() {
  return iterator(_tree.end());
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::cbegin() const {
  return const_iterator(_tree.cbegin());
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::cend() const {
  return const_iterator(_tree.cend());
}

//
//
//
//
//

template <typename Key>
inline set<Key>::Const_Set_Iterator::Const_Set_Iterator(tree_iterator it)
    : it(it) {}

template <typename Key>
inline set<Key>::Const_Set_Iterator::Const_Set_Iterator(const_tree_iterator it)
    : it(it){};

template <typename Key>
typename set<Key>::Const_Set_Iterator&
set<Key>::Const_Set_Iterator::operator++() {
  ++it;
  return *this;
}

template <typename Key>
typename set<Key>::Const_Set_Iterator&
set<Key>::Const_Set_Iterator::operator--() {
  --it;
  return *this;
}

template <typename Key>
typename set<Key>::Const_Set_Iterator set<Key>::Const_Set_Iterator::operator++(
    int) {
  return it++;
}

template <typename Key>
typename set<Key>::Const_Set_Iterator set<Key>::Const_Set_Iterator::operator--(
    int) {
  return it--;
}

template <typename Key>
bool set<Key>::Const_Set_Iterator::operator==(
    const const_iterator& other) const {
  return it == other.it;
}

template <typename Key>
inline bool set<Key>::Const_Set_Iterator::operator!=(
    const const_iterator& other) const {
  return it != other.it;
}

template <typename Key>
typename set<Key>::const_reference set<Key>::Const_Set_Iterator::operator*()
    const {
  if (it.get_node() == nullptr)
    throw std::out_of_range("Const_Set_Iterator::operator*()");
  return *it;
}

template <typename Key>
typename set<Key>::value_type* set<Key>::Const_Set_Iterator::operator->()
    const {
  return &(it->value);
}

template <typename Key>
template <typename... Args>
vector<std::pair<typename set<Key>::iterator, bool>> set<Key>::insert_many(
    Args&&... args) {
  vector<std::pair<typename set<Key>::iterator, bool>> result_vector;
  result_vector.reserve(sizeof...(args));

  auto args_tuple = std::make_tuple(std::forward<Args>(args)...);

  std::apply(
      [this, &result_vector](auto&&... unpacked_args) {
        // Используем инициализатор списка для вызова insert для каждого
        // элемента
        (result_vector.push_back(this->insert(
             std::forward<decltype(unpacked_args)>(unpacked_args))),
         ...);
      },
      args_tuple);

  return result_vector;
}

}  // namespace s21