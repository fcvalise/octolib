/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceManager.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/27 18:30:13 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/29 19:40:38 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ResourceManager.hpp"
#include "Palette.hpp"
#include "ColorWheel.hpp"
#include "SpriteSheet.hpp"
#include "SpriteAnimation.hpp"
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

		class SpriteSheetLoader : public details::ResourceManagerImp<SpriteSheet>::ILoader
		{
			bool	load(ByteArray const& buffer, SpriteSheet& sheet)
			{
				return (sheet.loadFromMemory(buffer));
			}
		};

		class SpriteAnimationLoader : public details::ResourceManagerImp<SpriteAnimation>::ILoader
		{
			bool	load(ByteArray const& buffer, SpriteAnimation& animation)
			{
				return (animation.loadFromMemory(buffer));
			}
		};
	}

	ResourceManager::ResourceManager() :
		m_fontManager(PackageHeader::EntryType::Font),
		m_textureManager(PackageHeader::EntryType::Texture),
		m_soundManager(PackageHeader::EntryType::Sound),
		m_textManager(PackageHeader::EntryType::Text),
		m_paletteManager(PackageHeader::EntryType::Palette),
		m_colorWheelManager(PackageHeader::EntryType::ColorWheel),
		m_spriteSheetManager(PackageHeader::EntryType::SpriteSheet),
		m_spriteAnimationManager(PackageHeader::EntryType::SpriteAnimation)
	{
	}

	bool	ResourceManager::loadPackage(std::string const& fileName,
										 IResourceListener* listener)
	{
		PackageReader	reader;

		if (reader.open(fileName) == false)
			return (false);
		m_fontManager.loadPackage(reader, FontLoader(), listener);
		m_textureManager.loadPackage(reader, TextureLoader(), listener);
		m_soundManager.loadPackage(reader, SoundLoader(), listener);
		m_textManager.loadPackage(reader, TextLoader(), listener);
		m_paletteManager.loadPackage(reader, PaletteLoader(), listener);
		m_colorWheelManager.loadPackage(reader, ColorWheelLoader(), listener);
		m_spriteSheetManager.loadPackage(reader, SpriteSheetLoader(), listener);
		m_spriteAnimationManager.loadPackage(reader, SpriteAnimationLoader(), listener);
		return (true);
	}

	sf::Font const&		ResourceManager::getFont(std::string const& fileName)const
	{
		return (m_fontManager.get(fileName).get());
	}

	sf::Texture const&	ResourceManager::getTexture(std::string const& fileName)const
	{
		return (m_textureManager.get(fileName));
	}

	sf::SoundBuffer const&	ResourceManager::getSound(std::string const& fileName)const
	{
		return (m_soundManager.get(fileName));
	}
	
	sf::String const&	ResourceManager::getText(std::string const& fileName)const
	{
		return (m_textManager.get(fileName));
	}

	Palette const&		ResourceManager::getPalette(std::string const& fileName)const
	{
		return (m_paletteManager.get(fileName));
	}

	ColorWheel const&		ResourceManager::getColorWheel(std::string const& fileName)const
	{
		return (m_colorWheelManager.get(fileName));
	}

	SpriteSheet const&		ResourceManager::getSpriteSheet(std::string const& fileName)const
	{
		return (m_spriteSheetManager.get(fileName));
	}

	SpriteAnimation const&		ResourceManager::getSpriteAnimation(std::string const& fileName)const
	{
		return (m_spriteAnimationManager.get(fileName));
	}
}
