//
// Created by j0sh on 2/1/16.
//

#ifndef CONTAINERS_SINGLE_LINKED_LIST_H
#define CONTAINERS_SINGLE_LINKED_LIST_H

#include <initializer_list>
#include <iterator>
#include <algorithm>


template<typename T>
class single_linked_list {

    template<typename U>
    class list_iterator;

    struct list_node {
        friend class single_linked_list<T>;

        friend class list_iterator<T>;

        friend class list_iterator<const T>;

        list_node *_next;
        T _data;
    public:
        list_node(const T &val = T(), list_node *_n = nullptr) : _next(_n),
                                                                 _data(val) { }

        ~list_node() {
            /*TODO: destructor?*/
        }
    };

    template<typename U>
    class list_iterator
            : public std::iterator<std::bidirectional_iterator_tag, U> {
        /*inherit from iterator so that iterator traits are defined properly*/

        friend class single_linked_list<T>;

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

        list_iterator<U> &operator+=(size_t x) {
            for (size_t i = 0; i < x; i++) {
                operator++();
            }
            return *this;
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

    list_node *_head;
    list_node *_tail;

public:
    typedef list_node node;
    typedef list_iterator<T> iterator;
    typedef list_iterator<const T> const_iterator;

    single_linked_list() : _head(nullptr), _tail(nullptr) { };

    ~single_linked_list() {
        clear();
    }

    single_linked_list(const std::initializer_list<T> &d) : _head(nullptr),
                                                            _tail(nullptr) {
        /*TODO: initializer list*/
        for (const auto &a : d) {
            push_back(a);
        }
    }

    single_linked_list(const single_linked_list<T> &r) : _head(nullptr),
                                                         _tail(nullptr) {
        for (const auto &a : r) {
            push_back(a);
        }
    }

    single_linked_list<T> &operator=(const single_linked_list<T> &r) {
        /*TODO: copy assignment*/
        clear();
        for (const auto &a : r) {
            push_back(a);
        }
    }

    single_linked_list(single_linked_list<T> &&r) {
        /*TODO: move constructor*/
    }

    single_linked_list<T> &operator=(single_linked_list<T> &&r) {
        /*TODO: move assignment*/
        return *this;
    }

    void push_front(const T &val) {
        if (_head == nullptr) {
            node *node1 = new node(val, nullptr);
            _head = node1;
            _tail = node1;
        } else {
            node *node1 = new node(val, _head);
            _head = node1;
        }

    }

    void push_back(const T &val) {
        node *node1 = new node(val, nullptr);
        if (_tail == nullptr) {
            _head = node1;
            _tail = node1;
        } else {
            _tail->_next = node1;
            _tail = _tail->_next;
        }
    }

    void pop_front() {
        if (_head != nullptr) {
            node *old = _head;
            _head = _head->_next;
            delete old;
            if (_head == nullptr) {
                _tail = nullptr;
            } else {
                _head->_next = nullptr;
            }
        } else {
            /*TODO: exception?*/
        }
    }

    void clear() {
        while (!empty()) {
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

    bool operator==(const single_linked_list<T> &r) {
        /*must run them both ways in case they are different lengths*/
        return std::equal(begin(), end(), r.begin()) &&
               std::equal(r.begin(), r.end(), begin());
    }

    bool operator!=(const single_linked_list<T> &r) { return !(*this == r); }

    iterator insert_after(const iterator &i, const T &val) {
        node *node1 = new node(val, i._current->_next);
        i._current->_next = node1;
        return iterator(node1);
    }
};


#endif //CONTAINERS_SINGLE_LINKED_LIST_H
