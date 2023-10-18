#include "../headers/s21_array.h"

template <class T, size_t N>
s21::array<T, N>::array() : size_(N) {}

template <class T, size_t N>
s21::array<T, N>::array(const std::initializer_list<T> &items) : array() {
  if (size_ < items.size()) {
    throw std::out_of_range("unvaliable amount of elements");
  }
  size_type i = 0;
  for (auto in = items.begin(); in != items.end(); i++, in++) {
    data_[i] = *in;
  }
}

template <class T, size_t N>
s21::array<T, N>::array(const array &a) : array() {
  std::copy(a.cbegin(), a.cend(), data_);
}

template <class T, size_t N>
s21::array<T, N>::array(array &&a) : array() {
  std::move(a.cbegin(), a.cend(), data_);
}

template <class T, size_t N>
s21::array<T, N>::~array() {}

template <class T, size_t N>
void s21::array<T, N>::operator=(s21::array<T, N> &a) {
  std::copy(a.cbegin(), a.cend(), data_);
}

template <class T, size_t N>
void s21::array<T, N>::operator=(s21::array<T, N> &&a) {
  std::move(a.cbegin(), a.cend(), data_);
}

template <class T, size_t N>
T &s21::array<T, N>::at(size_t pos) {
  if (pos > size_) {
    throw std::out_of_range("Error");
  }
  return data_[pos];
}

template <class T, size_t N>
T &s21::array<T, N>::operator[](size_t pos) {
  return data_[pos];
}

template <class T, size_t N>
const T &s21::array<T, N>::front() const {
  return data_[0];
}

template <class T, size_t N>
const T &s21::array<T, N>::back() const {
  return data_[size_ - 1];
}

template <class T, size_t N>
T *s21::array<T, N>::data() {
  return begin();
}

template <class T, size_t N>
T *s21::array<T, N>::begin() {
  return data_;
}

template <class T, size_t N>
T *s21::array<T, N>::end() {
  return &data_[size_];
}

template <class T, size_t N>
const T *s21::array<T, N>::cbegin() const {
  return data_;
}

template <class T, size_t N>
const T *s21::array<T, N>::cend() const {
  return &data_[size_];
}

template <class T, size_t N>
bool s21::array<T, N>::empty() const {
  if (data_ != data_) {
    return true;
  } else {
    return false;
  }
}

template <class T, size_t N>
size_t s21::array<T, N>::size() const {
  return size_;
}

template <class T, size_t N>
size_t s21::array<T, N>::max_size() const {
  return size();
}

template <class T, size_t N>
void s21::array<T, N>::swap(s21::array<T, N> &other) {
  std::swap(*this, other);
}

// template<class T, size_t N>
// void s21::array<T, N>::fill(const T &value) {
//       size_type i = 0;
//     for (iterator it = this->begin(); it != this->end(); it++, i++) {
//       data_[i] = value;
// }
// }
