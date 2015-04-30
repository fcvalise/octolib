/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 20:51:41 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/30 15:12:00 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Application.hpp"
#include "PausableClock.hpp"
#include "GraphicsManager.hpp"
#include "ResourceManager.hpp"
#include "Options.hpp"
#include "Console.hpp"
#include "PrintSFML.hpp"
#include "StringUtils.hpp"

#include <SFML/Graphics/RenderTexture.hpp>

#include <cassert>

namespace octo
{
	namespace
	{
		static std::string	makeSymbolName(std::string str)
		{
			std::for_each(std::begin(str), std::end(str), [](char& c)
				{
					if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
					{
						c = std::toupper(c);
					}
					else
					{
						c = '_';
					}
				});
			return (str);
		}

		std::string	screenshotFileName()
		{
			std::chrono::system_clock::time_point	tp = std::chrono::system_clock::now();
			std::time_t								t = std::chrono::system_clock::to_time_t(tp);
			std::string								ts = std::ctime(&t);

			ts.resize(ts.size() - 1);
			return ("screenshot_" + makeSymbolName(ts) + ".png");
		}
	}

	class ResourceLoadingListener : public IResourceListener
	{
	public:
		virtual void	progress(std::string const& name,
								 PackageHeader::EntryType type,
								 std::uint64_t current,
								 std::uint64_t total)
		{
			std::cout << "loading " << name << " [" << (int)type << "] " << current  + 1 << "/" << total << std::endl;
		}

		virtual void	error(std::string const& message)
		{
			std::cerr << "resource loading error: " << message << std::endl;
		}
	};

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
			m_graphicsManager.createRender(m_options.getValue<sf::VideoMode>("resolution", sf::VideoMode::getFullscreenModes().front()),
										   title,
										   m_options.getValue("fullscreen", false));
			m_graphicsManager.setVerticalSyncEnabled(m_options.getValue("vsync", true));
		}

		void	setupResources()
		{
			ResourceLoadingListener	listener;

			if (m_options.containsKey("package") && m_options.hasValue("package"))
				m_resourceManager.loadPackage(m_options.getValue<std::string>("package"), &listener);
			else
				std::cout << "warning no package loaded" << std::endl;
		}

		void	setupConsole()
		{
			if (m_options.containsKey("console_font") && m_options.hasValue("console_font"))
			{
				m_graphicsManager.addKeyboardListener(&m_console);
				m_graphicsManager.addTextListener(&m_console);
				m_console.setFont(m_resourceManager.getFont(m_options.getValue<std::string>("console_font")));
				// Setup builtin commands
				m_console.addCommand(L"console.close", [](){Application::getConsole().setEnabled(false);});
				m_console.addCommand(L"console.clear", [](){Application::getConsole().clear();});
				m_console.addCommand(L"console.list_commands", []()
						{
							Console&	console = Application::getConsole();

							std::wcout << "Available console commands:\n";

							for (std::wstring const& key : console.getCommandList())
							{
								std::wcout << " - " << key << "\n";  
							}
							return (L"See your terminal!");
						});
				m_console.addCommand(L"render.screenshot", this, &ApplicationImp::screenshot);
				m_console.addCommand(L"system.quit", [](){Application::stop();});
				m_console.addCommand(L"system.change_state", [](std::string const& key)
						{
							octo::Application::getStateManager().change(key);
						});
				m_console.addCommand(L"system.list_states",[]()
						{
							StateManager&	stateManager = Application::getStateManager();
	
							std::cout << "Available states:\n";

							for (std::string const& key : stateManager.availableStateKeys())
							{
								std::cout << " - " << key << "\n"; 
							}
							return (L"See your terminal!");
						});
				m_console.addCommand(L"system.list_transitions",[]()
						{
							StateManager&	stateManager = Application::getStateManager();
	
							std::cout << "Available states:\n";

							for (std::string const& key : stateManager.availableStateKeys())
							{
								std::cout << " - " << key << "\n"; 
							}
							return (L"See your terminal!");
						});
			}
			else
			{
				std::cout << "warning no console font defined, console is disabled" << std::endl;
			}
		}

		void	start(StateManager::Key const& startStateKey)
		{
			std::string		keyStarted = m_options.getValue("start_state", startStateKey);

			m_stateManager.push(keyStarted);
			m_clock.restart();
			m_console.print(L"Starting state " + stringToWide(keyStarted), Console::HelpColor);
		}

		void	stop()
		{
			m_stateManager.popAll();
			m_graphicsManager.closeRender();
		}

		void	run()
		{
			sf::Time	frameTime = sf::Time::Zero;

			m_paused = false;
			while (m_stateManager.hasCurrentState())
			{
				m_graphicsManager.processEvents();
				if (m_paused == false)
					m_stateManager.update(frameTime, m_graphicsManager.getView());
				m_console.update(frameTime, m_graphicsManager.getView());
				m_stateManager.draw(m_graphicsManager.getRender());
				m_console.draw(m_graphicsManager.getRender());
				m_graphicsManager.display();
				frameTime = m_clock.restart();
			}
		}

		std::string	screenshot(bool captureConsole)
		{
			sf::Image				image;
			std::string				path = screenshotFileName();
			
			if (m_screenshotRender == nullptr)
			{
				sf::VideoMode const&	mode = m_graphicsManager.getVideoMode();

				m_screenshotRender.reset(new sf::RenderTexture);
				m_screenshotRender->create(mode.width, mode.height);
			}
			m_screenshotRender->setView(m_graphicsManager.getView());
			m_stateManager.draw(*m_screenshotRender);
			if (captureConsole)
				m_console.draw(*m_screenshotRender);
			m_screenshotRender->display();
			image = std::move(m_screenshotRender->getTexture().copyToImage());
			image.saveToFile(path);
			return (path);
		}

		std::unique_ptr<sf::RenderTexture>	m_screenshotRender;
		StateManager						m_stateManager;
		GraphicsManager						m_graphicsManager;
		ResourceManager						m_resourceManager;
		Options								m_options;
		Console								m_console;
		PausableClock						m_clock;
		sf::Event							m_event;
		bool								m_paused;
	};

	ApplicationImp*	Application::s_instance = nullptr;

	void	Application::initialize(std::string const& title, std::string const& optionFilePath, int argc, char **argv)
	{
		assert (s_instance == nullptr);

		s_instance = new ApplicationImp;
		s_instance->setupOptions(optionFilePath, argc, argv);
		s_instance->setupGraphics(title);
		s_instance->setupResources();
		s_instance->setupConsole();
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
	
	ResourceManager&	Application::getResourceManager()
	{
		assert (s_instance != nullptr);

		return (s_instance->m_resourceManager);
	}

	Options&	Application::getOptions()
	{
		assert (s_instance != nullptr);

		return (s_instance->m_options);
	}

	Console&	Application::getConsole()
	{
		assert (s_instance != nullptr);

		return (s_instance->m_console);
	}
}
