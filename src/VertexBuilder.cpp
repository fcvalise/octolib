/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VertexBuilder.cpp                                   :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/08 05:35:34 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/14 21:22:59 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VertexBuilder.hpp"
#include "Math.hpp"
#include <stdexcept>
#include <cassert>

namespace octo
{
	namespace
	{
		static sf::Vector2f	computeNormale(sf::Vector2f const& v)
		{
			return (sf::Vector2f(-v.y, v.x));
		}
	}

	VertexBuilder::VertexBuilder(sf::Vertex* vertices, std::size_t count) :
		m_vertices(vertices),
		m_size(count),
		m_used(0u)
	{
		assert(vertices != nullptr);
		assert(count > 0);
	}

	void	VertexBuilder::createVertex(sf::Vector2f const& pos, sf::Color const& color)
	{
		if (m_used + 1 > m_size)
			throw std::runtime_error("vertex builder: no more vertices");
		m_vertices[m_used].position = pos;
		m_vertices[m_used].color = color;
		++m_used;
	}

	void	VertexBuilder::createLine(sf::Vector2f const& p0,
									  sf::Vector2f const& p1,
									  float thickness,
									  sf::Color const& color)
	{
		sf::Vector2f	p;
		float			halfThickness = thickness * .5f;

		p = computeNormale(p1 - p0);
		octo::normalize(p);
		p *= halfThickness;
		createQuad(p0 - p, p0 + p, p1 + p, p1 - p, color);
	}

	void	VertexBuilder::createTriangle(sf::Vector2f const& p0,
										  sf::Vector2f const& p1,
										  sf::Vector2f const& p2,
										  sf::Color const& color)
	{
		if (m_used + 3 > m_size)
			throw std::runtime_error("vertex builder: no more vertices");
		sf::Vertex* const	vertices = m_vertices + m_used;

		vertices[0].position = p0;
		vertices[1].position = p1;
		vertices[2].position = p2;
		vertices[0].color = color;
		vertices[1].color = color;
		vertices[2].color = color;
		m_used += 3;
	}

	void	VertexBuilder::createQuad(sf::Vector2f const& p0,
									  sf::Vector2f const& p1,
									  sf::Vector2f const& p2,
									  sf::Vector2f const& p3,
									  sf::Color const& color)
	{
		if (m_used + 6 > m_size)
			throw std::runtime_error("vertex builder: no more vertices");
		sf::Vertex* const	vertices = m_vertices + m_used;

		vertices[0].position = p0;
		vertices[1].position = p1;
		vertices[2].position = p2;
		vertices[3].position = p0;
		vertices[4].position = p3;
		vertices[5].position = p2;
		vertices[0].color = color;
		vertices[1].color = color;
		vertices[2].color = color;
		vertices[3].color = color;
		vertices[4].color = color;
		vertices[5].color = color;
		m_used += 6;
	}

	std::size_t VertexBuilder::getUsed()const
	{
		return (m_used);
	}
}
