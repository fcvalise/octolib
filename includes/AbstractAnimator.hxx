/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractAnimator.hxx                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/23 14:55:23 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/23 17:12:05 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractAnimator.hpp"

namespace octo
{
	template <class T>
	AbstractAnimator<T>::AbstractAnimator(AnimableProperty<T> const& property) :
		m_property(property),
		m_speedFactor(1.f),
		m_lastValue(nullptr)
	{
	}

	template <class T>
	void	AbstractAnimator<T>::update(sf::Time frameTime)
	{
		if (m_status != PlayStatus::Play)
			return;
		IAnimation<T> const&	animation = getCurrentAnimation();
		sf::Time				duration = animation.duration();

		m_currentTime += frameTime * m_speedFactor;
		if (m_currentTime >= duration)
		{
			if (animation.loopMode() == LoopMode::Loop)
			{
				m_currentTime -= duration;
			}
		}
		applyCurrentValue();
	}

	template <class T>
	void	AbstractAnimator<T>::reset()
	{
		m_currentTime = sf::Time::Zero;
	}

	template <class T>
	void	AbstractAnimator<T>::restart()
	{
		m_currentTime = sf::Time::Zero;
		m_status = PlayStatus::Play;
	}

	template <class T>
	void	AbstractAnimator<T>::play()
	{
		if (m_status == PlayStatus::Stop)
		{
			m_currentTime = sf::Time::Zero;
			m_lastValue = nullptr;
		}
		m_status = PlayStatus::Play;
		applyCurrentValue();
	}

	template <class T>
	void	AbstractAnimator<T>::stop()
	{
		m_status = PlayStatus::Stop;
		m_currentTime = sf::Time::Zero;
		m_lastValue = nullptr;
		applyCurrentValue();
	}

	template <class T>
	void	AbstractAnimator<T>::pause()
	{
		m_status = PlayStatus::Pause;
	}

	template <class T>
	PlayStatus	AbstractAnimator<T>::getStatus()const
	{
		return (m_status);
	}

	template <class T>
	void	AbstractAnimator<T>::setSpeedFactor(float factor)
	{
		m_speedFactor = factor;
	}

	template <class T>
	void	AbstractAnimator<T>::applyCurrentValue()
	{
		IAnimation<T> const&	animation = getCurrentAnimation();
		T const&				value = animation.value(m_currentTime);
		
		if (m_lastValue == nullptr || *m_lastValue != value)
		{
			m_property.setValue(animation.value(m_currentTime));
			m_lastValue = &value;
		}
	}
}
