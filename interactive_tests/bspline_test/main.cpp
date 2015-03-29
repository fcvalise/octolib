/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 02:35:21 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/29 12:59:55 by irabeson         ###   ########.fr       */
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

namespace octo
{
	template <class T>
	static T	squaredDistance(sf::Vector2<T> const& a, sf::Vector2<T> const& b)
	{
		return ((pow<2>(b.x - a.x) + pow<2>(b.y - a.y)));
	}
}

static sf::Vector2f	bspline(sf::Vector2f const& p0,
							sf::Vector2f const& p1,
							sf::Vector2f const& p2,
							sf::Vector2f const& p3,
							float t)
{
	sf::Vector2f	result;

	result.x =	(1.f / 6.f) * (octo::pow<3>(1.f - t) * p0.x +
				((3.f * octo::pow<3>(t) - 6.f * octo::pow<2>(t) + 4.f) * p1.x) +
				((-3.f * octo::pow<3>(t) + 3.f * octo::pow<2>(t) + (3.f * t) + 1.f) * p2.x) +
				octo::pow<3>(t) * p3.x);
	result.y =	(1.f / 6.f) * (octo::pow<3>(1.f - t) * p0.y +
				((3.f * octo::pow<3>(t) - 6.f * octo::pow<2>(t) + 4.f) * p1.y) +
				((-3.f * octo::pow<3>(t) + 3.f * octo::pow<2>(t) + (3.f * t) + 1.f) * p2.y) +
				octo::pow<3>(t) * p3.y);
	return (result);
}

class MainState : public octo::AbstractState,
				  public octo::IMouseListener
{
	static constexpr float const		Radius = 4.f;
	static constexpr float const		SelectorRadius = Radius + 3.f;
	static constexpr float const		SelectorAnchorDistance = (Radius * Radius * 6.f);
	static constexpr float const		ActiveThickness = 3.f;
	static constexpr float const		InactiveThickness = 1.f;
	static constexpr std::size_t const	NullSelection = std::numeric_limits<std::size_t>::max();
public:
	explicit MainState() :
		m_visibleSelector(false),
		m_selected(NullSelection)
	{
		float					radius = 4.f;
		float 					x = -200.f;

		for (auto& shape : m_checkpoints)
		{
			shape = sf::CircleShape(radius, 64.f);
			shape.setFillColor(sf::Color::Red);
			shape.setOrigin(radius, radius);
			shape.setPosition(x, 0.f);
			x += 200.f;
		}
		m_selector = sf::CircleShape(SelectorRadius, 64.f);
		m_selector.setOrigin(SelectorRadius, SelectorRadius);
		m_selector.setFillColor(sf::Color::Transparent);
		m_selector.setOutlineColor(sf::Color::Blue);
		m_selector.setOutlineThickness(2.f);
		m_update = true;
	}

	~MainState()
	{
	}

	virtual void	start()
	{
		std::cout << "start" << std::endl;
		octo::Application::getGraphicsManager().addMouseListener(this);
	}

	virtual void	pause()
	{
	}

	virtual void	resume()
	{
	}

	virtual void	stop()
	{
		octo::Application::getGraphicsManager().removeMouseListener(this);
		std::cout << "stop" << std::endl;
	}

	virtual void	update(sf::Time)
	{
		if (m_update)
		{
			redrawSpline();
			m_update = false;
		}
	}

	virtual void	draw(sf::RenderTarget& render)const
	{
        render.clear(sf::Color::White);
		render.draw(&m_vertices.front(), m_vertices.size(), sf::LinesStrip);
		for (auto const& shape : m_checkpoints)
			render.draw(shape);
		if (m_visibleSelector)
			render.draw(m_selector);
	}

	virtual void	onMoved(sf::Event::MouseMoveEvent const& event)
	{
		octo::GraphicsManager const&	manager = octo::Application::getGraphicsManager();
		sf::Vector2f					mousePosition = manager.mapPixelToCoords(sf::Vector2i(event.x, event.y), manager.getView());

		if (m_selected == NullSelection)
		{
			auto							it = std::find_if(std::begin(m_checkpoints), std::end(m_checkpoints),
															[=](sf::Transformable const& transformable)
															{
																return (octo::squaredDistance(transformable.getPosition(), mousePosition) < SelectorAnchorDistance);
															});
			
			if (it != std::end(m_checkpoints))
			{
				m_selector.setPosition(it->getPosition());
				m_visibleSelector = true;
			}
			else
			{
				m_visibleSelector = false;
			}
		}
		else
		{
			m_checkpoints[m_selected].setPosition(mousePosition);
			m_selector.setPosition(mousePosition);
			m_update = true;
		}
	}

	virtual void	onPressed(sf::Event::MouseButtonEvent const& event)
	{
		octo::GraphicsManager const&	manager = octo::Application::getGraphicsManager();
		sf::Vector2f					mousePosition = manager.mapPixelToCoords(sf::Vector2i(event.x, event.y), manager.getView());
		auto							it = std::find_if(std::begin(m_checkpoints), std::end(m_checkpoints),
														[=](sf::Transformable const& transformable)
														{
															return (octo::squaredDistance(transformable.getPosition(), mousePosition) < SelectorAnchorDistance);
														});

		if (it != std::end(m_checkpoints))
		{
			m_visibleSelector = true;
			m_selector.setOutlineThickness(ActiveThickness);
			m_selector.setPosition(it->getPosition());
			m_selected = std::distance(std::begin(m_checkpoints), it);
		}
		else
		{
			m_selected = NullSelection;
		}
	}

	virtual void	onReleased(sf::Event::MouseButtonEvent const&)
	{
		if (m_selected != NullSelection)
		{
			m_selector.setOutlineThickness(InactiveThickness);
			m_selector.setPosition(m_checkpoints[m_selected].getPosition());
			m_selected = NullSelection;
		}
	}

	virtual void	onWheel(sf::Event::MouseWheelEvent const& event)
	{
		(void)event;
	}
private:
	void	redrawSpline()
	{
		static const unsigned int	Count = 1000;
		float						step = 1.f / Count;
		sf::Vector2f				pos;
		std::size_t					i = 0;

		m_vertices.resize(Count);
		for (float t = 0.f; t <= 1.f; t += step)
		{
			pos = bspline(m_checkpoints[0].getPosition(),
						  m_checkpoints[1].getPosition(),
						  m_checkpoints[2].getPosition(),
						  m_checkpoints[3].getPosition(),
						  t);
			m_vertices[i].position = pos;
			m_vertices[i].color = sf::Color::Black;
			++i;
		}
	}
private:
	bool					m_update;
	sf::CircleShape			m_checkpoints[4];
	sf::CircleShape			m_selector;
	bool					m_visibleSelector;
	std::size_t				m_selected;
	std::vector<sf::Vertex>	m_vertices;
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
	virtual void	onPressed(sf::Event::KeyEvent const& event)
	{
		if (event.code == sf::Keyboard::Escape)
		{
			octo::Application::getStateManager().pop("black_f");
		}
	}

	virtual void	onReleased(sf::Event::KeyEvent const&)
	{
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
	states.registerState<MainState>("main");
	states.registerTransition<octo::BlackFadeTransition>("black_f");
	Application::run("main");
	Application::destroy();
	std::cout << "Goodbye!" << std::endl;
    return 0;
}
