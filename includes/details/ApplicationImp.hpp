/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ApplicationImp.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 01:22:47 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/28 01:52:37 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APPLICATIONIMP_HPP
# define APPLICATIONIMP_HPP
# include <chrono>
# include <algorithm>
# include <string>
# include <cctype>

namespace octo
{
	namespace details
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

		class ResourceLoadingListener : public IResourceListener
		{
		public:
			virtual void	progress(std::string const& name,
									 PackageHeader::EntryType type,
									 std::uint64_t current,
									 std::uint64_t total)
			{
				octo::Console&	console = octo::Application::getConsole();

				console.addWord(name, ConsoleCompletion::Lexems::Parameter);
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
			ApplicationImp() :
				m_paused(false)
			{
			}

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
				m_graphicsManager.setFramerateLimit(m_options.getValue("framerate_limit", 0));
				m_camera.setup(m_graphicsManager);
			}

			void	setupAudio()
			{
				m_audioManager.setup(m_options.getValue<std::size_t>("max_sounds", 128));
				m_audioManager.setSoundVolume(m_options.getValue<float>("sfx_volume", 100.f));
				m_audioManager.setMusicVolume(m_options.getValue<float>("music_volume", 100.f));
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
				Palette const*	consolePalette = nullptr;
				sf::Font const*	consoleFont = nullptr;
				unsigned int	consoleFontSize = 0;

				if (m_options.hasValue("console_font") == false)
				{
					std::cout << "Warning: no console font defined, console is disabled" << std::endl;
					return;
				}
				if (m_options.hasValue("console_palette") == false)
				{
					std::cout << "Warning: no console palette defined, console is disabled" << std::endl;
					return;
				}
				consolePalette = &m_resourceManager.getPalette(m_options.getValue<std::string>("console_palette"));
				consoleFont = &m_resourceManager.getFont(m_options.getValue<std::string>("console_font"));
				consoleFontSize = m_options.getValue<unsigned int>("console_font_size", 24);
				m_graphicsManager.addKeyboardListener(&m_console);
				m_graphicsManager.addTextListener(&m_console);
				m_console.setPalette(*consolePalette);
				m_console.setFont(*consoleFont, consoleFontSize);
				// Setup builtin commands
				// Console commands
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
				// Render commands
				m_console.addCommand(L"render.screenshot", this, &ApplicationImp::screenshot);
				m_console.addCommand(L"render.set_fullscreen", m_graphicsManager, &GraphicsManager::setFullscreen);
				m_console.addCommand(L"render.set_vsync", m_graphicsManager, &GraphicsManager::setVerticalSyncEnabled);
				// System commands
				m_console.addCommand(L"system.quit", [](){Application::stop();});
				m_console.addCommand(L"system.push_state", [](std::string const& key)
						{
							try
							{
								octo::Application::getStateManager().push(key);
							}
							catch (std::range_error const& e)
							{
								octo::Application::getConsole().printError(e);
							}
						});
				m_console.addCommand(L"system.change_state", [](std::string const& key)
						{
							try
							{
								octo::Application::getStateManager().change(key);
							}
							catch (std::range_error const& e)
							{
								octo::Application::getConsole().printError(e);
							}
						});
				m_console.addCommand(L"system.pop_state", []()
						{
							octo::Application::getStateManager().pop();
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

							for (std::string const& key : stateManager.availableTransitionKeys())
							{
								std::cout << " - " << key << "\n"; 
							}
							return (L"See your terminal!");
						});
				m_console.addCommand(L"system.show_fps_counter",[this](bool show)
						{
							if (m_fpsDisplayer)
								m_fpsDisplayer->setVisible(show);
						});
			}

			void	setupFpsCounter()
			{
				Palette const*	fpsPalette = nullptr;
				sf::Font const*	fpsFont = nullptr;
				unsigned int	fpsFontSize = 0;
				std::size_t		fpsCounterSamples = 0;

				if (m_options.getValue("fps_counter_enabled", false) == false)
					return;
				if (m_options.hasValue("fps_counter_palette") == false)
				{
					std::cout << "Warning: no FPS counter palette defined, FPS counter is disabled" << std::endl;
					return;
				}
				if (m_options.hasValue("fps_counter_font") == false)
				{
					std::cout << "Warning: no FPS counter font defined, FPS counter is disabled" << std::endl;
					return;
				}
				fpsPalette = &m_resourceManager.getPalette(m_options.getValue<std::string>("fps_counter_palette"));
				fpsFont = &m_resourceManager.getFont(m_options.getValue<std::string>("fps_counter_font"));
				fpsCounterSamples = m_options.getValue("fps_counter_samples", 8);
				fpsFontSize = m_options.getValue("fps_counter_font_size", 12);
				m_fpsDisplayer.reset(new FpsDisplayer(fpsFont, fpsFontSize, fpsPalette, fpsCounterSamples));
				m_fpsCounter.setDisplay(m_fpsDisplayer.get());
				m_fpsCounter.setEnabled(true);
			}

			void	start(StateManager::Key const& startStateKey)
			{
				std::string		keyStarted = m_options.getValue("start_state", startStateKey);

				m_stateManager.push(keyStarted);
				m_clock.restart();
				m_console.addWords(m_stateManager.availableStateKeys(), ConsoleCompletion::Lexems::Parameter);
				m_console.printHelp(L"Starting state " + stringToWide(keyStarted));
			}

			void	stop()
			{
				m_stateManager.pushEvent(PopAllStateEvent());
			}

			void	drawAll()
			{
				sf::RenderTarget&	render = m_graphicsManager.getRender();

				render.setView(m_camera.getView());
				m_stateManager.draw(render);
				render.setView(m_camera.getGuiView());
				m_stateManager.drawTransition(render);
				m_console.draw(render);
				if (m_fpsDisplayer)
					m_fpsDisplayer->draw(render);
				m_graphicsManager.display();
			}

			void	run()
			{
				sf::Time		frameTime = sf::Time::Zero;
				sf::View const&	guiView = m_camera.getGuiView();

				m_paused = false;
				while (m_stateManager.hasCurrentState())
				{
					m_graphicsManager.processEvents();
					m_audioManager.update(frameTime);
					if (m_paused == false)
						m_stateManager.update(frameTime, guiView);
					m_console.update(frameTime, guiView);
					m_fpsCounter.update(frameTime);
					if (m_fpsDisplayer)
						m_fpsDisplayer->update(guiView);
					drawAll();
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
				m_screenshotRender->setView(m_camera.getView());
				m_stateManager.draw(*m_screenshotRender);
				m_screenshotRender->setView(m_camera.getGuiView());
				if (captureConsole)
					m_console.draw(*m_screenshotRender);
				m_screenshotRender->display();
				image = std::move(m_screenshotRender->getTexture().copyToImage());
				image.saveToFile(path);
				return (path);
			}

			std::unique_ptr<sf::RenderTexture>	m_screenshotRender;
			std::unique_ptr<FpsDisplayer>		m_fpsDisplayer;
			StateManager						m_stateManager;
			GraphicsManager						m_graphicsManager;
			ResourceManager						m_resourceManager;
			AudioManager						m_audioManager;
			Options								m_options;
			Console								m_console;
			FpsCounter							m_fpsCounter;
			Camera								m_camera;
			PausableClock						m_clock;
			sf::Event							m_event;
			bool								m_paused;
		};
	}
}

#endif
