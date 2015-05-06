/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractFpsDisplayer.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 02:00:14 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/06 02:22:38 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTFPSDISPLAYER_HPP
# define ABSTRACTFPSDISPLAYER_HPP

# include "RingBuffer.hpp"

namespace octo
{
	/*!
	 *	\ingroup Graphics
	 *	\class AbstractFpsDisplayer
	 *	Display information provided by FpsCounter
	 *
	 *	This class store all informations required to made a nice display.
	 *	\see FpsCounter
	 */
	class AbstractFpsDisplayer
	{
	public:
		explicit AbstractFpsDisplayer(std::size_t maxSamples);

		/*!	Append a sample */
		void			addSample(unsigned int frameCount);

		/*!	Get the last sample added */
		unsigned int	getLastSample()const;

		/*!	Get the average of all samples */
		unsigned int	getAverage()const;

		/*!	Get the sample with the highest value */ 
		unsigned int	getMaxSamples()const;
	private:
		/*!	This method is called when a new sample is added */
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
