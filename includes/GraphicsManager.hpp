/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicsManager.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 21:35:29 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/14 14:32:41 by irabeson         ###   ########.fr       */
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
	/*!	\ingroup Graphics
	 *	Window event listener
	 *
	 *	This listener is notified when a window receive close event, resize event
	 *	and focus events.
	 */
	class IWindowListener
	{
	public:
		virtual ~IWindowListener(){}

		virtual void	onClosed() = 0;
		virtual void	onResized(sf::Event::SizeEvent const& event) = 0;
		virtual void	onFocusGained() = 0;
		virtual void	onFocusLost() = 0;
	};

	/*!	\ingroup Graphics
	 *	Keyboard listener interface
	 */
	class IKeyboardListener
	{
	public:
		virtual ~IKeyboardListener(){}

		virtual bool	onPressed(sf::Event::KeyEvent const& event) = 0;
		virtual bool	onReleased(sf::Event::KeyEvent const& event) = 0;
	};

	/*!
	 *	\ingroup Graphics
	 *	Mouse listener interface
	 */
	class IMouseListener
	{
	public:
		virtual ~IMouseListener(){}

		virtual void	onMoved(sf::Event::MouseMoveEvent const& event) = 0;
		virtual void	onPressed(sf::Event::MouseButtonEvent const& event) = 0;
		virtual void	onReleased(sf::Event::MouseButtonEvent const& event) = 0;
		virtual void	onWheel(sf::Event::MouseWheelEvent const& event) = 0;
	};

	/*!
	 *	\ingroup Graphics
	 *	Joystick listener interface
	 */
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

	/*!
	 *	\ingroup Graphics
	 *	Text entered listener interface
	 */
	class ITextListener
	{
	public:
		virtual ~ITextListener(){}

		virtual void	onTextEntered(sf::Event::TextEvent const& event) = 0;
	};

	/*!
	 *	\ingroup Graphics
	 *	Manage a render window
	 */
	class GraphicsManager
	{
	public:
		GraphicsManager();

		void					createRender(sf::VideoMode const& mode,
											 sf::String const& title,
									  		 bool fullscreen);
		void					draw(sf::Drawable const& drawble,
									 sf::RenderStates const& states = sf::RenderStates::Default);
		void					draw(sf::Vertex const* vertices, unsigned int count, sf::PrimitiveType type,
									 sf::RenderStates const& states = sf::RenderStates::Default);

		sf::RenderTarget&		getRender();
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

		void					setKeyboardEnabled(bool enable);
		void					setMouseEnabled(bool enable);
		void					setJoysticksEnabled(bool enable);
		void					addWindowListener(IWindowListener* listener);
		void					addKeyboardListener(IKeyboardListener* listener);
		void					addMouseListener(IMouseListener* listener);
		void					addJoystickListener(IJoystickListener* listener);
		void					addTextListener(ITextListener* listener);
		void					removeWindowListener(IWindowListener* listener);
		void					removeKeyboardListener(IKeyboardListener* listener);
		void					removeMouseListener(IMouseListener* listener);
		void					removeJoystickListener(IJoystickListener* listener);
		void					removeTextListener(ITextListener* listener);
	private:
		typedef ListenerArray<IWindowListener>		WindowListenerArray;
		typedef ListenerArray<IKeyboardListener>	KeyboardListenerArray;
		typedef ListenerArray<IMouseListener>		MouseListenerArray;
		typedef ListenerArray<IJoystickListener>	JoystickListenerArray;
		typedef ListenerArray<ITextListener>		TextListenerArray;

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
		TextListenerArray			m_textEnteredListeners;
		bool						m_keyboardListenersEnabled;
		bool						m_mouseListenersEnabled;
		bool						m_joystickListenersEnabled;
	};
}

#endif
