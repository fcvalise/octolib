/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceManagerImp.hxx                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/25 22:53:57 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/25 22:54:22 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace octo
{
	namespace details
	{
		template <class T>
		ResourceManagerImp<T>::ResourceManagerImp(PackageHeader::EntryType type) :
			m_type(type),
			m_offset(0),
			m_count(0)
		{
		}

		template <class T>
		ResourceManagerImp<T>::~ResourceManagerImp()
		{
			m_resources.reset();
			m_offset = 0;
			m_count = 0;
		}

		template <class T>
		bool	ResourceManagerImp<T>::loadPackage(PackageReader& reader,
												   ILoader&& loader,
												   IResourceListener* listener)
		{
			PackageHeader const&	header = reader.getHeader();
			std::uint64_t			offset = header.getFirstEntry(m_type);
			std::uint64_t			count = header.getEntryCount(m_type);
			std::uint64_t			key = PackageHeader::NullEntryKey;
			ByteArray				buffer;

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

		template <class T>
		T const&	ResourceManagerImp<T>::get(std::uint64_t key)const
		{
			if (key < m_offset || key >= (m_offset + m_count))
				throw std::range_error("resource manager: get by key: invalid key: " + std::to_string(key));
			return (m_resources[key - m_offset]);
		}

		template <class T>
		ResourceManagerImp<T>::ILoader::~ILoader()
		{
		}
	}
}
