/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 02:35:21 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/08 15:09:44 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <StateManager.hpp>
#include <AbstractState.hpp>
#include <AbstractTransition.hpp>
#include <DefaultTransition.hpp>
#include <Application.hpp>
#include <GraphicsManager.hpp>
#include <Console.hpp>
#include <Camera.hpp>
#include <NonCopyable.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>


/*!	Out keyboard listener
 *
 *	It's in this class is implemented the reaction of key press/release event.
 */
class KeyboardControl : public octo::IKeyboardListener,
						public octo::NonCopyable
{
public:
	virtual bool	onPressed(sf::Event::KeyEvent const& event)
	{
		switch (event.code)
		{
			case sf::Keyboard::F5:
				octo::Application::getConsole().setEnabled(true);
				break;
			case sf::Keyboard::Escape:
				octo::Application::stop();
				break;
			case sf::Keyboard::Space:
				m_cyclePosition = (m_cyclePosition + 1) % m_stateCycle.size();
				octo::Application::getStateManager().push(m_stateCycle[m_cyclePosition], "black_f");
				break;
			case sf::Keyboard::BackSpace:
				octo::Application::getStateManager().pop("black_h");
				std::cout << m_cyclePosition << std::endl;
				break;
			case sf::Keyboard::Up:
				m_cameraControl[0] = true;
				break;
			case sf::Keyboard::Left:
				m_cameraControl[1] = true;
				break;
			case sf::Keyboard::Down:
				m_cameraControl[2] = true;
				break;
			case sf::Keyboard::Right:
				m_cameraControl[3] = true;
				break;
			default:
				break;
		}
		return (true);
	}

	virtual bool	onReleased(sf::Event::KeyEvent const&event)
	{
		switch (event.code)
		{
			case sf::Keyboard::Up:
				m_cameraControl[0] = false;
				break;
			case sf::Keyboard::Left:
				m_cameraControl[1] = false;
				break;
			case sf::Keyboard::Down:
				m_cameraControl[2] = false;
				break;
			case sf::Keyboard::Right:
				m_cameraControl[3] = false;
				break;
			default:
				break;
		}
		return (true);
	}

	void	updateCamera(sf::Time frameTime)const
	{
		static float const	cameraSpeed = 128.f;
		octo::Camera&		camera = octo::Application::getCamera();

		if (m_cameraControl[0])
		{
			camera.move(0.f, -cameraSpeed * frameTime.asSeconds());
		}
		else if (m_cameraControl[2])
		{
			camera.move(0.f, cameraSpeed * frameTime.asSeconds());
		}
		if (m_cameraControl[1])
		{
			camera.move(-cameraSpeed * frameTime.asSeconds(), 0.f);
		}
		else if (m_cameraControl[3])
		{
			camera.move(cameraSpeed * frameTime.asSeconds(), 0.f);
		}
	}
private:
	std::vector<octo::StateManager::Key>	m_stateCycle{"circle", "red", "blue", "green"};
	std::size_t								m_cyclePosition{0};
	bool									m_cameraControl[4];
};

/*! A state with a colored square
 *
 *	This state has a constructor with one parameter.
 */
class SquareState : public octo::AbstractState
{
public:
	explicit SquareState(KeyboardControl const& control, sf::Color const& color) :
		m_control(control)
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
		m_control.updateCamera(frameTime);
	}

	virtual void	draw(sf::RenderTarget& render)const
	{
        render.clear(sf::Color(50, 50, 50));
		render.draw(m_square);
	}
private:
	sf::RectangleShape		m_square;
	KeyboardControl const&	m_control;
};

/*! A simple state with a with circle */
class CircleState : public octo::AbstractState
{
public:
	explicit CircleState(KeyboardControl const& control) :
		m_elapsed(sf::Time::Zero),
		m_control(control)
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
		m_control.updateCamera(frameTime);
	}

	virtual void	draw(sf::RenderTarget& render)const
	{
        render.clear(sf::Color(50, 50, 50));
		render.draw(m_circle);
	}
private:
	sf::CircleShape			m_circle;
	sf::Time				m_elapsed;
	KeyboardControl const&	m_control;
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

int main(int argc, char **argv)
{
	using namespace octo;

	try
	{
		Application::initialize("Application works!", "test.conf", argc, argv);
		GraphicsManager&						graphics = Application::getGraphicsManager();
		StateManager&							states = Application::getStateManager();
		Console&								console = Application::getConsole();
		Camera&									camera = Application::getCamera();
		SimpleWindowListener					windowListener;
		KeyboardControl							keyboardControl;

		camera.setCenter(0.f, 0.f);
		// Don't forget to add the listeners...
		graphics.addWindowListener(&windowListener);
		graphics.addKeyboardListener(&keyboardControl);
		graphics.setVerticalSyncEnabled(true);
		// Simple state registration for state with parameterless constructor
		states.registerStateCreator("circle", [&keyboardControl](){return new CircleState(keyboardControl);});
		// State registration with lambda
		states.registerStateCreator("red", [&keyboardControl](){return new SquareState(keyboardControl, sf::Color::Red);});
		states.registerStateCreator("blue", [&keyboardControl](){return new SquareState(keyboardControl, sf::Color::Blue);});
		states.registerStateCreator("green", [&keyboardControl](){return new SquareState(keyboardControl, sf::Color::Green);});
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
