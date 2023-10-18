#ifndef S21_SET_H_
#define S21_SET_H_

#include "../sources/s21_virtual_assoc_reliz.cc"

namespace s21 {

template <typename T, typename S = T>
class set : public virtual_map_set<T, S> {
 public:
  ////////////////////////////
  ////  Set Member type  ////
  //////////////////////////
  using key_type = T;
  using value_type = std::pair<const T, T>;
  using refernce = value_type &;
  using const_reference = const value_type &;
  using iterator = iterator_set<T, S>;
  using const_iterator = const iterator_set<T, S>;
  using size_type = size_t;
  /////////////////////////////
  ////Set Member functions////
  ///////////////////////////
  set(){};
  set(std::initializer_list<key_type> const &items);
  set(set &s);  /// убрал const
  set(set &&s);
  ~set() { this->destroy(this->root_); };
  set &operator=(set &s);
  set &operator=(set &&s);
  /////////////////////////////
  ////   Set Iterators    ////
  ///////////////////////////
  iterator begin();
  iterator end();
  //   /////////////////////////////
  //   ////    Set Capacity    ////
  //   ///////////////////////////
  //   bool empty();
  //   size_type size();
  //   size_type max_size();
  //   /////////////////////////////
  //   ////   Set Modifiers    ////
  //   ///////////////////////////
  //   void clear();
  std::pair<iterator, bool> insert(const key_type &key);
  void erase(iterator pos);
  //   void swap(set &other);
  void merge(set &other);
  /////////////////////////////
  ////     Set Lookup     ////
  ///////////////////////////
  iterator find(const T &key);
  //   bool contains(const T &key);
  /////////////////////////////
  ////        Bonus       ////
  ///////////////////////////
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> emplace(Args &&...args);

 protected:
  std::pair<iterator, bool> push(node<T, S> *(&knot), std::pair<T, S> value);
};  // set
}  // namespace s21

#endif  // S21_SET_H_