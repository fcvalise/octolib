/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PackageReader.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 07:03:10 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/28 10:45:09 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PackageReader.hpp"
#include "details/PackageCommons.hpp"

namespace octo
{
	bool	PackageReader::open(std::string const& fileName)
	{
		m_file.open(fileName.c_str(), std::ios_base::binary);
		if (m_file.is_open() && m_header.read(m_file))
		{
			details::generateMask(m_encryptionMask, details::PackageEncryptionMaskSize,
								  m_header.byteCount());
			return (true);
		}
		return (false);
	}

	bool	PackageReader::load(std::vector<char>& buffer, std::uint64_t key)
	{
		PackageHeader::Entry	entry;

		if (isOpen() && m_header.getEntry(key, entry))
		{
			m_file.seekg(entry.offset + m_header.byteCount(), std::istream::beg);
			buffer.resize(entry.size);
			m_file.read(&buffer.front(), entry.size);
			details::xorEncryptDecrypt(buffer.begin(), buffer.end(), m_encryptionMask);
			return (true);
		}
		return (false);
	}

	bool	PackageReader::isOpen()const
	{
		return (m_file.is_open());
	}
	
	PackageHeader const&	PackageReader::getHeader()const
	{
		return (m_header);
	}
}
