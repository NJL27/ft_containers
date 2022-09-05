/*=================================
=========== ft:: VECTOR ===========
===================================

=> MEMBER TYPES
	value_type
	allocator_type
	size_type
	difference_type
	reference
	const_reference
	pointer
	const_pointer
	iterator
	const_iterator
	reverse_iterator
	const_reverse_iterator
=> MEMBER FUNCTIONS
	(constructor)
	(deconstructor)
	operator=
	assign
	get_allocator
	-> ELEMENT ACCESS
		at
		operator[]
		front
		back
		data
	-> ITERATORS
		begin
		end
		rbegin
		rend
	-> CAPACITY
		empty
		size
		max_size
		reverse
		capacity
	-> MODIFIERS
		clear
		insert
		erase
		push_back
		pop_back
		resize
		swap
=> NON MEMBER FUNCTIONS
	operator==
	operator!=
	operator<
	operator<=
	operator>
	operator>=

*/

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "utils/iterator.hpp"
#include "utils/utility.hpp"
#include "utils/type_traits.hpp"
#include "utils/algorithm.hpp"


namespace ft {
template <typename T, typename Allocator = std::allocator<T> >
class vector {
   public:
// Types
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

// Constructor
     explicit vector(const allocator_type &alloc = allocator_type()) : _vector_array(NULL), _size(0), _capacity(0) {
         _allocator = alloc;
     }

     explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) {
         _allocator = alloc;
         _vector_array = NULL;
         if (n > 0) {
             _vector_array = _allocator.allocate(n);
             for (size_t i = 0; i < n; i++)
                 _allocator.construct(_vector_array + i, val);
         }
         _size = n;
         _capacity = n;
     }

     template <class InputIterator>
     vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
            typename enable_if<!ft::is_integral<InputIterator>::value, bool>::type = 0) {
         _vector_array = NULL;
         _allocator = alloc;
         _capacity = 0;
         _size = 0;
         assign(first, last);
     }

     vector(const vector &other) : _vector_array(NULL), _size(0), _capacity(0), _allocator() {
         size_type n = other.size();
         if (n > 0) {
             _vallocate(n);
             for (size_type i = 0; i < n; ++i)
                 push_back(other[i]);
             _size = n;
         }
     }

// Deconstuctor
     ~vector() {
         if (_vector_array != NULL) {
             clear();
             _allocator.deallocate(_vector_array, _capacity);
             _vector_array = NULL;
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

     reference operator[](size_type i) { return (_vector_array[i]); }

     const_reference operator[](size_type i) const { return (_vector_array[i]); }

// Iterators
     iterator begin() { return (_vector_array); }

     const_iterator begin() const { return (_vector_array); }

     iterator end() { return (_vector_array + _size); }

     const_iterator end() const { return (_vector_array + _size); }

     reverse_iterator rbegin() { return (reverse_iterator)(_vector_array + _size); }

     const_reverse_iterator rbegin() const { return (const_reverse_iterator)(_vector_array + _size); }

     reverse_iterator rend() { return (reverse_iterator)(_vector_array); }

     const_reverse_iterator rend() const { return (const_reverse_iterator)(_vector_array); }

// Capacity
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
                 _allocator.construct(_vector_array + _size, val);
         } else if (_size > n) {
             for (; _size > n; --_size)
                 _allocator.destroy(_vector_array + (_size - 1));
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

// Element Access
     reference at(size_type n) {
         if (n >= _size)
             throw std::out_of_range("vector");
         return (*(_vector_array + n));
     }

     const_reference at(size_type n) const {
         if (n >= _size)
             throw std::out_of_range("vector");
         return (*(_vector_array + n));
     }

     reference front() { return (*(_vector_array)); }

     const_reference front() const { return (*(_vector_array)); }

     reference back() { return (*(_vector_array + _size - 1)); }

     const_reference back() const { return (*(_vector_array + _size - 1)); }

// Modifiers
     template <class InputIterator>
     void assign(InputIterator first, InputIterator last,
                 typename enable_if<!ft::is_integral<InputIterator>::value, bool>::type = 0) {
         _assign_range(first, last, ft::iterator_category(first));
     }

     void assign(size_type n, const value_type &value) {
         for (size_type i = 0; i < _size; ++i)
             _allocator.destroy(_vector_array + i);
         if (n > _capacity) {
             if (_capacity > 0)
                 _allocator.deallocate(_vector_array, _capacity);
             _vector_array = _allocator.allocate(n);
             _capacity = n;
         }
         for (size_type i = 0; i < n; ++i)
             _allocator.construct(_vector_array + i, value);
         _size = n;
     }

     void push_back(const T &value) {
         if (_size + 1 > _capacity)
             reserve(_recommend_size(_size + 1));
         _construct_from_end(1, value);
     }

     void pop_back() {
         _allocator.destroy(_vector_array + _size - 1);
         --_size;
     }

     iterator insert(iterator position, const value_type &value) {
         difference_type offset = position - begin();
         insert(position, 1, value);
         return (_vector_array + offset);
     }

     void insert(iterator position, size_type n, const value_type &value) {
         if (n > 0) {
             const difference_type offset = position - begin();
             const size_type       old_size = _size;
             if (old_size + n > _capacity)
                 reserve(_recommend_size(old_size + n));
             resize(old_size + n);
             std::copy_backward(begin() + offset, begin() + old_size, begin() + old_size + n);
             std::fill_n(_vector_array + offset, n, value);
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
             _allocator.destroy(_vector_array + i);
             if (i != _size - 1)
                 _allocator.construct(_vector_array + i, *(_vector_array + i + 1));
         }
         --_size;
         return (_vector_array + savedPos);
     }

     iterator erase(iterator first, iterator last) {
         if (first != last) {
             iterator ptr = std::copy(last, end(), first);
             while (end() != ptr)
                 pop_back();
         }
         return (first);
     }

     void swap(vector &other) {
         allocator_type tmp_al = _allocator;
         pointer        tmp_cnt = _vector_array;
         size_type      tmp_size = _size;
         size_type      tmp_cap = _capacity;

         _allocator = other._allocator;
         _vector_array = other._vector_array;
         _size = other._size;
         _capacity = other._capacity;
         other._allocator = tmp_al;
         other._vector_array = tmp_cnt;
         other._size = tmp_size;
         other._capacity = tmp_cap;
     }

     void clear() {
         for (size_type i = 0; i < size(); ++i)
             _allocator.destroy(_vector_array + i);
         _size = 0;
     }

     allocator_type get_allocator() const { return (_allocator); }

   private:
     pointer        _vector_array;
     size_type      _size;
     size_type      _capacity;
     allocator_type _allocator;

     inline void _construct(pointer ptr, const_reference value) { _allocator.construct(ptr, value); }

     inline void _construct_from_end(size_type n, const_reference value = value_type()) {
         for (size_type i = 0; i < n; ++i, ++_size)
             _construct(_vector_array + _size, value);
     }

     template <typename ForwardIterator>
     inline void _construct_from_end(ForwardIterator first, ForwardIterator last, ft::forward_iterator_tag) {
         for (; first != last; ++first, ++_size)
             _construct(_vector_array + _size, *first);
     }

     inline void _vallocate(size_type n) {
         if (n > max_size())
             throw std::length_error("vector");

         _vector_array = _allocator.allocate(n);
         _capacity = n;
     }

     inline void _vdeallocate() {
         if (_vector_array != NULL) {
             clear();
             _allocator.deallocate(_vector_array, _capacity);
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
     inline void _assign_range(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag) {
         clear();
         const size_type n = static_cast<size_type>(ft::distance(first, last));
         if (n > 0) {
             if (n > _capacity) {
                 _vdeallocate();
                 _vallocate(n);
             }
             for (size_type i = 0; first != last; ++first, ++i)
                 _allocator.construct(_vector_array + i, *first);
             _size = n;
         }
     }

     template <typename InputIterator>
     void _insert_range(iterator position, InputIterator first, InputIterator last, std::input_iterator_tag) {
         if (position == end()) {
             for (; first != last; ++first)
                 push_back(*first);
         } else if (first != last) {
             vector tmp(first, last);
             insert(position, tmp.begin(), tmp.end());
         }
     }

     template <typename ForwardIterator>
     void _insert_range(iterator position, ForwardIterator first, ForwardIterator last, std::forward_iterator_tag) {
         size_type n = static_cast<size_type>(ft::distance(first, last));
         if (n > 0) {
             const difference_type offset = position - begin();
             const size_type       old_size = size();
             if (old_size + n > _capacity)
                 reserve(_recommend_size(old_size + n));
             resize(old_size + n);
             std::copy_backward(_vector_array + offset, _vector_array + old_size, _vector_array + old_size + n);
             std::copy(first, last, _vector_array + offset);
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
bool operator==(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
    return (x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin()));
}

template <typename T, typename Allocator>
bool operator!=(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
    return !(x == y);
}

template <typename T, typename Allocator>
bool operator<=(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
    return !(x > y);
}

template <typename T, typename Allocator>
bool operator>=(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
    return !(x < y);
}

template <typename T, typename Allocator>
bool operator<(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
    return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
}

template <typename T, typename Allocator>
bool operator>(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
    return (y < x);
}

template <typename T, typename Alloc>
void swap(ft::vector<T, Alloc>& x, ft::vector<T, Alloc>& y) {
    x.swap(y);
}
}  // namespace ft

#endif
