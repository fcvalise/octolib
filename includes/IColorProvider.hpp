/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IColorProvider.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/21 23:38:32 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/25 20:55:41 by irabeson         ###   ########.fr       */
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
		bool				loadFromFile(std::string const& fileName);
		bool				saveToFile(std::string const& fileName)const;
	};
}

#endif
