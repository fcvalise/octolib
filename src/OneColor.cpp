/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OneColor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/21 22:37:47 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/21 22:40:21 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OneColor.hpp"

namespace octo
{
	OneColor::OneColor(sf::Color const& color) :
		m_color(color)
	{
	}

	void	OneColor::setColor(sf::Color const& color)
	{
		m_color = color;
	}

	sf::Color	OneColor::getColor(std::size_t)const
	{
		return (m_color);
	}

	std::size_t	OneColor::getColorCount()const
	{
		return (1u);
	}
}
