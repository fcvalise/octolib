/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceManager.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/27 05:03:00 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/30 14:51:15 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOURCEMANAGER_HPP
# define RESOURCEMANAGER_HPP
# include "NonCopyable.hpp"
# include "PackageHeader.hpp"
# include "details/ResourceManagerImp.hpp"

# include <SFML/Graphics/Font.hpp>
# include <SFML/Graphics/Texture.hpp>
# include <SFML/System/String.hpp>
# include <SFML/Audio/SoundBuffer.hpp>

namespace octo
{
	class Package;
	class Palette;
	class ColorWheel;
	class SpriteSheet;
	class SpriteAnimation;
	class IResourceListener;
    class LevelMap;

	/*!
	 *	\ingroup Resource
	 *	Manage all game resources
	 *
	 *	Resource datas are loaded from a package file.<br>
	 *	Each ressource have a defined file extension:
	 *	<TABLE>
	 *	<TR>
	 *		<TH>Extension</TH>
	 *		<TH>Description</TH>
	 *	</TR>
	 *	<TR>
	 *		<TD>opa</TD>
	 *		<TD>Palette files</TD>
	 *	</TR>
	 *	<TR>
	 *		<TD>ocw</TD>
	 *		<TD>Color wheel files</TD>
	 *	</TR>
	 *	<TR>
	 *		<TD>oss</TD>
	 *		<TD>Sprite sheet files</TD>
	 *	</TR>
	 *	<TR>
	 *		<TD>osa</TD>
	 *		<TD>Sprite animation files</TD>
	 *	</TR>
	 *	</TABLE>
	 */
	class ResourceManager : public NonCopyable
	{
	public:
		ResourceManager();

		/*!	Load a package file */
		bool					loadPackage(std::string const& fileName, IResourceListener* listener);

		/*!	Start a package loading */
		ResourceLoading			loadPackageAsync(std::string const& fileName, IResourceListener* listener);

		/*!	Get a font
		 */
		sf::Font const&			getFont(std::string const& fileName)const;

		/*!	Get a texture
		 */
		sf::Texture const&		getTexture(std::string const& fileName)const;

		/*!	Get a sound buffer
		 */
		sf::SoundBuffer const&	getSound(std::string const& fileName)const;

		/*!	Get a text
		 */
		sf::String const&		getText(std::string const& fileName)const;

		/*!	Get a palette
		 */
		Palette const&			getPalette(std::string const& fileName)const;

		/*!	Get a color wheel
		 */
		ColorWheel const&		getColorWheel(std::string const& fileName)const;

		/*!	Get a sprite sheet
		 */
		SpriteSheet const&		getSpriteSheet(std::string const& fileName)const;

		/*!	Get a sprite animation
		 */
		SpriteAnimation const&	getSpriteAnimation(std::string const& fileName)const;

		/*!	Get a level map
		 */
		LevelMap const&         getLevelMap(std::string const& fileName)const;
	private:
		typedef details::StreamedResource<sf::Font>		Font;

		details::ResourceManagerImp<Font>				m_fontManager;
		details::ResourceManagerImp<sf::Texture>		m_textureManager;
		details::ResourceManagerImp<sf::SoundBuffer>	m_soundManager;
		details::ResourceManagerImp<sf::String>			m_textManager;
		details::ResourceManagerImp<Palette>			m_paletteManager;
		details::ResourceManagerImp<ColorWheel>			m_colorWheelManager;
		details::ResourceManagerImp<SpriteSheet>		m_spriteSheetManager;
		details::ResourceManagerImp<SpriteAnimation>		m_spriteAnimationManager;
		details::ResourceManagerImp<LevelMap>           m_levelMapManager;
	};
}

#endif
