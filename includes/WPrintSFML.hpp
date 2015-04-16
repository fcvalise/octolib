/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WPrintSFML.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/14 20:03:10 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/16 19:20:20 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WPRINTSFML_HPP
# define WPRINTSFML_HPP
# include "ExpectChar.hpp"

# include <iostream>

# include <SFML/System/Vector2.hpp>
# include <SFML/System/Vector3.hpp>
# include <SFML/Window/VideoMode.hpp>
# include <SFML/Graphics/Color.hpp>
# include <SFML/Graphics/Rect.hpp>

namespace octo
{
	template <class T>
	std::wostream&	operator << (std::wostream& os, sf::Vector2<T> const& value)
	{
		std::wostream::sentry	init(os);

		if (init)
		{
			os << value.x << L";" << value.y;
		}
		return (os);
	}

	template <class T>
	std::wistream&	operator >> (std::wistream& is, sf::Vector2<T>& value)
	{
		typename std::wistream::sentry init(is);

		if (init)
		{
			is >> value.x >> octo::WExpectChar(L';') >> value.y;
		}
		return (is);
	}

	template <class T>
	std::wostream&	operator << (std::wostream& os, sf::Vector3<T> const& value)
	{
		std::wostream::sentry	init(os);

		if (init)
		{
			os << value.x << L";" << value.y << L";" << value.z;
		}
		return (os);
	}

	template <class T>
	std::wistream&	operator >> (std::wistream& is, sf::Vector3<T>& value)
	{
		typename std::wistream::sentry init(is);

		if (init)
		{
			is >> value.x >> WExpectChar(L';') >> value.y >> WExpectChar(L';') >> value.z;
		}
		return (is);
	}
	template <class T>
	std::wostream&	operator << (std::wostream& os, sf::Rect<T> const& value)
	{
		std::wostream::sentry	init(os);

		if (init)
		{
			os << value.top << L";" << value.left << L";" << value.width << L";" << value.height;
		}
		return (os);
	}

	template <class T>
	std::wistream&	operator >> (std::wistream& is, sf::Rect<T>& value)
	{
		typename std::wistream::sentry init(is);

		if (init)
		{
			is >> value.top >> WExpectChar(L';') >> value.left >> WExpectChar(L';') >> value.width >> WExpectChar(L';') >> value.height;
		}
		return (is);
	}

	std::wostream&	operator << (std::wostream& os, sf::VideoMode const& value);
	std::wistream&	operator >> (std::wistream& is, sf::VideoMode& value);

	std::wostream&	operator << (std::wostream& os, sf::Color const& value);
	std::wistream&	operator >> (std::wistream& is, sf::Color& value);
}

#endif
