/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PostEffectManager.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/10 14:45:01 by irabeson          #+#    #+#             */
/*   Updated: 2015/08/11 00:07:50 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PostEffectManager.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace octo
{
	PostEffectManager::Shader::Shader() :
		shader(nullptr),
		enabled(false)
	{
	}

	PostEffectManager::Shader::Shader(sf::Shader& shader, bool enabled) :
		shader(&shader),
		enabled(enabled)
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
		if (m_shaders.empty())
		{
			sprite.setTexture(m_firstRender.getTexture());
		}
		else
		{
			applyShaders(sprite);
		}
		render.draw(sprite);
	}
	
	void	PostEffectManager::applyShaders(sf::Sprite& sprite)
	{
		sf::RenderTexture*	source = &m_firstRender;
		sf::RenderTexture*	target = &m_secondRender;

		m_firstRender.setView(m_firstRender.getDefaultView());
		for (auto const& shader : m_shaders)
		{
			if (shader.enabled)
			{
				sprite.setTexture(source->getTexture());
				target->draw(sprite, shader.shader);
				target->display();
				std::swap(source, target);
			}
		}
		sprite.setTexture(source->getTexture());
	}

	std::size_t	PostEffectManager::addShader(sf::Shader& shader, bool enable)
	{
		std::size_t	newIndex = m_shaders.size();

		m_shaders.emplace_back(shader, enable);
		return (newIndex);
	}

	void	PostEffectManager::removeShader(std::size_t index)
	{
		if (index < m_shaders.size())
		{
			m_shaders.erase(m_shaders.begin() + index);
		}
	}

	void	PostEffectManager::removeShaders()
	{
		m_shaders.clear();
	}

	void	PostEffectManager::enableShader(std::size_t index, bool enable)
	{
		m_shaders.at(index).enabled = enable;
	}

	bool	PostEffectManager::isShaderEnabled(std::size_t index)const
	{
		return (m_shaders.at(index).enabled);
	}

	sf::Shader&	PostEffectManager::getShader(std::size_t index)
	{
		return (*m_shaders.at(index).shader);
	}

	std::size_t	PostEffectManager::getShaderCount()const
	{
		return (m_shaders.size());
	}
}
