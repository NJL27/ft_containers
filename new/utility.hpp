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

    pair &operator=(const pair &p) {
        if (this != &p) {
            first = p.first;
            second = p.second;
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
inline bool operator==(const ft::pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <class T1, class T2>
inline bool operator!=(const ft::pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
    return !(lhs == rhs);
}

template <class T1, class T2>
inline bool operator<(const ft::pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
    return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template <class T1, class T2>
inline bool operator>(const ft::pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
    return rhs < lhs;
}

template <class T1, class T2>
inline bool operator<=(const ft::pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
    return !(rhs < lhs);
}

template <class T1, class T2>
inline bool operator>=(const ft::pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
    return !(lhs < rhs);
}
}  // namespace ft



#endif