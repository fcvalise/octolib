/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PostEffectManager.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/10 14:42:29 by irabeson          #+#    #+#             */
/*   Updated: 2015/08/11 00:08:28 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POSTEFFECTMANAGER_HPP
# define POSTEFFECTMANAGER_HPP
# include <SFML/Graphics/RenderTexture.hpp>
# include <SFML/Graphics/RenderStates.hpp>
# include <SFML/Graphics/Shader.hpp>
# include <SFML/Graphics/Sprite.hpp>
# include <SFML/Window/VideoMode.hpp>
# include <vector>

namespace octo
{
	class PostEffectManager
	{
		struct	Shader
		{
			Shader();
			Shader(sf::Shader& shader, bool enable);

			sf::Shader*	shader;
			bool		enabled;
		};
	public:
		void				createRender(sf::VideoMode const& videoMode);
		void				draw(sf::Drawable const& drawable, sf::RenderStates const& states);
		void				draw(sf::Vertex const* vertices, unsigned int count,
								 sf::PrimitiveType type, sf::RenderStates const& states);
		sf::RenderTarget&	getRender();
		void				setView(sf::View const& view);
		void				display(sf::RenderTarget& render);

		std::size_t			addShader(sf::Shader& shader, bool enabled = true);
		void				removeShader(std::size_t index);
		void				removeShaders();
		void				enableShader(std::size_t index, bool enable);
		bool				isShaderEnabled(std::size_t index)const;

		sf::Shader&			getShader(std::size_t index);
		std::size_t			getShaderCount()const;
	private:
		void				applyShaders(sf::Sprite& sprite);
	private:
		sf::RenderTexture	m_firstRender;
		sf::RenderTexture	m_secondRender;
		std::vector<Shader>	m_shaders;
	};
}

#endif