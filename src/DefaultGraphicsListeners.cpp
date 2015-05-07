/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DefaultGraphicsListeners.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 19:56:18 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/07 20:07:54 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DefaultGraphicsListeners.hpp"

namespace octo
{
	//
	// DefaultWindowListener
	//
	void	DefaultWindowListener::onClosed()
	{
	}

	void	DefaultWindowListener::onResized(sf::Event::SizeEvent const&)
	{
	}

	void	DefaultWindowListener::onFocusGained()
	{
	}

	void	DefaultWindowListener::onFocusLost()
	{
	}

	//
	// DefaultKeyboardListener
	//
	bool	DefaultKeyboardListener::onPressed(sf::Event::KeyEvent const&)
	{
		return (true);
	}

	bool	DefaultKeyboardListener::onReleased(sf::Event::KeyEvent const&)
	{
		return (true);
	}

	//
	// DefaultMouseListener
	//
	void	DefaultMouseListener::onMoved(sf::Event::MouseMoveEvent const&)
	{
	}

	void	DefaultMouseListener::onPressed(sf::Event::MouseButtonEvent const&)
	{
	}

	void	DefaultMouseListener::onReleased(sf::Event::MouseButtonEvent const&)
	{
	}

	void	DefaultMouseListener::onWheel(sf::Event::MouseWheelEvent const&)
	{
	}
	
	//
	// DefaultJoystickListener
	//
	void	DefaultJoystickListener::onConnected(sf::Event::JoystickConnectEvent const&)
	{
	}

	void	DefaultJoystickListener::onDisconnected(sf::Event::JoystickConnectEvent const&)
	{
	}

	void	DefaultJoystickListener::onMoved(sf::Event::JoystickMoveEvent const&)
	{
	}

	void	DefaultJoystickListener::onPressed(sf::Event::JoystickButtonEvent const&)
	{
	}

	void	DefaultJoystickListener::onReleased(sf::Event::JoystickButtonEvent const&)
	{
	}

	//
	// DefaultTextListener
	//
	void	DefaultTextListener::onTextEntered(sf::Event::TextEvent const&)
	{
	}
}
