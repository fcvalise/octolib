/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PostEffect.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/16 15:41:38 by irabeson          #+#    #+#             */
/*   Updated: 2015/08/16 16:07:00 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PostEffect.hpp"

namespace octo
{
	//
	// class PostEffect
	//
	PostEffect::PostEffect() :
		m_shader(nullptr),
		m_enabled(false)
	{
	}

	PostEffect::PostEffect(sf::Shader& shader, bool	enabled) :
		m_shader(&shader),
		m_enabled(enabled)
	{
	}

	PostEffect::PostEffect(sf::Shader& shader,
		   sf::BlendMode const& blendMode,
		   bool	enabled) :
		m_shader(&shader),
		m_blendMode(blendMode),
		m_enabled(enabled)
	{
	}

	PostEffect::~PostEffect()
	{
	}

	void	PostEffect::applyEffect(sf::Sprite& sprite,
									sf::Texture const& texture,
									sf::RenderTarget& render)const
	{
		sprite.setTexture(texture);
		render.draw(sprite, sf::RenderStates(m_blendMode,
											 sf::Transform::Identity,
											 &texture,
											 m_shader));
	}

	void	PostEffect::resetShader(sf::Shader* shader)
	{
		m_shader = shader;
	}

	sf::Shader&	PostEffect::getShader()
	{
		return (*m_shader);
	}

	sf::Shader const&	PostEffect::getShader()const
	{
		return (*m_shader);
	}

	void	PostEffect::setBlendMode(sf::BlendMode const& mode)
	{
		m_blendMode = mode;
	}

	sf::BlendMode const&	PostEffect::getBlendMode()const
	{
		return (m_blendMode);
	}

	void	PostEffect::setEnabled(bool enabled)
	{
		m_enabled = enabled;
	}

	bool	PostEffect::isEnabled()const
	{
		return (m_enabled);
	}
}
