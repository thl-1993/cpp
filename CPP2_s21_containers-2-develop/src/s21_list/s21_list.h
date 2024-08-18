#ifndef S21_LIST_H
#define S21_LIST_H

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
class list {
 public:
  // Member types
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;
  class ListIterator;
  class ListConstIterator;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

 private:
  struct Node {
    T data;
    Node* next;
    Node* prev;
    Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
  };

  Node* head;
  Node* tail;
  Node* end_node;
  size_type size_n;

 public:
  // Functions
  list();
  list(size_type n);
  list(std::initializer_list<value_type> const& items);
  list(const list& l);
  list(list&& l) noexcept;
  ~list();
  list& operator=(list&& l) noexcept;

  // Element access
  const_reference front() const;
  const_reference back() const;

  // Iterators
  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  // Capacity
  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  // Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list& other);
  void merge(list& other);
  void splice(const iterator pos, list& other);
  void reverse();
  void unique();
  void sort();

  // Part 3. insert_many
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);
  template <typename... Args>
  void insert_many_front(Args&&... args);
};

// реализация внутреннего класса ListIterator

template <typename T>
class list<T>::ListIterator {
 public:
  using value_type = T;
  using reference = T&;
  using pointer = T*;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;

  explicit ListIterator(Node* node, Node* head, Node* end_node, const list* lst)
      : node(node),
        head(head),
        end_node(end_node),
        lst(lst),
        special_state(false),
        list_size(lst->size()) {}

  ~ListIterator() = default;

  reference operator*() const {
    if (special_state) {
      special_value = static_cast<T>(list_size);
      return special_value;
    }
    return node->data;
  }

  pointer operator->() const { return &(operator*()); }

  ListIterator& operator++() {
    if (special_state) {
      special_state = false;
      node = head;
    } else if (node->next) {
      node = node->next;
    } else {
      special_state = true;
    }
    return *this;
  }

  ListIterator operator++(int) {
    ListIterator temp = *this;
    ++(*this);
    return temp;
  }

  ListIterator& operator--() {
    if (special_state) {
      special_state = false;
      Node* temp = head;
      while (temp->next) {
        temp = temp->next;
      }
      node = temp;
    } else if (node->prev) {
      node = node->prev;
    } else {
      special_state = true;
    }
    return *this;
  }

  ListIterator operator--(int) {
    ListIterator temp = *this;
    --(*this);
    return temp;
  }

  bool operator==(const ListIterator& other) const {
    return node == other.node && special_state == other.special_state;
  }

  bool operator!=(const ListIterator& other) const { return !(*this == other); }

 private:
  Node* node;
  Node* head;
  Node* end_node;
  const list* lst;
  bool special_state;
  mutable T special_value;
  size_t list_size;
};

// реализация внутреннего класса ListConstIterator

template <typename T>
class list<T>::ListConstIterator {
 public:
  using value_type = T;
  using reference = const T&;
  using pointer = const T*;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;

  explicit ListConstIterator(const Node* node, const Node* end_node)
      : node(node), end_node(end_node) {}

  reference operator*() const { return node->data; }
  pointer operator->() const { return &(node->data); }

  ListConstIterator& operator++() {
    if (node && node != end_node) {
      node = node->next ? node->next : end_node;
    }
    return *this;
  }

  ListConstIterator operator++(int) {
    ListConstIterator temp = *this;
    ++(*this);
    return temp;
  }

  ListConstIterator& operator--() {
    if (node && node != end_node) {
      node = node->prev ? node->prev : end_node;
    } else if (node == end_node) {
      node = end_node->prev;
    }
    return *this;
  }

  ListConstIterator operator--(int) {
    ListConstIterator temp = *this;
    --(*this);
    return temp;
  }

  bool operator==(const ListConstIterator& other) const {
    return node == other.node;
  }

  bool operator!=(const ListConstIterator& other) const {
    return !(*this == other);
  }

  const Node* getNode() const { return node; }

 private:
  const Node* node;
  const Node* end_node;
};

// Реализация конструкторов и деструктора

template <typename T>
list<T>::list() : head(nullptr), tail(nullptr), size_n(0) {
  end_node = new Node(T());
  end_node->next = nullptr;
  end_node->prev = tail;
}

template <typename T>
list<T>::list(size_type n) : list() {
  for (size_type i = 0; i < n; ++i) {
    push_back(T());
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const& items) : list() {
  for (const auto& item : items) {
    push_back(item);
  }
}

template <typename T>
list<T>::list(const list& l) : list() {
  Node* current = l.head;
  while (current) {
    push_back(current->data);
    current = current->next;
  }
}

template <typename T>
list<T>::list(list&& l) noexcept : list() {
  swap(l);
}

template <typename T>
list<T>::~list() {
  clear();
  delete end_node;
}

template <typename T>
list<T>& list<T>::operator=(list&& l) noexcept {
  if (this != &l) {
    clear();
    swap(l);
  }
  return *this;
}

// Реализация методов класса list

template <typename T>
typename list<T>::const_reference list<T>::front() const {
  if (empty()) {
    throw std::out_of_range("List is empty");
  }
  return head->data;
}

template <typename T>
typename list<T>::const_reference list<T>::back() const {
  if (empty()) {
    throw std::out_of_range("List is empty");
  }
  return tail->data;
}

template <typename T>
typename list<T>::iterator list<T>::begin() {
  return iterator(head, head, end_node, this);
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  return iterator(end_node, head, end_node, this);
}

template <typename T>
typename list<T>::const_iterator list<T>::cbegin() const {
  return const_iterator(head, end_node);
}

template <typename T>
typename list<T>::const_iterator list<T>::cend() const {
  return const_iterator(end_node, end_node);
}

template <typename T>
bool list<T>::empty() const {
  return size_n == 0;
}

template <typename T>
typename list<T>::size_type list<T>::size() const {
  return size_n;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() const {
  return std::numeric_limits<size_type>::max();
}

template <typename T>
void list<T>::clear() {
  while (head) {
    Node* next = head->next;
    delete head;
    head = next;
  }
  tail = nullptr;
  size_n = 0;
}

template <typename T>
typename list<T>::iterator list<T>::insert(
    iterator pos, typename list<T>::const_reference value) {
  Node* newNode = new Node(value);
  Node* current = pos.getNode();

  if (current && current != end_node) {
    newNode->next = current;
    newNode->prev = current->prev;

    if (current->prev) {
      current->prev->next = newNode;
    } else {
      head = newNode;
    }

    current->prev = newNode;
  } else {
    if (tail) {
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
    } else {
      head = tail = newNode;
    }
  }

  ++size_n;
  return iterator(newNode, end_node);
}

template <typename T>
void list<T>::erase(iterator pos) {
  Node* node = pos.getNode();
  if (node == nullptr || node == end_node) {
    throw std::out_of_range("Iterator is out of range");
  }
  if (node->prev) {
    node->prev->next = node->next;
  } else {
    head = node->next;
  }

  if (node->next) {
    node->next->prev = node->prev;
  } else {
    tail = node->prev;
  }

  delete node;
  --size_n;
}

template <typename T>
void list<T>::push_back(typename list<T>::const_reference value) {
  Node* newNode = new Node(value);
  if (tail) {
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
  } else {
    head = tail = newNode;
  }
  ++size_n;
}

template <typename T>
void list<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range("List is empty");
  }
  Node* oldTail = tail;
  tail = tail->prev;
  if (tail) {
    tail->next = nullptr;
  } else {
    head = nullptr;
  }
  delete oldTail;
  --size_n;
}

template <typename T>
void list<T>::push_front(typename list<T>::const_reference value) {
  Node* newNode = new Node(value);
  if (head) {
    head->prev = newNode;
    newNode->next = head;
    head = newNode;
  } else {
    head = tail = newNode;
  }
  ++size_n;
}

template <typename T>
void list<T>::pop_front() {
  if (empty()) {
    throw std::out_of_range("List is empty");
  }
  Node* oldHead = head;
  head = head->next;
  if (head) {
    head->prev = nullptr;
  } else {
    tail = nullptr;
  }
  delete oldHead;
  --size_n;
}

template <typename T>
void list<T>::swap(list& other) {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(end_node, other.end_node);
  std::swap(size_n, other.size_n);
}

template <typename T>
void list<T>::merge(list& other) {
  if (this != &other) {
    if (empty()) {
      swap(other);
    } else if (!other.empty()) {
      sort();
      other.sort();

      Node* mergedHead = nullptr;
      Node* mergedTail = nullptr;

      Node* current1 = head;
      Node* current2 = other.head;

      while (current1 && current2) {
        if (current1->data <= current2->data) {
          if (!mergedHead) {
            mergedHead = current1;
            mergedTail = current1;
          } else {
            mergedTail->next = current1;
            current1->prev = mergedTail;
            mergedTail = current1;
          }
          current1 = current1->next;
        } else {
          if (!mergedHead) {
            mergedHead = current2;
            mergedTail = current2;
          } else {
            mergedTail->next = current2;
            current2->prev = mergedTail;
            mergedTail = current2;
          }
          current2 = current2->next;
        }
      }

      Node* remaining = current1 ? current1 : current2;
      while (remaining) {
        mergedTail->next = remaining;
        remaining->prev = mergedTail;
        mergedTail = remaining;
        remaining = remaining->next;
      }

      head = mergedHead;
      tail = mergedTail;
      size_n += other.size_n;

      other.head = other.tail = nullptr;
      other.size_n = 0;
    }
  }
}

template <typename T>
void list<T>::splice(const iterator pos, list& other) {
  Node* node = pos.getNode();

  if (this != &other) {
    if (!node || node == end_node) {
      if (!empty()) {
        tail->next = other.head;
        if (other.head) {
          other.head->prev = tail;
        }
        tail = other.tail;
      } else {
        head = other.head;
        tail = other.tail;
      }
      size_n += other.size_n;
      other.head = other.tail = nullptr;
      other.size_n = 0;
    } else {
      Node* newPrev = node->prev;

      while (!other.empty()) {
        Node* newNode = new Node(other.front());
        other.pop_front();

        newNode->next = node;
        newNode->prev = newPrev;

        if (newPrev) {
          newPrev->next = newNode;
        } else {
          head = newNode;
        }

        node->prev = newNode;
        newPrev = newNode;

        ++size_n;
      }
    }
  }
}

template <typename T>
void list<T>::reverse() {
  Node* current = head;
  Node* temp = nullptr;

  while (current) {
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;
    current = current->prev;
  }

  if (temp) {
    temp = temp->prev;
    std::swap(head, tail);
  }
}

template <typename T>
void list<T>::unique() {
  if (!empty()) {
    iterator it = begin();
    iterator next = it;
    ++next;

    while (next != end()) {
      if (*it == *next) {
        erase(next);
        next = it;
        ++next;
      } else {
        ++it;
        ++next;
      }
    }
  }
}

template <typename T>
void list<T>::sort() {
  if (size_n > 2) {
    for (iterator i = begin(); i != end(); ++i) {
      for (iterator j = begin(); j != end(); ++j) {
        iterator next = j;
        ++next;

        if (next != end() && *j > *next) {
          std::swap(*j, *next);
        }
      }
    }
  }
}

// Реализация insert_many

template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args&&... args) {
  iterator it(const_cast<Node*>(pos.getNode()), end_node);
  for (const auto& arg : {args...}) {
    it = insert(it, arg);
  }
  return it;
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args&&... args) {
  insert_many(cend(), args...);
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args&&... args) {
  insert_many(cbegin(), args...);
}

}  // namespace s21

#endif  // S21_LIST_H