/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:24:57 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/18 13:13:45 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_ITERATOR_HPP_
#define RED_BLACK_TREE_ITERATOR_HPP_

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

    bool _tree_is_left_child(node_ptr x) { return (x == x->parent->left); }

    node_ptr _tree_next_iter(node_ptr x) {
        if (!x->right->is_leaf)
            return (tree_min(x->right));
        if (x->right->is_end)
            return (x->right);
        while (!_tree_is_left_child(x))
            x = x->parent;

        return (x->parent);
    }

    node_ptr _tree_prev_iter(node_ptr x) {
        if (!x->left->is_leaf)
            return (tree_max(x->left));
        node_ptr xx = static_cast<node_ptr>(x);
        while (_tree_is_left_child(xx))
            xx = xx->parent;

        return (xx->parent);
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
}  // namespace ft

#endif
