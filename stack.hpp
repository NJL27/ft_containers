/*==================================
============ ft:: STACK ============
====================================

=> MEMBER TYPES
	container_type
	value_type
	size_type
	reference
	const_reference
=> MEMBER FUNCTIONS
	(constructor)
	(deconstructor)
	operator=
	-> ELEMENT ACCESS
		top
	-> CAPACITY
		empty
		size
	-> MODIFIERS
		push
		pop
=> NON MEMBER FUNCTIONS
	operator==
	operator!=
	operator<
	operator<=
	operator>
	operator>=
*/

#ifndef STACK_HPP_
#define STACK_HPP_

#include "vector.hpp"

namespace ft {
template <class T, class Container = ft::vector<T> >
class stack {
   public:
    typedef Container                           container_type;
    typedef typename Container::value_type      value_type;
    typedef typename Container::size_type       size_type;
    typedef typename Container::reference       reference;
    typedef typename Container::const_reference const_reference;

    explicit stack(const container_type &ctnr = container_type()) { _c = ctnr; }

    bool empty() const { return (_c.empty()); }

    size_type size() const { return (_c.size()); }

    value_type &top() { return (_c.back()); }

    const value_type &top() const { return (_c.back()); }

    void push(const value_type &val) { _c.push_back(val); }

    void pop() { _c.pop_back(); }

    template <class U, class Cntr>
    friend bool operator==(const stack<U, Cntr>& x, const stack<U, Cntr>& y);
    template <class U, class Cntr>
    friend bool operator<(const stack<U, Cntr>& x, const stack<U, Cntr>& y);

   protected:
    container_type _c;
};

template <class U, class Cntr>
bool operator==(const ft::stack<U, Cntr>& x, const ft::stack<U, Cntr>& y) {
    return x._c == y._c;
}

template <class U, class Cntr>
bool operator!=(const ft::stack<U, Cntr>& x, const ft::stack<U, Cntr>& y) {
    return !(x == y);
}

template <class U, class Cntr>
bool operator<(const ft::stack<U, Cntr>& x, const ft::stack<U, Cntr>& y) {
    return x._c < y._c;
}
template <class U, class Cntr>
bool operator<=(const ft::stack<U, Cntr>& x, const ft::stack<U, Cntr>& y) {
    return !(x > y);
}
template <class U, class Cntr>
bool operator>(const ft::stack<U, Cntr>& x, const ft::stack<U, Cntr>& y) {
    return y < x;
}
template <class U, class Cntr>
bool operator>=(const ft::stack<U, Cntr>& x, const ft::stack<U, Cntr>& y) {
    return !(x < y);
}
}  // namespace ft

#endif