/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Interpolationis.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/14 20:00:37 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/16 03:00:48 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Interpolations.hpp"
#include "Math.hpp"

namespace octo
{
	sf::Color	linearInterpolation(sf::Color a, sf::Color b, float alpha)
	{
		sf::Color	result;

		result.r = linearInterpolation(a.r, b.r, alpha);
		result.g = linearInterpolation(a.g, b.g, alpha);
		result.b = linearInterpolation(a.b, b.b, alpha);
		result.a = linearInterpolation(a.a, b.a, alpha);
		return (result);
	}

	sf::Color	cosinusInterpolation(sf::Color a, sf::Color b, float alpha)
	{
		sf::Color	result;

		result.r = cosinusInterpolation(a.r, b.r, alpha);
		result.g = cosinusInterpolation(a.g, b.g, alpha);
		result.b = cosinusInterpolation(a.b, b.b, alpha);
		result.a = cosinusInterpolation(a.a, b.a, alpha);
		return (result);
	}
	  
	sf::Vector2f	bsplineInterpolation(sf::Vector2f const& p0,
										 sf::Vector2f const& p1,
										 sf::Vector2f const& p2,
										 sf::Vector2f const& p3,
										 float t)
	{
		float const		CoefA = (1.f / 6.f);
		float const 	CoefB = (3.f * octo::pow<3>(t) - 6.f * octo::pow<2>(t) + 4.f);
		float const 	CoefC = (-3.f * octo::pow<3>(t) + 3.f * octo::pow<2>(t) + (3.f * t) + 1.f);
		float const		CoefD = octo::pow<3>(t);
		sf::Vector2f	result;

		result.x =	CoefA * (octo::pow<3>(1.f - t) * p0.x +	(CoefB * p1.x) +
						(CoefC * p2.x) + CoefD * p3.x);
		result.y =	CoefA * (octo::pow<3>(1.f - t) * p0.y +	(CoefB * p1.y) +
								(CoefC * p2.y) + CoefD * p3.y);
		return (result);
	}
}
