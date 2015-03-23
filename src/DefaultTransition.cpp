/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DefaultTransition.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 15:03:29 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/23 17:25:54 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DefaultTransition.hpp"
#include "Interpolations.hpp"

namespace octo
{
	// Black fade transition
	BlackFadeTransition::BlackFadeTransition(sf::View const& view, Action action) :
		AbstractTransition(view, action)
	{
		m_shape = sf::RectangleShape(view.getSize());
		m_shape.setPosition(view.getCenter() - view.getSize() / 2.f);
	}

	void	BlackFadeTransition::draw(sf::RenderTarget& render)const
	{
		render.draw(m_shape);	
	}
	
	void	BlackFadeTransition::updateTransition(float, float timePosition)
	{
		m_shape.setFillColor(cosinusInterpolation(sf::Color::Transparent,
												 sf::Color::Black,
												 timePosition));
	}

	// Black horizontal transition
	BlackHSlideTransition::BlackHSlideTransition(sf::View const& view, Action action) :
		AbstractTransition(view, action)
	{
		m_shape = sf::RectangleShape(sf::Vector2f(0.f, view.getSize().y));
		m_shape.setPosition(view.getCenter() - view.getSize() / 2.f);
		m_shape.setFillColor(sf::Color::Black);
	}

	void	BlackHSlideTransition::draw(sf::RenderTarget& render)const
	{
		render.draw(m_shape);
	}

	void	BlackHSlideTransition::updateTransition(float, float timePosition)
	{
		sf::Vector2f	viewSize = view().getSize();

		viewSize.x *= timePosition;
		m_shape.setSize(viewSize);
	}

	// Black vertical transition
	BlackVSlideTransition::BlackVSlideTransition(sf::View const& view, Action action) :
		AbstractTransition(view, action)
	{
		m_shape = sf::RectangleShape(sf::Vector2f(0.f, view.getSize().y));
		m_shape.setPosition(view.getCenter() - view.getSize() / 2.f);
		m_shape.setFillColor(sf::Color::Black);
	}

	void	BlackVSlideTransition::draw(sf::RenderTarget& render)const
	{
		render.draw(m_shape);
	}

	void	BlackVSlideTransition::updateTransition(float, float timePosition)
	{
		sf::Vector2f	viewSize = view().getSize();

		viewSize.y *= timePosition;
		m_shape.setSize(viewSize);
	}
}
