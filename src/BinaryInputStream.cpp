/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BinaryInputStream.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/01 14:52:11 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/02 07:32:00 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BinaryInputStream.hpp"
#include <algorithm>

namespace octo
{
	BinaryInputStream::BinaryInputStream(ByteArray const& bytes) :
		m_bytes(bytes),
		m_it(m_bytes.begin()),
		m_isOk(true)
	{
	}
	
	bool	BinaryInputStream::isOk()const
	{
		return (m_isOk);
	}

	bool	BinaryInputStream::hasDataToRead()const
	{
		return (m_it != m_bytes.end());
	}

	BinaryInputStream::operator bool()const
	{
		return (isOk() && hasDataToRead());
	}

	void	BinaryInputStream::read(char* buffer, std::size_t size)
	{
		std::size_t	remaining = std::distance(m_it, m_bytes.end());

		if (m_isOk == false || remaining == 0 || remaining < size)
		{
			m_isOk = false;
		}
		else
		{
			std::copy_n(m_it, size, buffer);
			m_it += size;
		}
	}
}
