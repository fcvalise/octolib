/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Palette.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/19 20:39:42 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/22 21:53:59 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PALETTE_HPP
# define PALETTE_HPP
# include <memory>

# include <SFML/Graphics/Color.hpp>

# include "IColorProvider.hpp"
# include "ByteArray.hpp"
# include "Hsv.hpp"

namespace octo
{
	class Palette : public IColorProvider
	{
	public:
		explicit Palette();
		explicit Palette(std::initializer_list<sf::Color> colors);
		
		void				resize(std::size_t count);
		void				setColor(std::size_t id, sf::Color const& color);
		void				setColor(std::size_t id, Hsv const& color);
		virtual sf::Color	getColor(std::size_t id)const;
		virtual std::size_t	getColorCount()const;
		virtual bool		loadFromMemory(ByteArray const& buffer);
		virtual bool		saveToMemory(ByteArray& buffer)const;
	private:
		std::unique_ptr<sf::Color[]>	m_colors;
		std::uint64_t					m_colorCount;
	};
}

#endif
