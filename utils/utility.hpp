/*====================================
============ ft:: UTILITY ============
======================================

=> STD::PAIR
	template <class T1, class T2> struct pair;

This class couples together a pair of values, which may be of different types (T1 and T2).
The individual values can be accessed through its public members first and second.
Pairs are a particular case of tuple.

=> STD::MAKE_PAIR
	template <class T1, class T2> pair <T1,T2> make_pair (T1 x, T2 y);

Constructs a pair object with its first element set to x and its second element set to y.
The template types can be implicitly deduced from the arguments passed to make_pair.
pair objects can be constructed from other pair objects containing different types, if the respective types are implicitly convertible.
*/

#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace ft {
template <class T1, class T2>
struct pair {
    typedef T1 first_type;
    typedef T2 second_type;

    pair() : first(), second() {}

    template <class U, class V>
    pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) {}

    pair(const first_type &t1, const second_type &t2) : first(t1), second(t2) {}

    pair &operator=(const pair &pr) {
        if (this != &pr) {
            first = pr.first;
            second = pr.second;
        }
        return (*this);
    }

    first_type  first;
    second_type second;
};

template <class T1, class T2>
pair<T1, T2> make_pair(T1 x, T2 y) {
    return (pair<T1, T2>(x, y));
}

template <class T1, class T2>
inline bool operator==(const ft::pair<T1, T2>& x, const pair<T1, T2>& y) {
    return x.first == y.first && x.second == y.second;
}

template <class T1, class T2>
inline bool operator!=(const ft::pair<T1, T2>& x, const pair<T1, T2>& y) {
    return !(x == y);
}

template <class T1, class T2>
inline bool operator<(const ft::pair<T1, T2>& x, const pair<T1, T2>& y) {
    return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
}

template <class T1, class T2>
inline bool operator>(const ft::pair<T1, T2>& x, const pair<T1, T2>& y) {
    return y < x;
}

template <class T1, class T2>
inline bool operator<=(const ft::pair<T1, T2>& x, const pair<T1, T2>& y) {
    return !(y < x);
}

template <class T1, class T2>
inline bool operator>=(const ft::pair<T1, T2>& x, const pair<T1, T2>& y) {
    return !(x < y);
}
}  // namespace ft



#endif