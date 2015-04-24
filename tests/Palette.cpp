/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Palette.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/24 17:35:37 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/24 17:42:01 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>

#include <ByteArray.hpp>
#include <Palette.hpp>

BOOST_AUTO_TEST_SUITE( palette )

BOOST_AUTO_TEST_CASE( io )
{
	octo::Palette		pI{{sf::Color::Black, sf::Color::Red, sf::Color::Blue}};
	octo::Palette		pO;
	octo::ByteArray		buffer;

	pI.saveToMemory(buffer);
	pO.loadFromMemory(buffer);
	BOOST_CHECK_EQUAL( pI.getColorCount(), pO.getColorCount() );
	BOOST_CHECK( pI.getColor(0u) == pO.getColor(0u) );
	BOOST_CHECK( pI.getColor(1u) == pO.getColor(1u) );
	BOOST_CHECK( pI.getColor(2u) == pO.getColor(2u) );
}

BOOST_AUTO_TEST_SUITE_END()
