/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ByteArray.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/01 10:17:35 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/01 11:34:37 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ByteArray.hpp"
#include <algorithm>
#include <iostream>

namespace octo
{
	ByteArray::ByteArray() :
		m_capacity(0u),
		m_count(0u)
	{
	}

	ByteArray::ByteArray(std::size_t count) :
		m_bytes(new char[count]),
		m_capacity(count),
		m_count(0u)
	{
	}
	
	void			ByteArray::resize(std::size_t count)
	{
		if (m_capacity < count)
			reserve(count);
		m_count = count;
	}

	void			ByteArray::clear()
	{
		m_count = 0u;
	}

	std::size_t		ByteArray::capacity()const
	{
		return (m_capacity);
	}
	
	std::size_t		ByteArray::size()const
	{
		return (m_count);
	}

	char	ByteArray::operator[](std::size_t i)const
	{
		return (m_bytes[i]);
	}

	char&	ByteArray::operator[](std::size_t i)
	{
		return (m_bytes[i]);
	}

	char const*		ByteArray::bytes()const
	{
		return (m_bytes.get());
	}

	ByteArray::iterator		ByteArray::begin()
	{
		return (m_bytes.get());
	}

	ByteArray::iterator		ByteArray::end()
	{
		return (m_bytes.get() + m_count);
	}

	ByteArray::const_iterator	ByteArray::begin()const
	{
		return (m_bytes.get());
	}

	ByteArray::const_iterator	ByteArray::end()const
	{
		return (m_bytes.get() + m_count);
	}

	bool			ByteArray::read(std::istream& is, std::size_t count)
	{
		resize(count);
		return (is.read(m_bytes.get(), count) && is.gcount() == std::streamsize(count));
	}

	void			ByteArray::write(std::ostream& os)const
	{
		os.write(m_bytes.get(), m_count);
	}
	
	void			ByteArray::reserve(std::size_t count)
	{
		std::unique_ptr<char[]>	newBytes(new char[count]);
		std::size_t				newCount = std::min(count, m_count);

		std::copy_n(begin(), newCount, newBytes.get());
		m_count = newCount;
		m_capacity = count;
		std::swap(m_bytes, newBytes);
	}
}
