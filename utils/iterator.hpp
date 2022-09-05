/*=======================================
============= ft:: ITARATOR =============
=========================================

=> ITERATOR TRAITS:
	template<class Iter>
	struct iterator_traits;

=> SPECIALIZATIONS:
	template<class T>
	struct iterator_traits<T*>;
	template<class T>
	struct iterator_traits<const T*>;
	
=> ITERATOR MEMBER TYPES:
	template<class Iter>
	class reverse_iterator : public iterator
  < typename iterator_traits<Iter>::difference_type, 	-> Type to express the result of subtracting one iterator from another.
	typename iterator_traits<Iter>::value_type,			-> The type of the element the iterator can point to.
	typename iterator_traits<Iter>::pointer,			-> The type of a pointer to an element the iterator can point to.
	typename iterator_traits<Iter>::reference,			-> The type of a reference to an element the iterator can point to.
	typename iterator_traits<Iter>::iterator_category >	-> The iterator category. It can be one of these: input/output/forward/bidirectional/random_access _iterator_tag.

=> SPECIALIZATIONS MEMBER TYPES:
  < typename iterator_traits<Iter>::difference_type, 	-> ptrdiff_t
	typename iterator_traits<Iter>::value_type,			-> T
	typename iterator_traits<Iter>::pointer,			-> T* / const T*
	typename iterator_traits<Iter>::reference,			-> T& / const T&
	typename iterator_traits<Iter>::iterator_category >	-> random_access_iterator_tag			  

=> ITERATOR CATEGORY TAGS:
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag {};
	struct bidirectional_iterator_tag {};
	struct random_access_iterator_tag {};	

=> ITERATORS:
	template<typename T, class Category, typename T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&> struct iterator
*/

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace ft {

typedef std::output_iterator_tag        output_iterator_tag;
typedef std::input_iterator_tag         input_iterator_tag;
typedef std::forward_iterator_tag       forward_iterator_tag;
typedef std::bidirectional_iterator_tag bidirectional_iterator_tag;
typedef std::random_access_iterator_tag random_access_iterator_tag;

template <class Iterator>
class iterator_traits {
   public:
    typedef typename Iterator::difference_type   difference_type;
    typedef typename Iterator::value_type        value_type;
    typedef typename Iterator::pointer           pointer;
    typedef typename Iterator::reference         reference;
    typedef typename Iterator::iterator_category iterator_category;
};

template <class T>
class iterator_traits<T*> {
   public:
    typedef std::ptrdiff_t             difference_type;
    typedef T                          value_type;
    typedef T*                         pointer;
    typedef T&                         reference;
    typedef random_access_iterator_tag iterator_category;
};

template <class T>
class iterator_traits<const T*> {
   public:
    typedef std::ptrdiff_t             difference_type;
    typedef T                          value_type;
    typedef const T*                   pointer;
    typedef const T&                   reference;
    typedef random_access_iterator_tag iterator_category;
};

template <class Iterator>
typename ft::iterator_traits<Iterator>::iterator_category iterator_category(const Iterator&) {
    return (typename ft::iterator_traits<Iterator>::iterator_category());
}
    
template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
struct iterator {
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;
};

template <class Iterator>
class reverse_iterator {
   public:
    typedef Iterator                                              iterator_type;
    typedef typename iterator_traits<Iterator>::value_type        value_type;
    typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
    typedef typename iterator_traits<Iterator>::difference_type   difference_type;
    typedef typename iterator_traits<Iterator>::pointer           pointer;
    typedef typename iterator_traits<Iterator>::reference         reference;

    reverse_iterator() : _current() {}

    explicit reverse_iterator(iterator_type it) : _current(it) {}

    template <class Iter>
    reverse_iterator(const reverse_iterator<Iter> &rev_it) : _current(rev_it.base()) {}

    ~reverse_iterator() {}

    iterator_type base() const { return (_current); }

    reference operator*() const {
        iterator_type tmp = _current;
        return *(--tmp);
    }

    reverse_iterator &operator++() {
        _current--;
        return (*this);
    }

    reverse_iterator operator++(int) {
        reverse_iterator tmp = *this;
        --_current;
        return (tmp);
    }

    reverse_iterator &operator--() {
        _current++;
        return (*this);
    }

    reverse_iterator operator--(int) {
        reverse_iterator tmp = *this;
        ++_current;
        return (tmp);
    }

    reverse_iterator operator+(difference_type n) const { return reverse_iterator(_current - n); }

    reverse_iterator operator-(difference_type n) const { return reverse_iterator(_current + n); }

    reverse_iterator &operator+=(difference_type n) {
        _current -= n;
        return (*this);
    }

    reverse_iterator &operator-=(difference_type n) {
        _current += n;
        return (*this);
    }

    pointer operator->() const { return pointer(&(operator*())); }

    reference operator[](difference_type n) const { return *(operator+(n)); }

   private:
    iterator_type _current;
};

template <class Iterator1, class Iterator2>
bool operator==(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y) {
    return x.base() == y.base();
}

template <class Iterator1, class Iterator2>
bool operator!=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y) {
    return !(x == y);
}

template <class Iterator1, class Iterator2>
bool operator<(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y) {
    return y.base() < x.base();
}

template <class Iterator1, class Iterator2>
bool operator<=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y) {
    return !(x > y);
}

template <class Iterator1, class Iterator2>
bool operator>(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y) {
    return y < x;
}

template <class Iterator1, class Iterator2>
bool operator>=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y) {
    return !(x < y);
}

template <class Iterator>
reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &rev_it) {
    return reverse_iterator<Iterator>(rev_it + n);
}

template <class Iterator1, class Iterator2>
typename reverse_iterator<Iterator1>::difference_type operator-(const reverse_iterator<Iterator1> &x, const reverse_iterator<Iterator2> &y) {
    return typename reverse_iterator<Iterator1>::difference_type(y.base() - x.base());
}

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
    friend random_access_iterator operator-(const random_access_iterator<V>& x, const random_access_iterator<V>& y);

   protected:
    pointer _ptr;
};

template <class U, class V>
bool operator==(const random_access_iterator<U>& x, const random_access_iterator<V>& y) {
    return x.base() == y.base();
}

template <class U, class V>
bool operator!=(const random_access_iterator<U>& x, const random_access_iterator<V>& y) {
    return !(x == y);
}

template <class U, class V>
bool operator<(const random_access_iterator<U>& x, const random_access_iterator<V>& y) {
    return (x.base() < y.base());
}

template <class U, class V>
bool operator<=(const random_access_iterator<U>& x, const random_access_iterator<V>& y) {
    return !(x > y);
}

template <class U, class V>
bool operator>(const random_access_iterator<U>& x, const random_access_iterator<V>& y) {
    return y < x;
}

template <class U, class V>
bool operator>=(const random_access_iterator<U>& x, const random_access_iterator<V>& y) {
    return !(x < y);
}

template <class U>
random_access_iterator<U> operator+(const typename random_access_iterator<U>::difference_type& x, const random_access_iterator<U>& y) {
    return random_access_iterator<U>(y.base() + x);
}

template <class U>
typename random_access_iterator<U>::difference_type operator-(
    const random_access_iterator<U>& x, const random_access_iterator<U>& y) {
    return typename random_access_iterator<U>::difference_type(x.base() - y.base());
}

template <class U, class V>
typename random_access_iterator<U>::difference_type operator-(
    const random_access_iterator<U>& x, const random_access_iterator<V>& y) {
    return typename random_access_iterator<U>::difference_type(x.base() - y.base());
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