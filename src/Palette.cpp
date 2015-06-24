/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Palette.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/19 21:14:41 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/24 18:06:23 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Palette.hpp"
#include "BinaryInputStream.hpp"
#include "BinaryOutputStream.hpp"

#include <stdexcept>
#include <string>
#include <algorithm>

namespace octo
{
	Palette::Palette() :
		m_colors(nullptr),
		m_colorCount(0u)
	{
	}

	Palette::Palette(std::initializer_list<sf::Color> colors) :
		m_colors(nullptr),
		m_colorCount(0u)
	{
		std::size_t	i = 0;

		resize(colors.size());
		for (sf::Color const& color : colors)
		{
			m_colors[i] = color;
			++i;
		}
	}

	void	Palette::resize(std::size_t count)
	{
		if (m_colorCount == count)
			return;
		std::unique_ptr<sf::Color[]>	colors(new sf::Color[count]);
		std::uint64_t					copyCount = std::min<std::uint64_t>(m_colorCount, count);

		for (std::size_t i = 0u; i < copyCount; ++i)
		{
			colors[i] = m_colors[i];
		}
		std::swap(m_colors, colors);
		m_colorCount = count;
	}

	sf::Color	Palette::getColor(std::size_t id)const
	{
		if (id >= m_colorCount)
			throw std::range_error("palette: get color: invalid color identifier: " + std::to_string(id));
		return (m_colors[id]);
	}

	std::size_t	Palette::getColorCount()const
	{
		return (m_colorCount);
	}

	bool	Palette::loadFromMemory(ByteArray const& buffer)
	{
		std::unique_ptr<sf::Color[]>	colors;
		BinaryInputStream				is(buffer);
		sf::Color						color;
		std::uint64_t					count = 0u;
		std::uint64_t					i = 0u;

		if (!is)
			return (false);
		is.read(count);
		if (!is)
			return (false);
		colors.reset(new sf::Color[count]);
		while (is && i < count)
		{
			is.read(color.r, color.g, color.b, color.a);
			colors[i] = color;
			++i;
		}
		std::swap(m_colors, colors);
		m_colorCount = count;
		return (true);
	}

	bool	Palette::saveToMemory(ByteArray& buffer)const
	{
		BinaryOutputStream				os(buffer);

		os.write(m_colorCount);
		for (std::uint64_t i = 0u; i < m_colorCount; ++i)
		{
			sf::Color const&	color = m_colors[i];

			os.write(color.r, color.g, color.b, color.a);
		}
		return (true);
	}
}
