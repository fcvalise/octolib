/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractFrameAnimation.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/23 14:10:56 by irabeson          #+#    #+#             */
/*   Updated: 2015/07/03 17:23:19 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTFRAMEANIMATION_HPP
# define ABSTRACTFRAMEANIMATION_HPP
# include "IAnimation.hpp"

# include <SFML/System/Time.hpp>

# include <vector>
# include <initializer_list>

namespace octo
{
	/*!
	 *	\ingroup Animation
	 *	\brief Base of frame by frame animations
	 *
	 */
	template <class T>
	class AbstractFrameAnimation : public IAnimation<T>
	{
		struct	PrivateFrame;
		struct	SetupFrames;
	public:
		struct 						Frame;
		typedef std::vector<Frame>	FrameList;

		AbstractFrameAnimation();

		virtual T const&			value(sf::Time currentTime)const;
		virtual sf::Time			duration()const;
		virtual LoopMode			loopMode()const;
		virtual bool				loadFromMemory(ByteArray const& buffer) = 0;

		void						setFrames(std::vector<Frame> const& frames);
		void						setFrames(std::initializer_list<Frame> const& frames);
		void						setLoop(LoopMode mode);
		sf::Time					getFrameDuration(std::size_t i)const;
		T const&					getFrameValue(std::size_t i)const;
	private:
		PrivateFrame const&			binarySearch(PrivateFrame const& start)const;
	private:
		LoopMode					m_loopMode;
		std::vector<PrivateFrame>	m_frames;
		sf::Time					m_duration;
	};	
}

#include "AbstractFrameAnimation.hxx"
#endif
