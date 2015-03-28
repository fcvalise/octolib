/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 01:32:13 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/28 01:10:17 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>

#include <Stack.hpp>

BOOST_AUTO_TEST_SUITE( stack )

BOOST_AUTO_TEST_CASE( basic_tests )
{
	octo::Stack<int>	buffer(1024);

	BOOST_REQUIRE(buffer.empty());
	BOOST_REQUIRE_EQUAL(buffer.size(), 0);
	buffer.push(0);
	BOOST_REQUIRE(buffer.empty() == false);
	BOOST_CHECK_EQUAL(buffer.size(), 1);
	BOOST_CHECK_EQUAL(buffer.top(), 0);
	buffer.push(1);
	BOOST_CHECK_EQUAL(buffer.size(), 2);
	BOOST_CHECK_EQUAL(buffer.top(), 0);
	buffer.pop();
	BOOST_REQUIRE(buffer.empty() == false);
	BOOST_CHECK_EQUAL(buffer.size(), 1);
	BOOST_CHECK_EQUAL(buffer.top(), 1);
	buffer.pop();
	BOOST_REQUIRE(buffer.empty());
	BOOST_REQUIRE_EQUAL(buffer.size(), 0);
}

BOOST_AUTO_TEST_CASE( limit_tests )
{
	octo::Stack<int>	buffer(1);

	buffer.push(0);
	BOOST_CHECK_EQUAL(buffer.size(), 1);
	BOOST_CHECK_EQUAL(buffer.top(), 0);
	buffer.pop();
	BOOST_REQUIRE(buffer.empty());
	buffer.push(1);
	BOOST_CHECK_EQUAL(buffer.size(), 1);
	BOOST_CHECK_EQUAL(buffer.top(), 1);
}

BOOST_AUTO_TEST_SUITE_END()
