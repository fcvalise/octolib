#include <boost/test/unit_test.hpp>

#include <PackageReader.hpp>
#include <ByteArray.hpp>
#include <LevelMap.hpp>

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
    std::vector<octo::LevelMap::SpriteTrigger> sprites;
    int   * map;
    size_t index;

    BOOST_TEST_MESSAGE("open pck");

    if (file.open("map.pck")){
        int max =  file.getHeader().count();
        BOOST_TEST_MESSAGE("load map");
        for(int i = 0; i < max; ++i){
            if (octo::PackageHeader::EntryType::LevelMap == file.getHeader().getEntryType(i)){
                file.load(buffer, i);
                break;
            }
        }
        BOOST_TEST_MESSAGE("testing map int");
        BOOST_CHECK(lm0.loadFromMemory(buffer));
        BOOST_CHECK_EQUAL(lm0.getMapCount() , 3);
        for (std::size_t i = 0; i < 3; i++){
            map = lm0.getMap(i);
            for(int x = 0; x < 6000; x++){
                BOOST_CHECK_EQUAL(map[x], i);
            }
        }
        BOOST_TEST_MESSAGE("testing spriteTrigger");
        BOOST_CHECK(lm0.getMapSize() == sf::Vector2i(120, 50));
        index = lm0.getSpriteCount();
        BOOST_CHECK_EQUAL(index, 5);
        if (index != 5)
            return;
        BOOST_CHECK(lm0.getSprite(0).position == sf::Vector2f(0, 0));
        BOOST_CHECK(lm0.getSprite(0).trigger.getSize() == sf::Vector2f(160, 16));
        BOOST_CHECK(lm0.getSprite(2).position == sf::Vector2f(736, 336));
        BOOST_CHECK(lm0.getSprite(4).trigger.getPosition() == sf::Vector2f(1408, 480));
        BOOST_CHECK(lm0.getSprite(4).trigger.getSize() == sf::Vector2f(464, 48));
        BOOST_CHECK_EQUAL(lm0.getSprite(4).mapIndex, 0);
        BOOST_CHECK_EQUAL(lm0.getSprite(4).spriteIndex, 1);


        lm0.getSpritesByIndexPackage(1, sprites);
        BOOST_CHECK_EQUAL(sprites.size(), 5);

        lm0.getSpritesByIndexMap(0, sprites);
        BOOST_CHECK_EQUAL(sprites.size(), 5);
        BOOST_CHECK(sprites.at(0).position == sf::Vector2f(0, 0));
        BOOST_CHECK(sprites.at(4).trigger.getSize() == sf::Vector2f(464, 48));

        lm0.getSpritesByIndexMap(1, sprites);
        BOOST_CHECK_EQUAL(sprites.size(), 0);
    } 
    BOOST_CHECK(file.isOpen());
}

BOOST_AUTO_TEST_SUITE_END()
