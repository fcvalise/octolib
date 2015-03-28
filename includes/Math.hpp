/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Math.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 00:52:30 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/28 09:51:08 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_HPP
# define MATH_HPP
# include <type_traits>

namespace octo
{
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

	template <unsigned int N, class T>
	struct	Factorial
	{
		static constexpr const T		Value = N * Factorial<N - 1u, T>::Value;
	};

	template <class T>
	struct	Factorial<0u, T>
	{
		static constexpr const T		Value = 1;
	};

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
	
	/*!	Compute cos value
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
	 *	Return an approximation of cos with precision of 5 decimals.
	 */
	float	cosLPA(float x);

	/*!	High precision cos approximation
	 *
	 *	Return an approximation of cos with precision of 5 decimals.
	 */
	float	cosHPA(float x);
}

#endif
