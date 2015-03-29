/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceManager.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/27 05:03:00 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/29 04:05:54 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOURCEMANAGER_HPP
# define RESOURCEMANAGER_HPP
# include "PackageHeader.hpp"
# include "details/ResourceManagerImp.hpp"

# include <SFML/Graphics/Font.hpp>
# include <SFML/Graphics/Texture.hpp>
# include <SFML/System/String.hpp>
# include <SFML/Audio/SoundBuffer.hpp>

namespace octo
{
	class Package;
	class IResourceListener;

	/*!
	 *	\ingroup Resource
	 *	Manage all game resources
	 *
	 *	Resource datas are loaded from a package files.<br>
	 */
	class ResourceManager
	{

	public:
		ResourceManager();

		bool					loadPackage(std::string const& fileName,
											IResourceListener* listener);

		sf::Font const&			getFont(std::uint64_t key)const;
		sf::Texture const&		getTexture(std::uint64_t key)const;
		sf::SoundBuffer const&	getSound(std::uint64_t key)const;
		sf::String const&		getText(std::uint64_t key)const;
	private:
		typedef details::StreamedResource<sf::Font>		Font;

		PackageReader									m_reader;
		details::ResourceManagerImp<Font>				m_fontManager;
		details::ResourceManagerImp<sf::Texture>		m_textureManager;
		details::ResourceManagerImp<sf::SoundBuffer>	m_soundManager;
		details::ResourceManagerImp<sf::String>			m_textManager;
	};
}

#endif
