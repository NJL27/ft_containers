/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 08:22:39 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/19 22:18:43 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>
// #include <utility>

#include "iterators/random_access_iterator.hpp"
#include "new/iterator.hpp"
#include "new/utility.hpp"
#include "new/type_traits.hpp"
#include "new/algorithm.hpp"


namespace ft {
template <typename T, typename Allocator = std::allocator<T> >
class vector {
   public:
    //  Typedefs
     typedef T                                                                value_type;
     typedef Allocator                                                        allocator_type;
     typedef typename allocator_type::size_type                               size_type;
     typedef value_type                                                      &reference;
     typedef const value_type                                                &const_reference;
     typedef value_type                                                      *pointer;
     typedef const value_type                                                *const_pointer;
     typedef typename ft::random_access_iterator<value_type>::difference_type difference_type;
     typedef ft::random_access_iterator<value_type>                           iterator;
     typedef ft::random_access_iterator<const value_type>                     const_iterator;
     typedef ft::reverse_iterator<const_iterator>                             const_reverse_iterator;
     typedef ft::reverse_iterator<iterator>                                   reverse_iterator;

    //   Construct/Copy/Destroy
     explicit vector(const allocator_type &alloc = allocator_type())
         : _vector(NULL), _size(0), _capacity(0) {
         _allocator = alloc;
     }

     explicit vector(size_type n, const value_type &val = value_type(),
                     const allocator_type &alloc = allocator_type()) {
         _allocator = alloc;
         _vector = NULL;
         if (n > 0) {
             _vector = _allocator.allocate(n);
             for (size_t i = 0; i < n; i++)
                 _allocator.construct(_vector + i, val);
         }
         _size = n;
         _capacity = n;
     }

     template <class InputIterator>
     vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
            typename enable_if<!ft::is_integral<InputIterator>::value, bool>::type = 0) {
         _vector = NULL;
         _allocator = alloc;
         _capacity = 0;
         _size = 0;
         assign(first, last);
     }

     vector(const vector &other) : _vector(NULL), _size(0), _capacity(0), _allocator() {
         size_type n = other.size();
         if (n > 0) {
             _vallocate(n);
             for (size_type i = 0; i < n; ++i)
                 push_back(other[i]);
             _size = n;
         }
     }

     ~vector() {
         if (_vector != NULL) {
             clear();
             _allocator.deallocate(_vector, _capacity);
             _vector = NULL;
         }
     }

    //   Operators
     vector &operator=(const vector &other) {
         if (this != &other) {
             _allocator = other.get_allocator();
             assign(other.begin(), other.end());
         }
         return (*this);
     }

     reference operator[](size_type i) { return (_vector[i]); }

     const_reference operator[](size_type i) const { return (_vector[i]); }

    //  Iterators
     iterator begin() { return (_vector); }

     const_iterator begin() const { return (_vector); }

     iterator end() { return (_vector + _size); }

     const_iterator end() const { return (_vector + _size); }

     reverse_iterator rbegin() { return (reverse_iterator)(_vector + _size); }

     const_reverse_iterator rbegin() const { return (const_reverse_iterator)(_vector + _size); }

     reverse_iterator rend() { return (reverse_iterator)(_vector); }

     const_reverse_iterator rend() const { return (const_reverse_iterator)(_vector); }

    //  Capacity
     size_type size() const { return (_size); }

     size_type max_size() const {
         return (std::min<size_type>(_allocator.max_size(),
                                     std::numeric_limits<difference_type>::max()));
     }

     void resize(size_type n, value_type val = value_type()) {
         if (_size < n) {
             if (n > _capacity)
                 reserve(_recommend_size(n));
             for (; _size < n; ++_size)
                 _allocator.construct(_vector + _size, val);
         } else if (_size > n) {
             for (; _size > n; --_size)
                 _allocator.destroy(_vector + (_size - 1));
         }
     }

     size_type capacity() const { return (_capacity); }

     bool empty() const { return (_size == 0 ? true : false); }

     void reserve(size_type n) {
         if (n > _capacity) {
             vector tmp;
             tmp._vallocate(n);
             tmp._construct_from_end(begin(), end(), ft::iterator_category(begin()));
             swap(tmp);
         }
     }

    //  Element Access
     reference at(size_type n) {
         if (n >= _size)
             throw std::out_of_range("vector");
         return (*(_vector + n));
     }

     const_reference at(size_type n) const {
         if (n >= _size)
             throw std::out_of_range("vector");
         return (*(_vector + n));
     }

     reference front() { return (*(_vector)); }

     const_reference front() const { return (*(_vector)); }

     reference back() { return (*(_vector + _size - 1)); }

     const_reference back() const { return (*(_vector + _size - 1)); }

    //  Modifiers
     template <class InputIterator>
     void assign(InputIterator first, InputIterator last,
                 typename enable_if<!ft::is_integral<InputIterator>::value, bool>::type = 0) {
         _assign_range(first, last, ft::iterator_category(first));
     }

     void assign(size_type n, const value_type &val) {
         for (size_type i = 0; i < _size; ++i)
             _allocator.destroy(_vector + i);
         if (n > _capacity) {
             if (_capacity > 0)
                 _allocator.deallocate(_vector, _capacity);
             _vector = _allocator.allocate(n);
             _capacity = n;
         }
         for (size_type i = 0; i < n; ++i)
             _allocator.construct(_vector + i, val);
         _size = n;
     }

     void push_back(const T &value) {
         if (_size + 1 > _capacity)
             reserve(_recommend_size(_size + 1));
         _construct_from_end(1, value);
     }

     void pop_back() {
         _allocator.destroy(_vector + _size - 1);
         --_size;
     }

     iterator insert(iterator position, const value_type &val) {
         difference_type offset = position - begin();
         insert(position, 1, val);
         return (_vector + offset);
     }

     void insert(iterator position, size_type n, const value_type &val) {
         if (n > 0) {
             const difference_type offset = position - begin();
             const size_type       old_size = _size;
             if (old_size + n > _capacity)
                 reserve(_recommend_size(old_size + n));
             resize(old_size + n);
             std::copy_backward(begin() + offset, begin() + old_size, begin() + old_size + n);
             std::fill_n(_vector + offset, n, val);
         }
     }

     template <class InputIterator>
     void insert(iterator position, InputIterator first, InputIterator last,
                 typename enable_if<!ft::is_integral<InputIterator>::value, bool>::type = 0) {
         _insert_range(position, first, last, ft::iterator_category(first));
     }

     iterator erase(iterator position) {
         size_type savedPos = position - begin();
         for (size_type i = savedPos; i < _size; ++i) {
             _allocator.destroy(_vector + i);
             if (i != _size - 1)
                 _allocator.construct(_vector + i, *(_vector + i + 1));
         }
         --_size;
         return (_vector + savedPos);
     }

     iterator erase(iterator first, iterator last) {
         if (first != last) {
             iterator ptr = std::copy(last, end(), first);
             while (end() != ptr)
                 pop_back();
         }
         return (first);
     }

     void swap(vector &x) {
         allocator_type tmp_al = _allocator;
         pointer        tmp_cnt = _vector;
         size_type      tmp_size = _size;
         size_type      tmp_cap = _capacity;

         _allocator = x._allocator;
         _vector = x._vector;
         _size = x._size;
         _capacity = x._capacity;
         x._allocator = tmp_al;
         x._vector = tmp_cnt;
         x._size = tmp_size;
         x._capacity = tmp_cap;
     }

     void clear() {
         for (size_type i = 0; i < size(); ++i)
             _allocator.destroy(_vector + i);
         _size = 0;
     }

     allocator_type get_allocator() const { return (_allocator); }

   private:
     pointer        _vector;
     size_type      _size;
     size_type      _capacity;
     allocator_type _allocator;

     inline void _construct(pointer ptr, const_reference val) { _allocator.construct(ptr, val); }

     inline void _construct_from_end(size_type n, const_reference val = value_type()) {
         for (size_type i = 0; i < n; ++i, ++_size)
             _construct(_vector + _size, val);
     }

     template <typename ForwardIterator>
     inline void _construct_from_end(ForwardIterator first, ForwardIterator last,
                                     ft::forward_iterator_tag) {
         for (; first != last; ++first, ++_size)
             _construct(_vector + _size, *first);
     }

     inline void _vallocate(size_type n) {
         if (n > max_size())
             throw std::length_error("vector");

         _vector = _allocator.allocate(n);
         _capacity = n;
     }

     inline void _vdeallocate() {
         if (_vector != NULL) {
             clear();
             _allocator.deallocate(_vector, _capacity);
             _capacity = 0;
         }
     }

     template <typename InputIterator>
     inline void _assign_range(InputIterator first, InputIterator last, std::input_iterator_tag) {
         clear();
         for (; first != last; ++first)
             push_back(*first);
     }

     template <typename ForwardIterator>
     inline void _assign_range(ForwardIterator first, ForwardIterator last,
                               std::forward_iterator_tag) {
         clear();
         const size_type n = static_cast<size_type>(ft::distance(first, last));
         if (n > 0) {
             if (n > _capacity) {
                 _vdeallocate();
                 _vallocate(n);
             }
             for (size_type i = 0; first != last; ++first, ++i)
                 _allocator.construct(_vector + i, *first);
             _size = n;
         }
     }

     template <typename InputIterator>
     void _insert_range(iterator position, InputIterator first, InputIterator last,
                        std::input_iterator_tag) {
         if (position == end()) {
             for (; first != last; ++first)
                 push_back(*first);
         } else if (first != last) {
             vector tmp(first, last);
             insert(position, tmp.begin(), tmp.end());
         }
     }

     template <typename ForwardIterator>
     void _insert_range(iterator position, ForwardIterator first, ForwardIterator last,
                        std::forward_iterator_tag) {
         size_type n = static_cast<size_type>(ft::distance(first, last));
         if (n > 0) {
             const difference_type offset = position - begin();
             const size_type       old_size = size();
             if (old_size + n > _capacity)
                 reserve(_recommend_size(old_size + n));
             resize(old_size + n);
             std::copy_backward(_vector + offset, _vector + old_size, _vector + old_size + n);
             std::copy(first, last, _vector + offset);
         }
     }

     size_type _recommend_size(size_type new_size) const {
         const size_type ms = max_size();
         if (new_size > ms)
             throw std::length_error("vector");
         if (_capacity >= ms / 2)
             return (ms);
         return (std::max(_capacity * 2, new_size));
     }
};

template <typename T, typename Allocator>
bool operator==(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs) {
    return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <typename T, typename Allocator>
bool operator!=(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs) {
    return !(lhs == rhs);
}

template <typename T, typename Allocator>
bool operator<=(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs) {
    return !(lhs > rhs);
}

template <typename T, typename Allocator>
bool operator>=(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs) {
    return !(lhs < rhs);
}

template <typename T, typename Allocator>
bool operator<(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs) {
    return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <typename T, typename Allocator>
bool operator>(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs) {
    return (rhs < lhs);
}

template <typename T, typename Alloc>
void swap(ft::vector<T, Alloc> &x, ft::vector<T, Alloc> &y) {
    x.swap(y);
}
}  // namespace ft

#endif
