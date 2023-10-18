#ifndef VIRTUAL_CLASS_H
#define VIRTUAL_CLASS_H

#include <initializer_list>
#include <iostream>
#include <utility>
#include <vector>

#include "s21_tree.h"

namespace s21 {

template <typename T, typename S>
class virtual_map_set {
 protected:
  node<T, S> *root_ = nullptr;
  node<T, S> *end_dummy;

 public:
  using size_type = size_t;
  /////////////////////////////
  /////     Capacity    //////
  ///////////////////////////
  virtual bool empty();
  size_type size();
  size_type max_size();
  /////////////////////////////
  //////    Modifiers    /////
  ///////////////////////////
  void clear();
  void swap(virtual_map_set &other);
  void merge(virtual_map_set &other);
  ///////////////////////////
  ////      Lookup     /////
  /////////////////////////
  bool contains(const T &key);

 protected:
  node<T, S> *find_pair(node<T, S> *knot, const T &key);
  node<T, S> *max_elem(node<T, S> *elem);
  node<T, S> *min_elem(node<T, S> *elem);
  size_type count_size(node<T, S> *knot);
  void turn_left(node<T, S> *(&root));
  void turn_right(node<T, S> *(&root));
  void virtual_map_set_balance(node<T, S> *knot);
  int height(node<T, S> *knot);
  void destroy(node<T, S> *&knot);
  void remove(node<T, S> *&knot, std::pair<T, S> value);
  node<T, S> *get_min(node<T, S> *(&knot));
  node<T, S> *get_max(node<T, S> *(&knot));
  void first_case(node<T, S> *(&knot));
  void second_case(node<T, S> *(&knot));
  void third_case(node<T, S> *(&knot));
};  // virtual_map_set
}  // namespace s21
#endif  // VIRTUAL_CLASS_H