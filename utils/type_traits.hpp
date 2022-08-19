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

#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft {
template <bool, typename _Tp = void>
struct enable_if {};

template <typename _Tp>
struct enable_if<true, _Tp> {
    typedef _Tp type;
};

template <class T, T v>
struct integral_constant {
    typedef T value_type;
    typedef integral_constant<T, v> type;

    static const T value = v;
    operator T() { return (v); }
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

template <class T> struct is_integral 				: public false_type {};
template <> struct is_integral<bool> 				: public true_type {};
template <> struct is_integral<char> 				: public true_type {};
template <> struct is_integral<signed char> 		: public true_type {};
template <> struct is_integral<unsigned char> 		: public true_type {};
template <> struct is_integral<wchar_t> 			: public true_type {};
template <> struct is_integral<char16_t> 			: public true_type {};
template <> struct is_integral<char32_t> 			: public true_type {};
template <> struct is_integral<short> 				: public true_type {};
template <> struct is_integral<unsigned short> 		: public true_type {};
template <> struct is_integral<int> 				: public true_type {};
template <> struct is_integral<unsigned int> 		: public true_type {};
template <> struct is_integral<long>				: public true_type {};
template <> struct is_integral<unsigned long> 		: public true_type {};
template <> struct is_integral<long long> 			: public true_type {};
template <> struct is_integral<unsigned long long> 	: public true_type {};

}  // namespace ft

#endif