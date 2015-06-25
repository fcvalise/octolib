/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IColorProvider.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/21 23:38:32 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/21 22:34:12 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICOLORPROVIDER_HPP
# define ICOLORPROVIDER_HPP

# include <SFML/Graphics/Color.hpp>

# include <cstdlib>
# include <string>

namespace octo
{
	class ByteArray;

	/*!
	 *	\ingroup Graphics
	 *	\class IColorProvider
	 *	\brief Interface of a color provider
	 *	Abstract of a provider of color
	 *
	 *	Each color provider can get colors mapped to an unique id.<br>
	 *
	 *	\todo I/O virtual methods must be moved into a dedicated interface IResource.
	 */
	class IColorProvider
	{
	public:
		virtual ~IColorProvider() = default;

		/*!	Get a color */
		virtual sf::Color	getColor(std::size_t id)const = 0;

		/*!	Get the available color count */
		virtual std::size_t	getColorCount()const = 0;
	};
}

#endif
