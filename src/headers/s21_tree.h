// #pragma
#ifndef S21_TREE_H_
#define S21_TREE_H_

#include <iostream>
#include <utility>

namespace s21 {

template <typename T, typename S>
struct node {
 public:
  std::pair<T, S> pair;
  node<T, S> *parent = nullptr;
  node<T, S> *left = nullptr;
  node<T, S> *right = nullptr;
  int flag = 0;
  node(std::pair<T, S> two, node *p, node *l, node *r)
      : pair(two), parent(p), left(l), right(r){};
  node() : parent(nullptr), left(nullptr), right(nullptr){};
};  // node

template <typename T, typename S>
class iterator_tree {
 public:
  iterator_tree<T, S> &operator++();
  iterator_tree<T, S> &operator--();
  bool operator!=(const iterator_tree<T, S> &it) { return elem != it.elem; }
  bool operator==(const iterator_tree<T, S> &it) { return elem == it.elem; }
  node<T, S> *elem;
};  // iterator_tree

template <typename T, typename S>
class iterator_map : public iterator_tree<T, S> {
 public:
  iterator_map() { this->elem = nullptr; }
  iterator_map(node<T, S> *ref) { this->elem = ref; }
  std::pair<T, S> &operator*() { return this->elem->pair; }
};  // iterator_map

template <typename T, typename S>
class iterator_set : public iterator_tree<T, S> {
 public:
  iterator_set() { this->elem = nullptr; }
  iterator_set(node<T, S> *ref) { this->elem = ref; }
  T &operator*() { return this->elem->pair.first; }
};  // iterator_set

template <typename T, typename S>
iterator_tree<T, S> &iterator_tree<T, S>::operator++() {
  if (elem->right) {
    elem = elem->right;
    while (elem->left) {
      elem = elem->left;
    }
  } else {
    while (elem->parent) {
      node<T, S> *tmp = elem;
      elem = elem->parent;
      if (tmp->pair <= elem->pair) {
        if (tmp != elem->right) {
          return *this;  // условие для мультисета
        }
      }
    }
  }
  elem->flag = 1;
  return *this;
}

template <typename T, typename S>
iterator_tree<T, S> &iterator_tree<T, S>::operator--() {
  if (elem->left) {
    elem = elem->left;
    while (elem->right) {
      elem = elem->right;
    }
  } else {
    std::pair<T, S> tmp = elem->pair;
    while (elem->parent) {
      elem = elem->parent;
      if (tmp >= elem->pair) return *this;
    }
  }
  return *this;
}

}  // namespace s21
#endif  //  S21_TREE_H_
