// (c) Copyright 2017 Josh Wright
#pragma once

#include "vect.h"
#include <algorithm>
#include <cassert>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace util {

template <typename T, class Alloc = std::allocator<T>>
class matrix {
  using ptr_type = typename std::allocator_traits<Alloc>::pointer;
  std::size_t width, height;
  ptr_type _data;
  Alloc a;

  ptr_type allocate(const size_t &n) {
    return std::allocator_traits<Alloc>::allocate(a, n);
  }

  void deallocate(ptr_type t, const size_t &n) {
    std::allocator_traits<Alloc>::deallocate(a, t, n);
  }

public:
  using iterator = ptr_type;

  template <size_t I, size_t J>
  matrix(const std::array<std::array<T, J>, I> &m, const Alloc &alloc = Alloc())
      : width(I), height(J),
        _data(allocate(I * J)), a(alloc) {
    for (size_t i = 0; i < width; i++) {
      for (size_t j = 0; j < width; j++) {
        (*this)(i, j) = m[i][j];
      }
    }
  }

  matrix(const std::vector<std::vector<T>> &m, const Alloc &alloc = Alloc())
      : width(m.size()), height(m[0].size()),
        _data(allocate(width * height)), a(alloc) {
    for (size_t i = 0; i < width; i++) {
      assert(m[i].size() == height);
      for (size_t j = 0; j < height; j++) {
        (*this)(i, j) = m[i][j];
      }
    }
  };

  matrix() : width(0), height(0),
             _data(nullptr),
             a(Alloc()){};

  matrix(const std::size_t x, const std::size_t y, const T initial_value = T(),
         const Alloc &alloc = Alloc())
      : width(x), height(y),
        _data(allocate(width * height)),
        a(alloc) {
    std::fill_n(_data, width * height, initial_value);
  };

  matrix(const matrix<T, Alloc> &lhs)
      : width(lhs.width),
        height(lhs.height),
        _data(), a(lhs.a) {
    std::copy_n(lhs._data, width * height, _data);
  }

  ~matrix() {
    deallocate(_data, width * height);
  }

  matrix &operator=(const matrix<T, Alloc> &lhs) {
    if (&lhs == this) {
      /*we are being assigned to ourself*/
      return *this;
    }
    a = lhs.a;
    deallocate(_data, width * height);
    width = lhs.width;
    height = lhs.height;
    _data = allocate(width * height);
    std::copy_n(lhs._data, width * height, _data);
    return *this;
  }

  matrix(matrix<T, Alloc> &&lhs)
      : width(lhs.width), height(lhs.height), _data(lhs._data), a(lhs.a) {
    lhs._data = nullptr;
    lhs.width = 0;
    lhs.height = 0;
  }

  matrix<T, Alloc> &operator=(matrix<T, Alloc> &&lhs) {
    if (&lhs == this) {
      /*we are being moved to ourself*/
      return *this;
    }
    a = lhs.a;
    deallocate(_data, width * height);
    width = lhs.width;
    height = lhs.height;
    _data = lhs._data;
    lhs._data = nullptr;
    lhs.width = 0;
    lhs.height = 0;
    return *this;
  }

  void fill(const T &val) {
    std::fill(_data, _data + (width * height), val);
  }

  std::size_t x() const {
    return width;
  }

  std::size_t y() const {
    return height;
  }

  std::size_t size() const {
    return width * height;
  }

  ptr_type data() {
    /*simple getter for the underlying array*/
    return _data;
  }

  const ptr_type data() const {
    /*simple getter for the underlying array*/
    return _data;
  }

  ptr_type begin() { // first element
    return _data;
  }

  ptr_type end() { // past the end pointer
    return _data + height * width;
  }

  const ptr_type begin() const { // first element
    return _data;
  }

  const ptr_type end() const { // past the end pointer
    return _data + height * width;
  }

  const ptr_type cbegin() const { // first element
    return _data;
  }

  const ptr_type cend() const { // past the end pointer
    return _data + height * width;
  }

  T &operator()(const std::size_t x, const std::size_t y) {
    assert(x < width && y < height);
    return _data[y * width + x];
  }

  const T &operator()(const std::size_t x, const std::size_t y) const {
    assert(x < width && y < height);
    return _data[y * width + x];
  }

  T &operator()(const vect<size_t, 2> &p) {
    return (*this)(p[0], p[1]);
  }

  const T &operator()(const vect<size_t, 2> &p) const {
    return (*this)(p[0], p[1]);
  }

  T &operator()(std::size_t z) {
    assert(z < width * height);
    return _data[z];
  }

  const T &operator()(std::size_t z) const {
    assert(z < width * height);
    return _data[z];
  }

  T &at(std::size_t z) {
    if (z >= (width * height)) {
      std::stringstream ss;
      ss << "out of range: " << z << " >= " << width << "*" << height
         << "(=" << (width * height) << ")";
      throw std::out_of_range(ss.str());
    }
    return (*this)(z);
  }

  const T &at(std::size_t z) const {
    if (z >= (width * height)) {
      std::stringstream ss;
      ss << "out of range: " << z << " >= " << width << "*" << height
         << "(=" << (width * height) << ")";
      throw std::out_of_range(ss.str());
    }
    return (*this)(z);
  }

  const T &at(const std::size_t x, const std::size_t y) const {
    if (x >= width || y >= height) {
      std::stringstream ss;
      ss << "out of range: " << x << " >= " << width << " || " << y
         << " >= " << height;
      throw std::out_of_range(ss.str());
    }
    return (*this)(x, y);
  }

  T &at(const std::size_t x, const std::size_t y) {
    if (x >= width || y >= height) {
      std::stringstream ss;
      ss << "out of range: " << x << " >= " << width << " || " << y
         << " >= " << height;
      throw std::out_of_range(ss.str());
    }
    return (*this)(x, y);
  }

  T &at(const vect<size_t, 2> &p) {
    return at(p[0], p[1]);
  }

  const T &at(const vect<size_t, 2> &p) const {
    return at(p[0], p[1]);
  }

  std::size_t z_to_x(std::size_t z) {
    return z / height;
  };

  std::size_t z_to_y(std::size_t z) {
    return z % height;
  };

  template <typename F>
  matrix<T> &operator*=(const F &lhs) {
    std::transform(begin(), end(), begin(),
                   [&lhs](const T &n) { return n * lhs; });
    return *this;
  }

  template <typename F>
  matrix<T> &operator/=(const F &lhs) {
    std::transform(begin(), end(), begin(),
                   [&lhs](const T &n) { return n / lhs; });
    return *this;
  }

  template <typename F>
  matrix<T> &operator+=(const F &lhs) {
    std::transform(begin(), end(), begin(),
                   [&lhs](const T &n) { return n + lhs; });
    return *this;
  }

  template <typename F>
  matrix<T> &operator-=(const F &lhs) {
    std::transform(begin(), end(), begin(),
                   [&lhs](const T &n) { return n - lhs; });
    return *this;
  }

  template <typename F>
  matrix<T> &operator%=(const F &lhs) {
    std::transform(begin(), end(), begin(),
                   [&lhs](const T &n) { return n % lhs; });
    return *this;
  }

  template <typename F>
  matrix<T> &fmod_in_place(const F &rhs) {
    std::transform(begin(), end(), begin(),
                   [&rhs](const T &n) { return std::fmod(n, rhs); });
    return *this;
  }

  template <typename U>
  matrix<T> &operator*=(const matrix<U> &lhs) {
    assert_same_size(lhs);
    std::transform(begin(), end(), lhs.begin(), begin(),
                   [](const T &a, const U &b) { return a * b; });
    return *this;
  }

  template <typename U>
  matrix<T> &operator/=(const matrix<U> &lhs) {
    assert_same_size(lhs);
    std::transform(begin(), end(), lhs.begin(), begin(),
                   [](const T &a, const U &b) { return a / b; });
    return *this;
  }

  template <typename U>
  matrix<T> &operator+=(const matrix<U> &lhs) {
    assert_same_size(lhs);
    std::transform(begin(), end(), lhs.begin(), begin(),
                   [](const T &a, const U &b) { return a + b; });
    return *this;
  }

  template <typename U>
  matrix<T> &operator-=(const matrix<U> &lhs) {
    assert_same_size(lhs);
    std::transform(begin(), end(), lhs.begin(), begin(),
                   [](const T &a, const U &b) { return a - b; });
    return *this;
  }

  template <typename U>
  matrix<T> &operator%=(const matrix<U> &lhs) {
    assert_same_size(lhs);
    std::transform(begin(), end(), lhs.begin(), begin(),
                   [](const T &a, const U &b) { return a % b; });
    return *this;
  }

  bool operator==(const matrix<T, Alloc> &lhs) {
    if (!dimensions_equal(lhs)) {
      return false;
    }
    return std::equal(begin(), end(), lhs.begin());
  }

  bool operator!=(const matrix<T, Alloc> &lhs) {
    return !((*this) == lhs);
  }

  bool dimensions_equal(const matrix<T, Alloc> &other) {
    return (x() == other.x()) && (y() == other.y());
  }

  void assert_same_size(const matrix<T, Alloc> &other) {
    if (!dimensions_equal(other)) {
      throw std::invalid_argument("Dimensions must match!");
    }
  }
};
}