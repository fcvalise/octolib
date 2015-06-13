/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Segment.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 22:59:57 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/14 01:08:47 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Segment.hpp"
#include "Collision.hpp"
#include "ExpectChar.hpp"
#include "PrintSFML.hpp"
#include "Math.hpp"

#include <cmath>

namespace octo
{
	/*
		Coupe un segment en 2.
		\param segment Segment coupé
		\param t Valeur de la variable t dans l'équation paramétrique d'une droite
		\param first Reçoit la première partie du segment
		\param second Reçoit la deuxième partie du segment
		\see Segment::parametric()	
	*/
	void	Segment::split(Segment const& segment, float t, Segment& first, Segment &second)
	{
		sf::Vector2f const	inter = segment.parametric(t);

		first = Segment(segment.p0(), inter);
		second = Segment(inter, segment.p1());
	}

	bool	Segment::areParallel(Segment const& lhs, Segment const& rhs)
	{
		sf::Vector2f const	ld = lhs.direction();
		sf::Vector2f const	rd = rhs.direction();
		
		return (std::abs((ld.x * rd.y) - (ld.y * rd.x)) < std::numeric_limits<float>::epsilon());
	}

	bool	Segment::areAligned(Segment const& lhs, Segment const& rhs)
	{
		if (areParallel(lhs, rhs))
		{
			return (std::abs(rhs.location(lhs.p0())) < std::numeric_limits<float>::epsilon());
		}
		return (false);
	}

	Segment::Segment() :
		m_id(NullId)
	{
	}

	Segment::Segment(sf::Vector2f p0, sf::Vector2f p1) :
		m_p0(p0),
		m_p1(p1),
		m_id(NullId)
	{
	}

	Segment::Segment(float x0, float y0, float x1, float y1) :
		m_p0(x0, y0),
		m_p1(x1, y1),
		m_id(NullId)
	{
	}

	void	Segment::setIdentifier(Identifier id)
	{
		m_id = id;
	}

	Segment::Identifier	Segment::id()const
	{
		return (m_id);
	}

	bool	Segment::hitTest(Segment const& other, Collision& collision)const
	{
		sf::Vector2f const	l(m_p1.x - m_p0.x, m_p1.y - m_p0.y);
		sf::Vector2f const	j(other.m_p1.x - other.m_p0.x, other.m_p1.y - other.m_p0.y);
		float const			denom = (l.x * j.y - l.y * j.x);
		float				m = 0.f;
		float				k = 0.f;

		if (std::abs(denom) < std::numeric_limits<decltype(denom)>::epsilon())
		{
			return (false);
		}
		m = -((-l.x * m_p0.y + l.x * other.m_p0.y + l.y * m_p0.x - l.y * other.m_p0.x) / denom);
		k = -(m_p0.x * j.y - other.m_p0.x * j.y - j.x * m_p0.y + j.x * other.m_p0.y) / denom;
		if (m >= 0.f && m <= 1.f && k >= 0.f && k <= 1.f)
		{
			collision.setSegment(other);
			collision.setPosition(sf::Vector2f(m_p0.x + k * l.x, m_p0.y + k * l.y));
			collision.setCoef(k);
			return (true);
		}
		return (false);
	}

	void	Segment::reset(sf::Vector2f const& p0, sf::Vector2f const& p1)
	{
		m_p0 = p0;
		m_p1 = p1;
	}

	void	Segment::setP0(sf::Vector2f const& p0)
	{
		m_p0 = p0;
	}

	void	Segment::setP1(sf::Vector2f const& p1)
	{
		m_p1 = p1;
	}

	sf::Vector2f const&	Segment::p0()const
	{
		return (m_p0);
	}

	sf::Vector2f const&	Segment::p1()const
	{
		return (m_p1);
	}

	sf::Vector2f		Segment::normale()const
	{
		sf::Vector2f	d = m_p0 - m_p1;

		return (sf::Vector2f(-d.y, d.x));
	}

	/*
		Soit s le vecteur du segment [AB] (s = A - B):
		A + t * s
		Ce qui donne si on extrait les valeurs x et y des vecteurs:
		Ax + t * sx
		Ay + t * sy
		\param t Variable de l'éqaution paramétrique du segment([0;1]).
	*/
	sf::Vector2f	Segment::parametric(float t)const
	{
		sf::Vector2f const	d = direction();

		return (sf::Vector2f(m_p0.x + t * d.x, m_p0.y + t * d.y));
	}

	/*
		Indique de quel cote se situe un point par rapport au segment.
	*/
	float	Segment::location(sf::Vector2f const& point)const
	{
		return (dotProduct(normale(), point - m_p0));
	}

	sf::Vector2f	Segment::direction()const
	{
		return (m_p1 - m_p0);
	}

	float			Segment::directorCoef()const
	{
		sf::Vector2f const	d = direction();

		if (std::abs(d.x) < std::numeric_limits<float>::epsilon())
			return (0.f);
		else
			return (d.y / d.x);
	}

	bool	operator == (Segment const& left, Segment const& right)
	{
		return (std::abs(left.p0().x - right.p0().x) < std::numeric_limits<float>::epsilon() &&
				std::abs(left.p1().y - right.p1().y) < std::numeric_limits<float>::epsilon());
	}

	bool	operator != (Segment const& left, Segment const& right)
	{
		return (std::abs(left.p0().x - right.p0().x) >= std::numeric_limits<float>::epsilon() ||
				std::abs(left.p1().y - right.p1().y) >= std::numeric_limits<float>::epsilon());
	}

	std::ostream	&operator << (std::ostream& os, Segment const& value)
	{
		os << "[" << value.id() << ":" << value.p0() << ":" << value.p1() << "]";
		return(os);
	}

	std::istream	&operator >> (std::istream& is, Segment& value)
	{
		sf::Vector2f					p0;
		sf::Vector2f					p1;
		Segment::Identifier				id = Segment::NullId;
		typename std::istream::sentry	init(is);

		if (init)
		{
			is >> ExpectChar('[') >> id >> ExpectChar(':') >> p0 >> ExpectChar(':') >> p1 >> ExpectChar(']');
			value = Segment(p0, p1);
		}
		return (is);
	}

	std::ostream&	operator << (std::ostream& os, SegmentArray const& segments)
	{
		os << "[" << segments.size() << ":";
		for (const Segment& segment : segments)
		{
			os << segment << ':';
		}
		os << "]";
		return (os);
	}

	std::istream&	operator >> (std::istream& is, SegmentArray& segments)
	{
		SegmentArray			temp;
		SegmentArray::size_type	count = 0;
		std::istream::sentry	init(is);

		if (init)
		{
			is >> ExpectChar('[') >> count >> ExpectChar(':');
			temp.resize(count);
			for (SegmentArray::size_type i = 0; i < count; ++i)
			{
				is >> temp[i] >> ExpectChar(':');
			}
			is >> ExpectChar(']');
			temp.shrink_to_fit();
			segments = std::move(temp);
		}
		return (is);
	}
}
