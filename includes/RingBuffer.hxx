/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RingBuffer.hxx                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/20 22:52:53 by irabeson          #+#    #+#             */
/*   Updated: 2015/07/17 14:32:50 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <limits>
#include <stdexcept>

namespace octo
{
	template <class T>
	RingBuffer<T>::RingBuffer(int maxSize) :
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
		assert (empty() == false);

		return (m_values[m_head]);
	}

	template <class T>
	T&	RingBuffer<T>::top()
	{
		assert (empty() == false);

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
	int	RingBuffer<T>::advanceIndex(int index)const
	{
		return ((index + 1) % m_maxSize);
	}

	template <class T>
	int		RingBuffer<T>::computeIndex(int index)const
	{
		int	result = 0;

		if (index < 0)
		{
			index = abs(index) % size();
			result = (size() + index) % size();
			result = (size() - abs(index)) % size();
		}
		else
		{
			result = (m_head + index) % size();
		}
		return (result);
	}

	template <class T>
	T&	RingBuffer<T>::operator[](int index)
	{
		if (empty())
			throw std::range_error("empty ring buffer");
		return (m_values[computeIndex(index)]);
	}

	template <class T>
	T const&	RingBuffer<T>::operator[](int index)const
	{
		if (empty())
			throw std::range_error("empty ring buffer");
		return (m_values[computeIndex(index)]);
	}
}
