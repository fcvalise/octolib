/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractState.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 17:42:53 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/29 04:29:18 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTSTATE_HPP
# define ABSTRACTSTATE_HPP
# include <SFML/Graphics/RenderTarget.hpp>
# include <SFML/System/Time.hpp>

namespace octo
{
	/*!
	 *	\ingroup GameState
	 *	\brief Abstraction of game state
	 *
	 *	\remark All virtual pure methods are private for
 	 *	safety, only StateManager is able to calls it.
	 *	\see StateManager
	 *	\see AbstractTransition
	 */
	class AbstractState
	{
	public:
		virtual ~AbstractState();
	private:
		friend class StateManager;

		/*!	Method called when the state is started by the manager */
		virtual void	start() = 0;
		/*!	Method called when the state is paused by the manager */
		virtual void	pause() = 0;
		/*!	Method called when the state is resumed by the manager */
		virtual void	resume() = 0;
		/*!	Method called when the state is stopped by the manager */
		virtual void	stop() = 0;

		/*!	Method called once per frame before game render */
		virtual void	update(sf::Time frameTime) = 0;

		/*!	Method called once per frame after game update */
		virtual void	draw(sf::RenderTarget& render)const = 0;
	};
}

#endif
