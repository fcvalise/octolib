/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceManagerImp.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/27 18:39:42 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/29 20:07:11 by irabeson         ###   ########.fr       */
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
# include <stdexcept>
# include <map>

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
			bool		setBuffer(ByteArray const& buffer)
			{
				m_buffer.assign(buffer.begin(), buffer.end());
				return (m_resource.loadFromMemory(m_buffer.bytes(), m_buffer.size()));
			}

			T const&	get()const
			{
				return (m_resource);
			}
		private:
			ByteArray	m_buffer;
			T			m_resource;
		};

		template <class T>
		class ResourceManagerImp
		{
		public:
			class ILoader
			{
			public:
				virtual ~ILoader();
				virtual bool load(ByteArray const& buffer, T& resource) = 0;
			};

			explicit ResourceManagerImp(PackageHeader::EntryType type);
			~ResourceManagerImp();

			bool			loadPackage(PackageReader& reader,
										ILoader&& loader,
										IResourceListener* listener);
			T const&		get(std::string const& key)const;
		private:
			PackageHeader::EntryType const	m_type;
			std::map<std::string, T const*>	m_resources;	// TODO rename to resources
		};
	}
}

#include "ResourceManagerImp.hxx"
#endif
