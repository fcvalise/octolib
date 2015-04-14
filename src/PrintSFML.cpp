/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrintSFML.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/13 12:28:43 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/14 20:06:59 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PrintSFML.hpp"
#include <iostream>

namespace octo
{
	std::ostream&	operator << (std::ostream& os, sf::VideoMode const& value)
	{
		std::ostream::sentry	init(os);

		if (init)
		{
			os << value.width << ";" << value.height << ";" << value.bitsPerPixel;
		}
		return (os);
	}

	std::istream&	operator >> (std::istream& is, sf::VideoMode& value)
	{
		typename std::istream::sentry init(is);

		if (init)
		{
			is >> value.width >> ExpectChar(';') >> value.height >> ExpectChar(';') >> value.bitsPerPixel;
		}
		return (is);
	}
	
	std::ostream&	operator << (std::ostream& os, sf::Color const& value)
	{
		std::ostream::sentry	init(os);

		if (init)
		{
			os << value.r << ";" << value.g << ";" << value.b << ";" << value.a;
		}
		return (os);
	}

	std::istream&	operator >> (std::istream& is, sf::Color& value)
	{
		typename std::istream::sentry init(is);

		if (init)
		{
			is >> value.r >> ExpectChar(';') >> value.g >> ExpectChar(';') >> value.b >> ExpectChar(';') >> value.a;
		}
		return (is);
	}
}
