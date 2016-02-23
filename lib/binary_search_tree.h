//
// Created by j0sh on 2/21/16.
//

#ifndef CONTAINERS_BINARY_SEARCH_TREE_H
#define CONTAINERS_BINARY_SEARCH_TREE_H

#include <iterator>

/*TODO: move this and the iterator declaration inside the main container class?*/


template<typename K>
class binary_search_tree {

//public:
    /*for debugging*/

    class node {

        friend class binary_search_tree<K>;

        node *_left;
        node *_right;
        node *_parent;
        K _value;

        void set_value(const K &val) {
            _value = val;
            if (is_external()) {
                _left = new node(this);
                _right = new node(this);
            }
        }

    public:

        node() : _left(nullptr), _right(nullptr), _parent(nullptr) { }

        node(node *parent) : _left(nullptr), _right(nullptr),
                             _parent(parent) { }

        node(node *parent, node *left, node *right)
                : _left(left), _right(right), _parent(parent) { }

        bool is_external() { return (_left == nullptr) && (_right == nullptr); }

        bool is_internal() { return (_left != nullptr) || (_right != nullptr); }

        bool is_root() { return (_parent == nullptr); }

        bool has_left() { return _left != nullptr; }

        bool has_valued_left() {
            return (_left != nullptr) && (_left->is_internal());
        }

        bool has_right() { return _right != nullptr; }

        bool has_valued_right() {
            return (_right != nullptr) && (_right->is_internal());
        }

        node *left() { return _left; }

        node *right() { return _right; }


        node *parent() { return _parent; }

        void left(node *n) { _left = n; }

        void right(node *n) { _right = n; }

        void parent(node *n) { _parent = n; }

        K value() { return _value; }

    };

    class tree_iterator
            : public std::iterator<std::bidirectional_iterator_tag, K> {
        node *_current;

        friend class binary_search_tree<K>;

        static node *first_node(node *n) {
            if (n == nullptr) {
                return nullptr;
            } else if (n->has_valued_left()) {
                return first_node(n->left());
            } else {
                return n;
            }
        }

        static node *next_node(node *n) {
            /*TODO: make sure this works for empty and single node trees*/
            if (n->has_valued_right()) {
                /*find the right subtree*/
                return first_node(n->right());
            } else if (n->is_external()) {
                /*next is the parent*/
                return n->parent();
            } else {
                /*TODO: check this for nullptr validity*/
                node *child = n;
                node *parent = n->parent();
                /*as long as we're coming back up from the right subtree*/
                while ((parent->right() == child) && (!parent->is_root())) {
                    /*traverse up the tree*/
                    parent = parent->parent();
                    child = child->parent();
                }
                if (parent->is_root() && parent->right() == child) {
                    /*finished traversing the right subtree of the root node,
                     * therefore we are done iterating*/
                    return nullptr;
                }
                /*we just traversed up from a left subtree, so the next is the
                 * parent of that subtree*/
                return parent;
            }
        }

    public:

        tree_iterator(node *start) : _current(first_node(start)) { }

        tree_iterator &operator++() {
            /*TODO*/
            _current = next_node(_current);
            return *this;
        }

        tree_iterator &operator--() {
            /*TODO*/
            return *this;
        }

        K operator*() {
            return _current->value();
        }

        bool operator!=(const tree_iterator &rhs) {
            return rhs._current != _current;
        }

    };


    typedef tree_iterator const_iterator;
    typedef tree_iterator iterator;

    node *_root;
    /*size is number of values stored, not number of nodes*/
    std::size_t _size;


protected:
    node *_find_node(const K &key, node *current) {
        if (current->is_external()) {
            /*done searching*/
            return current;
        }
        if (key < current->_value) {
            /*search the left subtree*/
            return _find_node(key, current->left());
        } else if (key > current->_value) {
            /*search the right subtree*/
            return _find_node(key, current->right());
        } else {
            /*we assume that if it's neither greater than nor less than, it
             * is equal*/
            return current;
        }
    }


public:

    binary_search_tree() : _root(nullptr), _size(0) {
        /*make a new leaf node with no children*/
        _root = new node(nullptr, nullptr, nullptr);
    }

    void insert(const K &key) {
        /*find the node*/
        node *n = _find_node(key, _root);
        /*let it set it's own value (duplicate keys aren't allowed)*/
        n->set_value(key);
        /*keep track of size*/
        _size++;
    }

    bool contains(const K &key) {
        /*found internal node means it's value is valid*/
        return _find_node(key, _root)->is_internal();
    }

    std::size_t size() { return _size; }

    bool empty() { return (_size == 0); }

    iterator begin() { return iterator(_root); }

    iterator end() { return iterator(nullptr); }


};


#endif //CONTAINERS_BINARY_SEARCH_TREE_H
