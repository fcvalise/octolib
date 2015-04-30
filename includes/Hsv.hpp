/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hsv.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/19 20:40:25 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/30 03:05:27 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HSV_HPP
# define HSV_HPP
# include <SFML/Graphics/Color.hpp>

namespace octo
{
	class Hsv
	{
	public:
		Hsv();
		Hsv(int hue, float saturation, float value, float alpha = 1.f);
		Hsv(Hsv const&) = default;
		Hsv(Hsv&&) = default;
		Hsv& 		operator = (Hsv const&) = default;
		Hsv&		operator = (Hsv&&) = default;

		int			getHue()const;
		float		getSaturation()const;
		float		getValue()const;
		float		getAlpha()const;

		void		setHue(int hue);
		void		setSaturation(float saturation);
		void		setValue(float value);
		void		setAlpha(float alpha);

		int&		hue();
		float&		saturation();
		float&		value();
		float&		alpha();

		sf::Color	toRgba()const;
	private:
		int		m_hue;
		float	m_saturation;
		float	m_value;
		float	m_alpha;
	};
}

#endif
