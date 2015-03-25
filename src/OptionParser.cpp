/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OptionParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/24 02:29:58 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/25 04:31:35 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OptionParser.hpp"
#include <iostream>

namespace octo
{
	bool	OptionParser::parseLine(std::string const& line,
									std::string& key,
									std::string& value)
	{
		std::string::size_type  assignPos = line.find_first_of('=');
		std::string::size_type	keyStartPos = (assignPos == std::string::npos) ?
			0 : line.find_first_not_of(" \t\v\f\r\n", 0, assignPos);
		std::string::size_type	keyEndPos = (keyStartPos == std::string::npos) ?
			std::string::npos : line.find_last_not_of(" \t\v\f\r\n", assignPos - 1, assignPos);
		std::string::size_type	valueStartPos = (assignPos == std::string::npos) ?
			std::string::npos : line.find_first_not_of(" \t\v\f\r\n", assignPos + 1);
		std::string::size_type	valueEndPos = (valueStartPos == std::string::npos) ?
			std::string::npos : line.find_last_not_of(" \t\v\f\r\n", line.size(), (line.size() - valueStartPos) + 1);

		if (assignPos == 0)
		{
			std::cerr << "options: parser: unexpected '='" << std::endl;
			return (false);
		}
		else if (assignPos == std::string::npos)
		{
			std::cerr << "options: parser: no value defined" << std::endl;
			return (false);
		}
		if (keyStartPos == assignPos)
		{
			std::cerr << "options: parser: no key defined" << std::endl;
			return (false);
		}
		if (assignPos + 1 == line.size())
		{
			std::cerr << "options: parser: no value defined" << std::endl;
			return (false);
		}
		if (valueEndPos == std::string::npos || valueEndPos == assignPos)
		{
			std::cerr << "options: parser: no value defined" << std::endl;
			return (false);
		}
		key = line.substr(keyStartPos, (keyEndPos - keyStartPos) + 1);
		value = line.substr(valueStartPos, (valueEndPos - valueStartPos) + 1);
		return (true);
	}
}
