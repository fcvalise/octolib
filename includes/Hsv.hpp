/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hsv.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/19 20:40:25 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/30 04:50:34 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HSV_HPP
# define HSV_HPP
# include <cstdint>
# include <SFML/Graphics/Color.hpp>

namespace octo
{
	/*!
	 *	\ingroup Graphics
	 *	\class Hsv
	 *	Color stored as HSV format
	 *
	 *	Alpha channel is also stored. <br>
	 *	0 <= H <= 359<br>
	 *	0 <= S <= 255<br>
	 *	0 <= V <= 255<br>
	 *	0 <= A <= 255<br>
	 *	\see Hsv
	 */
	class Hsv
	{
	public:
		Hsv();
		Hsv(std::uint16_t hue, std::uint8_t saturation, std::uint8_t value, std::uint8_t alpha = 255u);
		Hsv(Hsv const&) = default;
		Hsv(Hsv&&) = default;
		Hsv& 				operator = (Hsv const&) = default;
		Hsv&				operator = (Hsv&&) = default;

		std::uint16_t		getHue()const;
		std::uint8_t		getSaturation()const;
		std::uint8_t		getValue()const;
		std::uint8_t		getAlpha()const;

		void				setHue(std::uint16_t hue);
		void				setSaturation(std::uint8_t saturation);
		void				setValue(std::uint8_t value);
		void				setAlpha(std::uint8_t alpha);

		std::uint16_t&		hue();
		std::uint8_t&		saturation();
		std::uint8_t&		value();
		std::uint8_t&		alpha();

		/*!	Convert to RGBA color format */
		sf::Color			toRgba()const;
	private:
		std::uint16_t	m_hue;
		std::uint8_t	m_saturation;
		std::uint8_t	m_value;
		std::uint8_t	m_alpha;
	};
}

#endif
