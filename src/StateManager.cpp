/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StateManager.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 17:07:58 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/22 21:50:37 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StateManager.hpp"
#include "AbstractState.hpp"
#include <cassert>
#include <type_traits>

namespace octo
{
	void	StateManager::registerCreator(Key const& key, Creator creator)
	{
		m_factory.emplace(key, creator);
	}

	void	StateManager::push(Key const& key)
	{
		push(createState(key));
	}

	void	StateManager::change(Key const& key)
	{
		change(createState(key));
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
		while (m_stack.empty() == false)
		{
			stopCurrentState();
			m_stack.pop();
		}
	}

	void	StateManager::push(StatePtr state)
	{
		pauseCurrentState();
		m_stack.push(state);
		startCurrentState();
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
		auto	it = m_factory.find(key);

		assert(it != m_factory.end());
		return (StatePtr(it->second()));
	}

	StateManager::StatePtr	StateManager::currentState()const
	{
		if (m_stack.empty())
			return (nullptr);
		else
			return (m_stack.top());
	}

	void	StateManager::update(float frameTime)
	{
		StatePtr	current = currentState();

		if (current)
		{
			current->update(frameTime);
		}
	}

	void	StateManager::draw(sf::RenderTarget& render)const
	{
		StatePtr	current = currentState();

		if (current)
		{
			current->draw(render);
		}
	}
}
