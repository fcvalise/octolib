/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 01:29:57 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/23 18:00:51 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
# define QUEUE_HPP
# include <memory>

namespace octo
{
	/*!	\class Queue
	 *	\brief Generic FIFO queue
	 *
	 *	Queue is implemented as circular buffer.<br>
	 *	You must define the maximum size of the queue when instanciated.
	 */
	template <class T>
	class Queue
	{
		Queue(Queue const&) = delete;
		Queue& operator = (Queue const&) = delete;
	public:
		/*!	Create an empty queue.
		 *	\param maxSize Max size of queue
		 */
		explicit Queue(std::size_t maxSize);

		/*!	Move constructor */
		Queue(Queue<T>&& other) = default;

		/*!	Move assignment operator */
		Queue<T>&	operator = (Queue<T>&& other) = default;

		/*!	Push a value on the top of the queue */
		void			push(T const& value);

		/*!	Push a value on the top of the queue */
		void			push(T&& value);

		/*!	Create a value on the top of the queue */
		template <class ... A>
		void			emplace(A&&... args);

		/*! Pop a value from the top of the queue
		 *
		 *	\warning never call this method on an empty queue, since
		 *	will cause an undefined behavior.
		 */
		void			pop();

		/*!	Constant access to the top.
		 *
		 *	\warning never call this method on an empty queue, since
		 *	will cause an undefined behavior.
		 */
		T const&		top()const;

		/*!	Access to the top of the queue.
		 *
		 *	\warning never call this method on an empty queue, since
		 *	will cause an undefined behavior.
		 */
		T&				top();

		/*!	Indicate if the queue is empty */
		bool			empty()const;

		/*!	Get the number of element pushed on the queue */
		std::size_t		size()const;

		/*!	Remove all values pushed */
		void			clear();
	private:
		std::size_t		advanceIndex(std::size_t index)const;
	private:
		std::unique_ptr<T[]>	m_values;
		std::size_t const		m_maxSize;
		std::size_t				m_head;
		std::size_t				m_tail;
	};
}
#include "Queue.hxx"
#endif
