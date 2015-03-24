/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicsManager.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 21:35:29 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/24 20:11:44 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICSMANAGER_HPP
# define GRAPHICSMANAGER_HPP
# include "ListenerHelpers.hpp"

# include <SFML/Graphics/RenderWindow.hpp>
# include <SFML/Window/VideoMode.hpp>
# include <SFML/Window/Event.hpp>
# include <SFML/System/String.hpp>

namespace octo
{
	class IWindowListener
	{
	public:
		virtual ~IWindowListener(){}

		virtual void	onClosed() = 0;
		virtual void	onResized(sf::Event::SizeEvent const& event) = 0;
		virtual void	onFocusGained() = 0;
		virtual void	onFocusLost() = 0;
	};

	class IKeyboardListener
	{
	public:
		virtual ~IKeyboardListener(){}

		virtual void	onPressed(sf::Event::KeyEvent const& event) = 0;
		virtual void	onReleased(sf::Event::KeyEvent const& event) = 0;
	};

	class IMouseListener
	{
	public:
		virtual ~IMouseListener(){}

		virtual void	onMoved(sf::Event::MouseMoveEvent const& event) = 0;
		virtual void	onPressed(sf::Event::MouseButtonEvent const& event) = 0;
		virtual void	onReleased(sf::Event::MouseButtonEvent const& event) = 0;
		virtual void	onWheel(sf::Event::MouseWheelEvent const& event) = 0;
	};

	class IJoystickListener
	{
	public:
		virtual ~IJoystickListener(){}

		virtual void	onConnected(sf::Event::JoystickConnectEvent const& event) = 0;
		virtual void	onDisconnected(sf::Event::JoystickConnectEvent const& event) = 0;
		virtual void	onMoved(sf::Event::JoystickMoveEvent const& event) = 0;
		virtual void	onPressed(sf::Event::JoystickButtonEvent const& event) = 0;
		virtual void	onReleased(sf::Event::JoystickButtonEvent const& event) = 0;
	};

	class GraphicsManager
	{
	public:
		GraphicsManager();

		void					createRender(sf::VideoMode const& mode,
											 sf::String const& title,
									  		 bool fullscreen);

		sf::RenderWindow&		getRenderWindow();

		void					processEvents();
		void					display();

		void					setVideoMode(sf::VideoMode const& mode);
		sf::VideoMode const&	getVideoMode()const;

		void					setFullscreen(bool fullscreen);
		bool					isFullscreen()const;

		void					setVerticalSyncEnabled(bool enable);
		bool					isVerticalSyncEnabled()const;

		void					setView(sf::View const& view);
		sf::View const&			getView()const;
		sf::View const&			getDefaultView()const;

		void					addWindowListener(IWindowListener* listener);
		void					addKeyboardListener(IKeyboardListener* listener);
		void					addMouseListener(IMouseListener* listener);
		void					addJoystickListener(IJoystickListener* listener);
		void					removeWindowListener(IWindowListener* listener);
		void					removeKeyboardListener(IKeyboardListener* listener);
		void					removeMouseListener(IMouseListener* listener);
		void					removeJoystickListener(IJoystickListener* listener);
	private:
		typedef ListenerArray<IWindowListener>		WindowListenerArray;
		typedef ListenerArray<IKeyboardListener>	KeyboardListenerArray;
		typedef ListenerArray<IMouseListener>		MouseListenerArray;
		typedef ListenerArray<IJoystickListener>	JoystickListenerArray;

		sf::RenderWindow			m_window;
		sf::VideoMode				m_videoMode;
		sf::String					m_title;
		bool						m_fullscreen;
		bool						m_verticalSync;

		sf::Event					m_event;
		WindowListenerArray			m_windowListeners;
		KeyboardListenerArray		m_keyboardListeners;
		MouseListenerArray			m_mouseListeners;
		JoystickListenerArray		m_joystickListeners;
	};
}

#endif
