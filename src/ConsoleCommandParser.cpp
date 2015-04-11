/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleCommandParser.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 14:34:12 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/10 19:31:40 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConsoleCommandParser.hpp"
#include "ConsoleInterpreter.hpp"

#include <locale>

namespace octo
{
	namespace
	{
		static std::locale			s_locale;
		static std::wstring const	Spaces = L" \t\f\v\n";
		static std::wstring const	Symbols = L"abcdefghijklmnopqrstuvwxyz"
											  L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
											  L"_";
		static constexpr wchar_t const		ArgumentIn = L'(';
		static constexpr wchar_t const		ArgumentOut = L')';
		static constexpr wchar_t const		ArgumentSeparator = L',';

		bool							isArgumentChar(wchar_t c)
		{
			return (std::isalpha(c, s_locale) || std::isdigit(c, s_locale) ||
					c == L'_' || c == L'.');
		}

		std::wstring::const_iterator	skipSpaces(std::wstring::const_iterator it,
												   std::wstring::const_iterator end)
		{
			if (it == end)
				return (it);
			while (it != end && std::isspace(*it, s_locale))
				++it;
			return (it);
		}

		bool							checkParamIn(std::wstring::const_iterator& it,
													 std::wstring::const_iterator end)
		{
			if (it != end && *it == ArgumentIn)
			{
				++it;
				return (true);
			}
			return (false);	
		}
													
		bool							checkParamOut(std::wstring::const_iterator& it,
													  std::wstring::const_iterator end)
		{
			if (it != end && *it == ArgumentOut)
			{
				++it;
				return (true);
			}
			return (false);	
		}

		bool							parseCommandName(std::wstring::const_iterator& it,
														 std::wstring::const_iterator end,
														 std::wstring& result)
		{
			auto	begin = it;

			if (it == end)
				return (false);
			while (it != end && std::find(Symbols.begin(), Symbols.end(), *it) != Symbols.end())
				++it;
			if (begin != end && it != end)
				result.assign(begin, it);
			return (result.size() > 0);
		}

		void							parseArguments(std::wstring const& line,
													   std::wstring::const_iterator& it,
													   std::wstring::const_iterator end,
													   std::vector<std::wstring>& arguments)
		{
			auto			begin = it;

			while (it != end && *it != ArgumentOut)
			{
				it = skipSpaces(it, end);
				if (*it == L'\"')
				{
					++it;
					begin = it;
					while (it != end && *it != L'\"')
						++it;
					arguments.emplace_back(begin, it);
					++it;
				}
				else if (std::isalpha(*it, s_locale) ||
						 std::isdigit(*it, s_locale) ||
						 *it == L'_')
				{
					begin = it;
					while (it != end && isArgumentChar(*it))
						++it;
					arguments.emplace_back(begin, it);
				}
				else if (*it == ArgumentSeparator)
				{
					if (arguments.empty())
					{
						throw ConsoleInterpreter::SyntaxErrorException(L"argument expected", std::distance(line.begin(), it));
					}
					++it;
					it = skipSpaces(it, end);
				}
				else
					break;
			}
		}
	}

	void	ConsoleCommandParser::parseLine(std::wstring const& line,
						  					std::wstring& name,
						  					std::vector<std::wstring>& arguments)
	{
		auto	it = line.begin();
		auto	end = line.end();

		it = skipSpaces(it, end);
		if (parseCommandName(it, end, name) == false)
		{
			// Error: command name expected
			throw ConsoleInterpreter::SyntaxErrorException(L"command name expected", std::distance(line.begin(), it));
		}
		it = skipSpaces(it, end);
		if (checkParamIn(it, end) == false)
		{
			throw ConsoleInterpreter::SyntaxErrorException(L"argument block begin expected", std::distance(line.begin(), it));
		}
		it = skipSpaces(it, end);
		parseArguments(line, it, end, arguments);
		it = skipSpaces(it, end);
		if (checkParamOut(it, end) == false)
		{
			throw ConsoleInterpreter::SyntaxErrorException(L"argument block end expected", std::distance(line.begin(), it));
		}
	}
}
