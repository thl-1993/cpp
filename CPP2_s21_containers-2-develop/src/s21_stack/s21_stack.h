#ifndef S21_STACK_S21_STACK_H_
#define S21_STACK_S21_STACK_H_

#include "../s21_vector/s21_vector.h"

namespace s21 {

template <class T, class Vector = s21::vector<T>>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  stack();
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &s);
  stack(stack &&s);
  ~stack();
  stack &operator=(stack &&s);

  stack &operator=(const stack &other);

  const_reference top();
  bool empty();
  size_type size();
  void push(const_reference value);
  void pop();
  void swap(stack &other);

  template <typename... Args>
  void insert_many_front(Args &&...args);

 private:
  Vector head;
};

}  // namespace s21
namespace s21 {
template <class T, class Vector>
stack<T, Vector>::stack() : head() {}

template <class T, class Vector>
stack<T, Vector>::stack(std::initializer_list<value_type> const &items)
    : head(items) {}

template <class T, class Vector>
stack<T, Vector>::stack(const stack &s) : head(s.head) {}

template <class T, class Vector>
stack<T, Vector>::stack(stack &&s) : head(std::move(s.head)) {}

template <class T, class Vector>
stack<T, Vector>::~stack() {}

template <class T, class Vector>
stack<T, Vector> &stack<T, Vector>::operator=(stack &&s) {
  this->head = std::move(s.head);
  return *this;
}

template <class T, class Vector>
stack<T, Vector> &stack<T, Vector>::operator=(const stack &other) {
  if (this != &other) {
    head = other.head;
  }
  return *this;
}

template <class T, class Vector>
typename stack<T, Vector>::size_type stack<T, Vector>::size() {
  return head.size();
}

template <class T, class Vector>
typename stack<T, Vector>::const_reference stack<T, Vector>::top() {
  return head.back();
}

template <class T, class Vector>
void stack<T, Vector>::push(const_reference value) {
  this->head.push_back(value);
}

template <class T, class Vector>
void stack<T, Vector>::pop() {
  this->head.pop_back();
}

template <class T, class Vector>
bool stack<T, Vector>::empty() {
  return head.empty();
}

template <class T, class Vector>
void stack<T, Vector>::swap(stack &other) {
  this->head.swap(other.head);
}

template <class value_type, class Vector>
template <typename... Args>
void stack<value_type, Vector>::insert_many_front(Args &&...args) {
  head.insert_many_back(args...);
}

}  // namespace s21

#endif  // S21_STACK_S21_STACK_H_