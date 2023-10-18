#ifndef __S21QUEUE_H__
#define __S21QUEUE_H__

#include "s21_list_like_class.h"

namespace s21 {

template <typename T>
class queue : public list_like<T> {
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef size_t size_type;

 public:
  using node_type = typename list_like<T>::node_type;

  // ------- Queue Functions -------
  queue();  // default constructor, creates empty queue
  queue(std::initializer_list<value_type> const
            &items);      // initializer list constructor, creates queue
                          // initizialized using std::initializer_list
  queue(const queue &q);  // copy constructor
  queue(queue &&q);       // move constructor
  ~queue();               // destructor
  queue<T> &operator=(
      queue &&q);  // assignment operator overload for moving object

  // ------- Queue Element access -------
  const_reference front();  // access the first element
  const_reference back();   // access the last element

  // ------- Queue Capacity -------
  bool empty();            // checks whether the container is empty
  size_type size() const;  // returns the number of elements

  // ------- Queue Modifiers -------
  void push(const_reference value);  // inserts element at the end
  void pop();                        // removes the first element
  void swap(queue &other);           // swaps the contents

 private:
  // ------- Queue Modifiers -------
  void clear();
};

}  // namespace s21

#endif