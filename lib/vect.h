//
// Created by j0sh on 4/5/16.
//

#ifndef CONTAINERS_VECT_H
#define CONTAINERS_VECT_H

#include <array>
#include <algorithm>


namespace containers {


  template<typename T, size_t dim>
  struct vect : public std::array<T, dim> {
    typedef std::array<T, dim> array;
  public:

    vect() : array() { }

    vect(const std::initializer_list<T> &list) : array() {
      if (list.size() != dim) {
        throw std::logic_error("Bad array initializer size!");
      }
      std::copy(list.begin(), list.end(), array::begin());
    }

    template<typename U>
    bool operator!=(const vect<T, dim> &rhs) {
      return !operator==(rhs);
    }

    template<typename U>
    vect<T, dim> &operator+=(const U &rhs) {
      for (auto &x : *this) {
        x += rhs;
      }
      return *this;
    }

    template<typename U>
    vect<T, dim> &operator-=(const U &rhs) {
      for (auto &x : *this) {
        x -= rhs;
      }
      return *this;
    };

    template<typename U>
    vect<T, dim> &operator*=(const U &rhs) {
      for (auto &x : *this) {
        x *= rhs;
      }
      return *this;
    };

    template<typename U>
    vect<T, dim> &operator/=(const U &rhs) {
      for (auto &x : *this) {
        x /= rhs;
      }
      return *this;
    };

    template<typename U>
    vect<T, dim> &operator%=(const U &rhs) {
      for (auto &x : *this) {
        x %= rhs;
      }
      return *this;
    };

  };

  template<typename T, size_t dim, typename U>
  vect<T, dim> operator+(const vect<T, dim> &lhs, const U &rhs) {
    vect<T, dim> out = lhs;
    out += rhs;
    return out;
  }

  template<typename T, size_t dim, typename U>
  vect<T, dim> operator-(const vect<T, dim> &lhs, const U &rhs) {
    vect<T, dim> out = lhs;
    out -= rhs;
    return out;
  }

  template<typename T, size_t dim, typename U>
  vect<T, dim> operator*(const vect<T, dim> &lhs, const U &rhs) {
    vect<T, dim> out = lhs;
    out *= rhs;
    return out;
  }

  template<typename T, size_t dim, typename U>
  vect<T, dim> operator/(const vect<T, dim> &lhs, const U &rhs) {
    vect<T, dim> out = lhs;
    out /= rhs;
    return out;
  }

  template<typename T, size_t dim, typename U>
  vect<T, dim> operator%(const vect<T, dim> &lhs, const U &rhs) {
    vect<T, dim> out = lhs;
    out %= rhs;
    return out;
  }

  template<typename T, size_t dim, typename U>
  vect<T, dim> operator+(const U &rhs, const vect<T, dim> &lhs) {
    vect<T, dim> out = lhs;
    out += rhs;
    return out;
  }

  template<typename T, size_t dim, typename U>
  vect<T, dim> operator-(const U &rhs, const vect<T, dim> &lhs) {
    vect<T, dim> out = lhs;
    std::transform(out.begin(), out.end(), out.begin(),
                   [&rhs](T &a) { return rhs - a; });
    return out;
  }

  template<typename T, size_t dim, typename U>
  vect<T, dim> operator*(const U &rhs, const vect<T, dim> &lhs) {
    vect<T, dim> out = lhs;
    out *= rhs;
    return out;
  }

  template<typename T, size_t dim, typename U>
  vect<T, dim> operator/(const U &rhs, const vect<T, dim> &lhs) {
    vect<T, dim> out = lhs;
    std::transform(out.begin(), out.end(), out.begin(),
                   [&rhs](T &a) { return rhs / a; });
    return out;
  }

}


#endif //CONTAINERS_VECT_H
