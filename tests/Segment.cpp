/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 14:16:19 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/14 01:14:56 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>
#include <Segment.hpp>

BOOST_TEST_DONT_PRINT_LOG_VALUE( sf::Vector2f );

BOOST_AUTO_TEST_SUITE( segments )

BOOST_AUTO_TEST_CASE( setter_getter )
{
	octo::Segment	s;

	BOOST_CHECK_EQUAL(s.p0(), sf::Vector2f());
	BOOST_CHECK_EQUAL(s.p1(), sf::Vector2f());
	s = octo::Segment(sf::Vector2f(1.f, 2.f), sf::Vector2f(3.f, 4.f));
	BOOST_CHECK_EQUAL(s.p0().x, 1.f);
	BOOST_CHECK_EQUAL(s.p0().y, 2.f);
	BOOST_CHECK_EQUAL(s.p1().x, 3.f);
	BOOST_CHECK_EQUAL(s.p1().y, 4.f);
}

BOOST_AUTO_TEST_CASE( parametric )
{
	octo::Segment s = octo::Segment(sf::Vector2f(1.f, 2.f), sf::Vector2f(3.f, 4.f));

	BOOST_CHECK_EQUAL(s.parametric(0.f), sf::Vector2f(1.f, 2.f));
	BOOST_CHECK_EQUAL(s.parametric(0.5f), sf::Vector2f(2.f, 3.f));
	BOOST_CHECK_EQUAL(s.parametric(1.f), sf::Vector2f(3.f, 4.f));
}

BOOST_AUTO_TEST_CASE( location )
{
	octo::Segment s = octo::Segment(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 1.f));

	BOOST_CHECK(s.location(sf::Vector2f(-1.f, 0.f)) < 0.f); 
	BOOST_CHECK(s.location(sf::Vector2f(1.f, 0.f)) > 0.f); 
	BOOST_CHECK_EQUAL(s.location(sf::Vector2f(0.f, 0.f)), 0.f); 
}

BOOST_AUTO_TEST_CASE( parallel )
{
	octo::Segment	s0(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 1.f));
	octo::Segment	s1(sf::Vector2f(0.f, 1.f), sf::Vector2f(0.f, 0.f));
	octo::Segment	s2(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 0.f));
	octo::Segment	s3(sf::Vector2f(1.f, 0.f), sf::Vector2f(0.f, 0.f));

	BOOST_CHECK(octo::Segment::areParallel(s0, s0));
	BOOST_CHECK(octo::Segment::areParallel(s0, s1));
	BOOST_CHECK(octo::Segment::areParallel(s2, s2));
	BOOST_CHECK(octo::Segment::areParallel(s2, s3));
	BOOST_CHECK(octo::Segment::areParallel(s0, s2) == false);
	BOOST_CHECK(octo::Segment::areParallel(s1, s2) == false);
}

BOOST_AUTO_TEST_CASE( aligned0 )
{
	octo::Segment s0 = octo::Segment(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 1.f));
	octo::Segment s1 = octo::Segment(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 1.f));
	octo::Segment s2 = octo::Segment(sf::Vector2f(0.f, 4.f), sf::Vector2f(0.f, 1.f));
	octo::Segment s3 = octo::Segment(sf::Vector2f(0.f, 1.f), sf::Vector2f(0.f, 4.f));
	octo::Segment s4 = octo::Segment(sf::Vector2f(0.01f, 0.f), sf::Vector2f(0.f, 1.f));
	octo::Segment s5 = octo::Segment(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 0.f));
	octo::Segment s6 = octo::Segment(sf::Vector2f(1.f, 0.f), sf::Vector2f(0.f, 1.f));
	octo::Segment s7 = octo::Segment(sf::Vector2f(1.f, 1.f), sf::Vector2f(1.f, 2.f));

	BOOST_CHECK(octo::Segment::areAligned(s0, s1));
	BOOST_CHECK(octo::Segment::areAligned(s0, s2));
	BOOST_CHECK(octo::Segment::areAligned(s0, s3));
	BOOST_CHECK(octo::Segment::areAligned(s0, s4) == false);
	BOOST_CHECK(octo::Segment::areAligned(s0, s5) == false);
	BOOST_CHECK(octo::Segment::areAligned(s0, s6) == false);
	BOOST_CHECK(octo::Segment::areAligned(s0, s7) == false);
}

BOOST_AUTO_TEST_CASE( io )
{
	octo::Segment		orig(sf::Vector2f(123.456f, 456.123f), sf::Vector2f(789.654f, 654.789f));
	octo::Segment		readed;
	std::ostringstream	oss;
	std::istringstream	iss;

	oss << orig;
	iss.str(oss.str());
	iss >> readed;
	BOOST_CHECK_EQUAL(orig, readed);
}
BOOST_AUTO_TEST_SUITE_END()
