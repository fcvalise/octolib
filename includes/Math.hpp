/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Math.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 00:52:30 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/16 02:19:03 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_HPP
# define MATH_HPP
# include <type_traits>
# include <cstdint>

namespace octo
{
	/*!
	 *	\addtogroup	Math
	 *	@{
	 */

	/*!
	 *	Compute the power of a value
	 *	\code
	 *	std::cout << octo::pow<5>(4) << std::endl;	// Compute 4^5 then display 1024
	 *	\endcode
	 */
	template <unsigned int P>
	inline float	pow(float value)
	{
		return ((P % 2u == 0u) ? pow<2u>(pow<P / 2u>(value)) : value * pow<2u>(pow<P / 2u>(value)));
	}

	template <>
	float	pow<2u>(float value);

	template <>
	float	pow<1u>(float value);

	template <>
	float	pow<0u>(float);

	/*!
	 *	Compute the n-th value of the factorial sequence
	 *	\code
	 *	std::cout << octo::Factorial<16>::Value << std::endl;	// Compute !16 then display 20922789888000
	 *	\endcode
	 */
	template <unsigned int N, class T = std::uint64_t>
	struct	Factorial
	{
		static constexpr const T		Value = N * Factorial<N - 1u, T>::Value;
	};

	template <class T>
	struct	Factorial<0u, T>
	{
		static constexpr const T		Value = 1;
	};

	/*!
	 *	Compute the exposantial of a value
	 *	\tparam N Define the precision
	 *	\tparam T Type of value
	 *	\code
	 *	std::cout << octo::Factorial<16>::Value << std::endl;	// Compute !16 then display 20922789888000
	 *	\endcode
	 */
	template <unsigned int N, class T>
	struct	Exponential
	{
		inline static T	compute(T value)
		{
			return (Exponential<N - 1, T>::compute(value) + (pow<N>(value) / Factorial<N, T>::Value));
		}
	};

	template <class T>
	struct	Exponential<1u, T>
	{
		inline static T	compute(T value)
		{
			return (value + T(1));
		}
	};
	
	/*!
	 *	Compute a constant of the power of 2 sequence
	 *
	 *	Computing is done at compile time.
	 *	\code
	 *	std::cout << Power2<8>::Value << std::endl;	// Display 265
	 *	\endcode
	 */
	template <unsigned int N, class T = std::uint64_t>
	struct	Power2
	{
		static constexpr T const	Value = 2u * Power2<N - 1, T>::Value;
	};

	template <class T>
	struct	Power2<0u, T>
	{
		static constexpr T const	Value = 1u;
	};

	/*!
	 *	Compute cos value
	 *	\tparam N Precision of approximation
	 */
	template <unsigned int N>
	inline float	cos(float value)
	{
		typedef typename std::conditional<((N / 2u) % 2u) == 0,
				 std::integral_constant<int, 1>,
				 std::integral_constant<int, -1>>::type	Sign;
		static constexpr float const	Nmod2 = N % 2u;
		static constexpr bool const		IsPair = N % 2u == 0u;

		return ((Nmod2 == 1) ? cos<(IsPair) ? 0u : N - 1u>(value) :
							   cos<(IsPair) ? N - 2u : 0u>(value) +
							   Sign::value * pow<(IsPair) ? N : 0u>(value) / Factorial<(IsPair) ? N : 0u, float>::Value);
	}

	template <>
	float	cos<1u>(float);

	template <>
	float	cos<0u>(float);

	/*!	Low precision cos approximation
	 *
	 *	Return an approximation of cos with precision of ? decimals.
	 */
	float	cosLPA(float x);

	/*!	High precision cos approximation
	 *
	 *	Return an approximation of cos with precision of ? decimals.
	 */
	float	cosHPA(float x);

	/*!
	 *	@}
	 */
}

#endif