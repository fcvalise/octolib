/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/16 18:09:44 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/01 16:30:13 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StringUtils.hpp"

#include <locale>

namespace octo
{
	std::wstring	stringToWide(std::string const& str)
	{
		static std::locale			s_locale;
		const std::ctype<wchar_t>&	ctfacet = std::use_facet<std::ctype<wchar_t>>(s_locale);
		std::wstring				result;

		for (char c : str)
			result.push_back(ctfacet.widen(c));
		return (result);
	}
	
	std::string		wideToString(std::wstring const& str)
	{
		static std::locale		s_locale;
		const std::ctype<char>&	ctfacet = std::use_facet<std::ctype<char>>(s_locale);
		std::string				result;

		for (wchar_t c : str)
			result.push_back(ctfacet.narrow(c, '?'));
		return (result);
	}
}
