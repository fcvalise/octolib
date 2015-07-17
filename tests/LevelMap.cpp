#include <boost/test/unit_test.hpp>

#include <PackageReader.hpp>
#include <ByteArray.hpp>
#include <LevelMap.hpp>
#include <stdio.h>
#include <unistd.h>
BOOST_AUTO_TEST_SUITE( level_map )

BOOST_AUTO_TEST_CASE( basic )
{
    octo::LevelMap	lm0;
    octo::ByteArray		buffer;

    BOOST_CHECK_EQUAL( lm0.loadFromMemory(buffer) , false );
}

BOOST_AUTO_TEST_CASE( simple )
{
    octo::LevelMap	lm0;
    octo::ByteArray		buffer;
    octo::PackageReader file;

    if (file.open("/level1.omp")){
        int max =  file.getHeader().count();
        for(int i = 0; i < max; ++i){
            if (octo::PackageHeader::EntryType::LevelMap == file.getHeader().getEntryType(i)){
                file.load(buffer, i);
                break;
            }
        }
        BOOST_CHECK( lm0.getMapCount() == 3 );
    } 
    BOOST_CHECK_EQUAL( lm0.loadFromMemory(buffer) , true );
}

BOOST_AUTO_TEST_SUITE_END()
