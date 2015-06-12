/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WPrintSFML.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/14 20:03:10 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/12 10:17:34 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WPRINTSFML_HPP
# define WPRINTSFML_HPP
# include "ExpectChar.hpp"

# include <iostream>

# include <SFML/System/Vector2.hpp>
# include <SFML/System/Vector3.hpp>
# include <SFML/System/Time.hpp>
# include <SFML/Window/VideoMode.hpp>
# include <SFML/Graphics/Color.hpp>
# include <SFML/Graphics/Rect.hpp>

namespace octo
{
	//
	//	sf::Vector2<T>
	//
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

	//
	//	sf::Vector3<T>
	//
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

	//
	//	sf::Rect<T>
	//
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

	//
	//	sf::VideoMode
	//
	std::wostream&	operator << (std::wostream& os, sf::VideoMode const& value);
	std::wistream&	operator >> (std::wistream& is, sf::VideoMode& value);

	//
	//	sf::Color
	//
	std::wostream&	operator << (std::wostream& os, sf::Color const& value);
	std::wistream&	operator >> (std::wistream& is, sf::Color& value);

	//
	//	sf::Time
	//
	std::wostream&	operator << (std::wostream& os, sf::Time value);
	std::wistream&	operator >> (std::wistream& is, sf::Time& value);
}

#endif
