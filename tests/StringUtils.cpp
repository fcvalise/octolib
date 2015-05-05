/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 21:34:04 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/06 00:27:48 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>

#include <StringUtils.hpp>

BOOST_AUTO_TEST_SUITE( string_utils )

BOOST_AUTO_TEST_CASE( splits_0 )
{
	std::string					str = "";
	std::vector<std::string>	lines;
	std::vector<std::string>	expected =
	{
	};

	octo::splits(str, '\n', lines);
	BOOST_CHECK_EQUAL_COLLECTIONS(lines.begin(), lines.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE( splits_1 )
{
	std::string					str = "hello\n\nyop\nbob\nboba feet\nlachez moi";
	std::vector<std::string>	lines;
	std::vector<std::string>	expected =
	{
		"hello",
		"yop",
		"bob",
		"boba feet",
		"lachez moi"
	};

	octo::splits(str, '\n', lines);
	BOOST_CHECK_EQUAL_COLLECTIONS(lines.begin(), lines.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE( splits_2 )
{
	std::string					str = "\nhalala \n\n\nmwe\nmiam roulala\n";
	std::vector<std::string>	lines;
	std::vector<std::string>	expected =
	{
		"halala ",
		"mwe",
		"miam roulala"
	};

	octo::splits(str, '\n', lines);
	BOOST_CHECK_EQUAL_COLLECTIONS(lines.begin(), lines.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE( splits_3 )
{
	std::string					str = "\n\n\n";
	std::vector<std::string>	lines;
	std::vector<std::string>	expected =
	{
	};

	octo::splits(str, '\n', lines);
	BOOST_CHECK_EQUAL_COLLECTIONS(lines.begin(), lines.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE( splits_4 )
{
	std::string					str = "\nhalala \n\n\nmwe\nmiam roulala\n\n\n";
	std::vector<std::string>	lines;
	std::vector<std::string>	expected =
	{
		"halala ",
		"mwe",
		"miam roulala"
	};

	octo::splits(str, '\n', lines);
	BOOST_CHECK_EQUAL_COLLECTIONS(lines.begin(), lines.end(), expected.begin(), expected.end());
}
BOOST_AUTO_TEST_SUITE_END()
