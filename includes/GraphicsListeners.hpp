/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicsListeners.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 19:51:50 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/07 20:07:14 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICSLISTENERS_HPP
# define GRAPHICSLISTENERS_HPP
# include <SFML/Window/Event.hpp>

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
		virtual ~IWindowListener();

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
		virtual ~IKeyboardListener();

		/*!
		 *	Method called when a key is pressed
	 	 *	\return true if the event must be propagated to other listeners, otherwise false.	 
		 */
		virtual bool	onPressed(sf::Event::KeyEvent const& event) = 0;

		/*!
		 *	Method called when a key is released
	 	 *	\return true if the event must be propagated to other listeners, otherwise false.	 
		 */
		virtual bool	onReleased(sf::Event::KeyEvent const& event) = 0;
	};

	/*!
	 *	\ingroup Graphics
	 *	Mouse listener interface
	 */
	class IMouseListener
	{
	public:
		virtual ~IMouseListener();

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
		virtual ~IJoystickListener();

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
		virtual ~ITextListener();

		virtual void	onTextEntered(sf::Event::TextEvent const& event) = 0;
	};
}

#endif
