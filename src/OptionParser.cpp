/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OptionParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/24 02:29:58 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/12 16:51:24 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OptionParser.hpp"
#include <iostream>

namespace octo
{
	namespace
	{
		static char const* const	Spaces = " \t\v\f\r\n";
		static char	const			Assignation = '=';
		static char	const			Comment = '#';
	}

	OptionParser::SyntaxErrorException::SyntaxErrorException(std::string const& message) :
		m_message(message)
	{
	}

	std::string const&	OptionParser::SyntaxErrorException::what()const
	{
		return (m_message);
	}

	void	OptionParser::parseLine(std::string const& line,
									std::string& key,
									std::string& value)
	{
		std::string::size_type  assignPos = line.find_first_of(Assignation);
		std::string::size_type	keyStartPos = (assignPos == std::string::npos) ?
			0 : line.find_first_not_of(Spaces, 0, assignPos);
		std::string::size_type	keyEndPos = (keyStartPos == std::string::npos) ?
			std::string::npos : line.find_last_not_of(Spaces, assignPos - 1);
		std::string::size_type	valueStartPos = (assignPos == std::string::npos) ?
			std::string::npos : line.find_first_not_of(Spaces, assignPos + 1);
		std::string::size_type	valueEndPos = (valueStartPos == std::string::npos) ?
			std::string::npos : line.find_last_not_of(Spaces, line.size(), (line.size() - valueStartPos) + 1);
		std::string::size_type 	beginOfLine = line.find_first_not_of(Spaces);

		if (beginOfLine == std::string::npos || line[beginOfLine] == Comment)
			return;
		if (assignPos == 0)
		{
			throw SyntaxErrorException("unexpected '='");
		}
		else if (assignPos == std::string::npos)
		{
			throw SyntaxErrorException("no value defined");
		}
		if (keyStartPos == assignPos)
		{
			throw SyntaxErrorException("no key defined");
		}
		if (assignPos + 1 == line.size())
		{
			throw SyntaxErrorException("no value defined");
		}
		if (valueEndPos == std::string::npos || valueEndPos == assignPos)
		{
			throw SyntaxErrorException("no value defined");
		}
		key = line.substr(keyStartPos, (keyEndPos - keyStartPos) + 1);
		value = line.substr(valueStartPos, (valueEndPos - valueStartPos) + 1);
	}
}
