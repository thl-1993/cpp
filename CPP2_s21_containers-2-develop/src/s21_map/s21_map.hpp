#include <vector>

#include "../s21_tree/s21_tree.hpp"
#include "../s21_vector/s21_vector.h"

namespace s21 {
template <typename Key, typename Value>
class map {
 public:
  class Map_Iterator;
  class Const_Map_Iterator;
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = Map_Iterator;
  using const_iterator = Const_Map_Iterator;
  using size_type = std::size_t;

 private:
  Tree<key_type, value_type> _tree;

 public:
  map();
  map(std::initializer_list<value_type> const& items);
  // map(std::initializer_list<typename map<Key, Value>::value_type> const&
  // items);
  map(const map& other);
  map(map&& other);
  ~map();

  map& operator=(const map& s);
  map& operator=(map&& s) noexcept;

  Value& operator[](const Key& key);
  Value& at(const Key& key);

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  template <typename... Args>
  vector<std::pair<typename map<Key, Value>::iterator, bool>> insert_many(
      Args&&... args);

  bool empty();
  size_type size();
  size_type max_size();

  void clear();

  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const Key& key, const Value& value);
  std::pair<iterator, bool> insert_or_assign(const Key& key,
                                             const Value& value);

  void erase(iterator pos);
  void swap(map& other);
  void merge(map& other);

  iterator find(const Key& key);
  bool contains(const Key& key);

  class Map_Iterator {
   public:
    using iterator = map<Key, Value>::Map_Iterator;
    using tree_iterator = typename Tree<Key, value_type>::Iterator;
    using const_tree_iterator = typename Tree<Key, value_type>::Const_Iterator;
    Map_Iterator() = default;
    Map_Iterator(tree_iterator it);
    Map_Iterator(const_tree_iterator it);
    ~Map_Iterator() = default;

    // Явно объявляем конструктор копирования
    Map_Iterator(const Map_Iterator& other) = default;

    // Явно объявляем оператор присваивания
    Map_Iterator& operator=(const Map_Iterator& other);

    Map_Iterator& operator++();
    Map_Iterator& operator--();
    Map_Iterator operator++(int);
    Map_Iterator operator--(int);

    // Map_Iterator &operator=(const Map_Iterator &other);
    // Map_Iterator &operator=(Map_Iterator &&other) = default;

    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;

    // value_type operator*() const;
    // value_type operator->() const;

    const_reference operator*() const;
    const value_type* operator->() const;

    // Key first;
    // Value second;

   private:
    tree_iterator get_it();

    tree_iterator it;

    friend void map<Key, Value>::erase(iterator pos);
  };

  class Const_Map_Iterator {
   public:
    using tree_iterator = typename Tree<Key, value_type>::Iterator;
    using const_iterator = Const_Map_Iterator;
    using const_tree_iterator = typename Tree<Key, value_type>::Const_Iterator;
    Const_Map_Iterator() = default;
    Const_Map_Iterator(tree_iterator it);
    Const_Map_Iterator(const_tree_iterator it);
    ~Const_Map_Iterator() = default;

    Const_Map_Iterator& operator++();
    Const_Map_Iterator& operator--();
    Const_Map_Iterator operator++(int);
    Const_Map_Iterator operator--(int);

    bool operator==(const const_iterator& other) const;
    bool operator!=(const const_iterator& other) const;

    const_reference operator*() const;
    value_type* operator->() const;

   private:
    const_tree_iterator it;
  };
};

template <typename Key, typename Value>
map<Key, Value>::map() : _tree() {}

template <typename Key, typename Value>
map<Key, Value>::map(std::initializer_list<value_type> const& items) {
  _tree = Tree<Key, value_type>();
  for (const value_type& item : items) {
    if (!contains(item.first)) _tree.__insert(item.first, item);
  }
}

template <typename Key, typename Value>
map<Key, Value>::map(const map& other) {
  _tree = Tree<Key, value_type>(other._tree);
}

template <typename Key, typename Value>
map<Key, Value>::map(map&& other) {
  _tree = std::move(other._tree);
}

template <typename Key, typename Value>
map<Key, Value>::~map() {
  // std::cout  <<  "Set destructor!" << std::endl;
  _tree.clean();
}

template <typename Key, typename Value>
map<Key, Value>& map<Key, Value>::operator=(const map& s) {
  if (this == &s) {
    return *this;
  }
  _tree = s._tree;
  return *this;
}

template <typename Key, typename Value>
map<Key, Value>& map<Key, Value>::operator=(map&& s) noexcept {
  if (this == &s) {
    return *this;
  }
  _tree = std::move(s._tree);
  return *this;
}

template <typename Key, typename Value>
inline bool s21::map<Key, Value>::empty() {
  return _tree.empty();
}

template <typename Key, typename Value>
typename map<Key, Value>::size_type map<Key, Value>::size() {
  return _tree.size();
}

template <typename Key, typename Value>
typename map<Key, Value>::size_type map<Key, Value>::max_size() {
  return _tree.max_size();
}

template <typename Key, typename Value>
void map<Key, Value>::clear() {
  _tree.clean();
}

template <typename Key, typename Value>
void map<Key, Value>::swap(map& other) {
  if (this == &other) throw std::invalid_argument("swap");
  _tree.swap(other._tree);
}

template <typename Key, typename Value>
void map<Key, Value>::merge(map& other) {
  if (this == &other) throw std::invalid_argument("merge");
  for (auto it = other.begin(); it != other.end(); ++it) {
    if (!contains(it->first)) insert(std::make_pair(it->first, it->second));
  }
}

template <typename Key, typename Value>
void map<Key, Value>::erase(iterator pos) {
  _tree.erase(pos.it);
}

template <typename Key, typename Value>
typename map<Key, Value>::iterator map<Key, Value>::find(const Key& key) {
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

template <typename Key, typename Value>
bool map<Key, Value>::contains(const Key& key) {
  return _tree.contains(key);
}

template <typename Key, typename Value>
inline map<Key, Value>::Map_Iterator::Map_Iterator(tree_iterator it) : it(it) {}

//
//
//
//

template <typename Key, typename Value>
inline map<Key, Value>::Map_Iterator::Map_Iterator(const_tree_iterator it)
    : it(it) {}

template <typename Key, typename Value>
typename map<Key, Value>::Map_Iterator&
map<Key, Value>::Map_Iterator::operator++() {
  ++it;
  return *this;
}

template <typename Key, typename Value>
typename map<Key, Value>::Map_Iterator&
map<Key, Value>::Map_Iterator::operator--() {
  --it;
  return *this;
}

template <typename Key, typename Value>
typename map<Key, Value>::Map_Iterator
map<Key, Value>::Map_Iterator::operator++(int) {
  return it++;
}

template <typename Key, typename Value>
typename map<Key, Value>::Map_Iterator
map<Key, Value>::Map_Iterator::operator--(int) {
  return it--;
}

template <typename Key, typename Value>
typename map<Key, Value>::Map_Iterator&
map<Key, Value>::Map_Iterator::operator=(const Map_Iterator& other) {
  if (this != &other) {
    it = other.it;
  }
  return *this;
}

template <typename Key, typename Value>
bool map<Key, Value>::Map_Iterator::operator==(const iterator& other) const {
  return it == other.it;
}

template <typename Key, typename Value>
inline bool map<Key, Value>::Map_Iterator::operator!=(
    const iterator& other) const {
  return it != other.it;
}

template <typename Key, typename Value>
typename map<Key, Value>::const_reference
map<Key, Value>::Map_Iterator::operator*() const {
  if (it.get_node() == nullptr)
    throw std::out_of_range("Map_Iterator::operator*()");
  return *it;
}

template <typename Key, typename Value>
const typename map<Key, Value>::value_type*
map<Key, Value>::Map_Iterator::operator->() const {
  if (it.get_node() == nullptr)
    throw std::out_of_range("Map_Iterator::operator*()");
  return &(*it);
}

template <typename Key, typename Value>
typename std::pair<typename map<Key, Value>::iterator, bool>
map<Key, Value>::insert(const value_type& value) {
  return insert(value.first, value.second);
}

template <typename Key, typename Value>
typename std::pair<typename map<Key, Value>::iterator, bool>
map<Key, Value>::insert(const Key& key, const Value& value) {
  if (contains(key)) {
    auto it = find(key);
    return std::make_pair(it, false);
  }
  auto res = _tree.insert(key, std::make_pair(key, value));
  return std::make_pair(iterator(res.first), res.second);
}

template <typename Key, typename Value>
typename std::pair<typename map<Key, Value>::iterator, bool>
map<Key, Value>::insert_or_assign(const Key& key, const Value& value) {
  if (contains(key)) {
    auto it = find(key);
    erase(it);
    insert(key, value);
    it = find(key);
    // auto pair = insert_or_assign(key, value);
    return std::make_pair(it, true);
  }
  auto res = _tree.insert(key, std::make_pair(key, value));
  return std::make_pair(iterator(res.first), res.second);
}

template <typename Key, typename Value>
typename map<Key, Value>::iterator map<Key, Value>::begin() {
  return iterator(_tree.begin());
}

template <typename Key, typename Value>
typename map<Key, Value>::iterator map<Key, Value>::end() {
  return iterator(_tree.end());
}

template <typename Key, typename Value>
typename map<Key, Value>::const_iterator map<Key, Value>::cbegin() const {
  return const_iterator(_tree.cbegin());
}

template <typename Key, typename Value>
typename map<Key, Value>::const_iterator map<Key, Value>::cend() const {
  return const_iterator(_tree.cend());
}

//
//
//
//
//

template <typename Key, typename Value>
inline map<Key, Value>::Const_Map_Iterator::Const_Map_Iterator(tree_iterator it)
    : it(it) {}

template <typename Key, typename Value>
inline map<Key, Value>::Const_Map_Iterator::Const_Map_Iterator(
    const_tree_iterator it)
    : it(it){};

template <typename Key, typename Value>
typename map<Key, Value>::Const_Map_Iterator&
map<Key, Value>::Const_Map_Iterator::operator++() {
  ++it;
  return *this;
}

template <typename Key, typename Value>
typename map<Key, Value>::Const_Map_Iterator&
map<Key, Value>::Const_Map_Iterator::operator--() {
  --it;
  return *this;
}

template <typename Key, typename Value>
typename map<Key, Value>::Const_Map_Iterator
map<Key, Value>::Const_Map_Iterator::operator++(int) {
  return it++;
}

template <typename Key, typename Value>
typename map<Key, Value>::Const_Map_Iterator
map<Key, Value>::Const_Map_Iterator::operator--(int) {
  return it--;
}

template <typename Key, typename Value>
bool map<Key, Value>::Const_Map_Iterator::operator==(
    const const_iterator& other) const {
  return it == other.it;
}

template <typename Key, typename Value>
inline bool map<Key, Value>::Const_Map_Iterator::operator!=(
    const const_iterator& other) const {
  return it != other.it;
}

template <typename Key, typename Value>
typename map<Key, Value>::const_reference
map<Key, Value>::Const_Map_Iterator::operator*() const {
  if (it.get_node() == nullptr)
    throw std::out_of_range("Const_Map_Iterator::operator*()");
  return *it;
}

template <typename Key, typename Value>
typename map<Key, Value>::value_type*
map<Key, Value>::Const_Map_Iterator::operator->() const {
  return &(it->value);
}

template <typename Key, typename Value>
template <typename... Args>
vector<std::pair<typename map<Key, Value>::iterator, bool>>
map<Key, Value>::insert_many(Args&&... args) {
  vector<std::pair<typename map<Key, Value>::iterator, bool>> result_vector;
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

template <typename Key, typename Value>
inline Value& map<Key, Value>::operator[](
    const Key& key) {  // TODO Rebuild. Or not..?
  return _tree.at(key).second;
}

template <typename Key, typename Value>
inline Value& map<Key, Value>::at(const Key& key) {
  return _tree.at(key).second;
}

template <typename Key, typename Value>
inline typename map<Key, Value>::Map_Iterator::tree_iterator
map<Key, Value>::Map_Iterator::get_it() {
  return it;
}

}  // namespace s21