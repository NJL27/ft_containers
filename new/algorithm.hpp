#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

namespace ft {

template <class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
    while (first1 != last1) {
        if (!(*first1 == *first2)) return (false);

        ++first1, ++first2;
    }
    return (true);
}

template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
                             InputIterator2 last2) {
    for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2) {
        if (*first1 < *first2)
            return true;
        if (*first2 < *first1)
            return false;
    }
    return (first1 == last1) && (first2 != last2);
}

}  // namespace ft

#endif