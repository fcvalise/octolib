/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractAnimator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 17:11:16 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/23 17:24:26 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTANIMATOR_HPP
# define ABSTRACTANIMATOR_HPP
# include "AnimableProperty.hpp"
# include "IAnimation.hpp"
# include <SFML/System/Time.hpp>

namespace octo
{
	/*!
	 *	\ingroup Animation
	 *	\brief Play status
	 *
	 */
	enum class PlayStatus
	{
		Stop,
		Play,
		Pause
	};

	/*!
	 *	\ingroup Animation
	 *	\class AbstractAnimator
	 *	\brief Base of animators
	 */
	template <class T>
	class AbstractAnimator
	{
	public:
		explicit AbstractAnimator(AnimableProperty<T> const& property);

		/*!	Update the animator states */
		void							update(sf::Time frameTime);

		/*!	Reset time to zero */
		void							reset();

		/*!	Reset time to zero and restart animation */
		void							restart();

		/*!	Start the animation */
		void							play();

		/*!	Stop the animation and reset time to zero */
		void							stop();

		/*!	Pause the animation */
		void							pause();

		/*!	Return play status */
		PlayStatus						getStatus()const;
		bool							isTerminated()const;

		/*!	Define the speed factor */
		void							setSpeedFactor(float factor);
	private:
		virtual IAnimation<T> const&	getCurrentAnimation()const = 0;
		void							applyCurrentValue();
	private:
		sf::Time			m_currentTime;
		PlayStatus			m_status;
		AnimableProperty<T>	m_property;
		float				m_speedFactor;
		T const*			m_lastValue;
	};
}

#include "AbstractAnimator.hxx"
#endif
