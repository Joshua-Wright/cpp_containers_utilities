//
// Created by j0sh on 2/23/16.
//

#ifndef CONTAINERS_ARRAY_LIST_H
#define CONTAINERS_ARRAY_LIST_H

#include <vector>
#include <limits>
#include "debug.h"

template<typename T>
class array_list {

    typedef std::size_t size_t;
    /*equivalent of nullptr for index*/
    static constexpr size_t npos = std::numeric_limits<size_t>::max();

    template<typename U>
    class list_iterator;

    struct list_node {
        friend class array_list<T>;

//        friend class iterator;
//        friend class const_iterator;

        size_t _prev;
        size_t _next;
        T _value;

    public:
        list_node(const T &val = T(), size_t _p = npos, size_t _n = npos)
                : _prev(_p), _next(_n),
                  _value(val) { }

        ~list_node() {
            /*TODO: destructor?*/
        }


    };

    typedef std::vector<list_node> node_container;


    template<typename U>
    class list_iterator
            : public std::iterator<std::bidirectional_iterator_tag, U> {
        /*inherit from iterator so that iterator traits are defined properly*/

        friend class array_list<T>;

        size_t _current;
        node_container &_data;
        bool _end;

    public:

        list_iterator(node_container &data, size_t n, bool end = false) : _current(
                n), _data(data), _end(end) {
        }

        /*TODO: copy constructor*/
        /*TODO: move constructor*/
        /*TODO: copy assignment*/

        list_iterator<U> &operator++() {
            if (_data.at(_current)._next != npos) {
                _current = _data.at(_current)._next;
            } else {
                _end = true;
            }
            return *this;
        }

        list_iterator<U> operator++(int) {
            list_iterator<U> old = *this;
            operator++();
            return old;
        }

        list_iterator<U> &operator--() {
            if (_end) {
                /*fallback to the end value, so that decrementing the past-end
                 * iteratork works properly*/
                _end = false;
            } else if (_data.at(_current)._prev != npos) {
                _current = _data.at(_current)._prev;
            } else {
                _end = true;
            }
            return *this;
        }

        list_iterator<U> operator--(int) {
            list_iterator<U> old = *this;
            operator--();
            return old;
        }

        list_iterator<U> &operator+=(size_t x) {
            for (size_t i = 0; i < x; i++) {
                operator++();
            }
            return *this;
        }

        list_iterator<U> &operator-=(size_t x) {
            for (size_t i = 0; i < x; i++) {
                operator--();
            }
            return *this;
        }

        T &operator*() {
            return _data.at(_current)._value;
        }

        bool operator==(const list_iterator<U> &rhs) {
            /* either both point to the same element or both are past-the-end.
             * Side effects: this means past-the-end iterators from different
             * lists will compare equal. */
            return (_current == rhs._current) && (_end == rhs._end);
        }

        bool operator!=(const list_iterator<U> &rhs) {
            return !operator==(rhs);
        }
    };

////////////////////////////////////////////////////////////////////////////////

    typedef list_node node;
    typedef list_iterator<T> iterator;
    typedef list_iterator<const T> const_iterator;

    /*indexes of the head and tail node*/
    size_t _head, _tail;
    /*size of the list*/
    size_t _size;
    /*the memory where we store our nodes*/
    node_container _data;
    /*a vector of the holes in this memory that need to be filled*/
    std::vector<size_t> _holes;

    size_t new_node(const T &val = T(), size_t _p = npos, size_t _n = npos) {
        if (!_holes.empty()) {
            /*allocate a node from a hole in the array*/
            size_t next_idx = _holes.back();
            _holes.pop_back();
            _data.at(next_idx)._value = val;
            _data.at(next_idx)._prev = _p;
            _data.at(next_idx)._next = _n;
            return next_idx;
        } else {
            /*push it back in the array*/
            _data.emplace_back(val, _p, _n);
            /*return the new index (last index)*/
            return _data.size() - 1;
        }
    }

    void _insert(size_t idx, const T &val) {
        /*inserts *after* the value*/
        if (idx == npos) {
            /*probably shouldn't be able to insert after past-end iterator, but
             * we'll allow it anyway*/
            push_back(val);
        } else {
            size_t node1 = new_node(val, idx, _data.at(idx)._next);
            /*inform the previous node of the insertion*/
            _data.at(_data.at(node1)._prev)._next = node1;
            /*and the next node, if it exists*/
            if (_data.at(node1)._next != npos) {
                _data.at(_data.at(node1)._next)._prev = node1;
            }
        }
        _size++;
    }

public:

    array_list() : _head(npos), _tail(npos), _size(0) { };

    /*TODO: initialize to specified size*/

    array_list(const std::initializer_list<T> &d) : _head(npos), _tail(npos),
                                                    _size(0) {
        _data.reserve(d.size());
        for (const auto &a : d) {
            push_back(a);
        }

    }

    /*TODO: reserve*/


    void push_back(const T &val) {
        size_t prev_node = _tail;
        size_t node1 = new_node(val, _tail, npos);
        _tail = node1;
        if (prev_node == npos) {
            _head = node1;
        } else {
            _data.at(prev_node)._next = node1;
        }
        _size++;
    }
    void insert(iterator p, const T& val) {
        _insert(p._current, val);
    }

    void push_front(const T &val) {
        size_t next_node = _head;
        size_t node1 = new_node(val, npos, _head);
        _head = node1;
        if (next_node == npos) {
            _tail = node1;
        } else {
            _data.at(next_node)._prev = node1;
        }
        _size++;
    }

    /*TODO: insert*/

    /*TODO: erase*/

    void pop_back() {
        if (_size > 0) {
            /*add the old tail index to the empty list*/
            _holes.push_back(_tail);
            /*update the tail index*/
            _tail = _data.at(_tail)._prev;
            /*update the second to last node's next index*/
            _data.at(_tail)._next = npos;
            _size--;
        } else {
            /*TODO: throw exception*/
        }
    }

    void pop_front() {
        if (_size > 0) {
            /*add the old tail index to the empty list*/
            _holes.push_back(_head);
            /*update the tail index*/
            _head = _data.at(_head)._next;
            /*update the second to last node's next index*/
            _data.at(_head)._prev = npos;
            _size--;
        } else {
            /*TODO: throw exception*/
        }
    }

    /*TODO: swap*/

    T &front() {
        return _data.at(_head)._value;
    }

    T &back() {
        return _data.at(_tail)._value;
    }

    iterator begin() { return list_iterator<T>(_data, _head, false); }

    iterator end() { return list_iterator<T>(_data, _tail, true); }

    /*TODO: const iterators*/

    size_t size() { return _size; }

    bool empty() { return (_size == 0); }


};


#endif //CONTAINERS_ARRAY_LIST_H
