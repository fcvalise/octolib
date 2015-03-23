/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StateManager.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 16:41:16 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/23 17:46:33 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATEMANAGER_HPP
# define STATEMANAGER_HPP
# include <string>
# include <memory>
# include <functional>
# include <map>
# include <stack>
# include <vector>

#include <SFML/Graphics/RenderTarget.hpp>

# include "AbstractTransition.hpp"

namespace octo
{
	class AbstractState;
	
	/*!	
	 *	\class StateManager
	 *	\brief Manage all stuff about game states
	 *
	 *	This class provide all services needed to
	 *	manage game state at runtime.
	 *
	 *	Different game states can be stacked.
	 *	Changing states can be done with visual transition and you can define
	 *	your own transition easilly.
	 *
	 *	This is a example of usage of StateManager:
	 *	\example state_manager/main.cpp
	 */
	class StateManager
	{
		typedef AbstractTransition::Action									Action;
		typedef std::function<AbstractState*(void)>							StateCreator;
		typedef std::function<AbstractTransition*(sf::View const&, Action)>	TransitionCreator;
	public:
		typedef std::string			Key;
		typedef std::vector<Key>	KeyList;

		/*!	Construct an empty state manager */
		StateManager();

		/*!	Register a new state class
		 *	\tparam S Type of state
		 *	\param key The key used to start the state with the manager
		 *	If a state with the same key is already registered then the state is
		 *	replaced by the new.
		 */
		template <class S>
		void			registerState(Key const& key);

		/*!	Register a state creator */
		void			registerStateCreator(Key const& key, StateCreator creator);

		/*!	Register a new transition class
		 *	\tparam T	Type of transition
		 *	\param key The key used to start the transition with the manager
		 *	If a transition with the same key is already registered then the transition is
		 *	replaced by the new.
		 */
		template <class T>
		void			registerTransition(Key const& key);

		/*!	Push a state on the stack.
		 *	The state become active and his method AbstractState::start() is called.
		 *	Eventual previously running state is stopped before.
		 */
		void			push(Key const& key);

		/*!	Push a state on the stack with a transition.
		 *	The state become active and his method AbstractState::start() is called.
		 *	Eventual previously running state is stopped before.
		 */
		void			push(Key const& stateKey, Key const& transitionKey, sf::View const& view);

		/*!
		 *	Change the current state (if exists) by another.
		 *	If no states are pushed, the new state is just pushed.
		 */
		void			change(Key const& key);

		/*!
		 *	Change the current state (if exists) by another with a transition.
		 *	If no states are pushed, the new state is just pushed.
		 */
		void			change(Key const& stateKey, Key const& transitionKey, sf::View const& view);

		/*!	Pop the current state (if any)
		 *	The state poped is stopped by calling his method AbstractState::stop().
		 */
		void			pop();

		/*!	Pop the current state (if any)
		 *	The state poped is stopped by calling his method AbstractState::stop().
		 */
		void			pop(Key const& transitionKey, sf::View const& view);

		/*!	Pop all states stacked */
		void			popAll();
	
		void			setTransitionDuration(float duration);

		bool			hasCurrentState()const;
		KeyList			availableStateKeys()const;
		KeyList			availableTransitionKeys()const;

		void			update(float frameTime);
		void			draw(sf::RenderTarget& render)const;
	private:
		typedef std::shared_ptr<AbstractState>		StatePtr;
		typedef std::map<Key, StateCreator>			StateFactory;
		typedef std::map<Key, TransitionCreator>	TransitionFactory;
		typedef std::stack<StatePtr>				StateStack;
		typedef std::unique_ptr<AbstractTransition>	TransitionPtr;

		void			push(StatePtr state);
		void			change(StatePtr state);
		void			startCurrentState();
		void			changeCurrentState();
		void			pauseCurrentState();
		void			resumeCurrentState();
		void			stopCurrentState();	
		StatePtr		createState(Key const& key)const;
		StatePtr		currentState()const;
		void			startTransition(Key const& key, sf::View const& view, Action action);
	private:
		StateFactory		m_stateFactory;
		TransitionFactory	m_transitionFactory;
		StateStack			m_stack;
		TransitionPtr		m_transition;
		float				m_transitionDuration;
	};

	template <class S>
	void	StateManager::registerState(Key const& key)
	{
		static_assert( std::is_base_of<AbstractState, S>::value,
					   "class S must be derived from octo::AbstractState" );

		m_stateFactory[key] = [](){return (new S);};
	}

	template <class T>
	void	StateManager::registerTransition(Key const& key)
	{
		static_assert( std::is_base_of<AbstractTransition, T>::value,
					   "class T must be derived from octo::AbstractTransition" );

		m_transitionFactory[key] = [](sf::View const& view, Action action){return (new T(view, action));};
	}
}

#endif
