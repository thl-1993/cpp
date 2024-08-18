#include <tuple>
#include <vector>

#include "../s21_tree/s21_tree.hpp"
#include "../s21_vector/s21_vector.h"

namespace s21 {
template <typename Key>
class multiset {
 public:
  class Multiset_Iterator;
  class Const_Multiset_Iterator;
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = multiset<Key>::Multiset_Iterator;
  using const_iterator = Const_Multiset_Iterator;
  using size_type = std::size_t;

 private:
  Tree<key_type, value_type> _tree;
  std::pair<iterator, bool> insert_pair(const value_type& value);

 public:
  multiset();
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& other);
  multiset(multiset&& other);
  ~multiset();

  multiset& operator=(const multiset& s);
  multiset& operator=(multiset&& s) noexcept;

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  template <typename... Args>
  vector<std::pair<typename multiset<Key>::iterator, bool>> insert_many(
      Args&&... args);

  bool empty();
  size_type size();
  size_type max_size();

  void clear();

  iterator insert(const value_type& value);
  void erase(iterator pos);
  void swap(multiset& other);
  void merge(multiset& other);

  iterator find(const Key& key);
  bool contains(const Key& key);
  size_type count(const Key& key);

  iterator lower_bound(const Key& key);
  iterator upper_bound(const Key& key);
  std::pair<iterator, iterator> equal_range(const Key& key);

  class Multiset_Iterator {
   public:
    using iterator = multiset<Key>::Multiset_Iterator;
    using tree_iterator = typename Tree<key_type, value_type>::Iterator;
    using const_tree_iterator =
        typename Tree<key_type, value_type>::Const_Iterator;
    Multiset_Iterator() = default;
    Multiset_Iterator(tree_iterator it);
    Multiset_Iterator(const_tree_iterator it);
    ~Multiset_Iterator() = default;

    Multiset_Iterator& operator++();
    Multiset_Iterator& operator--();
    Multiset_Iterator operator++(int);
    Multiset_Iterator operator--(int);

    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;

    const_reference operator*() const;
    const value_type* operator->() const;

    // Multiset_Iterator &operator=(const Multiset_Iterator &other);

   private:
    tree_iterator it;
    friend void multiset<Key>::erase(iterator pos);
  };

  class Const_Multiset_Iterator {
   public:
    using tree_iterator = typename Tree<key_type, value_type>::Iterator;
    using const_iterator = Const_Multiset_Iterator;
    using const_tree_iterator =
        typename Tree<key_type, value_type>::Const_Iterator;
    Const_Multiset_Iterator() = default;
    // typename multiset<Key>::Const_Multiset_Iterator &operator=(const typename
    // multiset<Key>::Const_Multiset_Iterator &other);
    Const_Multiset_Iterator(tree_iterator it);
    Const_Multiset_Iterator(const_tree_iterator it);
    ~Const_Multiset_Iterator() = default;

    Const_Multiset_Iterator& operator++();
    Const_Multiset_Iterator& operator--();
    Const_Multiset_Iterator operator++(int);
    Const_Multiset_Iterator operator--(int);

    bool operator==(const const_iterator& other) const;
    bool operator!=(const const_iterator& other) const;

    const_reference operator*() const;
    value_type* operator->() const;

   private:
    const_tree_iterator it;
  };
};

template <typename Key>
inline std::pair<typename multiset<Key>::iterator, bool>
multiset<Key>::insert_pair(const value_type& value) {
  return std::make_pair<multiset<Key>::iterator, bool>(insert(value), true);
}

template <typename Key>
multiset<Key>::multiset() : _tree() {}

template <typename Key>
multiset<Key>::multiset(std::initializer_list<value_type> const& items) {
  // _tree = Tree<key_type, value_type>();
  // for (const value_type& item : items)  {
  //     if (!contains(item)) insert(item);
  // }
  _tree = Tree<key_type, value_type>(items);
}

template <typename Key>
multiset<Key>::multiset(const multiset& other) {
  _tree = Tree<key_type, value_type>(other._tree);
}

template <typename Key>
multiset<Key>::multiset(multiset&& other) {
  // Tree<key_type, value_type> tmp(_tree);
  _tree = std::move(other._tree);
  // _tree = tmp;
  // tmp.clean();
}

template <typename Key>
multiset<Key>::~multiset() {
  // std::cout  <<  "Set destructor!" << std::endl;
  _tree.clean();
}

template <typename Key>
multiset<Key>& multiset<Key>::operator=(const multiset& s) {
  if (this == &s) {
    return *this;
  }
  _tree = s._tree;
  return *this;
}

template <typename Key>
multiset<Key>& multiset<Key>::operator=(multiset&& s) noexcept {
  if (this == &s) {
    return *this;
  }
  _tree = std::move(s._tree);
  return *this;
}

template <typename Key>
inline bool s21::multiset<Key>::empty() {
  return _tree.empty();
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::size() {
  return _tree.size();
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::max_size() {
  return _tree.max_size();
}

template <typename Key>
void multiset<Key>::clear() {
  _tree.clean();
  // _tree = Tree<key_type, value_type>();
}

template <typename Key>
void multiset<Key>::swap(multiset& other) {
  if (this == &other) throw std::invalid_argument("swap");
  _tree.swap(other._tree);
}

template <typename Key>
void multiset<Key>::merge(multiset& other) {
  if (this == &other) throw std::invalid_argument("merge");
  _tree.merge(other._tree);
  other.clear();
  // for (auto it = other.begin(); it != other.end(); ++it) {
  //     if (!contains(*it)) insert(*it);
  // }
}

template <typename Key>
void multiset<Key>::erase(iterator pos) {
  _tree.erase(pos.it);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::find(const Key& key) {
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
bool multiset<Key>::contains(const Key& key) {
  return _tree.contains(key);
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::count(const Key& key) {
  size_type count = 0;
  auto it = find(key);
  auto it_end = _tree.end();
  while (it != it_end) {
    if (*it > key) break;
    if (*it == key) {
      ++count;
      ++it;
    }
  }
  return count;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(const Key& key) {
  auto it = begin();
  while (it != end() && *it < key) {
    ++it;
  }
  return it;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(const Key& key) {
  auto it = begin();
  while (it != end() && *it <= key) {
    ++it;
  }
  return it;
}

template <typename Key>
std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
multiset<Key>::equal_range(const Key& key) {
  auto lower = lower_bound(key);
  auto upper = upper_bound(key);
  return std::make_pair(lower, upper);
}

template <typename Key>
inline multiset<Key>::Multiset_Iterator::Multiset_Iterator(tree_iterator it)
    : it(it) {}

template <typename Key>
inline multiset<Key>::Multiset_Iterator::Multiset_Iterator(
    const_tree_iterator it)
    : it(it) {}

template <typename Key>
typename multiset<Key>::Multiset_Iterator&
multiset<Key>::Multiset_Iterator::operator++() {
  ++it;
  return *this;
}

template <typename Key>
typename multiset<Key>::Multiset_Iterator&
multiset<Key>::Multiset_Iterator::operator--() {
  --it;
  return *this;
}

template <typename Key>
typename multiset<Key>::Multiset_Iterator
multiset<Key>::Multiset_Iterator::operator++(int) {
  return it++;
}

template <typename Key>
typename multiset<Key>::Multiset_Iterator
multiset<Key>::Multiset_Iterator::operator--(int) {
  return it--;
}

template <typename Key>
bool multiset<Key>::Multiset_Iterator::operator==(const iterator& other) const {
  return it == other.it;
}

template <typename Key>
inline bool multiset<Key>::Multiset_Iterator::operator!=(
    const iterator& other) const {
  return it != other.it;
}

template <typename Key>
typename multiset<Key>::const_reference
multiset<Key>::Multiset_Iterator::operator*() const {
  if (it.get_node() == nullptr)
    throw std::out_of_range("Multiset_Iterator::operator*()");
  return *it;
}

template <typename Key>
const typename multiset<Key>::value_type*
multiset<Key>::Multiset_Iterator::operator->() const {
  return &(it->value);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::insert(
    const value_type& value) {
  _tree.__insert(value, value);
  auto it = _tree.begin();
  auto it_end = _tree.end();
  while (it != it_end) {
    if (*it == value) break;
    ++it;
  }
  return iterator(it);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::begin() {
  return iterator(_tree.begin());
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::end() {
  return iterator(_tree.end());
}

template <typename Key>
typename multiset<Key>::const_iterator multiset<Key>::cbegin() const {
  return const_iterator(_tree.cbegin());
}

template <typename Key>
typename multiset<Key>::const_iterator multiset<Key>::cend() const {
  return const_iterator(_tree.cend());
}

//
//
//
//
//

template <typename Key>
inline multiset<Key>::Const_Multiset_Iterator::Const_Multiset_Iterator(
    tree_iterator it)
    : it(it) {}

template <typename Key>
inline multiset<Key>::Const_Multiset_Iterator::Const_Multiset_Iterator(
    const_tree_iterator it)
    : it(it){};

template <typename Key>
typename multiset<Key>::Const_Multiset_Iterator&
multiset<Key>::Const_Multiset_Iterator::operator++() {
  ++it;
  return *this;
}

template <typename Key>
typename multiset<Key>::Const_Multiset_Iterator&
multiset<Key>::Const_Multiset_Iterator::operator--() {
  --it;
  return *this;
}

template <typename Key>
typename multiset<Key>::Const_Multiset_Iterator
multiset<Key>::Const_Multiset_Iterator::operator++(int) {
  return it++;
}

template <typename Key>
typename multiset<Key>::Const_Multiset_Iterator
multiset<Key>::Const_Multiset_Iterator::operator--(int) {
  return it--;
}

template <typename Key>
bool multiset<Key>::Const_Multiset_Iterator::operator==(
    const const_iterator& other) const {
  return it == other.it;
}

template <typename Key>
inline bool multiset<Key>::Const_Multiset_Iterator::operator!=(
    const const_iterator& other) const {
  return it != other.it;
}

template <typename Key>
typename multiset<Key>::const_reference
multiset<Key>::Const_Multiset_Iterator::operator*() const {
  if (it.get_node() == nullptr)
    throw std::out_of_range("Const_Multiset_Iterator::operator*()");
  return *it;
}

template <typename Key>
typename multiset<Key>::value_type*
multiset<Key>::Const_Multiset_Iterator::operator->() const {
  return &(it->value);
}

template <typename Key>
template <typename... Args>
vector<std::pair<typename multiset<Key>::iterator, bool>>
multiset<Key>::insert_many(Args&&... args) {
  vector<std::pair<typename multiset<Key>::iterator, bool>> result_vector;
  result_vector.reserve(sizeof...(args));
  auto args_tuple = std::make_tuple(std::forward<Args>(args)...);
  std::apply(
      [this, &result_vector](auto&&... unpacked_args) {
        (result_vector.push_back(this->insert_pair(
             std::forward<decltype(unpacked_args)>(unpacked_args))),
         ...);
      },
      args_tuple);

  return result_vector;
}
}  // namespace s21