/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PostEffect.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/16 15:40:43 by irabeson          #+#    #+#             */
/*   Updated: 2015/08/16 16:06:47 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POSTEFFECT_HPP
# define POSTEFFECT_HPP
# include <SFML/Graphics/RenderTexture.hpp>
# include <SFML/Graphics/RenderStates.hpp>
# include <SFML/Graphics/Shader.hpp>
# include <SFML/Graphics/Sprite.hpp>

namespace octo
{
	class	PostEffect
	{
	public:
		PostEffect();
		PostEffect(sf::Shader& shader, bool	enabled);
		PostEffect(sf::Shader& shader,
			   sf::BlendMode const& blendMode,
			   bool	enabled);
		virtual ~PostEffect();

		virtual void			applyEffect(sf::Sprite& sprite,
											sf::Texture const& texture,
											sf::RenderTarget& render)const;
		void					resetShader(sf::Shader* shader = nullptr);
		sf::Shader&				getShader();
		sf::Shader const&		getShader()const;
		void					setBlendMode(sf::BlendMode const& mode);
		sf::BlendMode const&	getBlendMode()const;
		void					setEnabled(bool enabled);
		bool					isEnabled()const;
	private:
		sf::Shader*		m_shader;
		sf::BlendMode	m_blendMode;
		bool			m_enabled;
	};
}

#endif
