/*==============================
=========== ft:: SET ===========
================================

=> MEMBER TYPES
	key_type
	value_type
	size_type
	difference_type
	key_compare_type
	value_compare_type
	allocator_type
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
	get_allocator
	-> ITERATORS
		begin
		end
		rbegin
		rend
	-> CAPACITY
		empty
		size
		max_size
	-> MODIFIERS
		clear
		insert
		erase
		swap
	-> OPERATIONS
		count
		find
		equal_range
		lower_bond
		upper_bond
	-> OBSERVERS
		key_comp
		value_comp
=> NON MEMBER FUNCTIONS
	operator==
	operator!=
	operator<
	operator<=
	operator>
	operator>=

*/

#ifndef SET_HPP
#define SET_HPP

#include <algorithm>

#include "utils/iterator.hpp"
#include "utils/RB_tree.hpp"
#include "utils/algorithm.hpp"

namespace ft {
template <class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
class set {
   public:
    typedef Key                                                     key_type;
    typedef Key                                                     value_type;
    typedef Allocator                                               allocator_type;
    typedef typename allocator_type::size_type                      size_type;
    typedef typename allocator_type::difference_type                difference_type;
    typedef Compare                                                 key_compare;
    typedef Compare                                                 value_compare;
    typedef value_type&                                             reference;
    typedef const value_type&                                       const_reference;
    typedef typename allocator_type::pointer                        pointer;
    typedef typename allocator_type::const_pointer                  const_pointer;
    typedef node<value_type>                                        node_type;
    typedef typename ft::node<value_type>::node_pointer             node_pointer;
    typedef typename ft::node<value_type>::const_node_pointer       const_node_pointer;
    typedef ft::const_tree_iterator<const_node_pointer, value_type> iterator;
    typedef ft::const_tree_iterator<const_node_pointer, value_type> const_iterator;
    typedef ft::reverse_iterator<iterator>                          reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;

// MEMBER FUNCTIONS
// constructor
    explicit set(const key_compare&    comp = key_compare(), 
        const allocator_type& alloc = allocator_type()) : _tree(comp, alloc) {}

    template <class InputIterator>
    set(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
        const allocator_type& alloc = allocator_type()) : _tree(comp, alloc) {
        _tree.insert(first, last);
    }

    set(const set &other) : _tree(other._tree) {}

// deconstructor
    ~set() {}

// operator=
    set& operator=(const set &other) {
        _tree = other._tree;
        return *this;
    }

// get_allocator
    allocator_type get_allocator() const { return _tree.get_allocator(); }

// ITERATORS
    iterator begin() { return _tree.begin(); }

    const_iterator begin() const { return _tree.begin(); }

    iterator end() { return _tree.end(); }

    const_iterator end() const { return _tree.end(); }

    reverse_iterator rbegin() { return _tree.rbegin(); }

    const_reverse_iterator rbegin() const { return _tree.rbegin(); }

    reverse_iterator rend() { return _tree.rend(); }

    const_reverse_iterator rend() const { return _tree.rend(); }

// CAPACITY
    bool empty() const { return _tree.empty(); }

    size_type size() const { return _tree.size(); }

    size_type max_size() const { return _tree.max_size(); }

// MODIFIERS
    ft::pair<iterator, bool> insert(const value_type& value) { return (_tree.insert(value)); }

    iterator insert(iterator position, const value_type& value) {
        return (_tree.insert(position, value));
    }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        _tree.insert(first, last);
    }

    void erase(iterator position) { _tree.erase(const_cast<node_pointer>(position.base())); }

    size_type erase(const value_type& value) {
        size_type cnt = 0;
        iterator  it;
        while ((it = find(value)) != end()) {
            erase(it);
            ++cnt;
        }
        return cnt;
    }

    void erase(iterator first, iterator last) {
        for (iterator tmp = first; tmp != last; tmp = first) {
            first++;
            erase(tmp);
        }
    }

    void swap(set &other) { _tree.swap(other._tree); }

    void clear() { _tree.clear(); }

// OBSERVERS
    key_compare key_comp() const { return key_compare(); }

    value_compare value_comp() const { return value_compare(); }

// OPERATIONS
    iterator find(const value_type& value) const { return _tree.find(value); }

    size_type count(const value_type& key) const { return find(key) != end() ? 1 : 0; }

    iterator lower_bound(const value_type& key) const { return _tree.lower_bound(key); }

    iterator upper_bound(const value_type& key) const { return _tree.upper_bound(key); }

    ft::pair<iterator, iterator> equal_range(const value_type& value) const {
        return _tree.equal_range(value);
    }

   private:
    ft::red_black_tree<value_type, key_type, value_type, key_compare, allocator_type> _tree;
};

template <class Key, class Compare, class Alloc>
void swap(ft::set<Key, Compare, Alloc>& x, ft::set<Key, Compare, Alloc>& y) {
    x.swap(y);
}

template <class Key, class Compare, class Alloc>
inline bool operator==(const ft::set<Key, Compare, Alloc>& x, const ft::set<Key, Compare, Alloc>& y) {
    return x.size() == y.size() && std::equal(x.begin(), x.end(), y.begin());
}

template <class Key, class Compare, class Alloc>
inline bool operator!=(const ft::set<Key, Compare, Alloc>& x, const ft::set<Key, Compare, Alloc>& y) {
    return !(x == y);
}

template <class Key, class Compare, class Alloc>
inline bool operator<(const ft::set<Key, Compare, Alloc>& x, const ft::set<Key, Compare, Alloc>& y) {
    return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template <class Key, class Compare, class Alloc>
inline bool operator>(const ft::set<Key, Compare, Alloc>& x, const ft::set<Key, Compare, Alloc>& y) {
    return y < x;
}
template <class Key, class Compare, class Alloc>
inline bool operator<=(const ft::set<Key, Compare, Alloc>& x, const ft::set<Key, Compare, Alloc>& y) {
    return !(y < x);
}
template <class Key, class Compare, class Alloc>
inline bool operator>=(const ft::set<Key, Compare, Alloc>& x, const ft::set<Key, Compare, Alloc>& y) {
    return !(x < y);
}

}  // namespace ft

#endif