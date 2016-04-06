//
// Created by j0sh on 4/5/16.
//

#ifndef CONTAINERS_VECT_H
#define CONTAINERS_VECT_H

#include <array>


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
    vect<T, dim> &operator+=(const U &rhs) {
      for (auto &x : *this) {
        x += rhs;
      }
      return *this;
    }

    template<typename U>
    bool operator==(const vect<T, dim> &rhs) {
      return std::equal(this->begin(), this->end(), rhs.begin(), rhs.end());
    }

    template<typename U>
    bool operator!=(const vect<T, dim> &rhs) {
      return !operator==(rhs);
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

  };

}
#endif //CONTAINERS_VECT_H
