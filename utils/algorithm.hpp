/*========================================
============= ft:: ALGORITHM =============
==========================================

=> EQUAL:
Compares the elements in the range [first1,last1). 
With those in the range beginning at first2, and returns true if all of the elements in both ranges match.
The elements are compared using operator== (or pred, in version (2)).

equality (1)	
template <class InputIt1, class InputIt2>
bool equal (InputIt1 first1, InputIt1 last1, InputIt2 first2);

predicate (2)
template <class InputIt1, class InputIt2, class BinaryPredicate>
bool equal (InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate pred);

=> LEXICOGRAPHICAL COMPARE:
Returns true if the range [first1,last1) compares lexicographically less than the range [first2,last2).
If both sequences compare equal until one of them ends, the shorter sequence is lexicographically less than the longer one.
The elements are compared using operator< for the first version, and comp for the second.
Two elements, a and b are considered equivalent if (!(a<b) && !(b<a)) or if (!comp(a,b) && !comp(b,a)).

default (1)	
template <class InputIt1, class InputIt2>
bool lexicographical_compare (InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2);

custom (2)	
template <class InputIt1, class InputIt2, class Compare>
bool lexicographical_compare (InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp);
*/

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
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                             InputIterator2 first2, InputIterator2 last2) {
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