#include "../headers/s21_map.h"

using namespace s21;

template <typename T, typename S>
map<T, S>::map(std::initializer_list<value_type> const &items) {
  for (auto it = items.begin(); it != items.end(); ++it) insert(*it);
}

template <typename T, typename S>
map<T, S>::map(map &m) {
  for (auto it = m.begin(); it != m.end(); ++it) {
    insert(*it);
  }
}

template <typename T, typename S>
map<T, S>::map(map &&m) {
  this->clear();
  this->root_ = m.root_;
  m.root_ = nullptr;
}

template <typename T, typename S>
map<T, S>::~map() {
  this->destroy(this->root_);
}

template <typename T, typename S>
map<T, S> &map<T, S>::operator=(map &m) {
  for (auto it = m.begin(); it != m.end(); ++it) insert(*it);
  return *this;
}

template <typename T, typename S>
map<T, S> &map<T, S>::operator=(map &&m) {
  this->clear();
  this->root_ = m.root_;
  m.root_ = nullptr;
  return *this;
}

template <typename T, typename S>
std::pair<typename map<T, S>::iterator, bool> map<T, S>::insert(
    const value_type &value) {
  return push(this->root_, value);
}

template <typename T, typename S>
std::pair<typename map<T, S>::iterator, bool> map<T, S>::insert(const T &key,
                                                                const S &obj) {
  return insert(std::make_pair(key, obj));
}

template <typename T, typename S>
std::pair<typename map<T, S>::iterator, bool> map<T, S>::insert_or_assign(
    const T &key, const S &obj) {
  return (insert_or_assign_privat(std::make_pair(key, obj), this->root_));
}

template <typename T, typename S>
std::pair<typename map<T, S>::iterator, bool>
map<T, S>::insert_or_assign_privat(std::pair<T, S> value, node<T, S> *(&knot)) {
  std::pair<typename map<T, S>::iterator, bool> res;
  if (knot == nullptr) {
    knot = new node<T, S>(value, knot, nullptr, nullptr);
    return std::pair<typename map<T, S>::iterator, bool>{knot, true};
  } else if (value.first < knot->pair.first) {
    if (knot->left == nullptr) {
      node<T, S> *tmp = new node<T, S>(value, knot, nullptr, nullptr);
      knot->left = tmp;
      res = {knot, true};
    } else {
      res = insert_or_assign_privat(value, knot->left);
    }
    if ((this->height(knot->left) - this->height(knot->right)) > 1) {
      if (this->height(knot->left->left) < this->height(knot->left->right))
        this->turn_left(knot->left);
      this->turn_right(knot);
    }
  } else if (value.first == knot->pair.first) {
    knot->pair = value;
    return std::pair<typename map<T, S>::iterator, bool>{knot, false};
  } else {
    if (knot->right == nullptr) {
      node<T, S> *tmp = new node<T, S>(value, knot, nullptr, nullptr);
      knot->right = tmp;
      res = {knot, true};
    } else {
      res = insert_or_assign_privat(value, knot->right);
    }
    if ((this->height(knot->right) - this->height(knot->left)) > 1) {
      if (this->height(knot->right->right) < this->height(knot->right->left))
        this->turn_right(knot->right);
      this->turn_left(knot);
    }
  }
  return res;
}

template <typename T, typename S>
void map<T, S>::erase(iterator pos) {
  this->remove(this->root_, pos.elem->pair);
}

template <typename T, typename S>
void map<T, S>::merge(map &other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    this->insert(*it);
  }
}

template <typename T, typename S>
S &map<T, S>::at(const T &key) {
  iterator it(this->find_pair(this->root_, key));
  if (it.elem == nullptr) throw std::out_of_range("Map: at: out of range");
  return it.elem->pair.second;
}

template <typename T, typename S>
S &map<T, S>::operator[](const T &key) {
  if (!this->find_pair(this->root_, key)) {
    insert(key, S());
  }
  iterator it(this->find_pair(this->root_, key));
  return it.elem->pair.second;
}

template <typename T, typename S>
typename map<T, S>::iterator map<T, S>::begin() {
  iterator it;
  if (this->root_ == nullptr) {
    it.elem = this->end_dummy;
  } else {
    it.elem = this->min_elem(this->root_);
  }
  return it;
}

template <typename T, typename S>
typename map<T, S>::iterator map<T, S>::end() {
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
template <typename... Args>
std::vector<std::pair<typename map<T, S>::iterator, bool>> map<T, S>::emplace(
    Args &&...args) {
  std::vector<std::pair<iterator, bool>> res;
  for (auto &i : {args...}) res.push_back(insert(i));
  return res;
}

/////////////////////////////////////
////////////// PRIVATE /////////////
///////////////////////////////////

template <typename T, typename S>
std::pair<typename map<T, S>::iterator, bool> map<T, S>::push(
    node<T, S> *(&knot), std::pair<T, S> value) {
  std::pair<typename map<T, S>::iterator, bool> res;
  if (knot == nullptr) {
    knot = new node<T, S>(value, knot, nullptr, nullptr);
    return std::pair<typename map<T, S>::iterator, bool>{knot, true};
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
    return std::pair<typename map<T, S>::iterator, bool>{knot, false};
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
