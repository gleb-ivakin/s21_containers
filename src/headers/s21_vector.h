#ifndef S21_VECTOR_H
#define S21_VECTOR_H
#include <initializer_list>

namespace s21 {
template <typename T>
class Vector {
  // private attributes
  size_t m_size_;
  size_t m_capacity_;
  T *arr_;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;
  /*=========================================================*/
  /*                                                         */
  /*                 VECTOR MEMBER FUNCTIONS                 */
  /*                                                         */
  /*=========================================================*/
  Vector() : m_size_(0), m_capacity_(0), arr_(nullptr) {}
  explicit Vector(size_type n)
      : m_size_(n), m_capacity_(n), arr_(n ? new T[n]() : nullptr) {}
  Vector(std::initializer_list<value_type> const &items);
  Vector(const Vector &v)
      : m_size_(v.m_size_), m_capacity_(v.m_capacity_), arr_(v.arr_){};
  Vector(Vector &&v)
      : m_size_(v.m_size_), m_capacity_(v.m_capacity_), arr_(v.arr_) {
    v.arr_ = nullptr;
    v.m_size_ = 0;
  }
  ~Vector() { delete[] arr_; }
  Vector &operator=(Vector &other);
  Vector &operator=(Vector &&other);
  /*=========================================================*/
  /*                                                         */
  /*                  VECTOR ELEMENT ACCESS                  */
  /*                                                         */
  /*=========================================================*/
  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos) { return arr_[pos]; }
  const_reference operator[](size_type pos) const { return arr_[pos]; }
  const_reference front() const { return *arr_; }
  reference front() { return *arr_; }
  const_reference back() { return *(arr_ + m_size_ - 1); }
  const_reference back() const { return *(arr_ + m_size_ - 1); }
  T *data() noexcept { return arr_; }
  /*=========================================================*/
  /*                                                         */
  /*                     VECTOR ITERATOR                     */
  /*                                                         */
  /*=========================================================*/
  iterator begin() const { return arr_; }
  iterator end() const { return arr_ + m_size_; }
  /*=========================================================*/
  /*                                                         */
  /*                     VECTOR CAPACITY                     */
  /*                                                         */
  /*=========================================================*/
  bool empty() { return !m_size_; }
  size_type max_size();
  size_type size() { return m_size_; }
  void reserve(size_type size);
  void shrink_to_fit();
  size_type capacity() { return m_capacity_; }
  /*=========================================================*/
  /*                                                         */
  /*                     VECTOR MODIFIERS                    */
  /*                                                         */
  /*=========================================================*/
  void push_back(value_type v);
  void pop_back();
  void clear();
  iterator insert(iterator pos, const T &value);
  iterator erase(iterator pos);
  void swap(Vector &other);
  /*=========================================================*/
  /*                                                         */
  /*                     VECTOR BONUS                        */
  /*                                                         */
  /*=========================================================*/
  template <typename... Args>
  iterator emplace(iterator pos, Args &&...args);
  template <typename... Args>
  void emplace_back(Args &&...args);
  /*=========================================================*/
  /*                                                         */
  /*                       ITERATORS                         */
  /*                                                         */
  /*=========================================================*/
  reference operator++() { return *(++arr_); }
  reference operator--() { return *(--arr_); }
  const_reference operator++(int) { return *(arr_++); }
  const_reference operator--(int) { return *(arr_--); }
  const_reference operator+(int n) { return *(arr_ + n); }
  const_reference operator-(int n) { return *(arr_ - n); }
  bool operator==(const iterator &it) { return arr_ == it; }
  bool operator!=(const iterator &it) { return arr_ != it; }

 private:
  void reserve_more_capacity_(size_type size);
};
}  // namespace s21

#endif  //  S21_VECTOR_H
