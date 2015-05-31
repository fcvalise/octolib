/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceManagerImp.hxx                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/25 22:53:57 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/30 14:52:56 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace octo
{
	namespace details
	{
		template <class T>
		ResourceManagerImp<T>::ResourceManagerImp(PackageHeader::EntryType type) :
			m_type(type)
		{
		}

		template <class T>
		ResourceManagerImp<T>::~ResourceManagerImp()
		{
			auto	it = m_resources.begin();

			while (it != m_resources.end())
			{
				delete it->second;
				it = m_resources.erase(it);
			}
		}

		template <class T>
		void	ResourceManagerImp<T>::loadPackageAsync(PackageReader& reader, ResourceLoading::LoadActions& actions)
		{
			PackageHeader const&			header = reader.getHeader();
			std::uint64_t const				count = header.getEntryCount(m_type);

			for (std::uint64_t i = 0; i < count; ++i)
			{
				ResourceLoading::LoadAction	action =
					[this, i, count](PackageReader& reader, IResourceListener* listener)
					{
						PackageHeader const&	header = reader.getHeader();
						std::uint64_t const		offset = header.getFirstEntry(m_type);
						std::uint64_t const		key = i + offset;
						std::unique_ptr<T>		resource(new T);
						std::string const&		resourceName = header.getEntryName(key);
						ByteArray				buffer;

						if (listener)
							listener->progress(resourceName, header.getEntryType(key), i, count);
						if (m_resources.find(resourceName) != m_resources.end())
						{
							if (listener)
								listener->error("error when loading '" + resourceName + "': name conflict");
							return (false);
						}
						if (reader.load(buffer, key) == false)
						{
							if (listener)
								listener->error("error when loading '" + resourceName + "': key " + std::to_string(key) + " not found");
							return (false);
						}
						if (ResourceLoader<T>::load(buffer, *resource) == false)
						{
							if (listener)
							{
								listener->error("error when loading '" + resourceName + "': unsupported file format");
								listener->finished();
							}
							return (false);
						}
						m_resources.emplace(resourceName, resource.release());
						return (true);
					};
				actions.emplace_back(action);
			}
		}

		template <class T>
		bool	ResourceManagerImp<T>::loadPackage(PackageReader& reader,
												   IResourceListener* listener)
		{
			PackageHeader const&		header = reader.getHeader();
			std::uint64_t const			offset = header.getFirstEntry(m_type);
			std::uint64_t const			count = header.getEntryCount(m_type);
			std::uint64_t				key = PackageHeader::NullEntryKey;
			ByteArray					buffer;

			if (offset == PackageHeader::NullEntryKey || count == 0)
				return (true);
			for (std::uint64_t i = 0; i < count; ++i)
			{
				key = i + offset;
				std::unique_ptr<T>	resource(new T);
				std::string const&	resourceName = header.getEntryName(key);

				if (listener)
					listener->progress(resourceName, header.getEntryType(key), i, count);
				if (m_resources.find(resourceName) != m_resources.end())
				{
					if (listener)
					{
						listener->error("error when loading '" + resourceName + "': name conflict");
					}
					return (false);
				}
				if (reader.load(buffer, key) == false)
				{
					if (listener)
					{
						listener->error("error when loading '" + resourceName + "': key " + std::to_string(key) + " not found");
					}
					return (false);
				}
				if (ResourceLoader<T>::load(buffer, *resource) == false)
				{
					if (listener)
					{
						listener->error("error when loading '" + resourceName + "': unsupported file format");
					}
					return (false);
				}
				m_resources.emplace(resourceName, resource.release());
			}
			if (listener)
				listener->finished();
			return (true);
		}

		template <class T>
		T const&	ResourceManagerImp<T>::get(std::string const& key)const
		{
			auto	it = m_resources.find(key);
			
			if (it == m_resources.end())
				throw std::range_error("resource manager: not found: '" + key + "'");
			return (*(it->second));
		}

		template <class T>
		ResourceManagerImp<T>::ILoader::~ILoader()
		{
		}
	}
}
