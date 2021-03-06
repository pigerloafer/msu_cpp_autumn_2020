#pragma ones

#include <iostream>
#include <functional>

template <typename T>
class array
{
public:
  array() = default;
  array(const size_t &size);
  array(T *data_, const size_t &size);
  array(const std::initializer_list<T> &list);
  array(const array &other);
  ~array();

  array<T>& operator=(const array<T> &rhs);
  const T& operator[](const size_t &index) const;
  T& operator[](const size_t &index);

  const T *begin() const;
  T *begin();

  const T *end() const;
  T *end();

  size_t size() const;

  array apply(std::function<void(T &object)> func) const;
  array& apply_inplace(std::function<void(T &object)> func);

  array operator+(const T &rhs) const;

  array& operator+=(const T &rhs);

  array operator-(const T &rhs) const;

  array& operator-=(const T &rhs);

  array operator*(const T &rhs) const;

  array& operator*=(const T &rhs);

  array operator/(const T &rhs) const;

  array& operator/=(const T &rhs);

private:
  size_t size_ = 0;
  T *data_ = nullptr;
};

//----------------------------------------------------------------------
//Implementation

template <typename T>
array<T>::array(const size_t &size)
    : size_(size),
      data_(new T[size_])
{
}

template <typename T>
array<T>::array(T *data, const size_t &size)
    : size_(size),
      data_(new T[size_])
{
  std::copy(data, data + size, data_);
}

template <typename T>
array<T>::array(const array<T> &other)
    : size_(other.size_),
      data_(new T[size_])
{
  std::copy(other.begin(), other.end(), data_);
}

template <typename T>
array<T>::array(const std::initializer_list<T> &list)
    : size_(list.size()),
      data_(new T[size_])
{
  std::copy(list.begin(), list.end(), data_);
}

template <typename T>
array<T>::~array()
{
  delete[] data_;
}

template <typename T>
array<T>& array<T>::operator=(const array<T> &rhs)
{
  if (rhs.size_ <= size_)
  {
    std::copy(rhs.begin(), rhs.end(), data_);
  }
  else
  {
    array<T> tmp(rhs);
    std::swap(tmp.data_, data_);
    std::swap(tmp.size_, size_);
  }
  return *this;
}

template <typename T>
const T& array<T>::operator[](const size_t &index) const
{
  if (index >= size_)
  {
    throw std::out_of_range("Index out of range.");
  }
  else
  {
    return data_[index];
  }
}

template <typename T>
T& array<T>::operator[](const size_t &index)
{
  if (index >= size_)
  {
    throw std::out_of_range("Index out of range.");
  }
  else
  {
    return data_[index];
  }
}

template <typename T>
size_t array<T>::size() const
{
  return size_;
}

template <typename T>
array<T> array<T>::apply(std::function<void(T &object)> func) const
{
  array<T> result(*this);
  for (auto &object : result)
  {
    func(object);
  }
  return result;
}

template <typename T>
array<T>& array<T>::apply_inplace(std::function<void(T &object)> func)
{
  for (auto &object : *this)
  {
    func(object);
  }
  return *this;
}

template <typename T>
array<T> array<T>::operator+(const T &rhs) const
{
  return this->apply([&rhs](T &object) { object += rhs; });
}

template <typename T>
array<T>& array<T>::operator+=(const T &rhs)
{
  return this->apply_inplace([&rhs](T &object) { object += rhs; });
}

template <typename T>
array<T> array<T>::operator-(const T &rhs) const
{
  return this->apply([rhs](T &object) { object -= rhs; });
}

template <typename T>
array<T>& array<T>::operator-=(const T &rhs)
{
  return this->apply_inplace([&rhs](T &object) { object -= rhs; });
}

template <typename T>
array<T> array<T>::operator*(const T &rhs) const
{
  return this->apply([rhs](T &object) { object *= rhs; });
}

template <typename T>
array<T>& array<T>::operator*=(const T &rhs)
{
  return this->apply_inplace([&rhs](T &object) { object *= rhs; });
}

template <typename T>
array<T> array<T>::operator/(const T &rhs) const
{
  return this->apply([rhs](T &object) { object /= rhs; });
}

template <typename T>
array<T>& array<T>::operator/=(const T &rhs)
{
  return this->apply_inplace([&rhs](T &object) { object /= rhs; });
}

template <typename T>
const T *array<T>::begin() const
{
  return data_;
}

template <typename T>
T *array<T>::begin()
{
  return data_;
}

template <typename T>
const T *array<T>::end() const
{
  return data_ + size_;
}

template <typename T>
T *array<T>::end()
{
  return data_ + size_;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const array<T> &arr) {
  os << "[";
  for (auto it = arr.begin(); it != arr.end(); ++it) {
    os << *it << (it + 1 != arr.end() ? ", " : "");
  }
  os << "]";
  return os;
}