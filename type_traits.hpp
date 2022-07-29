/*========================================
============ ft:: TYPE_TRAITS ============
==========================================

=> ENABLE IF:
	template <bool Cond, class T = void> struct enable_if{}; 
	-> Cond = a compile time constant of type bool
	-> T = a type (only definde if Cond == true)

=> IS INTEGRAL:
	template <class T> struct is_integral;

	Trait class that identifies whether T is an integral type.
	Inherits from integral_constant. Is either true_type or false_type, depending if T is an integral type.

=> FUNDAMENTAL INTEGRAL TYPES:
	bool
	char
	char16_t
	char32_t
	wchar_t
	signed char
	short int
	int
	long int
	long long int
	unsigned char
	unsigned short int
	unsigned int
	unsigned long int
	unsigned long long int
*/

#ifndef FT_TYPE_TRAITS_HPP
#define FT_TYPE_TRAITS_HPP

#include <type_traits>

namespace ft{

	template <bool B, class Tp = void> struct enable_if {};								            //type_traits line 435
	template <class Tp> struct enable_if<true, Tp> {typedef Tp type;};				        //type_traits line 436
	
	// template <class Tp, Tp v>													                            //type_traits line 515
	// struct integral_constant{													                            //type_traits line 517
	// 	static const Tp value = v;												                            //type_traits line 518
	// 	typedef Tp value_type;														                            //type_traits line 519
	// 	typedef integral_constant type;										                            //type_traits line 520
	// };

	// template <bool b>																                              //type_traits line 448
	// using bool_constant = integral_constant<bool, b>;								              //type_traits line 449
	
	template <bool v = true>														                            	//type_traits line 513
	struct bool_constant{
		static const bool 		  value = v;
		typedef bool 			      value_type;
		typedef bool_constant	  type;
	};

	typedef bool_constant<true> true_type;												                    //type_traits line 540
	typedef bool_constant<false> false_type;											                    //type_traits line 541

	template <class T> struct ft_is_integral 			    	    : public false_type {};		//type_traits line 701
	
	template <> struct ft_is_integral <bool> 				        : public true_type {};		//type_traits line 702
	template <> struct ft_is_integral <char> 			          : public true_type {};		//type_traits line 703
	template <> struct ft_is_integral <signed char>		      : public true_type {};		//type_traits line 704
	template <> struct ft_is_integral <unsigned char>	      : public true_type {};		//type_traits line 705	
	template <> struct ft_is_integral <wchar_t>			        : public true_type {};		//type_traits line 706
	
	// template <> struct ft_is_integral <char8_t> 			    : public true_type {};		//type_traits line 745
	// template <> struct ft_is_integral <char16_t> 		    : public true_type {};		//type_traits line 708
	// template <> struct ft_is_integral <char32_t> 		    : public true_type {};		//type_traits line 709

	template <> struct ft_is_integral <short> 			        : public true_type {};		//type_traits line 711
	template <> struct ft_is_integral <unsigned short> 	    : public true_type {};		//type_traits line 712
	template <> struct ft_is_integral <int> 			        	: public true_type {};		//type_traits line 713
	template <> struct ft_is_integral <unsigned int> 	    	: public true_type {};		//type_traits line 714
	template <> struct ft_is_integral <long> 			        	: public true_type {};		//type_traits line 715
	template <> struct ft_is_integral <unsigned long> 	  	: public true_type {};		//type_traits line 716
	template <> struct ft_is_integral <long long> 		     	: public true_type {};		//type_traits line 717
	template <> struct ft_is_integral <unsigned long long> 	: public true_type {};		//type_traits line 718
	
	// template <> struct ft_is_integral <__int128_t> 	  	: public true_type {};		//type_traits line 720
	// template <> struct ft_is_integral <__uint128_t> 	  	: public true_type {};		//type_traits line 721

	template< typename T>																//type_traits line 724
	class is_integral : public ft_is_integral<T> {};									//type_traits line 725
}

#endif

// ORIGINAL FOR REFFERENCE AS ONE CANNOT TRUST NO ONE

// -*- C++ -*-
//===------------------------ type_traits ---------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// #ifndef _LIBCPP_TYPE_TRAITS			this needs to commented in
// #define _LIBCPP_TYPE_TRAITS			this needs to commented in

/*
    type_traits synopsis

namespace std
{

    // helper class:
    template <class T, T v> struct integral_constant;
    typedef integral_constant<bool, true>  true_type;   // C++11
    typedef integral_constant<bool, false> false_type;  // C++11

    template <bool B>                                   // C++14
    using bool_constant = integral_constant<bool, B>;   // C++14
    typedef bool_constant<true> true_type;              // C++14
    typedef bool_constant<false> false_type;            // C++14

    // helper traits
    template <bool, class T = void> struct enable_if;
    template <bool, class T, class F> struct conditional;

    // Primary classification traits:
    template <class T> struct is_void;
    template <class T> struct is_null_pointer;  // C++14
    template <class T> struct is_integral;
    template <class T> struct is_floating_point;
    template <class T> struct is_array;
    template <class T> struct is_pointer;
    template <class T> struct is_lvalue_reference;
    template <class T> struct is_rvalue_reference;
    template <class T> struct is_member_object_pointer;
    template <class T> struct is_member_function_pointer;
    template <class T> struct is_enum;
    template <class T> struct is_union;
    template <class T> struct is_class;
    template <class T> struct is_function;

    // Secondary classification traits:
    template <class T> struct is_reference;
    template <class T> struct is_arithmetic;
    template <class T> struct is_fundamental;
    template <class T> struct is_member_pointer;
    template <class T> struct is_scalar;
    template <class T> struct is_object;
    template <class T> struct is_compound;

    // Const-volatile properties and transformations:
    template <class T> struct is_const;
    template <class T> struct is_volatile;
    template <class T> struct remove_const;
    template <class T> struct remove_volatile;
    template <class T> struct remove_cv;
    template <class T> struct add_const;
    template <class T> struct add_volatile;
    template <class T> struct add_cv;

    // Reference transformations:
    template <class T> struct remove_reference;
    template <class T> struct add_lvalue_reference;
    template <class T> struct add_rvalue_reference;

    // Pointer transformations:
    template <class T> struct remove_pointer;
    template <class T> struct add_pointer;

    // Integral properties:
    template <class T> struct is_signed;
    template <class T> struct is_unsigned;
    template <class T> struct make_signed;
    template <class T> struct make_unsigned;

    // Array properties and transformations:
    template <class T> struct rank;
    template <class T, unsigned I = 0> struct extent;
    template <class T> struct remove_extent;
    template <class T> struct remove_all_extents;

    // Member introspection:
    template <class T> struct is_pod;
    template <class T> struct is_trivial;
    template <class T> struct is_trivially_copyable;
    template <class T> struct is_standard_layout;
    template <class T> struct is_literal_type;
    template <class T> struct is_empty;
    template <class T> struct is_polymorphic;
    template <class T> struct is_abstract;
    template <class T> struct is_final; // C++14
    template <class T> struct is_aggregate; // C++17

    template <class T, class... Args> struct is_constructible;
    template <class T>                struct is_default_constructible;
    template <class T>                struct is_copy_constructible;
    template <class T>                struct is_move_constructible;
    template <class T, class U>       struct is_assignable;
    template <class T>                struct is_copy_assignable;
    template <class T>                struct is_move_assignable;
    template <class T, class U>       struct is_swappable_with;       // C++17
    template <class T>                struct is_swappable;            // C++17
    template <class T>                struct is_destructible;

    template <class T, class... Args> struct is_trivially_constructible;
    template <class T>                struct is_trivially_default_constructible;
    template <class T>                struct is_trivially_copy_constructible;
    template <class T>                struct is_trivially_move_constructible;
    template <class T, class U>       struct is_trivially_assignable;
    template <class T>                struct is_trivially_copy_assignable;
    template <class T>                struct is_trivially_move_assignable;
    template <class T>                struct is_trivially_destructible;

    template <class T, class... Args> struct is_nothrow_constructible;
    template <class T>                struct is_nothrow_default_constructible;
    template <class T>                struct is_nothrow_copy_constructible;
    template <class T>                struct is_nothrow_move_constructible;
    template <class T, class U>       struct is_nothrow_assignable;
    template <class T>                struct is_nothrow_copy_assignable;
    template <class T>                struct is_nothrow_move_assignable;
    template <class T, class U>       struct is_nothrow_swappable_with; // C++17
    template <class T>                struct is_nothrow_swappable;      // C++17
    template <class T>                struct is_nothrow_destructible;

    template <class T> struct has_virtual_destructor;

    template<class T> struct has_unique_object_representations;         // C++17

    // Relationships between types:
    template <class T, class U> struct is_same;
    template <class Base, class Derived> struct is_base_of;
    template <class From, class To> struct is_convertible;

    template <class Fn, class... ArgTypes> struct is_invocable;
    template <class R, class Fn, class... ArgTypes> struct is_invocable_r;

    template <class Fn, class... ArgTypes> struct is_nothrow_invocable;
    template <class R, class Fn, class... ArgTypes> struct is_nothrow_invocable_r;

    // Alignment properties and transformations:
    template <class T> struct alignment_of;
    template <size_t Len, size_t Align = most_stringent_alignment_requirement>
        struct aligned_storage;
    template <size_t Len, class... Types> struct aligned_union;
    template <class T> struct remove_cvref; // C++20

    template <class T> struct decay;
    template <class... T> struct common_type;
    template <class T> struct underlying_type;
    template <class> class result_of; // undefined
    template <class Fn, class... ArgTypes> class result_of<Fn(ArgTypes...)>;
    template <class Fn, class... ArgTypes> struct invoke_result;  // C++17

    // const-volatile modifications:
    template <class T>
      using remove_const_t    = typename remove_const<T>::type;  // C++14
    template <class T>
      using remove_volatile_t = typename remove_volatile<T>::type;  // C++14
    template <class T>
      using remove_cv_t       = typename remove_cv<T>::type;  // C++14
    template <class T>
      using add_const_t       = typename add_const<T>::type;  // C++14
    template <class T>
      using add_volatile_t    = typename add_volatile<T>::type;  // C++14
    template <class T>
      using add_cv_t          = typename add_cv<T>::type;  // C++14

    // reference modifications:
    template <class T>
      using remove_reference_t     = typename remove_reference<T>::type;  // C++14
    template <class T>
      using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;  // C++14
    template <class T>
      using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;  // C++14

    // sign modifications:
    template <class T>
      using make_signed_t   = typename make_signed<T>::type;  // C++14
    template <class T>
      using make_unsigned_t = typename make_unsigned<T>::type;  // C++14

    // array modifications:
    template <class T>
      using remove_extent_t      = typename remove_extent<T>::type;  // C++14
    template <class T>
      using remove_all_extents_t = typename remove_all_extents<T>::type;  // C++14

    // pointer modifications:
    template <class T>
      using remove_pointer_t = typename remove_pointer<T>::type;  // C++14
    template <class T>
      using add_pointer_t    = typename add_pointer<T>::type;  // C++14

    // other transformations:
    template <size_t Len, std::size_t Align=default-alignment>
      using aligned_storage_t = typename aligned_storage<Len,Align>::type;  // C++14
    template <std::size_t Len, class... Types>
      using aligned_union_t   = typename aligned_union<Len,Types...>::type;  // C++14
    template <class T>
      using remove_cvref_t    = typename remove_cvref<T>::type;  // C++20
    template <class T>
      using decay_t           = typename decay<T>::type;  // C++14
    template <bool b, class T=void>
      using enable_if_t       = typename enable_if<b,T>::type;  // C++14
    template <bool b, class T, class F>
      using conditional_t     = typename conditional<b,T,F>::type;  // C++14
    template <class... T>
      using common_type_t     = typename common_type<T...>::type;  // C++14
    template <class T>
      using underlying_type_t = typename underlying_type<T>::type;  // C++14
    template <class T>
      using result_of_t       = typename result_of<T>::type;  // C++14
    template <class Fn, class... ArgTypes>
      using invoke_result_t   = typename invoke_result<Fn, ArgTypes...>::type;  // C++17

    template <class...>
      using void_t = void;   // C++17

      // See C++14 20.10.4.1, primary type categories
      template <class T> inline constexpr bool is_void_v
        = is_void<T>::value;                                             // C++17
      template <class T> inline constexpr bool is_null_pointer_v
        = is_null_pointer<T>::value;                                     // C++17
      template <class T> inline constexpr bool is_integral_v
        = is_integral<T>::value;                                         // C++17
      template <class T> inline constexpr bool is_floating_point_v
        = is_floating_point<T>::value;                                   // C++17
      template <class T> inline constexpr bool is_array_v
        = is_array<T>::value;                                            // C++17
      template <class T> inline constexpr bool is_pointer_v
        = is_pointer<T>::value;                                          // C++17
      template <class T> inline constexpr bool is_lvalue_reference_v
        = is_lvalue_reference<T>::value;                                 // C++17
      template <class T> inline constexpr bool is_rvalue_reference_v
        = is_rvalue_reference<T>::value;                                 // C++17
      template <class T> inline constexpr bool is_member_object_pointer_v
        = is_member_object_pointer<T>::value;                            // C++17
      template <class T> inline constexpr bool is_member_function_pointer_v
        = is_member_function_pointer<T>::value;                          // C++17
      template <class T> inline constexpr bool is_enum_v
        = is_enum<T>::value;                                             // C++17
      template <class T> inline constexpr bool is_union_v
        = is_union<T>::value;                                            // C++17
      template <class T> inline constexpr bool is_class_v
        = is_class<T>::value;                                            // C++17
      template <class T> inline constexpr bool is_function_v
        = is_function<T>::value;                                         // C++17

      // See C++14 20.10.4.2, composite type categories
      template <class T> inline constexpr bool is_reference_v
        = is_reference<T>::value;                                        // C++17
      template <class T> inline constexpr bool is_arithmetic_v
        = is_arithmetic<T>::value;                                       // C++17
      template <class T> inline constexpr bool is_fundamental_v
        = is_fundamental<T>::value;                                      // C++17
      template <class T> inline constexpr bool is_object_v
        = is_object<T>::value;                                           // C++17
      template <class T> inline constexpr bool is_scalar_v
        = is_scalar<T>::value;                                           // C++17
      template <class T> inline constexpr bool is_compound_v
        = is_compound<T>::value;                                         // C++17
      template <class T> inline constexpr bool is_member_pointer_v
        = is_member_pointer<T>::value;                                   // C++17

      // See C++14 20.10.4.3, type properties
      template <class T> inline constexpr bool is_const_v
        = is_const<T>::value;                                            // C++17
      template <class T> inline constexpr bool is_volatile_v
        = is_volatile<T>::value;                                         // C++17
      template <class T> inline constexpr bool is_trivial_v
        = is_trivial<T>::value;                                          // C++17
      template <class T> inline constexpr bool is_trivially_copyable_v
        = is_trivially_copyable<T>::value;                               // C++17
      template <class T> inline constexpr bool is_standard_layout_v
        = is_standard_layout<T>::value;                                  // C++17
      template <class T> inline constexpr bool is_pod_v
        = is_pod<T>::value;                                              // C++17
      template <class T> inline constexpr bool is_literal_type_v
        = is_literal_type<T>::value;                                     // C++17
      template <class T> inline constexpr bool is_empty_v
        = is_empty<T>::value;                                            // C++17
      template <class T> inline constexpr bool is_polymorphic_v
        = is_polymorphic<T>::value;                                      // C++17
      template <class T> inline constexpr bool is_abstract_v
        = is_abstract<T>::value;                                         // C++17
      template <class T> inline constexpr bool is_final_v
        = is_final<T>::value;                                            // C++17
      template <class T> inline constexpr bool is_aggregate_v
        = is_aggregate<T>::value;                                        // C++17
      template <class T> inline constexpr bool is_signed_v
        = is_signed<T>::value;                                           // C++17
      template <class T> inline constexpr bool is_unsigned_v
        = is_unsigned<T>::value;                                         // C++17
      template <class T, class... Args> inline constexpr bool is_constructible_v
        = is_constructible<T, Args...>::value;                           // C++17
      template <class T> inline constexpr bool is_default_constructible_v
        = is_default_constructible<T>::value;                            // C++17
      template <class T> inline constexpr bool is_copy_constructible_v
        = is_copy_constructible<T>::value;                               // C++17
      template <class T> inline constexpr bool is_move_constructible_v
        = is_move_constructible<T>::value;                               // C++17
      template <class T, class U> inline constexpr bool is_assignable_v
        = is_assignable<T, U>::value;                                    // C++17
      template <class T> inline constexpr bool is_copy_assignable_v
        = is_copy_assignable<T>::value;                                  // C++17
      template <class T> inline constexpr bool is_move_assignable_v
        = is_move_assignable<T>::value;                                  // C++17
      template <class T, class U> inline constexpr bool is_swappable_with_v
        = is_swappable_with<T, U>::value;                                // C++17
      template <class T> inline constexpr bool is_swappable_v
        = is_swappable<T>::value;                                        // C++17
      template <class T> inline constexpr bool is_destructible_v
        = is_destructible<T>::value;                                     // C++17
      template <class T, class... Args> inline constexpr bool is_trivially_constructible_v
        = is_trivially_constructible<T, Args...>::value;                 // C++17
      template <class T> inline constexpr bool is_trivially_default_constructible_v
        = is_trivially_default_constructible<T>::value;                  // C++17
      template <class T> inline constexpr bool is_trivially_copy_constructible_v
        = is_trivially_copy_constructible<T>::value;                     // C++17
      template <class T> inline constexpr bool is_trivially_move_constructible_v
        = is_trivially_move_constructible<T>::value;                     // C++17
      template <class T, class U> inline constexpr bool is_trivially_assignable_v
        = is_trivially_assignable<T, U>::value;                          // C++17
      template <class T> inline constexpr bool is_trivially_copy_assignable_v
        = is_trivially_copy_assignable<T>::value;                        // C++17
      template <class T> inline constexpr bool is_trivially_move_assignable_v
        = is_trivially_move_assignable<T>::value;                        // C++17
      template <class T> inline constexpr bool is_trivially_destructible_v
        = is_trivially_destructible<T>::value;                           // C++17
      template <class T, class... Args> inline constexpr bool is_nothrow_constructible_v
        = is_nothrow_constructible<T, Args...>::value;                   // C++17
      template <class T> inline constexpr bool is_nothrow_default_constructible_v
        = is_nothrow_default_constructible<T>::value;                    // C++17
      template <class T> inline constexpr bool is_nothrow_copy_constructible_v
        = is_nothrow_copy_constructible<T>::value;                       // C++17
      template <class T> inline constexpr bool is_nothrow_move_constructible_v
        = is_nothrow_move_constructible<T>::value;                       // C++17
      template <class T, class U> inline constexpr bool is_nothrow_assignable_v
        = is_nothrow_assignable<T, U>::value;                            // C++17
      template <class T> inline constexpr bool is_nothrow_copy_assignable_v
        = is_nothrow_copy_assignable<T>::value;                          // C++17
      template <class T> inline constexpr bool is_nothrow_move_assignable_v
        = is_nothrow_move_assignable<T>::value;                          // C++17
      template <class T, class U> inline constexpr bool is_nothrow_swappable_with_v
        = is_nothrow_swappable_with<T, U>::value;                       // C++17
      template <class T> inline constexpr bool is_nothrow_swappable_v
        = is_nothrow_swappable<T>::value;                               // C++17
      template <class T> inline constexpr bool is_nothrow_destructible_v
        = is_nothrow_destructible<T>::value;                             // C++17
      template <class T> inline constexpr bool has_virtual_destructor_v
        = has_virtual_destructor<T>::value;                              // C++17
      template<class T> inline constexpr bool has_unique_object_representations_v // C++17
        = has_unique_object_representations<T>::value;

      // See C++14 20.10.5, type property queries
      template <class T> inline constexpr size_t alignment_of_v
        = alignment_of<T>::value;                                        // C++17
      template <class T> inline constexpr size_t rank_v
        = rank<T>::value;                                                // C++17
      template <class T, unsigned I = 0> inline constexpr size_t extent_v
        = extent<T, I>::value;                                           // C++17

      // See C++14 20.10.6, type relations
      template <class T, class U> inline constexpr bool is_same_v
        = is_same<T, U>::value;                                          // C++17
      template <class Base, class Derived> inline constexpr bool is_base_of_v
        = is_base_of<Base, Derived>::value;                              // C++17
      template <class From, class To> inline constexpr bool is_convertible_v
        = is_convertible<From, To>::value;                               // C++17
      template <class Fn, class... ArgTypes> inline constexpr bool is_invocable_v
        = is_invocable<Fn, ArgTypes...>::value;                          // C++17
      template <class R, class Fn, class... ArgTypes> inline constexpr bool is_invocable_r_v
        = is_invocable_r<R, Fn, ArgTypes...>::value;                     // C++17
      template <class Fn, class... ArgTypes> inline constexpr bool is_nothrow_invocable_v
        = is_nothrow_invocable<Fn, ArgTypes...>::value;                  // C++17
      template <class R, class Fn, class... ArgTypes> inline constexpr bool is_nothrow_invocable_r_v
        = is_nothrow_invocable_r<R, Fn, ArgTypes...>::value;             // C++17

      // [meta.logical], logical operator traits:
      template<class... B> struct conjunction;                           // C++17
      template<class... B>
        inline constexpr bool conjunction_v = conjunction<B...>::value;  // C++17
      template<class... B> struct disjunction;                           // C++17
      template<class... B>
        inline constexpr bool disjunction_v = disjunction<B...>::value;  // C++17
      template<class B> struct negation;                                 // C++17
      template<class B>
        inline constexpr bool negation_v = negation<B>::value;           // C++17

}

NORMALLY EVERYTHING ABOVE IS COMMENTED OUT & EVERYTHIGN BELOW IS COMMENTED IN

#include <__config>
#include <cstddef>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

template <class _T1, class _T2> struct _LIBCPP_TEMPLATE_VIS pair;
template <class _Tp> class _LIBCPP_TEMPLATE_VIS reference_wrapper;
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS hash;

template <class>
struct __void_t { typedef void type; };

template <class _Tp>
struct __identity { typedef _Tp type; };

template <class _Tp, bool>
struct _LIBCPP_TEMPLATE_VIS __dependent_type : public _Tp {};

template <bool _Bp, class _If, class _Then>
    struct _LIBCPP_TEMPLATE_VIS conditional {typedef _If type;};
template <class _If, class _Then>
    struct _LIBCPP_TEMPLATE_VIS conditional<false, _If, _Then> {typedef _Then type;};

#if _LIBCPP_STD_VER > 11
template <bool _Bp, class _If, class _Then> using conditional_t = typename conditional<_Bp, _If, _Then>::type;
#endif

template <bool, class _Tp> struct _LIBCPP_TEMPLATE_VIS __lazy_enable_if {};
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS __lazy_enable_if<true, _Tp> {typedef typename _Tp::type type;};

template <bool, class _Tp = void> struct _LIBCPP_TEMPLATE_VIS enable_if {};
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS enable_if<true, _Tp> {typedef _Tp type;};

#if _LIBCPP_STD_VER > 11
template <bool _Bp, class _Tp = void> using enable_if_t = typename enable_if<_Bp, _Tp>::type;
#endif

// addressof
#ifndef _LIBCPP_HAS_NO_BUILTIN_ADDRESSOF

template <class _Tp>
inline _LIBCPP_CONSTEXPR_AFTER_CXX14
_LIBCPP_NO_CFI _LIBCPP_INLINE_VISIBILITY
_Tp*
addressof(_Tp& __x) _NOEXCEPT
{
    return __builtin_addressof(__x);
}

#else

template <class _Tp>
inline _LIBCPP_NO_CFI _LIBCPP_INLINE_VISIBILITY
_Tp*
addressof(_Tp& __x) _NOEXCEPT
{
  return reinterpret_cast<_Tp *>(
      const_cast<char *>(&reinterpret_cast<const volatile char &>(__x)));
}

#endif // _LIBCPP_HAS_NO_BUILTIN_ADDRESSOF

#if defined(_LIBCPP_HAS_OBJC_ARC) && !defined(_LIBCPP_PREDEFINED_OBJC_ARC_ADDRESSOF)
// Objective-C++ Automatic Reference Counting uses qualified pointers
// that require special addressof() signatures. When
// _LIBCPP_PREDEFINED_OBJC_ARC_ADDRESSOF is defined, the compiler
// itself is providing these definitions. Otherwise, we provide them.
template <class _Tp>
inline _LIBCPP_INLINE_VISIBILITY
__strong _Tp*
addressof(__strong _Tp& __x) _NOEXCEPT
{
  return &__x;
}

#ifdef _LIBCPP_HAS_OBJC_ARC_WEAK
template <class _Tp>
inline _LIBCPP_INLINE_VISIBILITY
__weak _Tp*
addressof(__weak _Tp& __x) _NOEXCEPT
{
  return &__x;
}
#endif

template <class _Tp>
inline _LIBCPP_INLINE_VISIBILITY
__autoreleasing _Tp*
addressof(__autoreleasing _Tp& __x) _NOEXCEPT
{
  return &__x;
}

template <class _Tp>
inline _LIBCPP_INLINE_VISIBILITY
__unsafe_unretained _Tp*
addressof(__unsafe_unretained _Tp& __x) _NOEXCEPT
{
  return &__x;
}
#endif

#if !defined(_LIBCPP_CXX03_LANG)
template <class _Tp> _Tp* addressof(const _Tp&&) noexcept = delete;
#endif

struct __two {char __lx[2];};

// helper class:

template <class _Tp, _Tp __v>
struct _LIBCPP_TEMPLATE_VIS integral_constant
{
    static _LIBCPP_CONSTEXPR const _Tp      value = __v;
    typedef _Tp               value_type;
    typedef integral_constant type;
    _LIBCPP_INLINE_VISIBILITY
        _LIBCPP_CONSTEXPR operator value_type() const _NOEXCEPT {return value;}
#if _LIBCPP_STD_VER > 11
    _LIBCPP_INLINE_VISIBILITY
         constexpr value_type operator ()() const _NOEXCEPT {return value;}
#endif
};

template <class _Tp, _Tp __v>
_LIBCPP_CONSTEXPR const _Tp integral_constant<_Tp, __v>::value;

#if _LIBCPP_STD_VER > 14
template <bool __b>
using bool_constant = integral_constant<bool, __b>;
#define _LIBCPP_BOOL_CONSTANT(__b) bool_constant<(__b)>
#else
#define _LIBCPP_BOOL_CONSTANT(__b) integral_constant<bool,(__b)>
#endif

typedef _LIBCPP_BOOL_CONSTANT(true)  true_type;
typedef _LIBCPP_BOOL_CONSTANT(false) false_type;

#if !defined(_LIBCPP_CXX03_LANG)

// __lazy_and

template <bool _Last, class ..._Preds>
struct __lazy_and_impl;

template <class ..._Preds>
struct __lazy_and_impl<false, _Preds...> : false_type {};

template <>
struct __lazy_and_impl<true> : true_type {};

template <class _Pred>
struct __lazy_and_impl<true, _Pred> : integral_constant<bool, _Pred::type::value> {};

template <class _Hp, class ..._Tp>
struct __lazy_and_impl<true, _Hp, _Tp...> : __lazy_and_impl<_Hp::type::value, _Tp...> {};

template <class _P1, class ..._Pr>
struct __lazy_and : __lazy_and_impl<_P1::type::value, _Pr...> {};

// __lazy_or

template <bool _List, class ..._Preds>
struct __lazy_or_impl;

template <class ..._Preds>
struct __lazy_or_impl<true, _Preds...> : true_type {};

template <>
struct __lazy_or_impl<false> : false_type {};

template <class _Hp, class ..._Tp>
struct __lazy_or_impl<false, _Hp, _Tp...>
        : __lazy_or_impl<_Hp::type::value, _Tp...> {};

template <class _P1, class ..._Pr>
struct __lazy_or : __lazy_or_impl<_P1::type::value, _Pr...> {};

// __lazy_not

template <class _Pred>
struct __lazy_not : integral_constant<bool, !_Pred::type::value> {};

// __and_
template<class...> struct __and_;
template<> struct __and_<> : true_type {};

template<class _B0> struct __and_<_B0> : _B0 {};

template<class _B0, class _B1>
struct __and_<_B0, _B1> : conditional<_B0::value, _B1, _B0>::type {};

template<class _B0, class _B1, class _B2, class... _Bn>
struct __and_<_B0, _B1, _B2, _Bn...>
        : conditional<_B0::value, __and_<_B1, _B2, _Bn...>, _B0>::type {};

// __or_
template<class...> struct __or_;
template<> struct __or_<> : false_type {};

template<class _B0> struct __or_<_B0> : _B0 {};

template<class _B0, class _B1>
struct __or_<_B0, _B1> : conditional<_B0::value, _B0, _B1>::type {};

template<class _B0, class _B1, class _B2, class... _Bn>
struct __or_<_B0, _B1, _B2, _Bn...>
        : conditional<_B0::value, _B0, __or_<_B1, _B2, _Bn...> >::type {};

// __not_
template<class _Tp>
struct __not_ : conditional<_Tp::value, false_type, true_type>::type {};

#endif // !defined(_LIBCPP_CXX03_LANG)

// is_const

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_const            : public false_type {};
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_const<_Tp const> : public true_type {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_const_v
    = is_const<_Tp>::value;
#endif

// is_volatile

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_volatile               : public false_type {};
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_volatile<_Tp volatile> : public true_type {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_volatile_v
    = is_volatile<_Tp>::value;
#endif

// remove_const

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_const            {typedef _Tp type;};
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_const<const _Tp> {typedef _Tp type;};
#if _LIBCPP_STD_VER > 11
template <class _Tp> using remove_const_t = typename remove_const<_Tp>::type;
#endif

// remove_volatile

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_volatile               {typedef _Tp type;};
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_volatile<volatile _Tp> {typedef _Tp type;};
#if _LIBCPP_STD_VER > 11
template <class _Tp> using remove_volatile_t = typename remove_volatile<_Tp>::type;
#endif

// remove_cv

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_cv
{typedef typename remove_volatile<typename remove_const<_Tp>::type>::type type;};
#if _LIBCPP_STD_VER > 11
template <class _Tp> using remove_cv_t = typename remove_cv<_Tp>::type;
#endif

// is_void

template <class _Tp> struct __libcpp_is_void       : public false_type {};
template <>          struct __libcpp_is_void<void> : public true_type {};

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_void
    : public __libcpp_is_void<typename remove_cv<_Tp>::type> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_void_v
    = is_void<_Tp>::value;
#endif

// __is_nullptr_t

template <class _Tp> struct __is_nullptr_t_impl       : public false_type {};
template <>          struct __is_nullptr_t_impl<nullptr_t> : public true_type {};

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS __is_nullptr_t
    : public __is_nullptr_t_impl<typename remove_cv<_Tp>::type> {};

#if _LIBCPP_STD_VER > 11
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_null_pointer
    : public __is_nullptr_t_impl<typename remove_cv<_Tp>::type> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_null_pointer_v
    = is_null_pointer<_Tp>::value;
#endif
#endif

// is_integral

template <class _Tp> struct __libcpp_is_integral                     : public false_type {};
template <>          struct __libcpp_is_integral<bool>               : public true_type {};
template <>          struct __libcpp_is_integral<char>               : public true_type {};
template <>          struct __libcpp_is_integral<signed char>        : public true_type {};
template <>          struct __libcpp_is_integral<unsigned char>      : public true_type {};
template <>          struct __libcpp_is_integral<wchar_t>            : public true_type {};
#ifndef _LIBCPP_HAS_NO_UNICODE_CHARS
template <>          struct __libcpp_is_integral<char16_t>           : public true_type {};
template <>          struct __libcpp_is_integral<char32_t>           : public true_type {};
#endif  // _LIBCPP_HAS_NO_UNICODE_CHARS
template <>          struct __libcpp_is_integral<short>              : public true_type {};
template <>          struct __libcpp_is_integral<unsigned short>     : public true_type {};
template <>          struct __libcpp_is_integral<int>                : public true_type {};
template <>          struct __libcpp_is_integral<unsigned int>       : public true_type {};
template <>          struct __libcpp_is_integral<long>               : public true_type {};
template <>          struct __libcpp_is_integral<unsigned long>      : public true_type {};
template <>          struct __libcpp_is_integral<long long>          : public true_type {};
template <>          struct __libcpp_is_integral<unsigned long long> : public true_type {};
#ifndef _LIBCPP_HAS_NO_INT128
template <>          struct __libcpp_is_integral<__int128_t>         : public true_type {};
template <>          struct __libcpp_is_integral<__uint128_t>        : public true_type {};
#endif

template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_integral
    : public __libcpp_is_integral<typename remove_cv<_Tp>::type> {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_integral_v
    = is_integral<_Tp>::value;
#endif

*/