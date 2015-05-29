/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StateManager.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 17:07:58 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/29 17:44:56 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StateManager.hpp"
#include "AbstractState.hpp"
#include <type_traits>
#include <stdexcept>

namespace octo
{
	namespace
	{
		class BooleanLock
		{
		public:
			inline explicit BooleanLock(bool& lock) :
				m_lock(lock)
			{
				m_lock = true;
			}

			inline ~BooleanLock()
			{
				m_lock = false;
			}
		private:
			bool&	m_lock;
		};
	}

	class PushStateEvent : public StateManagerEvent
	{
	public:
		explicit PushStateEvent(std::string const& stateKey, std::string const& transitionKey);
	};

	class ChangeStateEvent : public StateManagerEvent
	{
	public:
		explicit ChangeStateEvent(std::string const& stateKey, std::string const& transitionKey);
	};

	class PopStateEvent : public StateManagerEvent
	{
	public:
		explicit PopStateEvent(std::string const& transitionKey);
	};

	class PopAllStateEvent : public StateManagerEvent
	{
	public:
		PopAllStateEvent();
	};

	//
	//	class StateManager
	//
	StateManager::StateManager() :
		EventManager(1),
		m_transitionDuration(sf::seconds(0.8f)),
		m_inUpdate(false)
	{
	}

	void	StateManager::registerStateCreator(Key const& key, StateCreator creator)
	{
		m_stateFactory.emplace(key, creator);
	}

	bool	StateManager::isStateRegistered(Key const& key)const
	{
		return (m_stateFactory.find(key) != m_stateFactory.end());
	}

	bool	StateManager::isTransitionRegistered(Key const& key)const
	{
		return (m_transitionFactory.find(key) != m_transitionFactory.end());
	}

	void	StateManager::push(Key const& stateKey, Key const& transitionKey)
	{
		if (m_inUpdate)
		{
			pushEvent(PushStateEvent(stateKey, transitionKey));
			return;
		}
		if (hasCurrentState())
		{
			if (isStateRegistered(stateKey) == false)
				throw std::range_error("state_manager: invalid state key: " + stateKey);
			startTransition(transitionKey, [this, stateKey]()
				{
					push(createState(stateKey));
				});
		}
		else
		{
			push(createState(stateKey));
		}
	}

	void	StateManager::push(Key const& key)
	{
		if (m_inUpdate)
		{
			pushEvent(PushStateEvent(key, m_defaultTransitionKey));
			return;
		}
		if (m_defaultTransitionKey.empty() == false)
		{
			push(key, m_defaultTransitionKey);
		}
		else
		{
			push(createState(key));
		}
	}

	void	StateManager::push(StatePtr state)
	{
		pauseCurrentState();
		m_stack.push(state);
		startCurrentState();
	}

	void	StateManager::change(Key const& stateKey, Key const& transitionKey)
	{
		if (m_inUpdate)
		{
			pushEvent(ChangeStateEvent(stateKey, transitionKey));
			return;
		}
		if (hasCurrentState())
		{
			if (isStateRegistered(stateKey) == false)
				throw std::range_error("state_manager: invalid state key: " + stateKey);
			startTransition(transitionKey, [this, stateKey]()
				{
					change(createState(stateKey));
				});
		}
		else
		{
			change(createState(stateKey));
		}
	}

	void	StateManager::change(Key const& key)
	{
		if (m_inUpdate)
		{
			pushEvent(ChangeStateEvent(key, m_defaultTransitionKey));
			return;
		}
		if (m_defaultTransitionKey.empty() == false)
		{
			change(key, m_defaultTransitionKey);
		}
		else
		{
			change(createState(key));
		}
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
		if (m_inUpdate)
		{
			pushEvent(PopStateEvent(transitionKey));
			return;
		}
		startTransition(transitionKey, [this]()
			{
				stopCurrentState();
				m_stack.pop();
				resumeCurrentState();
			});	
	}

	void	StateManager::pop()
	{
		if (m_inUpdate)
		{
			pushEvent(PopStateEvent(m_defaultTransitionKey));
			return;
		}
		if (m_defaultTransitionKey.empty() == false)
		{
			pop(m_defaultTransitionKey);
		}
		else if (m_stack.empty() == false)
		{
			stopCurrentState();
			m_stack.pop();
			resumeCurrentState();
		}
	}

	void	StateManager::popAll()
	{
		if (m_inUpdate)
		{
			pushEvent(PopAllStateEvent());
			return;
		}
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

		if (it == m_stateFactory.end())
			throw std::range_error("state_manager: invalid state key: " + key);
		return (StatePtr(it->second()));
	}

	void					StateManager::startTransition(Key const& key,
														  AbstractTransition::Action action)
	{
		auto	it = m_transitionFactory.find(key);

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
		BooleanLock	lock(m_inUpdate);

		if (current)
		{
			current->update(frameTime);
		}
		if (m_transition)
		{
			if (m_transition->update(frameTime, view) == false)
			{
				m_transition.reset();
			}
		}
		m_inUpdate = false;
		processEventStack();
	}

	void	StateManager::drawTransition(sf::RenderTarget& render)const
	{
		if (m_transition)
		{
			m_transition->draw(render);
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
	
	void	StateManager::processEvent(StateManagerEvent const& event)
	{
		switch (event.getType())
		{
		case StateManagerEvent::Type::Push:
			push(event.getStateKey(), event.getTransitionKey());
			break;
		case StateManagerEvent::Type::Change:
			change(event.getStateKey(), event.getTransitionKey());
			break;
		case StateManagerEvent::Type::Pop:
			pop(event.getTransitionKey());
			break;
		case StateManagerEvent::Type::PopAll:
			popAll();
			break;
		default:
			break;
		}
	}

	StateManagerEvent::StateManagerEvent() :
		m_type(Type::Undef)
	{
	}

	StateManagerEvent::StateManagerEvent(Type type, std::string const& stateKey, std::string const& transitionKey) :
		m_type(type),
		m_stateKey(stateKey),
		m_transitionKey(transitionKey)
	{
	}

	StateManagerEvent::Type	StateManagerEvent::getType()const
	{
		return (m_type);
	}

	std::string const&	StateManagerEvent::getStateKey()const
	{
		return (m_stateKey);
	}

	std::string const&	StateManagerEvent::getTransitionKey()const
	{
		return (m_transitionKey);
	}

	PushStateEvent::PushStateEvent(std::string const& stateKey, std::string const& transitionKey) :
		StateManagerEvent(Type::Push, stateKey, transitionKey)
	{
	}

	ChangeStateEvent::ChangeStateEvent(std::string const& stateKey, std::string const& transitionKey) :
		StateManagerEvent(Type::Change, stateKey, transitionKey)
	{
	}

	PopStateEvent::PopStateEvent(std::string const& transitionKey) :
		StateManagerEvent(Type::Pop, std::string(), transitionKey)
	{
	}

	PopAllStateEvent::PopAllStateEvent() :
		StateManagerEvent(Type::PopAll, std::string(), std::string())
	{
	}
}
