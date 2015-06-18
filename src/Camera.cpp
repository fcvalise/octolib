/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 20:30:10 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/18 20:44:25 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Camera.hpp"
#include "GraphicsManager.hpp"

#include <cassert>

namespace octo
{
	/*!
	 *	\ingroup Graphics
	 *	\class Camera
	 *	\brief Camera
	 *
	 *	Camera provides unified view controls.
	 *	\see Application
	 */

	/*!	Create a null camera */
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

	/*!	Defines the center of the camera */
	void	Camera::setCenter(sf::Vector2f const& center)
	{
		m_view.setCenter(center);
	}

	/*!	Defines the center of the camera */
	void	Camera::setCenter(float x, float y)
	{
		m_view.setCenter(x, y);
	}

	/*!	Moves the center of the camera */
	void	Camera::move(sf::Vector2f const& offset)
	{
		m_view.move(offset);
	}

	/*!	Moves the center of the camera */
	void	Camera::move(float offsetX, float offsetY)
	{
		m_view.move(offsetX, offsetY);
	}

	/*!	Defines the camera rotation in degrees
	 *	\param angle Angle in degrees
	 */
	void	Camera::setRotation(float angle)
	{
		m_view.setRotation(angle);
	}

	/*!	Rotate the camera
	 *	\param angle Angle in degrees
	 */
	void	Camera::rotate(float angle)
	{
		m_view.rotate(angle);
	}

	/*!	Define the zoom factor */
	void	Camera::setZoom(float factor)
	{
		m_zoomFactor = factor;
		m_view.zoom(m_zoomFactor);
	}

	/*!	Get the position of the center of the camera */
	sf::Vector2f const&	Camera::getCenter()const
	{
		return (m_view.getCenter());
	}

	/*!	Get the size of the camera */
	sf::Vector2f const&	Camera::getSize()const
	{
		return (m_view.getSize());
	}

	/*!	Get the camera rotation */
	float	Camera::getRotation()const
	{
		return (m_view.getRotation());
	}

	/*!	Get the zoom factor */
	float	Camera::getZoom()const
	{
		return (m_zoomFactor);
	}

	/*! Update the camera */
	void	Camera::update(sf::Time)
	{
	}

	/*!	Get the SFML view handled by the camera */
	sf::View const&	Camera::getView()const
	{
		return (m_view);
	}

	/*!	Get the SFML view dedicated to the gui handled by the camera */
	sf::View const&	Camera::getGuiView()const
	{
		return (m_guiView);
	}

	/*!	Get the camera rectangle */
	sf::FloatRect	Camera::getRectangle()const
	{
		sf::Vector2f	size = m_view.getSize();

		return (sf::FloatRect(m_view.getCenter() - size / 2.f, size));
	}

	/*!	Convert a pixel position on the screen to a position in world coordinate using the game view */
	sf::Vector2f	Camera::mapPixelToCoords(sf::Vector2i const& position)const
	{
		assert (m_graphicsManager != nullptr);

		return (m_graphicsManager->mapPixelToCoords(position, m_view));
	}

	/*!	Convert a pixel position on the screen to a position in world coordinate using the GUI view */
	sf::Vector2f	Camera::mapGuiPixelToCoords(sf::Vector2i const& position)const
	{
		assert (m_graphicsManager != nullptr);

		return (m_graphicsManager->mapPixelToCoords(position, m_guiView));
	}

	/*!	Convert a position in world coordinate to a pixel position on the screen using the game view */
	sf::Vector2i	Camera::mapCoordsToPixel(sf::Vector2f const& position)const
	{
		assert (m_graphicsManager != nullptr);

		return (m_graphicsManager->mapCoordsToPixel(position, m_view));
	}

	/*!	Convert a position in world coordinate to a pixel position on the screen using the GUI view */
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
