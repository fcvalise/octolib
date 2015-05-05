/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RingBuffer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 01:29:57 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/05 01:32:27 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RINGBUFFER_HPP
# define RINGBUFFER_HPP
# include <memory>

namespace octo
{
	/*!
	 *	\ingroup Core
	 *	\class RingBuffer
	 *
	 */
	template <class T>
	class RingBuffer
	{
		RingBuffer(RingBuffer const&) = delete;
		RingBuffer& operator = (RingBuffer const&) = delete;
	public:
		/*!	Create an empty stack.
		 *	\param maxSize Max size of stack
		 */
		explicit RingBuffer(std::size_t maxSize);

		/*!	Move constructor */
		RingBuffer(RingBuffer<T>&& other) = default;

		/*!	Move assignment operator */
		RingBuffer<T>&	operator = (RingBuffer<T>&& other) = default;

		/*!	Push a value on the back of the stack */
		void			push(T const& value);

		/*!	Push a value on the back of the stack */
		void			push(T&& value);

		/*!	Create a value on the back of the stack */
		template <class ... A>
		void			emplace(A&&... args);

		/*! Pop a value from the top of the stack
		 *
		 *	\warning never call this method on an empty stack, since
		 *	will cause an undefined behavior.
		 */
		void			pop();

		/*!	Constant access to the top.
		 *
		 *	\warning never call this method on an empty stack, since
		 *	will cause an undefined behavior.
		 */
		T const&		top()const;

		/*!	Access to the top of the stack.
		 *
		 *	\warning never call this method on an empty stack, since
		 *	will cause an undefined behavior.
		 */
		T&				top();

		T&				operator[](std::size_t index);

		T const&		operator[](std::size_t index)const;

		/*!	Indicate if the stack is empty */
		bool			empty()const;

		/*!	Get the number of element pushed */
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
#include "RingBuffer.hxx"
#endif
