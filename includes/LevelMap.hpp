#ifndef LEVELMAP_HPP
# define LEVELMAP_HPP
# include <SFML/Graphics/RectangleShape.hpp>
# include "ByteArray.hpp"
# include "Array3D.hpp"
# include <string>
namespace octo
{
	/*!
	 *	\ingroup Level
	 *	\class LevelMap
	 *	\brief get a LevelMap from ByteArray
	 */
	class LevelMap
	{
		public:
			/*!	Identifiers of tileType
			 *
			 * add custom tileType here, defined in editor
			 */
			enum class TileType : std::uint8_t
		{
			Empty,
			Square,
			TopRightCorner,
			TopLeftCorner,
			BotLeftCorner,
			BotRightCorner,
			Rock = 6,
			Custom = 7,
		};

			/*! struct SpriteTrigger */
			struct SpriteTrigger
			{
				SpriteTrigger() = default;
				explicit SpriteTrigger(sf::Vector2f const& pos, bool isFront, std::string const& fileName,
						sf::FloatRect const& rec, std::size_t mapIndex) :
					positionSprite(pos),
					trigger(rec),
					isFront(isFront),
					name(fileName),
					mapIndex(mapIndex)
				{
				}
				sf::Vector2f		positionSprite;
				sf::FloatRect		trigger;
				bool				isFront;
				std::string			name;
				std::size_t			mapIndex;
			};

			struct Decor
			{
				Decor() = default;
				explicit Decor(sf::Vector2f const& pos, sf::Vector2f const& scale, bool isFront, std::string const& fileName) :
					position(pos),
					scale(scale),
					isFront(isFront),
					name(fileName)
				{
				}
				sf::Vector2f		position;
				sf::Vector2f		scale;
				bool				isFront;
				std::string			name;
			};

			/*!	Get the map count */
			std::size_t				getMapCount() const;

			/*!	Get the size of map */
			sf::Vector2i const &	getMapSize() const;

			/*!	Get all map 
			 *  return all map storage in octo::Array3D
			 */
			Array3D<TileType>const &			getMap() const;

			/*!	Get the sprite count */
			std::size_t							getSpriteCount() const;
			/*!	Get decors count */
			std::size_t							getDecorCount() const;

			/*! Get spriteTrigger 
			 *
			 *	\param index =	between 0 and map count 
			 */
			LevelMap::SpriteTrigger const &		getSprite(std::size_t index) const;
			LevelMap::SpriteTrigger &			getSprite(std::size_t index);

			/*! Get decor
			 *
			 *	\param index =	between 0 and map count
			 */
			LevelMap::Decor const &		getDecor(std::size_t index) const;
			LevelMap::Decor &			getDecor(std::size_t index);

			/*! Get collection of spriteTrigger by indexPackage
			 *
			 *	\param name = fileName of spriteSheet
			 *	\param sprites vector of LevelMap::SpriteTrigger
			 */
			void	getSpritesByName(std::string const& name,
					std::vector<LevelMap::SpriteTrigger *> & sprites);

			/*! Get collection of spriteTrigger by indexMap
			 *
			 *	\param indexMap => 0 and < map count (Array3D.depth())
			 *	\param sprites vector of LevelMap::SpriteTrigger
			 */
			void	getSpritesByIndexMap(std::size_t indexMap,
					std::vector<LevelMap::SpriteTrigger *> & sprites);

			/*! Load from octo::ByteArray */
			bool							loadFromMemory(ByteArray const& buffer);
			/*! Load from file */
			bool							loadFromFile(std::string filename);
		private:
			bool							load(std::istream & file);
			void							setup(std::size_t len);
			void							addLineAt(std::size_t map, std::size_t index, std::string & line);
			void							addSprite(std::string & line, std::size_t map);
			void							addDecor(std::string & line);
			std::size_t						m_spritesCount;
			std::size_t						m_decorsCount;
			Array3D<TileType>				m_tileMap;
			std::vector<SpriteTrigger>		m_sprites;
			std::vector<Decor>				m_decors;
			sf::Vector2i					m_size;
	};
}

#endif
