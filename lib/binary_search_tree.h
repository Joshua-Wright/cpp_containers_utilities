//
// Created by j0sh on 2/21/16.
//

#ifndef CONTAINERS_BINARY_SEARCH_TREE_H
#define CONTAINERS_BINARY_SEARCH_TREE_H

#include <iterator>

/*TODO: move this and the iterator declaration inside the main container class?*/


template<typename K>
class binary_search_tree {

public:
    /*for debugging*/

    class tree_node {

        friend class binary_search_tree<K>;

        tree_node *_left;
        tree_node *_right;
        tree_node *_parent;
        K _key;

    public:

        tree_node() : _left(nullptr), _right(nullptr), _parent(nullptr) { }

        tree_node(tree_node *parent) : _left(nullptr), _right(nullptr),
                                       _parent(parent) { }

        tree_node(tree_node *parent, tree_node *left, tree_node *right)
                : _left(left), _right(right), _parent(parent) { }

        bool is_external() { return (_left == nullptr) && (_right == nullptr); }

        bool is_internal() { return (_left != nullptr) || (_right != nullptr); }

        bool is_root() { return (_parent == nullptr); }

        tree_node *left() { return _left; }

        tree_node *right() { return _right; }

        tree_node *parent() { return _parent; }

        void left(tree_node *n) { _left = n; }

        void right(tree_node *n) { _right = n; }

        void parent(tree_node *n) { _parent = n; }

        K key() { return _key; }

    };

    class tree_iterator
            : public std::iterator<std::bidirectional_iterator_tag, K> {
        /*TODO*/

    };


    typedef tree_node node;
    typedef tree_iterator const_iterator;
    typedef tree_iterator iterator;

    node *_root;
    /*size is number of values stored, not number of nodes*/
    std::size_t _size;

    node *_find_node(const K &key, node *current) {
//        if (cur == nullptr) {
//            cur = _root;
//        }
        if (current->is_external()) {
            return current;
        }
        if (key < current->_key) {
            return _find_node(key, current->left());
        } else if (key > current->_key) {
            return _find_node(key, current->right());
        } else {
            /*we assume that if it's neither greater than nor less than, it
             * is equal*/
            return current;
        }

        /*root is external, so return root*/
//        return _root;
    }


public:

    binary_search_tree() : _root(nullptr), _size(0) {
        /*make a new leaf node with no children*/
        _root = new node(nullptr, nullptr, nullptr);
    }

    void insert(const K &key) {
        node *n = _find_node(key, _root);
        if (n->is_external()) {
            /*only insert the new node if it's external*/
            /*set the key of the node*/
            n->_key = key;
            /*give it leaves so it's internal*/
            n->left(new node(n));
            n->right(new node(n));
            /*inserted something so increment size*/
            _size++;
        } else {
            /*if it's external, simply overwrite it*/
            n->_key = key;
        }
    }

    bool contains(const K &key) {
        return _find_node(key, _root)->is_internal();
    }

    std::size_t size() { return _size; }

    bool empty() { return (_size == 0); }


};


#endif //CONTAINERS_BINARY_SEARCH_TREE_H
