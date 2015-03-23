/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Interpolationis.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/14 20:00:37 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/23 01:16:04 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Interpolations.hpp"


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
}
