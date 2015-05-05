/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OptionParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/24 02:57:14 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/05 16:13:17 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>

#include <OptionParser.hpp>

BOOST_AUTO_TEST_SUITE( option_parser )

static void	testOptionParser(std::string const& line,
							 std::string const& expectedKey,
							 std::string const& expectedValue)
{
	std::string	key;
	std::string	value;

	BOOST_TEST_CHECKPOINT("Parse '" << line << "'");
	octo::OptionParser::parseLine(line, key, value);
	BOOST_CHECK_EQUAL(key, expectedKey);
	BOOST_CHECK_EQUAL(value, expectedValue);
}

BOOST_AUTO_TEST_CASE( extract_key_values )
{
	testOptionParser("console_font = yop.bob", "console_font", "yop.bob");
	testOptionParser("fps_counter_palette = FpsCounter.opa", "fps_counter_palette", "FpsCounter.opa");

	testOptionParser("", "", "");
	testOptionParser(" ", "", "");
	testOptionParser("   ", "", "");

	testOptionParser("#", "", "");
	testOptionParser(" # kjhkjhkjh", "", "");

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
	std::string	key;
	std::string	value;

	BOOST_CHECK_THROW( octo::OptionParser::parseLine(" = ", key, value), octo::OptionParser::SyntaxErrorException);

	BOOST_CHECK_THROW( octo::OptionParser::parseLine("a=", key, value), octo::OptionParser::SyntaxErrorException);
	BOOST_CHECK_THROW( octo::OptionParser::parseLine("a= ", key, value), octo::OptionParser::SyntaxErrorException);

	BOOST_CHECK_THROW( octo::OptionParser::parseLine("=b", key, value), octo::OptionParser::SyntaxErrorException);
	BOOST_CHECK_THROW( octo::OptionParser::parseLine(" =b", key, value), octo::OptionParser::SyntaxErrorException);
	BOOST_CHECK_THROW( octo::OptionParser::parseLine("==b", key, value), octo::OptionParser::SyntaxErrorException);
}

BOOST_AUTO_TEST_SUITE_END()
