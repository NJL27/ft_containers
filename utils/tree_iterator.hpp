#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include "type_traits.hpp"

namespace ft {

template <class T>
struct node;
template <class T>
node<T>* tree_min(node<T>* x);
template <class T>
node<T>* tree_max(node<T>* x);

template <class T, class Val>
class tree_iterator {
   public:
    typedef ft::bidirectional_iterator_tag iterator_category;
    typedef T                              node_ptr;
    typedef std::ptrdiff_t                 difference_type;
    typedef Val                            value_type;
    typedef value_type&                    reference;
    typedef const value_type&              const_reference;
    typedef value_type*                    pointer;

    tree_iterator(const node_ptr& ptr = NULL) : _ptr(ptr) {}

    tree_iterator(const tree_iterator& other) : _ptr(other._ptr) {}

    ~tree_iterator() {}

    node_ptr base() const { return (_ptr); }

    tree_iterator& operator=(const tree_iterator& other) {
        if (*this != other) {
            _ptr = other._ptr;
        }
        return (*this);
    }

    tree_iterator& operator++() {
        _ptr = _tree_next_iter(_ptr);
        return (*this);
    }

    tree_iterator operator++(int) {
        tree_iterator tmp(*this);
        ++(*this);
        return (tmp);
    }

    tree_iterator& operator--() {
        _ptr = _tree_prev_iter(_ptr);
        return (*this);
    }

    tree_iterator operator--(int) {
        tree_iterator tmp(*this);
        --(*this);
        return (tmp);
    }

    pointer operator->() const { return (_ptr->key); }

    reference operator*() const { return (*_ptr->key); }

   private:
    node_ptr _ptr;

    bool _tree_is_left_child(node_ptr node) { return (node == node->parent->left); }

    node_ptr _tree_next_iter(node_ptr node) {
        if (!node->right->is_leaf)
            return (tree_min(node->right));
        while (!_tree_is_left_child(node)) {
            node = node->parent;
        }

        return (node->parent);
    }

    node_ptr _tree_prev_iter(node_ptr node) {
        if (!node->left->is_leaf)
            return (tree_max(node->left));
        node_ptr new_node = static_cast<node_ptr>(node);
        while (_tree_is_left_child(new_node))
            new_node = new_node->parent;

        return (new_node->parent);
    }
};

template <class T, class Val>
bool operator==(const tree_iterator<T, Val>& x, const tree_iterator<T, Val>& y) {
    return x.base() == y.base();
}

template <class T, class Val>
bool operator!=(const tree_iterator<T, Val>& x, const tree_iterator<T, Val>& y) {
    return !(x == y);
}

template <class T>
struct node;
template <class T>
node<T>* tree_min(node<T>* x);
template <class T>
node<T>* tree_max(node<T>* x);

template <class T, class Val>
class const_tree_iterator {
   public:
    typedef ft::bidirectional_iterator_tag iterator_category;
    typedef T                              const_node_ptr;
    typedef std::ptrdiff_t                 difference_type;
    typedef Val                            value_type;
    typedef const value_type&              reference;
    typedef const value_type*              pointer;
    typedef ft::tree_iterator<typename ft::node<value_type>::node_pointer, value_type>
        normal_tree_iterator;

    const_tree_iterator(const const_node_ptr& ptr = NULL) : _ptr(ptr) {}

    const_tree_iterator(const const_tree_iterator &other) : _ptr(other._ptr) {}

    const_tree_iterator(const normal_tree_iterator &other) : _ptr(other.base()) {}

    ~const_tree_iterator() {}

    const_node_ptr base() const { return (_ptr); }

    const_tree_iterator& operator=(const const_tree_iterator &other) {
        if (*this != other) {
            _ptr = other._ptr;
        }
        return (*this);
    }

    const_tree_iterator& operator=(normal_tree_iterator &other) {
        if (*this != other) {
            _ptr = other._ptr;
        }
        return (*this);
    }

    const_tree_iterator& operator=(const_node_ptr &value) {
        _ptr = value;
        return (*this);
    }

    const_tree_iterator& operator++() {
        _ptr = _tree_next_iter(_ptr);
        return (*this);
    }

    const_tree_iterator operator++(int) {
        const_tree_iterator tmp(*this);
        ++(*this);
        return (tmp);
    }

    const_tree_iterator& operator--() {
        _ptr = _tree_prev_iter(_ptr);
        return (*this);
    }

    const_tree_iterator operator--(int) {
        const_tree_iterator tmp(*this);
        --(*this);
        return (tmp);
    }

    pointer operator->() const { return (_ptr->key); }

    reference operator*() const { return (*_ptr->key); }

   private:
    const_node_ptr _ptr;

    bool _tree_is_left_child(const_node_ptr node) { return (node == node->parent->left); }

    const_node_ptr _tree_next_iter(const_node_ptr node) {
        if (!node->right->is_leaf)
            return (tree_min(node->right));
        while (!_tree_is_left_child(node))
            node = node->parent;

        return (node->parent);
    }

    const_node_ptr _tree_prev_iter(const_node_ptr node) {
        if (!node->left->is_leaf)
            return (tree_max(node->left));
        const_node_ptr new_node = static_cast<const_node_ptr>(node);
        while (_tree_is_left_child(new_node))
            new_node = new_node->parent;

        return (new_node->parent);
    }
};

template <class T, class Val>
bool operator==(const const_tree_iterator<T, Val>& x, const const_tree_iterator<T, Val>& y) {
    return (x.base() == y.base());
}

template <class T, class Val>
bool operator!=(const const_tree_iterator<T, Val>& x, const const_tree_iterator<T, Val>& y) {
    return !(x.base() == y.base());
}

template <class node_ptr, class const_node_ptr, class Val>
bool operator==(const tree_iterator<node_ptr, Val>& x, const const_tree_iterator<const_node_ptr, Val>& y) {
    return (x.base() == y.base());
}

template <class node_ptr, class const_node_ptr, class Val>
bool operator!=(const tree_iterator<node_ptr, Val>& x, const const_tree_iterator<const_node_ptr, Val>& y) {
    return (x.base() != y.base());
}

template <class node_ptr, class const_node_ptr, class Val>
bool operator==(const const_tree_iterator<const_node_ptr, Val>& x, const tree_iterator<node_ptr, Val>& y) {
    return (x.base() == y.base());
}

template <class node_ptr, class const_node_ptr, class Val>
bool operator!=(const const_tree_iterator<const_node_ptr, Val>& x, const tree_iterator<node_ptr, Val>& y) {
    return (x.base() != y.base());
}

}  // namespace ft

#endif
