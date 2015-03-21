/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Math.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 01:06:48 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/21 16:51:42 by irabeson         ###   ########.fr       */
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

BOOST_AUTO_TEST_CASE( cos )
{
	BOOST_CHECK_CLOSE( (octo::Cosinus<8, float>::compute(3.14f)), std::cos(3.14f), 0.001f );
	BOOST_CHECK_CLOSE( (octo::Cosinus<9, float>::compute(3.14f)), std::cos(3.14f), 0.001f );
	BOOST_CHECK_CLOSE( (octo::Cosinus<10, float>::compute(3.14f)), std::cos(3.14f), 0.001f );
	BOOST_CHECK_CLOSE( (octo::Cosinus<11, float>::compute(3.14f)), std::cos(3.14f), 0.001f );
	BOOST_CHECK_CLOSE( (octo::Cosinus<12, float>::compute(3.14f)), std::cos(3.14f), 0.001f );
	BOOST_CHECK_CLOSE( (octo::Cosinus<13, float>::compute(3.14f)), std::cos(3.14f), 0.001f );
	BOOST_CHECK_CLOSE( (octo::Cosinus<14, float>::compute(3.14f)), std::cos(3.14f), 0.001f );
	BOOST_CHECK_CLOSE( (octo::Cosinus<15, float>::compute(3.14f)), std::cos(3.14f), 0.001f );
	BOOST_CHECK_CLOSE( (octo::Cosinus<20, float>::compute(3.14f)), std::cos(3.14f), 0.001f );

}

BOOST_AUTO_TEST_SUITE_END()
