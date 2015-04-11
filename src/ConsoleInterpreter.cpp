/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleInterpreter.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/04 03:03:00 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/11 11:41:07 by irabeson         ###   ########.fr       */
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

	//
	//	ArgumentTypeException
	//
	ConsoleInterpreter::ArgumentTypeException::ArgumentTypeException(std::size_t argumentIndex) :
		m_argumentIndex(argumentIndex)
	{
	}

	std::size_t	ConsoleInterpreter::ArgumentTypeException::getArgumentIndex()const
	{
		return (m_argumentIndex);
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
}
