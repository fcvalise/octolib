/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CharacterFrame.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 15:42:39 by irabeson          #+#    #+#             */
/*   Updated: 2015/07/23 00:51:39 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CharacterFrame.hpp"
#include "BinaryInputStream.hpp"

namespace octo
{
	CharacterFrame::CharacterFrame() :
		m_textureRectangleId(0)
	{
	}

	CharacterFrame::CharacterFrame(std::size_t textureRectangleId, sf::FloatRect const& box, sf::Vector2f const& hotPoint) :
		m_box(box),
		m_hotPoint(hotPoint),
		m_textureRectangleId(textureRectangleId)
	{
	}

	void	CharacterFrame::loadFromMemory(BinaryInputStream& is)
	{
		sf::Rect<std::uint32_t>		box;
		sf::Vector2<std::uint32_t>	hotPoint;
		std::uint32_t				textureRectangleId;

		is.read<std::uint32_t>(box.left);
		is.read<std::uint32_t>(box.top);
		is.read<std::uint32_t>(box.width);
		is.read<std::uint32_t>(box.height);
		is.read<std::uint32_t>(hotPoint.x);
		is.read<std::uint32_t>(hotPoint.y);
		is.read<std::uint32_t>(textureRectangleId);
		m_box = sf::FloatRect(box);
		m_hotPoint = sf::Vector2f(hotPoint);
		m_textureRectangleId = std::move(textureRectangleId);
	}

	sf::FloatRect const&	CharacterFrame::getBox()const
	{
		return (m_box);
	}

	sf::Vector2f const&		CharacterFrame::getHotPoint()const
	{
		return (m_hotPoint);
	}

	std::size_t				CharacterFrame::getTextureRectangleId()const
	{
		return (m_textureRectangleId);
	}
}
