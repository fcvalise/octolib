/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 02:35:21 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/29 04:42:33 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <StateManager.hpp>
#include <AbstractState.hpp>
#include <AbstractTransition.hpp>
#include <DefaultTransition.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>

// A state with a colored square
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
		render.draw(m_square);
	}
private:
	sf::RectangleShape	m_square;
};

// A state with a with circle
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

static octo::StateManager::Key	queryKey(std::string const& action)
{
	std::string	key;

	std::cout << "Enter a key to " << action << ": ";
   	std::cin >> key;
	return (key);
}

int main()
{
    sf::RenderWindow						window(sf::VideoMode::getDesktopMode(), "StateManager works!");
	sf::Clock								clock;
	sf::Event								event;
	sf::View								view = window.getDefaultView();
	octo::StateManager						manager;
	std::vector<octo::StateManager::Key>	stateCycle{"circle", "red", "blue", "green"};
	std::size_t								cyclePosition{0};

	view.setCenter(0.f, 0.f);
	window.setView(view);
	window.setVerticalSyncEnabled(true);
	// Simple state registration for state with parameterless constructor
	manager.registerState<CircleState>("circle");
	// State registration with lambda
	manager.registerStateCreator("red", [](){return new SquareState(sf::Color::Red);});
	manager.registerStateCreator("blue", [](){return new SquareState(sf::Color::Blue);});
	manager.registerStateCreator("green", [](){return new SquareState(sf::Color::Green);});
	// Transition registration
	manager.registerTransition<octo::BlackFadeTransition>("black_f");
	manager.registerTransition<octo::BlackVSlideTransition>("black_v");
	manager.registerTransition<octo::BlackHSlideTransition>("black_h");

	std::cout << " - Press Space to change current state by an other state.\n"
				 " - Press Backspace to pop the current state.\n"
				 " - Press Escape to quit\n\n"
				 " - Press P to push a new state (type the key).\n"
				 " - Press C to change current state by a new state (type the key).\n\n"
				 " - Available keys: circle, red, blue, green" << std::endl;
	manager.push(stateCycle[cyclePosition]);
    while (manager.hasCurrentState())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
				manager.popAll();
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
			{
				manager.push(queryKey("push"), "black_f");
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C)
			{
				manager.change(queryKey("change"), "black_f");
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			{
				cyclePosition = (cyclePosition + 1) % stateCycle.size();
				manager.change(stateCycle[cyclePosition], "black_f");
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace)
			{
				manager.pop("black_v");
			}
        }
		manager.update(clock.restart(), window.getView());
        window.clear(sf::Color(50, 50, 50));
		manager.draw(window);
        window.display();
    }
    return 0;
}
