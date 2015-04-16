/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FireFlySwarm.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/15 14:55:04 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/15 22:44:12 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIREFLYSWARM_HPP
# define FIREFLYSWARM_HPP
# include "FireFly.hpp"

# include <random>

class FireFlySwarm
{
	typedef std::uniform_real_distribution<float>	Dist;
	typedef std::normal_distribution<float>			GaussDist;
	typedef std::uniform_int_distribution<char>		CharDist;
	typedef std::mt19937							Engine;
public:
	FireFlySwarm();

	void		setTexture(sf::Texture const& texture);

	std::size_t	createFireFly();
	void		createFireFlies(std::size_t count);
	void		clear();

	void		setSpeed(std::size_t id, float speed);
	void		setInterest(std::size_t id, float interest);
	void		setDiameter(std::size_t id, float diameter);
	void		setColor(std::size_t id, sf::Color const& color);

	float		getSpeed(std::size_t id)const;
	float		getInterest(std::size_t id)const;
	float		getDiameter(std::size_t id)const;
	sf::Color	getColor(std::size_t id)const;

	void		update(sf::Time frameTime, sf::Vector2f const& interestPoint);
	void		draw(sf::RenderTarget& render)const;
private:
	std::vector<FireFly>	m_flies;
	sf::Texture const*		m_texture;
	Engine					m_engine;
	Dist					m_dist;
	GaussDist				m_gaussDist;
	float					m_gaussRange;
	CharDist				m_charDist;

};

#endif
