/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IColorProvider.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/25 20:49:40 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/25 20:55:52 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IColorProvider.hpp"
#include "BinaryInputStream.hpp"
#include "BinaryOutputStream.hpp"
#include "ByteArray.hpp"
#include <fstream>

namespace octo
{
	bool	IColorProvider::loadFromFile(std::string const& fileName)
	{
		ByteArray		buffer;
		std::ifstream	file(fileName.c_str(), std::ios_base::in | std::ios_base::binary);

		if (file.is_open() == false)
			return (false);
		if (buffer.read(file) == false)
			return (false);
		if (loadFromMemory(buffer) == false)
			return (false);
		return (true);
	}

	bool	IColorProvider::saveToFile(std::string const& fileName)const
	{
		ByteArray		buffer;
		std::ofstream	file(fileName.c_str(), std::ios_base::out | std::ios_base::binary);

		if (file.is_open() == false)
			return (false);
		if (saveToMemory(buffer) == false)
			return (false);
		buffer.write(file);
		return (true);
	}
}
