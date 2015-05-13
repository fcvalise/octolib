/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 20:30:10 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/08 18:31:17 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Camera.hpp"
#include "GraphicsManager.hpp"

#include <cassert>

namespace octo
{
	Camera::Camera() :
		m_graphicsManager(nullptr),
		m_zoomFactor(1.f)
	{
	}

	void Camera::setup(GraphicsManager& graphicsManager)
	{
		graphicsManager.addWindowListener(this);
		m_view = graphicsManager.getDefaultView();
		m_guiView = graphicsManager.getDefaultView();
		m_graphicsManager = &graphicsManager;
		m_zoomFactor = 1.f;
	}

	void	Camera::setCenter(sf::Vector2f const& center)
	{
		m_view.setCenter(center);
	}

	void	Camera::setCenter(float x, float y)
	{
		m_view.setCenter(x, y);
	}

	void	Camera::move(sf::Vector2f const& offset)
	{
		m_view.move(offset);
	}

	void	Camera::move(float offsetX, float offsetY)
	{
		m_view.move(offsetX, offsetY);
	}

	void	Camera::setRotation(float angle)
	{
		m_view.setRotation(angle);
	}

	void	Camera::rotate(float angle)
	{
		m_view.rotate(angle);
	}

	void	Camera::setZoom(float factor)
	{
		m_zoomFactor = factor;
		m_view.zoom(m_zoomFactor);
	}

	sf::Vector2f const&	Camera::getCenter()const
	{
		return (m_view.getCenter());
	}

	sf::Vector2f const&	Camera::getSize()const
	{
		return (m_view.getSize());
	}

	float	Camera::getRotation()const
	{
		return (m_view.getRotation());
	}

	float	Camera::getZoom()const
	{
		return (m_zoomFactor);
	}

	void	Camera::update(sf::Time)
	{
	}

	sf::View const&	Camera::getView()const
	{
		return (m_view);
	}

	sf::View const&	Camera::getGuiView()const
	{
		return (m_guiView);
	}

	sf::Vector2f	Camera::mapPixelToCoords(sf::Vector2i const& position)const
	{
		assert (m_graphicsManager != nullptr);

		return (m_graphicsManager->mapPixelToCoords(position, m_view));
	}

	sf::Vector2f	Camera::mapGuiPixelToCoords(sf::Vector2i const& position)const
	{
		assert (m_graphicsManager != nullptr);

		return (m_graphicsManager->mapPixelToCoords(position, m_guiView));
	}

	sf::Vector2i	Camera::mapCoordsToPixel(sf::Vector2f const& position)const
	{
		assert (m_graphicsManager != nullptr);

		return (m_graphicsManager->mapCoordsToPixel(position, m_view));
	}

	sf::Vector2i	Camera::mapGuiCoordsToPixel(sf::Vector2f const& position)const
	{
		assert (m_graphicsManager != nullptr);

		return (m_graphicsManager->mapCoordsToPixel(position, m_guiView));
	}

	void	Camera::onResized(sf::Event::SizeEvent const& event)
	{
		sf::Vector2f	newSize	(event.width, event.height);

		m_view.setSize(newSize);
		m_guiView.setSize(newSize);
	}
}