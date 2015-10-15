/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ApplicationImp.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 01:22:47 by irabeson          #+#    #+#             */
/*   Updated: 2015/08/13 15:14:33 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APPLICATIONIMP_HPP
# define APPLICATIONIMP_HPP
# include <chrono>
# include <algorithm>
# include <string>
# include <cctype>

# include "PostEffectManager.hpp"

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
				std::cout << "loading " << name << " [" << (int)type << "] " << current  + 1 << "/" << total << std::endl;
			}

			virtual void	error(std::string const& message)
			{
				std::cerr << "resource loading error: " << message << std::endl;
			}

			virtual void	finished()
			{
			}
		};

		class ApplicationImp
		{
		public:
			ApplicationImp() :
				m_paused(false)
			{
			}

			void	setupPath(char **argv)
			{
				char *pos = strrchr(argv[0], '/');
				if (pos != NULL)
				   *pos = '\0';
				std::string path(argv[0]);
				path += "/";
				m_options.setValue("path", path);
			}

			void	setupOptions(std::string const& optionFilePath, int argc, char **argv)
			{
				setupPath(argv);
				m_options.load(Options::ConfigFileLoader(optionFilePath));
				m_options.load(Options::CommandLineLoader(argc, argv));
			}

			void	setupGraphics(std::string const& title)
			{
				// Adapt resolution to screenSize
				sf::VideoMode	videoMode = m_options.getValue<sf::VideoMode>("resolution", sf::VideoMode::getFullscreenModes().front());
				sf::VideoMode	fullscreen = sf::VideoMode::getFullscreenModes().front();
				videoMode.height = videoMode.width * fullscreen.height / fullscreen.width;

				// Create cameraView before createRender to use the automatic resize of the view
				m_cameraView = sf::View(sf::FloatRect(0, 0, videoMode.width, videoMode.height));
				m_graphicsManager.setCamera(m_camera, m_cameraView);

				m_graphicsManager.createRender(videoMode,
											   title,
											   m_options.getValue("fullscreen", false),
											   m_options.getValue("antialiasing", 0u));
				m_graphicsManager.setVerticalSyncEnabled(m_options.getValue("vsync", true));
				m_graphicsManager.setFramerateLimit(m_options.getValue("framerate_limit", 0));
				m_postEffectManager.createRender(videoMode);
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
					m_resourceManager.loadPackage(m_options.getValue<std::string>("path") + m_options.getValue<std::string>("package"), &listener);
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
				m_console.addCommand(L"render.set_framerate_limit", m_graphicsManager, &GraphicsManager::setFramerateLimit);
				m_console.addCommand(L"render.set_antialiasing", m_graphicsManager, &GraphicsManager::setAntialiasing);
				// System commands
				m_console.addCommand(L"system.quit", [](){Application::stop();});
				m_console.addCommand(L"system.execute", m_console, &Console::run);
				m_console.addCommand(L"system.version", [](){return (Application::getOctolibVersion());});
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
				m_stateManager.pushEvent(StateManagerEvent(StateManagerEvent::Type::PopAll, "", ""));
			}

			void	drawAll()
			{
				sf::RenderTarget&	finalRender = m_graphicsManager.getRender();

				finalRender.clear();
				m_postEffectManager.setView(m_camera.getView());
				m_stateManager.draw(m_postEffectManager.getRender());
				m_postEffectManager.display(finalRender);
				finalRender.setView(m_camera.getGuiView());
				m_stateManager.drawTransition(finalRender);
				m_console.draw(finalRender);
				if (m_fpsDisplayer)
					m_fpsDisplayer->draw(finalRender);
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
			PostEffectManager					m_postEffectManager;
			ResourceManager						m_resourceManager;
			AudioManager						m_audioManager;
			Options								m_options;
			Console								m_console;
			FpsCounter							m_fpsCounter;
			Camera								m_camera;
			sf::View							m_cameraView;
			PausableClock						m_clock;
			sf::Event							m_event;
			bool								m_paused;
		};
	}
}

#endif
