/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/16 18:09:44 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/21 17:30:47 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StringUtils.hpp"

#include <codecvt>
#include <locale>

namespace octo
{
	std::wstring	stringToWide(std::string const& str)
	{
		static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>	converter;

		return (converter.from_bytes(str));
	}
	
	std::string		wideToString(std::wstring const& str)
	{
		typedef std::codecvt_utf8<wchar_t> 					ConvertType;
		typedef std::wstring_convert<ConvertType, wchar_t>	ConverterType;
		static ConverterType								Converter;

		return (Converter.to_bytes(str));
	}
}
