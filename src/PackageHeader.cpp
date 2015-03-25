/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PackageHeader.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 03:38:21 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/26 04:13:19 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PackageHeader.hpp"

namespace octo
{
	namespace details
	{
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

	void	PackageHeader::addEntry(Entry const& entry)
	{
		m_entries.push_back(entry);
	}

	bool	PackageHeader::getEntry(EntryKey key, Entry& entry)const
	{
		if (key < m_entries.size())
		{
			entry = m_entries[key];
			return (true);
		}
		else
		{
			return (false);
		}
	}

	std::string const&	PackageHeader::getEntryName(EntryKey key)const
	{
		return (m_entries[key].name);
	}

	PackageHeader::EntryType	PackageHeader::getEntryType(EntryKey key)const
	{
		return (m_entries[key].type);
	}

	bool	PackageHeader::write(std::ostream& os)const
	{
		std::uint64_t	count = m_entries.size();

		details::write(os, count);
		for (auto const& entry : m_entries)
			details::writeEntry(os, entry);
		return (true);
	}

	bool	PackageHeader::read(std::istream& is)
	{
		std::uint64_t	count = 0;
		Entry		entry;

		details::read(is, count);
		m_entries.clear();
		m_entries.resize(count);
		for (std::uint64_t i = 0; i < count; ++i)
			details::readEntry(is, m_entries[i]);
		m_entries.shrink_to_fit();
		return (true);
	}

	std::uint64_t	PackageHeader::count()const
	{
		return (m_entries.size());
	}
	
	std::uint64_t	PackageHeader::byteCount()const
	{
		std::uint64_t	result = 0;

		result += sizeof(std::uint64_t);
		for (auto const& entry : m_entries)
		{
			result += sizeof(std::uint64_t) * 3 +
					  sizeof(EntryType) +
					  entry.name.size();
		}
		return (result);
	}

	PackageHeader::const_iterator	PackageHeader::begin()const
	{
		return (m_entries.begin());
	}

	PackageHeader::const_iterator	PackageHeader::end()const
	{
		return (m_entries.end());
	}
}
