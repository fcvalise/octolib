/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Segment.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 22:50:33 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/14 00:49:44 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEGMENT_HPP
# define SEGMENT_HPP
# include <SFML/System/Vector2.hpp>
# include <SFML/Graphics/Rect.hpp>
# include <iostream>
# include <vector>

namespace octo
{
	class Collision;

	class Segment
	{
	public:
		typedef std::uint64_t			Identifier;
		static constexpr Identifier		NullId = std::numeric_limits<Identifier>::max();

		Segment();
		Segment(sf::Vector2f p0, sf::Vector2f p1);
		Segment(float x0, float y0, float x1, float y1);

		bool				hitTest(Segment const& other, Collision& collision)const;

		void				setIdentifier(Identifier id);
		Identifier			id()const;

		void				reset(sf::Vector2f const& p0, sf::Vector2f const& p1);
		void				setP0(sf::Vector2f const& p0);
		void				setP1(sf::Vector2f const& p1);

		sf::Vector2f const&	p0()const;
		sf::Vector2f const&	p1()const;
		sf::Vector2f		normale()const;
		sf::Vector2f		parametric(float t)const;
		float				location(sf::Vector2f const& point)const;
		sf::Vector2f		direction()const;
		float				directorCoef()const;

		static void			split(Segment const &segment, float t, Segment& first, Segment &second);
		static bool			areParallel(Segment const& left, Segment const& right);
		static bool			areAligned(Segment const& left, Segment const& right);
	private:
		sf::Vector2f	m_p0;
		sf::Vector2f	m_p1;
		Identifier		m_id;
	};

	typedef std::vector<Segment>	SegmentArray;

	bool			operator == (Segment const& left, Segment const& right);
	bool			operator != (Segment const& left, Segment const& right);

	std::ostream	&operator << (std::ostream& os, Segment const& value);
	std::istream	&operator >> (std::istream& is, Segment& value);
	std::ostream	&operator << (std::ostream& os, SegmentArray const& value);
	std::istream	&operator >> (std::istream& is, SegmentArray& value);
}

#endif
