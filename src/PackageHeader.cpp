/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PackageHeader.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 03:38:21 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/27 18:09:57 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PackageHeader.hpp"
#include <numeric>

namespace octo
{
	namespace details
	{
		static constexpr std::uint64_t const	PackageMagic = 0xf03b3a02;

		template<typename T> 
		void	write(std::ostream& os, T const& value) 
		{ 
			os.write(reinterpret_cast<char const*>(&value), sizeof(T)); 
		}

		template<typename T> 
		void	read(std::istream& is, T& value) 
		{ 
			is.read(reinterpret_cast<char*>(&value), sizeof(T)); 
		}

		static void		writeEntry(std::ostream& os, PackageHeader::Entry const& entry)
		{
			std::uint64_t	nameSize = entry.name.size();

			write(os, nameSize);
			write(os, entry.offset);
			write(os, entry.size);
			write(os, entry.type);
			os.write(entry.name.c_str(), nameSize);
		}

		static void		readEntry(std::istream& is, PackageHeader::Entry& entry)
		{
			std::uint64_t				nameSize = 0;
			std::uint64_t				offset = 0;
			std::uint64_t				size = 0;
			PackageHeader::EntryType	type = PackageHeader::EntryType::Invalid;
			std::unique_ptr<char[]>		name;

			read(is, nameSize);
			read(is, offset);
			read(is, size);
			read(is, type);
			name.reset(new char[nameSize]);
			is.read(name.get(), nameSize);
			entry.name.assign(name.get(), nameSize);
			entry.offset = offset;
			entry.size = size;
			entry.type = type;
		}
	}

	PackageHeader::Entry::Entry() :
		offset(0),
		size(0),
		type(EntryType::Invalid)
	{
	}

	PackageHeader::Entry::Entry(std::string const& name, std::uint64_t offset,
										std::uint64_t size, EntryType type) :
		name(name),
		offset(offset),
		size(size),
		type(type)
	{
	}

	void	PackageHeader::addEntry(EntryType type, std::string const& name, std::uint64_t offset, std::uint64_t size)
	{
		m_entries.emplace_back(name, offset, size, type);
	}

	bool	PackageHeader::getEntry(EntryKey key, Entry& entry)const
	{
		if (entryExists(key))
		{
			entry = m_entries[key];
			return (true);
		}
		else
		{
			return (false);
		}
	}

	bool	PackageHeader::entryExists(EntryKey key)const
	{
		return (key < m_entries.size());
	}

	std::string const&	PackageHeader::getEntryName(EntryKey key)const
	{
		return (m_entries[key].name);
	}

	PackageHeader::EntryType	PackageHeader::getEntryType(EntryKey key)const
	{
		return (m_entries[key].type);
	}

	std::uint64_t	PackageHeader::getEntryOffset(EntryKey key)const
	{
		return (m_entries[key].offset);
	}

	std::uint64_t	PackageHeader::getEntrySize(EntryKey key)const
	{
		return (m_entries[key].size);
	}

	std::uint64_t	PackageHeader::getFirstEntry(EntryType type)const
	{
		std::uint64_t	key = 0;

		while (getEntryType(key) != type)
			++key;
		if (key == count())
			return (NullEntryKey);
		else
			return (key);
	}

	std::uint64_t	PackageHeader::getEntryCount(EntryType type)const
	{
		std::uint64_t	key = getFirstEntry(type);
		std::uint64_t	count = 0;

		if (key == NullEntryKey)
			return (NullEntryKey);
		while (getEntryType(key + count) == type)
			++count;
		return (count);
	}

	std::uint64_t	PackageHeader::count()const
	{
		return (m_entries.size());
	}
	
	// HEADER:
	// 1 magic number:			64bits
	// 1 entry count:			64bits
	// For each entry:
	//		1 data offset		64bits
	//		1 data size			64bits
	//		1 name size			64bits
	//		1 name				Variable: defined by value stored in name size field
	//	
	std::uint64_t	PackageHeader::byteCount()const
	{
		std::uint64_t	result = 0;

		result += sizeof(std::uint64_t) * 2;
		for (auto const& entry : m_entries)
		{
			result += sizeof(std::uint64_t) * 3 +
					  sizeof(EntryType) +
					  entry.name.size();
		}
		return (result);
	}

	std::uint64_t	PackageHeader::packagedByteCount()const
	{
		return (std::accumulate(m_entries.begin(), m_entries.end(), 0u,
						[](std::uint64_t value, Entry const& entry)
						{
							return (value + entry.size);
						}));
	}

	PackageHeader::const_iterator	PackageHeader::begin()const
	{
		return (m_entries.begin());
	}

	PackageHeader::const_iterator	PackageHeader::end()const
	{
		return (m_entries.end());
	}

	bool	PackageHeader::write(std::ostream& os)const
	{
		std::uint64_t	count = m_entries.size();
		std::uint64_t	magic = details::PackageMagic;

		details::write(os, magic);
		details::write(os, count);
		for (auto const& entry : m_entries)
			details::writeEntry(os, entry);
		return (true);
	}

	bool	PackageHeader::read(std::istream& is)
	{
		std::uint64_t	magic = 0;
		std::uint64_t	count = 0;
		Entry			entry;

		details::read(is, magic);
		if (magic != details::PackageMagic)
			return (false);
		details::read(is, count);
		m_entries.clear();
		m_entries.resize(count);
		for (std::uint64_t i = 0; i < count; ++i)
			details::readEntry(is, m_entries[i]);
		m_entries.shrink_to_fit();
		return (true);
	}
}
