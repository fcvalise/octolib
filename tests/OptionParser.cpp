/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OptionParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/24 02:57:14 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/24 15:24:41 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>

#include <OptionParser.hpp>

BOOST_AUTO_TEST_SUITE( option_parser )

static void	testOptionParser(std::string const& line,
							 std::string const& expectedKey,
							 std::string const& expectedValue,
							 bool expectedReturn = true)
{
	std::string	key;
	std::string	value;

	BOOST_CHECK_EQUAL(octo::OptionParser::parseLine(line, key, value), expectedReturn);
	BOOST_CHECK_EQUAL(key, expectedKey);
	BOOST_CHECK_EQUAL(value, expectedValue);
}

BOOST_AUTO_TEST_CASE( extract_key_values )
{
	testOptionParser("a=b", "a", "b");
	testOptionParser("ab=c", "ab", "c");
	testOptionParser("a=bc", "a", "bc");

	testOptionParser(" a=b", "a", "b");
	testOptionParser("a =b", "a", "b");
	testOptionParser(" a =b", "a", "b");
	testOptionParser("  a =b", "a", "b");

	testOptionParser("a= b", "a", "b");
	testOptionParser("a=b ", "a", "b");
	testOptionParser("a= b ", "a", "b");

	testOptionParser("a=b", "a", "b");
	testOptionParser("a=b ", "a", "b");
	testOptionParser("a=b  ", "a", "b");
	testOptionParser("a=b   ", "a", "b");
	testOptionParser("a= b", "a", "b");
	testOptionParser("a=  b", "a", "b");

	testOptionParser("a=b d  ", "a", "b d");
	testOptionParser("a= b d", "a", "b d");
	testOptionParser("a=  b d ", "a", "b d");
	testOptionParser("a=  b d  ", "a", "b d");

	testOptionParser("a=b c", "a", "b c");
	testOptionParser("a=b c", "a", "b c");
	testOptionParser("a=b c", "a", "b c");

	testOptionParser("a b=c", "a b", "c");
	testOptionParser(" a b=c", "a b", "c");
	testOptionParser("a b =c", "a b", "c");
	testOptionParser(" a b =c", "a b", "c");

	testOptionParser(" a=b", "a", "b");
	testOptionParser("  a=b", "a", "b");
	testOptionParser(" a =b", "a", "b");
	testOptionParser(" a  =b", "a", "b");
	testOptionParser("a =b", "a", "b");
	testOptionParser("a  =b", "a", "b");

	testOptionParser(" ac=b", "ac", "b");
	testOptionParser("  ac=b", "ac", "b");
	testOptionParser(" ac =b", "ac", "b");
	testOptionParser(" ac  =b", "ac", "b");
	testOptionParser("ac =b", "ac", "b");
	testOptionParser("ac  =b", "ac", "b");
}

BOOST_AUTO_TEST_CASE (errors)
{
	testOptionParser("", "", "", false);
	testOptionParser(" ", "", "", false);
	testOptionParser("   ", "", "", false);
	testOptionParser(" = ", "", "", false);
	testOptionParser("a=", "", "", false);
	testOptionParser("a= ", "", "", false);
	testOptionParser("=b", "", "", false);
	testOptionParser(" =b", "", "", false);
}

BOOST_AUTO_TEST_SUITE_END()
