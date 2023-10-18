#include "../headers/s21_list_like_class.h"

using namespace s21;

// ------- Supporting -------

template <typename T>
void list_like<T>::CreateDummy() {
  dummy = new Node<T>();
  dummy->next = head;
  dummy->prev = tail;
  dummy->data = T();
}

template <typename T>
void list_like<T>::MoveFrom(list_like<T> &&l) {
  head = l.head;
  tail = l.tail;
  Size = l.Size;

  l.head = nullptr;
  l.tail = nullptr;
  l.Size = 0;
}

// ------- List-like Functions -------

template <typename T>
list_like<T>::list_like() {
  Size = 0;
  head = tail = nullptr;

  CreateDummy();
}

template <typename T>
list_like<T>::list_like(size_type n) {
  if (n) {
    head = new Node<T>();
    size_type counter = 0;
    Node<T> *current = head;

    while (++counter < n) {
      current->next = new Node<T>();
      current->next->prev = current;
      current = current->next;
    }

    tail = current;
    Size = n;

  } else {
    Size = 0;
    head = tail = nullptr;
  }

  CreateDummy();
}

template <typename T>
list_like<T>::list_like(std::initializer_list<value_type> const &items)
    :  // используем делегирующий конструктор для начальной установки списка
      list_like<T>::list_like(items.size()) {
  Node<T> *current = head;

  for (auto item : items) {
    current->data = item;
    current = current->next;
  }
}

template <typename T>
list_like<T>::list_like(const list_like &l) : list_like<T>::list_like(l.Size) {
  Node<T> *current_l = l.head;
  Node<T> *current_this = this->head;
  for (size_t i = 0; i < l.Size; i++) {
    current_this->data = current_l->data;
    current_l = current_l->next;
    current_this = current_this->next;
  }
}

template <typename T>
list_like<T>::list_like(list_like &&l) : list_like<T>::list_like() {
  MoveFrom(std::move(l));
}

// ------- List-like Element access -------

template <typename T>
typename list_like<T>::const_reference list_like<T>::front() {
  return this->head ? this->head->data : this->dummy->data;
}

template <typename T>
typename list_like<T>::const_reference list_like<T>::back() {
  return this->tail ? this->tail->data : this->dummy->data;
}

// ------- List-like Capacity -------

template <typename T>
typename list_like<T>::size_type list_like<T>::size() const {
  return this->Size;
}

// ------- List-like Modifiers -------

template <typename T>
void list_like<T>::clear() {
  while (this->Size) pop_front();
}

template <typename T>
void list_like<T>::push_back(const_reference value) {
  node_type *new_node = new node_type(value);
  if (this->head == nullptr) {
    this->head = this->tail = new_node;
  } else {
    new_node->prev = this->tail;
    this->tail->next = new_node;
    this->tail = new_node;
  }
  this->Size++;
}

template <typename T>
void list_like<T>::push_front(const_reference value) {
  node_type *new_node = new node_type(value);
  if (this->head == nullptr) {
    this->head = this->tail = new_node;
  } else {
    new_node->next = this->head;
    this->head->prev = new_node;
    this->head = new_node;
  }
  this->Size++;
}

template <typename T>
void list_like<T>::pop_front() {
  if (this->head == nullptr) return;

  node_type *to_delete = this->head;
  this->head = this->head->next;

  if (this->head != nullptr) this->head->prev = nullptr;

  delete to_delete;
  this->Size--;
}

template <typename T>
void list_like<T>::swap(list_like &other) {
  if (this->head == other.head) return;

  node_type *temp;

  temp = other.head;
  other.head = this->head;
  this->head = temp;

  temp = other.tail;
  other.tail = this->tail;
  this->tail = temp;

  size_type temp_size;
  temp_size = other.Size;
  other.Size = this->Size;
  this->Size = temp_size;
}