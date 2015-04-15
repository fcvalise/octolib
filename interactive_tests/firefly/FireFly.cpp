/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FireFly.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/14 22:18:38 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/15 14:35:38 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FireFly.hpp"
#include <PrintSFML.hpp>
#include <iostream>

FireFly::FireFly() :
	m_engine(12345),
	m_dist(-1.f, 1.f),
	m_diameter(8.f),
	m_speed(1.f),
	m_interest(50.f)
{
}

void	FireFly::setTexture(sf::Texture const& texture)
{
	m_shape.setTexture(texture);
	m_shape.setOrigin(sf::Vector2f(texture.getSize()) * 0.5f);
	m_shape.setScale(m_diameter / texture.getSize().x, m_diameter / texture.getSize().y); 
	m_texture = &texture;
}

void	FireFly::setSpeed(float speed)
{
	m_speed = speed;
}

void	FireFly::setInterest(float interest)
{
	m_interest = interest;
}

void	FireFly::setDiameter(float diameter)
{
	m_diameter = diameter;
	m_shape.setScale(m_diameter / m_texture->getSize().x, m_diameter / m_texture->getSize().y); 
}

void	FireFly::setColor(sf::Color const& color)
{
	m_shape.setColor(color);
}

float	FireFly::getSpeed()const
{
	return (m_speed);
}

float	FireFly::getInterest()const
{
	return (m_interest);
}

float	FireFly::getDiameter()const
{
	return (m_diameter);
}

float	FireFly::getT()const
{
	return (m_t);
}

sf::Color const&	FireFly::getColor()const
{
	return (m_shape.getColor());
}

void	FireFly::addPoint(sf::Vector2f const& pos)
{
	m_spline.pushBack(pos);
}

void	FireFly::update(sf::Time const& time, sf::Vector2f const& interestPoint)
{
	int		oldIntegerPart = static_cast<int>(m_t);
	int		newIntegerPart = 0;

	m_t += m_speed * time.asSeconds();
	newIntegerPart = static_cast<int>(m_t);
	if (m_spline.size() >= 4)
	{
		m_shape.setPosition(m_spline.compute(m_t));
		if (newIntegerPart > oldIntegerPart)
		{
			m_spline.pushBack(randomize(interestPoint));
			if (m_spline.size() > 8 && newIntegerPart >= 4)
			{
				m_spline.popFront();
				m_t -= 1.f;
			}
		}
	}
	else
	{
		m_spline.pushBack(randomize(interestPoint));	
	}
}

void	FireFly::draw(sf::RenderTarget& render)const
{
	render.draw(m_shape);
}

sf::Vector2f	FireFly::randomize(sf::Vector2f point)
{
	point.x += m_dist(m_engine) * m_interest;
	point.y += m_dist(m_engine) * m_interest;
	return (point);
}
