#ifndef __S21LIST_H__
#define __S21LIST_H__

#include "s21_list_like_class.h"

namespace s21 {

template <typename T>
class list : public list_like<T> {
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef size_t size_type;

 private:
  void split(list* other);  // additional method that is used in sort() - splits
                            // the list in half

 public:
  using node_type = typename list_like<T>::node_type;

  class iterator {
    friend class list<value_type>;
    list<value_type>* parentList;
    node_type* currentNode;

   public:
    iterator(){};
    iterator(node_type* node, list<T>* parent_list);
    iterator(const iterator& other);
    iterator operator++();
    iterator operator--();
    reference operator*() const;
    bool operator!=(const iterator& i);
    bool operator==(const iterator& i);
    iterator& operator=(const iterator& other);
  };

  class const_iterator {
    friend class list<value_type>;
    list<value_type>* parentList;
    node_type* currentNode;

   public:
    const_iterator(){};
    const_iterator(const node_type* node, const list<T>* parent_list);
    const_iterator(const iterator& other);
    const_iterator operator++();
    const_iterator operator--();
    const_reference operator*() const;
    bool operator!=(const const_iterator& i);
    bool operator==(const const_iterator& i);
    const_iterator& operator=(const const_iterator& other);
  };

  // ------- List Functions -------
  list();             // default constructor, creates empty list 
  list(size_type n);  // parameterized constructor, creates the list of Size n
  list(std::initializer_list<value_type> const&
           items);      // initializer list constructor
  list(const list& l);  // copy constructor
  list(list&& l);       // move constructor
  ~list();              // destructor
  list<T>& operator=(
      list&& l);  // assignment operator overload for moving object

  // ------- List Element access -------
  const_reference front();  // access the first element
  const_reference back();   // access the last element

  // ------- List Iterators -------
  iterator begin();  // returns an iterator to the beginning
  iterator end();    // returns an iterator to the end

  // ------- List Capacity -------
  bool empty();            // checks whether the container is empty
  size_type size() const;  // returns the number of elements
  size_type max_size()
      const;  // returns the maximum possible number of elements

  // ------- List Modifiers -------
  void clear();  // clears the contents
  iterator insert(
      iterator pos,
      const_reference value);  // inserts elements into concrete pos and returns
                               // the iterator that points to the new element
  void erase(iterator pos);    // erases element at pos
  void push_back(const_reference value);   // adds an element to the end
  void pop_back();                         // removes the last element
  void push_front(const_reference value);  // adds an element to the head
  void pop_front();                        // removes the first element
  void swap(list& other);                  // swaps the contents
  void merge(list& other);                 // merges two sorted lists
  void splice(
      const_iterator pos,
      list& other);  // transfers elements from list other starting from pos
  void reverse();    // reverses the order of the elements
  void unique();     // removes consecutive duplicate elements
  void sort();       // sorts the elements

  template <typename... Args>
  iterator emplace(const_iterator pos, Args&&... args);
};

}  // namespace s21

#endif