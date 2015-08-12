/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CharacterAnimation.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 16:01:49 by irabeson          #+#    #+#             */
/*   Updated: 2015/07/20 16:09:21 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CharacterAnimation.hpp"
#include "ByteArray.hpp"
#include "BinaryInputStream.hpp"

namespace octo
{
	bool	CharacterAnimation::loadFromMemory(ByteArray const& buffer)
	{
		BinaryInputStream	is(buffer);
		std::uint32_t		frameCount = 0u;
		std::uint64_t		frameDuration = 0u;
		CharacterFrame		frameValue;
		LoopMode			loopMode = LoopMode::NoLoop;
		std::vector<Frame>	frames;

		is.read(loopMode);
		is.read(frameCount);
		for (std::uint32_t i = 0; i < frameCount; ++i)
		{
			frameValue.loadFromMemory(is);
			is.read(frameDuration);
			frames.emplace_back(sf::microseconds(frameDuration), frameValue);
		}
		setFrames(frames);
		return (true);
	}
}
