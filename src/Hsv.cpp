/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hsv.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/19 20:41:59 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/20 18:14:38 by irabeson         ###   ########.fr       */
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
		m_hue(0),
		m_saturation(0.f),
		m_value(0.f),
		m_alpha(1.f)
	{
	}

	Hsv::Hsv(int hue, float saturation, float value, float alpha) :
		m_hue(hue),
		m_saturation(saturation),
		m_value(value),
		m_alpha(alpha)
	{
	}

	int	Hsv::getHue()const
	{
		return (m_hue);
	}

	float	Hsv::getSaturation()const
	{
		return (m_saturation);
	}

	float	Hsv::getValue()const
	{
		return (m_value);
	}

	float	Hsv::getAlpha()const
	{
		return (m_alpha);
	}
	
	void	Hsv::setHue(int hue)
	{
		m_hue = hue;
	}

	void	Hsv::setSaturation(float saturation)
	{
		m_saturation = saturation;
	}

	void	Hsv::setValue(float value)
	{
		m_value = value;
	}

	void	Hsv::setAlpha(float alpha)
	{
		m_alpha = alpha;
	}

	sf::Color	Hsv::toRgba()const
	{
		float		hue = (m_hue / 60.f);
		int			hueSector = static_cast<int>(hue);
		float		hueFractional = hue - hueSector;
		float		components[3] =
		{
			m_value * (1.f - m_saturation),
			m_value * (1.f - m_saturation * hueFractional),
			m_value * (1.f - m_saturation * (1.f - hueFractional))
		};
		sf::Color	result;

		std::cout << m_hue << ";" << m_saturation << ";" << m_value << " = ";
		if (std::fabs(m_saturation) < std::numeric_limits<float>::epsilon())
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
					result.r = m_value * 255;
					result.g = components[2] * 255;
					result.b = components[0] * 255;
					break;
				case 1:
					result.r = components[1] * 255;
					result.g = m_value * 255;
					result.b = components[0] * 255;
					break;
				case 2:
					result.r = components[0] * 255;
					result.g = m_value * 255;
					result.b = components[2] * 255;
					break;
				case 3:
					result.r = components[0] * 255;
					result.g = components[1] * 255;
					result.b = m_value * 255;
					break;
				case 4:
					result.r = components[2] * 255;
					result.g = components[0] * 255;
					result.b = m_value * 255;
					break;
				case 5:
					result.r = m_value * 255;
					result.g = components[0] * 255;
					result.b = components[1] * 255;
					break;
				default:
					break;
			}
		}
		result.a = m_alpha * 255;
		std::cout << result << std::endl;
		return (result);
	}
	
	int&	Hsv::hue()
	{
		return (m_hue);
	}

	float&	Hsv::saturation()
	{
		return (m_saturation);
	}

	float&	Hsv::value()
	{
		return (m_value);
	}
}
