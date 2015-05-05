/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractFpsDisplayer.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 02:00:14 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/05 17:50:33 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTFPSDISPLAYER_HPP
# define ABSTRACTFPSDISPLAYER_HPP

# include "RingBuffer.hpp"

namespace octo
{
	class AbstractFpsDisplayer
	{
	public:
		explicit AbstractFpsDisplayer(std::size_t maxSamples);

		void			addSample(unsigned int frameCount);
		unsigned int	getLastSample()const;
		unsigned int	getAverage()const;
		unsigned int	getMaxSamples()const;
	private:
		virtual void	updateDisplay(RingBuffer<unsigned int> const& samples, unsigned int maxFrameCount) = 0;
	private:
		RingBuffer<unsigned int>		m_samples;
		std::size_t						m_maxSamples;
		unsigned int					m_maxFrameCount;
		unsigned int					m_lastSample;
		unsigned int					m_averageBuffer;
		unsigned int					m_averageCount;
	};
}

#endif
