/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Palette.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/19 20:39:42 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/20 16:19:36 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PALETTE_HPP
# define PALETTE_HPP
# include <memory>
# include <functional>

# include "Hsv.hpp"
# include <SFML/Graphics/Color.hpp>

namespace octo
{
	class Palette
	{
	public:
		typedef std::function<Hsv(Hsv)>	Variator;

		explicit Palette(std::size_t colorCount, std::size_t variatorCount);
		
		void		set(std::size_t colorId, Hsv const& color);
		void		set(std::size_t variationId, Variator variator);

		sf::Color	get(std::size_t colorId)const;
		sf::Color	get(std::size_t colorId, std::size_t variationId)const;

		std::size_t	getColorCount()const;
		std::size_t	getVariationCount()const;
	private:
		std::unique_ptr<Hsv[]>		m_colors;
		std::unique_ptr<Variator[]>	m_variators;
		std::size_t					m_colorCount;
		std::size_t					m_variatorCount;
	};
}

#endif
