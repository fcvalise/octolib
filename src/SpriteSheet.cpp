/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SpriteSheet.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 18:55:13 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/23 00:52:32 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SpriteSheet.hpp"
#include "ByteArray.hpp"
#include "BinaryInputStream.hpp"

namespace octo
{
	sf::Texture const&	SpriteSheet::getTexture()const
	{
		return (m_texture);
	}

	sf::FloatRect const&	SpriteSheet::getSubRect(std::size_t i)const
	{
		return (m_subRects.at(i));
	}

	std::size_t	SpriteSheet::getSubRectCount()const
	{
		return (m_subRects.size());
	}

	bool	SpriteSheet::loadFromMemory(ByteArray const& buffer)
	{
		BinaryInputStream			is(buffer);
		std::vector<sf::FloatRect>	rects;
		sf::Texture					texture;
		std::uint32_t				textureByteCount = 0u;
		std::uint32_t				rectangleCount = 0u;
		std::uint32_t				posX = 0u;
		std::uint32_t				posY = 0u;
		std::uint32_t				width = 0u;
		std::uint32_t				height = 0u;

		is.read(textureByteCount);
		if (texture.loadFromMemory(buffer.bytes() + is.getPosition(), textureByteCount) == false)
			return (false);
		is.skip(textureByteCount);
		is.read(width, height, rectangleCount);
		for (std::uint32_t i = 0u; i < rectangleCount; ++i)
		{
			is.read(posX, posY);
			rects.push_back(sf::FloatRect(posX, posY, width, height));
		}
		std::swap(m_texture, texture);
		std::swap(m_subRects, rects);
		return (true);
	}
}
