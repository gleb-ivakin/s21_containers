#ifndef S21_MULTISET_H_
#define S21_MULTISET_H_

#include "../sources/s21_set_reliz.cc"

namespace s21 {

template <typename T, typename S = T>
class multiset : public set<T, S> {
 public:
  using key_type = T;
  using value_type = std::pair<const T, T>;
  using refernce = value_type &;
  using const_reference = const value_type &;
  using iterator = iterator_set<T, S>;
  using const_iterator = const iterator_set<T, S>;
  using size_type = size_t;

 public:
  multiset() {}
  multiset(std::initializer_list<key_type> const &items);
  multiset(multiset &ms);
  multiset(multiset &&ms);
  ~multiset();
  multiset &operator=(multiset &ms);
  multiset &operator=(multiset &&ms);
  // multiset &operator=(multiset &&ms);
  // iterator begin();
  // iterator end();
  // bool empty();
  // size_type size();
  // size_type max_size();
  // void clear();
  iterator insert(const key_type &value);
  // void erase(iterator pos);
  // void swap(multiset &other);
  // void merge(multiset &other);
  size_type count(const key_type &key);
  // iterator find(const key_type &key);
  // bool contains(const key_type &key);
  std::pair<iterator, iterator> equal_range(const key_type &key);
  iterator lower_bound(const key_type &key);
  iterator upper_bound(const key_type &key);
  /////////////////////////////
  ////       Bonus        ////
  ///////////////////////////
  // template <typename... Args>
  // std::vector<std::pair<iterator,bool>> emplace(Args&&... args);

 private:
  size_type coun_key(node<T, S> knot, key_type &key);
  iterator push(node<T, S> *(&knot), std::pair<T, S> value);

};  // multiset
}  // namespace s21

#endif  // S21_MULTISET_H_