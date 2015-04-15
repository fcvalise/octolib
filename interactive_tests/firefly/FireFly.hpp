/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FireFly.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/14 22:14:31 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/15 14:35:21 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIREFLY_HPP
# define FIREFLY_HPP
# include <SFML/Graphics/CircleShape.hpp>
# include <SFML/Graphics/RenderTarget.hpp>
# include <SFML/Graphics/Sprite.hpp>
# include <SFML/Graphics/Texture.hpp>
# include <SFML/System/Time.hpp>
# include "BSpline.hpp"

#include <random>

class FireFly
{
public:
	FireFly();

	void				setTexture(sf::Texture const& texture);
	void				setSpeed(float speed);
	void				setInterest(float interest);
	void				setDiameter(float diameter);
	void				setColor(sf::Color const& color);

	float				getSpeed()const;
	float				getInterest()const;
	float				getDiameter()const;
	sf::Color const&	getColor()const;
	float				getT()const;

	void				addPoint(sf::Vector2f const& pos);
	void				update(sf::Time const& time, sf::Vector2f const& interestPoint);
	void				draw(sf::RenderTarget& render)const;
private:
	sf::Vector2f		randomize(sf::Vector2f point);
private:
	typedef std::uniform_real_distribution<float>	Dist;
	typedef std::mt19937							Engine;

	Engine				m_engine;
	Dist				m_dist;
	sf::Sprite			m_shape;
	BSpline				m_spline;
	sf::Texture const*	m_texture;
	float				m_t;
	float				m_diameter;
	float				m_speed;
	float				m_interest;
};

#endif
