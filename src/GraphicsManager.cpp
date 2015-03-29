/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicsManager.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 21:39:51 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/29 11:11:34 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GraphicsManager.hpp"

namespace octo
{
	GraphicsManager::GraphicsManager() :
		m_fullscreen(false),
		m_verticalSync(false)
	{
	}

	void	GraphicsManager::createRender(sf::VideoMode const& mode,
										 sf::String const& title,
										 bool fullscreen)
	{
		m_window.create(mode, title, (fullscreen) ? sf::Style::Fullscreen : sf::Style::Default);
		m_videoMode = mode;
		m_title = title;
		m_fullscreen = fullscreen;
	}

	void	GraphicsManager::draw(sf::Drawable const& drawable, sf::RenderStates const& states)
	{
		m_window.draw(drawable, states);
	}

	void	GraphicsManager::draw(sf::Vertex const* vertices, unsigned int count, sf::PrimitiveType type,
								  sf::RenderStates const& states)
	{
		m_window.draw(vertices, count, type, states);
	}

	sf::RenderTarget&	GraphicsManager::getRender()
	{
		return (m_window);
	}

	void	GraphicsManager::processEvents()
	{
		while (m_window.pollEvent(m_event))
		{
			switch (m_event.type)
			{
				// Window events
				case sf::Event::Closed:
					for (IWindowListener* listener : m_windowListeners)
						listener->onClosed();
					break;
				case sf::Event::Resized:
					for (IWindowListener* listener : m_windowListeners)
						listener->onResized(m_event.size);
					break;
				case sf::Event::GainedFocus:
					for (IWindowListener* listener : m_windowListeners)
						listener->onFocusGained();
					break;
				case sf::Event::LostFocus:
					for (IWindowListener* listener : m_windowListeners)
						listener->onFocusLost();
					break;
				// Keyboard events
				case sf::Event::KeyPressed:
					for (IKeyboardListener* listener : m_keyboardListeners)
						listener->onPressed(m_event.key);
					break;
				case sf::Event::KeyReleased:
					for (IKeyboardListener* listener : m_keyboardListeners)
						listener->onReleased(m_event.key);
					break;
				// Mouse events
				case sf::Event::MouseButtonPressed:
					for (IMouseListener* listener : m_mouseListeners)
						listener->onPressed(m_event.mouseButton);
					break;
				case sf::Event::MouseButtonReleased:
					for (IMouseListener* listener : m_mouseListeners)
						listener->onReleased(m_event.mouseButton);
					break;
				case sf::Event::MouseMoved:
					for (IMouseListener* listener : m_mouseListeners)
						listener->onMoved(m_event.mouseMove);
					break;
				case sf::Event::MouseWheelMoved:
					for (IMouseListener* listener : m_mouseListeners)
						listener->onWheel(m_event.mouseWheel);
					break;
				// Joystick events
				case sf::Event::JoystickConnected:
					for (IJoystickListener* listener : m_joystickListeners)
						listener->onConnected(m_event.joystickConnect);
					break;
				case sf::Event::JoystickDisconnected:
					for (IJoystickListener* listener : m_joystickListeners)
						listener->onDisconnected(m_event.joystickConnect);
					break;
				case sf::Event::JoystickMoved:
					for (IJoystickListener* listener : m_joystickListeners)
						listener->onMoved(m_event.joystickMove);
					break;
				case sf::Event::JoystickButtonPressed:
					for (IJoystickListener* listener : m_joystickListeners)
						listener->onPressed(m_event.joystickButton);
					break;
				case sf::Event::JoystickButtonReleased:
					for (IJoystickListener* listener : m_joystickListeners)
						listener->onReleased(m_event.joystickButton);
					break;
				default:
					break;
			}
		}
	}

	void	GraphicsManager::display()
	{
		m_window.display();
	}

	void	GraphicsManager::setVideoMode(sf::VideoMode const& mode)
	{
		if (m_videoMode != mode)
		{
			createRender(mode, m_title, m_fullscreen);
		}
	}

	sf::VideoMode const&	GraphicsManager::getVideoMode()const
	{
		return (m_videoMode);
	}

	void	GraphicsManager::setFullscreen(bool fullscreen)
	{
		if (m_fullscreen != fullscreen)
		{
			createRender(m_videoMode, m_title, fullscreen);
		}
	}

	bool	GraphicsManager::isFullscreen()const
	{
		return (m_fullscreen);
	}

	void	GraphicsManager::setVerticalSyncEnabled(bool enable)
	{
		if (m_verticalSync != enable)
		{
			m_window.setVerticalSyncEnabled(enable);
			m_verticalSync = enable;
		}
	}

	bool	GraphicsManager::isVerticalSyncEnabled()const
	{
		return (m_verticalSync);
	}

	void	GraphicsManager::setView(sf::View const& view)
	{
		m_window.setView(view);
	}

	sf::View const&	GraphicsManager::getView()const
	{
		return (m_window.getView());
	}

	sf::View const&	GraphicsManager::getDefaultView()const
	{
		return (m_window.getDefaultView());
	}

	sf::Vector2f	GraphicsManager::mapPixelToCoords(sf::Vector2i const& position)const
	{
		return (m_window.mapPixelToCoords(position));
	}

	sf::Vector2f	GraphicsManager::mapPixelToCoords(sf::Vector2i const& position, sf::View const& view)const
	{
		return (m_window.mapPixelToCoords(position, view));
	}

	sf::Vector2i	GraphicsManager::mapCoordsToPixel(sf::Vector2f const& position)const
	{
		return (m_window.mapCoordsToPixel(position));
	}

	sf::Vector2i	GraphicsManager::mapCoordsToPixel(sf::Vector2f const& position, sf::View const& view)const
	{
		return (m_window.mapCoordsToPixel(position, view));
	}

	void	GraphicsManager::addWindowListener(IWindowListener* listener)
	{
		appendListener(listener, m_windowListeners);
	}

	void	GraphicsManager::addKeyboardListener(IKeyboardListener* listener)
	{
		appendListener(listener, m_keyboardListeners);
	}

	void	GraphicsManager::addMouseListener(IMouseListener* listener)
	{
		appendListener(listener, m_mouseListeners);
	}

	void	GraphicsManager::addJoystickListener(IJoystickListener* listener)
	{
		appendListener(listener, m_joystickListeners);
	}

	void	GraphicsManager::removeWindowListener(IWindowListener* listener)
	{
		removeListener(listener, m_windowListeners);
	}

	void	GraphicsManager::removeKeyboardListener(IKeyboardListener* listener)
	{
		removeListener(listener, m_keyboardListeners);
	}

	void	GraphicsManager::removeMouseListener(IMouseListener* listener)
	{
		removeListener(listener, m_mouseListeners);
	}

	void	GraphicsManager::removeJoystickListener(IJoystickListener* listener)
	{
		removeListener(listener, m_joystickListeners);
	}
}
