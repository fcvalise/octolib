/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Collision.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/29 09:00:33 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/14 00:52:15 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISION_HPP
# define COLLISION_HPP
# include "Segment.hpp"

# include <SFML/System/Vector2.hpp>

namespace octo
{
	class Collision
	{
	public:
		Collision() :
			m_coef(0.f)
		{
		}
		
		void				setPosition(sf::Vector2f const& pos){m_position = pos;}
		void				setSegment(Segment const& segment){m_segment = segment;}
		void				setCoef(float coef){m_coef = coef;}

		sf::Vector2f const&	position()const{return m_position;}
		Segment const&		segment()const{return m_segment;}
		float				coef()const{return m_coef;}
	private:
		Segment				m_segment;
		sf::Vector2f		m_position;
		float				m_coef;
	};
}

#endif
