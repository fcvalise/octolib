/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WPrintSFML.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/14 20:04:14 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/20 18:07:50 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WPrintSFML.hpp"
#include <iostream>

namespace octo
{
	std::wostream&	operator << (std::wostream& os, sf::VideoMode const& value)
	{
		std::wostream::sentry	init(os);

		if (init)
		{
			os << value.width << L";" << value.height << L";" << value.bitsPerPixel;
		}
		return (os);
	}

	std::wistream&	operator >> (std::wistream& is, sf::VideoMode& value)
	{
		typename std::wistream::sentry init(is);

		if (init)
		{
			is >> value.width >> WExpectChar(L';') >> value.height >> WExpectChar(L';') >> value.bitsPerPixel;
		}
		return (is);
	}
	
	std::wostream&	operator << (std::wostream& os, sf::Color const& value)
	{
		std::wostream::sentry	init(os);

		if (init)
		{
			os << static_cast<int>(value.r) << L";" <<
				  static_cast<int>(value.g) << L";" <<
				  static_cast<int>(value.b) << L";" <<
				  static_cast<int>(value.a);
		}
		return (os);
	}

	std::wistream&	operator >> (std::wistream& is, sf::Color& value)
	{
		typename std::wistream::sentry	init(is);
		int								r = 0;
		int								g = 0;
		int								b = 0;
		int								a = 0;

		if (init)
		{
			is >> r >> WExpectChar(L';') >> g >> WExpectChar(L';') >> b >> WExpectChar(L';') >> a;
			value.r = r;
			value.g = g;
			value.b = b;
			value.a = a;
		}
		return (is);
	}
}
