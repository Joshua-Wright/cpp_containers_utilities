//
// Created by j0sh on 1/29/16.
//

#ifndef CONTAINERS_DOUBLE_LINKED_LIST_H
#define CONTAINERS_DOUBLE_LINKED_LIST_H

#include <initializer_list>
#include <bits/stl_iterator_base_types.h>

template<typename T>
class double_linked_list {

    template<typename U>
    class list_iterator;

    struct list_node {
        friend class double_linked_list<T>;

        friend class list_iterator<T>;

        list_node *_prev;
        list_node *_next;
        T _data;
    public:
        list_node(const T &val = T(),
                  list_node *_p = nullptr,
                  list_node *_n = nullptr) : _prev(_p), _next(_n),
                                             _data(val) { }
    };

    template<typename U>
    class list_iterator
            : public std::iterator<std::bidirectional_iterator_tag, U> {
        /*inherit from iterator so that iterator traits are defined properly*/

        friend class double_linked_list<T>;

        list_node *_current;
        bool _end;

    public:

        list_iterator(list_node *n, bool end = false) : _current(n), _end(end) {
        }

        /*TODO: copy constructor*/
        /*TODO: move constructor*/
        /*TODO: copy assignment*/

        list_iterator<U> &operator++() {
            if (_current->_next != nullptr) {
                _current = _current->_next;
            } else {
                _end = true;
            }
            return *this;
        }

        list_iterator<U> operator++(int) {
            list_iterator<U> old = *this;
            if (_current->_next != nullptr) {
                _current = _current->_next;
            } else {
                _end = true;
            }
            return old;
        }

        list_iterator<U> &operator--() {
            if (_current->_prev != nullptr) {
                _current = _current->_prev;
            } else {
                _end = true;
            }
            return *this;
        }

        list_iterator<U> operator--(int) {
            list_iterator<U> old = *this;
            if (_current->_prev != nullptr) {
                _current = _current->_prev;
            } else {
                _end = true;
            }
            return old;
        }

        T &operator*() {
            return _current->_data;
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
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

    list_node *_head;
    list_node *_tail;

public:

    typedef list_node node;
    typedef list_iterator<T> iterator;
    typedef list_iterator<const T> const_iterator;

    double_linked_list() : _head(nullptr), _tail(nullptr) { };

    ~double_linked_list() {
        clear();
    }

    double_linked_list(const std::initializer_list<T> &d) {
        /*TODO: initializer list*/
    }

    double_linked_list(const double_linked_list<T> &r) : _head(nullptr),
                                                         _tail(nullptr) {
        for (const auto &a : r) {
            push_back(a);
        }
    }

    double_linked_list<T> &operator=(const double_linked_list<T> &r) {
        /*TODO: copy assignment*/
        clear();
        for (const auto &a : r) {
            push_back(a);
        }
    }

    double_linked_list(double_linked_list<T> &&r) {
        /*TODO: move constructor*/
    }

    double_linked_list<T> &operator=(double_linked_list<T> &&r) {
        /*TODO: move assignment*/
    }

    void push_front(const T &val) {
        node *node1 = new node(val, nullptr, _head);
        _head = node1;
        if (node1->_next == nullptr) {
            /*this node is the only node*/
            _tail = node1;
        } else {
            /*set the next node's previous*/
            _head->_next->_prev = _head;
        }
    }

    void push_back(const T &val) {
        node *node1 = new node(val, _tail, nullptr);
        _tail = node1;
        if (node1->_prev == nullptr) {
            _head = node1;
        } else {
            _tail->_prev->_next = _tail;
        }
    }

    void pop_front() {
        if (_head != nullptr) {
            node *old = _head;
            _head = _head->_next;
            delete old;
            if (_head == nullptr) {
                _tail = nullptr;
            }
        }
    }

    void pop_back() {
        if (_tail != nullptr) {
            node *old = _tail;
            _tail = _tail->_prev;
            delete old;
            if (_tail == nullptr) {
                _head = nullptr;
            }
        }
    }

    void clear() {
        while (!empty()) {
//            pop_back();
            pop_front();
        }
    }

    bool empty() { return _head == nullptr; }

    T front() { return _head->_data; }

    T back() { return _tail->_data; }

    iterator begin() { return iterator(_head); }

    iterator end() { return iterator(_tail, true); }

    const_iterator end() const { return const_iterator(_tail, true); }

    const_iterator begin() const { return const_iterator(_head); }

    const_iterator cbegin() const { return const_iterator(_head); }

    const_iterator cend() const { return const_iterator(_tail, true); }
};


#endif //CONTAINERS_DOUBLE_LINKED_LIST_H
