/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OptionParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/24 02:28:56 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/02 14:31:10 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONPARSER_HPP
# define OPTIONPARSER_HPP
# include <string>

namespace octo
{
	/*!	\ingroup Core
	 *	\brief Option parser
	 */
	class OptionParser
	{
	public:
		static bool	parseLine(std::string const& line, std::string& key, std::string& value);
	};
}

#endif
