/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VertexBuilder.hpp                                   :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/08 05:04:37 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/19 05:35:16 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTEXBUILDER_HPP
# define VERTEXBUILDER_HPP
# include <SFML/System/Vector2.hpp>
# include <SFML/Graphics/Color.hpp>
# include <SFML/Graphics/Vertex.hpp>
# include <cstddef>
# include <vector>

namespace octo
{
	/*!
	 *	\ingroup Graphics
	 *	\class VertexBuilder
	 *	\brief Build primitives in a vertex array
	 *
	 *	VertexBuilder takes an array of vertices and
	 *	builds primitives with his vertex.<br>
	 *
	 *	The total of vertices used can be obtained with getUsed().<br>
	 *	The vertex array builded must be rendered as triangle.
	 *
	 *	\code
	 *	sf::Vertex*			vertices = new sf::Vertex[42];
	 *	VertexBuilder		builder(vertices, 42);
	 *	sf::RenderWindow	render;
	 *
	 *	builder.createTriangle( ... );
	 *	builder.createQuad( ... );
	 *
	 *	// Draw only vertices used
	 *	render.draw(vertices, builder.getUsed(), sf::Triangles);
	 *	\endcode
	 */
	class VertexBuilder
	{
	public:
		static void	makeNull(sf::Vertex* vertices, std::size_t count);

		static void	makeLine(sf::Vertex* vertices,
							 sf::Vector2f const& p0,
							 sf::Vector2f const& p1,
							 float thickness,
							 sf::Color const& color);

		static void	makeTriangle(sf::Vertex* vertices,
								 sf::Vector2f const& p0,
								 sf::Vector2f const& p1,
								 sf::Vector2f const& p2,
								 sf::Color const& color);

		static void	makeQuad(sf::Vertex* vertices,
							 sf::Vector2f const& p0,
							 sf::Vector2f const& p1,
							 sf::Vector2f const& p2,
							 sf::Vector2f const& p3,
							 sf::Color const& color);

		VertexBuilder();
		VertexBuilder(sf::Vertex* vertices, std::size_t count);
		VertexBuilder(VertexBuilder&& other) = default;
		VertexBuilder& operator = (VertexBuilder&& other) = default;

		void		createVertex(sf::Vector2f const& pos, sf::Color const& color);

		void		createLine(sf::Vector2f const& p0,
							   sf::Vector2f const& p1,
							   float thickness,
							   sf::Color const& color);

		void		createTriangle(sf::Vector2f const& p0,
								   sf::Vector2f const& p1,
								   sf::Vector2f const& p2,
								   sf::Color const& color);

		void		createQuad(sf::Vector2f const& p0,
							   sf::Vector2f const& p1,
							   sf::Vector2f const& p2,
							   sf::Vector2f const& p3,
							   sf::Color const& color);

		void		createVertices(std::vector<sf::Vertex> const& vertices);
		
		void		clear();
		std::size_t	getUsed()const;
		bool		isNull()const;
	private:
		sf::Vertex* m_vertices;
		std::size_t	m_size;
		std::size_t	m_used;
	};
}

#endif
