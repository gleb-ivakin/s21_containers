#ifndef __S21LISTLIKECLASS_H__
#define __S21LISTLIKECLASS_H__

#include <iostream>
#include <limits>
#include <memory>

namespace s21 {

template <typename T>
class list_like {
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef size_t size_type;

 protected:
  template <typename value_type>
  class Node {
    friend class list_like<value_type>;
    friend class iterator;

   public:
    Node *prev;
    Node *next;
    value_type data;

    Node(value_type data = value_type(), Node *next = nullptr,
         Node *prev = nullptr) {
      this->data = data;
      this->next = next;
      this->prev = prev;
    }

    // Конструктор, принимающий указатели (для метода emplace)
    // Node(T* value) : prev(nullptr), next(nullptr), data(*value) {}

    template <typename... Args>
    Node(Args &&...args)
        : data(std::forward<Args>(args)...), prev(nullptr), next(nullptr) {}
  };

  using node_type = Node<T>;

 protected:
  Node<value_type> *head;
  Node<value_type> *tail;
  Node<value_type> *dummy;
  size_type Size;

  // ------- Supporting -------
  void CreateDummy();
  void MoveFrom(list_like<T> &&l);

  // ------- List-like Functions -------
  list_like();  // default constructor, creates empty list 
  list_like(
      size_type n);  // parameterized constructor, creates the list of Size n
  list_like(std::initializer_list<value_type> const
                &items);          // initializer list constructor
  list_like(const list_like &l);  // copy constructor
  list_like(list_like &&l);       // move constructor
  virtual ~list_like(){};         // destructor for virtual class

  // ------- List-like Element access -------
  const_reference front();  // access the first element
  const_reference back();   // access the last element

  // ------- List-like Capacity -------
  size_type size() const;    // returns the number of elements
  virtual bool empty() = 0;  // checks whether the container is empty

  // ------- List-like Modifiers -------
  void clear();                            // clears the contents
  void push_back(const_reference value);   // adds an element to the end
  void push_front(const_reference value);  // adds an element to the head
  void pop_front();                        // removes the first element
  void swap(list_like &other);             // swaps the contents
};

}  // namespace s21

#endif