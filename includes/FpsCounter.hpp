/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FpsCounter.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 00:43:01 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/05 02:13:40 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FPSCOUNTER_HPP
# define FPSCOUNTER_HPP

# include <SFML/System/Time.hpp>

# include <memory>

namespace octo
{
	class AbstractFpsDisplayer;

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
