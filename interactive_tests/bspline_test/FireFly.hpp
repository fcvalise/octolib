/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FireFly.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/14 22:14:31 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/15 12:11:32 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIREFLY_HPP
# define FIREFLY_HPP
# include <SFML/Graphics/CircleShape.hpp>
# include <SFML/Graphics/RenderTarget.hpp>
# include <SFML/System/Time.hpp>
# include "BSpline.hpp"

class FireFly
{
public:
	FireFly();

	void	addPoint(sf::Vector2f const& pos, bool remove = true);
	void	update(sf::Time const& time, sf::Vector2f const& interestPoint);
	void	draw(sf::RenderTarget& render)const;
private:
private:
	BSpline			m_spline;
	float			m_t;
	float			m_speed;
	sf::CircleShape	m_shape;
};

#endif
