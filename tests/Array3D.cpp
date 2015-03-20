/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array3D.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/20 21:59:01 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/20 22:22:11 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>
#include <iterator>

#include <Array3D.hpp>

BOOST_AUTO_TEST_SUITE( array_3d )

BOOST_AUTO_TEST_CASE( trivials_tests )
{
	octo::Array3D<int>	array0;
	octo::Array3D<int>	array1(3u, 4u, 5u);
	octo::Array3D<int>	array2(3u, 4u, 5u, 666);
	
	BOOST_CHECK_EQUAL( true, array0.isNull() );
	BOOST_CHECK_EQUAL( false, array1.isNull() );
	BOOST_CHECK_EQUAL( false, array2.isNull() );

	BOOST_CHECK_EQUAL( 0u, array0.columns() );
	BOOST_CHECK_EQUAL( 0u, array0.rows() );
	BOOST_CHECK_EQUAL( 0u, array0.depth() );
	BOOST_CHECK_EQUAL( 0u, array0.count() );

	BOOST_CHECK_EQUAL( 3u, array1.columns() );
	BOOST_CHECK_EQUAL( 4u, array1.rows() );
	BOOST_CHECK_EQUAL( 5u, array1.depth() );
	BOOST_CHECK_EQUAL( 60u, array1.count() );

	BOOST_CHECK_EQUAL( 3u, array2.columns() );
	BOOST_CHECK_EQUAL( 4u, array2.rows() );
	BOOST_CHECK_EQUAL( 5u, array2.depth() );
	BOOST_CHECK_EQUAL( 60u, array2.count() );

	BOOST_CHECK_EQUAL( 60u, std::distance(array1.begin(), array1.end()) );
	BOOST_CHECK_EQUAL( 60u, std::distance(array2.begin(), array2.end()) );
	BOOST_CHECK_EQUAL( 60u, std::count(array2.begin(), array2.end(), 666) );
}

BOOST_AUTO_TEST_CASE( resize_tests )
{
	octo::Array3D<int>	array0;

	array0.resize(3u, 4u, 5u);
	BOOST_CHECK_EQUAL( 3u, array0.columns() );
	BOOST_CHECK_EQUAL( 4u, array0.rows() );
	BOOST_CHECK_EQUAL( 5u, array0.depth() );
	BOOST_CHECK_EQUAL( 60u, array0.count() );
	BOOST_CHECK_EQUAL( 60u, std::distance(array0.begin(), array0.end()) );
}

BOOST_AUTO_TEST_CASE( move_tests )
{
	octo::Array3D<int>	array0(3u, 4u, 5u, 666);
	octo::Array3D<int>	array1(std::move(array0));

	BOOST_CHECK_EQUAL( true, array0.isNull() );
	BOOST_CHECK_EQUAL( 0u, array0.columns() );
	BOOST_CHECK_EQUAL( 0u, array0.rows() );
	BOOST_CHECK_EQUAL( 0u, array0.depth() );
	BOOST_CHECK_EQUAL( 0u, array0.count() );
	BOOST_CHECK_EQUAL( false, array1.isNull() );
	BOOST_CHECK_EQUAL( 3u, array1.columns() );
	BOOST_CHECK_EQUAL( 4u, array1.rows() );
	BOOST_CHECK_EQUAL( 5u, array1.depth() );
	BOOST_CHECK_EQUAL( 60u, array1.count() );
	BOOST_CHECK_EQUAL( 60u, std::distance(array1.begin(), array1.end()) );
	array0 = std::move(array1);
	BOOST_CHECK_EQUAL( true, array1.isNull() );
	BOOST_CHECK_EQUAL( 0u, array1.columns() );
	BOOST_CHECK_EQUAL( 0u, array1.rows() );
	BOOST_CHECK_EQUAL( 0u, array1.depth() );
	BOOST_CHECK_EQUAL( 0u, array1.count() );
	BOOST_CHECK_EQUAL( false, array0.isNull() );
	BOOST_CHECK_EQUAL( 3u, array0.columns() );
	BOOST_CHECK_EQUAL( 4u, array0.rows() );
	BOOST_CHECK_EQUAL( 5u, array0.depth() );
	BOOST_CHECK_EQUAL( 60u, array0.count() );
	BOOST_CHECK_EQUAL( 60u, std::distance(array0.begin(), array0.end()) );
}

BOOST_AUTO_TEST_SUITE_END()
