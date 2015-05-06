/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FpsCounter.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 00:43:01 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/06 02:13:48 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FPSCOUNTER_HPP
# define FPSCOUNTER_HPP

# include <SFML/System/Time.hpp>

namespace octo
{
	class AbstractFpsDisplayer;

	/*!	
	 *	\ingroup Graphics
	 *	\class FpsCounter
	 *	Count the number of frame per second
	 *
	 *	This class does not manage any display.<br>
	 *	Display is delegated to AbstractFpsDisplayer.
	 */
	class FpsCounter
	{
	public:
		FpsCounter();

		void	setDisplay(AbstractFpsDisplayer* displayer);
		void	setEnabled(bool enabled);
		void	update(sf::Time frameTime);
	private:
		sf::Time						m_currentTime;
		unsigned int					m_frameCount;
		bool							m_enabled;
		AbstractFpsDisplayer*			m_displayer;
	};
}

#endif
