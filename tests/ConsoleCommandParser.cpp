/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleCommandParser.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/03 09:27:15 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/04 15:51:28 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>
#include <iterator>
#include <codecvt>

#include <ConsoleCommandParser.hpp>

namespace std
{
	std::string ws2s(const std::wstring& wstr)
	{
		typedef std::codecvt_utf8<wchar_t> convert_typeX;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.to_bytes(wstr);
	}

	std::ostream&	operator << (std::ostream& os, std::wstring const& str)
	{
		os << ws2s(str);
		return (os);
	}
}

BOOST_AUTO_TEST_SUITE( console_command_parser )

static void	testParser(std::wstring const& line,
					   std::wstring const& expectedName,
					   std::vector<std::wstring> const& expectedArguments,
					   bool expectedReturn = true)
{
	std::wstring				name;
	std::vector<std::wstring>	arguments;
	bool 						result = false;

	result = octo::ConsoleCommandParser::parseLine(line, name, arguments);
	BOOST_CHECK_EQUAL( name, expectedName );
	BOOST_CHECK_EQUAL_COLLECTIONS( expectedArguments.begin(), expectedArguments.end(),
								   arguments.begin(), arguments.end() );
	BOOST_CHECK_EQUAL ( result, expectedReturn );
}

BOOST_AUTO_TEST_CASE( simple_test )
{
	testParser(L"hello()", L"hello", {});
	testParser(L"yop()", L"yop", {});
	testParser(L" yop   (    )  ", L"yop", {});
	testParser(L" K_yop   (  shsfhsf    ,   kkkkkss  )  ", L"K_yop", {L"shsfhsf", L"kkkkkss"});
	testParser(L" yop   (  shsfhsf    ,   kkkkkss  )  ", L"yop", {L"shsfhsf", L"kkkkkss"});
	testParser(L"  yop   (shsfhsf,kkkkkss)  ", L"yop", {L"shsfhsf", L"kkkkkss"});
	testParser(L"yop(123, 456, true, hello)", L"yop", {L"123", L"456", L"true", L"hello"});
	testParser(L"  yop   (\"shsfhsf\",kkkkkss)  ", L"yop", {L"shsfhsf", L"kkkkkss"});
	testParser(L"hello(90, 87)", L"hello", {L"90", L"87"});
	testParser(L"hello(\"90, 87\")", L"hello", {L"90, 87"});
}

BOOST_AUTO_TEST_CASE( error_test )
{
	testParser(L"  yop   (,\"shsfhsf\",kkkkkss)  ", L"", {}, false);
	testParser(L" 7575 yop   (,\"shsfhsf\",kkkkkss)  ", L"", {}, false);
	testParser(L" (,\"shsfhsf\",kkkkkss)  ", L"", {}, false);
	testParser(L"r r (,\"shsfhsf\",kkkkkss)  ", L"", {}, false);
}

BOOST_AUTO_TEST_SUITE_END()
