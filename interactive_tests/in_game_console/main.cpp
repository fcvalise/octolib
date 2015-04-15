/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 02:35:21 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/14 20:02:04 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <StateManager.hpp>
#include <AbstractState.hpp>
#include <AbstractTransition.hpp>
#include <DefaultTransition.hpp>
#include <Application.hpp>
#include <GraphicsManager.hpp>
#include <Console.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>
#include <codecvt>

/*! A state with a colored square
 *
 *	This state has a constructor with one parameter.
 */
class SquareState : public octo::AbstractState
{
public:
	explicit SquareState(sf::Color const& color)
	{
		m_square = sf::RectangleShape(sf::Vector2f(128.f, 128.f));
		m_square.setOrigin(64.f, 64.f);
		m_square.setFillColor(color);
	}

	virtual void	start()
	{
		std::cout << "Square state start" << std::endl;
	}

	virtual void	pause()
	{
		std::cout << "Square state pause" << std::endl;
	}

	virtual void	resume()
	{
		std::cout << "Square state resume" << std::endl;
	}

	virtual void	stop()
	{
		std::cout << "Square state stop" << std::endl;
	}

	virtual void	update(sf::Time frameTime)
	{
		m_square.rotate(45.f * frameTime.asSeconds());
	}

	virtual void	draw(sf::RenderTarget& render)const
	{
        render.clear(sf::Color(50, 50, 50));
		render.draw(m_square);
	}
private:
	sf::RectangleShape	m_square;
};

/*! A simple state with a with circle */
class CircleState : public octo::AbstractState
{
public:
	explicit CircleState() :
		m_elapsed(sf::Time::Zero)
	{
		m_circle = sf::CircleShape(128.f, 64);
		m_circle.setOrigin(64.f, 64.f);
		m_circle.setFillColor(sf::Color::White);
	}

	virtual void	start()
	{
		std::cout << "Circle state start" << std::endl;
	}

	virtual void	pause()
	{
		std::cout << "Circle state pause" << std::endl;
	}

	virtual void	resume()
	{
		std::cout << "Circle state resume" << std::endl;
	}

	virtual void	stop()
	{
		std::cout << "Circle state stop" << std::endl;
	}

	virtual void	update(sf::Time frameTime)
	{
		float		x = 0.f;

		m_elapsed += frameTime;
		if (m_elapsed > sf::seconds(1.f))
			m_elapsed -= sf::seconds(1.f);
		x = (std::sin((m_elapsed.asSeconds() / 0.5f) * M_PI) * 256.f) - 64.f;
		m_circle.setPosition(x, -64.f);
	}

	virtual void	draw(sf::RenderTarget& render)const
	{
        render.clear(sf::Color(50, 50, 50));
		render.draw(m_circle);
	}
private:
	sf::CircleShape	m_circle;
	sf::Time		m_elapsed;
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
		octo::Application::resume();
	}

	virtual void	onFocusLost()
	{
		octo::Application::pause();
	}
};

/*!	Out keyboard listener
 *
 *	It's in this class is implemented the reaction of key press/release event.
 */
class KeyboardControl : public octo::IKeyboardListener
{
public:
	virtual bool	onPressed(sf::Event::KeyEvent const& event)
	{
		if (event.code == sf::Keyboard::F5)
			octo::Application::getConsole().setEnabled(true);
		if (event.code == sf::Keyboard::Escape)
		{
			octo::Application::getStateManager().popAll();
		}
		if (event.code == sf::Keyboard::Space)
		{
			m_cyclePosition = (m_cyclePosition + 1) % m_stateCycle.size();
			octo::Application::getStateManager().push(m_stateCycle[m_cyclePosition], "black_f");
			std::cout << m_cyclePosition << std::endl;
		}
		else if (event.code == sf::Keyboard::BackSpace)
		{
			octo::Application::getStateManager().pop("black_h");
			std::cout << m_cyclePosition << std::endl;
		}
		return (true);
	}

	virtual bool	onReleased(sf::Event::KeyEvent const&)
	{
		return (true);
	}
private:
	std::vector<octo::StateManager::Key>	m_stateCycle{"circle", "red", "blue", "green"};
	std::size_t								m_cyclePosition{0};
};

int main(int argc, char **argv)
{
	using namespace octo;

	try
	{
		Application::initialize("Application works!", "test.conf", argc, argv);
		GraphicsManager&						graphics = Application::getGraphicsManager();
		StateManager&							states = Application::getStateManager();
		Console&								console = Application::getConsole();
		sf::View								view = graphics.getDefaultView();
		SimpleWindowListener					windowListener;
		KeyboardControl							keyboardControl;


		view.setCenter(0.f, 0.f);
		// Don't forget to add the listeners...
		graphics.addWindowListener(&windowListener);
		graphics.addKeyboardListener(&keyboardControl);
		graphics.setView(view);
		graphics.setVerticalSyncEnabled(true);
		// Simple state registration for state with parameterless constructor
		states.registerState<CircleState>("circle");
		// State registration with lambda
		states.registerStateCreator("red", [](){return new SquareState(sf::Color::Red);});
		states.registerStateCreator("blue", [](){return new SquareState(sf::Color::Blue);});
		states.registerStateCreator("green", [](){return new SquareState(sf::Color::Green);});
		// Transition registration
		states.registerTransition<octo::BlackFadeTransition>("black_f");
		states.registerTransition<octo::BlackVSlideTransition>("black_v");
		states.registerTransition<octo::BlackHSlideTransition>("black_h");
		std::cout << " - Press Space to change current state by an other state.\n"
					 " - Press Backspace to pop the current state.\n"
					 " - Press Escape to quit\n\n";
		std::cout << "You can change somes parameters with command line and test.conf file" << std::endl;
		// Start the main loop with initial state "circle"
		console.addCommand(L"echo", [](std::wstring const& message, sf::Color const& color)
				{
					Application::getConsole().print(message, color);
				});
		Application::run("circle");
	}
	catch (std::exception const& e)
	{
		std::cerr << "exception: " << e.what() << std::endl;
	}
	// When application is stopped, the program quit normally...
	Application::destroy();
	std::cout << "Goodbye!" << std::endl;
    return 0;
}
