/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrintSFML.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 01:06:49 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/24 17:03:52 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTSFML_HPP
# define PRINTSFML_HPP
#include "ExpectChar.hpp"

# include <iostream>

# include <SFML/System/Vector2.hpp>
# include <SFML/Window/VideoMode.hpp>

namespace octo
{
	template <class T, class C, class CT>
	std::basic_ostream<C, CT>&	operator << (std::basic_ostream<C, CT>& os, sf::Vector2<T> const& value)
	{
		os << "[" << value.x << ";" << value.y << "]";
		return (os);
	}

	template <class T, class C, class CT>
	std::basic_istream<C, CT>&	operator >> (std::basic_istream<C, CT>& is, sf::Vector2<T>& value)
	{
		typename std::basic_istream<C, CT>::sentry init(is);

		if (init)
		{
			is >> octo::ExpectChar('[') >> value.x >> octo::ExpectChar(';') >> value.y >> octo::ExpectChar(']');
		}
		return (is);
	}

	template <class C, class CT>
	std::basic_ostream<C, CT>&	operator << (std::basic_ostream<C, CT>& os, sf::VideoMode const& value)
	{
		os << value.width << "x" << value.height << "-" << value.bitsPerPixel;
		return (os);
	}

	template <class C, class CT>
	std::basic_istream<C, CT>	&operator >> (std::basic_istream<C, CT>& is, sf::VideoMode& value)
	{
		typename std::basic_istream<C, CT>::sentry init(is);

		if (init)
		{
			is >> value.width >> octo::ExpectChar('x') >> value.height >> octo::ExpectChar('-') >> value.bitsPerPixel;
		}
		return (is);
	}
}

#endif
