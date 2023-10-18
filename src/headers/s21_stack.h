#ifndef __S21STACK_H__
#define __S21STACK_H__

#include "s21_list_like_class.h"

namespace s21 {

template <typename T>
class stack : public list_like<T> {
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef size_t size_type;

 public:
  using node_type = typename list_like<T>::node_type;

  // ------- stack Functions -------
  stack();  // default constructor, creates empty stack
  stack(std::initializer_list<value_type> const
            &items);      // initializer list constructor, creates stack
                          // initizialized using std::initializer_list
  stack(const stack &q);  // copy constructor
  stack(stack &&q);       // move constructor
  ~stack();               // destructor
  stack<T> &operator=(
      stack &&q);  // assignment operator overload for moving object

  // ------- stack Element access -------
  const_reference top();  // access the top element

  // ------- stack Capacity -------
  bool empty();            // checks whether the container is empty
  size_type size() const;  // returns the number of elements

  // ------- stack Modifiers -------
  void push(const_reference value);  // inserts element at the top
  void pop();                        // removes the top element
  void swap(stack &other);           // swaps the contents

 private:
  // ------- stack Modifiers -------
  void clear();
};

}  // namespace s21

#endif