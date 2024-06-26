/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Math.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 00:52:30 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/20 17:18:23 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_HPP
# define MATH_HPP
# include <type_traits>
# include <cstdint>
# include <cmath>
# include <SFML/System/Vector2.hpp>

namespace octo
{
	/*!
	 *	\addtogroup	Math
	 *	@{
	 */

	/*!	Constant value of Pi */
	static constexpr float const	Pi = 3.14159265358979323846f;

	/*!	Constant value of Pi divided by 2 */
	static constexpr float const	PiDiv2 = Pi / 2.f;

	/*!	Constant value of Pi divided by 4 */
	static constexpr float const	PiDiv4 = Pi / 4.f;

	/*!	Constant value of Pi multiplied by 2 */
	static constexpr float const	Pi2 = Pi * 2.f;

	/*!	Constant value of Pi multiplied by 4 */
	static constexpr float const	Pi4 = Pi * 4.f;

	/*!	Factor to convert degrees in radians */
	static constexpr float const	Deg2Rad = Pi / 180.f; 

	/*!	Factor to convert radians in degrees */
	static constexpr float const	Rad2Deg = 180.f / Pi; 

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
	inline float	pow<3u>(float value)
	{
		return (value * value * value);
	}

	template <>
	inline float	pow<2u>(float value)
	{
		return (value * value);
	}

	template <>
	inline float	pow<1u>(float value)
	{
		return (value);
	}

	template <>
	inline float	pow<0u>(float)
	{
		return (1.f);
	}

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
	inline float	cos<1u>(float value)
	{
		return (value);
	}

	template <>
	inline float	cos<0u>(float)
	{
		return (1.f);
	}

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
	 *	Compute magnitude
	 */
	template <class T>
	inline T	magnitude(sf::Vector2<T> const & v)
	{
		return std::sqrt(v.x * v.x + v.y * v.y);
	}

	/*!
	 *	Normalize the vector, magnitude = 1
	 */
	template <class T>
	inline void	normalize(sf::Vector2<T> & v)
	{
		float mag = magnitude(v);

		v.x /= mag;
		v.y /= mag;
	}

	/*!
	 *	Normalize the vector, magnitude = 1
	 */
	template <class T>
	inline sf::Vector2f	normalized(sf::Vector2<T> const& v)
	{
		float mag = magnitude(v);

		return (sf::Vector2f(v.x / mag, v.y / mag));
	}

	/*!
	 *	Compute dot product
	 */
	template <class T>
	inline T	dotProduct(sf::Vector2<T> const & left, sf::Vector2<T> const & right)
	{
		return (left.x * right.x + left.y * right.y);
	}

	/*!	Compute the manhattan length
	 *
	 *	The distance between two points in a grid based on a strictly horizontal and/or vertical path.
	 */
	template <class T>
	inline T	manhattanLength(sf::Vector2<T> const& vector)
	{
		return (vector.x + vector.y);
	}

	/*!	Convert degrees in radians */
	inline constexpr float	deg2Rad(float degrees)
	{
		return (degrees * Deg2Rad);
	}

	/*!	Convert radians in degrees */
	inline constexpr float	rad2Deg(float radians)
	{
		return (radians * Rad2Deg);
	}

	/*!	Rotate vector around zero. Result is store in vector */
	void rotateVector(sf::Vector2f & vector,
						float const cosAngle,
						float const sinAngle);

	/*!	Rotate vector around an origin. Result is store in vector */
	void rotateVector(sf::Vector2f & vector,
						sf::Vector2f const & origin,
						float const cosAngle,
						float const sinAngle);

	/*!
	 *	@}
	 */
}

#endif
