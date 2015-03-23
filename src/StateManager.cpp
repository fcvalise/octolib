/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StateManager.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 17:07:58 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/23 17:24:45 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StateManager.hpp"
#include "AbstractState.hpp"
#include <cassert>
#include <type_traits>

namespace octo
{
	StateManager::StateManager() :
		m_transitionDuration(0.8f)
	{
	}

	void	StateManager::registerStateCreator(Key const& key, StateCreator creator)
	{
		m_stateFactory.emplace(key, creator);
	}

	void	StateManager::push(Key const& stateKey, Key const& transitionKey, sf::View const& view)
	{
		if (hasCurrentState())
		{
			startTransition(transitionKey, view, [this, stateKey]()
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

	void	StateManager::change(Key const& stateKey, Key const& transitionKey, sf::View const& view)
	{
		if (hasCurrentState())
		{
			startTransition(transitionKey, view, [this, stateKey]()
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

	void	StateManager::pop(Key const& transitionKey, sf::View const& view)
	{
		startTransition(transitionKey, view, [this]()
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
		return (m_stack.empty() == false);
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

		assert(it != m_stateFactory.end());
		return (StatePtr(it->second()));
	}

	void					StateManager::startTransition(Key const& key,
														  sf::View const& view,
														  AbstractTransition::Action action)
	{
		auto	it = m_transitionFactory.find(key);

		assert(it != m_transitionFactory.end());
		m_transition.reset(it->second(view, action));
		m_transition->setDuration(m_transitionDuration * 0.5f, m_transitionDuration * 0.5f);
	}

	StateManager::StatePtr	StateManager::currentState()const
	{
		if (m_stack.empty())
			return (nullptr);
		else
			return (m_stack.top());
	}

	void	StateManager::setTransitionDuration(float duration)
	{
		m_transitionDuration = duration;
	}

	void	StateManager::update(float frameTime)
	{
		StatePtr	current = currentState();

		if (current)
		{
			current->update(frameTime);
		}
		if (m_transition)
		{
			if (m_transition->update(frameTime) == false)
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
		KeyList	results(m_stateFactory.size());

		for (auto const& pair : m_stateFactory)
			results.push_back(pair.first);
		return (results);
	}

	StateManager::KeyList	StateManager::availableTransitionKeys()const
	{
		KeyList	results(m_transitionFactory.size());

		for (auto const& pair : m_transitionFactory)
			results.push_back(pair.first);
		return (results);
	}
}
