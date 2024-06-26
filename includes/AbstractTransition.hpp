/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractTransition.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 00:04:12 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/29 04:30:34 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTTRANSITION_HPP
# define ABSTRACTTRANSITION_HPP
# include "AbstractState.hpp"

# include <SFML/Graphics/View.hpp>

# include <functional>

namespace octo
{
	/*!
	 *	\ingroup GameState
	 *	Abstraction of transition between game states
	 *
	 *	A transition have two phases, in-phase and out-phase.<br>
	 *	A transition is started in paralle of the current state. <br>
	 *	When current state is about to be changed by the state manager, it is not really changed
	 *	until the current transition have not
	 *	finished his in-phase.<br> When the transition in-phase is finished, the change is done
	 *	and the out-phase begin.<br>
	 *	In other words, the StateManager's action (pushing state, exchange state or pop) is just
	 *	delayed until transition's in-phase is done..<br>
	 *	This behavior allows some fancy stuffs as black fade-in fade-out but
	 *	more complex transition as possible, such post-processing.<br>
	 *	You can create a new transition by deriving your class from AbstractTransition
	 *	then implementing methods AbstractTransition::updateTransition()
	 *	and AbstractTransition::draw().<br>
	 *
	 *	\see StateManager
	 *	\see AbstractState
	 */
	class AbstractTransition
	{
	public:
		/*!	Transition status */
		enum class Status
		{
			In,			///<	Phase is in in-phase
			Out,		///<	Phase is in out-phase
			Finished	///<	Transition is finished
		};

		/*! Function storing the delayed action.
		 */
		typedef std::function<void()>	Action;

		/*!	Construct a transition.
		 *
		 *	\param view You can get this view in your derived class
		 *	with AbstractTransition;;view().
		 *	\param action Delayed state manager action.
		 */
		explicit AbstractTransition(Action action);

		/*!	Transition destructor */
		virtual ~AbstractTransition();

		/*!	Define the duration of each phase (phase in and out) */
		void			setDuration(sf::Time in, sf::Time out);

		/*!	Get transition status */
		Status			status()const;

		/*!	Called once per frame, before render */
		bool			update(sf::Time frameTime, sf::View const& view);

		/*!	Implement all transition draw here */
		virtual void	draw(sf::RenderTarget& render)const = 0;
	private:
		/*!	Implement all transition logic here
		 *	\param frameTime Time elapsed during the last frame
		 *	\param timePosition This value define how many time is elapsed
		 *	At the beginning of the transition, this value is set to 0. After when
		 *	the in transition is finished this value must be equal or greater to 1
		 *	and when the transition out is finished, the value must be returned to 0
		 *	or less.
		 */
		virtual void	updateTransition(sf::Time frameTime, float timePosition, sf::View const& view) = 0;
	private:
		sf::Time	m_inDuration;
		sf::Time	m_outDuration;
		sf::Time	m_currentTime;
		Action		m_action;
		Status		m_status;
		bool		m_outFirstFrame;
	};
}

#endif
