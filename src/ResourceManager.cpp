/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceManager.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/27 18:30:13 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/27 19:53:34 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ResourceManager.hpp"
#include "details/ResourceManagerImp.hpp"

namespace octo
{
	namespace
	{
		class FontLoader : public details::ResourceManagerImp<sf::Font>::ILoader
		{
		public:
			bool	load(std::vector<char> const& buffer, sf::Font& font)
			{
				return (font.loadFromMemory(&buffer.front(), buffer.size()));
			}
		};

		class TextureLoader : public details::ResourceManagerImp<sf::Texture>::ILoader
		{
		public:
			bool	load(std::vector<char> const& buffer, sf::Texture& texture)
			{
				return (texture.loadFromMemory(&buffer.front(), buffer.size()));
			}
		};

		class SoundLoader : public details::ResourceManagerImp<sf::SoundBuffer>::ILoader
		{
		public:
			bool	load(std::vector<char> const& buffer, sf::SoundBuffer& sound)
			{
				return (sound.loadFromMemory(&buffer.front(), buffer.size()));
			}
		};

		class TextLoader : public details::ResourceManagerImp<sf::String>::ILoader
		{
		public:
			bool	load(std::vector<char> const& buffer, sf::String& text)
			{
				std::string	temp(buffer.begin(), buffer.end());

				text = temp;
				return (true);
			}
		};
	}

	ResourceManager::ResourceManager() :
		m_fontManager(PackageHeader::EntryType::Font),
		m_textureManager(PackageHeader::EntryType::Texture),
		m_soundManager(PackageHeader::EntryType::Sound),
		m_textManager(PackageHeader::EntryType::Text)
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
		return (true);
	}

	sf::Font const&	ResourceManager::getFont(std::uint64_t key)const
	{
		return (m_fontManager.get(key));
	}

	sf::Texture const&	ResourceManager::getTexture(std::uint64_t key)const
	{
		return (m_textureManager.get(key));
	}

	sf::SoundBuffer const&	ResourceManager::getSound(std::uint64_t key)const
	{
		return (m_soundManager.get(key));
	}

	sf::String const&	ResourceManager::getText(std::uint64_t key)const
	{
		return (m_textManager.get(key));
	}
}
