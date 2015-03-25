/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 20:51:41 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/25 02:48:21 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Application.hpp"
#include "PausableClock.hpp"
#include "GraphicsManager.hpp"
#include "Options.hpp"

#include <cassert>

namespace octo
{
	class ApplicationImp
	{
	public:
		void	setupOptions(std::string const& optionFilePath, int argc, char **argv)
		{
			m_options.load(Options::ConfigFileLoader(optionFilePath));
			m_options.load(Options::CommandLineLoader(argc, argv));
		}

		void	setupGraphics(std::string const& title)
		{
			m_graphicsManager.createRender(m_options.getValue("resolution", sf::VideoMode::getFullscreenModes().front()),
										   title,
										   m_options.getValue("fullscreen", false));
		}

		void	start(StateManager::Key const& startStateKey)
		{
			m_stateManager.push(m_options.getValue("start_state", startStateKey));
			m_clock.restart();
		}

		void	stop()
		{
			m_stateManager.popAll();
		}

		void	run()
		{
			float	frameTime = .0f;

			m_paused = false;
			while (m_stateManager.hasCurrentState())
			{
				m_graphicsManager.processEvents();
				if (m_paused == false)
					m_stateManager.update(frameTime, m_graphicsManager.getView());
				m_stateManager.draw(m_graphicsManager.getRender());
				m_graphicsManager.display();
				frameTime = m_clock.restart().asSeconds();
			}
		}

		StateManager	m_stateManager;
		GraphicsManager	m_graphicsManager;
		Options			m_options;
		PausableClock	m_clock;
		sf::Event		m_event;
		bool			m_paused;
	};

	ApplicationImp*	Application::s_instance = nullptr;

	void	Application::initialize(std::string const& title, std::string const& optionFilePath, int argc, char **argv)
	{
		assert (s_instance == nullptr);

		s_instance = new ApplicationImp;
		s_instance->setupOptions(optionFilePath, argc, argv);
		s_instance->setupGraphics(title);
		static_cast<void>(argc);
		static_cast<void>(argv);
	}

	void	Application::destroy()
	{
		assert (s_instance != nullptr);

		delete s_instance;
		s_instance = nullptr;
	}

	void	Application::run(StateManager::Key const& stateKey)
	{
		assert (s_instance != nullptr);

		s_instance->start(stateKey);
		s_instance->run();
	}

	void	Application::pause()
	{
		assert (s_instance != nullptr);
		
		s_instance->m_paused = true;
		s_instance->m_clock.pause();
	}

	void	Application::resume()
	{
		assert (s_instance != nullptr);
		
		s_instance->m_paused = false;
		s_instance->m_clock.resume();
	}

	void	Application::stop()
	{
		assert (s_instance != nullptr);

		s_instance->stop();
	}

	void	Application::error(char const* message)
	{
		std::cerr << "fatal: " << message << std::endl;
		if (s_instance != nullptr)
			s_instance->stop();
	}

	StateManager&	Application::getStateManager()
	{
		assert (s_instance != nullptr);

		return (s_instance->m_stateManager);
	}

	GraphicsManager&	Application::getGraphicsManager()
	{
		assert (s_instance != nullptr);

		return (s_instance->m_graphicsManager);
	}
	
	Options&	Application::getOptions()
	{
		assert (s_instance != nullptr);

		return (s_instance->m_options);
	}
}