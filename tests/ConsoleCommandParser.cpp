/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleCommandParser.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/03 09:27:15 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/01 16:32:53 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>
#include <iterator>

#include <ConsoleCommandParser.hpp>
#include <ConsoleInterpreter.hpp>
#include <StringUtils.hpp>

namespace std
{
	std::ostream&	operator << (std::ostream& os, std::wstring const& str)
	{
		os << octo::wideToString(str);
		return (os);
	}
}

BOOST_AUTO_TEST_SUITE( console_command_parser )

static void	testParser(std::wstring const& line,
					   std::wstring const& expectedName,
					   std::vector<std::wstring> const& expectedArguments)
{
	std::wstring				name;
	std::vector<std::wstring>	arguments;

	octo::ConsoleCommandParser::parseLine(line, name, arguments);
	BOOST_CHECK_EQUAL( name, expectedName );
	BOOST_CHECK_EQUAL_COLLECTIONS( expectedArguments.begin(), expectedArguments.end(),
								   arguments.begin(), arguments.end() );
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

BOOST_AUTO_TEST_CASE( namespace_test )
{
	testParser(L"foo.hello()", L"foo.hello", {});
	testParser(L"foo.bar.yop()", L"foo.bar.yop", {});
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
	std::wstring				name;
	std::vector<std::wstring>	arguments;

	BOOST_CHECK_THROW( octo::ConsoleCommandParser::parseLine(L"  yop   (,\"shsfhsf\",kkkkkss)  ", name, arguments), octo::ConsoleInterpreter::SyntaxErrorException );
	BOOST_CHECK_THROW( octo::ConsoleCommandParser::parseLine(L" 7575 yop   (\"shsfhsf\",kkkkkss)  ", name, arguments), octo::ConsoleInterpreter::SyntaxErrorException );
	BOOST_CHECK_THROW( octo::ConsoleCommandParser::parseLine(L" (,\"shsfhsf\",kkkkkss)  ", name, arguments), octo::ConsoleInterpreter::SyntaxErrorException );
	BOOST_CHECK_THROW( octo::ConsoleCommandParser::parseLine(L"r r (,\"shsfhsf\",kkkkkss)  ", name, arguments), octo::ConsoleInterpreter::SyntaxErrorException );
}

BOOST_AUTO_TEST_SUITE_END()
