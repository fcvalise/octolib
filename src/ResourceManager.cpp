/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceManager.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/27 18:30:13 by irabeson          #+#    #+#             */
/*   Updated: 2015/07/23 13:32:05 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ResourceManager.hpp"
#include "Palette.hpp"
#include "ColorWheel.hpp"
#include "SpriteSheet.hpp"
#include "SpriteAnimation.hpp"
#include "LevelMap.hpp"
#include "details/ResourceManagerImp.hpp"

namespace octo
{
	ResourceManager::ResourceManager() :
		m_fontManager(PackageHeader::EntryType::Font),
		m_textureManager(PackageHeader::EntryType::Texture),
		m_soundManager(PackageHeader::EntryType::Sound),
		m_textManager(PackageHeader::EntryType::Text),
		m_paletteManager(PackageHeader::EntryType::Palette),
		m_colorWheelManager(PackageHeader::EntryType::ColorWheel),
		m_spriteSheetManager(PackageHeader::EntryType::SpriteSheet),
		m_spriteAnimationManager(PackageHeader::EntryType::SpriteAnimation),
		m_characterAnimationManager(PackageHeader::EntryType::CharacterAnimation),
        m_levelMapManager(PackageHeader::EntryType::LevelMap) 
	{
	}

	bool	ResourceManager::loadPackage(std::string const& fileName,
										 IResourceListener* listener)
	{
		PackageReader	reader;

		if (reader.open(fileName) == false)
			return (false);
		m_fontManager.loadPackage(reader, listener);
		m_textureManager.loadPackage(reader, listener);
		m_soundManager.loadPackage(reader, listener);
		m_textManager.loadPackage(reader, listener);
		m_paletteManager.loadPackage(reader, listener);
		m_colorWheelManager.loadPackage(reader, listener);
		m_spriteSheetManager.loadPackage(reader, listener);
		m_spriteAnimationManager.loadPackage(reader, listener);
		m_characterAnimationManager.loadPackage(reader, listener);
		m_levelMapManager.loadPackage(reader, listener);
		return (true);
	}

	ResourceLoading	ResourceManager::loadPackageAsync(std::string const& fileName, IResourceListener* listener)
	{
		ResourceLoading::LoadActions	actions;
		PackageReader					reader;

		if (reader.open(fileName))
		{
			m_fontManager.loadPackageAsync(reader, actions);
			m_textureManager.loadPackageAsync(reader, actions);
			m_soundManager.loadPackageAsync(reader, actions);
			m_textManager.loadPackageAsync(reader, actions);
			m_paletteManager.loadPackageAsync(reader, actions);
			m_colorWheelManager.loadPackageAsync(reader, actions);
			m_spriteSheetManager.loadPackageAsync(reader, actions);
			m_spriteAnimationManager.loadPackageAsync(reader, actions);
			m_characterAnimationManager.loadPackageAsync(reader, actions);
			m_levelMapManager.loadPackageAsync(reader, actions);
		}
		return (ResourceLoading(std::move(reader), std::move(actions), listener));
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

	CharacterAnimation const&	ResourceManager::getCharacterAnimation(std::string const& fileName)const
	{
		return (m_characterAnimationManager.get(fileName));
	}
	
	LevelMap const&		ResourceManager::getLevelMap(std::string const& fileName)const
	{
		return (m_levelMapManager.get(fileName));
	}
}
