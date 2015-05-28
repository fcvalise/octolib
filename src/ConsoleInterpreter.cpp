/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleInterpreter.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/04 03:03:00 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/27 02:45:07 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConsoleInterpreter.hpp"
#include "ConsoleCommandParser.hpp"
#include "StringUtils.hpp"

#include <algorithm>

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
		std::string		fromStringImp<std::string>(std::wstring const& str)
		{
			return (wideToString(str));
		}

		template <>
		std::wstring	toStringImp(std::wstring const& value)
		{
			return (value);
		}

		template <>
		std::wstring	toStringImp(std::string const& value)
		{
			return (stringToWide(value));
		}
	}

	//
	//	ConsoleInterpreter
	//
	std::wstring	ConsoleInterpreter::execute(std::wstring const& line)
	{
		std::wstring				name;
		std::vector<std::wstring>	arguments;
		std::wstring				result;
		
		ConsoleCommandParser::parseLine(line, name, arguments);

		auto	it = m_callables.find(name);
		if (it != m_callables.end())
		{
			result = it->second->call(arguments);
		}
		else
		{
			throw UnknowCommandException(name);
		}
		return (result);
	}
	
	std::vector<std::wstring>	ConsoleInterpreter::getCommandList()const
	{
		std::vector<std::wstring>	commands;

		commands.reserve(m_callables.size());
		for (auto it = m_callables.begin(); it != m_callables.end(); ++it)
			commands.push_back(it->first);
		std::sort(commands.begin(), commands.end());
		return (commands);
	}

	//
	//	ArgumentTypeException
	//
	ConsoleInterpreter::ArgumentTypeException::ArgumentTypeException(std::size_t argumentIndex, std::string const& expectedTypeName) :
		m_expectedTypeName(stringToWide(expectedTypeName)),
		m_argumentIndex(argumentIndex)
	{
	}

	std::size_t	ConsoleInterpreter::ArgumentTypeException::getArgumentIndex()const
	{
		return (m_argumentIndex);
	}

	//
	//	NotEnoughArgumentException
	//
	ConsoleInterpreter::NotEnoughArgumentException::NotEnoughArgumentException(std::size_t expected, std::size_t provided) :
		m_expected(expected),
		m_provided(provided)
	{
	}

	std::size_t	ConsoleInterpreter::NotEnoughArgumentException::getExpected()const
	{
		return (m_expected);
	}

	std::size_t	ConsoleInterpreter::NotEnoughArgumentException::getProvided()const
	{
		return (m_provided);
	}

	//
	//	TooManyArgumentException
	//
	ConsoleInterpreter::TooManyArgumentException::TooManyArgumentException(std::size_t expected, std::size_t provided) :
		m_expected(expected),
		m_provided(provided)
	{
	}

	std::size_t	ConsoleInterpreter::TooManyArgumentException::getExpected()const
	{
		return (m_expected);
	}

	std::size_t	ConsoleInterpreter::TooManyArgumentException::getProvided()const
	{
		return (m_provided);
	}
	//
	//	UnknowCommandException
	//
	ConsoleInterpreter::UnknowCommandException::UnknowCommandException(std::wstring const& commandName) :
		m_commandName(commandName)
	{
	}

	std::wstring const& ConsoleInterpreter::UnknowCommandException::getCommandName()const
	{
		return (m_commandName);
	}

	//
	//	SyntaxErrorException
	//
	ConsoleInterpreter::SyntaxErrorException::SyntaxErrorException(std::wstring const& description, std::size_t pos) :
		m_description(description),
		m_pos(pos)
	{
	}

	std::wstring const&	ConsoleInterpreter::SyntaxErrorException::getDescription()const
	{
		return (m_description);
	}

	std::size_t		ConsoleInterpreter::SyntaxErrorException::getPosition()const
	{
		return (m_pos);
	}
}
