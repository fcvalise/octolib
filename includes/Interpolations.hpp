/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Interpolations.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/11 15:52:34 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/23 01:15:10 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPOLATIONS_HPP
# define INTERPOLATIONS_HPP
# include <SFML/Graphics/Color.hpp>
# include <cmath>

namespace octo
{
	template <class T>
	static T	linearInterpolation(T a, T b, float alpha)
	{
		return (a * (1.f - alpha) + b * alpha);
	}

	template <class T>
	static T	cosinusInterpolation(T a, T b, float alpha)
	{
		return (a * std::cos((1.f - alpha) * M_PI) + b * alpha);
	}

	sf::Color	linearInterpolation(sf::Color a, sf::Color b, float alpha);
	sf::Color	cosinusInterpolation(sf::Color a, sf::Color b, float alpha);
}

#endif
