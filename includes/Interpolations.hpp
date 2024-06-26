/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Interpolations.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/11 15:52:34 by irabeson          #+#    #+#             */
/*   Updated: 2015/07/14 16:16:38 by pciavald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPOLATIONS_HPP
# define INTERPOLATIONS_HPP
# include <SFML/Graphics/Color.hpp>
# include <SFML/System/Vector2.hpp>
# include <cmath>

# include "Math.hpp"

namespace octo
{
	/*!
	 *	\addtogroup	Math
	 *	@{
	 */

	/*!
	 *	Linear interpolation between 2 values
	 */
	template <class T>
	static T	linearInterpolation(T a, T b, float alpha)
	{
		return (a * (1.f - alpha) + b * alpha);
	}

	/*!
	 *	Cosinus interpolation between 2 values
	 */
	template <class T>
	static T	cosinusInterpolation(T a, T b, float alpha)
	{
		return linearInterpolation(a, b, 0.5f - (std::cos(alpha * Pi) / 2.f));
	}

	sf::Color		linearInterpolation(sf::Color a, sf::Color b, float alpha);
	sf::Color		cosinusInterpolation(sf::Color a, sf::Color b, float alpha);
	sf::Vector2f	bsplineInterpolation(sf::Vector2f const& p0, sf::Vector2f const& p1,
										 sf::Vector2f const& p2, sf::Vector2f const& p3,
										 float t);
	/*!
	 *	@}
	 */
}

#endif
