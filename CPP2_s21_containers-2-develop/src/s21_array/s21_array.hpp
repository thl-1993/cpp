#ifndef SRC_S21_CONTAINERSPLUS_ARRAY_H
#define SRC_S21_CONTAINERSPLUS_ARRAY_H
#include <iostream>
namespace s21 {
template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using size_type = std::size_t;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;

  array();
  array(std::initializer_list<value_type> const &items);
  array(const array &a);
  array(array &&a) noexcept;
  ~array();

  array<T, N> &operator=(array<T, N> &&a) noexcept;

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();

  iterator data();
  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void swap(array &other);
  void fill(const_reference value);

 private:
  size_type size_;
  value_type data_[N] = {};
};

template <typename T, size_t N>
inline array<T, N>::array() : size_(N){};

template <typename T, size_t N>
inline array<T, N>::array(std::initializer_list<value_type> const &items)
    : size_(N) {
  auto iter = items.begin();
  for (size_type i = 0; i < items.size(); i++) {
    data_[i] = *(iter + i);
  }
};

template <typename T, size_t N>
inline array<T, N>::array(const array &a) : size_(N) {
  for (size_type i = 0; i < size_; i++) {
    data_[i] = a.data_[i];
  }
};

template <typename T, size_t N>
inline array<T, N>::array(array &&a) noexcept : array(a){};

template <typename T, size_t N>
inline array<T, N>::~array(){};

template <typename T, size_t N>
inline array<T, N> &array<T, N>::operator=(array<T, N> &&a) noexcept {
  if (this != &a) {
    for (size_type i = 0; i < size_; ++i) {
      data_[i] = a.data_[i];
    }
  }
  return *this;
};

template <typename T, size_t N>
inline typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= size_ || size_ == 0) throw std::out_of_range("Out of range");
  return data_[pos];
};

template <typename T, size_t N>
inline typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return data_[pos];
};

template <typename T, size_t N>
inline typename array<T, N>::const_reference array<T, N>::front() {
  return data_[0];
};

template <typename T, size_t N>
inline typename array<T, N>::const_reference array<T, N>::back() {
  return data_[size_ - 1];
};

template <typename T, size_t N>
inline typename array<T, N>::iterator array<T, N>::data() {
  return data_;
};

template <typename T, size_t N>
inline typename array<T, N>::iterator array<T, N>::begin() {
  return data_;
};

template <typename T, size_t N>
inline typename array<T, N>::iterator array<T, N>::end() {
  return data_ + size_;
};

template <typename T, size_t N>
inline bool array<T, N>::empty() {
  return size_ == 0;
};

template <typename T, size_t N>
inline typename array<T, N>::size_type array<T, N>::size() {
  return size_;
};

template <typename T, size_t N>
inline typename array<T, N>::size_type array<T, N>::max_size() {
  return size_;
};

template <typename T, size_t N>
inline void array<T, N>::swap(array &other) {
  value_type temp;
  for (size_type i = 0; i < size_; i++) {
    temp = other.data_[i];
    other.data_[i] = data_[i];
    data_[i] = temp;
  }
};

template <typename T, size_t N>
inline void array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < size_; i++) data_[i] = value;
};
}  // namespace s21
#endif  // SRC_S21_CONTAINERSPLUS_ARRAY_H