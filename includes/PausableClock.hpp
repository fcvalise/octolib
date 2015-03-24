/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PausableClock.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/24 20:14:15 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/24 20:30:11 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAUSABLECLOCK_HPP
# define PAUSABLECLOCK_HPP
# include <SFML/System/Time.hpp>
# include <SFML/System/Clock.hpp>

namespace octo
{
	/*!	Pausable time counter */
	class PausableClock
	{
	public:
		PausableClock();

		sf::Time	restart();
		void		pause();
		void		resume();
		sf::Time	getElapsedTime()const;
	private:
		sf::Clock	m_clock;
		sf::Time	m_buffer;
		bool		m_run;
	};
}

#endif
