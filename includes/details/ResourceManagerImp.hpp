/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceManagerImp.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/27 18:39:42 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/28 12:37:54 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOURCEMANAGERIMP_HPP
# define RESOURCEMANAGERIMP_HPP
# include "PackageHeader.hpp"
# include "PackageReader.hpp"
# include "IResourceListener.hpp"

# include <memory>
# include <vector>
# include <cassert>

namespace octo
{
	namespace details
	{
		/*!	Allow to use streamed resource with resource manager
		 *
		 *	sf::Font and sf::Music are not loaded in one pass but they are
		 *	streamed on demand.<br>
		 *	This adapter class combine a buffer filled by entire datas from the resource
		 *	and the resource himself, which read the buffer when required.
		 */
		template <class T>
		class StreamedResource
		{
		public:
			bool				setBuffer(std::vector<char> const& buffer)
			{
				m_buffer.assign(buffer.begin(), buffer.end());
				return (m_resource.loadFromMemory(&m_buffer.front(), m_buffer.size()));
			}

			T const&			get()const
			{
				return (m_resource);
			}
		private:
			std::vector<char>	m_buffer;
			T					m_resource;
		};

		template <class T>
		class ResourceManagerImp
		{
		public:
			class ILoader
			{
			public:
				virtual ~ILoader(){}
				virtual bool load(std::vector<char> const& buffer, T& resource) = 0;
			};

			explicit ResourceManagerImp(PackageHeader::EntryType type) :
				m_type(type),
				m_offset(0),
				m_count(0)
			{
			}

			~ResourceManagerImp()
			{
				m_resources.reset();
				m_offset = 0;
				m_count = 0;
			}

			bool			loadPackage(PackageReader& reader,
										ILoader&& loader,
										IResourceListener* listener)
			{
				PackageHeader const&	header = reader.getHeader();
				std::uint64_t			offset = header.getFirstEntry(m_type);
				std::uint64_t			count = header.getEntryCount(m_type);
				std::uint64_t			key = PackageHeader::NullEntryKey;
				std::vector<char>		buffer;

				if (offset == PackageHeader::NullEntryKey || count == 0)
					return (true);
				m_offset = offset;
				m_count = count;
				m_resources.reset(new T[count]);
				for (std::uint64_t i = 0; i < count; ++i)
				{
					key = i + m_offset;
					if (listener)
						listener->progress(header.getEntryName(key),
										   header.getEntryType(key),
										   i, count);
					if (reader.load(buffer, key) == false)
					{
						if (listener)
							listener->error("key " + std::to_string(key) + " not found");
						return (false);
					}
					if (loader.load(buffer, m_resources[i]) == false)
					{
						if (listener)
							listener->error("error when loading key " + std::to_string(key));
						return (false);
					}
				}
				return (true);
			}

			T const&		get(std::uint64_t key)const
			{
				assert(key >= m_offset && key < (m_offset + m_count));

				return (m_resources[key - m_offset]);
			}
		private:
			std::unique_ptr<T[]>			m_resources;
			PackageHeader::EntryType const	m_type;
			std::uint64_t					m_offset;
			std::uint64_t					m_count;
		};
	}
}

#endif
