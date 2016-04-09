//
// Created by j0sh on 4/5/16.
//

#ifndef CONTAINERS_VECT_H
#define CONTAINERS_VECT_H

#include <cmath>
#include <array>
#include <algorithm>


namespace containers {


  template<typename T, size_t dim>
  struct vect : public std::array<T, dim> {
    typedef std::array<T, dim> array;
    using array::begin;
    using array::end;
    using array::cbegin;
    using array::cend;
  public:

    vect() : array() { }

    vect(const std::initializer_list<T> &list) : array() {
      if (list.size() != dim) {
        throw std::logic_error("Bad array initializer size!");
      }
      std::copy(list.begin(), list.end(), begin());
    }

    vect<T, dim> &operator+=(const T &rhs) {
      std::transform(begin(), end(), begin(),
                     [&rhs](const T &a) { return a + rhs; });
      return *this;
    };

    vect<T, dim> &operator-=(const T &rhs) {
      std::transform(begin(), end(), begin(),
                     [&rhs](const T &a) { return a - rhs; });
      return *this;
    };

    vect<T, dim> &operator*=(const T &rhs) {
      std::transform(begin(), end(), begin(),
                     [&rhs](const T &a) { return a * rhs; });
      return *this;
    };

    vect<T, dim> &operator/=(const T &rhs) {
      std::transform(begin(), end(), begin(),
                     [&rhs](const T &a) { return a / rhs; });
      return *this;
    };

    vect<T, dim> &operator%=(const T &rhs) {
      std::transform(begin(), end(), begin(),
                     [&rhs](const T &a) { return a % rhs; });
      return *this;
    };

    vect<T, dim> &pow(const T &rhs) {
      std::transform(begin(), end(), begin(),
                     [&rhs](const T &a) { return std::pow(a, rhs); });
      return *this;
    };

    T norm2() {
      return std::accumulate(begin(), end(), T(), [](const T &cur, const T &b) {
        return cur + b * b;
      });
    };

    T norm() { return std::sqrt(norm2()); }



    /*TODO: vector-to-vector element-wise operators*/
    vect<T, dim> operator+(const vect<T, dim> &rhs) {
      vect<T, dim> out;
      for (auto i1 = begin(), i2 = rhs.begin(), o1 = out.begin();
           o1 < out.end(); ++i1, ++i2, ++o1) {
        *o1 = *i1 + *i2;
      }
      return out;
    }
    /*TODO: - */
    /*TODO: * */
    /*TODO: / */
    /*TODO: % */



    /*TODO: C-style cast to other vect<U,dim> type*/

  };

  template<typename T, size_t dim>
  vect<T, dim> operator+(const vect<T, dim> &lhs, const T &rhs) {
    vect<T, dim> out = lhs;
    out += rhs;
    return out;
  }

  template<typename T, size_t dim>
  vect<T, dim> operator-(const vect<T, dim> &lhs, const T &rhs) {
    vect<T, dim> out = lhs;
    out -= rhs;
    return out;
  }

  template<typename T, size_t dim>
  vect<T, dim> operator*(const vect<T, dim> &lhs, const T &rhs) {
    vect<T, dim> out = lhs;
    out *= rhs;
    return out;
  }

  template<typename T, size_t dim>
  vect<T, dim> operator/(const vect<T, dim> &lhs, const T &rhs) {
    vect<T, dim> out = lhs;
    out /= rhs;
    return out;
  }

  template<typename T, size_t dim>
  vect<T, dim> operator%(const vect<T, dim> &lhs, const T &rhs) {
    vect<T, dim> out = lhs;
    out %= rhs;
    return out;
  }

  template<typename T, size_t dim>
  vect<T, dim> operator+(const T &rhs, const vect<T, dim> &lhs) {
    vect<T, dim> out = lhs;
    out += rhs;
    return out;
  }

  template<typename T, size_t dim>
  vect<T, dim> operator-(const T &rhs, const vect<T, dim> &lhs) {
    vect<T, dim> out;
    std::transform(lhs.cbegin(), lhs.cend(), out.begin(),
                   [&rhs](const T &a) { return rhs - a; });
    return out;
  }

  template<typename T, size_t dim>
  vect<T, dim> operator*(const T &rhs, const vect<T, dim> &lhs) {
    vect<T, dim> out = lhs;
    out *= rhs;
    return out;
  }

  template<typename T, size_t dim>
  vect<T, dim> operator/(const T &rhs, const vect<T, dim> &lhs) {
    vect<T, dim> out;
    std::transform(lhs.begin(), lhs.end(), out.begin(),
                   [&rhs](const T &a) { return rhs / a; });
    return out;
  }

}



#endif //CONTAINERS_VECT_H
