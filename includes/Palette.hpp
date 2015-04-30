/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Palette.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/19 20:39:42 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/30 04:48:41 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PALETTE_HPP
# define PALETTE_HPP
# include <memory>
# include <initializer_list>

# include <SFML/Graphics/Color.hpp>

# include "IColorProvider.hpp"
# include "ByteArray.hpp"
# include "Hsv.hpp"

namespace octo
{
	/*!
	 *	\ingroup Graphics
	 *	\class Palette
	 *	\brief Store a set of colors
	 */
	class Palette : public IColorProvider
	{
	public:
		/*!	Create an empty palette */
		explicit Palette();

		/*!	Create a palette defined by a list of color */
		explicit Palette(std::initializer_list<sf::Color> colors);
		
		virtual sf::Color	getColor(std::size_t id)const;
		virtual std::size_t	getColorCount()const;
		virtual bool		loadFromMemory(ByteArray const& buffer);
		virtual bool		saveToMemory(ByteArray& buffer)const;
	private:
		void				resize(std::size_t count);
	private:
		std::unique_ptr<sf::Color[]>	m_colors;
		std::uint64_t					m_colorCount;
	};
}

#endif
