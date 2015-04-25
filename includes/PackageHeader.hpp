/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PackageHeader.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 03:40:52 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/24 18:50:31 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PACKAGEHEADER_HPP
# define PACKAGEHEADER_HPP
# include <vector>
# include <string>
# include <iostream>

namespace octo
{
	/*!	
	 *	\ingroup Package
	 *	\brief Store package header information
	 *
	 *	This container store a table indicating position and size of each
	 *	packaged files.<br>
	 *	This class is the key of package system. For creating a package, the
	 *	compiler build an header with datas of inputs files. For reading a package
	 *	the header is used as table of matter to finding packaged files.<br>
	 *
	 *	For each file packaged they are an Entry in package header storing
	 *	the name, the type, the position offset and the size of the file.<br>
	 *
	 *	You can access to theses datas with getEntry().
	 *	
	 */
	class PackageHeader
	{
	public:
		enum class EntryType : std::uint8_t;
		struct Entry;
	private:
		typedef std::vector<Entry>				Entries;
	public:
		/*!	Iterator constant an entries collection */
		typedef Entries::const_iterator			const_iterator;

		/*!	Key of a packaged ressource */
		typedef std::uint64_t					EntryKey;

		/*!	The null key identifier */
		static constexpr std::uint64_t const	NullEntryKey =
			std::numeric_limits<std::uint64_t>::max();

		/*!	Add an entry to the table
		 *	\param type Type of ressource packaged
		 *	\param name The name of the file
		 *	\param offset The position in the file relative to the end of header
		 *	(this means the first file must be always an offset of 0).
		 *	\param size Size of the file
		 */
		void				addEntry(EntryType type, std::string const& name,
									 std::uint64_t offset, std::uint64_t size);

		/*!	Return true if \a key is a valid entry key */
		bool				entryExists(EntryKey key)const;

		/*!	Get entry datas */
		bool				getEntry(EntryKey key, Entry& entry)const;

		/*!	Get the entry name */
		std::string const&	getEntryName(EntryKey key)const;

		/*!	Get the entry type */
		EntryType			getEntryType(EntryKey key)const;

		/*!	Get the offset of the datas in package.
		 *
		 *	This offset is relative to the end of header table, so
		 *	this value must be added to byteCount() to obtains the
		 *	real position offset.
		 */
		std::uint64_t		getEntryOffset(EntryKey key)const;

		/*!	Return the size(in bytes) of an entry */
		std::uint64_t		getEntrySize(EntryKey key)const;

		/*!	Return the first key of entry of a type given */
		std::uint64_t		getFirstEntry(EntryType type)const;

		/*!	Return the count of entry of a type given */
		std::uint64_t		getEntryCount(EntryType type)const;

		/*!	Find an entry by specifying his type and his name
		 *
		 *	\return the key of the entry, or NullEntryKey if no entry is corresponding.
		 */
		std::uint64_t		findEntryByName(EntryType type, std::string const& fileName)const;

		/*!	Return the count of entries */
		std::uint64_t		count()const;

		/*!	Return the count of bytes used to store the header datas
		 *
		 *	This function must be called after all entries are added.
		 */
		std::uint64_t		byteCount()const;

		/*!	Return the count of bytes used to store the packaged datas
		 *
		 *	This function must be called after all entries are added.
		 */
		std::uint64_t		packagedByteCount()const;

		/*!	Return an iterator on the first element of the entry table */
		const_iterator		begin()const;

		/*!	Return an iterator on the end of the entry table */
		const_iterator		end()const;

		/*!	Write header datas */
		bool				write(std::ostream& os)const;

		/*!	Read header datas */
		bool				read(std::istream& is);
	private:
		Entries	m_entries;
	};

	/*!	Identifiers of entry type */
	enum class PackageHeader::EntryType : std::uint8_t
	{
		Font,
		Texture,
		Sound,
		Text,
		Palette,
		Count,
		Invalid
	};

	/*!	Entry data */
	struct PackageHeader::Entry
	{
		Entry();
		Entry(std::string const& name, std::uint64_t offset, std::uint64_t size, EntryType type);

		std::string		name;
		std::uint64_t	offset;
		std::uint64_t	size;
		EntryType		type;
	};
}

#endif
