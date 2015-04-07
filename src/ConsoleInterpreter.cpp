/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleInterpreter.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/04 03:03:00 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/07 10:36:54 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConsoleInterpreter.hpp"
#include "ConsoleCommandParser.hpp"

namespace octo
{
	namespace details
	{
		template <>
		std::wstring	fromStringImp<std::wstring>(std::wstring const& str)
		{
			return (str);
		}

		template <>
		std::wstring	toStringImp(std::wstring const& value)
		{
			return (value);
		}
	}

	std::wstring	ConsoleInterpreter::execute(std::wstring const& line)
	{
		std::wstring				name;
		std::vector<std::wstring>	arguments;
		std::wstring				result;
		bool						ok = true;

		if (ConsoleCommandParser::parseLine(line, name, arguments))
		{
			auto	it = m_callables.find(name);
			
			if (it != m_callables.end())
			{
				result = it->second->call(arguments, ok);
			}
			else
			{
				return (L"Unknow function");
			}
			if (ok == false)
			{
				return (L"Argument error");
			}
		}
		else
		{
			return (L"Syntax error");
		}
		return (result);
	}
}
