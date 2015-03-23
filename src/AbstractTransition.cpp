/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractTransition.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 00:24:47 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/23 15:55:26 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractTransition.hpp"

namespace octo
{
	AbstractTransition::AbstractTransition(sf::View const& view, Action action) :
		m_view(view),
		m_inDuration(0.f),
		m_outDuration(0.f),
		m_currentTime(0.f),
		m_action(action),
		m_status(Status::In)
	{
	}

	AbstractTransition::~AbstractTransition()
	{
	}

	void	AbstractTransition::setDuration(float in, float out)
	{
		m_inDuration = in;
		m_outDuration = out;
	}

	bool	AbstractTransition::update(float frameTime)
	{
		switch (m_status)
		{
			case Status::In:
				if (m_currentTime >= m_inDuration)
				{
					m_action();
					m_currentTime = m_outDuration;
					m_status = Status::Out;
				}
				else
				{
					updateTransition(frameTime, m_currentTime / m_inDuration);	
					m_currentTime += frameTime;
				}
				break;
			case Status::Out:
				if (m_currentTime <= 0.f)
				{
					m_status = Status::Finished;
					return (false);
				}
				else
				{
					updateTransition(frameTime, m_currentTime / m_outDuration);	
					m_currentTime -= frameTime;
				}
				break;
			case Status::Finished:
				break;
			default:
				break;
		}
		return (true);
	}
	
	sf::View const&	AbstractTransition::view()const
	{
		return (m_view);
	}

	AbstractTransition::Status	AbstractTransition::status()const
	{
		return (m_status);
	}
}
