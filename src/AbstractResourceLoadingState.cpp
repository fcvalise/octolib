/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractResourceLoadingState.cpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 15:34:46 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/06 09:47:51 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractResourceLoadingState.hpp"
#include "ResourceManager.hpp"
#include "Application.hpp"

namespace octo
{
	AbstractResourceLoadingState::AbstractResourceLoadingState() :
		m_currentLoading(m_loadings.end()),
		m_currentStep(0u),
		m_totalSteps(0u),
		m_noMoreLoadingNotified(false)
	{
	}

	void	AbstractResourceLoadingState::pushLoading(std::string packageFileName)
	{
		octo::ResourceManager&	resources = octo::Application::getResourceManager();

		m_loadings.push_back(resources.loadPackageAsync(packageFileName, this));
	}

	void	AbstractResourceLoadingState::start()
	{

	}

	void	AbstractResourceLoadingState::pause()
	{

	}

	void	AbstractResourceLoadingState::resume()
	{

	}

	void	AbstractResourceLoadingState::stop()
	{
		
	}

	void	AbstractResourceLoadingState::update(sf::Time)
	{
		if (m_error.empty() == false)
		{
			m_currentLoading = m_loadings.end();
			m_loadings.clear();
			m_error.clear();
		}
		if (m_currentLoading == m_loadings.end() && m_loadings.empty() == false)
			m_currentLoading = m_loadings.begin();
		if (m_currentLoading != m_loadings.end())
		{
			if (m_currentLoading->loadOne() == false)
			{
				m_loadings.clear();
				m_currentLoading = m_loadings.end();
			}
			else if (m_currentLoading->isFinished())
			{
				m_currentLoading = m_loadings.erase(m_currentLoading);
			}
		}
		if (m_currentLoading == m_loadings.end() && m_noMoreLoadingNotified == false)
		{
			onNoMoreLoading();
			m_noMoreLoadingNotified = true;
		}
	}

	void	AbstractResourceLoadingState::progress(std::string const& itemName,
					 PackageHeader::EntryType itemType,
					 std::uint64_t current,
					 std::uint64_t total)
	{
		m_currentKeyLoaded = itemName;
		m_currentStep = current;
		m_totalSteps = total;
		switch (itemType)
		{
			case PackageHeader::EntryType::Font:
				m_currentTypeLoaded = "Font";
				break;
			case PackageHeader::EntryType::Texture:
				m_currentTypeLoaded = "Texture";
				break;
			case PackageHeader::EntryType::Sound:
				m_currentTypeLoaded = "Sound";
				break;
			case PackageHeader::EntryType::Text:
				m_currentTypeLoaded = "Text";
				break;
			case PackageHeader::EntryType::Palette:
				m_currentTypeLoaded = "Text";
				break;
			case PackageHeader::EntryType::ColorWheel:
				m_currentTypeLoaded = "Color wheel";
				break;
			case PackageHeader::EntryType::SpriteSheet:
				m_currentTypeLoaded = "Sprite sheet";
				break;
			case PackageHeader::EntryType::SpriteAnimation:
				m_currentTypeLoaded = "Sprite animation";
				break;
			case PackageHeader::EntryType::LevelMap:
				m_currentTypeLoaded = "Level map";
				break;
			default:
				m_currentTypeLoaded.clear();
				break;
		}
	}

	void	AbstractResourceLoadingState::error(std::string const& message)
	{
		m_error = message;
	}

	void	AbstractResourceLoadingState::finished()
	{
	}

	std::string const	AbstractResourceLoadingState::getCurrentKeyLoaded()const
	{
		return (m_currentKeyLoaded);
	}

	std::string const	AbstractResourceLoadingState::getCurrentTypeLoaded()const
	{
		return (m_currentTypeLoaded);
	}
	std::uint64_t		AbstractResourceLoadingState::getCurrentStep()const
	{
		return (m_currentStep);
	}
	std::uint64_t		AbstractResourceLoadingState::getTotalSteps()const
	{
		return (m_totalSteps);
	}
}
