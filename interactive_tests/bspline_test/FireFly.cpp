/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FireFly.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/14 22:18:38 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/15 12:17:37 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FireFly.hpp"
#include <PrintSFML.hpp>
#include <iostream>

FireFly::FireFly() :
	m_speed(0.5f)
{
	m_shape = sf::CircleShape(8.f, 64);
	m_shape.setFillColor(sf::Color::Red);
	m_shape.setOrigin(sf::Vector2f(4.f, 4.f));
}

void	FireFly::addPoint(sf::Vector2f const& pos, bool remove)
{
	m_spline.pushBack(pos);
	(void)remove;
}

void	FireFly::update(sf::Time const& time, sf::Vector2f const& interestPoint)
{
	using octo::operator <<;
	int		oldIntegerPart = static_cast<int>(m_t);
	int		newIntegerPart = 0;

	m_t += m_speed * time.asSeconds();
	newIntegerPart = static_cast<int>(m_t);
	m_shape.setPosition(m_spline.compute(m_t));
	if (newIntegerPart > oldIntegerPart)
	{
		m_spline.pushBack(interestPoint);
		if (m_spline.size() > 8 && newIntegerPart >= 4)
		{
			m_spline.popFront();
			m_t -= 1.f;
		}
	}
	(void)interestPoint;
}

void	FireFly::draw(sf::RenderTarget& render)const
{
	render.draw(m_shape);
}
