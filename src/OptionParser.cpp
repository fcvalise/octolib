/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OptionParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/24 02:29:58 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/05 16:28:46 by irabeson         ###   ########.fr       */
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

	namespace
	{
		void								trimR(std::string& str)
		{
			while (str.empty() == false && std::isspace(str.back()))
				str.pop_back();
		}

		static bool							isComment(std::string const& line)
		{
			std::string::size_type	pos = line.find_first_not_of(Spaces);

			return (pos != std::string::npos && line[pos] == Comment);
		}

		static std::string::const_iterator	skipSpace(std::string::const_iterator it,
													  std::string::const_iterator end)
		{
			while (it != end && std::isspace(*it))
				++it;
			return (it);
		}

		static std::string::const_iterator	parseKey(std::string::const_iterator it,
													 std::string::const_iterator end,
													 std::string& key)
		{
			std::string::const_iterator	begin = it;

			while (it != end && *it != Assignation)
				++it;
			key.assign(begin, it);
			trimR(key);
			if (key.empty())
				throw OptionParser::SyntaxErrorException("no key defined");
			return (it);
		}

		static std::string::const_iterator	checkAssign(std::string::const_iterator it,
														std::string::const_iterator end)
		{
			if (it == end || *it != Assignation)
				throw OptionParser::SyntaxErrorException("expected '='");
			return (it + 1);
		}

		static std::string::const_iterator	parseValue(std::string::const_iterator it,
													   std::string::const_iterator end,
													   std::string& value)
		{
			std::string::const_iterator	begin = it;

			while (it != end)
				++it;
			value.assign(begin, it);
			trimR(value);
			if (value.empty())
				throw OptionParser::SyntaxErrorException("no value defined");
			return (it);
		}
	}
	void	OptionParser::parseLine(std::string const& line,
									std::string& key,
									std::string& value)
	{
		std::string::const_iterator	it = line.begin();
		std::string::const_iterator end = line.end();

		if (isComment(line))
			return;
		it = skipSpace(it, end);
		if (it == end)
			return;
		it = parseKey(it, end, key);
		it = skipSpace(it, end);
		it = checkAssign(it, end);
		it = skipSpace(it, end);
		it = parseValue(it, end, value);
	}
}
