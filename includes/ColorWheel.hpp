/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ColorWheel.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/30 01:22:37 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/02 01:33:51 by irabeson         ###   ########.fr       */
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
	 *	\ingroup Graphics
	 *	\class ColorWheel
	 *	\brief Store a set of hue offset and a color base
	 *
	 *	This class define a set of color from a base color and a set of hue offsets.<br>
	 *	Each color is computed by adding hue offset to hue component of the base color.<br>
	 *	ColorWheel can be packaged with packager.app and loaded as a resource.<br>
	 *	\see Hsv
	 *	\see ResourceManager
	 */
	class ColorWheel : public IColorProvider
	{
		struct	HueOffset
		{
			HueOffset() :
				hueOffset(0),
				saturation(0u),
				value(0u),
				alpha(0u)
			{
			}

			explicit HueOffset(std::int16_t offset, std::uint8_t saturation = 255u,
					  std::uint8_t value = 255u, std::uint8_t alpha = 255u) :
				hueOffset(offset),
				saturation(saturation),
				value(value),
				alpha(alpha)
			{
			}

			std::int16_t	hueOffset;
			std::uint8_t	saturation;
			std::uint8_t	value;
			std::uint8_t	alpha;
		};
	public:
		/*!	Create an empty color wheel */
		ColorWheel();

		/*!	Create a color wheel by defining a color and a set of hue offsets */
		ColorWheel(int hue, std::initializer_list<std::int16_t> offsets);

		/*!	Set the base hue */
		void				setBaseHue(std::uint16_t hue);

		/*!	Compute a color
		 *
		 *	\param id The index of the color, must be less than color count
		 *	\throw std::range_error if id is invalid
		 */
		virtual sf::Color	getColor(std::size_t id)const;

		/*!	Get the color count */
		virtual std::size_t	getColorCount()const;

		virtual bool		loadFromMemory(ByteArray const& buffer);
		virtual bool		saveToMemory(ByteArray& buffer)const;
	private:
		void				resize(std::size_t count);
	private:
		std::uint16_t					m_hue;
		std::unique_ptr<HueOffset[]>	m_offsets;
		std::size_t						m_offsetCount;
	};
}

#endif
