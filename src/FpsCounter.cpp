/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FpsCounter.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 00:50:31 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/05 02:39:05 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FpsCounter.hpp"
#include "AbstractFpsDisplayer.hpp"

namespace octo
{
	namespace
	{
		static sf::Time const	OneSecond = sf::seconds(1);
	}

	FpsCounter::FpsCounter() :
		m_frameCount(0),
		m_enabled(false),
		m_displayer(nullptr)
	{
	}

	void	FpsCounter::setDisplay(AbstractFpsDisplayer* displayer)
	{
		m_displayer = displayer;
	}

	void	FpsCounter::setEnabled(bool enabled)
	{
		m_enabled = enabled;
	}

	void	FpsCounter::update(sf::Time frameTime)
	{
		if (m_enabled == false || m_displayer == nullptr)
			return;
		++m_frameCount;
		m_currentTime += frameTime;
		if (m_currentTime >= OneSecond)
		{
			m_displayer->addSample(m_frameCount);
			m_frameCount = 0;
			m_currentTime -= OneSecond;
		}
	}
}
