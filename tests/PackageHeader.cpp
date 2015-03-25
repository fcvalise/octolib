/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PackageHeader.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 04:31:20 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/25 10:53:01 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>

#include <PackageHeader.hpp>

BOOST_TEST_DONT_PRINT_LOG_VALUE( octo::PackageHeader::EntryType );

BOOST_AUTO_TEST_SUITE( package_header )

BOOST_AUTO_TEST_CASE( integrity_checks )
{
	octo::PackageHeader	header0;
	octo::PackageHeader	header1;
	std::ostringstream	oss(std::ios_base::binary);
	std::string			buffer;
	std::istringstream	iss(std::ios_base::binary);
	octo::PackageHeader::Entry	entry;

	header0.addEntry(octo::PackageHeader::EntryType::Texture, "tex", 0, 2);
	header0.addEntry(octo::PackageHeader::EntryType::Text, "tox", 1, 3);
	header0.addEntry(octo::PackageHeader::EntryType::Sound, "toxmex", 2, 4);
	header0.write(oss);
	iss.str(oss.str());
	header1.read(iss);
	BOOST_CHECK_EQUAL( header0.count(), header1.count() );
	BOOST_CHECK( header1.getEntry(0, entry) );
	BOOST_CHECK_EQUAL( entry.name, "tex" );
	BOOST_CHECK_EQUAL( entry.offset, 0 );
	BOOST_CHECK_EQUAL( entry.size, 2 );
	BOOST_CHECK_EQUAL( entry.type, octo::PackageHeader::EntryType::Texture );
	BOOST_CHECK( header1.getEntry(1, entry) );
	BOOST_CHECK_EQUAL( entry.name, "tox" );
	BOOST_CHECK_EQUAL( entry.offset, 1 );
	BOOST_CHECK_EQUAL( entry.size, 3 );
	BOOST_CHECK_EQUAL( entry.type, octo::PackageHeader::EntryType::Text );
	BOOST_CHECK( header1.getEntry(2, entry) );
	BOOST_CHECK_EQUAL( entry.name, "toxmex" );
	BOOST_CHECK_EQUAL( entry.offset, 2 );
	BOOST_CHECK_EQUAL( entry.size, 4 );
	BOOST_CHECK_EQUAL( entry.type, octo::PackageHeader::EntryType::Sound );
}

BOOST_AUTO_TEST_SUITE_END()
