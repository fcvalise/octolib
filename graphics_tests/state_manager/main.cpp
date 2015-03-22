/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 02:35:21 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/22 22:01:38 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <StateManager.hpp>
#include <AbstractState.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>

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

	virtual void	update(float frameTime)
	{
		m_square.rotate(45.f * frameTime);
	}

	virtual void	draw(sf::RenderTarget& render)const
	{
		render.draw(m_square);
	}
private:
	sf::RectangleShape	m_square;
};

class CircleState : public octo::AbstractState
{
public:
	explicit CircleState()
	{
		m_circle = sf::CircleShape(128.f);
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

	virtual void	update(float frameTime)
	{
		float		x = 0.f;

		m_elapsed += frameTime;
		x = (std::sin((m_elapsed / 0.5f) * M_PI) * 256.f) - 64.f;
		m_circle.setPosition(x, -64.f);
	}

	virtual void	draw(sf::RenderTarget& render)const
	{
		render.draw(m_circle);
	}
private:
	sf::CircleShape	m_circle;
	float			m_elapsed;
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
    sf::RenderWindow						window(sf::VideoMode::getDesktopMode(), "SFML works!");
	sf::Clock								clock;
	sf::Event								event;
	sf::View								view = window.getDefaultView();
	octo::StateManager						manager;

	view.setCenter(0.f, 0.f);
	window.setView(view);
	// Simple registration for state with parameterless constructor
	manager.registerState<CircleState>("circle");
	// Registration with lambda
	manager.registerCreator("red", [](){return new SquareState(sf::Color::Red);});
	manager.registerCreator("blue", [](){return new SquareState(sf::Color::Blue);});
	manager.registerCreator("green", [](){return new SquareState(sf::Color::Green);});
	std::cout << " - Press P to push a new state (type the key).\n"
				 " - Press C to change current state by a new state (type the key).\n"
				 " - Press backspace to pop the current state.\n"
				 " - Press escape to quit\n\n";
	std::cout << " - Available keys: circle, red, blue, green" << std::endl;
	manager.push(queryKey("push"));
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
				manager.push(queryKey("push"));
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C)
			{
				manager.change(queryKey("change"));
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace)
			{
				manager.pop();
			}
        }
		manager.update(clock.restart().asSeconds());
        window.clear();
		manager.draw(window);
        window.display();
    }
    return 0;
}
