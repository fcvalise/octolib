/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OneColor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/21 22:29:26 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/22 17:42:10 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ONECOLOR_HPP
# define ONECOLOR_HPP
# include "IColorProvider.hpp"

namespace octo
{
	/*!	\ingroup Graphics
	 *	\class OneColor
	 *	\brief Provider which can gives only one color
	 */
	class OneColor : public IColorProvider
	{
	public:
		explicit OneColor(sf::Color const& color);

		void				setColor(sf::Color const& color);
		virtual sf::Color	getColor(std::size_t id)const;
		virtual std::size_t	getColorCount()const;
	private:
		sf::Color	m_color;
	};
}

#endif
