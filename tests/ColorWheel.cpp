/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ColorWheel.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/30 02:59:17 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/01 03:12:19 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>

#include <ByteArray.hpp>
#include <ColorWheel.hpp>

#include <stdexcept>

BOOST_AUTO_TEST_SUITE( color_wheel )

BOOST_AUTO_TEST_CASE( basic )
{
	octo::ColorWheel	cw0{0, {0, 120, 240}};

	BOOST_CHECK_EQUAL( cw0.getColorCount(), 3u );
	BOOST_CHECK( cw0.getColor(0u) == sf::Color::Red );
	BOOST_CHECK( cw0.getColor(1u) == sf::Color::Green );
	BOOST_CHECK( cw0.getColor(2u) == sf::Color::Blue );
}

BOOST_AUTO_TEST_CASE( errors )
{
	octo::ColorWheel	cw0{0, {0, 120, 240}};

	BOOST_CHECK_THROW( cw0.getColor(3u), std::range_error );
	BOOST_CHECK_THROW( cw0.getColor(666u), std::range_error );
}

BOOST_AUTO_TEST_CASE( io3 )
{
	octo::ColorWheel	cw0{0, {0, 120, 240}};
	octo::ColorWheel	cw1;
	octo::ByteArray		buffer;

	cw0.saveToMemory(buffer);
	cw1.loadFromMemory(buffer);
	BOOST_CHECK_EQUAL( cw0.getColorCount(), cw1.getColorCount() );
	BOOST_CHECK( cw0.getColor(0u) == cw1.getColor(0u) );
	BOOST_CHECK( cw0.getColor(1u) == cw1.getColor(1u) );
	BOOST_CHECK( cw0.getColor(2u) == cw1.getColor(2u) );
}

BOOST_AUTO_TEST_CASE( io0 )
{
	octo::ColorWheel	cw0;
	octo::ColorWheel	cw1;
	octo::ByteArray		buffer;

	cw0.saveToMemory(buffer);
	cw1.loadFromMemory(buffer);
	BOOST_CHECK_EQUAL( cw0.getColorCount(), cw1.getColorCount() );
	BOOST_CHECK_EQUAL( cw0.getColorCount(), 0u );
}

BOOST_AUTO_TEST_SUITE_END()
