#include <boost/test/unit_test.hpp>

#include <PackageReader.hpp>
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
	octo::LevelMap			lm0;
	octo::ByteArray			buffer;
	octo::PackageReader		file;
	size_t					index;
	bool					loadFromMemory;
	std::vector<octo::LevelMap::SpriteTrigger *>	sprites;

	BOOST_TEST_MESSAGE("open pck");
	if (file.open("map.pck")){
		std::size_t max =  file.getHeader().count();
		BOOST_TEST_MESSAGE("load map");
		for(std::size_t i = 0; i < max; i++){
			if (octo::PackageHeader::EntryType::LevelMap == file.getHeader().getEntryType(i)){
				BOOST_CHECK(file.load(buffer, i));
				break;
			}
		}
		BOOST_TEST_MESSAGE("testing map");
		loadFromMemory = lm0.loadFromMemory(buffer);
		BOOST_CHECK(loadFromMemory);
		if (!loadFromMemory)
			return ;
		BOOST_CHECK(lm0.getMapSize() == sf::Vector2i(120, 50));
		BOOST_CHECK_EQUAL(lm0.getMapCount() , 3);

		octo::Array3D<octo::LevelMap::TileType> const & map = lm0.getMap();
		BOOST_CHECK_EQUAL(map.columns(), 120);
		BOOST_CHECK_EQUAL(map.rows(), 50);
		BOOST_CHECK_EQUAL(map.depth(), 3);
		BOOST_CHECK_EQUAL(map.count(), 18000);

		BOOST_CHECK(map.get(0, 0 , 0) == octo::LevelMap::TileType::Empty);
		/* Error return TileType::TopRightCorner */
		BOOST_CHECK(map.get(119, 49, 0) == octo::LevelMap::TileType::Empty);

		BOOST_CHECK(map.get(0, 0, 1) == octo::LevelMap::TileType::Square);
		/* Error return TileType::TopRightCorner */
		BOOST_CHECK(map.get(119, 49, 1) == octo::LevelMap::TileType::Square);

		BOOST_CHECK(map.get(0, 0, 2) == octo::LevelMap::TileType::TopRightCorner);
		BOOST_CHECK(map.get(119, 49, 2) == octo::LevelMap::TileType::TopRightCorner);

		BOOST_TEST_MESSAGE("testing spriteTrigger");
		index = lm0.getSpriteCount();
		BOOST_CHECK_EQUAL(index, 5);
		if (index != 5)
			return;
		BOOST_CHECK(lm0.getSprite(0).positionSprite == sf::Vector2f(0, 0));
		BOOST_CHECK_EQUAL(lm0.getSprite(0).trigger.top, 48);
		BOOST_CHECK_EQUAL(lm0.getSprite(0).trigger.left, 0);

		BOOST_CHECK(lm0.getSprite(2).positionSprite == sf::Vector2f(736, 336));

		BOOST_CHECK_EQUAL(lm0.getSprite(4).trigger.top, 480);
		BOOST_CHECK_EQUAL(lm0.getSprite(4).trigger.left, 1408);
		BOOST_CHECK_EQUAL(lm0.getSprite(4).trigger.width, 464);
		BOOST_CHECK_EQUAL(lm0.getSprite(4).trigger.height, 48);
		BOOST_CHECK_EQUAL(lm0.getSprite(4).mapIndex, 0);
		BOOST_CHECK_EQUAL(lm0.getSprite(4).spriteIndex, 1);

		lm0.getSpritesByIndexPackage(1, sprites);
		BOOST_CHECK_EQUAL(sprites.size(), 5);

		lm0.getSpritesByIndexMap(0, sprites);
		BOOST_CHECK_EQUAL(sprites.size(), 5);
		BOOST_CHECK(sprites.at(0)->positionSprite == sf::Vector2f(0, 0));
		BOOST_CHECK_EQUAL(sprites.at(4)->trigger.width, 464);
		BOOST_CHECK_EQUAL(sprites.at(4)->trigger.height, 48);
		sprites.at(0)->positionSprite = sf::Vector2f(2,2);
		BOOST_CHECK(lm0.getSprite(0).positionSprite == sf::Vector2f(2, 2));

		lm0.getSpritesByIndexMap(1, sprites);
		BOOST_CHECK_EQUAL(sprites.size(), 0);
	}
	BOOST_CHECK(file.isOpen());
}

BOOST_AUTO_TEST_SUITE_END()
