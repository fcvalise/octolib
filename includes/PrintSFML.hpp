/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrintSFML.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 01:06:49 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/14 04:24:51 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTSFML_HPP
# define PRINTSFML_HPP
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
	std::ostream&	operator << (std::ostream& os, sf::Vector2<T> const& value)
	{
		std::ostream::sentry	init(os);

		if (init)
		{
			os << value.x << ";" << value.y;
		}
		return (os);
	}

	template <class T>
	std::istream&	operator >> (std::istream& is, sf::Vector2<T>& value)
	{
		typename std::istream::sentry init(is);

		if (init)
		{
			is >> value.x >> octo::ExpectChar(';') >> value.y;
		}
		return (is);
	}

	template <class T>
	std::ostream&	operator << (std::ostream& os, sf::Vector3<T> const& value)
	{
		std::ostream::sentry	init(os);

		if (init)
		{
			os << value.x << ";" << value.y << ";" << value.z;
		}
		return (os);
	}

	template <class T>
	std::istream&	operator >> (std::istream& is, sf::Vector3<T>& value)
	{
		typename std::istream::sentry init(is);

		if (init)
		{
			is >> value.x >> ExpectChar(';') >> value.y >> ExpectChar(';') >> value.z;
		}
		return (is);
	}
	template <class T>
	std::ostream&	operator << (std::ostream& os, sf::Rect<T> const& value)
	{
		std::ostream::sentry	init(os);

		if (init)
		{
			os << value.top << ";" << value.left << ";" << value.width << ";" << value.height;
		}
		return (os);
	}

	template <class T>
	std::istream&	operator >> (std::istream& is, sf::Rect<T>& value)
	{
		typename std::istream::sentry init(is);

		if (init)
		{
			is >> value.top >> ExpectChar(';') >> value.left >> ExpectChar(';') >> value.width >> ExpectChar(';') >> value.height;
		}
		return (is);
	}

	std::ostream&	operator << (std::ostream& os, sf::VideoMode const& value);
	std::istream&	operator >> (std::istream& is, sf::VideoMode& value);

	std::ostream&	operator << (std::ostream& os, sf::Color const& value);
	std::istream&	operator >> (std::istream& is, sf::Color& value);
}

#endif
