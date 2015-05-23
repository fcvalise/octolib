/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AnimatedSprite.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 18:30:04 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/23 17:14:00 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATEDSPRITE_HPP
# define ANIMATEDSPRITE_HPP
# include "SingleAnimator.hpp"
# include "SpriteAnimation.hpp"
# include "SpriteSheet.hpp"

# include <SFML/Graphics/Drawable.hpp>
# include <SFML/Graphics/Sprite.hpp>

namespace octo
{
	/*!
	 *	\ingroup Graphics
	 *	\class AnimatedSprite
	 *	\brief Frame by frame animated sprite
	 *
	 *	This class is very similar to sf::Sprite but it uses
	 *	a sprite sheet and an animation to be animated frame by frame.
	 */
	class AnimatedSprite : public sf::Drawable
	{
	public:
		AnimatedSprite();

		void					update(sf::Time frameTime);
		void 					draw(sf::RenderTarget &target, sf::RenderStates states) const;

		void					setAnimation(SpriteAnimation const& animation);
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
	private:
		sf::Sprite						m_sprite;
		SingleAnimator<std::size_t>		m_animator;
		SpriteSheet const*				m_spriteSheet;
	};
}

#endif
