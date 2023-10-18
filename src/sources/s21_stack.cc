#include "../headers/s21_stack.h"

using namespace s21;

// ------- Stack Functions -------

template <typename T>
stack<T>::stack() : list_like<T>::list_like() {}

template <typename T>
stack<T>::stack(std::initializer_list<value_type> const &items)
    : list_like<T>::list_like(items) {}

template <typename T>
stack<T>::stack(const stack &l) : list_like<T>::list_like(l) {}

template <typename T>
stack<T>::stack(stack &&l) : list_like<T>::list_like(std::move(l)) {}

template <typename T>
stack<T>::~stack() {
  clear();
  delete this->dummy;
}

template <typename T>
stack<T> &stack<T>::operator=(stack &&l) {
  if (this != &l) {
    clear();
    this->MoveFrom(std::move(l));
  }

  return *this;
}

// ------- Stack Element access -------
template <typename T>
typename stack<T>::const_reference stack<T>::top() {
  return list_like<T>::front();
}

// ------- Stack Capacity -------
template <typename T>
typename stack<T>::size_type stack<T>::size() const {
  return list_like<T>::size();
}

template <typename T>
bool stack<T>::empty() {
  return this->size() ? false : true;
}

// ------- Stack Modifiers -------

template <typename T>
void stack<T>::push(const_reference value) {
  list_like<T>::push_front(value);
}

template <typename T>
void stack<T>::pop() {
  list_like<T>::pop_front();
}

template <typename T>
void stack<T>::swap(stack &other) {
  list_like<T>::swap(other);
}

// ------- Stack Modifiers -------

template <typename T>
void stack<T>::clear() {
  list_like<T>::clear();
}
