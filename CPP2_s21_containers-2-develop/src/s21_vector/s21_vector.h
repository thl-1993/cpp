#ifndef VECTOR_H
#define VECTOR_H
#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  vector();
  explicit vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector<T> &v);
  vector(vector<T> &&v);
  ~vector();
  vector<T> &operator=(vector<T> &&v);

  vector &operator=(const vector &other);

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  T *data();

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size() const;
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);

  void bring_to_zero();
  void delete_arr();

 private:
  T *arr_;
  size_t size_;
  size_t capacity_;
};

template <typename T>
inline typename vector<T>::size_type vector<T>::size() {
  return size_;
}

template <typename T>
inline typename vector<T>::size_type vector<T>::capacity() {
  return capacity_;
}

template <typename T>
inline typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return arr_[pos];
}

template <typename T>
inline vector<T>::vector() : arr_(nullptr), size_(0), capacity_(0) {}

template <typename T>
inline vector<T>::vector(size_type n)
    : arr_(new value_type[n]), size_(n), capacity_(n) {
  if (arr_ == nullptr) {
    throw std::bad_alloc();
  }
  for (size_type i = 0; i < n; ++i) {
    arr_[i] = T();
  }
}

template <typename T>
inline typename vector<T>::iterator vector<T>::begin() {
  return arr_;
}

template <typename T>
inline typename vector<T>::iterator vector<T>::end() {
  return arr_ + size_;
}

template <typename T>
inline vector<T>::vector(std::initializer_list<value_type> const &items) {
  arr_ = new value_type[items.size()];
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    arr_[i] = *it;
    i++;
  }
  size_ = items.size();
  capacity_ = items.size();
};

template <typename T>
inline vector<T>::vector(const vector<T> &v) : vector(v.size_) {
  for (size_t i = 0; i < size_; i++) arr_[i] = v.arr_[i];
}

template <typename T>
void vector<T>::bring_to_zero() {
  this->size_ = 0;
  this->capacity_ = 0;
  this->arr_ = nullptr;
}

template <typename T>
inline vector<T>::vector(vector<T> &&v)
    : arr_(v.arr_), size_(v.size_), capacity_(v.capacity_) {
  v.bring_to_zero();
}

template <typename T>
inline vector<T>::~vector() {
  delete[] arr_;
  bring_to_zero();
}

template <typename T>
inline void vector<T>::delete_arr() {
  if (this->arr_) {
    delete[] this->arr_;
  }
  bring_to_zero();
}

template <typename T>
inline vector<T> &vector<T>::operator=(vector<T> &&v) {
  if (this != &v) {
    this->delete_arr();
    this->size_ = v.size_;
    this->capacity_ = v.capacity_;
    this->arr_ = v.arr_;
    v.bring_to_zero();
  }
  return *this;
}

template <typename T>
vector<T> &vector<T>::operator=(const vector &other) {
  if (this != &other) {
    reserve(other.size_);
    size_ = other.size_;
    capacity_ = other.capacity_;
    for (size_t i = 0; i < size_; i++) arr_[i] = other.arr_[i];
  }
  return *this;
}

template <typename T>
inline typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_ || size_ == 0) {
    throw std::out_of_range("Index out range");
  }
  return arr_[pos];
}

template <typename T>
inline typename vector<T>::const_reference vector<T>::front() {
  return *arr_;
}

template <typename T>
inline typename vector<T>::const_reference vector<T>::back() {
  return *(arr_ + size_ - 1);
}

template <typename T>
inline typename vector<T>::iterator vector<T>::data() {
  return arr_;
}

template <typename T>
inline bool vector<T>::empty() {
  return size_ == 0;
}

template <typename T>
inline typename vector<T>::size_type vector<T>::max_size() const {
  return std::numeric_limits<std::size_t>::max() / sizeof(value_type) / 2;
}

template <typename T>
inline void vector<T>::reserve(size_type size) {
  if (size >= size_) {
    vector<value_type> new_arr(size);
    for (size_type i = 0; i < size_; ++i) {
      new_arr.arr_[i] = arr_[i];
    }
    new_arr.size_ = size_;
    *this = std::move(new_arr);
  }
}

template <typename T>
inline void vector<T>::shrink_to_fit() {
  if (size_ != capacity_) {
    vector<value_type> new_arr(size_);
    for (size_type i = 0; i < size_; ++i) {
      new_arr.arr_[i] = arr_[i];
    }
    *this = std::move(new_arr);
  }
}

template <typename T>
inline void vector<T>::clear() {
  delete[] arr_;
  bring_to_zero();
}

template <typename T>
inline typename vector<T>::iterator vector<T>::insert(iterator pos,
                                                      const_reference value) {
  size_t zero = 0;
  size_t position = &(*pos) - this->arr_;
  if (position < zero || position > this->size_) {
    throw std::out_of_range("Index out ot range");
  }
  size_t index = pos - begin();
  if (size_ == capacity_) {
    reserve(capacity_ * 2);
  }
  for (size_t i = size_; i > index; i--) {
    arr_[i] = arr_[i - 1];
  }
  arr_[index] = value;
  size_++;
  return begin() + index;
}

template <typename T>
inline void vector<T>::erase(iterator pos) {
  size_t zero = 0;
  size_t position = &(*pos) - this->arr_;
  if (position < zero || position > this->size_) {
    throw std::out_of_range("Index out ot range");
  }
  size_t index = pos - begin();
  for (size_t i = index; i < size_ - 1; i++) {
    arr_[i] = arr_[i + 1];
  }
  size_--;
}

template <typename T>
inline void vector<T>::push_back(const_reference value) {
  if (size_ >= capacity_) {
    if (capacity_ == 0)
      reserve(1);
    else
      reserve(capacity_ * 2);
  }
  arr_[size_] = value;
  size_++;
}

template <typename T>
inline void vector<T>::pop_back() {
  size_ -= 1;
}

template <typename T>
inline void vector<T>::swap(vector &other) {
  T *new_arr = arr_;
  size_t new_size = size_;
  size_t new_capacity = capacity_;
  arr_ = other.arr_;
  size_ = other.size_;
  capacity_ = other.capacity_;
  other.arr_ = new_arr;
  other.size_ = new_size;
  other.capacity_ = new_capacity;
}

template <typename T>
template <typename... Args>
inline typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                           Args &&...args) {
  size_type index = pos - begin();
  size_type count = sizeof...(args);
  if (size_ + count > capacity_) {
    reserve(size_ + count);
  }
  for (size_type i = size_ + count - 1; i > index + count - 1; i--) {
    arr_[i] = arr_[i - count];
  }
  size_ += count;
  ((arr_[index++] = std::forward<Args>(args)), ...);
  return begin() + index - 1;
}

template <typename value_type>
template <typename... Args>
void vector<value_type>::insert_many_back(Args &&...args) {
  size_type count = sizeof...(args);
  if (size_ + count > capacity_) {
    reserve(size_ + count);
  }
  insert_many(end(), args...);
}

}  // namespace s21

#endif  // VECTOR_H