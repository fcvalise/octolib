/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceManager.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/27 18:30:13 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/30 10:24:10 by irabeson         ###   ########.fr       */
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
		m_fontManager.loadPackage(reader, listener);
		m_textureManager.loadPackage(reader, listener);
		m_soundManager.loadPackage(reader, listener);
		m_textManager.loadPackage(reader, listener);
		m_paletteManager.loadPackage(reader, listener);
		m_colorWheelManager.loadPackage(reader, listener);
		m_spriteSheetManager.loadPackage(reader, listener);
		m_spriteAnimationManager.loadPackage(reader, listener);
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
