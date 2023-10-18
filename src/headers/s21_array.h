#include <stddef.h>

#include <initializer_list>
#include <iostream>

namespace s21 {
template <typename T, size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 private:
  size_type size_;
  value_type data_[N];

 public:
  array();
  array(std::initializer_list<value_type> const &items);
  array(const array &a);
  array(array &&a);
  ~array();
  void operator=(array &a);
  void operator=(array &&a);

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() const;
  const_reference back() const;

  iterator data();

  iterator begin();
  iterator end();

  const_iterator cbegin() const;
  const_iterator cend() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void swap(array &other);
  // void fill(const_reference value);
};
}  // namespace s21