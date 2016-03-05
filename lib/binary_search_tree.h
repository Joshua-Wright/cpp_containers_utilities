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

        ~node() {
            delete _left;
            delete _right;
        }

        bool is_external() { return (_left == nullptr) && (_right == nullptr); }

        bool is_internal() { return (_left != nullptr) || (_right != nullptr); }

        bool is_root() { return (_parent == nullptr); }

        bool has_left() { return _left != nullptr; }

        bool has_right() { return _right != nullptr; }

        bool has_internal_left() {
            return (_left != nullptr) && (_left->is_internal());
        }

        bool has_internal_right() {
            return (_right != nullptr) && (_right->is_internal());
        }

        bool has_internal_child() {
            return (has_internal_left() || has_internal_right());
        }

        node *left() { return _left; }

        node *right() { return _right; }


        node *parent() { return _parent; }

        void left(node *n) { _left = n; }

        void right(node *n) { _right = n; }

        void parent(node *n) { _parent = n; }

        K value() { return _value; }

    };

    static node *first_node(node *n) {
        if (n == nullptr) {
            return nullptr;
        } else if (n->has_internal_left()) {
            return first_node(n->left());
        } else {
            return n;
        }
    }

    static node *next_node(node *n) {
        /*TODO: make sure this works for empty and single node trees*/
        if (n->has_internal_right()) {
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

    class tree_iterator
            : public std::iterator<std::bidirectional_iterator_tag, K> {

        friend class binary_search_tree<K>;

        /*pointer to the node we're currently at*/
        node *_current;

    public:

        tree_iterator(node *start) : _current(start) { }

        tree_iterator &operator++() {
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

    size_t _height(node *n = nullptr) {
        if (n == nullptr) {
            // n = _root;
            return 0;
        }
        if (n->is_external()) {
            return 0;
        } else {
            size_t h_left = _height(n->_left) + 1;
            size_t h_right = _height(n->_right) + 1;
            /*max of the two heights*/
            return (h_left > h_right) ? h_left : h_right;
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

    void remove(const K &key) {
        /*TODO*/
        node *n = _find_node(key, _root);
        if (n->has_internal_child()) {
            /*handle deleting internal node with internal children*/
        } else {
            /*node has no internal children*/
            if (!n->is_root()) {
                node *p = n->parent();
                if (p->right() == n) {
                    /*we're deleting the right node of this parent node*/
                    delete n; /*expect the node to clean up it's children*/
                    /*give the parent node a leaf child in n's place*/
                    p->right(new node(p));
                } else {
                    /*same thing for left child*/
                    delete n;
                    p->left(new node(p));
                }
            }
        }
    }

    std::size_t size() { return _size; }

    bool empty() { return (_size == 0); }

    iterator begin() { return iterator(first_node(_root)); }

    iterator end() { return iterator(nullptr); }

    size_t max_height() { return _height(_root); }


    void print_tree(node* start = nullptr, const size_t indent = 0) {
        if (start == nullptr) {
            start = _root;
        }
        /*print current nodenode*/
        for (size_t i=0; i<indent; i++){std::cout << "\t";}
        std::cout << start->_value << std::endl;
        /*print left node if it exists*/
        // for (size_t i=0; i<indent; i++){std::cout << "\t";}
        if (start->has_internal_left()) {
            print_tree(start->_left, indent + 1);
        }
        /*print right node if it exists*/
        // for (size_t i=0; i<indent; i++){std::cout << "\t";}
        if (start->has_internal_right()) {
            print_tree(start->_right, indent + 1);
        }
        
        
    }

};


#endif //CONTAINERS_BINARY_SEARCH_TREE_H
