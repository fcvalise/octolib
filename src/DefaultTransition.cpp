/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DefaultTransition.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 15:03:29 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/10 19:56:12 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DefaultTransition.hpp"
#include "Interpolations.hpp"

namespace octo
{
	// Black fade transition
	BlackFadeTransition::BlackFadeTransition(Action action) :
		AbstractTransition(action)
	{
		m_shape.setFillColor(sf::Color::Black);
	}

	void	BlackFadeTransition::draw(sf::RenderTarget& render)const
	{
		render.draw(m_shape);	
	}
	
	void	BlackFadeTransition::updateTransition(sf::Time, float timePosition, sf::View const& view)
	{
		m_shape.setSize(view.getSize());
		m_shape.setPosition(view.getCenter() - view.getSize() / 2.f);
		m_shape.setFillColor(cosinusInterpolation(sf::Color::Transparent,
												 sf::Color::Black,
												 timePosition));
	}

	// Red fade transition
	RedFadeTransition::RedFadeTransition(Action action) :
		AbstractTransition(action)
	{
		m_shape.setFillColor(sf::Color::Red);
	}

	void	RedFadeTransition::draw(sf::RenderTarget& render)const
	{
		render.draw(m_shape);	
	}
	
	void	RedFadeTransition::updateTransition(sf::Time, float timePosition, sf::View const& view)
	{
		m_shape.setSize(view.getSize());
		m_shape.setPosition(view.getCenter() - view.getSize() / 2.f);
		m_shape.setFillColor(cosinusInterpolation(sf::Color::Transparent,
												 sf::Color(155, 0, 0),
												 timePosition));
	}

	// Blue fade transition
	BlueFadeTransition::BlueFadeTransition(Action action) :
		AbstractTransition(action)
	{
		m_shape.setFillColor(sf::Color::Blue);
	}

	void	BlueFadeTransition::draw(sf::RenderTarget& render)const
	{
		render.draw(m_shape);	
	}
	
	void	BlueFadeTransition::updateTransition(sf::Time, float timePosition, sf::View const& view)
	{
		m_shape.setSize(view.getSize());
		m_shape.setPosition(view.getCenter() - view.getSize() / 2.f);
		m_shape.setFillColor(cosinusInterpolation(sf::Color::Transparent,
												 sf::Color(0, 0, 155),
												 timePosition));
	}

	// Black horizontal transition
	BlackHSlideTransition::BlackHSlideTransition(Action action) :
		AbstractTransition(action)
	{
		m_shape.setFillColor(sf::Color::Black);
	}

	void	BlackHSlideTransition::draw(sf::RenderTarget& render)const
	{
		render.draw(m_shape);
	}

	void	BlackHSlideTransition::updateTransition(sf::Time, float timePosition, sf::View const& view)
	{
		sf::Vector2f	viewSize = view.getSize();

		viewSize.x *= timePosition;
		m_shape.setSize(viewSize);
		m_shape.setPosition(view.getCenter() - view.getSize() / 2.f);
	}

	// Black vertical transition
	BlackVSlideTransition::BlackVSlideTransition(Action action) :
		AbstractTransition(action)
	{
		m_shape.setFillColor(sf::Color::Black);
	}

	void	BlackVSlideTransition::draw(sf::RenderTarget& render)const
	{
		render.draw(m_shape);
	}

	void	BlackVSlideTransition::updateTransition(sf::Time, float timePosition, sf::View const& view)
	{
		sf::Vector2f	viewSize = view.getSize();

		viewSize.y *= timePosition;
		m_shape.setSize(viewSize);
		m_shape.setPosition(view.getCenter() - view.getSize() / 2.f);
	}
}
