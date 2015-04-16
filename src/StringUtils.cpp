/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/16 18:09:44 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/16 18:10:15 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StringUtils.hpp"

#include <codecvt>

namespace octo
{
	std::wstring	stringToWide(std::string const& str)
	{
		static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>	converter;

		return (converter.from_bytes(str));
	}
}
