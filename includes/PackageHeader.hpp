/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PackageHeader.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 03:40:52 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/26 04:18:59 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PACKAGEHEADER_HPP
# define PACKAGEHEADER_HPP
# include <vector>
# include <string>
# include <iostream>

namespace octo
{
	/*!	Package header datas
	 *
	 */
	class PackageHeader
	{
	public:
		enum class EntryType : std::uint8_t
		{
			Font,
			Texture,
			Sound,
			Text,
			Invalid
		};

		struct Entry
		{
			Entry();
			Entry(std::string const& name, std::uint64_t offset, std::uint64_t size, EntryType type);

			std::string		name;
			std::uint64_t	offset;
			std::uint64_t	size;
			EntryType		type;
		};
	private:
		typedef std::vector<Entry>			Entries;
	public:
		typedef Entries::const_iterator		const_iterator;
		typedef std::uint64_t				EntryKey;

		void				addEntry(EntryType type, std::string const& name,
									 std::uint64_t offset, std::uint64_t size);
		void				addEntry(Entry const& entry);

		bool				getEntry(EntryKey key, Entry& entry)const;
		std::string const&	getEntryName(EntryKey key)const;
		EntryType			getEntryType(EntryKey key)const;
		

		bool			write(std::ostream& os)const;
		bool			read(std::istream& is);
		std::uint64_t	count()const;
		std::uint64_t	byteCount()const;
		const_iterator	begin()const;
		const_iterator	end()const;
	private:
		Entries	m_entries;
	};
}

#endif
