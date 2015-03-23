/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventManager.hxx                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 18:13:18 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/23 18:13:21 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace octo
{
	template <class E>
	EventManager<E>::EventManager(std::size_t maxEvent) :
		m_queue(maxEvent)
	{
	}

	template <class E>
	EventManager<E>::~EventManager()
	{
	}

	template <class E>
	void	EventManager<E>::pushEvent(E const& event)
	{
		m_queue.push(event);
	}

	template <class E>
	void	EventManager<E>::pushEvent(E&& event)
	{
		m_queue.push(std::forward<E>(event));
	}

	template <class E>
	template <class ... A>
	void	EventManager<E>::emplaceEvent(A&&... args)
	{
		m_queue.emplace(std::forward<A>(args)...);
	}

	template <class E>
	void	EventManager<E>::processEventQueue()
	{
		while (m_queue.empty() == false)
		{
			processEvent(m_queue.top());
			m_queue.pop();
		}
	}
}
