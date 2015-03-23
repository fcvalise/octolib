/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventManager.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 00:48:12 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/23 18:13:40 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTMANAGER_HPP
# define EVENTMANAGER_HPP
# include "Queue.hpp"

namespace octo
{
	/*!
	 *	\class EventManager
	 *	\brief Generic class for event queuing
	 *	\tparam E Define events type
	 *
	 *	This template class is used to allow a class
	 *	to enqueing events and processing it.<br>
	 *
	 *	All allocations are preformed by the constructor. <br>
	 *
	 *	EventManager is designed to be inertited.
	 *	\code
	 *	struct MyEvent
	 *	{
	 *		// here your stuff...
	 *	};
	 *
	 *	class MySystem : public EventManager<MyEvent>
	 *	{
	 *		// here your stuff
	 *	public:
	 *		MySystem() :
	 *			EventManager(50)	// Reserve memory for 50 event max at the same frame
	 *		{
	 *		}
	 *
	 *		// This method is called once per frame
	 *		void	update()
	 *		{
	 *			// Process event queue
	 *			processQueue();
	 *		}
	 *	private:
	 *		void	processEvent(MyEvent const& event)
	 *		{
	 *			// Use event to do something...
	 *		}
	 *	};
	 *
	 *	MySystem	system;
	 *
	 *	system.pushEvent(MyEvent(...));
	 *	system.update();
	 *
	 *	\endcode
	 *	\see EventManagers
	 */
	template <class E>
	class EventManager
	{
		typedef Queue<E>	EventQueue;
	public:
		typedef E	EventType;

		/*!
		 *	Create a manager and performe memory allocations
		 *	\param maxEvent Maximum of event which can be enqueued
		 */
		explicit EventManager(std::size_t maxEvent);

		virtual ~EventManager();

		/*!	Push a new event */
		void			pushEvent(E const& event);

		/*!	Push a new event */
		void			pushEvent(E&& event);

		/*!	Emplace a new event */
		template <class ... A>
		void			emplaceEvent(A&&... args);
	protected:
		/*!	This method process and pop each pending event. */
		void			processEventQueue();
	private:
		/*!	This method is called for each event processed */
		virtual void	processEvent(E const& event) = 0;
	private:
		EventQueue	m_queue;
	};
}

#include "EventManager.hxx"
#endif
