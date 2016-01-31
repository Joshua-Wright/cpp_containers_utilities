//
// Created by j0sh on 12/11/15.
//

#ifndef CONTAINERS_STACK_H
#define CONTAINERS_STACK_H

#include <forward_list>

namespace containers {

    template<typename T>
    /*protected inherritance because we don't want someone
     * to modify the underlying list*/
    class stack : protected std::forward_list<T> {

    public:

        stack() : std::forward_list<T>() { };

        T pop() {
            /*get (and remove) the element on the top of the stack*/
            T out = this->front();
            this->pop_front();
            return out;
        }

        void push(const T &val) { std::forward_list<T>::push_front(val); }

        void push(T &&val) { std::forward_list<T>::push_front(val); }

        bool empty() { return std::forward_list<T>::empty(); }

    };

}
#endif //CONTAINERS_STACK_H
