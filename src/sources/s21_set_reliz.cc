#include "../headers/s21_set.h"

using namespace s21;

template <typename T, typename S>
set<T, S>::set(std::initializer_list<key_type> const &items) {
  for (auto it = items.begin(); it != items.end(); ++it) {
    insert(*it);
  }
}

template <typename T, typename S>
set<T, S>::set(set &s) {
  for (auto it = s.begin(); it != s.end(); ++it) {
    insert(*it);
  }
}

template <typename T, typename S>
set<T, S>::set(set &&s) {
  this->clear();
  this->root_ = s.root_;
  s.root_ = nullptr;
}

template <typename T, typename S>
set<T, S> &set<T, S>::operator=(set &s) {
  for (iterator it = s.begin(); it != s.end(); ++it) {
    insert(*it);
  }
  return *this;
}

template <typename T, typename S>
set<T, S> &set<T, S>::operator=(set &&s) {
  this->clear();
  this->root_ = s.root_;
  s.root_ = nullptr;
  return *this;
}

template <typename T, typename S>
typename set<T, S>::iterator set<T, S>::begin() {
  iterator it;
  if (this->root_ == nullptr) {
    it.elem = this->end_dummy;
  } else {
    it.elem = this->min_elem(this->root_);
  }
  return it;
}

template <typename T, typename S>
typename set<T, S>::iterator set<T, S>::end() {
  if (this->root_ != nullptr) {
    node<T, S> *max = this->max_elem(this->root_);
    if (max != this->end_dummy) {
      this->end_dummy = new node<T, S>(max->pair, max, nullptr, nullptr);
      max->right = this->end_dummy;
    }
  }
  iterator it(this->end_dummy);
  return it;
}

template <typename T, typename S>
std::pair<typename set<T, S>::iterator, bool> set<T, S>::insert(
    const key_type &key) {
  value_type pair = std::make_pair(key, key);
  return push(this->root_, pair);
}

template <typename T, typename S>
typename set<T, S>::iterator set<T, S>::find(const T &key) {
  iterator it(this->find_pair(this->root_, key));
  return it;
}

template <typename T, typename S>
void set<T, S>::erase(iterator pos) {
  this->remove(this->root_, pos.elem->pair);
}

template <typename T, typename S>
void set<T, S>::merge(set &other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    insert(*it);
  }
}

template <typename T, typename S>
template <typename... Args>
std::vector<std::pair<typename set<T, S>::iterator, bool>> set<T, S>::emplace(
    Args &&...args) {
  std::vector<std::pair<iterator, bool>> res;
  for (auto &i : {args...}) res.push_back(insert(i));
  return res;
}

/////////////////////////////////////
////////////// PRIVATE /////////////
///////////////////////////////////

template <typename T, typename S>
std::pair<typename set<T, S>::iterator, bool> set<T, S>::push(
    node<T, S> *(&knot), std::pair<T, S> value) {
  std::pair<typename set<T, S>::iterator, bool> res;
  if (knot == nullptr) {
    knot = new node<T, S>(value, knot, nullptr, nullptr);
    return std::pair<typename set<T, S>::iterator, bool>{knot, true};
  } else if (value < knot->pair) {
    if (knot->left == nullptr) {
      node<T, S> *tmp = new node<T, S>(value, knot, nullptr, nullptr);
      knot->left = tmp;
      res = {tmp, true};
    } else {
      res = push(knot->left, value);
    }
    if ((this->height(knot->left) - this->height(knot->right)) > 1) {
      if (this->height(knot->left->left) < this->height(knot->left->right))
        this->turn_left(knot->left);
      this->turn_right(knot);
    }
  } else if (value.first == knot->pair.first) {
    return std::pair<typename set<T, S>::iterator, bool>{knot, false};
  } else {
    if (knot->right == nullptr) {
      node<T, S> *tmp = new node<T, S>(value, knot, nullptr, nullptr);
      knot->right = tmp;
      res = {tmp, true};
    } else {
      res = push(knot->right, value);
    }
    if ((this->height(knot->right) - this->height(knot->left)) > 1) {
      if (this->height(knot->right->right) < this->height(knot->right->left))
        this->turn_right(knot->right);
      this->turn_left(knot);
    }
  }
  return res;
}
