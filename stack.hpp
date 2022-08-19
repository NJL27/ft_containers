/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 08:43:51 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/18 12:37:20 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    friend bool operator==(const stack<U, Cntr> &lhs, const stack<U, Cntr> &rhs);
    template <class U, class Cntr>
    friend bool operator<(const stack<U, Cntr> &lhs, const stack<U, Cntr> &rhs);

   private:
    container_type _c;
};

template <class U, class Cntr>
bool operator==(const ft::stack<U, Cntr> &lhs, const ft::stack<U, Cntr> &rhs) {
    return lhs._c == rhs._c;
}

template <class U, class Cntr>
bool operator!=(const ft::stack<U, Cntr> &lhs, const ft::stack<U, Cntr> &rhs) {
    return !(lhs == rhs);
}

template <class U, class Cntr>
bool operator<(const ft::stack<U, Cntr> &lhs, const ft::stack<U, Cntr> &rhs) {
    return lhs._c < rhs._c;
}
template <class U, class Cntr>
bool operator<=(const ft::stack<U, Cntr> &lhs, const ft::stack<U, Cntr> &rhs) {
    return !(lhs > rhs);
}
template <class U, class Cntr>
bool operator>(const ft::stack<U, Cntr> &lhs, const ft::stack<U, Cntr> &rhs) {
    return rhs < lhs;
}
template <class U, class Cntr>
bool operator>=(const ft::stack<U, Cntr> &lhs, const ft::stack<U, Cntr> &rhs) {
    return !(lhs < rhs);
}
}  // namespace ft

#endif