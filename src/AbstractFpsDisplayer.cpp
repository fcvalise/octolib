/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractFpsDisplayer.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 02:05:31 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/06 11:28:14 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractFpsDisplayer.hpp"
#include <iostream>

namespace octo
{
	AbstractFpsDisplayer::AbstractFpsDisplayer(std::size_t maxSamples) :
		m_samples(maxSamples),
		m_maxSamples(maxSamples),
		m_maxFrameCount(0u),
		m_lastSample(0u),
		m_averageBuffer(0u),
		m_averageCount(0u)
	{
	}

	unsigned int	AbstractFpsDisplayer::getLastSample()const
	{
		return (m_lastSample);
	}

	unsigned int	AbstractFpsDisplayer::getAverage()const
	{
		if (m_averageCount == 0u)
			return (0u);
		return (m_averageBuffer / m_averageCount);
	}

	unsigned int	AbstractFpsDisplayer::getMaxSamples()const
	{
		return (m_maxSamples);
	}

	void	AbstractFpsDisplayer::addSample(unsigned int frameCount)
	{
		if (m_samples.size() == m_maxSamples)
			m_samples.pop();
		m_samples.push(frameCount);
		if (frameCount > m_maxFrameCount)
			m_maxFrameCount = frameCount;
		m_lastSample = frameCount;
		m_averageBuffer += frameCount;
		++m_averageCount;
		updateDisplay(m_samples, m_maxFrameCount);
	}
}
