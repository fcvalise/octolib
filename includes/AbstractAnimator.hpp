/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractAnimator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 17:11:16 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/13 18:25:48 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTANIMATOR_HPP
# define ABSTRACTANIMATOR_HPP

namespace octo
{
	enum class PlayStatus
	{
		Stop,
		Play,
		Pause
	};

	template <class T>
	class AbstractAnimator
	{
	public:
		explicit AnimableProperty(AnimableProperty<T> const& property) :
			m_property(property)
		{
		}

		void							update(sf::Time frameTime)
		{
			if (m_status != PlayStatus::Play)
				return;
			IAnimation<T> const&	animation = getCurrentAnimation();
			sf::Time				duration = animation.duration();

			m_currentTime += frameTime;
			if (m_currentTime >= duration)
			{
				if (animation.loopMode() == LoopMode::Loop)
				{
					m_currentTime -= duration;
				}
			}
			applyCurrentValue();
		}

		void							restart()
		{
			m_currentTime = sf::Time::Zero;
			m_status = PlayStatus::Play;
		}

		void							play()
		{
			if (m_status == PlayStatus::Stop)
				m_currentTime = sf::Time::Zero;
			m_status = PlayStatus::Play;
		}

		void							stop()
		{
			m_status = PlayStatus::Stop;
		}

		void							pause()
		{
			m_status = PlayStatus::Pause;
		}

		PlayStatus						getStatus()const
		{
			return (m_status);
		}
	private:
		virtual IAnimation<T> const&	getCurrentAnimation()const = 0;

		void							applyCurrentValue()
		{
			IAnimation<T> const&	animation = getCurrentAnimation();

			m_property(animation->value(m_currentTime));
		}
	private:
		sf::Time			m_currentTime;
		PlayStatus			m_status;
		AnimableProperty<T>	m_property;
	};
}

#endif
