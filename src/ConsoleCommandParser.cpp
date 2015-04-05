/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleCommandParser.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 14:34:12 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/04 15:23:21 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConsoleCommandParser.hpp"
#include <locale>
#include <iostream> // test
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

		std::wstring::const_iterator	parseCommandName(std::wstring::const_iterator it,
														 std::wstring::const_iterator end,
														 std::wstring& result)
		{
			auto	begin = it;

			if (it == end)
				return (it);
			while (it != end && std::find(Symbols.begin(), Symbols.end(), *it) != Symbols.end())
				++it;
			if (begin != end && it != end)
				result.assign(begin, it);
			return (it);
		}

		std::wstring::const_iterator	parseArguments(std::wstring::const_iterator it,
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
						return (end);
						// Error
					}
					++it;
					it = skipSpaces(it, end);
				}
				else
					break;
			}
			return (it);
		}
	}

	bool	ConsoleCommandParser::parseLine(std::wstring const& line,
						  					std::wstring& name,
						  					std::vector<std::wstring>& arguments)
	{
		auto	it = line.begin();
		auto	end = line.end();

		it = skipSpaces(it, end);
		it = parseCommandName(it, end, name);
		it = skipSpaces(it, end);
		if (checkParamIn(it, end) == false)
		{
			name.clear();
			arguments.clear();
			return (false);
		}
		it = skipSpaces(it, end);
		it = parseArguments(it, end, arguments);
		it = skipSpaces(it, end);
		if (checkParamOut(it, end) == false)
		{
			name.clear();
			arguments.clear();
			return (false);
		}
		return (true);
	}
}
