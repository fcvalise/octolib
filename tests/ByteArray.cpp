/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ByteArray.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/01 16:03:29 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/02 05:59:37 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>
#include <iterator>

#include <ByteArray.hpp>

BOOST_AUTO_TEST_SUITE( byte_array )

BOOST_AUTO_TEST_CASE( empty_test )
{
	octo::ByteArray	array0;

	BOOST_CHECK_EQUAL( array0.size(), 0u );
	BOOST_CHECK_EQUAL( array0.capacity(), 0u );
	BOOST_CHECK_EQUAL( array0.empty(), true );

	BOOST_CHECK( array0.begin() == array0.end() );
	BOOST_CHECK_EQUAL( std::distance(array0.begin(), array0.end()), 0u );
}

BOOST_AUTO_TEST_CASE( ctor_test )
{
	octo::ByteArray	array0({'a', 'b', 'c', 'd'});
	octo::ByteArray	array1(1);
	octo::ByteArray	array2(16);

	BOOST_CHECK_EQUAL( array0.size(), 4u );
	BOOST_CHECK_EQUAL( array0.capacity(), 4u );
	BOOST_CHECK_EQUAL( array0.empty(), false );
	BOOST_CHECK( array0.begin() != array0.end() );
	BOOST_CHECK_EQUAL( std::distance(array0.begin(), array0.end()), array0.size() );

	BOOST_CHECK_EQUAL( array1.size(), 0u );
	BOOST_CHECK_EQUAL( array1.capacity(), 1u );
	BOOST_CHECK_EQUAL( array1.empty(), true );
	BOOST_CHECK( array1.begin() == array1.end() );
	BOOST_CHECK_EQUAL( std::distance(array1.begin(), array1.end()), 0u );

	BOOST_CHECK_EQUAL( array2.size(), 0u );
	BOOST_CHECK_EQUAL( array2.capacity(), 16u );
	BOOST_CHECK_EQUAL( array2.empty(), true );
	BOOST_CHECK( array2.begin() == array2.end() );
	BOOST_CHECK_EQUAL( std::distance(array2.begin(), array2.end()), 0u );
}

BOOST_AUTO_TEST_CASE( reserve_capacity_test )
{
	octo::ByteArray	array0;

	BOOST_CHECK_EQUAL( array0.size(), 0u );
	BOOST_CHECK_EQUAL( array0.capacity(), 0u );

	array0.reserve(0);
	BOOST_CHECK_EQUAL( array0.size(), 0u );
	BOOST_CHECK_EQUAL( array0.capacity(), 0u );

	array0.reserve(1);
	BOOST_CHECK_EQUAL( array0.size(), 0u );
	BOOST_CHECK_EQUAL( array0.capacity(), 1u );

	array0.reserve(0);
	BOOST_CHECK_EQUAL( array0.size(), 0u );
	BOOST_CHECK_EQUAL( array0.capacity(), 1u );

	array0.reserve(2);
	BOOST_CHECK_EQUAL( array0.size(), 0u );
	BOOST_CHECK_EQUAL( array0.capacity(), 2u );
}

BOOST_AUTO_TEST_CASE( reserve_copy_test )
{
	octo::ByteArray	array0({'y', 'o', 'p'});
	std::string		expected("yop");

	BOOST_CHECK_EQUAL( array0.size(), 3u );
	BOOST_CHECK_EQUAL( array0.capacity(), 3u );
	BOOST_CHECK_EQUAL_COLLECTIONS( array0.begin(), array0.end(), expected.begin(), expected.end() );

	array0.reserve(0);
	BOOST_CHECK_EQUAL( array0.size(), 3u );
	BOOST_CHECK_EQUAL( array0.capacity(), 3u );
	BOOST_CHECK_EQUAL_COLLECTIONS( array0.begin(), array0.end(), expected.begin(), expected.end() );

	array0.reserve(1);
	BOOST_CHECK_EQUAL( array0.size(), 3u );
	BOOST_CHECK_EQUAL( array0.capacity(), 3u );
	BOOST_CHECK_EQUAL_COLLECTIONS( array0.begin(), array0.end(), expected.begin(), expected.end() );

	array0.reserve(6);
	BOOST_CHECK_EQUAL( array0.size(), 3u );
	BOOST_CHECK_EQUAL( array0.capacity(), 6u );
	BOOST_CHECK_EQUAL_COLLECTIONS( array0.begin(), array0.end(), expected.begin(), expected.end() );
}

BOOST_AUTO_TEST_CASE( append_test )
{
	octo::ByteArray	array0;

	array0.append({'0'});
	BOOST_CHECK_EQUAL( array0.size(), 1u );
	BOOST_CHECK_EQUAL( array0.capacity(), 1u );
	BOOST_CHECK_EQUAL( array0[0u], '0' );

	array0.append({'1'});
	BOOST_CHECK_EQUAL( array0.size(), 2u );
	BOOST_CHECK_EQUAL( array0.capacity(), 2u );
	BOOST_CHECK_EQUAL( array0[0u], '0' );
	BOOST_CHECK_EQUAL( array0[1u], '1' );

	array0.append({'2', '3'});
	BOOST_CHECK_EQUAL( array0.size(), 4u );
	BOOST_CHECK_EQUAL( array0.capacity(), 4u );
	BOOST_CHECK_EQUAL( array0[0u], '0' );
	BOOST_CHECK_EQUAL( array0[1u], '1' );
	BOOST_CHECK_EQUAL( array0[2u], '2' );
	BOOST_CHECK_EQUAL( array0[3u], '3' );
}

BOOST_AUTO_TEST_CASE( assign_test )
{
	octo::ByteArray	array0;

	array0.assign({'0'});
	BOOST_CHECK_EQUAL( array0.size(), 1u );
	BOOST_CHECK_EQUAL( array0.capacity(), 1u );
	BOOST_CHECK_EQUAL( array0[0u], '0' );

	array0.assign({'1'});
	BOOST_CHECK_EQUAL( array0.size(), 1u );
	BOOST_CHECK_EQUAL( array0.capacity(), 1u );
	BOOST_CHECK_EQUAL( array0[0u], '1' );

	array0.assign({'2', '3'});
	BOOST_CHECK_EQUAL( array0.size(), 2u );
	BOOST_CHECK_EQUAL( array0.capacity(), 2u );
	BOOST_CHECK_EQUAL( array0[0u], '2' );
	BOOST_CHECK_EQUAL( array0[1u], '3' );
}

BOOST_AUTO_TEST_SUITE_END()
