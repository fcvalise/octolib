/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ByteArray.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/01 10:17:35 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/26 18:45:09 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ByteArray.hpp"
#include <algorithm>
#include <iostream>

namespace octo
{
	ByteArray::ByteArray() :
		m_bytes(nullptr),
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
	
	// cppcheck-suppress uninitMemberVar
	ByteArray::ByteArray(std::initializer_list<char> bytes) :
		ByteArray(bytes.begin(), bytes.end())
	{
	}

	ByteArray::ByteArray(char const* str, std::size_t size) :
		ByteArray()
	{
		assign(str, size);
	}

	void	ByteArray::assign(ByteArray const& bytes)
	{
		assign(bytes.begin(), bytes.end());
	}

	void	ByteArray::assign(std::initializer_list<char> bytes)
	{
		assign(bytes.begin(), bytes.end());
	}

	void			ByteArray::assign(char const* str, std::size_t size)
	{
		if (str && size > 0u)
			assign(str, str + size);
		else
			clear();
	}

	void			ByteArray::append(ByteArray const& bytes)
	{
		append(bytes.begin(), bytes.end());
	}

	void			ByteArray::append(std::initializer_list<char> bytes)
	{
		append(bytes.begin(), bytes.end());
	}

	void			ByteArray::append(char const* str, std::size_t size)
	{
		if (str && size > 0)
			append(str, str + size);
	}

	void			ByteArray::reserve(std::size_t count)
	{
		if (count <= m_capacity)
			return;
		std::unique_ptr<char[]>	newBytes(new char[count]);

		std::copy_n(begin(), m_count, newBytes.get());
		m_capacity = count;
		std::swap(m_bytes, newBytes);
	}

	void			ByteArray::resize(std::size_t count)
	{
		reserve(count);
		m_count = count;
	}

	void			ByteArray::clear()
	{
		m_count = 0u;
	}
	
	std::size_t		ByteArray::size()const
	{
		return (m_count);
	}

	std::size_t		ByteArray::capacity()const
	{
		return (m_capacity);
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

	bool			ByteArray::empty()const
	{
		return (m_count == 0u);
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

	bool			ByteArray::read(std::istream& is)
	{
		char	buffer[512];

		clear();
		is.read(buffer, 512);
		while (is.gcount() > 0)
		{
		    append(buffer, is.gcount());
		    is.read(buffer, 512);
		}
		return (true);
	}

	void			ByteArray::write(std::ostream& os)const
	{
		os.write(m_bytes.get(), m_count);
	}
}
