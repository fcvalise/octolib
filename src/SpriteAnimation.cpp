/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SpriteAnimation.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/23 14:37:18 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/23 15:42:18 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SpriteAnimation.hpp"
#include "ByteArray.hpp"
#include "BinaryInputStream.hpp"

namespace octo
{
	bool	SpriteAnimation::loadFromMemory(ByteArray const& buffer)
	{
		BinaryInputStream	is(buffer);
		std::uint32_t		frameCount = 0u;
		std::uint32_t		frameValue = 0u;
		std::uint64_t		frameDuration = 0u;
		LoopMode			loopMode = LoopMode::NoLoop;
		std::vector<Frame>	frames;

		is.read(loopMode);
		is.read(frameCount);
		for (std::uint32_t i = 0; i < frameCount; ++i)
		{
			is.read(frameValue, frameDuration);
			frames.emplace_back(sf::microseconds(frameDuration), frameValue);
		}
		setFrames(frames);
		return (true);
	}
}
