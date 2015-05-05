/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FpsDisplayer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 02:33:38 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/05 19:21:49 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FPSDISPLAYER_HPP
# define FPSDISPLAYER_HPP
# include <AbstractFpsDisplayer.hpp>
# include <SFML/Graphics/Drawable.hpp>
# include <SFML/Graphics/Vertex.hpp>
# include <SFML/Graphics/Transformable.hpp>
# include <SFML/Graphics/View.hpp>
# include <SFML/Graphics/Font.hpp>
# include <SFML/Graphics/Text.hpp>

# include <memory>

namespace octo
{
	class IColorProvider;

	class FpsDisplayer : public AbstractFpsDisplayer,
						 public sf::Drawable,
						 public sf::Transformable
	{
	public:
		explicit FpsDisplayer(sf::Font const* font, unsigned int fontSize, IColorProvider const* colors, std::size_t maxSamples);

		void			setVisible(bool visible);
		void			update(sf::View const& view);
		virtual void	draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const;
	private:
		virtual void	updateDisplay(RingBuffer<unsigned int> const& samples, unsigned int maxFrameCount);
	private:
		static constexpr std::size_t const	BackgroundColor = 0;
		static constexpr std::size_t const	BarColor = 1;
		static constexpr std::size_t const	AlertBarColor = 2;

		sf::Text						m_text;
		sf::Vector2f					m_size;
		std::unique_ptr<sf::Vertex[]>	m_vertices;
		std::size_t						m_count;
		IColorProvider const*			m_colors;
		bool							m_visible;
	};
}

#endif
