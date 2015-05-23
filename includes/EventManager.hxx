/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventManager.hxx                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 18:13:18 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/23 02:47:40 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace octo
{
	template <class E>
	EventManager<E>::EventManager(std::size_t maxEvent) :
		m_stack(maxEvent)
	{
	}

	template <class E>
	EventManager<E>::~EventManager()
	{
	}

	template <class E>
	void	EventManager<E>::pushEvent(E const& event)
	{
		m_stack.push(event);
	}

	template <class E>
	void	EventManager<E>::pushEvent(E&& event)
	{
		m_stack.push(std::forward<E>(event));
	}

	template <class E>
	template <class ... A>
	void	EventManager<E>::emplaceEvent(A&&... args)
	{
		m_stack.emplace(std::forward<A>(args)...);
	}

	template <class E>
	void	EventManager<E>::processEventStack()
	{
		while (m_stack.empty() == false)
		{
			processEvent(m_stack.top());
			m_stack.pop();
		}
	}
}
