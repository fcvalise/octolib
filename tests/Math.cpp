/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Math.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 01:06:48 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/20 17:08:23 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>
#include <cmath>

#include <Math.hpp>

BOOST_AUTO_TEST_SUITE( math_meta_basic )

BOOST_AUTO_TEST_CASE( pow )
{
	BOOST_CHECK_CLOSE( (octo::pow<2>(2.f)), 4.f, std::numeric_limits<float>::epsilon() );
	BOOST_CHECK_CLOSE( (octo::pow<3>(2.f)), 8.f, std::numeric_limits<float>::epsilon() );
	BOOST_CHECK_CLOSE( (octo::pow<4>(2.f)), 16.f, std::numeric_limits<float>::epsilon() );
	BOOST_CHECK_CLOSE( (octo::pow<8>(2.f)), 256.f, std::numeric_limits<float>::epsilon() );
}

BOOST_AUTO_TEST_CASE( factorial )
{
	BOOST_CHECK( (octo::Factorial<0u, unsigned int>::Value) == 1u );
	BOOST_CHECK( (octo::Factorial<1u, unsigned int>::Value) == 1u );
	BOOST_CHECK( (octo::Factorial<2u, unsigned int>::Value) == 2u );
	BOOST_CHECK( (octo::Factorial<3u, unsigned int>::Value) == 6u );
	BOOST_CHECK( (octo::Factorial<10u, unsigned int>::Value) == 3628800u );
}

BOOST_AUTO_TEST_CASE( exponential )
{
	BOOST_CHECK_CLOSE( (octo::Exponential<10, float>::compute(1.f)), 2.71828f, 0.0001f );
}

BOOST_AUTO_TEST_CASE( power_two )
{
	BOOST_CHECK( (octo::Power2<0u>::Value == 1u) );
	BOOST_CHECK( (octo::Power2<1u>::Value == 2u) );
	BOOST_CHECK( (octo::Power2<8u>::Value == 256u) );
	BOOST_CHECK( (octo::Power2<52u>::Value == 4503599627370496u) );
}

BOOST_AUTO_TEST_CASE( cos )
{
	BOOST_CHECK_CLOSE( (octo::cos<30>(3.14f)), std::cos(3.14f), 0.0001f );
	BOOST_CHECK_CLOSE( (octo::cosHPA(3.14f)), std::cos(3.14f), 0.00001f );
	BOOST_CHECK_CLOSE( (octo::cosLPA(3.14f)), std::cos(3.14f), 0.0001f );
}

BOOST_AUTO_TEST_CASE( convert_angles_deg_to_rad )
{
	BOOST_CHECK_CLOSE( (octo::deg2Rad(0)), 0.f, 0.000001f );
	BOOST_CHECK_CLOSE( (octo::deg2Rad(90)), octo::PiDiv2, 0.000001f );
	BOOST_CHECK_CLOSE( (octo::deg2Rad(180)), octo::Pi, 0.000001f );
	BOOST_CHECK_CLOSE( (octo::deg2Rad(270)), octo::Pi + octo::PiDiv2, 0.000001f );
	BOOST_CHECK_CLOSE( (octo::deg2Rad(360)), octo::Pi2, 0.000001f );
}

BOOST_AUTO_TEST_CASE( convert_angles_rad_to_deg )
{
	BOOST_CHECK_CLOSE( (octo::rad2Deg(0)), 0.f, 0.000001f );
	BOOST_CHECK_CLOSE( (octo::rad2Deg(octo::PiDiv2)), 90.f, 0.000001f );
	BOOST_CHECK_CLOSE( (octo::rad2Deg(octo::Pi)), 180.f, 0.000001f );
	BOOST_CHECK_CLOSE( (octo::rad2Deg(octo::Pi + octo::PiDiv2)), 270.f, 0.000001f );
	BOOST_CHECK_CLOSE( (octo::rad2Deg(octo::Pi2)), 360.f, 0.000001f );
}
BOOST_AUTO_TEST_SUITE_END()
