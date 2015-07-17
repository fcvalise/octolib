/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RingBuffer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 01:29:57 by irabeson          #+#    #+#             */
/*   Updated: 2015/07/17 14:32:39 by irabeson         ###   ########.fr       */
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
	 *	Circular buffer
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
		explicit RingBuffer(int maxSize);

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

		/*!	Access to an element of the buffer
		 *
		 *	\param index Index of the element accessed.<br>
		 *	This index can be negative, or higher than the elements number.<br>
		 *	\code
		 *	RingBuffer<int>	buffer(2);
		 *
		 *	buffer.push(1);
		 *	buffer.push(2);
		 *	std::cout << buffer[0] << std::endl; // print 1
		 *	std::cout << buffer[1] << std::endl; // print 2
		 *	std::cout << buffer[2] << std::endl; // print 1
		 *	std::cout << buffer[-1] << std::endl; // print 2
		 *	std::cout << buffer[-2] << std::endl; // print 1
		 *	\endcode
		 *	\throw std::range_error if the ring buffer is empty.
		 */
		T&				operator[](int index);

		/*!	Constant access to an element of the buffer
		 *
		 *	\param index Index of the element accessed.<br>
		 *	This index can be negative, or higher than the elements number.<br>
		 *	\code
		 *	RingBuffer<int>	buffer(2);
		 *
		 *	buffer.push(1);
		 *	buffer.push(2);
		 *	std::cout << buffer[0] << std::endl; // print 1
		 *	std::cout << buffer[1] << std::endl; // print 2
		 *	std::cout << buffer[2] << std::endl; // print 1
		 *	std::cout << buffer[-1] << std::endl; // print 2
		 *	std::cout << buffer[-2] << std::endl; // print 1
		 *	\endcode
		 *	\throw std::range_error if the ring buffer is empty.
		 */
		T const&		operator[](int index)const;

		/*!	Indicate if the stack is empty */
		bool			empty()const;

		/*!	Get the number of element pushed */
		std::size_t		size()const;

		/*!	Remove all values pushed */
		void			clear();
	private:
		int				advanceIndex(int index)const;
		int				computeIndex(int index)const;
	private:
		std::unique_ptr<T[]>	m_values;
		int const				m_maxSize;
		int						m_head;
		int						m_tail;
	};
}
#include "RingBuffer.hxx"
#endif
