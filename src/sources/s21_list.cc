#include "../headers/s21_list.h"

using namespace s21;

// ------- List Functions -------

template <typename T>
list<T>::list() : list_like<T>::list_like() {}

template <typename T>
list<T>::list(size_type n) : list_like<T>::list_like(n) {}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items)
    : list_like<T>::list_like(items) {}

template <typename T>
list<T>::list(const list &l) : list_like<T>::list_like(l) {}

template <typename T>
list<T>::list(list &&l) : list_like<T>::list_like(std::move(l)) {}

template <typename T>
list<T>::~list() {
  clear();
  delete this->dummy;
}

template <typename T>
list<T> &list<T>::operator=(list &&l) {
  if (this != &l) {
    clear();
    this->MoveFrom(std::move(l));
  }

  return *this;
}

// ------- List Element access -------
template <typename T>
typename list<T>::const_reference list<T>::front() {
  return list_like<T>::front();
}

template <typename T>
typename list<T>::const_reference list<T>::back() {
  return list_like<T>::back();
}

// ------- List Iterators -------

template <typename T>
typename list<T>::iterator list<T>::begin() {
  iterator it;
  it.parentList = this;

  if (this->Size == 0)
    it.currentNode = this->dummy;
  else
    it.currentNode = this->head;

  return it;
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  iterator it;
  it.parentList = this;

  if (this->Size != 0) this->dummy->prev = this->tail;

  it.currentNode = this->dummy;

  return it;
}

// -------- Iterator methods --------

template <typename T>
list<T>::iterator::iterator(node_type *node, list<T> *parent_list) {
  currentNode = node;
  parentList = parent_list;
}

template <typename T>
list<T>::iterator::iterator(const iterator &other) {
  currentNode = other.currentNode;
  parentList = other.parentList;
}

template <typename T>
typename list<T>::iterator list<T>::iterator::operator++() {
  if (parentList->Size != 0 && currentNode->next != nullptr)
    currentNode = currentNode->next;
  else
    currentNode = parentList->dummy;

  return *this;
}

template <typename T>
typename list<T>::iterator list<T>::iterator::operator--() {
  if (parentList->Size != 0 && currentNode->prev != nullptr)
    currentNode = currentNode->prev;
  else
    currentNode = parentList->dummy;

  return *this;
}

template <typename T>
typename list<T>::reference list<T>::iterator::operator*() const {
  return currentNode->data;
}

template <typename T>
bool list<T>::iterator::operator!=(const iterator &i) {
  return (parentList == i.parentList && currentNode == i.currentNode) ? false
                                                                      : true;
}

template <typename T>
bool list<T>::iterator::operator==(const iterator &i) {
  return (parentList == i.parentList && currentNode == i.currentNode) ? true
                                                                      : false;
}

template <typename T>
typename list<T>::iterator &list<T>::iterator::operator=(
    const iterator &other) {
  if (this != &other) {
    currentNode = other.currentNode;
    parentList = other.parentList;
  }

  return *this;
}

// -------- Const iterator methods --------

template <typename T>
list<T>::const_iterator::const_iterator(const node_type *node,
                                        const list<T> *parent_list) {
  currentNode = node;
  parentList = parent_list;
}

template <typename T>
list<T>::const_iterator::const_iterator(const iterator &other) {
  currentNode = other.currentNode;
  parentList = other.parentList;
}

template <typename T>
typename list<T>::const_iterator list<T>::const_iterator::operator++() {
  if (parentList->Size != 0 && currentNode->next != nullptr)
    currentNode = currentNode->next;
  else
    currentNode = parentList->dummy;

  return *this;
}

template <typename T>
typename list<T>::const_iterator list<T>::const_iterator::operator--() {
  if (parentList->Size != 0 && currentNode->prev != nullptr)
    currentNode = currentNode->prev;
  else
    currentNode = parentList->dummy;

  return *this;
}

template <typename T>
typename list<T>::const_reference list<T>::const_iterator::operator*() const {
  return currentNode->data;
}

template <typename T>
bool list<T>::const_iterator::operator!=(const const_iterator &i) {
  return (parentList == i.parentList && currentNode == i.currentNode) ? false
                                                                      : true;
}

template <typename T>
bool list<T>::const_iterator::operator==(const const_iterator &i) {
  return (parentList == i.parentList && currentNode == i.currentNode) ? true
                                                                      : false;
}

template <typename T>
typename list<T>::const_iterator &list<T>::const_iterator::operator=(
    const const_iterator &other) {
  return *this;
}

// ------- List Capacity -------

template <typename T>
bool list<T>::empty() {
  return (begin() == end());
}

template <typename T>
typename list<T>::size_type list<T>::size() const {
  return list_like<T>::size();
}

template <typename T>
typename list<T>::size_type list<T>::max_size() const {
  return std::numeric_limits<size_type>::max();
}

// ------- List Modifiers -------

template <typename T>
void list<T>::clear() {
  list_like<T>::clear();
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  node_type *newNode = new node_type(value);

  if (this->Size != 0) {
    node_type *current;
    current = pos.currentNode;

    if (pos.currentNode == this->dummy) {  // для обработки end()
      newNode->prev = this->tail;
      this->tail->next = newNode;
      this->tail = newNode;
    } else {
      newNode->prev = current->prev;
      newNode->next = current;

      if (current->prev != nullptr)
        current->prev->next = newNode;
      else
        this->head = newNode;  // для обработки begin()

      current->prev = newNode;
    }
  } else {
    this->head = this->tail = newNode;  // для пустого списка
  }

  this->Size++;

  return iterator(newNode, this);
}

template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::emplace(const_iterator pos,
                                            Args &&...args) {
  node_type *new_node = new node_type(std::forward<Args>(args)...);
  new_node->next = pos.currentNode;
  new_node->prev = pos.currentNode->prev;
  pos.currentNode->prev = new_node;

  if (pos == begin()) {
    this->head = new_node;
  } else {
    new_node->prev->next = new_node;
  }

  this->Size++;

  return iterator(new_node, this);
}

template <typename T>
void list<T>::erase(iterator pos) {
  node_type *to_delete = pos.currentNode;

  if (to_delete != this->dummy) {
    if (to_delete->prev != nullptr)
      to_delete->prev->next = to_delete->next;
    else
      this->head = to_delete->next;

    if (to_delete->next != nullptr)
      to_delete->next->prev = to_delete->prev;
    else
      this->tail = to_delete->prev;

    delete to_delete;

    // std::unique_ptr<node_type> node_ptr(to_delete);

    this->Size--;
  }
}

template <typename T>
void list<T>::push_back(const_reference value) {
  list_like<T>::push_back(value);
}

template <typename T>
void list<T>::pop_back() {
  if (this->tail == nullptr) return;

  node_type *to_delete = this->tail;
  this->tail = this->tail->prev;

  if (this->tail != nullptr) this->tail->next = nullptr;

  delete to_delete;
  this->Size--;
}

template <typename T>
void list<T>::push_front(const_reference value) {
  list_like<T>::push_front(value);
}

template <typename T>
void list<T>::pop_front() {
  list_like<T>::pop_front();
}

template <typename T>
void list<T>::swap(list &other) {
  list_like<T>::swap(other);
}

template <typename T>
void list<T>::merge(list &other) {
  if (this->head == other.head) return;

  node_type *temp = new node_type();
  node_type *curr = temp;

  iterator it1 = this->begin();
  iterator it2 = other.begin();

  while (it1 != end() && it2 != other.end()) {
    if (*it1 < *it2) {
      curr->next = it1.currentNode;
      it1.currentNode->prev = curr;
      ++it1;
    } else {
      curr->next = it2.currentNode;
      it2.currentNode->prev = curr;
      ++it2;
    }
    curr = curr->next;
  }

  if (it1 != end()) {
    curr->next = it1.currentNode;
    it1.currentNode->prev = curr;
    if (it1.parentList->Size > 1)
      this->tail = it1.parentList->tail;
    else
      this->tail = curr->next;
  } else {
    curr->next = it2.currentNode;
    it2.currentNode->prev = curr;
    if (it2.parentList->Size > 1)
      this->tail = it2.parentList->tail;
    else
      this->tail = curr->next;
  }

  temp->next->prev = nullptr;
  this->head = temp->next;

  this->Size += other.Size;

  other.head = other.tail = other.dummy;
  other.Size = 0;

  delete temp;
}

template <typename T>
void list<T>::splice(const_iterator pos, list &other) {
  if (pos == pos.parentList->begin()) {
    other.tail->next = pos.currentNode;
    pos.currentNode->prev = other.tail;
    pos.parentList->head = other.head;
    pos.parentList->head->prev = pos.parentList->dummy;
  } else if (pos == pos.parentList->end()) {
    pos.currentNode->prev->next = other.head;
    other.head->prev = pos.currentNode->prev;
    other.tail->next = pos.currentNode->next;
    pos.currentNode->next->prev = other.tail;
    pos.parentList->tail = other.tail;
    pos.parentList->tail->next = pos.parentList->dummy;
  } else {
    pos.currentNode->prev->next = other.head;
    other.head->prev = pos.currentNode->prev;
    other.tail->next = pos.currentNode;
    pos.currentNode->prev = other.tail;
  }

  pos.parentList->Size += other.Size;
  other.head = other.tail = nullptr;
  other.Size = 0;
}

template <typename T>
void list<T>::reverse() {
  if (this->empty()) return;

  iterator it = this->begin();
  node_type *temp = this->head;
  this->head = this->tail;
  this->tail = temp;
  while (it != this->end()) {
    temp = it.currentNode->prev;
    it.currentNode->prev = it.currentNode->next;
    it.currentNode->next = temp;
    --it;  // потому что верх стал низом
  }
}

template <typename T>
void list<T>::unique() {
  if (this->empty()) return;

  iterator end = this->end();
  iterator prev = this->begin();
  iterator current = prev;
  ++current;

  while (current != end) {
    if (*current == *prev) {
      prev.currentNode->next = prev.currentNode->next->next;
      erase(current);
      current = prev;
      ++current;
    } else {
      prev = current;
      ++current;
    }
  }
}

template <typename T>
void list<T>::sort() {
  if (this->Size < 2) {
    return;
  }

  list<T> auxiliary;

  this->split(&auxiliary);

  this->sort();
  auxiliary.sort();

  this->merge(auxiliary);
}

// ------- Supporting -------

template <typename T>
void list<T>::split(list *other) {
  if (this->Size == 1 || this->head == other->head) return;

  node_type *fast;
  node_type *slow;
  slow = this->head;
  fast = this->head->next;

  // используем метод "зайца и черепахи"
  while (fast != NULL) {
    fast = fast->next;
    if (fast != NULL) {
      slow = slow->next;
      fast = fast->next;
    }
  }

  other->head = slow->next;
  slow->next = NULL;

  other->Size = this->Size / 2;
  if (this->Size % 2 == 1)
    this->Size = this->Size / 2 + 1;
  else
    this->Size = this->Size / 2;
}