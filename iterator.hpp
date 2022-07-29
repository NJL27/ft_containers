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

#ifndef FT_ITERATOR_HPP
#define FT_ITERATOR_HPP

// #include <iterator>

namespace ft{


// ===== ITERATOR TRAITS =====

	template <class Iter>																				//iterator line 20
	struct iterator_traits{																				//iterator line 21
		typedef typename Iter::difference_type difference_type;											//iterator line 23
    	typedef typename Iter::value_type value_type;													//iterator line 24
    	typedef typename Iter::pointer pointer;															//iterator line 25
    	typedef typename Iter::reference reference;														//iterator line 26
    	typedef typename Iter::iterator_category iterator_category;										//iterator line 27
	};

// ===== ITERATOR SPECIALIZATIONS =====

	template<class T>																					//iterator line 30	
	struct iterator_traits<T*>{																			//iterator line 31		
	    typedef std::ptrdiff_t 					difference_type;										//iterator line 33
	    typedef T 								value_type;												//iterator line 34
	    typedef T* 								pointer;												//iterator line 35
	    typedef T& 								reference;												//iterator line 36
	    typedef std::random_access_iterator_tag iterator_category;										//iterator line 37
	};

	template<class T>
	struct iterator_traits<const T*>{
	    typedef std::ptrdiff_t 					difference_type;											
	    typedef T 								value_type;													
	    typedef const T* 						pointer;													
	    typedef const T& 						reference;													
	    typedef std::random_access_iterator_tag	iterator_category;											
	};

// ===== ITERATORS =====

template <class Category, typename T, class Distance = ptrdiff_t,										//iterator line 40	
			class Pointer = T*, class Reference = T&>													//iterator line 41	
struct iterator{																						//iterator line 42
	typedef T         value_type;																		//iterator line 44
    typedef Distance  difference_type;																	//iterator line 45
    typedef Pointer   pointer;																			//iterator line 46
    typedef Reference reference;																		//iterator line 47
    typedef Category  iterator_category;																//iterator line 48
};

// ===== ITERATOR CATEGORY TAGS =====

	struct input_iterator_tag {};																		//iterator line 433
	struct output_iterator_tag {};																		//iterator line 434
	struct forward_iterator_tag       : public input_iterator_tag {};									//iterator line 435
	struct bidirectional_iterator_tag : public forward_iterator_tag {};									//iterator line 436
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};							//iterator line 437

// ====== REVERSE ITERATOR ======

	template <class Iter>																				//iterator line 631
	class reverse_iterator : public iterator															//iterator line 632
<	typename iterator_traits<Iter>::iterator_category,													//iterator line 633	
    typename iterator_traits<Iter>::value_type,															//iterator line 634
    typename iterator_traits<Iter>::difference_type,													//iterator line 635	
    typename iterator_traits<Iter>::pointer,															//iterator line 636
    typename iterator_traits<Iter>::reference >															//iterator line 637
{
protected:
	Iter current;																						//iterator line 647
public:
    typedef Iter                                           		iterator_type;							//iterator line 649
    typedef typename iterator_traits<Iter>::iterator_category 	iterator_category;						
    typedef typename iterator_traits<Iter>::value_type 			value_type;
    typedef typename iterator_traits<Iter>::difference_type 	difference_type;						//iterator line 650
    typedef typename iterator_traits<Iter>::reference       	reference;								//iterator line 651
    typedef typename iterator_traits<Iter>::pointer         	pointer;								//iterator line 652

	reverse_iterator() : current() {}																	//iterator line 655
	explicit reverse_iterator(Iter x) : current(x) {}													//iterator line 657
	template <class Up> reverse_iterator(const reverse_iterator<Up>& u) : current(u.base()) {} 			//iterator line 659
	template <class Up> reverse_iterator& operator=(const reverse_iterator<Up>& u) {					//iterator line 661
		current = u.base();																				//iterator line 664
		return *this;																					//iterator line 664
	}
	Iter base() const {return current;}																	//iterator line 666
	reference operator*() const {Iter tmp = current; return *--tmp;}									//iterator line 668
	pointer operator->() const {return &(operator*());}													//iterator line 670
	reverse_iterator& operator++() {--current; return *this;}											//iterator line 672
    reverse_iterator  operator++(int) {reverse_iterator tmp(*this); --current; return tmp;}				//iterator line 674
    reverse_iterator& operator--() {++current; return *this;}											//iterator line 676
    reverse_iterator  operator--(int) {reverse_iterator tmp(*this); ++current; return tmp;}				//iterator line 678
    reverse_iterator  operator+ (difference_type n) const {return reverse_iterator(current - n);}		//iterator line 680	
    reverse_iterator& operator+=(difference_type n) {current -= n; return *this;}						//iterator line 682
    reverse_iterator  operator- (difference_type n) const {return reverse_iterator(current + n);}		//iterator line 684
    reverse_iterator& operator-=(difference_type n) {current += n; return *this;}						//iterator line 686
    reference         operator[](difference_type n) const {return *(*this + n);}						//iterator line 688
};

template <class Iter1, class Iter2>
bool operator==(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y){					//iterator line 694
    return x.base() == y.base();
}

template <class Iter1, class Iter2>
bool operator<(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y){						//iterator line 702
    return x.base() > y.base();
}

template <class Iter1, class Iter2>
bool operator!=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y){					//iterator line 710
    return x.base() != y.base();
}

template <class Iter1, class Iter2>
bool operator>(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y){						//iterator line 718
    return x.base() < y.base();
}

template <class Iter1, class Iter2>
bool operator>=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y){					//iterator line 726
    return x.base() <= y.base();
}

template <class Iter1, class Iter2>
bool operator<=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y){					//iterator line 734
    return x.base() >= y.base();
}

template <class Iter1, class Iter2>
typename reverse_iterator<Iter1>::difference_type
operator-(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y){							//iterator line 752
    return y.base() - x.base();
}

template <class Iter>
reverse_iterator<Iter>
operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& x){			//iterator line 761
    return reverse_iterator<Iter>(x.base() - n);
}

}
#endif


// ORIGINAL REFERENCE AS ONE CANNOT TRUST NO ONE

// -*- C++ -*-
//===-------------------------- iterator ----------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// #ifndef _LIBCPP_ITERATOR			COMMENT THESE IN
// #define _LIBCPP_ITERATOR			COMMENT THESE IN

/*
    iterator synopsis

namespace std
{

template<class Iterator>
struct iterator_traits
{
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
    typedef typename Iterator::iterator_category iterator_category;
};

template<class T>
struct iterator_traits<T*>
{
    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef random_access_iterator_tag iterator_category;
};

template<class Category, class T, class Distance = ptrdiff_t,
         class Pointer = T*, class Reference = T&>
struct iterator
{
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;
};

struct input_iterator_tag  {};
struct output_iterator_tag {};
struct forward_iterator_tag       : public input_iterator_tag         {};
struct bidirectional_iterator_tag : public forward_iterator_tag       {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

// 27.4.3, iterator operations
// extension: second argument not conforming to C++03
template <class InputIterator>  // constexpr in C++17
  constexpr void advance(InputIterator& i,
             typename iterator_traits<InputIterator>::difference_type n);

template <class InputIterator>  // constexpr in C++17
  constexpr typename iterator_traits<InputIterator>::difference_type
    distance(InputIterator first, InputIterator last);

template <class InputIterator>  // constexpr in C++17
  constexpr InputIterator next(InputIterator x,
typename iterator_traits<InputIterator>::difference_type n = 1);

template <class BidirectionalIterator>  // constexpr in C++17
  constexpr BidirectionalIterator prev(BidirectionalIterator x,
    typename iterator_traits<BidirectionalIterator>::difference_type n = 1);    

template <class Iterator>
class reverse_iterator
    : public iterator<typename iterator_traits<Iterator>::iterator_category,
                      typename iterator_traits<Iterator>::value_type,
                      typename iterator_traits<Iterator>::difference_type,
                      typename iterator_traits<Iterator>::pointer,
                      typename iterator_traits<Iterator>::reference>
{
protected:
    Iterator current;
public:
    typedef Iterator                                            iterator_type;
    typedef typename iterator_traits<Iterator>::difference_type difference_type;
    typedef typename iterator_traits<Iterator>::reference       reference;
    typedef typename iterator_traits<Iterator>::pointer         pointer;

    constexpr reverse_iterator();
    constexpr explicit reverse_iterator(Iterator x);
    template <class U> constexpr reverse_iterator(const reverse_iterator<U>& u);
    template <class U> constexpr reverse_iterator& operator=(const reverse_iterator<U>& u);
    constexpr Iterator base() const;
    constexpr reference operator*() const;
    constexpr pointer   operator->() const;
    constexpr reverse_iterator& operator++();
    constexpr reverse_iterator  operator++(int);
    constexpr reverse_iterator& operator--();
    constexpr reverse_iterator  operator--(int);
    constexpr reverse_iterator  operator+ (difference_type n) const;
    constexpr reverse_iterator& operator+=(difference_type n);
    constexpr reverse_iterator  operator- (difference_type n) const;
    constexpr reverse_iterator& operator-=(difference_type n);
    constexpr reference         operator[](difference_type n) const;
};

template <class Iterator1, class Iterator2>
constexpr bool                          // constexpr in C++17
operator==(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr bool                          // constexpr in C++17
operator<(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr bool                          // constexpr in C++17
operator!=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr bool                          // constexpr in C++17
operator>(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr bool                          // constexpr in C++17
operator>=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr bool                          // constexpr in C++17
operator<=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr auto
operator-(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y)
-> decltype(__y.base() - __x.base());   // constexpr in C++17

template <class Iterator>
constexpr reverse_iterator<Iterator>
operator+(typename reverse_iterator<Iterator>::difference_type n, 
          const reverse_iterator<Iterator>& x);   // constexpr in C++17

template <class Iterator>
constexpr reverse_iterator<Iterator> make_reverse_iterator(Iterator i); // C++14, constexpr in C++17

template <class Container>
class back_insert_iterator
{
protected:
    Container* container;
public:
    typedef Container                   container_type;
    typedef void                        value_type;
    typedef void                        difference_type;
    typedef void                        reference;
    typedef void                        pointer;

    explicit back_insert_iterator(Container& x);
    back_insert_iterator& operator=(const typename Container::value_type& value);
    back_insert_iterator& operator*();
    back_insert_iterator& operator++();
    back_insert_iterator  operator++(int);
};

template <class Container> back_insert_iterator<Container> back_inserter(Container& x);

template <class Container>
class front_insert_iterator
{
protected:
    Container* container;
public:
    typedef Container                    container_type;
    typedef void                         value_type;
    typedef void                         difference_type;
    typedef void                         reference;
    typedef void                         pointer;

    explicit front_insert_iterator(Container& x);
    front_insert_iterator& operator=(const typename Container::value_type& value);
    front_insert_iterator& operator*();
    front_insert_iterator& operator++();
    front_insert_iterator  operator++(int);
};

template <class Container> front_insert_iterator<Container> front_inserter(Container& x);

template <class Container>
class insert_iterator
{
protected:
    Container* container;
    typename Container::iterator iter;
public:
    typedef Container              container_type;
    typedef void                   value_type;
    typedef void                   difference_type;
    typedef void                   reference;
    typedef void                   pointer;

    insert_iterator(Container& x, typename Container::iterator i);
    insert_iterator& operator=(const typename Container::value_type& value);
    insert_iterator& operator*();
    insert_iterator& operator++();
    insert_iterator& operator++(int);
};

template <class Container, class Iterator>
insert_iterator<Container> inserter(Container& x, Iterator i);

template <class Iterator>
class move_iterator {
public:
    typedef Iterator                                              iterator_type;
    typedef typename iterator_traits<Iterator>::difference_type   difference_type;
    typedef Iterator                                              pointer;
    typedef typename iterator_traits<Iterator>::value_type        value_type;
    typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
    typedef value_type&&                                          reference;
 
    constexpr move_iterator();  // all the constexprs are in C++17
    constexpr explicit move_iterator(Iterator i);
    template <class U>
      constexpr move_iterator(const move_iterator<U>& u);
    template <class U>
      constexpr move_iterator& operator=(const move_iterator<U>& u);
    constexpr iterator_type base() const;
    constexpr reference operator*() const;
    constexpr pointer operator->() const;
    constexpr move_iterator& operator++();
    constexpr move_iterator operator++(int);
    constexpr move_iterator& operator--();
    constexpr move_iterator operator--(int);
    constexpr move_iterator operator+(difference_type n) const; 
    constexpr move_iterator& operator+=(difference_type n); 
    constexpr move_iterator operator-(difference_type n) const; 
    constexpr move_iterator& operator-=(difference_type n); 
    constexpr unspecified operator[](difference_type n) const;
private:
    Iterator current; // exposition only
};

template <class Iterator1, class Iterator2>
constexpr bool   // constexpr in C++17
operator==(const move_iterator<Iterator1>& x, const move_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr bool   // constexpr in C++17
operator!=(const move_iterator<Iterator1>& x, const move_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr bool   // constexpr in C++17
operator<(const move_iterator<Iterator1>& x, const move_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr bool   // constexpr in C++17
operator<=(const move_iterator<Iterator1>& x, const move_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr bool   // constexpr in C++17
operator>(const move_iterator<Iterator1>& x, const move_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr bool   // constexpr in C++17
operator>=(const move_iterator<Iterator1>& x, const move_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr auto   // constexpr in C++17
operator-(const move_iterator<Iterator1>& x,
          const move_iterator<Iterator2>& y) -> decltype(x.base() - y.base());

template <class Iterator>
constexpr move_iterator<Iterator> operator+(   // constexpr in C++17
            typename move_iterator<Iterator>::difference_type n, 
            const move_iterator<Iterator>& x);

template <class Iterator>   // constexpr in C++17
constexpr  move_iterator<Iterator> make_move_iterator(const Iterator& i);


template <class T, class charT = char, class traits = char_traits<charT>, class Distance = ptrdiff_t>
class istream_iterator
    : public iterator<input_iterator_tag, T, Distance, const T*, const T&>
{
public:
    typedef charT char_type;
    typedef traits traits_type;
    typedef basic_istream<charT,traits> istream_type;

    constexpr istream_iterator();
    istream_iterator(istream_type& s);
    istream_iterator(const istream_iterator& x);
    ~istream_iterator();

    const T& operator*() const;
    const T* operator->() const;
    istream_iterator& operator++();
    istream_iterator  operator++(int);
};

template <class T, class charT, class traits, class Distance>
bool operator==(const istream_iterator<T,charT,traits,Distance>& x,
                const istream_iterator<T,charT,traits,Distance>& y);
template <class T, class charT, class traits, class Distance>
bool operator!=(const istream_iterator<T,charT,traits,Distance>& x,
                const istream_iterator<T,charT,traits,Distance>& y);

template <class T, class charT = char, class traits = char_traits<charT> >
class ostream_iterator
    : public iterator<output_iterator_tag, void, void, void ,void>
{
public:
    typedef charT char_type;
    typedef traits traits_type;
    typedef basic_ostream<charT,traits> ostream_type;

    ostream_iterator(ostream_type& s);
    ostream_iterator(ostream_type& s, const charT* delimiter);
    ostream_iterator(const ostream_iterator& x);
    ~ostream_iterator();
    ostream_iterator& operator=(const T& value);

    ostream_iterator& operator*();
    ostream_iterator& operator++();
    ostream_iterator& operator++(int);
};

template<class charT, class traits = char_traits<charT> >
class istreambuf_iterator
    : public iterator<input_iterator_tag, charT,
                      typename traits::off_type, unspecified,
                      charT>
{
public:
    typedef charT                         char_type;
    typedef traits                        traits_type;
    typedef typename traits::int_type     int_type;
    typedef basic_streambuf<charT,traits> streambuf_type;
    typedef basic_istream<charT,traits>   istream_type;

    istreambuf_iterator() noexcept;
    istreambuf_iterator(istream_type& s) noexcept;
    istreambuf_iterator(streambuf_type* s) noexcept;
    istreambuf_iterator(a-private-type) noexcept;

    charT                operator*() const;
    pointer operator->() const;
    istreambuf_iterator& operator++();
    a-private-type       operator++(int);

    bool equal(const istreambuf_iterator& b) const;
};

template <class charT, class traits>
bool operator==(const istreambuf_iterator<charT,traits>& a,
                const istreambuf_iterator<charT,traits>& b);
template <class charT, class traits>
bool operator!=(const istreambuf_iterator<charT,traits>& a,
                const istreambuf_iterator<charT,traits>& b);

template <class charT, class traits = char_traits<charT> >
class ostreambuf_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
{
public:
    typedef charT                         char_type;
    typedef traits                        traits_type;
    typedef basic_streambuf<charT,traits> streambuf_type;
    typedef basic_ostream<charT,traits>   ostream_type;

    ostreambuf_iterator(ostream_type& s) noexcept;
    ostreambuf_iterator(streambuf_type* s) noexcept;
    ostreambuf_iterator& operator=(charT c);
    ostreambuf_iterator& operator*();
    ostreambuf_iterator& operator++();
    ostreambuf_iterator& operator++(int);
    bool failed() const noexcept;
};

template <class C> constexpr auto begin(C& c) -> decltype(c.begin());
template <class C> constexpr auto begin(const C& c) -> decltype(c.begin());
template <class C> constexpr auto end(C& c) -> decltype(c.end());
template <class C> constexpr auto end(const C& c) -> decltype(c.end());
template <class T, size_t N> constexpr T* begin(T (&array)[N]);
template <class T, size_t N> constexpr T* end(T (&array)[N]);

template <class C> auto constexpr cbegin(const C& c) -> decltype(std::begin(c));        // C++14
template <class C> auto constexpr cend(const C& c) -> decltype(std::end(c));            // C++14
template <class C> auto constexpr rbegin(C& c) -> decltype(c.rbegin());                 // C++14
template <class C> auto constexpr rbegin(const C& c) -> decltype(c.rbegin());           // C++14
template <class C> auto constexpr rend(C& c) -> decltype(c.rend());                     // C++14
template <class C> constexpr auto rend(const C& c) -> decltype(c.rend());               // C++14
template <class E> reverse_iterator<const E*> constexpr rbegin(initializer_list<E> il); // C++14
template <class E> reverse_iterator<const E*> constexpr rend(initializer_list<E> il);   // C++14
template <class T, size_t N> reverse_iterator<T*> constexpr rbegin(T (&array)[N]);      // C++14
template <class T, size_t N> reverse_iterator<T*> constexpr rend(T (&array)[N]);        // C++14
template <class C> constexpr auto crbegin(const C& c) -> decltype(std::rbegin(c));      // C++14
template <class C> constexpr auto crend(const C& c) -> decltype(std::rend(c));          // C++14

// 24.8, container access:
template <class C> constexpr auto size(const C& c) -> decltype(c.size());         // C++17
template <class T, size_t N> constexpr size_t size(const T (&array)[N]) noexcept; // C++17
template <class C> constexpr auto empty(const C& c) -> decltype(c.empty());       // C++17
template <class T, size_t N> constexpr bool empty(const T (&array)[N]) noexcept;  // C++17
template <class E> constexpr bool empty(initializer_list<E> il) noexcept;         // C++17
template <class C> constexpr auto data(C& c) -> decltype(c.data());               // C++17
template <class C> constexpr auto data(const C& c) -> decltype(c.data());         // C++17
template <class T, size_t N> constexpr T* data(T (&array)[N]) noexcept;           // C++17
template <class E> constexpr const E* data(initializer_list<E> il) noexcept;      // C++17

}  // std

// EVERYTHING ABOVE NEEDS TO BE COMMENTED OUT EVERYTHIGN BELOW NEEDS TO BE COMMENTED IN

#include <__config>
#include <iosfwd> // for forward declarations of vector and string.
#include <__functional_base>
#include <type_traits>
#include <cstddef>
#include <initializer_list>
#ifdef __APPLE__
#include <Availability.h>
#endif

#include <__debug>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

struct _LIBCPP_TEMPLATE_VIS input_iterator_tag {};
struct _LIBCPP_TEMPLATE_VIS output_iterator_tag {};
struct _LIBCPP_TEMPLATE_VIS forward_iterator_tag       : public input_iterator_tag {};
struct _LIBCPP_TEMPLATE_VIS bidirectional_iterator_tag : public forward_iterator_tag {};
struct _LIBCPP_TEMPLATE_VIS random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class _Tp>
struct __has_iterator_category
{
private:
    struct __two {char __lx; char __lxx;};
    template <class _Up> static __two __test(...);
    template <class _Up> static char __test(typename _Up::iterator_category* = 0);
public:
    static const bool value = sizeof(__test<_Tp>(0)) == 1;
};

template <class _Iter, bool> struct __iterator_traits_impl {};

template <class _Iter>
struct __iterator_traits_impl<_Iter, true>
{
    typedef typename _Iter::difference_type   difference_type;
    typedef typename _Iter::value_type        value_type;
    typedef typename _Iter::pointer           pointer;
    typedef typename _Iter::reference         reference;
    typedef typename _Iter::iterator_category iterator_category;
};

template <class _Iter, bool> struct __iterator_traits {};

template <class _Iter>
struct __iterator_traits<_Iter, true>
    :  __iterator_traits_impl
      <
        _Iter,
        is_convertible<typename _Iter::iterator_category, input_iterator_tag>::value ||
        is_convertible<typename _Iter::iterator_category, output_iterator_tag>::value
      >
{};

// iterator_traits<Iterator> will only have the nested types if Iterator::iterator_category
//    exists.  Else iterator_traits<Iterator> will be an empty class.  This is a
//    conforming extension which allows some programs to compile and behave as
//    the client expects instead of failing at compile time.

template <class _Iter>
struct _LIBCPP_TEMPLATE_VIS iterator_traits
    : __iterator_traits<_Iter, __has_iterator_category<_Iter>::value> {};

template<class _Tp>
struct _LIBCPP_TEMPLATE_VIS iterator_traits<_Tp*>
{
    typedef ptrdiff_t difference_type;
    typedef typename remove_cv<_Tp>::type value_type;
    typedef _Tp* pointer;
    typedef _Tp& reference;
    typedef random_access_iterator_tag iterator_category;
};

template <class _Tp, class _Up, bool = __has_iterator_category<iterator_traits<_Tp> >::value>
struct __has_iterator_category_convertible_to
    : public integral_constant<bool, is_convertible<typename iterator_traits<_Tp>::iterator_category, _Up>::value>
{};

template <class _Tp, class _Up>
struct __has_iterator_category_convertible_to<_Tp, _Up, false> : public false_type {};

template <class _Tp>
struct __is_input_iterator : public __has_iterator_category_convertible_to<_Tp, input_iterator_tag> {};

template <class _Tp>
struct __is_forward_iterator : public __has_iterator_category_convertible_to<_Tp, forward_iterator_tag> {};

template <class _Tp>
struct __is_bidirectional_iterator : public __has_iterator_category_convertible_to<_Tp, bidirectional_iterator_tag> {};

template <class _Tp>
struct __is_random_access_iterator : public __has_iterator_category_convertible_to<_Tp, random_access_iterator_tag> {};

template <class _Tp>
struct __is_exactly_input_iterator
    : public integral_constant<bool, 
         __has_iterator_category_convertible_to<_Tp, input_iterator_tag>::value && 
        !__has_iterator_category_convertible_to<_Tp, forward_iterator_tag>::value> {};

template<class _Category, class _Tp, class _Distance = ptrdiff_t,
         class _Pointer = _Tp*, class _Reference = _Tp&>
struct _LIBCPP_TEMPLATE_VIS iterator
{
    typedef _Tp        value_type;
    typedef _Distance  difference_type;
    typedef _Pointer   pointer;
    typedef _Reference reference;
    typedef _Category  iterator_category;
};

template <class _InputIter>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
void __advance(_InputIter& __i,
             typename iterator_traits<_InputIter>::difference_type __n, input_iterator_tag)
{
    for (; __n > 0; --__n)
        ++__i;
}

template <class _BiDirIter>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
void __advance(_BiDirIter& __i,
             typename iterator_traits<_BiDirIter>::difference_type __n, bidirectional_iterator_tag)
{
    if (__n >= 0)
        for (; __n > 0; --__n)
            ++__i;
    else
        for (; __n < 0; ++__n)
            --__i;
}

template <class _RandIter>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
void __advance(_RandIter& __i,
             typename iterator_traits<_RandIter>::difference_type __n, random_access_iterator_tag)
{
   __i += __n;
}

template <class _InputIter>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
void advance(_InputIter& __i,
             typename iterator_traits<_InputIter>::difference_type __n)
{
    __advance(__i, __n, typename iterator_traits<_InputIter>::iterator_category());
}

template <class _InputIter>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
typename iterator_traits<_InputIter>::difference_type
__distance(_InputIter __first, _InputIter __last, input_iterator_tag)
{
    typename iterator_traits<_InputIter>::difference_type __r(0);
    for (; __first != __last; ++__first)
        ++__r;
    return __r;
}

template <class _RandIter>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
typename iterator_traits<_RandIter>::difference_type
__distance(_RandIter __first, _RandIter __last, random_access_iterator_tag)
{
    return __last - __first;
}

template <class _InputIter>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
typename iterator_traits<_InputIter>::difference_type
distance(_InputIter __first, _InputIter __last)
{
    return __distance(__first, __last, typename iterator_traits<_InputIter>::iterator_category());
}

template <class _InputIter>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
typename enable_if
<
    __is_input_iterator<_InputIter>::value, 
    _InputIter
>::type
next(_InputIter __x,
     typename iterator_traits<_InputIter>::difference_type __n = 1)
{
    _VSTD::advance(__x, __n);
    return __x;
}

template <class _BidirectionalIter>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
typename enable_if
<
    __is_bidirectional_iterator<_BidirectionalIter>::value, 
    _BidirectionalIter
>::type
prev(_BidirectionalIter __x,
     typename iterator_traits<_BidirectionalIter>::difference_type __n = 1)
{
    _VSTD::advance(__x, -__n);
    return __x;
}


template <class _Tp, class = void>
struct __is_stashing_iterator : false_type {};

template <class _Tp>
struct __is_stashing_iterator<_Tp, typename __void_t<typename _Tp::__stashing_iterator_tag>::type>
  : true_type {};

template <class _Iter>
class _LIBCPP_TEMPLATE_VIS reverse_iterator
    : public iterator<typename iterator_traits<_Iter>::iterator_category,
                      typename iterator_traits<_Iter>::value_type,
                      typename iterator_traits<_Iter>::difference_type,
                      typename iterator_traits<_Iter>::pointer,
                      typename iterator_traits<_Iter>::reference>
{
private:
    /*mutable _Iter __t;  // no longer used as of LWG #2360, not removed due to ABI break

    static_assert(!__is_stashing_iterator<_Iter>::value,
      "The specified iterator type cannot be used with reverse_iterator; "
      "Using stashing iterators with reverse_iterator causes undefined behavior");

protected:
    _Iter current;
public:
    typedef _Iter                                            iterator_type;
    typedef typename iterator_traits<_Iter>::difference_type difference_type;
    typedef typename iterator_traits<_Iter>::reference       reference;
    typedef typename iterator_traits<_Iter>::pointer         pointer;

    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
    reverse_iterator() : __t(), current() {}
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
    explicit reverse_iterator(_Iter __x) : __t(__x), current(__x) {}
    template <class _Up>
        _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
        reverse_iterator(const reverse_iterator<_Up>& __u) : __t(__u.base()), current(__u.base()) {}
    template <class _Up>
        _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
        reverse_iterator& operator=(const reverse_iterator<_Up>& __u)
            { __t = current = __u.base(); return *this; }
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
    _Iter base() const {return current;}
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
    reference operator*() const {_Iter __tmp = current; return *--__tmp;}
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
    pointer  operator->() const {return _VSTD::addressof(operator*());}
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
    reverse_iterator& operator++() {--current; return *this;}
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
    reverse_iterator  operator++(int) {reverse_iterator __tmp(*this); --current; return __tmp;}
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
    reverse_iterator& operator--() {++current; return *this;}
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
    reverse_iterator  operator--(int) {reverse_iterator __tmp(*this); ++current; return __tmp;}
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
    reverse_iterator  operator+ (difference_type __n) const {return reverse_iterator(current - __n);}
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
    reverse_iterator& operator+=(difference_type __n) {current -= __n; return *this;}
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
    reverse_iterator  operator- (difference_type __n) const {return reverse_iterator(current + __n);}
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
    reverse_iterator& operator-=(difference_type __n) {current += __n; return *this;}
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
    reference         operator[](difference_type __n) const {return *(*this + __n);}
};

template <class _Iter1, class _Iter2>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
bool
operator==(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __x.base() == __y.base();
}

template <class _Iter1, class _Iter2>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
bool
operator<(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __x.base() > __y.base();
}

template <class _Iter1, class _Iter2>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
bool
operator!=(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __x.base() != __y.base();
}

template <class _Iter1, class _Iter2>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
bool
operator>(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __x.base() < __y.base();
}

template <class _Iter1, class _Iter2>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
bool
operator>=(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __x.base() <= __y.base();
}

template <class _Iter1, class _Iter2>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
bool
operator<=(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __x.base() >= __y.base();
}

#ifndef _LIBCPP_CXX03_LANG
template <class _Iter1, class _Iter2>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
auto
operator-(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
-> decltype(__y.base() - __x.base())
{
    return __y.base() - __x.base();
}
#else
template <class _Iter1, class _Iter2>
inline _LIBCPP_INLINE_VISIBILITY
typename reverse_iterator<_Iter1>::difference_type
operator-(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __y.base() - __x.base();
}
#endif

template <class _Iter>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
reverse_iterator<_Iter>
operator+(typename reverse_iterator<_Iter>::difference_type __n, const reverse_iterator<_Iter>& __x)
{
    return reverse_iterator<_Iter>(__x.base() - __n);
}

#if _LIBCPP_STD_VER > 11
template <class _Iter>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
reverse_iterator<_Iter> make_reverse_iterator(_Iter __i)
{
    return reverse_iterator<_Iter>(__i);
}
#endif

*/