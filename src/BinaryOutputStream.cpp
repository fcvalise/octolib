/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BinaryOutputStream.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 06:22:46 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/02 07:33:30 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BinaryOutputStream.hpp"

namespace octo
{
	BinaryOutputStream::BinaryOutputStream(ByteArray& bytes) :
		m_bytes(bytes)
	{
	}

	void	BinaryOutputStream::write(char const* buffer, std::size_t size)
	{
		m_bytes.append(buffer, size);
	}
}
