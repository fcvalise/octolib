/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FireFlyTest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/15 12:20:22 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/15 14:36:32 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIREFLYTEST_HPP
# define FIREFLYTEST_HPP
# include <Application.hpp>
# include <GraphicsManager.hpp>
# include <Console.hpp>
# include <ResourceManager.hpp>
# include "FireFly.hpp"
# include "ResourceDefinitions.hpp"

class FireFlyTest : public octo::AbstractState,
					public octo::IMouseListener,
					public octo::IKeyboardListener,
					public octo::IWindowListener
{
public:
	using AbstractState::AbstractState;

	/*!	Method called when the state is started by the manager */
	virtual void	start()
	{
		octo::GraphicsManager&	graphics = octo::Application::getGraphicsManager();
		octo::Console&			console = octo::Application::getConsole();
		octo::ResourceManager&	resources = octo::Application::getResourceManager();

		graphics.addMouseListener(this);
		graphics.addKeyboardListener(this);
		graphics.addWindowListener(this);
		m_fireFly.setTexture(resources.getTexture(FIREFLY01_PNG));
		m_view = octo::Application::getGraphicsManager().getDefaultView();
		m_view.setCenter(m_interestPoint);
		octo::Application::getGraphicsManager().addMouseListener(this);
		console.addCommand(L"setSpeed", m_fireFly, &FireFly::setSpeed);
		console.addCommand(L"getSpeed", m_fireFly, &FireFly::getSpeed);
		console.addCommand(L"setInterest", m_fireFly, &FireFly::setInterest);
		console.addCommand(L"getInterest", m_fireFly, &FireFly::getInterest);
		console.addCommand(L"setDiameter", m_fireFly, &FireFly::setDiameter);
		console.addCommand(L"getDiameter", m_fireFly, &FireFly::getDiameter);
		console.addCommand(L"setColor", m_fireFly, &FireFly::setColor);
		console.addCommand(L"getColor", m_fireFly, &FireFly::getColor);
		console.addCommand(L"getT", m_fireFly, &FireFly::getT);
	}

	/*!	Method called when the state is paused by the manager */
	virtual void	pause()
	{
	}

	/*!	Method called when the state is resumed by the manager */
	virtual void	resume()
	{
	}

	/*!	Method called when the state is stopped by the manager */
	virtual void	stop()
	{
	}

	/*!	Method called once per frame before game render */
	virtual void	update(sf::Time frameTime)
	{
		m_fireFly.update(frameTime, m_interestPoint);
	}

	/*!	Method called once per frame after game update */
	virtual void	draw(sf::RenderTarget& render)const
	{
		render.clear();
		render.setView(m_view);
		m_fireFly.draw(render);
	}

	virtual void	onMoved(sf::Event::MouseMoveEvent const& event)
	{
		sf::Vector2i		mousePos(event.x, event.y);
		
		m_interestPoint = octo::Application::getGraphicsManager().mapPixelToCoords(mousePos, m_view);		
	}

	virtual void	onPressed(sf::Event::MouseButtonEvent const&)
	{

	}

	virtual void	onReleased(sf::Event::MouseButtonEvent const&)
	{

	}

	virtual void	onWheel(sf::Event::MouseWheelEvent const&)
	{

	}

	virtual bool	onPressed(sf::Event::KeyEvent const& event)
	{
		if (event.code == sf::Keyboard::F5)
			octo::Application::getConsole().setEnabled(true);
		if (event.code == sf::Keyboard::Escape)
		{
			octo::Application::getStateManager().popAll();
		}
		return (true);
	}

	virtual bool	onReleased(sf::Event::KeyEvent const&)
	{
		return (true);
	}

	virtual void	onClosed()
	{
		octo::Application::stop();
	}

	virtual void	onResized(sf::Event::SizeEvent const&)
	{
	}

	virtual void	onFocusGained()
	{
		octo::Application::resume();
	}

	virtual void	onFocusLost()
	{
		octo::Application::pause();
	}
private:
	FireFly			m_fireFly;
	sf::Vector2f	m_interestPoint;
	sf::View		m_view;
};

#endif
