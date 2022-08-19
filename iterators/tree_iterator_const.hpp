/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const_tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:24:57 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/16 12:51:18 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_CONST_TREE_ITERATOR_HPP_
#define RED_BLACK_CONST_TREE_ITERATOR_HPP_

#include "type_traits.hpp"

namespace ft {

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

    const_tree_iterator(const const_tree_iterator& other) : _ptr(other._ptr) {}

    const_tree_iterator(const normal_tree_iterator& other) : _ptr(other.base()) {}

    ~const_tree_iterator() {}

    const_node_ptr base() const { return (_ptr); }

    const_tree_iterator& operator=(const const_tree_iterator& other) {
        if (*this != other) {
            _ptr = other._ptr;
        }
        return (*this);
    }

    const_tree_iterator& operator=(normal_tree_iterator& other) {
        if (*this != other) {
            _ptr = other._ptr;
        }
        return (*this);
    }

    const_tree_iterator& operator=(const_node_ptr& val) {
        _ptr = val;
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

    bool _tree_is_left_child(const_node_ptr x) { return (x == x->parent->left); }

    const_node_ptr _tree_next_iter(const_node_ptr x) {
        if (!x->right->is_leaf)
            return (tree_min(x->right));
        if (x->right->is_end)
            return (x->right);
        while (!_tree_is_left_child(x))
            x = x->parent;

        return (x->parent);
    }

    const_node_ptr _tree_prev_iter(const_node_ptr x) {
        if (!x->left->is_leaf)
            return (tree_max(x->left));
        // if (x->left->is_end)
        //     return (x->left);
        const_node_ptr xx = static_cast<const_node_ptr>(x);
        while (_tree_is_left_child(xx))
            xx = xx->parent;

        return (xx->parent);
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
bool operator==(const tree_iterator<node_ptr, Val>&             x,
                const const_tree_iterator<const_node_ptr, Val>& y) {
    return (x.base() == y.base());
}

template <class node_ptr, class const_node_ptr, class Val>
bool operator!=(const tree_iterator<node_ptr, Val>&             x,
                const const_tree_iterator<const_node_ptr, Val>& y) {
    return (x.base() != y.base());
}

template <class node_ptr, class const_node_ptr, class Val>
bool operator==(const const_tree_iterator<const_node_ptr, Val>& x,
                const tree_iterator<node_ptr, Val>&             y) {
    return (x.base() == y.base());
}

template <class node_ptr, class const_node_ptr, class Val>
bool operator!=(const const_tree_iterator<const_node_ptr, Val>& x,
                const tree_iterator<node_ptr, Val>&             y) {
    return (x.base() != y.base());
}
}  // namespace ft

#endif
