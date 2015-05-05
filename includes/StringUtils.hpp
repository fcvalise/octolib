/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringUtils.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/16 18:09:01 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/06 00:29:33 by irabeson         ###   ########.fr       */
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

	/*!	Splits a string with a defined delimiter
	 *
	 *	The delimiter is not stored in results.
	 *	\param str String to splits
	 *	\param delimiter Char used as delimiter
	 *	\param container Container which receives the substrings extracted
	 */
	template <class E, class C>
	void			splits(std::basic_string<E> const& str, E delimiter, C& container)
	{
		auto	eolPos = str.find_first_of(delimiter);
		auto	beginPos = 0u;
		auto	size = 0u;

		size = eolPos - beginPos;
		while (beginPos < str.size() && eolPos != std::basic_string<E>::npos)
		{
			if (size > 0u)
				container.push_back(str.substr(beginPos, size));
			beginPos = eolPos + 1u;
			eolPos = str.find_first_of(delimiter, beginPos);
			size = eolPos - beginPos;
		}
		if (beginPos < str.size())
			container.push_back(str.substr(beginPos));
	}							   
}

#endif
