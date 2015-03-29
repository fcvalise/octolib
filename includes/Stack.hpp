/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 01:29:57 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/29 01:48:37 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP
# include <memory>

namespace octo
{
	/*!
	 *	\ingroup Core
	 *	\class Stack
	 *	\brief Generic FIFO stack
	 *
	 *	Stack is implemented as circular buffer.<br>
	 *	You must define the maximum size of the stack when instanciated.
	 */
	template <class T>
	class Stack
	{
		Stack(Stack const&) = delete;
		Stack& operator = (Stack const&) = delete;
	public:
		/*!	Create an empty stack.
		 *	\param maxSize Max size of stack
		 */
		explicit Stack(std::size_t maxSize);

		/*!	Move constructor */
		Stack(Stack<T>&& other) = default;

		/*!	Move assignment operator */
		Stack<T>&	operator = (Stack<T>&& other) = default;

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

		/*!	Indicate if the stack is empty */
		bool			empty()const;

		/*!	Get the number of element pushed on the stack */
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
#include "Stack.hxx"
#endif
