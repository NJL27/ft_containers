#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "../iterator.hpp"

namespace ft {
template <typename T>
class random_access_iterator {
   public:
    typedef typename iterator<random_access_iterator_tag, T>::value_type        value_type;
    typedef typename iterator<random_access_iterator_tag, T>::pointer           pointer;
    typedef typename iterator<random_access_iterator_tag, T>::reference         reference;
    typedef typename iterator<random_access_iterator_tag, T>::difference_type   difference_type;
    typedef typename iterator<random_access_iterator_tag, T>::iterator_category iterator_category;

    random_access_iterator(T *ptr = NULL) : _ptr(ptr) {}

    ~random_access_iterator() {}

    pointer base() const { return (_ptr); }

    random_access_iterator &operator++() {
        ++_ptr;
        return (*this);
    }

    random_access_iterator operator++(int) {
        pointer tmp = _ptr;
        ++_ptr;
        return random_access_iterator(tmp);
    }

    random_access_iterator &operator--() {
        --_ptr;
        return (*this);
    }

    random_access_iterator operator--(int) {
        pointer tmp = _ptr;
        --_ptr;
        return random_access_iterator(tmp);
    }

    operator random_access_iterator<const T>() const {
        return (random_access_iterator<const T>(this->_ptr));
    }

    reference operator[](difference_type n) const { return *(operator+(n)); }

    pointer operator->() { return (_ptr); }

    reference operator*() { return (*_ptr); }

    random_access_iterator &operator+=(difference_type offset) {
        _ptr += offset;
        return (*this);
    }

    random_access_iterator &operator-=(difference_type offset) {
        _ptr -= offset;
        return (*this);
    }

    random_access_iterator operator+(difference_type offset) const { return (_ptr + offset); }

    random_access_iterator operator-(difference_type offset) const { return (_ptr - offset); }

    template <class U, class V>
    friend random_access_iterator operator-(const random_access_iterator<V> &pre,
                                            const random_access_iterator<V> &post);

   protected:
    pointer _ptr;
};

template <class U, class V>
bool operator==(const random_access_iterator<U> &pre, const random_access_iterator<V> &post) {
    return pre.base() == post.base();
}

template <class U, class V>
bool operator!=(const random_access_iterator<U> &pre, const random_access_iterator<V> &post) {
    return !(pre == post);
}

template <class U, class V>
bool operator<(const random_access_iterator<U> &pre, const random_access_iterator<V> &post) {
    return (pre.base() < post.base());
}

template <class U, class V>
bool operator<=(const random_access_iterator<U> &pre, const random_access_iterator<V> &post) {
    return !(pre > post);
}

template <class U, class V>
bool operator>(const random_access_iterator<U> &pre, const random_access_iterator<V> &post) {
    return post < pre;
}

template <class U, class V>
bool operator>=(const random_access_iterator<U> &pre, const random_access_iterator<V> &post) {
    return !(pre < post);
}

template <class U>
random_access_iterator<U> operator+(const typename random_access_iterator<U>::difference_type &pre,
                                    const random_access_iterator<U> &post) {
    return random_access_iterator<U>(post.base() + pre);
}

template <class U>
typename random_access_iterator<U>::difference_type operator-(
    const random_access_iterator<U> &pre, const random_access_iterator<U> &post) {
    return typename random_access_iterator<U>::difference_type(pre.base() - post.base());
}

template <class U, class V>
typename random_access_iterator<U>::difference_type operator-(
    const random_access_iterator<U> &pre, const random_access_iterator<V> &post) {
    return typename random_access_iterator<U>::difference_type(pre.base() - post.base());
}

template <class InputIt>
typename random_access_iterator<InputIt>::difference_type distance(InputIt first, InputIt last) {
    typename random_access_iterator<InputIt>::difference_type dist = 0;
    while (first != last)
        ++first, ++dist;
    return dist;
}
}  // namespace ft

#endif
