/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Interpolations.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/11 15:52:34 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/29 01:41:46 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPOLATIONS_HPP
# define INTERPOLATIONS_HPP
# include <SFML/Graphics/Color.hpp>
# include <cmath>

namespace octo
{
	/*!	Linear interpolation between 2 values
	 *	\ingroup Core
	 */
	template <class T>
	static T	linearInterpolation(T a, T b, float alpha)
	{
		return (a * (1.f - alpha) + b * alpha);
	}

	/*!	Cosinus interpolation between 2 values
	 *	\ingroup Core
	 */
	template <class T>
	static T	cosinusInterpolation(T a, T b, float alpha)
	{
		return (a * std::cos((1.f - alpha) * M_PI) + b * alpha);
	}

	sf::Color	linearInterpolation(sf::Color a, sf::Color b, float alpha);
	sf::Color	cosinusInterpolation(sf::Color a, sf::Color b, float alpha);
}

#endif
