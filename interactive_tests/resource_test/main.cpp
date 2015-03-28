/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 02:35:21 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/28 23:03:14 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ResourceDefinitions.hpp"

#include <StateManager.hpp>
#include <AbstractState.hpp>
#include <AbstractTransition.hpp>
#include <DefaultTransition.hpp>
#include <Application.hpp>
#include <GraphicsManager.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/Sound.hpp>

#include <iostream>
#include <cmath>

class MainState : public octo::AbstractState
{
public:
	explicit MainState()
	{
		m_text.setFont(octo::Application::getResourceManager().getFont(QUICKSAND_REGULAR_OTF));
		m_text.setCharacterSize(20);
		m_text.setString(octo::Application::getResourceManager().getText(MONOLOGUE_TXT));
		m_text.setColor(sf::Color::White);
		m_text.setPosition(0.f, 0.f);
		m_sprite.setTexture(octo::Application::getResourceManager().getTexture(BLOCKS_PNG));
		m_sprite.setPosition(-128, -64);
		m_sound.setBuffer(octo::Application::getResourceManager().getSound(LOOP0_WAV));
		m_sound.setLoop(true);
	}

	~MainState()
	{
		m_sound.resetBuffer();
	}

	virtual void	start()
	{
		m_sound.play();
	}

	virtual void	pause()
	{
		m_sound.pause();
	}

	virtual void	resume()
	{
		m_sound.play();
	}

	virtual void	stop()
	{
		m_sound.stop();
	}

	virtual void	update(float)
	{
	}

	virtual void	draw(sf::RenderTarget& render)const
	{
        render.clear(sf::Color(50, 50, 50));
		render.draw(m_text);
		render.draw(m_sprite);
	}
private:
	sf::Text			m_text;
	sf::Sprite			m_sprite;
	sf::Sound			m_sound;
	sf::SoundBuffer		m_buffer;
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

	Application::initialize("Resource system works!", "test.conf", argc, argv);
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
