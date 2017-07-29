// (c) Copyright 2016-2017 Josh Wright
#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <numeric> // for accumulate
#include <ostream>

#ifndef VECT_NO_ALIGN
#define VECT_ALIGN(dim) __attribute__((aligned(upper_power_of_two(dim))))
#else
#ifndef VECT_ALIGN
#define VECT_ALIGN(dim)
#endif
#endif

namespace util {
    
namespace {
constexpr size_t upper_power_of_two(size_t v) {
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v |= v >> 32;
    v++;
    return v;
    
}
}

template <typename T, size_t dim>
struct vect : public std::array<T, dim> {
    typedef std::array<T, dim> array;
    using array::begin;
    using array::end;
    using array::cbegin;
    using array::cend;

public:
    friend std::ostream &operator<<(std::ostream &os, const vect &v) {
        os << "vect{";
        if (dim > 0) {
            os << v[0];
        }
        for (size_t i = 1; i < dim; ++i) {
            os << ", " << v[i];
        }
        os << "}";
        return os;
    }

    vect() : array() {}

    vect(const T &val) : array() { std::fill(begin(), end(), val); }

    vect(const vect<T, dim> &rhs) {
        std::copy(rhs.begin(), rhs.end(), begin());
    }

    vect(const T *data) {
        std::copy_n(data, dim, begin());
    }

    vect(const std::initializer_list<T> &list) : array() {
        if (list.size() != dim) {
            throw std::logic_error("Bad array initializer size!");
        }
        std::copy(list.begin(), list.end(), begin());
    }


    /*scalars*/
    vect<T, dim> &operator+=(const T &rhs) {
        std::transform(begin(), end(), begin(),
                       [&rhs](const T &a) { return a + rhs; });
        return *this;
    }

    vect<T, dim> &operator-=(const T &rhs) {
        std::transform(begin(), end(), begin(),
                       [&rhs](const T &a) { return a - rhs; });
        return *this;
    }

    vect<T, dim> &operator*=(const T &rhs) {
        std::transform(begin(), end(), begin(),
                       [&rhs](const T &a) { return a * rhs; });
        return *this;
    }

    vect<T, dim> &operator/=(const T &rhs) {
        std::transform(begin(), end(), begin(),
                       [&rhs](const T &a) { return a / rhs; });
        return *this;
    }

    vect<T, dim> &operator%=(const T &rhs) {
        std::transform(begin(), end(), begin(),
                       [&rhs](const T &a) { return a % rhs; });
        return *this;
    }

    /*vectors*/
    vect<T, dim> operator+=(const vect<T, dim> &rhs) {
        for (auto i1 = begin(), i2 = rhs.begin(); i1 < end(); ++i1, ++i2) {
            (*i1) += (*i2);
        }
        return *this;
    }

    vect<T, dim> operator-=(const vect<T, dim> &rhs) {
        for (auto i1 = begin(), i2 = rhs.begin(); i1 < end(); ++i1, ++i2) {
            *i1 -= *i2;
        }
        return *this;
    }

    vect<T, dim> operator*=(const vect<T, dim> &rhs) {
        for (auto i1 = begin(), i2 = rhs.begin(); i1 < end(); ++i1, ++i2) {
            *i1 *= *i2;
        }
        return *this;
    }

    vect<T, dim> operator/=(const vect<T, dim> &rhs) {
        for (auto i1 = begin(), i2 = rhs.begin(); i1 < end(); ++i1, ++i2) {
            *i1 /= *i2;
        }
        return *this;
    }

    vect<T, dim> operator%=(const vect<T, dim> &rhs) {
        for (auto i1 = begin(), i2 = rhs.begin(); i1 < end(); ++i1, ++i2) {
            *i1 %= *i2;
        }
        return *this;
    }

    vect<T, dim> operator+(const vect<T, dim> &rhs) const {
        vect<T, dim> out(*this);
        out += rhs;
        return out;
    }

    vect<T, dim> operator-(const vect<T, dim> &rhs) const {
        vect<T, dim> out(*this);
        out -= rhs;
        return out;
    }

    vect<T, dim> operator*(const vect<T, dim> &rhs) const {
        vect<T, dim> out(*this);
        out *= rhs;
        return out;
    }

    vect<T, dim> operator/(const vect<T, dim> &rhs) const {
        vect<T, dim> out(*this);
        out /= rhs;
        return out;
    }

    vect<T, dim> operator%(const vect<T, dim> &rhs) const {
        vect<T, dim> out(*this);
        out %= rhs;
        return out;
    }


    vect<T, dim> pow(const T &rhs) const {
        vect<T, dim> out;
        std::transform(begin(), end(), out.begin(),
                       [&rhs](const T &a) { return std::pow(a, rhs); });
        return out;
    }

    T norm2() const {
        return std::accumulate(begin(), end(), T(), [](const T &cur, const T &b) {
            return cur + b * b;
        });
    }

    T norm() const { return std::sqrt(norm2()); }

    vect<T, dim> unitV() const { return (*this) / norm(); };

    T sum() const {
        return std::accumulate(begin(), end(), T(), [](const T &cur, const T &b) {
            return cur + b;
        });
    }

    T avg() const {
        return sum() / dim;
    }

    T dist2(const vect<T, dim> &rhs) const { return (rhs - *this).norm2(); }

    T dist(const vect<T, dim> &rhs) const { return std::sqrt(dist2(rhs)); }

    template <typename U>
    operator vect<U, dim>() const {
        vect<U, dim> out;
        std::transform(begin(), end(), out.begin(),
                       [](const T &t) { return (U) t; });
        return out;
    }
} VECT_ALIGN(dim);

template <typename T, size_t dim>
vect<T, dim> operator+(const vect<T, dim> &lhs, const T &rhs) {
    vect<T, dim> out = lhs;
    out += rhs;
    return out;
}

template <typename T, size_t dim>
vect<T, dim> operator-(const vect<T, dim> &lhs, const T &rhs) {
    vect<T, dim> out = lhs;
    out -= rhs;
    return out;
}

template <typename T, size_t dim>
vect<T, dim> operator*(const vect<T, dim> &lhs, const T &rhs) {
    vect<T, dim> out = lhs;
    out *= rhs;
    return out;
}

template <typename T, size_t dim>
vect<T, dim> operator/(const vect<T, dim> &lhs, const T &rhs) {
    vect<T, dim> out = lhs;
    out /= rhs;
    return out;
}

template <typename T, size_t dim>
vect<T, dim> operator%(const vect<T, dim> &lhs, const T &rhs) {
    vect<T, dim> out = lhs;
    out %= rhs;
    return out;
}

template <typename T, size_t dim>
vect<T, dim> operator+(const T &rhs, const vect<T, dim> &lhs) {
    vect<T, dim> out = lhs;
    out += rhs;
    return out;
}

template <typename T, size_t dim>
vect<T, dim> operator-(const T &rhs, const vect<T, dim> &lhs) {
    vect<T, dim> out;
    std::transform(lhs.cbegin(), lhs.cend(), out.begin(),
                   [&rhs](const T &a) { return rhs - a; });
    return out;
}

template <typename T, size_t dim>
vect<T, dim> operator*(const T &rhs, const vect<T, dim> &lhs) {
    vect<T, dim> out = lhs;
    out *= rhs;
    return out;
}

template <typename T, size_t dim>
vect<T, dim> operator/(const T &rhs, const vect<T, dim> &lhs) {
    vect<T, dim> out;
    std::transform(lhs.begin(), lhs.end(), out.begin(),
                   [&rhs](const T &a) { return rhs / a; });
    return out;
}

template <typename T>
vect<T, 3> crossP(const vect<T, 3> &u, const vect<T, 3> &v) {
    vect<T, 3> out;
    out[0] = u[1] * v[2] - u[2] * v[1];
    out[1] = u[2] * v[0] - u[0] * v[2];
    out[2] = u[0] * v[1] - u[1] * v[0];
    return out;
}

template <typename T>
vect<T, 3> crossP(const vect<T, 2> &u, const vect<T, 2> &v) {
    vect<T, 3> out;
    out[0] = 0;
    out[1] = 0;
    out[2] = u[0] * v[1] - u[1] * v[0];
    return out;
}
}
