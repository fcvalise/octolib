/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VertexBuilder.cpp                                   :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/08 05:35:34 by irabeson          #+#    #+#             */
/*   Updated: 2015/08/07 10:58:17 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VertexBuilder.hpp"
#include "Math.hpp"
#include <stdexcept>
#include <cassert>
#include <algorithm>

namespace octo
{
	namespace
	{
		static sf::Vector2f	computeNormale(sf::Vector2f const& v)
		{
			return (sf::Vector2f(-v.y, v.x));
		}
	}

	/*!	Create a null builder */
	VertexBuilder::VertexBuilder() :
		VertexBuilder(nullptr, 0u)
	{
	}

	/*!	Create a builder by defining the begin of vertices array and the count of vertices
	 *	available.
	 *	\param vertices Begin of vertices array
	 *	\param count Count of vertices available
	 */
	VertexBuilder::VertexBuilder(sf::Vertex* vertices, std::size_t count) :
		m_vertices(vertices),
		m_size(count),
		m_used(0u)
	{
	}

	/*
	VertexBuilder::VertexBuilder(VertexBuilder&& other) :
		m_vertices(other.m_vertices),
		m_size(other.m_size),
		m_used(other.m_used)
	{
		other.m_vertices = nullptr;
		other.m_used = 0u;
		other.m_size = 0u;
	}*/

	/*!	Add a vertex by defining his position and color
	 *
	 *	This method must be called only with no null builder
	 *	\see isNull()
	 *	\throw std::runtime_error is thrown if there are not enough vertices
	 */
	void	VertexBuilder::createVertex(sf::Vector2f const& pos, sf::Color const& color)
	{
		assert(m_vertices != nullptr);
		if (m_used + 1 > m_size)
			throw std::runtime_error("vertex builder: no more vertices");
		m_vertices[m_used].position = pos;
		m_vertices[m_used].color = color;
		++m_used;
	}

	void	VertexBuilder::createVertex(sf::Vertex const& vertex)
	{
		assert(m_vertices != nullptr);
		if (m_used + 1 > m_size)
			throw std::runtime_error("vertex builder: no more vertices");
		m_vertices[m_used] = vertex;
		++m_used;
	}

	void	VertexBuilder::createVertex(sf::Vertex&& vertex)
	{
		assert(m_vertices != nullptr);
		if (m_used + 1 > m_size)
			throw std::runtime_error("vertex builder: no more vertices");
		m_vertices[m_used] = std::move(vertex);
		++m_used;
	}

	/*!	Add a line
	 *
	 *	This method must be called only with no null builder
	 *	\see isNull()
	 *	\throw std::runtime_error is thrown if there are not enough vertices
	 */
	void	VertexBuilder::createLine(sf::Vector2f const& p0,
									  sf::Vector2f const& p1,
									  float thickness,
									  sf::Color const& color)
	{
		assert(m_vertices != nullptr);
		if (m_used + 6 > m_size)
			throw std::runtime_error("vertex builder: no more vertices");
		 makeLine(m_vertices + m_used, p0, p1, thickness, color);
		 m_used += 6;
	}

	/*!	Add a triangle
	 *
	 *	This method must be called only with no null builder
	 *	\see isNull()
	 *	\throw std::runtime_error is thrown if there are not enough vertices
	 */
	void	VertexBuilder::createTriangle(sf::Vector2f const& p0,
										  sf::Vector2f const& p1,
										  sf::Vector2f const& p2,
										  sf::Color const& color)
	{
		assert(m_vertices != nullptr);
		if (m_used + 3 > m_size)
			throw std::runtime_error("vertex builder: no more vertices");
		sf::Vertex* const	vertices = m_vertices + m_used;

		makeTriangle(vertices, p0, p1, p2, color);
		m_used += 3;
	}

	/*!	Add a quad
	 *
	 *	This method must be called only with no null builder
	 *	\see isNull()
	 *	\throw std::runtime_error is thrown if there are not enough vertices
	 */
	void	VertexBuilder::createQuad(sf::Vector2f const& p0,
									  sf::Vector2f const& p1,
									  sf::Vector2f const& p2,
									  sf::Vector2f const& p3,
									  sf::Color const& color)
	{
		assert(m_vertices != nullptr);
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

	/*!	Add somes vertices
	 *
	 *	This method must be called only with no null builder
	 *	\see isNull()
	 *	\throw std::runtime_error is thrown if there are not enough vertices
	 */
	void	VertexBuilder::createVertices(std::vector<sf::Vertex> const& vertices)
	{
		assert(m_vertices != nullptr);
		if (m_used + vertices.size() > m_size)
			throw std::runtime_error("vertex builder: no more vertices");
		std::copy(vertices.begin(), vertices.end(), m_vertices + m_used);
		m_used += vertices.size();
	}

	void	VertexBuilder::createVertices(std::vector<sf::Vertex> const& vertices,
								   		  sf::Color const& color)
	{
		assert(m_vertices != nullptr);
		if (m_used + vertices.size() > m_size)
			throw std::runtime_error("vertex builder: no more vertices");
		for (auto i = 0u; i < vertices.size(); ++i)
		{
			m_vertices[m_used + i] = vertices[i];
			m_vertices[m_used + i].color = color;
		}
		m_used += vertices.size();
	}

	/*!	Remove all primitives
	 *
	 *	This method reset the builder on the first vertex.<br>
	 *	This method is usefull if you don't want to instanciate a vertex builder
	 *	many times with the same vertices array. 
	 */
	void	VertexBuilder::clear()
	{
		m_used = 0;
	}

	/*!	Get the vertices count which have to be drawn */
	std::size_t VertexBuilder::getUsed()const
	{
		return (m_used);
	}

	bool	VertexBuilder::isNull()const
	{
		return (m_vertices == nullptr);
	}

	/*!	Make a range of null vertex
	 *
	 *	\warning This function admits that the array \a vertices contains at least \a count elements
	 */
	void	VertexBuilder::makeNull(sf::Vertex* vertices, std::size_t count)
	{
		std::size_t	i = 0u;

		while (i < count)
			vertices[++i] = sf::Vertex();
	}

	/*!	Make a line
	 *
	 *	\warning This function admits that the array \a vertices contains at least 6 elements
	 */
	void	VertexBuilder::makeLine(sf::Vertex* vertices,
									sf::Vector2f const& p0,
									sf::Vector2f const& p1,
									float thickness,
									sf::Color const& color)
	{
		sf::Vector2f	p;
		float			halfThickness = thickness * .5f;

		p = computeNormale(p1 - p0);
		normalize(p);
		p *= halfThickness;
		makeQuad(vertices, p0 - p, p0 + p, p1 + p, p1 - p, color);
	}

	/*!	Make a triangle
	 *
	 *	\warning This function admits that the array \a vertices contains at least 3 elements
	 */
	void	VertexBuilder::makeTriangle(sf::Vertex* vertices, sf::Vector2f const& p0, sf::Vector2f const& p1,
							 			sf::Vector2f const& p2, sf::Color const& color)
	{
		vertices[0].position = p0;
		vertices[1].position = p1;
		vertices[2].position = p2;
		vertices[0].color = color;
		vertices[1].color = color;
		vertices[2].color = color;
	}

	/*!	Make a quad
	 *
	 *	\warning This function admits that the array \a vertices contains at least 6 elements
	 */
	void	VertexBuilder::makeQuad(sf::Vertex* vertices, sf::Vector2f const& p0, sf::Vector2f const& p1,
						 			sf::Vector2f const& p2, sf::Vector2f const& p3, sf::Color const& color)
	{
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
	}
}
