/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CharacterSprite.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 17:05:26 by irabeson          #+#    #+#             */
/*   Updated: 2015/07/23 02:35:48 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CharacterSprite.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace octo
{
	//
	// class ACharacterState
	//

	CharacterSprite::ACharacterState::ACharacterState(std::string const& name, CharacterAnimation const& animation, CharacterSprite& character) :
		AState(name),
		m_animation(animation),
		m_animator(character.m_animator)
	{
	}

	//
	//	class CharacterSprite
	//
	CharacterSprite::CharacterSprite() :
		m_animator(AnimableProperty<CharacterFrame>([this](CharacterFrame const& frame)
				{
					sf::IntRect const&	rect = m_spriteSheet->getSubRect(frame.getTextureRectangleId());

					m_boundingBox = frame.getBox();
					m_hotPoint = frame.getHotPoint();
					m_sprite.setTextureRect(rect);
				}))
	{
		m_currentEvent = FiniteStateMachine::NullEvent;
	}

	void	CharacterSprite::update(sf::Time frameTime)
	{
		auto					state = m_machine.getCurrentState();

		if (m_machine.update(frameTime))
		{
			m_possibleEvents.clear();
			for (auto transition : *state)
			{
				m_possibleEvents.push_back(transition.second.getTriggerEvent());
			}
		}
		m_animator.update(frameTime);
	}

	void 	CharacterSprite::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		target.draw(m_sprite, states);
	}

	void	CharacterSprite::setAnimation(CharacterAnimation const& animation)
	{
		m_animator.setAnimation(animation);
		m_animator.reset();
	}

	void	CharacterSprite::setMachine(FiniteStateMachine const& machine)
	{
		m_machine = machine;
	}

	void	CharacterSprite::setSpriteSheet(SpriteSheet const& spriteSheet)
	{
		m_spriteSheet = &spriteSheet;
		m_sprite.setTexture(spriteSheet.getTexture());
	}

	void	CharacterSprite::setNextEvent(EventId eventId)
	{
		m_currentEvent = eventId;
		m_machine.setNextEvent(eventId);
	}

	CharacterSprite::EventId	CharacterSprite::getCurrentEvent()
	{
		return m_currentEvent;
	}

	void	CharacterSprite::restart()
	{
		m_machine.start();
		m_animator.restart();
	}

	void	CharacterSprite::play()
	{
		m_animator.play();
	}

	void	CharacterSprite::stop()
	{
		m_animator.stop();
	}

	void	CharacterSprite::pause()
	{
		m_animator.pause();
	}

	PlayStatus	CharacterSprite::getStatus()const
	{
		return (m_animator.getStatus());
	}

	void	CharacterSprite::setSpeedFactor(float factor)
	{
		m_animator.setSpeedFactor(factor);
	}

	void	CharacterSprite::setColor(sf::Color const& color)
	{
		m_sprite.setColor(color);
	}

	sf::Color const&	CharacterSprite::getColor()const
	{
		return (m_sprite.getColor());
	}

	sf::FloatRect	CharacterSprite::getLocalBounds()const
	{
		return (m_sprite.getLocalBounds());
	}

	sf::FloatRect	CharacterSprite::getGlobalBounds()const
	{
		return (m_sprite.getGlobalBounds());
	}

	sf::Vector2f	CharacterSprite::getLocalSize()const
	{
		sf::FloatRect	rect = getLocalBounds();

		return (sf::Vector2f(rect.width, rect.height));
	}

	sf::Vector2f	CharacterSprite::getGlobalSize()const
	{
		sf::FloatRect	rect = getGlobalBounds();

		return (sf::Vector2f(rect.width, rect.height));
	}

	void	CharacterSprite::setPosition(float x, float y)
	{
		m_sprite.setPosition(x, y);
	}

	void	CharacterSprite::setPosition(sf::Vector2f const& position)
	{
		m_sprite.setPosition(position);
	}

	void	CharacterSprite::setRotation(float angle)
	{
		m_sprite.setRotation(angle);
	}

	void	CharacterSprite::setScale(float factorX, float factorY)
	{
		m_sprite.setScale(factorX, factorY);
	}

	void	CharacterSprite::setScale(sf::Vector2f const& factors)
	{
		m_sprite.setScale(factors);
	}

	void	CharacterSprite::setOrigin(float x, float y)
	{
		m_sprite.setOrigin(x, y);
	}

	void	CharacterSprite::setOrigin(sf::Vector2f const& origin)
	{
		m_sprite.setOrigin(origin);
	}

	sf::Vector2f const&	CharacterSprite::getPosition()const
	{
		return (m_sprite.getPosition());
	}

	float	CharacterSprite::getRotation()const
	{
		return (m_sprite.getRotation());
	}

	sf::Vector2f const&	CharacterSprite::getScale()const
	{
		return (m_sprite.getScale());
	}

	sf::Vector2f const&	CharacterSprite::getOrigin()const
	{
		return (m_sprite.getOrigin());
	}

	void	CharacterSprite::move(float offsetX, float offsetY)
	{
		m_sprite.move(offsetX, offsetY);
	}

	void	CharacterSprite::move(sf::Vector2f const& offset)
	{
		m_sprite.move(offset);
	}

	void	CharacterSprite::rotate(float angle)
	{
		m_sprite.rotate(angle);
	}

	void	CharacterSprite::scale(float factorX, float factorY)
	{
		m_sprite.scale(factorX, factorY);
	}

	void	CharacterSprite::scale(sf::Vector2f const& factor)
	{
		m_sprite.scale(factor);
	}

	sf::Transform const&	CharacterSprite::getTransform()const
	{
		return (m_sprite.getTransform());
	}

	sf::Transform const&	CharacterSprite::getInverseTransform()const
	{
		return (m_sprite.getInverseTransform());
	}
	
	sf::FloatRect const&	CharacterSprite::getBoundingBox()const
	{
		return (m_boundingBox);
	}

	sf::Vector2f const&		CharacterSprite::getHotPoint()const
	{
		return (m_hotPoint);
	}
	
	std::vector<CharacterSprite::EventId> const&	CharacterSprite::getPossibleEvents()const
	{
		return (m_possibleEvents);
	}

	bool		CharacterSprite::canGetEvent(EventId eventId) const
	{
		for (auto it : m_possibleEvents){
			if (it == eventId)
				return true;
		}
		return false;
	}
}
