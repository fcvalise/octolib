/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ColorWheel.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/30 01:36:36 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/30 04:40:45 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ColorWheel.hpp"
#include "BinaryInputStream.hpp"
#include "BinaryOutputStream.hpp"
#include <algorithm>

namespace octo
{
	ColorWheel::ColorWheel() :
		m_offsets(nullptr),
		m_offsetCount(0u)
	{
	}

	ColorWheel::ColorWheel(Hsv const& base, std::initializer_list<std::int16_t> offsets) :
		m_colorBase(base),
		m_offsets(nullptr),
		m_offsetCount(0u)
	{
		std::size_t	i = 0u;

		resize(offsets.size());
		for (auto offset : offsets)
		{
			m_offsets[i] = offset;
			++i;
		}
	}

	void	ColorWheel::resize(std::size_t count)
	{
		if (m_offsetCount == count)
			return;
		std::unique_ptr<int16_t[]>	offsets(new std::int16_t[count]);
		std::uint64_t				copyCount = std::min<std::uint64_t>(m_offsetCount, count);
		
		for (std::size_t i = 0u; i < copyCount; ++i)
		{
			offsets[i] = m_offsets[i];
		}
		std::swap(m_offsets, offsets);
		m_offsetCount = count;
	}

	void		ColorWheel::setBaseColor(Hsv const& color)
	{
		m_colorBase = color;
	}

	sf::Color	ColorWheel::getColor(std::size_t id)const
	{
		if (id >= m_offsetCount)
			throw std::range_error("color wheel: set offset: invalid offset identifier: " + std::to_string(id));
		Hsv	result(m_colorBase.getHue() + m_offsets[id], m_colorBase.getSaturation(), m_colorBase.getValue());

		return (result.toRgba());
	}

	std::size_t	ColorWheel::getColorCount()const
	{
		return (m_offsetCount);
	}

	bool		ColorWheel::loadFromMemory(ByteArray const& buffer)
	{
		std::unique_ptr<std::int16_t[]>	offsets;
		BinaryInputStream				is(buffer);
		std::uint64_t					count = 0u;
		std::uint64_t					i = 0u;
		std::int16_t					offset;

		if (!is)
			return (false);
		is.read(m_colorBase.hue());
		is.read(m_colorBase.saturation());
		is.read(m_colorBase.value());
		is.read(m_colorBase.alpha());
		is.read(count);
		if (!is)
			return (false);
		offsets.reset(new std::int16_t[count]);
		while (is && i < count)
		{
			is.read(offset);
			offsets[i] = offset;
			++i;
		}
		std::swap(m_offsets, offsets);
		m_offsetCount = count;
		return (true);
	}

	bool		ColorWheel::saveToMemory(ByteArray& buffer)const
	{
		BinaryOutputStream				os(buffer);

		os.write(m_colorBase.getHue());
		os.write(m_colorBase.getSaturation());
		os.write(m_colorBase.getValue());
		os.write(m_colorBase.getAlpha());
		os.write(m_offsetCount);
		for (std::uint64_t i = 0u; i < m_offsetCount; ++i)
		{
			os.write(m_offsets[i]);
		}
		return (true);
	}
}
