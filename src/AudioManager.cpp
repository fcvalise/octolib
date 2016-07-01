/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AudioManager.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 02:43:03 by irabeson          #+#    #+#             */
/*   Updated: 2015/10/09 13:42:24 by jbalestr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AudioManager.hpp"
#include "Interpolations.hpp"

#include <algorithm>

#include <SFML/Audio/Sound.hpp>

#include <iostream>

namespace octo
{
	namespace
	{
		static bool	isPlaying(sf::Sound const& sound)
		{
			return (sound.getStatus() == sf::SoundSource::Playing);
		}

		struct	SortSound
		{
			bool	operator()(std::shared_ptr<sf::Sound> const& left,
							   std::shared_ptr<sf::Sound> const& right)const
			{
				if (left && right)
					return (left->getStatus() < right->getStatus());
				return (false);
			}
		};
	}

	AudioManager::Transition::Transition(SoundPtr const& newSound, SoundPtr const& oldSound, sf::Time duration, float finalVolume, sf::Time offset) :
		m_duration(duration),
		m_newSound(newSound),
		m_oldSound(oldSound),
		m_oldStartVolume(0.f),
		m_newEndVolume(finalVolume),
		m_run(true)
	{
		if (m_newSound)
		{
			m_newSound->setPlayingOffset(offset);
			m_newSound->setPitch(1.f);
			m_newSound->play();
			m_newSound->setVolume(0.f);
		}
		if (m_oldSound)
		{
			m_oldStartVolume = m_oldSound->getVolume();
		}
	}

	AudioManager::SoundPtr	AudioManager::Transition::getNewSound()const
	{
		return (m_newSound);
	}

	/*
	 *	Transition is made by fade out the volume of old sound and
	 *	in the same time fade in the volume of new sound.
	 */
	bool	AudioManager::Transition::update(sf::Time frameTime)
	{
		float	relativePos = 0.f;

		if (m_run)
		{
			m_current += frameTime;
			relativePos = std::min(m_current.asSeconds() / m_duration.asSeconds(), 1.f);
			if (m_newSound && isPlaying(*m_newSound))
				m_newSound->setVolume(linearInterpolation(0.f, m_newEndVolume, relativePos));
			if (m_oldSound && isPlaying(*m_oldSound))
				m_oldSound->setVolume(linearInterpolation(m_oldStartVolume, 0.f, relativePos));
			if (m_current >= m_duration)
			{
				m_run = false;
				if (m_oldSound)
				{
					m_oldSound->stop();
					m_oldSound->resetBuffer();
				}
			}
		}
		return (m_run);
	}

	bool	AudioManager::Transition::isRunning()const
	{
		return (m_run);
	}

	/*!
	 *	\ingroup Audio
	 *	\class AudioManager
	 *	\brief Music and sound manager
	 *
	 *
	 */

	/*!	Default constructor
	 *
	 *	Initialize volumes to 100.
	 */
	AudioManager::AudioManager() :
		m_soundVolume(100),
		m_musicVolume(100),
		m_soundEnabled(true),
		m_musicEnabled(true)
	{
	}

	/*!	Stop all sounds and release each sf::SoundBuffer used */
	AudioManager::~AudioManager()
	{
		std::for_each(m_sounds.begin(), m_sounds.end(),
					  [](SoundPtr& sound)
					  {
					  	if (sound)
						{
							sound->stop();
							sound->resetBuffer();
						}
					  });
	}

	/*!	Setup the manager
	 *	\param maxSoundCount Define the maximum count of sound playable
	 *	Define the maximum count of sound playable at the same time, including music.
	 *
	 */
	void	AudioManager::setup(std::size_t maxSoundCount)
	{
		m_sounds.resize(maxSoundCount);
		std::generate(m_sounds.begin(), m_sounds.end(), [](){return (SoundPtr(new sf::Sound()));});
	}

	/*!	Stop all sounds and release each sf::SoundBuffer used */
	void	AudioManager::reset(void)
	{
		std::for_each(m_sounds.begin(), m_sounds.end(),
					  [](SoundPtr& sound)
					  {
					  	if (sound)
						{
							sound->stop();
							sound->resetBuffer();
						}
					  });
	}

	/*!	Play one sound */
	AudioManager::SoundPtr	AudioManager::playSound(sf::SoundBuffer const& buffer, float volume,
													float pitch, sf::Vector3f const& position,
													float minimumDistance,
													float attenuation)
	{
		if (m_soundEnabled == false)
			return(nullptr);
		SoundPtr	sound = createSound(buffer);

		sound->setVolume(m_soundVolume * volume);
		sound->setPitch(pitch);
		sound->setLoop(false);
		sound->setPosition(position);
		sound->setMinDistance(minimumDistance);
		sound->setAttenuation(attenuation);
		sound->play();
		return (sound);
	}

	/*!	Play a music
	 *	\param buffer Buffer readed
	 *	\param transitionTime Time of crossfade between the old music and the new one
	 *	\param loop enable or disable loop for the new music
	 *
	 *	If transitionTime is null then the old music (if any) is immediatly stopped
	 *	and the new music starts directly at full volume.
	 */
	void	AudioManager::startMusic(sf::SoundBuffer const& buffer, sf::Time transitionTime, sf::Time offset, bool loop)
	{
		if (m_musicEnabled == false)
			return;
		SoundPtr	sound;

		sound = createSound(buffer);
		if (transitionTime == sf::Time::Zero)
		{
			sound->setPlayingOffset(offset);
			sound->setVolume(m_musicVolume);
			sound->setPitch(1.f);
			sound->setLoop(loop);
			sound->play();
			m_transition.reset();
			setMusicSound(sound);
		}
		else
		{
			m_transition.reset(new Transition(sound, getMusicSound(), transitionTime, m_musicVolume, offset));
		}
	}

	/*!	Stop the music played
	 *
	 *	\param transitionTime Time of volume fade out before music stops
	 */
	void	AudioManager::stopMusic(sf::Time transitionTime)
	{
		if (m_music == nullptr)
			return;
		if (transitionTime == sf::Time::Zero)
		{
			m_music->stop();
			m_music->resetBuffer();
			m_music.reset();
			m_transition.reset();
		}
		else
		{
			m_transition.reset(new Transition(SoundPtr(), getMusicSound(), transitionTime, m_musicVolume));
		}
	}

	/*!	Change effects track level
	 *	\param volume The new volume in the interval ]0;100[
	 */
	void	AudioManager::setSoundVolume(float volume)
	{
		if (m_soundEnabled == false)
			return;
		m_soundVolume = volume;
		for (SoundPtr& sound : m_sounds)
		{
			if (sound && sound != m_music)
			{
				sound->setVolume(sound->getVolume() * volume / 100.f);
			}
		}
	}

	/*!	Change music track level
	 *	\param volume The new volume in the interval ]0;100[
	 */
	void	AudioManager::setMusicVolume(float volume)
	{
		if (m_musicEnabled == false)
			return;
		m_musicVolume = volume;
		if (m_music)
			m_music->setVolume(volume);
	}

	/*!	Enable or disable the sounds track */
	void	AudioManager::setSoundEnabled(bool enable)
	{
		if (m_soundEnabled != enable)
		{
			m_soundEnabled = enable;
			if (m_soundEnabled == false)
			{
				std::for_each(m_sounds.begin(), m_sounds.end(),
							  [this](SoundPtr& sound)
							  {
								if (sound && sound != m_music)
								{
									sound->stop();
									sound->resetBuffer();
								}
							  });
			}	
		}
	}

	/*!	Enable or disable the music track */
	void	AudioManager::setMusicEnabled(bool enable)
	{
		if (m_musicEnabled != enable)
		{
			m_musicEnabled = enable;
			if (m_musicEnabled == false && m_music)
			{
				m_music->stop();
				m_music.reset();	
			}	
		}
	}

	float		AudioManager::getSoundVolume(void) const
	{
		return m_soundVolume;
	}

	float		AudioManager::getMusicVolume(void) const
	{
		return m_musicVolume;
	}

	bool		AudioManager::getSoundEnabled(void) const
	{
		return m_soundEnabled;
	}

	bool		AudioManager::getMusicEnabled(void) const
	{
		return m_musicEnabled;
	}

	/*!	This method must be called at each frame */
	void	AudioManager::update(sf::Time frameTime)
	{
		if (m_transition && m_transition->update(frameTime) == false)
		{
			setMusicSound(m_transition->getNewSound());
			m_transition.reset();
		}
	}

	AudioManager::SoundPtr	AudioManager::createSound(sf::SoundBuffer const& buffer)
	{
		SoundPtr	freeSound;

		//std::sort(m_sounds.begin(), m_sounds.end(), SortSound());
		std::size_t i = 0u;
		for (i = 0u; i < m_sounds.size(); i++)
		{
			if (m_sounds[i]->getStatus() == sf::SoundSource::Stopped)
			{
				freeSound = m_sounds[i];
				break;
			}
		}
		//freeSound = m_sounds.front();
		if (i > m_sounds.size())
		//if (freeSound == nullptr || isPlaying(*freeSound))
		{
			throw std::runtime_error("audio manager: not enought sounds reserved (max = " + std::to_string(m_sounds.size()) + ")");
		}
		freeSound->setBuffer(buffer);
		return (freeSound);
	}

	void	AudioManager::setMusicSound(SoundPtr const& sound)
	{
		if (m_music)
			m_music->stop();
		m_music = sound;
	}

	AudioManager::SoundPtr	AudioManager::getMusicSound()const
	{
		return (m_music);
	}
}
