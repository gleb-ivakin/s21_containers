#include "../headers/s21_queue.h"

using namespace s21;

// ------- Queue Functions -------

template <typename T>
queue<T>::queue() : list_like<T>::list_like() {}

template <typename T>
queue<T>::queue(std::initializer_list<value_type> const &items)
    : list_like<T>::list_like(items) {}

template <typename T>
queue<T>::queue(const queue &l) : list_like<T>::list_like(l) {}

template <typename T>
queue<T>::queue(queue &&l) : list_like<T>::list_like(std::move(l)) {}

template <typename T>
queue<T>::~queue() {
  clear();
  delete this->dummy;
}

template <typename T>
queue<T> &queue<T>::operator=(queue &&l) {
  if (this != &l) {
    clear();
    this->MoveFrom(std::move(l));
  }

  return *this;
}

// ------- Queue Element access -------
template <typename T>
typename queue<T>::const_reference queue<T>::front() {
  return list_like<T>::front();
}

template <typename T>
typename queue<T>::const_reference queue<T>::back() {
  return list_like<T>::back();
}

// ------- Queue Capacity -------
template <typename T>
typename queue<T>::size_type queue<T>::size() const {
  return list_like<T>::size();
}

template <typename T>
bool queue<T>::empty() {
  return this->size() ? false : true;
}

// ------- Queue Modifiers -------

template <typename T>
void queue<T>::push(const_reference value) {
  list_like<T>::push_back(value);
}

template <typename T>
void queue<T>::pop() {
  list_like<T>::pop_front();
}

template <typename T>
void queue<T>::swap(queue &other) {
  list_like<T>::swap(other);
}

// ------- Queue Modifiers -------

template <typename T>
void queue<T>::clear() {
  list_like<T>::clear();
}
