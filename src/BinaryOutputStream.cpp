/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BinaryOutputStream.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 06:22:46 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/24 19:12:37 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BinaryOutputStream.hpp"

namespace octo
{
	BinaryOutputStream::BinaryOutputStream(ByteArray& bytes) :
		m_bytes(bytes)
	{
	}

	void	BinaryOutputStream::writeBytes(char const* buffer, std::size_t size)
	{
		m_bytes.append(buffer, size);
	}

	void	BinaryOutputStream::writeBytes(ByteArray const& buffer)
	{
		m_bytes.append(buffer.bytes(), buffer.size());
	}
}
