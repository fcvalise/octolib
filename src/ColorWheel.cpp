/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ColorWheel.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/30 01:36:36 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/06 04:51:53 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ColorWheel.hpp"
#include "BinaryInputStream.hpp"
#include "BinaryOutputStream.hpp"
#include <algorithm>
#include <stdexcept>

namespace octo
{
	ColorWheel::ColorWheel() :
		m_hue(0u),
		m_offsets(nullptr),
		m_offsetCount(0u)
	{
	}

	ColorWheel::ColorWheel(int hue, std::initializer_list<std::int16_t> offsets) :
		m_hue(hue),
		m_offsets(nullptr),
		m_offsetCount(0u)
	{
		std::size_t	i = 0u;

		resize(offsets.size());
		for (auto offset : offsets)
		{
			m_offsets[i] = HueOffset(offset);
			++i;
		}
	}

	void	ColorWheel::resize(std::size_t count)
	{
		if (m_offsetCount == count)
			return;
		std::unique_ptr<HueOffset[]>	offsets(new HueOffset[count]);
		std::uint64_t					copyCount = std::min<std::uint64_t>(m_offsetCount, count);
		
		for (std::size_t i = 0u; i < copyCount; ++i)
		{
			offsets[i] = m_offsets[i];
		}
		std::swap(m_offsets, offsets);
		m_offsetCount = count;
	}

	void		ColorWheel::setBaseHue(std::uint16_t hue)
	{
		m_hue = hue;
	}

	sf::Color	ColorWheel::getColor(std::size_t id)const
	{
		if (id >= m_offsetCount)
			throw std::range_error("color wheel: set offset: invalid offset identifier: " + std::to_string(id));
		std::int16_t	offset = m_offsets[id].hueOffset;

		if (offset < 0 && m_hue < std::abs(offset) )
		{
			offset += 360;
		}
		else if (offset > 0 && m_hue + offset > 359)
		{
			offset -= 360;
		}
		Hsv	result(m_hue + offset, m_offsets[id].saturation, m_offsets[id].value, m_offsets[id].alpha);

		return (result.toRgba());
	}

	std::size_t	ColorWheel::getColorCount()const
	{
		return (m_offsetCount);
	}

	bool		ColorWheel::loadFromMemory(ByteArray const& buffer)
	{
		std::unique_ptr<HueOffset[]>	offsets;
		BinaryInputStream				is(buffer);
		std::uint64_t					count = 0u;
		std::uint64_t					i = 0u;
		HueOffset						offset;

		if (!is)
			return (false);
		is.read(m_hue);
		is.read(count);
		if (!is)
			return (false);
		offsets.reset(new HueOffset[count]);
		while (is && i < count)
		{
			is.read(offset.hueOffset);
			is.read(offset.saturation);
			is.read(offset.value);
			is.read(offset.alpha);
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

		os.write(m_hue);
		os.write(m_offsetCount);
		for (std::uint64_t i = 0u; i < m_offsetCount; ++i)
		{
			os.write(m_offsets[i].hueOffset);
			os.write(m_offsets[i].saturation);
			os.write(m_offsets[i].value);
			os.write(m_offsets[i].alpha);
		}
		return (true);
	}
}
