/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SpriteSheet.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 18:36:32 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/13 22:57:30 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITESHEET_HPP
# define SPRITESHEET_HPP
# include <SFML/Graphics/Texture.hpp>
# include <SFML/Graphics/Rect.hpp>

namespace octo
{
	class ByteArray;

	/*!
	 *	\ingroup Graphics
	 *	\class SpriteSheet
	 *	\brief Sprite sheet
	 *
	 *	A sprite sheet is a ressource combining a texture and a set of sub-rectangles.
	 */
	class SpriteSheet
	{
	public:
		sf::Texture const&		getTexture()const;
		sf::FloatRect const&	getSubRect(std::size_t i)const;
		std::size_t				getSubRectCount()const;
		bool					loadFromMemory(ByteArray const& buffer);
	private:
		sf::Texture						m_texture;
		std::vector<sf::FloatRect>		m_subRects;
	};
}

#endif
