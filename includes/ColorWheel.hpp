/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ColorWheel.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/30 01:22:37 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/30 02:37:29 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORWHEEL_HPP
# define COLORWHEEL_HPP
# include <memory>
# include <initializer_list>

# include <SFML/Graphics/Color.hpp>

# include "IColorProvider.hpp"
# include "ByteArray.hpp"
# include "Hsv.hpp"

namespace octo
{
	/*!
	 *	\ingroup Colors
	 *	\class ColorWheel
	 *	\brief Store a set of hue offset and a color base
	 *
	 *	This class define a set of color from a base color and a set of hue offsets.<br>
	 *	Each color is computed by adding hue offset to hue component of the base color.
	 */
	class ColorWheel : public IColorProvider
	{
	public:
		/*!	Create an empty color wheel */
		ColorWheel();

		/*!	Create a color wheel by defining a color and a set of hue offsets */
		ColorWheel(Hsv const& base, std::initializer_list<std::int16_t> offsets);

		/*!	Set the base color */
		void				setBaseColor(Hsv const& color);

		/*!	Compute a color */
		virtual sf::Color	getColor(std::size_t id)const;

		/*!	Get the color count */
		virtual std::size_t	getColorCount()const;

		virtual bool		loadFromMemory(ByteArray const& buffer);
		virtual bool		saveToMemory(ByteArray& buffer)const;
	private:
		void				resize(std::size_t count);
	private:
		Hsv								m_colorBase;
		std::unique_ptr<std::int16_t[]>	m_offsets;
		std::size_t						m_offsetCount;
	};
}

#endif
