/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PausableClock.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/24 20:25:59 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/24 20:41:01 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PausableClock.hpp"

namespace octo
{
	PausableClock::PausableClock() :
		m_run(false)
	{
	}

	sf::Time	PausableClock::restart()
	{
		sf::Time	result = getElapsedTime();
		
		m_run = true;
		m_buffer = sf::Time::Zero;
		m_clock.restart();
		return (result);
	}

	void		PausableClock::pause()
	{
		if (m_run)
		{
			m_run = false;
			m_buffer += m_clock.getElapsedTime();
		}
	}

	void		PausableClock::resume()
	{
		if (m_run == false)
		{
			m_clock.restart();
			m_run = true;
		}
	}

	sf::Time	PausableClock::getElapsedTime()const
	{
		if (m_run)
			return (m_clock.getElapsedTime() + m_buffer);
		else
			return (m_buffer);
	}
}
