/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Palette.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/19 21:14:41 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/20 18:01:35 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Palette.hpp"

#include <stdexcept>
#include <string>

namespace octo
{
	Palette::Palette(std::size_t colorCount, std::size_t variatorCount) :
		m_colors(new Hsv[colorCount]),
		m_variators(new Variator[variatorCount]),
		m_colorCount(colorCount),
		m_variatorCount(variatorCount)
	{
	}
	
	void		Palette::set(std::size_t colorId, Hsv const& color)
	{
		if (colorId >= m_colorCount)
			throw std::out_of_range("palette: set: invalid color id: " + std::to_string(colorId));
		m_colors[colorId] = color;
	}

	void		Palette::set(std::size_t variationId, Variator variator)
	{
		if (variationId >= m_variatorCount)
			throw std::out_of_range("palette: set: invalid variator id: " + std::to_string(variationId));
		m_variators[variationId] = variator;
	}

	sf::Color	Palette::get(std::size_t colorId)const
	{
		if (colorId >= m_colorCount)
			throw std::out_of_range("palette: get: invalid color id: " + std::to_string(colorId));
		return (m_colors[colorId].toRgba());
	}

	sf::Color	Palette::get(std::size_t colorId, std::size_t variationId)const
	{
		if (colorId >= m_colorCount)
			throw std::out_of_range("palette: get: invalid color id: " + std::to_string(colorId));
		if (variationId >= m_variatorCount)
			throw std::out_of_range("palette: get: invalid variation id: " + std::to_string(variationId));
		return (m_variators[variationId](m_colors[colorId]).toRgba());
	}

	std::size_t	Palette::getColorCount()const
	{
		return (m_colorCount);
	}

	std::size_t	Palette::getVariationCount()const
	{
		return (m_variatorCount);
	}
}
