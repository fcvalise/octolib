/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Math.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 00:52:30 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/21 18:09:38 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_HPP
# define MATH_HPP
# include <type_traits>

namespace octo
{
	template <unsigned int P>
	float	pow(float value)
	{
		return (value * pow<P - 1>(value));
	}

	template <>
	float	pow<1u>(float value)
	{
		return (value);
	}

	template <>
	float	pow<0u>(float)
	{
		return (1.f);
	}

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
	
	template <unsigned int N>
	float	cos(float value)
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
	float	cos<1u>(float value)
	{
		return (value);
	}

	template <>
	float	cos<0u>(float)
	{
		return (1.f);
	}
}

#endif
