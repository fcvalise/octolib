/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractTransition.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 00:24:47 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/31 09:01:26 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractTransition.hpp"

namespace octo
{
	AbstractTransition::AbstractTransition(Action action) :
		m_inDuration(sf::Time::Zero),
		m_outDuration(sf::Time::Zero),
		m_currentTime(sf::Time::Zero),
		m_action(action),
		m_status(Status::In)
	{
	}

	AbstractTransition::~AbstractTransition()
	{
	}

	void	AbstractTransition::setDuration(sf::Time in, sf::Time out)
	{
		m_inDuration = in;
		m_outDuration = out;
	}

	bool	AbstractTransition::update(sf::Time frameTime, sf::View const& view)
	{
		switch (m_status)
		{
			case Status::In:
				if (m_currentTime >= m_inDuration)
				{
					m_action();
					m_currentTime = m_outDuration;
					m_status = Status::Out;
					updateTransition(frameTime, 1.f, view);
				}
				else
				{
					updateTransition(frameTime, std::min(m_currentTime.asSeconds() / m_inDuration.asSeconds(), 1.f), view);
					m_currentTime += frameTime;
				}
				break;
			case Status::Out:
				if (m_currentTime.asMicroseconds() <= 0)
				{
					m_status = Status::Finished;
					updateTransition(frameTime, 0.f, view);
					return (false);
				}
				else
				{
					updateTransition(frameTime, std::max(m_currentTime.asSeconds() / m_outDuration.asSeconds(), 0.f), view);
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

	AbstractTransition::Status	AbstractTransition::status()const
	{
		return (m_status);
	}
}
