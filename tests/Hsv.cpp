/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hsv.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/30 03:36:51 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/30 04:15:34 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <PrintSFML.hpp>
#include <boost/test/unit_test.hpp>

#include <ByteArray.hpp>
#include <Hsv.hpp>

namespace std
{
	std::ostream&	operator << (std::ostream& os, sf::Color const& color)
	{
		octo::operator << (os, color);
		return (os);
	}
}

BOOST_AUTO_TEST_SUITE( hsv )

BOOST_AUTO_TEST_CASE( convert_to_rgba )
{

	BOOST_CHECK_EQUAL( octo::Hsv(0u, 255u, 255u, 255u).toRgba(), sf::Color::Red );
	BOOST_CHECK_EQUAL( octo::Hsv(120u, 255u, 255u, 255u).toRgba(), sf::Color::Green );
	BOOST_CHECK_EQUAL( octo::Hsv(240u, 255u, 255u, 255u).toRgba(), sf::Color::Blue );
	BOOST_CHECK_EQUAL( octo::Hsv(85, 255u, 255u, 255u).toRgba(), sf::Color(148u, 255u, 0u, 255u) );
	BOOST_CHECK_EQUAL( octo::Hsv(213u, 102u, 255u, 255u).toRgba(), sf::Color(153u, 198u, 255u, 255u) );
}

BOOST_AUTO_TEST_SUITE_END()
