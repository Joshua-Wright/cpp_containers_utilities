// (c) Copyright 2015 Josh Wright
#ifndef CONTAINERS_DYNAMIC_ARRAY_H
#define CONTAINERS_DYNAMIC_ARRAY_H

#include <cstring>
#include <algorithm>
#include <stdexcept>

namespace containers {

    template<typename T>
    class dynamic_array {


        std::size_t _capacity;
        std::size_t _size;

        T *_data;

        void grow(size_t new_size) {
            /*does not change size, only capacity*/
            _capacity = new_size;
            /*growing always fills with zeros*/
            T *new_data = new T[_capacity];
            /*don't bother filling them because they aren't accessible without using data()*/
            std::copy_n(_data, _size, new_data);
            /*free the previous array*/
            delete[] _data;
            _data = new_data;
        };

    public:

        dynamic_array(const size_t size = 0, const T initial_value = T()) : _capacity(size), _size(size),
                                                                            _data(new T[_capacity]) {
            std::fill_n(_data, _capacity, initial_value);
        }

        dynamic_array(const dynamic_array<T> &lhs) : _size(lhs._size), _capacity(lhs._size), _data(new T[_capacity]) {
            std::copy_n(lhs._data, _size, _data);

        };

        dynamic_array &operator=(const dynamic_array<T> &lhs) {
            if (&lhs == this) {
                /*we are being assigned to ourself*/
                return *this;
            }
            delete[] _data;
            _size = lhs._size;
            _capacity = lhs._size;
            _data = new T[_capacity];
            std::copy_n(lhs._data, _size, _data);
            return *this;
        }

        dynamic_array(dynamic_array<T> &&lhs) : _size(lhs._size), _capacity(lhs._size), _data(lhs._data) {
            lhs._data = nullptr;
            lhs._size = 0;
            lhs._capacity = 0;
        }

        dynamic_array<T> &operator=(dynamic_array<T> &&lhs) {
            if (&lhs == this) {
                /*we are being moved to ourself*/
                return *this;
            }
            delete[] _data;
            _size = lhs._size;
            _capacity = lhs._size;
            _data = lhs._data;
            lhs._data = nullptr;
            lhs._size = 0;
            lhs._capacity = 0;
            return *this;

        }

        ~dynamic_array() { delete[] _data; }

        const size_t size() const { return _size; };

        const size_t capacity() const { return _capacity; };

        T *begin() { return _data; };

        const T *begin() const { return _data; };

        T *end() { return _data + _size; };

        const T *end() const { return _data + _size; };

        const T *data() const { return _data; };

        T *data() { return _data; };

        T &operator[](const size_t idx) {
            if (idx < 0 || idx >= _size) {
                throw std::out_of_range("Out of range");
            }
            return _data[idx];
        };

        const T &operator[](const size_t idx) const {
            if (idx < 0 || idx >= _size) {
                throw std::out_of_range("Out of range");
            }
            return _data[idx];
        };

        void append(const T element) {
            if (_size == _capacity) {
                /*geomertric progression*/
                grow(_size * 2);
            }
            /*this is safe because there is extra padding space after _size*/
            _data[_size] = element;
            _size++;
        }

        template<typename F>
        dynamic_array<T> &operator*=(const F &lhs) {
            std::transform(begin(), end(), begin(), [&lhs](const T &n) { return n * lhs; });
            return *this;
        };

        template<typename F>
        dynamic_array<T> &operator/=(const F &lhs) {
            std::transform(begin(), end(), begin(), [&lhs](const T &n) { return n / lhs; });
            return *this;
        };

        template<typename F>
        dynamic_array<T> &operator+=(const F &lhs) {
            std::transform(begin(), end(), begin(), [&lhs](const T &n) { return n + lhs; });
            return *this;
        };

        template<typename F>
        dynamic_array<T> &operator-=(const F &lhs) {
            std::transform(begin(), end(), begin(), [&lhs](const T &n) { return n - lhs; });
            return *this;
        };

        template<typename F>
        dynamic_array<T> &operator%=(const F &lhs) {
            std::transform(begin(), end(), begin(), [&lhs](const T &n) { return n % lhs; });
            return *this;
        };

        template<typename U>
        dynamic_array<T> &operator*=(const dynamic_array<U> &lhs) {
            if (_size != lhs.size()) {
                throw std::invalid_argument("vector dimensions must match!");
            }
            std::transform(begin(), end(), lhs.begin(), begin(), [](const T &a, const U &b) { return a * b; });
            return *this;
        };

        template<typename U>
        dynamic_array<T> &operator/=(const dynamic_array<U> &lhs) {
            if (_size != lhs.size()) {
                throw std::invalid_argument("vector dimensions must match!");
            }
            std::transform(begin(), end(), lhs.begin(), begin(), [](const T &a, const U &b) { return a / b; });
            return *this;
        };

        template<typename U>
        dynamic_array<T> &operator+=(const dynamic_array<U> &lhs) {
            if (_size != lhs.size()) {
                throw std::invalid_argument("vector dimensions must match!");
            }
            std::transform(begin(), end(), lhs.begin(), begin(), [](const T &a, const U &b) { return a + b; });
            return *this;
        };

        template<typename U>
        dynamic_array<T> &operator-=(const dynamic_array<U> &lhs) {
            if (_size != lhs.size()) {
                throw std::invalid_argument("vector dimensions must match!");
            }
            std::transform(begin(), end(), lhs.begin(), begin(), [](const T &a, const U &b) { return a - b; });
            return *this;
        };

        template<typename U>
        dynamic_array<T> &operator%=(const dynamic_array<U> &lhs) {
            if (_size != lhs.size()) {
                throw std::invalid_argument("vector dimensions must match!");
            }
            std::transform(begin(), end(), lhs.begin(), begin(), [](const T &a, const U &b) { return a % b; });
            return *this;
        };


        template<typename U>
        bool operator==(const dynamic_array<U> &lhs) { return std::equal(begin(), end(), lhs.begin(), lhs.end()); };

        template<typename U>
        bool operator!=(const dynamic_array<U> &lhs) { return !std::equal(begin(), end(), lhs.begin(), lhs.end()); };

        void resize(const size_t new_size) {
            if (new_size < _size) {
                _size = new_size;
            } else if (new_size > _capacity) {
                grow(new_size);
                _size = new_size;
            }
        };

        void clear() {
            /*do not actually delete anything, so we can reuse memory*/
            _size = 0;
        }

    };

}
#endif //CONTAINERS_DYNAMIC_ARRAY_H
