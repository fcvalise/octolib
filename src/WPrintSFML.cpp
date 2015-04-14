/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WPrintSFML.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/14 20:04:14 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/14 20:09:35 by irabeson         ###   ########.fr       */
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
			os << (int)value.r << L";" << (int)value.g << L";" << (int)value.b << L";" << (int)value.a;
		}
		return (os);
	}

	std::wistream&	operator >> (std::wistream& is, sf::Color& value)
	{
		typename std::wistream::sentry init(is);
		int			r;
		int			g;
		int			b;
		int			a;

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
