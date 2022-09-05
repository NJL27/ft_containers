/*=====================================
=========== ft:: FUNCTIONAL ===========
=======================================
*/

#ifndef FUNCTIONAL_HPP
#define FUNCTIONAL_HPP

namespace ft {

template <class T>
struct less : binary_function<T, T, bool> {
    bool operator()(const T &x, const T &y) const { return (x < y); }
};

}  // namespace ft

#endif