/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 02:35:21 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/31 07:02:22 by irabeson         ###   ########.fr       */
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

namespace octo
{
	template <class T>
	static T	squaredDistance(sf::Vector2<T> const& a, sf::Vector2<T> const& b)
	{
		return ((pow<2>(b.x - a.x) + pow<2>(b.y - a.y)));
	}
}

class MainState : public octo::AbstractState,
				  public octo::IMouseListener
{
	static constexpr float const		CheckpointRadius = 4.f;
	static constexpr float const		SelectorRadius = CheckpointRadius + 3.f;
	static constexpr float const		SelectorAnchorDistance = (CheckpointRadius * CheckpointRadius * 6.f);
	static constexpr float const		ActiveThickness = 3.f;
	static constexpr float const		InactiveThickness = 1.f;
	static constexpr std::size_t const	NullSelection = std::numeric_limits<std::size_t>::max();
public:
	explicit MainState() :
		m_selected(NullSelection),
		m_update(false),
		m_visibleSelector(false)
	{
		m_checkpoint = sf::CircleShape(CheckpointRadius, 64.f);
		m_checkpoint.setFillColor(sf::Color::Red);
		m_checkpoint.setOrigin(CheckpointRadius, CheckpointRadius);
		m_selector = sf::CircleShape(SelectorRadius, 64.f);
		m_selector.setOrigin(SelectorRadius, SelectorRadius);
		m_selector.setFillColor(sf::Color::Transparent);
		m_selector.setOutlineColor(sf::Color::Blue);
		m_selector.setOutlineThickness(2.f);
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
			updateSpline();
			m_update = false;
		}
	}

	virtual void	draw(sf::RenderTarget& render)const
	{
        render.clear(sf::Color::White);
		render.draw(&m_vertices.front(), m_vertices.size(), sf::LinesStrip);
		drawCheckpoints(render);
	}

	virtual void	onMoved(sf::Event::MouseMoveEvent const& event)
	{
		octo::GraphicsManager const&	manager = octo::Application::getGraphicsManager();
		sf::Vector2f					mousePosition = manager.mapPixelToCoords(sf::Vector2i(event.x, event.y), manager.getView());
		auto							it = getNearPoint(mousePosition);

		if (m_selected == NullSelection)
		{
			if (it != std::end(m_bspline))
			{
				m_selector.setPosition(*it);
				m_visibleSelector = true;
			}
			else
			{
				m_visibleSelector = false;
			}
		}
		else
		{
			m_bspline[m_selected] = mousePosition;
			m_selector.setPosition(mousePosition);
			m_update = true;
		}
	}

	virtual void	onPressed(sf::Event::MouseButtonEvent const& event)
	{
		octo::GraphicsManager const&	manager = octo::Application::getGraphicsManager();
		sf::Vector2f					mousePosition = manager.mapPixelToCoords(sf::Vector2i(event.x, event.y), manager.getView());
		auto							it = getNearPoint(mousePosition);

		if (event.button == sf::Mouse::Left)
		{
			if (it != std::end(m_bspline))
			{
				m_visibleSelector = true;
				m_selector.setOutlineThickness(ActiveThickness);
				m_selector.setPosition(*it);
				m_selected = std::distance(m_bspline.cbegin(), it);
			}
			else
			{
				m_selected = NullSelection;
			}
		}
	}

	virtual void	onReleased(sf::Event::MouseButtonEvent const& event)
	{
		if (event.button == sf::Mouse::Left && m_selected != NullSelection)
		{
			m_selector.setOutlineThickness(InactiveThickness);
			m_selector.setPosition(m_bspline[m_selected]);
			m_selected = NullSelection;
		}
		else if (event.button == sf::Mouse::Right)
		{
			octo::GraphicsManager const&	manager = octo::Application::getGraphicsManager();
			sf::Vector2f					mousePosition = manager.mapPixelToCoords(sf::Vector2i(event.x, event.y), manager.getView());

			addCheckpoint(mousePosition);
		}
	}

	virtual void	onWheel(sf::Event::MouseWheelEvent const& event)
	{
		(void)event;
	}
private:
	BSpline::const_iterator	getNearPoint(sf::Vector2f const& position)const
	{
		return (std::find_if(std::begin(m_bspline), std::end(m_bspline),
								[=](sf::Vector2f const& p)
								{
									return (octo::squaredDistance(p, position) < SelectorAnchorDistance);
								}));
	}

	void	updateSpline()
	{
		static const unsigned int	Count = 1000;
		float						step = 1.f / Count;
		sf::Vector2f				pos;
		std::size_t					i = 0;

		m_vertices.resize(Count * m_bspline.size());
		for (float t = 0.f; t <= m_bspline.maxT(); t += step)
		{
			pos = m_bspline.compute(t);
			m_vertices[i].position = pos;
			m_vertices[i].color = sf::Color::Black;
			++i;
		}
	}

	void	drawCheckpoints(sf::RenderTarget& render)const
	{
		for (sf::Vector2f const& pos : m_bspline)
		{
			m_checkpoint.setPosition(pos);
			render.draw(m_checkpoint);
		}
		if (m_visibleSelector)
			render.draw(m_selector);
	}
private:
	void	addCheckpoint(sf::Vector2f const& position)
	{
		m_bspline.pushBack(position);
	}
private:
	std::vector<sf::Vertex>			m_vertices;
	sf::CircleShape					m_selector;
	mutable sf::CircleShape			m_checkpoint;
	std::size_t						m_selected;
	bool							m_update;
	bool							m_visibleSelector;
	BSpline							m_bspline;
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
