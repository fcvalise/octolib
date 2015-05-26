/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 20:51:41 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/26 15:41:17 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Application.hpp"
#include "PausableClock.hpp"
#include "GraphicsManager.hpp"
#include "ResourceManager.hpp"
#include "AudioManager.hpp"
#include "Palette.hpp"
#include "ColorWheel.hpp"
#include "SpriteSheet.hpp"
#include "SpriteAnimation.hpp"
#include "Options.hpp"
#include "Console.hpp"
#include "PrintSFML.hpp"
#include "StringUtils.hpp"
#include "FpsCounter.hpp"
#include "FpsDisplayer.hpp"
#include "Camera.hpp"

#include "details/ApplicationImp.hpp"

#include <SFML/Graphics/RenderTexture.hpp>

#include <cassert>
#include <chrono>

namespace octo
{
	details::ApplicationImp*	Application::s_instance = nullptr;

	void	Application::initialize(std::string const& title, std::string const& optionFilePath, int argc, char **argv)
	{
		assert (s_instance == nullptr);

		s_instance = new details::ApplicationImp;
		s_instance->setupOptions(optionFilePath, argc, argv);
		s_instance->setupGraphics(title);
		s_instance->setupAudio();
		s_instance->setupResources();
		s_instance->setupConsole();
		s_instance->setupFpsCounter();
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

	AudioManager&	Application::getAudioManager()
	{
		assert (s_instance != nullptr);

		return (s_instance->m_audioManager);
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
	
	Camera&		Application::getCamera()
	{
		assert (s_instance != nullptr);

		return (s_instance->m_camera);
	}
}
