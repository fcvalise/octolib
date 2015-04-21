/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringUtils.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/16 18:09:01 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/21 17:26:35 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGUTILS_HPP
# define STRINGUTILS_HPP
# include <string>

namespace octo
{
	std::wstring	stringToWide(std::string const& str);
	std::string		wideToString(std::wstring const& str);
}

#endif
