/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FireFlySwarm.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/15 14:59:23 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/15 23:00:17 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FireFlySwarm.hpp"

FireFlySwarm::FireFlySwarm() :
	m_texture(nullptr),
	m_engine(7854),
	m_dist(-1.f, 1.f),
	m_gaussDist(0.f, 0.6f),
	m_gaussRange(1.3f),
	m_charDist(0, 255)
{
}

void	FireFlySwarm::setTexture(sf::Texture const& texture)
{
	m_texture = &texture;
}

std::size_t	FireFlySwarm::createFireFly()
{
	std::size_t	newId = m_flies.size();
	FireFly		fireFly;

	fireFly.setRandom(std::bind(std::ref(m_dist), std::ref(m_engine)));
	fireFly.setTexture(*m_texture);
	fireFly.setDiameter(std::max(14.f + (m_gaussDist(m_engine) * 6.f), 8.f));
	fireFly.setSpeed(std::max(1.f + (m_gaussDist(m_engine) / m_gaussRange), 0.5f));
	fireFly.setColor(sf::Color(233, 213, 61));
	m_flies.emplace_back(fireFly);
	return (newId);
}

void	FireFlySwarm::createFireFlies(std::size_t count)
{
	for (std::size_t i = 0; i < count; ++i)
		createFireFly();
}

void	FireFlySwarm::clear()
{
	m_flies.clear();
}

void	FireFlySwarm::setSpeed(std::size_t id, float speed)
{
	m_flies.at(id).setSpeed(speed);
}

void	FireFlySwarm::setInterest(std::size_t id, float interest)
{
	m_flies.at(id).setInterest(interest);
}

void	FireFlySwarm::setDiameter(std::size_t id, float diameter)
{
	m_flies.at(id).setDiameter(diameter);
}

void	FireFlySwarm::setColor(std::size_t id, sf::Color const& color)
{
	m_flies.at(id).setColor(color);
}

float	FireFlySwarm::getSpeed(std::size_t id)const
{
	return (m_flies.at(id).getSpeed());
}

float	FireFlySwarm::getInterest(std::size_t id)const
{
	return (m_flies.at(id).getInterest());
}

float	FireFlySwarm::getDiameter(std::size_t id)const
{
	return (m_flies.at(id).getDiameter());
}

sf::Color	FireFlySwarm::getColor(std::size_t id)const
{
	return (m_flies.at(id).getColor());
}

void	FireFlySwarm::update(sf::Time frameTime, sf::Vector2f const& interestPoint)
{
	for (FireFly& fly : m_flies)
		fly.update(frameTime, interestPoint);
}

void	FireFlySwarm::draw(sf::RenderTarget& render)const
{
	for (FireFly const& fly : m_flies)
		fly.draw(render);
}
