#ifndef __TYPE_TRAITS_HPP__
#define __TYPE_TRAITS_HPP__

#include <cstdint>

namespace ft
{

	// implement enable_if in c++ 98 manner !
	template <bool, class T = void>
	struct enable_if
	{
	};

	// add specialization for true case !
	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	// Integral constant -> This template is designed to provide compile-time constants as types.
	// reference -> https://www.cs.auckland.ac.nz/references/unix/digital/AQTLTBTE/DOCU_032.HTM

	template <class T, T v>
	struct integral_constant
	{
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
		operator value_type() { return value; }
	};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	// is_integral -> Trait class that identifies whether T is an integral type.

	template <class T>
	struct is_integral : public false_type
	{
	};

	template <>
	struct is_integral<bool> : public true_type
	{
	};

	template <>
	struct is_integral<char> : public true_type
	{
	};

	template <>
	struct is_integral<char16_t> : public true_type
	{
	};

	template <>
	struct is_integral<char32_t> : public true_type
	{
	};

	template <>
	struct is_integral<wchar_t> : public true_type
	{
	};

	template <>
	struct is_integral<signed char> : public true_type
	{
	};

	template <>
	struct is_integral<short int> : public true_type
	{
	};

	template <>
	struct is_integral<int> : public true_type
	{
	};

	template <>
	struct is_integral<long int> : public true_type
	{
	};

	template <>
	struct is_integral<long long int> : public true_type
	{
	};

	template <>
	struct is_integral<unsigned char> : public true_type
	{
	};

	template <>
	struct is_integral<unsigned short int> : public true_type
	{
	};

	template <>
	struct is_integral<unsigned int> : public true_type
	{
	};

	template <>
	struct is_integral<unsigned long int> : public true_type
	{
	};

	template <>
	struct is_integral<unsigned long long int> : public true_type
	{
	};

};

#endif