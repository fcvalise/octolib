/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StateManager.hxx                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/15 18:59:07 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/15 18:59:16 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace octo
{
	template <class S>
	void	StateManager::registerState(Key const& key)
	{
		static_assert( std::is_base_of<AbstractState, S>::value,
					   "class S must be derived from octo::AbstractState" );
		if (m_stateFactory.find(key) != m_stateFactory.end())
			throw std::logic_error("state_manager: register transition: key already used: " + key);
		m_stateFactory[key] = [](){return (new S);};
	}

	template <class T>
	void	StateManager::registerTransition(Key const& key)
	{
		static_assert( std::is_base_of<AbstractTransition, T>::value,
					   "class T must be derived from octo::AbstractTransition" );

		if (m_stateFactory.find(key) != m_stateFactory.end())
			throw std::logic_error("state_manager: register transition: key already used: " + key);
		m_transitionFactory[key] = [](Action action){return (new T(action));};
	}
}
