/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PackageDetails.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 07:50:58 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/01 11:37:18 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>

#include <details/PackageCommons.hpp>

#include <iostream>

BOOST_AUTO_TEST_SUITE( package_details )

BOOST_AUTO_TEST_CASE( get_extension )
{
	BOOST_CHECK_EQUAL( octo::details::getExtension(""), "" );
	BOOST_CHECK_EQUAL( octo::details::getExtension("."), "" );
	BOOST_CHECK_EQUAL( octo::details::getExtension("yay.yup"), "yup" );
	BOOST_CHECK_EQUAL( octo::details::getExtension("yoy.yay.yup"), "yup" );
	BOOST_CHECK_EQUAL( octo::details::getExtension("yayaya.yyyyaa/yoy.yay.yup"), "yup" );
}

BOOST_AUTO_TEST_CASE( get_basename )
{
	BOOST_CHECK_EQUAL( octo::details::getBaseName(""), "" );
	BOOST_CHECK_EQUAL( octo::details::getBaseName("yaya/"), "" );
	BOOST_CHECK_EQUAL( octo::details::getBaseName("yo"), "yo" );
	BOOST_CHECK_EQUAL( octo::details::getBaseName("jjj/ye/yo"), "yo" );
}

BOOST_AUTO_TEST_CASE( xor_cypher )
{
	std::string					text = "hello random string lalala lalali";
	std::unique_ptr<char[]>		buffer(new char[text.size()]);
	std::unique_ptr<char[]>		expected(new char[text.size()]);
	std::size_t					seed = 12345;
	octo::ByteArray				mask;

	octo::details::generateMask(mask, 16, seed);
	std::copy(text.begin(), text.end(), buffer.get());
	std::copy(text.begin(), text.end(), expected.get());
	octo::details::xorEncryptDecrypt(buffer.get(), buffer.get() + text.size(), mask);
	BOOST_REQUIRE( std::equal(text.begin(), text.end(), buffer.get()) == false );
	octo::details::xorEncryptDecrypt(buffer.get(), buffer.get() + text.size(), mask);
	BOOST_CHECK_EQUAL_COLLECTIONS( text.begin(), text.end(), buffer.get(), buffer.get() + text.size() );
	
}

BOOST_AUTO_TEST_SUITE_END()
