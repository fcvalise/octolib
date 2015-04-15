/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 02:35:21 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/15 11:54:24 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <StateManager.hpp>
#include <AbstractState.hpp>
#include <AbstractTransition.hpp>
#include <DefaultTransition.hpp>
#include <Application.hpp>
#include <Math.hpp>

#include <GraphicsManager.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Audio/Sound.hpp>

#include <iostream>
#include <cmath>
#include <limits>
#include <iterator>

#include "BSpline.hpp"
#include "FireFly.hpp"

namespace octo
{
	template <class T>
	static T	squaredDistance(sf::Vector2<T> const& a, sf::Vector2<T> const& b)
	{
		return ((pow<2>(b.x - a.x) + pow<2>(b.y - a.y)));
	}
}

class FireFlyTest : public octo::AbstractState,
					public octo::IMouseListener
{
public:
	using AbstractState::AbstractState;

	/*!	Method called when the state is started by the manager */
	virtual void	start()
	{
		m_fireFly.addPoint(sf::Vector2f(0.f, 0.f), true);
		m_fireFly.addPoint(sf::Vector2f(200.f, 0.f), true);
		m_fireFly.addPoint(sf::Vector2f(-200.f, 40.f), true);
		m_fireFly.addPoint(sf::Vector2f(100.f, 60.f), true);
		m_view = octo::Application::getGraphicsManager().getDefaultView();
		m_view.setCenter(m_interestPoint);
		octo::Application::getGraphicsManager().addMouseListener(this);
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
private:
	FireFly			m_fireFly;
	sf::Vector2f	m_interestPoint;
	sf::View		m_view;
};

/*!	Window events listener */
class SimpleWindowListener : public octo::IWindowListener
{
public:
	virtual void	onClosed()
	{
		octo::Application::stop();
	}

	virtual void	onResized(sf::Event::SizeEvent const&)
	{
	}

	virtual void	onFocusGained()
	{
	}

	virtual void	onFocusLost()
	{
	}
};

class KeyboardControl : public octo::IKeyboardListener
{
public:
	virtual bool	onPressed(sf::Event::KeyEvent const& event)
	{
		if (event.code == sf::Keyboard::Escape)
		{
			octo::Application::getStateManager().pop("black_f");
		}
		return (true);
	}

	virtual bool	onReleased(sf::Event::KeyEvent const&)
	{
		return (true);
	}
private:
};

int main(int argc, char **argv)
{
	using namespace octo;

	Application::initialize("bspline", "test.conf", argc, argv);
	GraphicsManager&						graphics = Application::getGraphicsManager();
	StateManager&							states = Application::getStateManager();
	sf::View								view = graphics.getDefaultView();
	SimpleWindowListener					windowListener;
	KeyboardControl							keyboardControl;

	view.setCenter(0.f, 0.f);
	graphics.addWindowListener(&windowListener);
	graphics.addKeyboardListener(&keyboardControl);
	graphics.setView(view);
	graphics.setVerticalSyncEnabled(true);
	states.registerState<FireFlyTest>("main");
	states.registerTransition<octo::BlackFadeTransition>("black_f");
	Application::run("main");
	Application::destroy();
	std::cout << "Goodbye!" << std::endl;
    return 0;
}
