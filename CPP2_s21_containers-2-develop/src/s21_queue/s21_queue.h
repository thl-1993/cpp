#ifndef S21_QUEUE_S21_QUEUE_H_
#define S21_QUEUE_S21_QUEUE_H_

#include "../s21_vector/s21_vector.h"

namespace s21 {

template <class T, class Vector = s21::vector<T>>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  queue();
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &q);
  queue(queue &&q);
  ~queue();
  queue &operator=(queue &&q);

  const_reference front();
  const_reference back();

  bool empty();
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(queue &other);

  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  Vector head;
};

}  // namespace s21
namespace s21 {
template <class T, class Vector>
queue<T, Vector>::queue() : head() {}

template <class T, class Vector>
queue<T, Vector>::queue(std::initializer_list<value_type> const &items)
    : head(items) {}

template <class T, class Vector>
queue<T, Vector>::queue(const queue &q) : head(q.head) {}

template <class T, class Vector>
queue<T, Vector>::queue(queue &&q) : head(std::move(q.head)) {}

template <class T, class Vector>
queue<T, Vector>::~queue() {}

template <class T, class Vector>
queue<T, Vector> &queue<T, Vector>::operator=(queue &&q) {
  this->head = std::move(q.head);
  return *this;
}

template <class T, class Vector>
typename queue<T, Vector>::size_type queue<T, Vector>::size() {
  return head.size();
}

template <typename T, typename Vector>
typename queue<T, Vector>::const_reference queue<T, Vector>::front() {
  return head.front();
}

template <typename T, typename Vector>
typename queue<T, Vector>::const_reference queue<T, Vector>::back() {
  return head.back();
}

template <class T, class Vector>
void queue<T, Vector>::push(const_reference value) {
  this->head.push_back(value);
}

template <typename T, class Vector>
void queue<T, Vector>::pop() {
  if (empty()) {
    throw std::out_of_range("Queue is empty");
  }
  head.erase(head.begin());
}

template <class T, class Vector>
bool queue<T, Vector>::empty() {
  return head.empty();
}

template <class T, class Vector>
void queue<T, Vector>::swap(queue &other) {
  this->head.swap(other.head);
}

template <class T, class Vector>
template <typename... Args>
void queue<T, Vector>::insert_many_back(Args &&...args) {
  head.insert_many_back(args...);
}

}  // namespace s21

#endif  // S21_QUEUE_S21_QUEUE_H_