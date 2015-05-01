/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringUtils.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/16 18:09:01 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/01 04:06:10 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGUTILS_HPP
# define STRINGUTILS_HPP
# include <string>

namespace octo
{
	/*!	Convert std::string to std::wstring */
	std::wstring	stringToWide(std::string const& str);

	/*!	Convert std::wstring to std::string */
	std::string		wideToString(std::wstring const& str);
}

#endif
