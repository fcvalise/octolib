/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PostEffectManager.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/10 14:42:29 by irabeson          #+#    #+#             */
/*   Updated: 2015/08/16 16:51:21 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POSTEFFECTMANAGER_HPP
# define POSTEFFECTMANAGER_HPP
# include "PostEffect.hpp"

# include <SFML/Graphics/RenderTexture.hpp>
# include <SFML/Graphics/RenderStates.hpp>
# include <SFML/Graphics/Shader.hpp>
# include <SFML/Graphics/Sprite.hpp>
# include <SFML/Window/VideoMode.hpp>

# include <map>
# include <memory>

namespace octo
{
	class PostEffect;

	class PostEffectManager
	{
	public:
		PostEffectManager();

		void				createRender(sf::VideoMode const& videoMode);
		void				draw(sf::Drawable const& drawable, sf::RenderStates const& states);
		void				draw(sf::Vertex const* vertices, unsigned int count,
								 sf::PrimitiveType type, sf::RenderStates const& states);
		sf::RenderTarget&	getRender();
		void				setView(sf::View const& view);
		void				display(sf::RenderTarget& render);

		std::size_t			addEffect(PostEffect&& effect);
		void				removeEffect(std::size_t index);
		void				removeEffects();
		void				enableEffect(std::size_t index, bool enable);

		PostEffect&			getEffect(std::size_t index);
		PostEffect const&	getEffect(std::size_t index)const;
		std::size_t			getEffectCount()const;
		bool				hasEnabledEffects()const;
		void				setAllShaderEnabled(bool isAllShaderEnable);
	private:
		void				applyEffects(sf::Sprite& sprite);
	private:
		typedef std::map<std::size_t, std::unique_ptr<PostEffect>>	EffectMap;

		sf::RenderTexture	m_firstRender;
		sf::RenderTexture	m_secondRender;
		EffectMap			m_effects;
		std::size_t			m_enabledCount;
		bool				m_allShaderEnabled;
	};
}

#endif
