/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicsManager.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 21:39:51 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/08 15:07:57 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GraphicsManager.hpp"
#include "GraphicsListeners.hpp"

namespace octo
{
	GraphicsManager::GraphicsManager() :
		m_fullscreen(false),
		m_verticalSync(false),
		m_keyboardListenersEnabled(true),
		m_mouseListenersEnabled(true),
		m_joystickListenersEnabled(true)
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

	void	GraphicsManager::closeRender()
	{
		m_window.close();
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
		while (m_window.isOpen() && m_window.pollEvent(m_event))
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
					if (m_keyboardListenersEnabled)
					{
						for (IKeyboardListener* listener : m_keyboardListeners)
						{
							if (listener->onPressed(m_event.key) == false)
								break;
						}
					}
					break;
				case sf::Event::KeyReleased:
					if (m_keyboardListenersEnabled)
					{
						for (IKeyboardListener* listener : m_keyboardListeners)
						{
							if (listener->onReleased(m_event.key) == false)
								break;
						}
					}
					break;
				// Mouse events
				case sf::Event::MouseButtonPressed:
					if (m_mouseListenersEnabled)
					{
						for (IMouseListener* listener : m_mouseListeners)
							listener->onPressed(m_event.mouseButton);
					}
					break;
				case sf::Event::MouseButtonReleased:
					if (m_mouseListenersEnabled)
					{
						for (IMouseListener* listener : m_mouseListeners)
							listener->onReleased(m_event.mouseButton);
					}
					break;
				case sf::Event::MouseMoved:
					if (m_mouseListenersEnabled)
					{
						for (IMouseListener* listener : m_mouseListeners)
							listener->onMoved(m_event.mouseMove);
					}
					break;
				case sf::Event::MouseWheelMoved:
					if (m_mouseListenersEnabled)
					{
						for (IMouseListener* listener : m_mouseListeners)
							listener->onWheel(m_event.mouseWheel);
					}
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
					if (m_joystickListenersEnabled)
					{
						for (IJoystickListener* listener : m_joystickListeners)
							listener->onMoved(m_event.joystickMove);
					}
					break;
				case sf::Event::JoystickButtonPressed:
					if (m_joystickListenersEnabled)
					{
						for (IJoystickListener* listener : m_joystickListeners)
							listener->onPressed(m_event.joystickButton);
					}
					break;
				case sf::Event::JoystickButtonReleased:
					if (m_joystickListenersEnabled)
					{
						for (IJoystickListener* listener : m_joystickListeners)
							listener->onReleased(m_event.joystickButton);
					}
					break;
				// Text event
				case sf::Event::TextEntered:
					for (ITextListener* listener : m_textEnteredListeners)
						listener->onTextEntered(m_event.text);
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

	void	GraphicsManager::setKeyboardEnabled(bool enable)
	{
		m_keyboardListenersEnabled = enable;
	}

	void	GraphicsManager::setMouseEnabled(bool enable)
	{
		m_mouseListenersEnabled = enable;
	}

	void	GraphicsManager::setJoysticksEnabled(bool enable)
	{
		m_joystickListenersEnabled = enable;
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

	void	GraphicsManager::addTextListener(ITextListener* listener)
	{
		appendListener(listener, m_textEnteredListeners);
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

	void	GraphicsManager::removeTextListener(ITextListener* listener)
	{
		removeListener(listener, m_textEnteredListeners);
	}
}
