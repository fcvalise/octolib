/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StateManager.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 17:07:58 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/30 16:25:20 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StateManager.hpp"
#include "AbstractState.hpp"
#include <cassert>
#include <type_traits>

namespace octo
{
	StateManager::StateManager() :
		m_transitionDuration(sf::seconds(0.8f))
	{
	}

	void	StateManager::registerStateCreator(Key const& key, StateCreator creator)
	{
		m_stateFactory.emplace(key, creator);
	}

	void	StateManager::push(Key const& stateKey, Key const& transitionKey)
	{
		if (hasCurrentState())
		{
			startTransition(transitionKey, [this, stateKey]()
				{
					push(stateKey);
				});
		}
		else
		{
			push(stateKey);
		}
	}

	void	StateManager::push(Key const& key)
	{
		push(createState(key));
	}

	void	StateManager::push(StatePtr state)
	{
		pauseCurrentState();
		m_stack.push(state);
		startCurrentState();
	}

	void	StateManager::change(Key const& stateKey, Key const& transitionKey)
	{
		if (hasCurrentState())
		{
			startTransition(transitionKey, [this, stateKey]()
				{
					change(stateKey);
				});
		}
		else
		{
			change(stateKey);
		}
	}

	void	StateManager::change(Key const& key)
	{
		change(createState(key));
	}

	void	StateManager::change(StatePtr state)
	{
		if (hasCurrentState())
		{
			stopCurrentState();
			m_stack.top() = state;
			startCurrentState();
		}
		else
		{
			push(state);	
		}
	}

	void	StateManager::pop(Key const& transitionKey)
	{
		startTransition(transitionKey, [this]()
			{
				pop();
			});	
	}

	void	StateManager::pop()
	{
		if (m_stack.empty() == false)
		{
			stopCurrentState();
			m_stack.pop();
			resumeCurrentState();
		}
	}

	void	StateManager::popAll()
	{
		m_transition.reset();
		while (m_stack.empty() == false)
		{
			stopCurrentState();
			m_stack.pop();
		}
	}

	bool	StateManager::hasCurrentState()const
	{
		return (m_stack.size() > 0);
	}

	void	StateManager::startCurrentState()
	{
		StatePtr	state = currentState();

		if (state)
		{
			state->start();
		}
	}

	void	StateManager::resumeCurrentState()
	{
		StatePtr	state = currentState();

		if (state)
		{
			state->resume();
		}
	}

	void	StateManager::pauseCurrentState()
	{
		StatePtr	state = currentState();

		if (state)
		{
			state->pause();
		}
	}

	void	StateManager::stopCurrentState()
	{
		StatePtr	state = currentState();

		if (state)
		{
			state->stop();
		}
	}
	
	StateManager::StatePtr	StateManager::createState(Key const& key)const
	{
		auto	it = m_stateFactory.find(key);

		if (it == m_stateFactory.end())
			throw std::range_error("state_manager: invalid state key: " + key);
		return (StatePtr(it->second()));
	}

	void					StateManager::startTransition(Key const& key,
														  AbstractTransition::Action action)
	{
		auto	it = m_transitionFactory.find(key);

		assert(it != m_transitionFactory.end());
		if (it == m_transitionFactory.end())
			throw std::range_error("state_manager: invalid transition key: " + key);
		m_transition.reset(it->second(action));
		m_transition->setDuration(m_transitionDuration * 0.5f, m_transitionDuration * 0.5f);
	}

	StateManager::StatePtr	StateManager::currentState()const
	{
		if (m_stack.empty())
			return (nullptr);
		else
			return (m_stack.top());
	}

	void	StateManager::setTransitionDuration(sf::Time duration)
	{
		m_transitionDuration = duration;
	}

	void	StateManager::update(sf::Time frameTime, sf::View const& view)
	{
		StatePtr	current = currentState();

		if (current)
		{
			current->update(frameTime);
		}
		if (m_transition)
		{
			if (m_transition->update(frameTime, view) == false)
				m_transition.reset();
		}
	}

	void	StateManager::draw(sf::RenderTarget& render)const
	{
		StatePtr	current = currentState();

		if (current)
		{
			current->draw(render);
		}
		if (m_transition)
		{
			m_transition->draw(render);
		}
	}
	
	StateManager::KeyList	StateManager::availableStateKeys()const
	{
		KeyList	results;

		results.reserve(m_stateFactory.size());
		for (auto const& pair : m_stateFactory)
			results.push_back(pair.first);
		return (results);
	}

	StateManager::KeyList	StateManager::availableTransitionKeys()const
	{
		KeyList	results;

		results.reserve(m_transitionFactory.size());
		for (auto const& pair : m_transitionFactory)
			results.push_back(pair.first);
		return (results);
	}
}
