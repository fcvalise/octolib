/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SpriteSheet.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 18:55:13 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/13 22:53:58 by irabeson         ###   ########.fr       */
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
		std::uint32_t				textureByteCount = 0u;
		std::uint32_t				rectangleCount = 0u;
		BinaryInputStream			is(buffer);
		sf::FloatRect				rect;
		std::vector<sf::FloatRect>	rects;
		sf::Texture					texture;

		is.read(textureByteCount);
		if (texture.loadFromMemory(buffer.bytes() + is.getPosition(), textureByteCount) == false)
			return (false);
		is.skip(textureByteCount);
		is.read(rectangleCount);
		for (std::uint32_t i = 0u; i < rectangleCount; ++i)
		{
			is.read(rect.left, rect.top, rect.width, rect.height);
			rects.push_back(rect);
		}
		std::swap(m_texture, texture);
		std::swap(m_subRects, rects);
		return (true);
	}
}
