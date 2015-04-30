/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hsv.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/19 20:41:59 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/30 04:24:41 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Hsv.hpp"
#include <cmath>
#include <limits>

#include <iostream>			// TEST
#include "PrintSFML.hpp"	// TEST

namespace octo
{
	Hsv::Hsv() :
		m_hue(0u),
		m_saturation(0u),
		m_value(0u),
		m_alpha(255u)
	{
	}

	Hsv::Hsv(std::uint16_t hue, std::uint8_t saturation, std::uint8_t value, std::uint8_t alpha) :
		m_hue(hue),
		m_saturation(saturation),
		m_value(value),
		m_alpha(alpha)
	{
	}

	std::uint16_t	Hsv::getHue()const
	{
		return (m_hue);
	}

	std::uint8_t	Hsv::getSaturation()const
	{
		return (m_saturation);
	}

	std::uint8_t	Hsv::getValue()const
	{
		return (m_value);
	}

	std::uint8_t	Hsv::getAlpha()const
	{
		return (m_alpha);
	}
	
	void	Hsv::setHue(std::uint16_t hue)
	{
		m_hue = hue;
	}

	void	Hsv::setSaturation(std::uint8_t saturation)
	{
		m_saturation = saturation;
	}

	void	Hsv::setValue(std::uint8_t value)
	{
		m_value = value;
	}

	void	Hsv::setAlpha(std::uint8_t alpha)
	{
		m_alpha = alpha;
	}

	sf::Color	Hsv::toRgba()const
	{
		float			hue = (m_hue / 60.f);
		std::uint16_t	hueSector = static_cast<std::uint16_t>(hue);
		float			hueFractional = hue - hueSector;
		float			value = m_value * (1.f / 255.f);
		std::uint8_t	components[3] =
		{
			static_cast<std::uint8_t>(value * (255 - m_saturation)),
			static_cast<std::uint8_t>(value * (255 - m_saturation * hueFractional)),
			static_cast<std::uint8_t>(value * (255 - m_saturation * (1.f - hueFractional)))
		};
		sf::Color		result;

		if (m_saturation == 0u)
		{
			result.r = m_value;
			result.g = m_value;
			result.b = m_value;
		}
		else
		{
			switch (hueSector)
			{
				case 0:
					result.r = m_value;
					result.g = components[2];
					result.b = components[0];
					break;
				case 1:
					result.r = components[1];
					result.g = m_value;
					result.b = components[0];
					break;
				case 2:
					result.r = components[0];
					result.g = m_value;
					result.b = components[2];
					break;
				case 3:
					result.r = components[0];
					result.g = components[1];
					result.b = m_value;
					break;
				case 4:
					result.r = components[2];
					result.g = components[0];
					result.b = m_value;
					break;
				case 5:
					result.r = m_value;
					result.g = components[0];
					result.b = components[1];
					break;
				default:
					break;
			}
		}
		result.a = m_alpha;
		return (result);
	}
	
	std::uint16_t&	Hsv::hue()
	{
		return (m_hue);
	}

	std::uint8_t&	Hsv::saturation()
	{
		return (m_saturation);
	}

	std::uint8_t&	Hsv::value()
	{
		return (m_value);
	}
	
	std::uint8_t&	Hsv::alpha()
	{
		return (m_alpha);
	}
}
