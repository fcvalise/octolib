/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicsManager.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 21:35:29 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/07 20:12:29 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICSMANAGER_HPP
# define GRAPHICSMANAGER_HPP
# include "ListenerHelpers.hpp"
# include "NonCopyable.hpp"

# include <SFML/Graphics/RenderWindow.hpp>
# include <SFML/Window/VideoMode.hpp>
# include <SFML/Window/Event.hpp>
# include <SFML/System/String.hpp>

namespace octo
{
	class IWindowListener;
	class IKeyboardListener;
	class IMouseListener;
	class IJoystickListener;
	class ITextListener;

	/*!
	 *	\ingroup Graphics
	 *	Manage a render window
	 */
	class GraphicsManager : public NonCopyable
	{
	public:
		GraphicsManager();

		void					createRender(sf::VideoMode const& mode,
											 sf::String const& title,
									  		 bool fullscreen);
		void					closeRender();

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
		sf::Vector2f			mapPixelToCoords(sf::Vector2i const& position)const;
		sf::Vector2f			mapPixelToCoords(sf::Vector2i const& position, sf::View const& view)const;
		sf::Vector2i			mapCoordsToPixel(sf::Vector2f const& position)const;
		sf::Vector2i			mapCoordsToPixel(sf::Vector2f const& position, sf::View const& view)const;

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
