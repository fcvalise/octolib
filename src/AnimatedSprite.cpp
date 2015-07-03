/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AnimatedSprite.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/23 15:06:39 by irabeson          #+#    #+#             */
/*   Updated: 2015/07/03 18:17:55 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AnimatedSprite.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>	// TEST
namespace octo
{
	AnimatedSprite::AnimatedSprite() :
		m_animator(AnimableProperty<std::size_t>([this](std::size_t key)
				{
					sf::IntRect const&	rect = m_spriteSheet->getSubRect(key);

					m_sprite.setTextureRect(rect);
				}))
	{
	}

	void	AnimatedSprite::update(sf::Time frameTime)
	{
		m_animator.update(frameTime);
	}

	void 	AnimatedSprite::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		target.draw(m_sprite, states);
	}

	void	AnimatedSprite::setAnimation(SpriteAnimation const& animation)
	{
		m_animator.setAnimation(animation);
		m_animator.reset();
	}

	void	AnimatedSprite::setSpriteSheet(SpriteSheet const& spriteSheet)
	{
		m_spriteSheet = &spriteSheet;
		m_sprite.setTexture(spriteSheet.getTexture());
	}

	void	AnimatedSprite::restart()
	{
		m_animator.restart();
	}

	void	AnimatedSprite::play()
	{
		m_animator.play();
	}

	void	AnimatedSprite::stop()
	{
		m_animator.stop();
	}

	void	AnimatedSprite::pause()
	{
		m_animator.pause();
	}

	PlayStatus	AnimatedSprite::getStatus()const
	{
		return (m_animator.getStatus());
	}

	void	AnimatedSprite::setSpeedFactor(float factor)
	{
		m_animator.setSpeedFactor(factor);
	}

	void	AnimatedSprite::setColor(sf::Color const& color)
	{
		m_sprite.setColor(color);
	}

	sf::Color const&	AnimatedSprite::getColor()const
	{
		return (m_sprite.getColor());
	}

	sf::FloatRect	AnimatedSprite::getLocalBounds()const
	{
		return (m_sprite.getLocalBounds());
	}

	sf::FloatRect	AnimatedSprite::getGlobalBounds()const
	{
		return (m_sprite.getGlobalBounds());
	}

	sf::Vector2f	AnimatedSprite::getLocalSize()const
	{
		sf::FloatRect	rect = getLocalBounds();

		return (sf::Vector2f(rect.width, rect.height));
	}

	sf::Vector2f	AnimatedSprite::getGlobalSize()const
	{
		sf::FloatRect	rect = getGlobalBounds();

		return (sf::Vector2f(rect.width, rect.height));
	}

	void	AnimatedSprite::setPosition(float x, float y)
	{
		m_sprite.setPosition(x, y);
	}

	void	AnimatedSprite::setPosition(sf::Vector2f const& position)
	{
		m_sprite.setPosition(position);
	}

	void	AnimatedSprite::setRotation(float angle)
	{
		m_sprite.setRotation(angle);
	}

	void	AnimatedSprite::setScale(float factorX, float factorY)
	{
		m_sprite.setScale(factorX, factorY);
	}

	void	AnimatedSprite::setScale(sf::Vector2f const& factors)
	{
		m_sprite.setScale(factors);
	}

	void	AnimatedSprite::setOrigin(float x, float y)
	{
		m_sprite.setOrigin(x, y);
	}

	void	AnimatedSprite::setOrigin(sf::Vector2f const& origin)
	{
		m_sprite.setOrigin(origin);
	}

	sf::Vector2f const&	AnimatedSprite::getPosition()const
	{
		return (m_sprite.getPosition());
	}

	float	AnimatedSprite::getRotation()const
	{
		return (m_sprite.getRotation());
	}

	sf::Vector2f const&	AnimatedSprite::getScale()const
	{
		return (m_sprite.getScale());
	}

	sf::Vector2f const&	AnimatedSprite::getOrigin()const
	{
		return (m_sprite.getOrigin());
	}

	void	AnimatedSprite::move(float offsetX, float offsetY)
	{
		m_sprite.move(offsetX, offsetY);
	}

	void	AnimatedSprite::move(sf::Vector2f const& offset)
	{
		m_sprite.move(offset);
	}

	void	AnimatedSprite::rotate(float angle)
	{
		m_sprite.rotate(angle);
	}

	void	AnimatedSprite::scale(float factorX, float factorY)
	{
		m_sprite.scale(factorX, factorY);
	}

	void	AnimatedSprite::scale(sf::Vector2f const& factor)
	{
		m_sprite.scale(factor);
	}

	sf::Transform const&	AnimatedSprite::getTransform()const
	{
		return (m_sprite.getTransform());
	}

	sf::Transform const&	AnimatedSprite::getInverseTransform()const
	{
		return (m_sprite.getInverseTransform());
	}
}
