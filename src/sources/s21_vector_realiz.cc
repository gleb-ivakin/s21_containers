#include "../headers/s21_vector.h"

using namespace s21;

template <typename T>
Vector<T>::Vector(std::initializer_list<value_type> const &items) {
  arr_ = new value_type[items.size()];
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    arr_[i] = *it;
    i++;
  }
  m_size_ = items.size();
  m_capacity_ = items.size();
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T> &other) {
  delete[] arr_;
  m_capacity_ = other.m_capacity_;
  m_size_ = other.m_size_;
  try {
    arr_ = new T[m_size_]();
  } catch (std::exception &ex) {
    std::cerr << ex.what() << std::endl;
  }
  for (size_t i = 0; i != m_size_; ++i) {
    arr_[i] = other.arr_[i];
  }
  return *this;
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T> &&other) {
  delete[] arr_;
  this->swap(other);
  return *this;
}

template <typename T>
typename Vector<T>::reference Vector<T>::at(size_type pos) {
  if (pos >= m_size_) throw std::out_of_range("error_range");
  return arr_[pos];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::at(size_type pos) const {
  if (pos >= m_size_) throw std::out_of_range("error_range");
  return arr_[pos];
}

template <typename T>
void Vector<T>::reserve(size_type size) {
  if (size < m_size_) return;
  if (size > max_size()) throw std::length_error("error_max_size");
  reserve_more_capacity_(size);
}

template <typename T>
void Vector<T>::shrink_to_fit() {
  if (m_capacity_ > m_size_) {
    reserve_more_capacity_(m_size_);
  }
}

template <typename T>
void Vector<T>::push_back(value_type v) {
  if (m_size_ == m_capacity_) {
    reserve(m_capacity_ * 2);
  }
  arr_[m_size_] = v;
  ++m_size_;
}

template <typename T>
void Vector<T>::pop_back() {
  if (!empty()) {
    (arr_ + m_size_ - 1)->~T();
    --m_size_;
  }
}

template <typename T>
size_t Vector<T>::max_size() {
  std::allocator<T> alloc;
  return alloc.max_size();
}

template <typename T>
void Vector<T>::clear() {
  if (arr_) {
    delete[] arr_;
    arr_ = nullptr;
  }
  m_size_ = 0;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos, const T &value) {
  if (pos > end()) return pos;
  Vector tmp(std::move(*this));
  m_size_ = tmp.m_size_ + 1;
  m_capacity_ = tmp.m_capacity_;
  arr_ = new T[m_size_]();
  if (m_capacity_ <= m_size_) reserve(m_capacity_ * 2);
  size_t i = 0;
  for (iterator it = tmp.begin(); it < tmp.end(); ++it) {
    if (pos == it) {
      arr_[i++] = value;
      arr_[i++] = *it;
    } else {
      arr_[i++] = *it;
    }
  }
  return pos;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator pos) {
  if (pos == end()) return end();
  Vector tmp(std::move(*this));
  m_size_ = tmp.m_size_ - 1;
  m_capacity_ = tmp.m_capacity_;
  arr_ = new T[m_size_]();
  size_t i = 0;
  for (iterator it = tmp.begin(); it < tmp.end(); ++it) {
    if (pos == it) {
      continue;
    }
    arr_[i++] = *it;
  }
  return pos;
}

template <typename T>
void Vector<T>::swap(Vector<T> &other) {
  std::swap(this->m_size_, other.m_size_);
  std::swap(this->m_capacity_, other.m_capacity_);
  std::swap(this->arr_, other.arr_);
}

template <typename T>
template <typename... Args>
T *Vector<T>::emplace(iterator pos, Args &&...args) {
  for (auto i : {args...}) {
    insert(pos, i);
  }
  return pos;
}

template <typename T>
template <typename... Args>
void Vector<T>::emplace_back(Args &&...args) {
  for (auto i : {args...}) {
    push_back(i);
  }
}

template <typename T>
void Vector<T>::reserve_more_capacity_(size_t size) {
  value_type *buff = new value_type[size];
  for (size_t i = 0; i < m_size_; ++i) buff[i] = std::move(arr_[i]);
  delete[] arr_;
  arr_ = buff;
  m_capacity_ = size;
}
