/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VertexBuilder.hpp                                   :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/08 05:04:37 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/14 21:19:10 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTEXBUILDER_HPP
# define VERTEXBUILDER_HPP
# include <SFML/System/Vector2.hpp>
# include <SFML/Graphics/Color.hpp>
# include <SFML/Graphics/Vertex.hpp>
# include <cstddef>

namespace octo
{
	class VertexBuilder
	{
	public:
		VertexBuilder(sf::Vertex* vertices, std::size_t count);

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

		std::size_t	getUsed()const;
	private:
		sf::Vertex* const 	m_vertices;
		std::size_t const	m_size;
		std::size_t			m_used;
	};
}

#endif
