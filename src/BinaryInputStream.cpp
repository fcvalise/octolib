/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BinaryInputStream.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/01 14:52:11 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/13 20:33:23 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BinaryInputStream.hpp"
#include <algorithm>

namespace octo
{
	BinaryInputStream::BinaryInputStream(ByteArray const& bytes) :
		m_bytes(bytes),
		m_pos(0u),
		m_isOk(true)
	{
	}
	
	void	BinaryInputStream::skip(std::size_t count)
	{
		m_pos = std::min(m_bytes.size(), m_pos + count);
	}

	bool	BinaryInputStream::isOk()const
	{
		return (m_isOk);
	}

	bool	BinaryInputStream::hasDataToRead()const
	{
		return (m_pos != m_bytes.size());
	}

	std::size_t	BinaryInputStream::getPosition()const
	{
		return (m_pos);
	}

	BinaryInputStream::operator bool()const
	{
		return (isOk() && hasDataToRead());
	}

	void	BinaryInputStream::read(char* buffer, std::size_t size)
	{
		std::size_t	remaining = m_bytes.size() - m_pos;

		if (m_isOk == false || remaining == 0 || remaining < size)
		{
			m_isOk = false;
		}
		else
		{
			std::copy_n(m_bytes.begin() + m_pos, size, buffer);
			m_pos += size;
		}
	}
}
