/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceManager.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/27 18:30:13 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/05 15:34:12 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ResourceManager.hpp"
#include "Palette.hpp"
#include "ColorWheel.hpp"
#include "details/ResourceManagerImp.hpp"

namespace octo
{
	namespace
	{
		class FontLoader : public details::ResourceManagerImp<details::StreamedResource<sf::Font>>::ILoader
		{
		public:
			bool	load(ByteArray const& buffer, details::StreamedResource<sf::Font>& font)
			{
				return (font.setBuffer(buffer));
			}
		};

		class TextureLoader : public details::ResourceManagerImp<sf::Texture>::ILoader
		{
		public:
			bool	load(ByteArray const& buffer, sf::Texture& texture)
			{
				return (texture.loadFromMemory(buffer.bytes(), buffer.size()));
			}
		};

		class SoundLoader : public details::ResourceManagerImp<sf::SoundBuffer>::ILoader
		{
		public:
			bool	load(ByteArray const& buffer, sf::SoundBuffer& sound)
			{
				return (sound.loadFromMemory(buffer.bytes(), buffer.size()));
			}
		};

		class TextLoader : public details::ResourceManagerImp<sf::String>::ILoader
		{
		public:
			bool	load(ByteArray const& buffer, sf::String& text)
			{
				std::basic_string<std::uint32_t>	utf32;

				sf::Utf8::toUtf32(buffer.begin(), buffer.end(), std::back_inserter(utf32));
				text = utf32;
				return (true);
			}
		};

		class PaletteLoader : public details::ResourceManagerImp<Palette>::ILoader
		{
		public:
			bool	load(ByteArray const& buffer, Palette& palette)
			{
				return (palette.loadFromMemory(buffer));
			}
		};

		class ColorWheelLoader : public details::ResourceManagerImp<ColorWheel>::ILoader
		{
		public:
			bool	load(ByteArray const& buffer, ColorWheel& palette)
			{
				return (palette.loadFromMemory(buffer));
			}
		};
	}

	ResourceManager::ResourceManager() :
		m_fontManager(PackageHeader::EntryType::Font),
		m_textureManager(PackageHeader::EntryType::Texture),
		m_soundManager(PackageHeader::EntryType::Sound),
		m_textManager(PackageHeader::EntryType::Text),
		m_paletteManager(PackageHeader::EntryType::Palette),
		m_colorWheelManager(PackageHeader::EntryType::ColorWheel)
	{
	}

	bool	ResourceManager::loadPackage(std::string const& fileName,
										 IResourceListener* listener)
	{
		if (m_reader.open(fileName) == false)
			return (false);
		m_fontManager.loadPackage(m_reader, FontLoader(), listener);
		m_textureManager.loadPackage(m_reader, TextureLoader(), listener);
		m_soundManager.loadPackage(m_reader, SoundLoader(), listener);
		m_textManager.loadPackage(m_reader, TextLoader(), listener);
		m_paletteManager.loadPackage(m_reader, PaletteLoader(), listener);
		m_colorWheelManager.loadPackage(m_reader, ColorWheelLoader(), listener);
		return (true);
	}

	sf::Font const&	ResourceManager::getFont(std::uint64_t key)const
	{
		return (m_fontManager.get(key).get());
	}

	sf::Font const&		ResourceManager::getFont(std::string const& fileName)const
	{
		std::uint64_t	key = m_reader.getHeader().findEntryByName(PackageHeader::EntryType::Font, fileName);

		if (key == PackageHeader::NullEntryKey)
			throw std::range_error("resource manager: get font by name: " + fileName + " not found");
		return (getFont(key));
	}

	sf::Texture const&	ResourceManager::getTexture(std::uint64_t key)const
	{
		return (m_textureManager.get(key));
	}

	sf::Texture const&	ResourceManager::getTexture(std::string const& fileName)const
	{
		std::uint64_t	key = m_reader.getHeader().findEntryByName(PackageHeader::EntryType::Texture, fileName);

		if (key == PackageHeader::NullEntryKey)
			throw std::range_error("resource manager: get texture by name: " + fileName + " not found");
		return (getTexture(key));
	}

	sf::SoundBuffer const&	ResourceManager::getSound(std::uint64_t key)const
	{
		return (m_soundManager.get(key));
	}

	sf::SoundBuffer const&	ResourceManager::getSound(std::string const& fileName)const
	{
		std::uint64_t	key = m_reader.getHeader().findEntryByName(PackageHeader::EntryType::Sound, fileName);

		if (key == PackageHeader::NullEntryKey)
			throw std::range_error("resource manager: get sound by name: " + fileName + " not found");
		return (getSound(key));
	}

	sf::String const&	ResourceManager::getText(std::uint64_t key)const
	{
		return (m_textManager.get(key));
	}
	
	sf::String const&	ResourceManager::getText(std::string const& fileName)const
	{
		std::uint64_t	key = m_reader.getHeader().findEntryByName(PackageHeader::EntryType::Text, fileName);

		if (key == PackageHeader::NullEntryKey)
			throw std::range_error("resource manager: get text by name: " + fileName + " not found");
		return (getText(key));
	}

	Palette const&		ResourceManager::getPalette(std::uint64_t key)const
	{
		return (m_paletteManager.get(key));
	}

	Palette const&		ResourceManager::getPalette(std::string const& fileName)const
	{
		std::uint64_t	key = m_reader.getHeader().findEntryByName(PackageHeader::EntryType::Palette, fileName);

		if (key == PackageHeader::NullEntryKey)
			throw std::range_error("resource manager: get palette by name: " + fileName + " not found");
		return (getPalette(key));
	}

	ColorWheel const&		ResourceManager::getColorWheel(std::uint64_t key)const
	{
		return (m_colorWheelManager.get(key));
	}

	ColorWheel const&		ResourceManager::getColorWheel(std::string const& fileName)const
	{
		std::uint64_t	key = m_reader.getHeader().findEntryByName(PackageHeader::EntryType::ColorWheel, fileName);

		if (key == PackageHeader::NullEntryKey)
			throw std::range_error("resource manager: get wheel by name: " + fileName + " not found");
		return (getColorWheel(key));
	}
}
