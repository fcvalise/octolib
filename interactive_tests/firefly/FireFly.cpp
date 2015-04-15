/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FireFly.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/14 22:18:38 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/15 16:10:39 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FireFly.hpp"
#include <PrintSFML.hpp>
#include <iostream>

FireFly::FireFly() :
	m_t(0.f),
	m_diameter(8.f),
	m_haloDiameter(20),
	m_speed(0.5f),
	m_interest(500.f)
{
}

void	FireFly::setRandom(RandomFunc func)
{
	m_rnd = func;
}

void	FireFly::setTexture(sf::Texture const& texture)
{
	m_shape.setTexture(texture);
	m_shape.setOrigin(sf::Vector2f(texture.getSize()) * 0.5f);
	m_haloShape.setTexture(texture);
	m_haloShape.setOrigin(sf::Vector2f(texture.getSize()) * 0.5f);
	m_texture = &texture;
	setDiameter(m_diameter);
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
	m_haloDiameter = diameter * 4.f;
	m_shape.setScale(m_diameter / m_texture->getSize().x, m_diameter / m_texture->getSize().y); 
	m_haloShape.setScale(m_haloDiameter / m_texture->getSize().x, m_haloDiameter / m_texture->getSize().y); 
}

void	FireFly::setColor(sf::Color const& color)
{
	sf::Color	haloColor = color;

	haloColor.a = 100;
	m_shape.setColor(color);
	m_haloShape.setColor(haloColor);
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

	if (m_spline.size() >= 4)
	{
		m_t += m_speed * time.asSeconds();
		newIntegerPart = static_cast<int>(m_t);
		m_shape.setPosition(m_spline.compute(m_t));
		m_haloShape.setPosition(m_spline.compute(m_t));
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
		m_spline.pushBack(randomize(interestPoint));	
		m_spline.pushBack(randomize(interestPoint));	
		m_spline.pushBack(randomize(interestPoint));	
	}
}

void	FireFly::draw(sf::RenderTarget& render)const
{
	render.draw(m_haloShape);
	render.draw(m_shape);
}

sf::Vector2f	FireFly::randomize(sf::Vector2f point)
{
	point.x += m_rnd() * m_interest;
	point.y += m_rnd() * m_interest;
	return (point);
}
