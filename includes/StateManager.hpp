/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StateManager.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 16:41:16 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/23 00:03:39 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATEMANAGER_HPP
# define STATEMANAGER_HPP
# include <string>
# include <memory>
# include <functional>
# include <map>
# include <stack>

#include <SFML/Graphics/RenderTarget.hpp>

namespace octo
{
	class AbstractState;

	class StateManager
	{
		typedef std::function<AbstractState*(void)>	Creator;
	public:
		typedef std::string	Key;

		/*!	Register a new state class
		 *	\tparam S Type of state
		 *	\param key The key used to start the state with the manager
		 *	If a state with the same key is already registered then the state is
		 *	replaced by the new.
		 */
		template <class S>
		void	registerState(Key const& key);

		/*!	Register a state creator */
		void	registerCreator(Key const& key, Creator creator);

		/*!	Push a state on the stack.
		 *	The state become active and his method AbstractState::start() is called.
		 *	Eventual previously running state is stopped before.
		 */
		void	push(Key const& key);

		/*!
		 *	Change the current state (if exists) by another.
		 *	If no states are pushed, the new state is just pushed.
		 */
		void	change(Key const& key);

		/*!	Pop the current state (if any)
		 *	The state poped is stopped by calling his method AbstractState::stop().
		 */
		void	pop();

		/*!	Pop all states stacked */
		void	popAll();

		bool	hasCurrentState()const;

		void	update(float frameTime);

		void	draw(sf::RenderTarget& render)const;
	private:
		typedef std::shared_ptr<AbstractState>		StatePtr;
		typedef std::map<Key, Creator>				Factory;
		typedef std::stack<StatePtr>				StateStack;

		void			push(StatePtr state);
		void			change(StatePtr state);
		void			startCurrentState();
		void			changeCurrentState();
		void			pauseCurrentState();
		void			resumeCurrentState();
		void			stopCurrentState();	
		StatePtr		createState(Key const& key)const;
		StatePtr		currentState()const;
	private:
		Factory		m_factory;
		StateStack	m_stack;
	};

	template <class S>
	void	StateManager::registerState(Key const& key)
	{
		static_assert( std::is_base_of<AbstractState, S>::value,
					   "class S must be derived from octo::AbstractState" );

		m_factory[key] = [](){return (new S);};
	}
}

#endif
