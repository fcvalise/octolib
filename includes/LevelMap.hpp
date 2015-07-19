#ifndef LEVELMAP_HPP
# define LEVELMAP_HPP
# include <SFML/Graphics/RectangleShape.hpp>
# include "ByteArray.hpp"

namespace octo
{
	/*!
	 *	\ingroup Level
	 *	\class LevelMap
	 *	\brief Level map
	 *
	 */
    class LevelMap
    {
    public:
        struct SpriteTrigger
        {
            SpriteTrigger(){};
            explicit SpriteTrigger(sf::Vector2f const& pos, int index,
                    sf::RectangleShape const& rec, int mapIndex = -1) :
                position(pos),
                trigger(rec),
                mapIndex(mapIndex),
                spriteIndex(index)
            {
            }
            
            sf::Vector2f        position;
            sf::RectangleShape  trigger;
            std::size_t         mapIndex;
            std::size_t         spriteIndex;
        };
        int * const &               getMap(std::size_t i) const;
        std::size_t                 getMapCount() const;
        sf::Vector2i const &              getMapSize() const;
        std::size_t                 getSpriteCount() const;
        LevelMap::SpriteTrigger const &    getSprite(std::size_t index) const;
        LevelMap::SpriteTrigger &    getSprite(std::size_t index);

        void                    getSpritesByIndexPackage(std::size_t indexPackage,
                std::vector<LevelMap::SpriteTrigger> & sprites);
        void                    getSpritesByIndexMap(std::size_t indexMap,
                std::vector<LevelMap::SpriteTrigger> & sprites);

		bool					    loadFromMemory(ByteArray const& buffer);
        
    private:
        bool                        load(std::istream & ile);
        void                        setup(int len);
        void                        addLineAt(int map, int index, std::string & line);
        void                        addSprite(std::string & line, int map);
        std::size_t                 m_spritesCount;
        std::vector<int *>          m_tileMap;
        std::vector<SpriteTrigger>  m_sprites;
        sf::Vector2i                m_size; 
    };
}

#endif
