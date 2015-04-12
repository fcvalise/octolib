/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetTypeName.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 22:03:38 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/11 22:20:12 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETTYPENAME_HPP
# define GETTYPENAME_HPP
# include <string>
# include <SFML/System/String.hpp>
# include <SFML/System/Vector2.hpp>
# include <SFML/System/Vector3.hpp>
# include <SFML/Graphics/Rect.hpp>
# include <SFML/Graphics/Color.hpp>
# include <SFML/Window/VideoMode.hpp>

namespace octo
{
	namespace details
	{
		template <class T>
		struct	GetTypeName
		{
			static constexpr char const* const	Value = "unamed type";
		};

		template <> struct	GetTypeName<bool>{static constexpr char const* const	Value = "bool";};
		template <> struct	GetTypeName<char>{static constexpr char const* const	Value = "char8";};
		template <> struct	GetTypeName<char16_t>{static constexpr char const* const	Value = "char16";};
		template <> struct	GetTypeName<char32_t>{static constexpr char const* const	Value = "char32";};
		template <> struct	GetTypeName<std::int8_t>{static constexpr char const* const	Value = "int8";};
		template <> struct	GetTypeName<std::int16_t>{static constexpr char const* const	Value = "int16";};
		template <> struct	GetTypeName<std::int32_t>{static constexpr char const* const	Value = "int32";};
		template <> struct	GetTypeName<std::int64_t>{static constexpr char const* const	Value = "int64";};
		template <> struct	GetTypeName<std::uint8_t>{static constexpr char const* const	Value = "uint8";};
		template <> struct	GetTypeName<std::uint16_t>{static constexpr char const* const	Value = "uint16";};
		template <> struct	GetTypeName<std::uint32_t>{static constexpr char const* const	Value = "uint32";};
		template <> struct	GetTypeName<std::uint64_t>{static constexpr char const* const	Value = "uint64";};
		template <> struct	GetTypeName<float>{static constexpr char const* const	Value = "float";};
		template <> struct	GetTypeName<double>{static constexpr char const* const	Value = "double";};
		template <> struct	GetTypeName<long double>{static constexpr char const* const	Value = "long double";};
		template <> struct	GetTypeName<std::string>{static constexpr char const* const	Value = "std::string";};
		template <> struct	GetTypeName<std::wstring>{static constexpr char const* const	Value = "std::wstring";};
		template <> struct	GetTypeName<sf::VideoMode>{static constexpr char const* const	Value = "sf::VideoMode";};
		template <> struct	GetTypeName<sf::Color>{static constexpr char const* const	Value = "sf::Color";};
		template <> struct	GetTypeName<sf::Vector2i>{static constexpr char const* const	Value = "sf::Vector2i";};
		template <> struct	GetTypeName<sf::Vector2f>{static constexpr char const* const	Value = "sf::Vector2f";};
		template <> struct	GetTypeName<sf::Vector2u>{static constexpr char const* const	Value = "sf::Vector2u";};
		template <> struct	GetTypeName<sf::Vector3i>{static constexpr char const* const	Value = "sf::Vector3i";};
		template <> struct	GetTypeName<sf::Vector3f>{static constexpr char const* const	Value = "sf::Vector3f";};
		template <> struct	GetTypeName<sf::IntRect>{static constexpr char const* const	Value = "sf::IntRect";};
		template <> struct	GetTypeName<sf::FloatRect>{static constexpr char const* const	Value = "sf::FloatRect";};
	}
}

#endif
