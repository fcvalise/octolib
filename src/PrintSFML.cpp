/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrintSFML.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/13 12:28:43 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/20 18:05:39 by irabeson         ###   ########.fr       */
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
			os << static_cast<int>(value.r) << ";" <<
				  static_cast<int>(value.g) << ";" <<
				  static_cast<int>(value.b) << ";" <<
				  static_cast<int>(value.a);
		}
		return (os);
	}

	std::istream&	operator >> (std::istream& is, sf::Color& value)
	{
		typename std::istream::sentry	init(is);
		int								r = 0;
		int								g = 0;
		int								b = 0;
		int								a = 0;

		if (init)
		{
			is >> r >> ExpectChar(';') >> g >> ExpectChar(';') >> b >> ExpectChar(';') >> a;
			value.r = r;
			value.g = g;
			value.b = b;
			value.a = a;
		}
		return (is);
	}
}
