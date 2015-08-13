/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AudioManager.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 01:20:39 by irabeson          #+#    #+#             */
/*   Updated: 2015/08/13 02:22:33 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUDIOMANAGER_HPP
# define AUDIOMANAGER_HPP
# include "AbstractTransition.hpp"

# include <memory>

# include <SFML/Audio/SoundBuffer.hpp>
# include <SFML/Audio/Sound.hpp>
# include <SFML/System/Time.hpp>

#include <iostream>

namespace octo
{
	class AudioManager
	{
	public:
		typedef std::shared_ptr<sf::Sound>	SoundPtr;
	private:
		class Transition
		{
		public:
			Transition(SoundPtr const& newSound,
					   SoundPtr const& oldSound,
					   sf::Time duration,
					   float finalVolume);

			SoundPtr	getNewSound()const;
			bool		update(sf::Time frameTime);
			bool		isRunning()const;
		private:
			sf::Time	m_duration;
			sf::Time	m_current;
			SoundPtr	m_newSound;
			SoundPtr	m_oldSound;
			float		m_oldStartVolume;
			float		m_newEndVolume;
			bool		m_run;
		};
	public:
		AudioManager();
		~AudioManager();

		void		setup(std::size_t maxSoundCount);

		/*!	Start sound playing.
		 *
		 *	\return A pointer on the new sound played, or a null pointeur if
		 *	sounds are disabled.
		 */
		SoundPtr	playSound(sf::SoundBuffer const& buffer,
							  float volume = 1.f,
							  float pitch = 1.f,
							  sf::Vector3f const& position = sf::Vector3f(),
							  float minimumDistance = 1.f,
							  float attenuation = 1.f);

		void		startMusic(sf::SoundBuffer const& buffer, sf::Time transitionTime, bool loop = false);
		void		stopMusic(sf::Time transitionTime);

		void		setSoundVolume(float volume);
		void		setMusicVolume(float volume);
		void		setSoundEnabled(bool enable);
		void		setMusicEnabled(bool enable);

		void		update(sf::Time frameTime);
	private:
		SoundPtr	createSound(sf::SoundBuffer const& buffer);
		void		setMusicSound(SoundPtr const& sound);
		SoundPtr	getMusicSound()const;
	private:
		std::unique_ptr<Transition>	m_transition;
		std::vector<SoundPtr>		m_sounds;
		SoundPtr					m_music;
		float						m_soundVolume;
		float						m_musicVolume;
		bool						m_soundEnabled;
		bool						m_musicEnabled;
	};
}

#endif
