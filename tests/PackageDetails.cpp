/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PackageDetails.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 07:50:58 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/25 07:56:11 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>

#include <details/PackageCommons.hpp>

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

BOOST_AUTO_TEST_SUITE_END()
