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

#ifndef FT_UTILITY_HPP
#define FT_UTILITY_HPP

#include <utility>

namespace ft{

	template <class T1, class T2> 																//utilities line 313
	struct pair{																				//utilities line 314
		typedef T1 first_type;																	//utilities line 319
		typedef T2 second_type;																	//utilities line 320

		first_type first;																		//utilities line 322
		second_type second;																		//utilities line 323

		pair() : first(), second() {}															//utilities line 334
		pair(const T1& t1, const T2& t2) : first(t1), second(t2) {} 							//utilities line 337
		template <class U1, class U2> 															//utilities line 339
		pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}						//utilities line 341
		pair& operator=(const pair& p){ 														//utilities line 344
			first = p.first;																	//utilities line 345
			second = p.second;																	//utilities line 346
			return *this;																		//utilities line 347
		}
	};

	template <class T1, class T2>
	bool operator==(const typename ft::pair<T1, T2>& x, const typename ft::pair<T1, T2>& y){	//utilities line 578
		return x.first == y.first && x.second == y.second;										
	}

	template <class T1, class T2>
	bool operator!=(const typename ft::pair<T1, T2>& x, const typename ft::pair<T1, T2>& y){	//utilities line 586
		return !(x == y);																	
	}

	template <class T1, class T2>
	bool operator<(const typename ft::pair<T1, T2>& x, const typename ft::pair<T1, T2>& y){		//utilities line 594
		return x.first < y.first || (!(y.first < x.first) && x.second < y.second);				
	}

	template <class T1, class T2>
	bool operator>(const typename ft::pair<T1, T2>& x, const typename ft::pair<T1, T2>& y){		//utilities line 602
		return x > y;																		
	}

	template <class T1, class T2>
	bool operator>=(const typename ft::pair<T1, T2>& x, const typename ft::pair<T1, T2>& y){	//utilities line 610
		return !(x < y);																		
	}

	template <class T1, class T2>
	bool operator<=(const typename ft::pair<T1, T2>& x, const typename ft::pair<T1, T2>& y){	//utilities line 618
		return !(x > y);																		
	}

	template <class T1, class T2>
	ft::pair<T1, T2> make_pair(T1 x, T2 y){														//utilities line 672
		return (ft::pair<T1, T2>(x, y));														//utilities line 674
	}
}

#endif


// ORIGINAL REFERECNE AS ONE CANNOT TRUST NO ONE

// -*- C++ -*-
//===-------------------------- utility -----------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// #ifndef _LIBCPP_UTILITY				COMMENT THESE IN
// #define _LIBCPP_UTILITY				COMMENT THESE IN

/*
    utility synopsis

#include <initializer_list>

namespace std
{

template <class T>
    void
    swap(T& a, T& b);

namespace rel_ops
{
    template<class T> bool operator!=(const T&, const T&);
    template<class T> bool operator> (const T&, const T&);
    template<class T> bool operator<=(const T&, const T&);
    template<class T> bool operator>=(const T&, const T&);
}

template<class T>
void
swap(T& a, T& b) noexcept(is_nothrow_move_constructible<T>::value &&
                          is_nothrow_move_assignable<T>::value);

template <class T, size_t N>
void
swap(T (&a)[N], T (&b)[N]) noexcept(noexcept(swap(*a, *b)));

template <class T> T&& forward(typename remove_reference<T>::type& t) noexcept;  // constexpr in C++14
template <class T> T&& forward(typename remove_reference<T>::type&& t) noexcept; // constexpr in C++14

template <class T> typename remove_reference<T>::type&& move(T&&) noexcept;      // constexpr in C++14

template <class T>
    typename conditional
    <
        !is_nothrow_move_constructible<T>::value && is_copy_constructible<T>::value,
        const T&,
        T&&
    >::type
    move_if_noexcept(T& x) noexcept; // constexpr in C++14

template <class T> constexpr add_const_t<T>& as_const(T& t) noexcept;      // C++17
template <class T>                      void as_const(const T&&) = delete; // C++17

template <class T> typename add_rvalue_reference<T>::type declval() noexcept;

template <class T1, class T2>
struct pair
{
    typedef T1 first_type;
    typedef T2 second_type;

    T1 first;
    T2 second;

    pair(const pair&) = default;
    pair(pair&&) = default;
    constexpr pair();
    pair(const T1& x, const T2& y);                          // constexpr in C++14
    template <class U, class V> pair(U&& x, V&& y);          // constexpr in C++14
    template <class U, class V> pair(const pair<U, V>& p);   // constexpr in C++14
    template <class U, class V> pair(pair<U, V>&& p);        // constexpr in C++14
    template <class... Args1, class... Args2>
        pair(piecewise_construct_t, tuple<Args1...> first_args,
             tuple<Args2...> second_args);

    template <class U, class V> pair& operator=(const pair<U, V>& p);
    pair& operator=(pair&& p) noexcept(is_nothrow_move_assignable<T1>::value &&
                                       is_nothrow_move_assignable<T2>::value);
    template <class U, class V> pair& operator=(pair<U, V>&& p);

    void swap(pair& p) noexcept(is_nothrow_swappable_v<T1> &&
                                is_nothrow_swappable_v<T2>);
};

template <class T1, class T2> bool operator==(const pair<T1,T2>&, const pair<T1,T2>&); // constexpr in C++14
template <class T1, class T2> bool operator!=(const pair<T1,T2>&, const pair<T1,T2>&); // constexpr in C++14
template <class T1, class T2> bool operator< (const pair<T1,T2>&, const pair<T1,T2>&); // constexpr in C++14
template <class T1, class T2> bool operator> (const pair<T1,T2>&, const pair<T1,T2>&); // constexpr in C++14
template <class T1, class T2> bool operator>=(const pair<T1,T2>&, const pair<T1,T2>&); // constexpr in C++14
template <class T1, class T2> bool operator<=(const pair<T1,T2>&, const pair<T1,T2>&); // constexpr in C++14

template <class T1, class T2> pair<V1, V2> make_pair(T1&&, T2&&);   // constexpr in C++14
template <class T1, class T2>
void
swap(pair<T1, T2>& x, pair<T1, T2>& y) noexcept(noexcept(x.swap(y)));

struct piecewise_construct_t { };
inline constexpr piecewise_construct_t piecewise_construct = piecewise_construct_t();

template <class T> class tuple_size;
template <size_t I, class T> class tuple_element;

template <class T1, class T2> struct tuple_size<pair<T1, T2> >;
template <class T1, class T2> struct tuple_element<0, pair<T1, T2> >;
template <class T1, class T2> struct tuple_element<1, pair<T1, T2> >;

template<size_t I, class T1, class T2>
    typename tuple_element<I, pair<T1, T2> >::type&
    get(pair<T1, T2>&) noexcept; // constexpr in C++14

template<size_t I, class T1, class T2>
    const typename tuple_element<I, pair<T1, T2> >::type&
    get(const pair<T1, T2>&) noexcept; // constexpr in C++14

template<size_t I, class T1, class T2>
    typename tuple_element<I, pair<T1, T2> >::type&&
    get(pair<T1, T2>&&) noexcept; // constexpr in C++14

template<size_t I, class T1, class T2>
    const typename tuple_element<I, pair<T1, T2> >::type&&
    get(const pair<T1, T2>&&) noexcept; // constexpr in C++14

template<class T1, class T2>
    constexpr T1& get(pair<T1, T2>&) noexcept; // C++14

template<class T1, class T2>
    constexpr const T1& get(const pair<T1, T2>&) noexcept; // C++14

template<class T1, class T2>
    constexpr T1&& get(pair<T1, T2>&&) noexcept; // C++14

template<class T1, class T2>
    constexpr const T1&& get(const pair<T1, T2>&&) noexcept; // C++14

template<class T1, class T2>
    constexpr T1& get(pair<T2, T1>&) noexcept; // C++14

template<class T1, class T2>
    constexpr const T1& get(const pair<T2, T1>&) noexcept; // C++14

template<class T1, class T2>
    constexpr T1&& get(pair<T2, T1>&&) noexcept; // C++14

template<class T1, class T2>
    constexpr const T1&& get(const pair<T2, T1>&&) noexcept; // C++14

// C++14

template<class T, T... I>
struct integer_sequence
{
    typedef T value_type;

    static constexpr size_t size() noexcept;
};

template<size_t... I>
  using index_sequence = integer_sequence<size_t, I...>;

template<class T, T N>
  using make_integer_sequence = integer_sequence<T, 0, 1, ..., N-1>;
template<size_t N>
  using make_index_sequence = make_integer_sequence<size_t, N>;

template<class... T>
  using index_sequence_for = make_index_sequence<sizeof...(T)>;

template<class T, class U=T>
    T exchange(T& obj, U&& new_value);

// 20.2.7, in-place construction // C++17
struct in_place_t {
  explicit in_place_t() = default;
};
inline constexpr in_place_t in_place{};
template <class T>
  struct in_place_type_t {
    explicit in_place_type_t() = default;
  };
template <class T>
  inline constexpr in_place_type_t<T> in_place_type{};
template <size_t I>
  struct in_place_index_t {
    explicit in_place_index_t() = default;
  };
template <size_t I>
  inline constexpr in_place_index_t<I> in_place_index{};

}  // std

// EVERYTHING BELOW NEEDS TO BE COMMENTED IN & EVERYTHING ABOVE NEEDS TO BE COMMENTED OUT

#include <__config>
#include <__tuple>
#include <type_traits>
#include <initializer_list>
#include <cstddef>
#include <cstring>
#include <cstdint>
#include <__debug>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

namespace rel_ops
{

template<class _Tp>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator!=(const _Tp& __x, const _Tp& __y)
{
    return !(__x == __y);
}

template<class _Tp>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator> (const _Tp& __x, const _Tp& __y)
{
    return __y < __x;
}

template<class _Tp>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator<=(const _Tp& __x, const _Tp& __y)
{
    return !(__y < __x);
}

template<class _Tp>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator>=(const _Tp& __x, const _Tp& __y)
{
    return !(__x < __y);
}

}  // rel_ops

// swap_ranges


template <class _ForwardIterator1, class _ForwardIterator2>
inline _LIBCPP_INLINE_VISIBILITY
_ForwardIterator2
swap_ranges(_ForwardIterator1 __first1, _ForwardIterator1 __last1, _ForwardIterator2 __first2)
{
    for(; __first1 != __last1; ++__first1, (void) ++__first2)
        swap(*__first1, *__first2);
    return __first2;
}

// forward declared in <type_traits>
template<class _Tp, size_t _Np>
inline _LIBCPP_INLINE_VISIBILITY
typename enable_if<
    __is_swappable<_Tp>::value
>::type
swap(_Tp (&__a)[_Np], _Tp (&__b)[_Np]) _NOEXCEPT_(__is_nothrow_swappable<_Tp>::value)
{
    _VSTD::swap_ranges(__a, __a + _Np, __b);
}

template <class _Tp>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
#ifndef _LIBCPP_CXX03_LANG
typename conditional
<
    !is_nothrow_move_constructible<_Tp>::value && is_copy_constructible<_Tp>::value,
    const _Tp&,
    _Tp&&
>::type
#else  // _LIBCPP_CXX03_LANG
const _Tp&
#endif
move_if_noexcept(_Tp& __x) _NOEXCEPT
{
    return _VSTD::move(__x);
}

#if _LIBCPP_STD_VER > 14
template <class _Tp> constexpr add_const_t<_Tp>& as_const(_Tp& __t) noexcept { return __t; }
template <class _Tp>                        void as_const(const _Tp&&) = delete;
#endif

struct _LIBCPP_TEMPLATE_VIS piecewise_construct_t { };
#if defined(_LIBCPP_CXX03_LANG) || defined(_LIBCPP_BUILDING_LIBRARY)
extern const piecewise_construct_t piecewise_construct;// = piecewise_construct_t();
#else
/* _LIBCPP_INLINE_VAR  constexpr piecewise_construct_t piecewise_construct = piecewise_construct_t();
#endif

#if defined(_LIBCPP_DEPRECATED_ABI_DISABLE_PAIR_TRIVIAL_COPY_CTOR)
struct __non_trivially_copyable_base {
  _LIBCPP_CONSTEXPR _LIBCPP_INLINE_VISIBILITY
  __non_trivially_copyable_base() _NOEXCEPT {}
  _LIBCPP_CONSTEXPR_AFTER_CXX11 _LIBCPP_INLINE_VISIBILITY
  __non_trivially_copyable_base(__non_trivially_copyable_base const&) _NOEXCEPT {}
};
#endif

template <class _T1, class _T2>
struct _LIBCPP_TEMPLATE_VIS pair
#if defined(_LIBCPP_DEPRECATED_ABI_DISABLE_PAIR_TRIVIAL_COPY_CTOR)
: private __non_trivially_copyable_base
#endif
{
    typedef _T1 first_type;
    typedef _T2 second_type;

    _T1 first;
    _T2 second;

#if !defined(_LIBCPP_CXX03_LANG)
    pair(pair const&) = default;
    pair(pair&&) = default;
#else
  // Use the implicitly declared copy constructor in C++03
#endif

#ifdef _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    pair() : first(), second() {}

    _LIBCPP_INLINE_VISIBILITY
    pair(_T1 const& __t1, _T2 const& __t2) : first(__t1), second(__t2) {}

    template <class _U1, class _U2>
    _LIBCPP_INLINE_VISIBILITY
    pair(const pair<_U1, _U2>& __p) : first(__p.first), second(__p.second) {}

    _LIBCPP_INLINE_VISIBILITY
    pair& operator=(pair const& __p) {
        first = __p.first;
        second = __p.second;
        return *this;
    }
#else
    template <bool _Val>
    using _EnableB = typename enable_if<_Val, bool>::type;

    struct _CheckArgs {
      template <class _U1, class _U2>
      static constexpr bool __enable_default() {
          return is_default_constructible<_U1>::value
              && is_default_constructible<_U2>::value;
      }

      template <class _U1, class _U2>
      static constexpr bool __enable_explicit() {
          return is_constructible<first_type, _U1>::value
              && is_constructible<second_type, _U2>::value
              && (!is_convertible<_U1, first_type>::value
                  || !is_convertible<_U2, second_type>::value);
      }

      template <class _U1, class _U2>
      static constexpr bool __enable_implicit() {
          return is_constructible<first_type, _U1>::value
              && is_constructible<second_type, _U2>::value
              && is_convertible<_U1, first_type>::value
              && is_convertible<_U2, second_type>::value;
      }
    };

    template <bool _MaybeEnable>
    using _CheckArgsDep = typename conditional<
      _MaybeEnable, _CheckArgs, __check_tuple_constructor_fail>::type;

    struct _CheckTupleLikeConstructor {
        template <class _Tuple>
        static constexpr bool __enable_implicit() {
            return __tuple_convertible<_Tuple, pair>::value;
        }

        template <class _Tuple>
        static constexpr bool __enable_explicit() {
            return __tuple_constructible<_Tuple, pair>::value
               && !__tuple_convertible<_Tuple, pair>::value;
        }

        template <class _Tuple>
        static constexpr bool __enable_assign() {
            return __tuple_assignable<_Tuple, pair>::value;
        }
    };

    template <class _Tuple>
    using _CheckTLC = typename conditional<
        __tuple_like_with_size<_Tuple, 2>::value
            && !is_same<typename decay<_Tuple>::type, pair>::value,
        _CheckTupleLikeConstructor,
        __check_tuple_constructor_fail
    >::type;

    template<bool _Dummy = true, _EnableB<
            _CheckArgsDep<_Dummy>::template __enable_default<_T1, _T2>()
    > = false>
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
    pair() _NOEXCEPT_(is_nothrow_default_constructible<first_type>::value &&
                      is_nothrow_default_constructible<second_type>::value)
        : first(), second() {}

    template <bool _Dummy = true, _EnableB<
             _CheckArgsDep<_Dummy>::template __enable_explicit<_T1 const&, _T2 const&>()
    > = false>
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
    explicit pair(_T1 const& __t1, _T2 const& __t2)
        _NOEXCEPT_(is_nothrow_copy_constructible<first_type>::value &&
                   is_nothrow_copy_constructible<second_type>::value)
        : first(__t1), second(__t2) {}

    template<bool _Dummy = true, _EnableB<
            _CheckArgsDep<_Dummy>::template __enable_implicit<_T1 const&, _T2 const&>()
    > = false>
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
    pair(_T1 const& __t1, _T2 const& __t2)
        _NOEXCEPT_(is_nothrow_copy_constructible<first_type>::value &&
                   is_nothrow_copy_constructible<second_type>::value)
        : first(__t1), second(__t2) {}

    template<class _U1, class _U2, _EnableB<
             _CheckArgs::template __enable_explicit<_U1, _U2>()
    > = false>
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
    explicit pair(_U1&& __u1, _U2&& __u2)
        _NOEXCEPT_((is_nothrow_constructible<first_type, _U1>::value &&
                    is_nothrow_constructible<second_type, _U2>::value))
        : first(_VSTD::forward<_U1>(__u1)), second(_VSTD::forward<_U2>(__u2)) {}

    template<class _U1, class _U2, _EnableB<
            _CheckArgs::template __enable_implicit<_U1, _U2>()
    > = false>
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
    pair(_U1&& __u1, _U2&& __u2)
        _NOEXCEPT_((is_nothrow_constructible<first_type, _U1>::value &&
                    is_nothrow_constructible<second_type, _U2>::value))
        : first(_VSTD::forward<_U1>(__u1)), second(_VSTD::forward<_U2>(__u2)) {}

    template<class _U1, class _U2, _EnableB<
            _CheckArgs::template __enable_explicit<_U1 const&, _U2 const&>()
    > = false>
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
    explicit pair(pair<_U1, _U2> const& __p)
        _NOEXCEPT_((is_nothrow_constructible<first_type, _U1 const&>::value &&
                    is_nothrow_constructible<second_type, _U2 const&>::value))
        : first(__p.first), second(__p.second) {}

    template<class _U1, class _U2, _EnableB<
            _CheckArgs::template __enable_implicit<_U1 const&, _U2 const&>()
    > = false>
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
    pair(pair<_U1, _U2> const& __p)
        _NOEXCEPT_((is_nothrow_constructible<first_type, _U1 const&>::value &&
                    is_nothrow_constructible<second_type, _U2 const&>::value))
        : first(__p.first), second(__p.second) {}

    template<class _U1, class _U2, _EnableB<
            _CheckArgs::template __enable_explicit<_U1, _U2>()
    > = false>
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
    explicit pair(pair<_U1, _U2>&&__p)
        _NOEXCEPT_((is_nothrow_constructible<first_type, _U1&&>::value &&
                    is_nothrow_constructible<second_type, _U2&&>::value))
        : first(_VSTD::forward<_U1>(__p.first)), second(_VSTD::forward<_U2>(__p.second)) {}

    template<class _U1, class _U2, _EnableB<
            _CheckArgs::template __enable_implicit<_U1, _U2>()
    > = false>
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
    pair(pair<_U1, _U2>&& __p)
        _NOEXCEPT_((is_nothrow_constructible<first_type, _U1&&>::value &&
                    is_nothrow_constructible<second_type, _U2&&>::value))
        : first(_VSTD::forward<_U1>(__p.first)), second(_VSTD::forward<_U2>(__p.second)) {}

    template<class _Tuple, _EnableB<
            _CheckTLC<_Tuple>::template __enable_explicit<_Tuple>()
    > = false>
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
    explicit pair(_Tuple&& __p)
        : first(_VSTD::get<0>(_VSTD::forward<_Tuple>(__p))),
          second(_VSTD::get<1>(_VSTD::forward<_Tuple>(__p))) {}

    template<class _Tuple, _EnableB<
            _CheckTLC<_Tuple>::template __enable_implicit<_Tuple>()
    > = false>
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
    pair(_Tuple&& __p)
        : first(_VSTD::get<0>(_VSTD::forward<_Tuple>(__p))),
          second(_VSTD::get<1>(_VSTD::forward<_Tuple>(__p))) {}

    template <class... _Args1, class... _Args2>
    _LIBCPP_INLINE_VISIBILITY
    pair(piecewise_construct_t __pc,
         tuple<_Args1...> __first_args, tuple<_Args2...> __second_args)
        _NOEXCEPT_((is_nothrow_constructible<first_type, _Args1...>::value &&
                    is_nothrow_constructible<second_type, _Args2...>::value))
        : pair(__pc, __first_args, __second_args,
                typename __make_tuple_indices<sizeof...(_Args1)>::type(),
                typename __make_tuple_indices<sizeof...(_Args2) >::type()) {}

    _LIBCPP_INLINE_VISIBILITY
    pair& operator=(typename conditional<
                        is_copy_assignable<first_type>::value &&
                        is_copy_assignable<second_type>::value,
                    pair, __nat>::type const& __p)
        _NOEXCEPT_(is_nothrow_copy_assignable<first_type>::value &&
                   is_nothrow_copy_assignable<second_type>::value)
    {
        first = __p.first;
        second = __p.second;
        return *this;
    }

    _LIBCPP_INLINE_VISIBILITY
    pair& operator=(typename conditional<
                        is_move_assignable<first_type>::value &&
                        is_move_assignable<second_type>::value,
                    pair, __nat>::type&& __p)
        _NOEXCEPT_(is_nothrow_move_assignable<first_type>::value &&
                   is_nothrow_move_assignable<second_type>::value)
    {
        first = _VSTD::forward<first_type>(__p.first);
        second = _VSTD::forward<second_type>(__p.second);
        return *this;
    }

    template <class _Tuple, _EnableB<
            _CheckTLC<_Tuple>::template __enable_assign<_Tuple>()
     > = false>
    _LIBCPP_INLINE_VISIBILITY
    pair& operator=(_Tuple&& __p) {
        first = _VSTD::get<0>(_VSTD::forward<_Tuple>(__p));
        second = _VSTD::get<1>(_VSTD::forward<_Tuple>(__p));
        return *this;
    }
#endif

    _LIBCPP_INLINE_VISIBILITY
    void
    swap(pair& __p) _NOEXCEPT_(__is_nothrow_swappable<first_type>::value &&
                               __is_nothrow_swappable<second_type>::value)
    {
        using _VSTD::swap;
        swap(first,  __p.first);
        swap(second, __p.second);
    }
private:

#ifndef _LIBCPP_CXX03_LANG
    template <class... _Args1, class... _Args2, size_t... _I1, size_t... _I2>
        _LIBCPP_INLINE_VISIBILITY
        pair(piecewise_construct_t,
             tuple<_Args1...>& __first_args, tuple<_Args2...>& __second_args,
             __tuple_indices<_I1...>, __tuple_indices<_I2...>);
#endif
};

#ifndef _LIBCPP_HAS_NO_DEDUCTION_GUIDES
template<class _T1, class _T2>
pair(_T1, _T2) -> pair<_T1, _T2>;
#endif // _LIBCPP_HAS_NO_DEDUCTION_GUIDES

template <class _T1, class _T2>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
bool
operator==(const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
{
    return __x.first == __y.first && __x.second == __y.second;
}

template <class _T1, class _T2>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
bool
operator!=(const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
{
    return !(__x == __y);
}

template <class _T1, class _T2>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
bool
operator< (const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
{
    return __x.first < __y.first || (!(__y.first < __x.first) && __x.second < __y.second);
}

template <class _T1, class _T2>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
bool
operator> (const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
{
    return __y < __x;
}

template <class _T1, class _T2>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
bool
operator>=(const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
{
    return !(__x < __y);
}

template <class _T1, class _T2>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
bool
operator<=(const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
{
    return !(__y < __x);
}

template <class _T1, class _T2>
inline _LIBCPP_INLINE_VISIBILITY
typename enable_if
<
    __is_swappable<_T1>::value &&
    __is_swappable<_T2>::value,
    void
>::type
swap(pair<_T1, _T2>& __x, pair<_T1, _T2>& __y)
                     _NOEXCEPT_((__is_nothrow_swappable<_T1>::value &&
                                 __is_nothrow_swappable<_T2>::value))
{
    __x.swap(__y);
}

#ifndef _LIBCPP_CXX03_LANG

template <class _Tp>
struct __make_pair_return_impl
{
    typedef _Tp type;
};

template <class _Tp>
struct __make_pair_return_impl<reference_wrapper<_Tp>>
{
    typedef _Tp& type;
};

template <class _Tp>
struct __make_pair_return
{
    typedef typename __make_pair_return_impl<typename decay<_Tp>::type>::type type;
};

template <class _T1, class _T2>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX11
pair<typename __make_pair_return<_T1>::type, typename __make_pair_return<_T2>::type>
make_pair(_T1&& __t1, _T2&& __t2)
{
    return pair<typename __make_pair_return<_T1>::type, typename __make_pair_return<_T2>::type>
               (_VSTD::forward<_T1>(__t1), _VSTD::forward<_T2>(__t2));
}

#else  // _LIBCPP_CXX03_LANG

template <class _T1, class _T2>
inline _LIBCPP_INLINE_VISIBILITY
pair<_T1,_T2>
make_pair(_T1 __x, _T2 __y)
{
    return pair<_T1, _T2>(__x, __y);
}

#endif  // _LIBCPP_CXX03_LANG
*/