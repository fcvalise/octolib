/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DefaultGraphicsListeners.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 19:49:31 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/07 20:18:48 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFAULTGRAPHICSLISTENERS_HPP
# define DEFAULTGRAPHICSLISTENERS_HPP
# include "GraphicsListeners.hpp"

namespace octo
{
	/*!
	 *	\ingroup Graphics
	 *	\class BasicWindowListener
	 *	\brief Class that helps to define window listeners
	 *
	 *	This helper provides a default (empty) implementation
	 *	of each virtual pure methods.
	 */
	class DefaultWindowListener : public IWindowListener
	{
	public:
		virtual void	onClosed();
		virtual void	onResized(sf::Event::SizeEvent const& event);
		virtual void	onFocusGained();
		virtual void	onFocusLost();
	};

	/*!
	 *	\ingroup Graphics
	 *	\class BasicKeyboardListener
	 *	\brief Class that helps to define keyboard listeners
	 *
	 *	This helper provides a default (empty) implementation
	 *	of each virtual pure methods.
	 */
	class DefaultKeyboardListener : public IKeyboardListener
	{
	public:
		virtual ~DefaultKeyboardListener(){}

		virtual bool	onPressed(sf::Event::KeyEvent const& event);
		virtual bool	onReleased(sf::Event::KeyEvent const& event);
	};

	/*!
	 *	\ingroup Graphics
	 *	\class BasicMouseListener
	 *	\brief Class that helps to define mouse listeners
	 *
	 *	This helper provides a default (empty) implementation
	 *	of each virtual pure methods.
	 */
	class DefaultMouseListener : public IMouseListener
	{
	public:
		virtual void	onMoved(sf::Event::MouseMoveEvent const& event);
		virtual void	onPressed(sf::Event::MouseButtonEvent const& event);
		virtual void	onReleased(sf::Event::MouseButtonEvent const& event);
		virtual void	onWheel(sf::Event::MouseWheelEvent const& event);
	};

	/*!
	 *	\ingroup Graphics
	 *	\class BasicJoystickListener
	 *	\brief Class that helps to define joystick listeners
	 *
	 *	This helper provides a default (empty) implementation
	 *	of each virtual pure methods.
	 */
	class DefaultJoystickListener : public IJoystickListener
	{
	public:
		virtual void	onConnected(sf::Event::JoystickConnectEvent const& event);
		virtual void	onDisconnected(sf::Event::JoystickConnectEvent const& event);
		virtual void	onMoved(sf::Event::JoystickMoveEvent const& event);
		virtual void	onPressed(sf::Event::JoystickButtonEvent const& event);
		virtual void	onReleased(sf::Event::JoystickButtonEvent const& event);
	};

	/*!
	 *	\ingroup Graphics
	 *	\class BasicJoystickListener
	 *	\brief Class that helps to define text listeners
	 *
	 *	This helper provides a default (empty) implementation
	 *	of each virtual pure methods.
	 */
	class DefaultTextListener : public ITextListener
	{
	public:
		virtual void	onTextEntered(sf::Event::TextEvent const& event);
	};
}

#endif
