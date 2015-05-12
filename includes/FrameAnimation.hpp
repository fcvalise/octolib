/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FrameAnimation.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 20:24:50 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/11 01:11:47 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAMEANIMATION_HPP
# define FRAMEANIMATION_HPP
# include "IAnimation.hpp"

# include <SFML/System/Time.hpp>

# include <vector>

namespace octo
{
	template <class T>
	class FrameAnimation
	{
		struct PrivateFrame;

	public:
		struct Frame
		{
			Frame() :
				value(T())
			{
			}

			explicit Frame(sf::Time durationParam, T const& valueParam = T()) :
				duration(durationParam),
				value(valueParam)
			{
			}

			sf::Time	duration;
			T			value;
		};
		
		typedef std::vector<Frame>	FrameList;

		FrameAnimation();

		virtual T const&			value(sf::Time currentTime)const;
		virtual sf::Time			duration()const;
		virtual LoopMode			loopMode()const;
		virtual bool				loadFromMemory(char* data, std::size_t count);
		virtual bool				loadFromFile(std::string const& fileName);
		virtual bool				saveToFile(std::string const& fileName)const;

		void						setFrames(std::vector<Frame> const& frames);
		sf::Time					getFrameDuration(std::size_t i)const;
		T							getFrameValue(std::size_t i)const;
	private:
		PrivateFrame const&			binarySearch(PrivateFrame const& start)const;
	private:
		struct PrivateFrame
		{
			explicit PrivateFrame(sf::Time startParam) :
				start(startParam)
			{
			}

			explicit PrivateFrame(Frame const& other) :
				duration(other.duration),
				value(other.value)
			{
			}

			bool	operator == (PrivateFrame const& other)const
			{
				return (start == other.start);
			}

			bool	operator < (PrivateFrame const& other)const
			{
				return (start < other.start);
			}

			sf::Time	start;		// Only for binary search
			sf::Time	duration;
			T			value;
		};

		/*!	Compute start value of each frame */
		struct	SetupFrames
		{
			void	operator()(PrivateFrame& frame)
			{
				frame.start = m_currentStart;
				m_currentStart += frame.duration;
			}

			operator sf::Time () const
			{
				return (m_currentStart);
			}
		private:
			sf::Time	m_currentStart;
		};

		struct	FindFrameByTime
		{
			bool	operator()(PrivateFrame const& left, PrivateFrame const& right)
			{
				return (left.start < right.start);
			}
		};

		LoopMode					m_loopMode;
		std::vector<PrivateFrame>	m_frames;
		sf::Time					m_duration;
	};	
}

#include "FrameAnimation.hxx"
#endif
