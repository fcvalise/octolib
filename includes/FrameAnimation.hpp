/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FrameAnimation.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 20:24:50 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/13 16:58:23 by irabeson         ###   ########.fr       */
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
	class FrameAnimation : public IAnimation<T>
	{
		struct	PrivateFrame;
		struct	SetupFrames;
	public:
		struct Frame;
		
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

		LoopMode					m_loopMode;
		std::vector<PrivateFrame>	m_frames;
		sf::Time					m_duration;
	};	
}

#include "FrameAnimation.hxx"
#endif
