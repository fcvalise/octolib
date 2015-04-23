/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IColorProvider.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/21 23:38:32 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/22 21:52:34 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICOLORPROVIDER_HPP
# define ICOLORPROVIDER_HPP

# include <SFML/Graphics/Color.hpp>

namespace octo
{
	class ByteArray;

	/*!	Abstract of a provider of color
	 *
	 *	Each color provider can get colors mapped to an unique id.
	 */
	class IColorProvider
	{
	public:
		virtual ~IColorProvider() = default;

		virtual sf::Color	getColor(std::size_t id)const = 0;
		virtual std::size_t	getColorCount()const = 0;
		virtual bool		loadFromMemory(ByteArray const& buffer) = 0;
		virtual bool		saveToMemory(ByteArray& buffer)const = 0;
	};
}

#endif
