/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PostEffectManager.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/10 14:45:01 by irabeson          #+#    #+#             */
/*   Updated: 2015/08/16 16:00:39 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PostEffectManager.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace octo
{
	//
	// class PostEffectManager
	//
	PostEffectManager::PostEffectManager() :
		m_enabledCount(0u),
		m_allShaderEnabled(true)
	{
	}

	void	PostEffectManager::createRender(sf::VideoMode const& videoMode)
	{
		m_firstRender.create(videoMode.width, videoMode.height);
		m_secondRender.create(videoMode.width, videoMode.height);
	}

	void	PostEffectManager::draw(sf::Drawable const& drawable, sf::RenderStates const& states)
	{
		m_firstRender.draw(drawable, states);
	}

	void	PostEffectManager::draw(sf::Vertex const* vertices,
									unsigned int count, sf::PrimitiveType type,
									sf::RenderStates const& states)
	{
		m_firstRender.draw(vertices, count, type, states);
	}

	sf::RenderTarget&	PostEffectManager::getRender()
	{
		return (m_firstRender);
	}

	void	PostEffectManager::setView(sf::View const& view)
	{
		m_firstRender.setView(view);
	}

	void	PostEffectManager::display(sf::RenderTarget& render)
	{
		sf::Sprite	sprite;

		m_firstRender.display();
		if (m_effects.empty())
		{
			sprite.setTexture(m_firstRender.getTexture());
		}
		else
		{
			applyEffects(sprite);
		}
		render.draw(sprite);
	}
	
	void	PostEffectManager::applyEffects(sf::Sprite& sprite)
	{
		sf::RenderTexture*	source = &m_firstRender;
		sf::RenderTexture*	target = &m_secondRender;

		if (m_allShaderEnabled)
		{
			m_firstRender.setView(m_firstRender.getDefaultView());
			for (auto const& pair : m_effects)
			{
				if (pair.second->isEnabled())
				{
					pair.second->applyEffect(sprite, source->getTexture(), *target);
					target->display();
					std::swap(source, target);
				}
			}
		}
		sprite.setTexture(source->getTexture());
	}

	std::size_t	PostEffectManager::addEffect(PostEffect&& effect)
	{
		static std::size_t	newIndex = 0;

		m_effects[newIndex].reset(new PostEffect(std::move(effect)));
		if (m_effects[newIndex]->isEnabled())
		{
			++m_enabledCount;
		}
		return (newIndex++);
	}

	void	PostEffectManager::removeEffect(std::size_t index)
	{
		auto	it = m_effects.find(index);

		if (it != m_effects.end())
		{
			if (it->second->isEnabled())
			{
				--m_enabledCount;
			}
			m_effects.erase(it);
		}
	}

	void	PostEffectManager::removeEffects()
	{
		m_effects.clear();
		m_enabledCount = 0u;
	}

	void	PostEffectManager::enableEffect(std::size_t index, bool enable)
	{
		auto	it = m_effects.find(index);
		bool	enabled = it->second->isEnabled();

		if (enabled && enable == false)
		{
			--m_enabledCount;
		}
		else if (enabled == false && enable)
		{
			++m_enabledCount;
		}
		it->second->setEnabled(enable);
	}

	PostEffect const&	PostEffectManager::getEffect(std::size_t index)const
	{
		return (*m_effects.at(index));
	}

	PostEffect&	PostEffectManager::getEffect(std::size_t index)
	{
		return (*m_effects.at(index));
	}

	std::size_t	PostEffectManager::getEffectCount()const
	{
		return (m_effects.size());
	}

	bool	PostEffectManager::hasEnabledEffects()const
	{
		return (m_enabledCount > 0u);
	}

	void	PostEffectManager::setAllShaderEnabled(bool isAllShaderEnable)
	{
		m_allShaderEnabled = isAllShaderEnable;
	}
}
