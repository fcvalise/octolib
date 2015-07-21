/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceManagerImp.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/27 18:39:42 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/30 15:26:44 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOURCEMANAGERIMP_HPP
# define RESOURCEMANAGERIMP_HPP
# include "PackageHeader.hpp"
# include "PackageReader.hpp"
# include "IResourceListener.hpp"
# include "Palette.hpp"
# include "ColorWheel.hpp"
# include "SpriteAnimation.hpp"
# include "SpriteSheet.hpp"
# include "LevelMap.hpp"
# include "../ResourceLoading.hpp"

# include <memory>
# include <vector>
# include <cassert>
# include <stdexcept>
# include <map>

# include <SFML/Graphics/Font.hpp>
# include <SFML/Graphics/Texture.hpp>
# include <SFML/System/String.hpp>
# include <SFML/Audio/SoundBuffer.hpp>

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
		class ResourceLoader
		{
		};

		template <>
		class ResourceLoader<details::StreamedResource<sf::Font>>
		{
		public:
			inline static bool	load(ByteArray const& buffer, details::StreamedResource<sf::Font>& font)
			{
				return (font.setBuffer(buffer));
			}
		};

		template <>
		class ResourceLoader<sf::Texture>
		{
		public:
			inline static bool	load(ByteArray const& buffer, sf::Texture& texture)
			{
				return (texture.loadFromMemory(buffer.bytes(), buffer.size()));
			}
		};

		template <>
		class ResourceLoader<sf::SoundBuffer>
		{
		public:
			inline static bool	load(ByteArray const& buffer, sf::SoundBuffer& sound)
			{
				return (sound.loadFromMemory(buffer.bytes(), buffer.size()));
			}
		};

		template <>
		class ResourceLoader<sf::String>
		{
		public:
			inline static bool	load(ByteArray const& buffer, sf::String& text)
			{
				std::basic_string<std::uint32_t>	utf32;

				sf::Utf8::toUtf32(buffer.begin(), buffer.end(), std::back_inserter(utf32));
				text = utf32;
				return (true);
			}
		};

		template <>
		class ResourceLoader<Palette>
		{
		public:
			inline static bool	load(ByteArray const& buffer, Palette& palette)
			{
				return (palette.loadFromMemory(buffer));
			}
		};

		template <>
		class ResourceLoader<ColorWheel>
		{
		public:
			inline static bool	load(ByteArray const& buffer, ColorWheel& palette)
			{
				return (palette.loadFromMemory(buffer));
			}
		};

		template <>
		class ResourceLoader<SpriteSheet>
		{
		public:
			inline static bool	load(ByteArray const& buffer, SpriteSheet& sheet)
			{
				return (sheet.loadFromMemory(buffer));
			}
		};

		template <>
		class ResourceLoader<SpriteAnimation>
		{
		public:
			inline static bool	load(ByteArray const& buffer, SpriteAnimation& animation)
			{
				return (animation.loadFromMemory(buffer));
			}
		};

		template <>
		class ResourceLoader<LevelMap>
		{
		public:
			inline static bool	load(ByteArray const& buffer, LevelMap & map)
            {
				return (map.loadFromMemory(buffer));
			}
		};

		template <class T>
		class ResourceManagerImp
		{
		public:
			typedef std::function<bool(ByteArray const&, T& resource)>		Loader;

			class ILoader
			{
			public:
				virtual ~ILoader();
				virtual bool load(ByteArray const& buffer, T& resource) = 0;
			};

			explicit ResourceManagerImp(PackageHeader::EntryType type);
			~ResourceManagerImp();

			bool			loadPackage(PackageReader& reader, IResourceListener* listener);
			void			loadPackageAsync(PackageReader& reader, ResourceLoading::LoadActions& actions);
			T const&		get(std::string const& key)const;
		private:
			PackageHeader::EntryType const	m_type;
			std::map<std::string, T const*>	m_resources;
		};
	}
}

#include "ResourceManagerImp.hxx"
#endif
