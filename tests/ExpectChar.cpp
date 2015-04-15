/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExpectChar.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/12 22:15:28 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/12 22:28:00 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>
#include <sstream>
#include <array>

#include <ExpectChar.hpp>

BOOST_AUTO_TEST_SUITE( expect_char )

BOOST_AUTO_TEST_CASE( trivial_test )
{
	std::istringstream	iss("qwerty");

	iss >> octo::ExpectChar('q') >>
		   octo::ExpectChar('w') >>
		   octo::ExpectChar('e') >>
		   octo::ExpectChar('r') >>
		   octo::ExpectChar('t') >>
		   octo::ExpectChar('y');
	BOOST_CHECK( iss.good() );
}

BOOST_AUTO_TEST_CASE( alternance_test )
{
	std::istringstream			iss("q1w2e3r4t5y");
	std::array<int, 5>			integers;
	std::array<int, 5> const	expected{{1, 2, 3, 4, 5}};

	iss >> octo::ExpectChar('q') >>
		   integers[0] >>
		   octo::ExpectChar('w') >>
		   integers[1] >>
		   octo::ExpectChar('e') >>
		   integers[2] >>
		   octo::ExpectChar('r') >>
		   integers[3] >>
		   octo::ExpectChar('t') >>
		   integers[4] >>
		   octo::ExpectChar('y');
	BOOST_CHECK( iss.good() );
	BOOST_CHECK_EQUAL_COLLECTIONS(integers.begin(), integers.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE( simple_fail_test )
{
	std::istringstream	iss("Kwerty");

	iss >> octo::ExpectChar('q') >>
		   octo::ExpectChar('w') >>
		   octo::ExpectChar('e') >>
		   octo::ExpectChar('r') >>
		   octo::ExpectChar('t') >>
		   octo::ExpectChar('y');
	BOOST_CHECK( iss.good() == false );
}

BOOST_AUTO_TEST_CASE( alternance_fail_test )
{
	std::istringstream			iss("q1w2e3r4t5y");
	std::array<int, 5>			integers{{0, 0, 0, 0, 0}};
	std::array<int, 5> const	expected{{1, 2, 0, 0, 0}};

	iss >> octo::ExpectChar('q') >>
		   integers[0] >>
		   octo::ExpectChar('w') >>
		   integers[1] >>
		   octo::ExpectChar('K') >>
		   integers[2] >>
		   octo::ExpectChar('r') >>
		   integers[3] >>
		   octo::ExpectChar('t') >>
		   integers[4] >>
		   octo::ExpectChar('y');
	BOOST_CHECK( iss.good() == false );
	BOOST_CHECK_EQUAL_COLLECTIONS(integers.begin(), integers.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_SUITE_END()
