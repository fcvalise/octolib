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
            explicit SpriteTrigger(sf::Vector2f pos, int index,
                    sf::RectangleShape rec, int mapIndex = -1) :
                position(pos),
                trigger(rec),
                mapIndex(mapIndex),
                spriteIndex(index)
            {
            }
            
            sf::Vector2f        position;
            sf::RectangleShape  trigger;
            int                 mapIndex;
            int                 spriteIndex;
        };
        int * const &               getMap(std::size_t i) const;
        std::size_t                 getMapCount() const;
        sf::Vector2i                getMapSize() const;
        std::size_t                 getSpriteCount() const;
        LevelMap::SpriteTrigger     getSprite(std::size_t index);
        LevelMap::SpriteTrigger     getSpriteByIndexPackage(std::size_t indexPackage);
        LevelMap::SpriteTrigger     getSpriteByIndexMap(std::size_t indexMap);
		bool					    loadFromMemory(ByteArray const& buffer);
        
    private:
        bool                        load(std::istream & ile);
        void                        setup(int len);
        void                        addLineAt(int, int, std::string);
        void                        addSprite(std::string , int);
        std::size_t                 m_spritesCount;
        std::vector<int *>          m_tileMap;
        std::unique_ptr<SpriteTrigger[]>  m_sprites;
        sf::Vector2i                m_size; 
    };
}

#endif
