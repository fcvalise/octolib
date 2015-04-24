/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BinaryStream.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 06:57:46 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/24 00:14:14 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>
#include <iterator>

#include <ByteArray.hpp>
#include <BinaryInputStream.hpp>
#include <BinaryOutputStream.hpp>

BOOST_AUTO_TEST_SUITE( binary_stream )

BOOST_AUTO_TEST_CASE( totalSizeOf_test)
{
	BOOST_CHECK_EQUAL( sizeof(int), octo::details::totalSizeOf<int>() );
	BOOST_CHECK_EQUAL( (sizeof(int) + sizeof(char) + sizeof(double)), (octo::details::totalSizeOf<int, char, double>()) );
	BOOST_CHECK_EQUAL( (sizeof(int)), (octo::details::totalSizeOf<int>()) );
}

BOOST_AUTO_TEST_CASE( simple_test1 )
{
	octo::ByteArray				buffer;
	octo::BinaryOutputStream	os(buffer);
	std::uint8_t				iValueA = 255;
	std::uint8_t				oValueA = 0;
	
	os.write(iValueA);

	octo::BinaryInputStream		is(buffer);

	BOOST_CHECK( is.isOk() );
	BOOST_CHECK( is.hasDataToRead() );
	is.read(oValueA);
	BOOST_CHECK_EQUAL( oValueA, iValueA );
	BOOST_CHECK( is.isOk() );
	BOOST_CHECK( is.hasDataToRead() == false );
}

BOOST_AUTO_TEST_CASE( simple_test4 )
{
	octo::ByteArray				buffer;
	octo::BinaryOutputStream	os(buffer);
	std::uint8_t				iValueA = 255;
	std::uint16_t				iValueB = 43636;
	std::uint32_t				iValueC = 23423567;	
	std::uint64_t				iValueD = 23423454545567;
	std::uint8_t				oValueA = 0;
	std::uint16_t				oValueB = 0;
	std::uint32_t				oValueC = 0;
	std::uint64_t				oValueD = 0;
	
	os.write(iValueA, iValueB, iValueC, iValueD);

	octo::BinaryInputStream		is(buffer);

	BOOST_CHECK( is.isOk() );
	BOOST_CHECK( is.hasDataToRead() );
	is.read(oValueA, oValueB, oValueC, oValueD);
	BOOST_CHECK_EQUAL( oValueA, iValueA );
	BOOST_CHECK_EQUAL( oValueB, iValueB );
	BOOST_CHECK_EQUAL( oValueC, iValueC );
	BOOST_CHECK_EQUAL( oValueD, iValueD );
	BOOST_CHECK( is.isOk() );
	BOOST_CHECK( is.hasDataToRead() == false );
}

BOOST_AUTO_TEST_SUITE_END()
