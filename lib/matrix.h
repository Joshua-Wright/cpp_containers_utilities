#ifndef CONTAINERS_MATRIX
#define CONTAINERS_MATRIX

#include <stdexcept>
#include <type_traits>
#include <algorithm>

namespace containers {

    template<typename T>
    class matrix {
        std::size_t width, height;
        __restrict__ T *data;

    public:
        matrix(const std::size_t x, const std::size_t y,
               const T initial_value = T()) : width(x), height(y),
                                              data(new T[width * height]) {
            std::fill_n(data, width * height, initial_value);
        };

        matrix(const matrix<T> &lhs) : width(lhs.width), height(lhs.height),
                                       data(new T[width * height]) {
            std::copy_n(lhs.data, width * height, data);
        }

        matrix &operator=(const matrix<T> &lhs) {
            if (&lhs == this) {
                /*we are being assigned to ourself*/
                return *this;
            }
            delete[] data;
            width = lhs.width;
            height = lhs.height;
            data = new T[width * height];
            std::copy_n(lhs.data, width * height, data);
            return *this;
        }

        matrix(matrix<T> &&lhs) : width(lhs.width), height(lhs.height),
                                  data(lhs.data) {
            lhs.data = nullptr;
            lhs.width = 0;
            lhs.height = 0;
        }

        matrix<T> operator=(matrix<T> &&lhs) {
            if (&lhs == this) {
                /*we are being moved to ourself*/
                return *this;
            }
            delete[] data;
            width = lhs.width;
            height = lhs.height;
            data = lhs.data;
            lhs.data = nullptr;
            lhs.width = 0;
            lhs.height = 0;
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

        T *begin() { // first element
            return data;
        }

        T *end() { // past the end pointer
            return data + height * width;
        }

        const T *begin() const { // first element
            return (T *) data;
        }

        const T *end() const { // past the end pointer
            return data + height * width;
        }

        const T *cbegin() const { // first element
            return (T *) data;
        }

        const T *cend() const { // past the end pointer
            return data + height * width;
        }

        T &operator()(const std::size_t x, const std::size_t y) {
            if (x >= width || y >= height) {
                throw std::out_of_range("out of range");
            }
            return data[y * width + x];
        }

        const T &operator()(const std::size_t x, const std::size_t y) const {
            if (x >= width || y >= height) {
                throw std::out_of_range("out of range");
            }

            return data[x * height + y];
        }

        T &operator()(std::size_t z) {
            if (z >= (width * height)) {
                throw std::out_of_range("out of range");
            }
            return data[z];
        }

        const T &operator()(std::size_t z) const {
            if (z >= (width * height)) {
                throw std::out_of_range("out of range");
            }
            return data[z];
        }

        std::size_t z_to_x(std::size_t z) { return z / height; };

        std::size_t z_to_y(std::size_t z) { return z % height; };


        template<typename F>
        matrix<T> &operator*=(const F &lhs) {
            std::transform(begin(), end(), begin(),
                           [&lhs](const T &n) { return n * lhs; });
            return *this;
        };

        template<typename F>
        matrix<T> &operator/=(const F &lhs) {
            std::transform(begin(), end(), begin(),
                           [&lhs](const T &n) { return n / lhs; });
            return *this;
        };

        template<typename F>
        matrix<T> &operator+=(const F &lhs) {
            std::transform(begin(), end(), begin(),
                           [&lhs](const T &n) { return n + lhs; });
            return *this;
        };

        template<typename F>
        matrix<T> &operator-=(const F &lhs) {
            std::transform(begin(), end(), begin(),
                           [&lhs](const T &n) { return n - lhs; });
            return *this;
        };

        template<typename F>
        matrix<T> &operator%=(const F &lhs) {
            std::transform(begin(), end(), begin(),
                           [&lhs](const T &n) { return n % lhs; });
            return *this;
        };

        template<typename U>
        matrix<T> &operator*=(const matrix<U> &lhs) {
            assert_same_size(*this, lhs);
            std::transform(begin(), end(), lhs.begin(), begin(),
                           [](const T &a, const U &b) { return a * b; });
            return *this;
        };

        template<typename U>
        matrix<T> &operator/=(const matrix<U> &lhs) {
            assert_same_size(*this, lhs);
            std::transform(begin(), end(), lhs.begin(), begin(),
                           [](const T &a, const U &b) { return a / b; });
            return *this;
        };

        template<typename U>
        matrix<T> &operator+=(const matrix<U> &lhs) {
            assert_same_size(*this, lhs);
            std::transform(begin(), end(), lhs.begin(), begin(),
                           [](const T &a, const U &b) { return a + b; });
            return *this;
        };

        template<typename U>
        matrix<T> &operator-=(const matrix<U> &lhs) {
            assert_same_size(*this, lhs);
            std::transform(begin(), end(), lhs.begin(), begin(),
                           [](const T &a, const U &b) { return a - b; });
            return *this;
        };

        template<typename U>
        matrix<T> &operator%=(const matrix<U> &lhs) {
            assert_same_size(*this, lhs);
            std::transform(begin(), end(), lhs.begin(), begin(),
                           [](const T &a, const U &b) { return a % b; });
            return *this;
        };

        template<typename U>
        bool operator==(const matrix<U> &lhs) {
            if (!dimensions_equal(*this, lhs)) {
                return false;
            }
            return std::equal(begin(), end(), lhs.begin());
        }

        template<typename U>
        bool operator!=(const matrix<U> &lhs) {
            return !((*this) == lhs);
        }

    };

    template<typename T, typename U>
    bool dimensions_equal(const matrix<T> &a, const matrix<U> &b) {
        return (a.x() == b.x()) && (a.y() == b.y());
    };

    template<typename T, typename U>
    void assert_same_size(const matrix<T> &a, const matrix<U> &b) {
        if (!dimensions_equal(a, b)) {
            throw std::invalid_argument("Dimensions must match!");
        }
    };

}

#endif /*CONTAINERS_MATRIX*/