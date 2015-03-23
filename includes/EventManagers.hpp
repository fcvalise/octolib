/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventManagers.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 23:12:05 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/23 18:01:37 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTMANAGERS_HPP
# define EVENTMANAGERS_HPP
# include "EventManager.hpp"

namespace octo
{
	/*!
	 *	\class EventManagers
	 *	\brief Combination of EventManager
	 *	\tparam ES Typelist defining the events managers to generate by meta programming
	 *
	 *	This class makes it easier to create object able to support different types
	 *	of events.
	 *
	 *	Instead of this:
	 *	\code
	 *	
	 *	class Foo : public EventManager<A>,
	 *				public EventManager<B>,
	 *				public EventManager<C>
	 *	{
	 *	public:
	 *		Foo() :
	 *			EventManager<A>(10),
	 *			EventManager<A>(200),
	 *			EventManager<A>(3000)
	 *		{
	 *		}
	 *
	 *		void	update()
	 *		{
	 *			// It's easy to forget on manager, and it tedious to write
	 *			// if the number of event types increases..
	 *			EventManager<A>::processEventQueue();
	 *			EventManager<B>::processEventQueue();
	 *			EventManager<C>::processEventQueue();
	 *		}
	 *	private:
	 *		virtual void	processEvent(A const& event);
	 *		virtual void	processEvent(B const& event);
	 *		virtual void	processEvent(C const& event);
	 *	};
	 *	\endcode
	 *	EventManagers allows this:
	 *
	 *	\code
	 *	class Foo : public EventManagers<A, B, C>
	 *	{
	 *	public:
	 *		Foo() :
	 *			EventManagers(10, 200, 3000)
	 *		{
	 *		}
	 *
	 *		void	update()
	 *		{
	 *			// Call EventManager::processQueue for each type of manager
	 *			processEventQueues();
	 *		}
	 *	private:
	 *		virtual void	processEvent(A const& event);
	 *		virtual void	processEvent(B const& event);
	 *		virtual void	processEvent(C const& event);
	 *	};
	 *	\endcode
	 *
	 *	\see EventManager
	 */
	template <class ... ES>
	class EventManagers : private EventManager<ES>...
	{
		template <class T>
		struct	ManagerInitializer
		{
			typedef std::size_t	Type;
		};
	public:
		/*!	
		 *	Constructs each event manager.
		 *
		 *	Since each event manager constructor haves a parameter which specify
		 *	the maximum, this constructors takes a numers of std::size_t equal
		 *	to the count of event manager.
		 *	<br>
		 *	If we have 3 event type A, B, C, we can create a class capable
		 *	to handle all these event types as following:
		 *	\code
		 *	class Foo : public EventManagers<A, B, C>
		 *	{
		 *	public:
		 *		Foo() :
		 *			EventManagers
		 *				(
		 *					1,	// Maximum count of event of type A
		 *					10, // Maximum count of event of type B
		 *					23	// Max count of C
		 *				)
		 *			{
		 *			}
		 *	private:
		 *		virtual void	processEvent(A const& event);
		 *		virtual void	processEvent(B const& event);
		 *		virtual void	processEvent(C const& event);	
		 *	};
		 *	\endcode
		 */
		EventManagers(typename ManagerInitializer<ES>::Type ... maxEvents) :
			EventManager<ES>(maxEvents)...
		{
		}

		/*!	Push a new event */
		template <class E>
		void			pushEvent(E const& event)
		{
			EventManager<E>::pushEvent(event);
		}

		/*!	Push a new event */
		template <class E>
		void			pushEvent(E&& event)
		{
			EventManager<E>::pushEvent(std::forward(event));
		}

		/*!	Emplace a new event */
		template <class E, class ... A>
		void			emplaceEvent(A&&... args)
		{
			EventManager<E>::emplaceEvent(std::forward<A>(args)...);
		}

		/*!	Process event queue of each event manager */
		void			processEventQueues()
		{
			ProcessEventQueue<0u, sizeof...(ES)>::exec(this);
		}
	private:
		typedef EventManagers<ES...>	Managers;

		template <std::size_t I, size_t N>
		struct	ProcessEventQueue;

		template <std::size_t I>
		struct	ProcessEventQueue<I, I>;
	};

	template <class ... ES>
	template <std::size_t I, size_t N>
	struct	EventManagers<ES...>::ProcessEventQueue
	{
		static inline void	exec(Managers* managers)
		{
			typedef typename std::tuple_element<I, std::tuple<ES...>>::type ElementType;

			managers->EventManager<ElementType>::processEventQueue();
			ProcessEventQueue<I + 1, N>::exec(managers);
		}
	};

	template <class ... ES>
	template <std::size_t I>
	struct	EventManagers<ES...>::ProcessEventQueue<I, I>
	{
		static inline void	exec(Managers*)
		{
		}
	};
}

#endif
