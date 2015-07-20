/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CharacterSprite.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 17:04:23 by irabeson          #+#    #+#             */
/*   Updated: 2015/07/20 17:19:11 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTERSPRITE_HPP
# define CHARACTERSPRITE_HPP
# include "SingleAnimator.hpp"
# include "CharacterAnimation.hpp"
# include "SpriteSheet.hpp"

# include <SFML/Graphics/Drawable.hpp>
# include <SFML/Graphics/Sprite.hpp>

namespace octo
{
	/*!
	 *	\ingroup Graphics
	 *	\class CharacterSprite
	 *	\brief Frame by frame animated sprite
	 *
	 *	This class is very similar to sf::Sprite but it uses
	 *	a sprite sheet and an animation to be animated frame by frame.
	 */
	class CharacterSprite : public sf::Drawable
	{
	public:
		CharacterSprite();

		void					update(sf::Time frameTime);
		void 					draw(sf::RenderTarget &target, sf::RenderStates states) const;

		void					setAnimation(CharacterAnimation const& animation);
		void					setSpriteSheet(SpriteSheet const& spriteSheet);

		void					restart();
		void					play();
		void					stop();
		void					pause();
		PlayStatus				getStatus()const;
		void					setSpeedFactor(float factor);

		void					setColor(sf::Color const& color);
		sf::Color const&		getColor()const;
		sf::FloatRect			getLocalBounds()const;
		sf::FloatRect			getGlobalBounds()const;
		sf::Vector2f			getLocalSize()const;
		sf::Vector2f			getGlobalSize()const;
		void					setPosition(float x, float y);
		void					setPosition(sf::Vector2f const& position);
		void					setRotation(float angle);
		void					setScale(float factorX, float factorY);
		void					setScale(sf::Vector2f const& factors);
		void					setOrigin(float x, float y);
		void					setOrigin(sf::Vector2f const& origin);
		sf::Vector2f const&		getPosition()const;
		float					getRotation()const;
		sf::Vector2f const&		getScale()const;
		sf::Vector2f const&		getOrigin()const;
		void					move(float offsetX, float offsetY);
		void					move(sf::Vector2f const& offfset);
		void					rotate(float angle);
		void					scale(float factorX, float factorY);
		void					scale(sf::Vector2f const& factor);
		sf::Transform const&	getTransform()const;
		sf::Transform const&	getInverseTransform()const;
		sf::FloatRect const&	getBoundingBox()const;
		sf::Vector2f const&		getHotPoint()const;
	private:
		sf::Sprite						m_sprite;
		SingleAnimator<CharacterFrame>	m_animator;
		SpriteSheet const*				m_spriteSheet;
		sf::FloatRect					m_boundingBox;
		sf::Vector2f					m_hotPoint;
	};
}

#endif
