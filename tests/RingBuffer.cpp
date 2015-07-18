/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RingBuffer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/16 18:54:35 by irabeson          #+#    #+#             */
/*   Updated: 2015/07/18 15:59:24 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>
#include <iterator>

#include <RingBuffer.hpp>

BOOST_AUTO_TEST_SUITE( ring_buffer )

BOOST_AUTO_TEST_CASE( trivials_tests )
{
	octo::RingBuffer<int>	ringBuffer(5);

	BOOST_CHECK_EQUAL( ringBuffer.empty(), true );
	BOOST_CHECK_EQUAL( ringBuffer.size(), 0 );
	
	ringBuffer.push(0);
	ringBuffer.push(1);
	ringBuffer.push(2);
	ringBuffer.push(3);
	ringBuffer.push(4);
	BOOST_CHECK_EQUAL( ringBuffer[0], 0 );
	BOOST_CHECK_EQUAL( ringBuffer[1], 1 );
	BOOST_CHECK_EQUAL( ringBuffer[2], 2 );
	BOOST_CHECK_EQUAL( ringBuffer[3], 3 );
	BOOST_CHECK_EQUAL( ringBuffer[4], 4 );
}

BOOST_AUTO_TEST_CASE( capacity )
{
	octo::RingBuffer<int>	ringBuffer(5);

	BOOST_CHECK_EQUAL( ringBuffer.empty(), true );
	BOOST_CHECK_EQUAL( ringBuffer.size(), 0 );
	
	BOOST_CHECK_EQUAL( ringBuffer.capacity(), 5 );
	ringBuffer.push(0);
	BOOST_CHECK_EQUAL( ringBuffer.capacity(), 4 );
	ringBuffer.push(1);
	BOOST_CHECK_EQUAL( ringBuffer.capacity(), 3 );
	ringBuffer.push(2);
	BOOST_CHECK_EQUAL( ringBuffer.capacity(), 2 );
	ringBuffer.push(3);
	BOOST_CHECK_EQUAL( ringBuffer.capacity(), 1 );
	ringBuffer.push(4);
	BOOST_CHECK_EQUAL( ringBuffer.capacity(), 0 );
	BOOST_CHECK_EQUAL( ringBuffer[0], 0 );
	BOOST_CHECK_EQUAL( ringBuffer[1], 1 );
	BOOST_CHECK_EQUAL( ringBuffer[2], 2 );
	BOOST_CHECK_EQUAL( ringBuffer[3], 3 );
	BOOST_CHECK_EQUAL( ringBuffer[4], 4 );
}
BOOST_AUTO_TEST_CASE( push_pop )
{
	octo::RingBuffer<int>	ringBuffer(1);

	BOOST_CHECK_EQUAL( ringBuffer.empty(), true );
	BOOST_CHECK_EQUAL( ringBuffer.size(), 0 );
	ringBuffer.push(0);
	BOOST_CHECK_EQUAL( ringBuffer.empty(), false );
	BOOST_CHECK_EQUAL( ringBuffer.size(), 1 );
	BOOST_CHECK_EQUAL( ringBuffer[0], 0 );
	BOOST_CHECK_EQUAL( ringBuffer.capacity(), 0 );
	ringBuffer.pop();
	BOOST_CHECK_EQUAL( ringBuffer.empty(), true );
	BOOST_CHECK_EQUAL( ringBuffer.size(), 0 );
}

BOOST_AUTO_TEST_CASE( top )
{
	octo::RingBuffer<int>	ringBuffer(2);

	ringBuffer.push(0);
	ringBuffer.push(1);
	BOOST_CHECK_EQUAL( ringBuffer.top(), 0 );
	ringBuffer.pop();
	BOOST_CHECK_EQUAL( ringBuffer.top(), 1 );
	ringBuffer.push(2);
	BOOST_CHECK_EQUAL( ringBuffer.top(), 1 );
	ringBuffer.pop();
	BOOST_CHECK_EQUAL( ringBuffer.top(), 2 );
}

BOOST_AUTO_TEST_CASE( access_tests )
{
	octo::RingBuffer<int>	ringBuffer(5);

	BOOST_CHECK_EQUAL( ringBuffer.empty(), true );
	BOOST_CHECK_EQUAL( ringBuffer.size(), 0 );
	
	ringBuffer.push(0);
	ringBuffer.push(1);
	ringBuffer.push(2);
	ringBuffer.push(3);
	ringBuffer.push(4);
	BOOST_CHECK_EQUAL( ringBuffer[0], 0 );
	BOOST_CHECK_EQUAL( ringBuffer[1], 1 );
	BOOST_CHECK_EQUAL( ringBuffer[2], 2 );
	BOOST_CHECK_EQUAL( ringBuffer[3], 3 );
	BOOST_CHECK_EQUAL( ringBuffer[4], 4 );

	BOOST_CHECK_EQUAL( ringBuffer[0 + 5], 0);
	BOOST_CHECK_EQUAL( ringBuffer[1 + 5], 1);
	BOOST_CHECK_EQUAL( ringBuffer[2 + 5], 2);
	BOOST_CHECK_EQUAL( ringBuffer[3 + 5], 3);
	BOOST_CHECK_EQUAL( ringBuffer[4 + 5], 4);

	BOOST_CHECK_EQUAL( ringBuffer[0 + 10], 0);
	BOOST_CHECK_EQUAL( ringBuffer[1 + 10], 1);
	BOOST_CHECK_EQUAL( ringBuffer[2 + 10], 2);
	BOOST_CHECK_EQUAL( ringBuffer[3 + 10], 3);
	BOOST_CHECK_EQUAL( ringBuffer[4 + 10], 4);

	BOOST_CHECK_EQUAL( ringBuffer[0 - 5], 0);
	BOOST_CHECK_EQUAL( ringBuffer[1 - 5], 1);
	BOOST_CHECK_EQUAL( ringBuffer[2 - 5], 2);
	BOOST_CHECK_EQUAL( ringBuffer[3 - 5], 3);
	BOOST_CHECK_EQUAL( ringBuffer[4 - 5], 4);
	
	BOOST_CHECK_EQUAL( ringBuffer[0 - 10], 0);
	BOOST_CHECK_EQUAL( ringBuffer[1 - 10], 1);
	BOOST_CHECK_EQUAL( ringBuffer[2 - 10], 2);
	BOOST_CHECK_EQUAL( ringBuffer[3 - 10], 3);
	BOOST_CHECK_EQUAL( ringBuffer[4 - 10], 4);
}
BOOST_AUTO_TEST_SUITE_END()
