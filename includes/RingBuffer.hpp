/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RingBuffer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 01:29:57 by irabeson          #+#    #+#             */
/*   Updated: 2015/07/18 15:59:39 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RINGBUFFER_HPP
# define RINGBUFFER_HPP
# include <memory>
# include <type_traits>

namespace octo
{
	/*!
	 *	\ingroup Core
	 *	\class RingBuffer
	 *	\brief Static circular buffer
	 *	\tparam T Type of values stored<br>
	 *
	 *	This container does memory allocation only once.<br>
	 *	The type T must be:
	 *		- default constructible
	 *		- assignable (to use push())
	 *		- movable (to use emplace())
	 */
	template <class T>
	class RingBuffer
	{
		static_assert( std::is_default_constructible<T>::value, "T must be default constructible" );

		RingBuffer(RingBuffer<T> const&) = delete;
		RingBuffer<T>& operator = (RingBuffer<T> const&) = delete;
	public:
		/*!	Create an empty buffer.
		 *	\param maxSize Max size of buffer (minimum 1)
		 */
		explicit RingBuffer(int maxSize);

		/*!	Move constructor */
		RingBuffer(RingBuffer<T>&& other) = default;

		/*!	Move assignment operator */
		RingBuffer<T>&	operator = (RingBuffer<T>&& other) = default;

		/*!	Push a value on the back of the buffer
		 *
		 *	\warning You must ensure that there is enough space to add an element.
		 *	\see capacity()
		 */
		void			push(T const& value);

		/*!	Push a value on the back of the buffer
		 *
		 *	\warning You must ensure that there is enough space to add an element.
		 *	\see capacity()
		 */
		void			push(T&& value);

		/*!	Create a value on the back of the buffer
		 *
		 *	\warning You must ensure that there is enough space to add an element.
		 *	\see capacity()
		 */
		template <class ... A>
		void			emplace(A&&... args);

		/*! Pop a value from the top of the buffer
		 *
		 *	\warning never call this method on an empty buffer, since
		 *	will cause an undefined behavior.
		 *	\see empty()
		 */
		void			pop();

		/*!	Constant access to the top.
		 *
		 *	\warning never call this method on an empty buffer, since
		 *	will cause an undefined behavior.
		 *	\see empty()
		 */
		T const&		top()const;

		/*!	Access to the top of the buffer.
		 *
		 *	\warning never call this method on an empty buffer, since
		 *	will cause an undefined behavior.
		 *	\see empty()
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

		/*!	Indicate if the buffer is empty */
		bool			empty()const;

		/*!	Get the number of element pushed */
		std::size_t		size()const;

		/*!	Get the number of the remaining reserved elements
		 *
		 *	\code
		 *	RingBuffer<int>	buffer(3);
		 *
		 *	std::cout << buffer.capacity() << std::endl;	// Print 3
		 *	buffer.push(666);
		 *	std::cout << buffer.capacity() << std::endl;	// Print 2
		 *	buffer.push(666);
		 *	std::cout << buffer.capacity() << std::endl;	// Print 1
		 *	buffer.push(666);
		 *	std::cout << buffer.capacity() << std::endl;	// Print 0
		 *	\endcode
		 */
		std::size_t		capacity()const;

		/*!	Get the maximum count of element stored */
		std::size_t		maxCapacity()const;

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
