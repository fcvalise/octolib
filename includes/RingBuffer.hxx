/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RingBuffer.hxx                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/20 22:52:53 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/05 01:32:43 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>

namespace octo
{
	template <class T>
	RingBuffer<T>::RingBuffer(std::size_t maxSize) :
		m_values(new T[maxSize + 1]),
		m_maxSize(maxSize + 1),
		m_head(0u),
		m_tail(0u)
	{
		assert(maxSize > 0);
		assert(maxSize < std::numeric_limits<decltype(maxSize)>::max());
	}

	template <class T>
	void	RingBuffer<T>::push(T const& value)
	{
		assert(m_head != (m_tail + 1) % m_maxSize);

		m_values[m_tail] = value;
		m_tail = advanceIndex(m_tail);
	}

	template <class T>
	void	RingBuffer<T>::push(T&& value)
	{
		assert(m_head != (m_tail + 1) % m_maxSize);

		m_values[m_tail] = std::move(value);
		m_tail = advanceIndex(m_tail);
	}

	template <class T>
	template <class ... A>
	void	RingBuffer<T>::emplace(A&&... args)
	{
		assert(m_head != (m_tail + 1) % m_maxSize);

		m_values[m_tail] = T(std::forward<A>(args)...);
		m_tail = advanceIndex(m_tail);
	}

	template <class T>
	void	RingBuffer<T>::pop()
	{
		assert(empty() == false);

		m_head = advanceIndex(m_head);
	}

	template <class T>
	T const&	RingBuffer<T>::top()const
	{
		return (m_values[m_head]);
	}

	template <class T>
	T&	RingBuffer<T>::top()
	{
		return (m_values[m_head]);
	}

	template <class T>
	bool	RingBuffer<T>::empty()const
	{
		return (m_head == m_tail);
	}

	template <class T>
	std::size_t	RingBuffer<T>::size()const
	{
		if (m_head <= m_tail)
			return (m_tail - m_head);
		else
			return (m_maxSize - (m_head - m_tail));
	}

	template <class T>
	void	RingBuffer<T>::clear()
	{
		m_head = 0u;
		m_tail = 0u;
	}

	template <class T>
	std::size_t	RingBuffer<T>::advanceIndex(std::size_t index)const
	{
		return ((index + 1) % m_maxSize);
	}

	template <class T>
	T&	RingBuffer<T>::operator[](std::size_t index)
	{
		return (m_values[(m_head + index) % m_maxSize]);
	}

	template <class T>
	T const&	RingBuffer<T>::operator[](std::size_t index)const
	{
		return (m_values[(m_head + index) % m_maxSize]);
	}
}
