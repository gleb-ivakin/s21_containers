#include "../headers/s21_multiset.h"

using namespace s21;

template <typename T, typename S>
multiset<T, S>::multiset(std::initializer_list<key_type> const &items) {
  for (auto it = items.begin(); it != items.end(); ++it) {
    insert(*it);
  }
}

template <typename T, typename S>
multiset<T, S>::multiset(multiset &ms) {
  for (auto it = ms.begin(); it != ms.end(); ++it) {
    insert(*it);
  }
}

template <typename T, typename S>
multiset<T, S>::multiset(multiset &&ms) {
  this->clear();
  this->root_ = ms.root_;
  ms.root_ = nullptr;
}

template <typename T, typename S>
multiset<T, S>::~multiset() {
  this->destroy(this->root_);
}

template <typename T, typename S>
multiset<T, S> &multiset<T, S>::operator=(multiset &ms) {
  for (iterator it = ms.begin(); it != ms.end(); ++it) {
    insert(*it);
  }
  return *this;
}

template <typename T, typename S>
multiset<T, S> &multiset<T, S>::operator=(multiset &&ms) {
  this->clear();
  this->root_ = ms.root_;
  ms.root_ = nullptr;
  return *this;
}

template <typename T, typename S>
typename multiset<T, S>::iterator multiset<T, S>::insert(
    const key_type &value) {
  std::pair<T, S> pair = std::make_pair(value, value);
  return push(this->root_, pair);
}

template <typename T, typename S>
std::pair<typename multiset<T, S>::iterator, typename multiset<T, S>::iterator>
multiset<T, S>::equal_range(const key_type &key) {
  return std::make_pair(this->lower_bound(key), this->upper_bound(key));
}

template <typename T, typename S>
typename multiset<T, S>::iterator multiset<T, S>::lower_bound(
    const key_type &key) {
  iterator it(this->min_elem(this->root_));
  for (; it != this->end(); ++it) {
    if (*it >= key) return it;
  }
  ++it;
  return it;
}

template <typename T, typename S>
typename multiset<T, S>::iterator multiset<T, S>::upper_bound(
    const key_type &key) {
  iterator it(this->min_elem(this->root_));
  for (; it != this->end(); ++it) {
    if (*it > key) return it;
  }
  ++it;
  return it;
}

template <typename T, typename S>
typename multiset<T, S>::size_type multiset<T, S>::count(const key_type &key) {
  iterator it_find(this->find);
  iterator it_noequal(this->find_upper());
  size_type sz = 0;
  for (iterator it(this->find); it != this->find_boumd; ++it) {
    ++sz;
  }
  return sz;
}

/////////////////////////////////////
////////////// PRIVATE /////////////
///////////////////////////////////

template <typename T, typename S>
typename multiset<T, S>::size_type multiset<T, S>::coun_key(node<T, S> knot,
                                                            key_type &key) {
  iterator it_find(this->find);
  iterator it_noequal(this->find_upper());
  size_type size = 0;
  for (iterator it(this->find); it != this->find_upper(); ++it) {
    ++size;
  }
  return size;
}

template <typename T, typename S>
typename multiset<T, S>::iterator multiset<T, S>::push(node<T, S> *(&knot),
                                                       std::pair<T, S> value) {
  iterator it;
  if (knot == nullptr) {
    knot = new node<T, S>(value, knot, nullptr, nullptr);
    return it.elem = knot;
  } else if (value < knot->pair) {
    if (knot->left == nullptr) {
      node<T, S> *tmp = new node<T, S>(value, knot, nullptr, nullptr);
      knot->left = tmp;
      it.elem = knot;
    } else {
      it = push(knot->left, value);
    }
    if ((this->height(knot->left) - this->height(knot->right)) > 1) {
      if (this->height(knot->left->left) < this->height(knot->left->right))
        this->turn_left(knot->left);
      this->turn_right(knot);
    }
  } else {
    if (knot->right == nullptr) {
      node<T, S> *tmp = new node<T, S>(value, knot, nullptr, nullptr);
      knot->right = tmp;
      it.elem = knot;
    } else {
      it = push(knot->right, value);
    }
    if ((this->height(knot->right) - this->height(knot->left)) > 1) {
      if (this->height(knot->right->right) < this->height(knot->right->left))
        this->turn_right(knot->right);
      this->turn_left(knot);
    }
  }
  return it;
}
