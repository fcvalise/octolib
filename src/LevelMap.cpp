#include <LevelMap.hpp>
#include <iostream>
#include <sstream>
#include <string>

namespace octo
{
    std::size_t LevelMap::getMapCount() const
    {
        return m_tileMap.size();
    }

    sf::Vector2i const & LevelMap::getMapSize() const
    {
        return m_size;
    }

    int * const& LevelMap::getMap(std::size_t i) const
    {
        return m_tileMap.at(i);
    }

    std::size_t LevelMap::getSpriteCount() const
    {
        return m_sprites.size();
    }

    LevelMap::SpriteTrigger const & LevelMap::getSprite(std::size_t index) const
    {
        return m_sprites.at(index);
    }

    LevelMap::SpriteTrigger & LevelMap::getSprite(std::size_t index)
    {
        return m_sprites.at(index);
    }

    void LevelMap::getSpritesByIndexPackage(std::size_t index, std::vector<LevelMap::SpriteTrigger>& sprites)
    {
        sprites.clear();
        std::size_t i = 0;
        for (auto sprite : m_sprites){
            if (sprite.spriteIndex == index){
                sprites.push_back(sprite);
                i++;
            }
        }
        sprites.resize(i);
    }

    void LevelMap::getSpritesByIndexMap(std::size_t index, std::vector<LevelMap::SpriteTrigger>& sprites)
    {
        sprites.clear();
        std::size_t i = 0;
        for (auto sprite : m_sprites){
            if (sprite.mapIndex == index){
                sprites.push_back(sprite);
                i++;
            }
        }
        sprites.resize(i);
    }

    bool LevelMap::loadFromMemory(ByteArray const& buffer)
    {
        if (!buffer.size())
            return false;
        std::string map = std::string(buffer.bytes(), buffer.size());
        std::istringstream mapS;
        mapS.str(map.c_str());
        if (!load(mapS))
            return false;
        m_sprites.resize(m_spritesCount);
        return true;
    }

    bool LevelMap::load(std::istream & file)
    {
        int indexLine = 0;
        int currentMap = 0;
        int nbrOfMap = 0;
        m_spritesCount = 0;
        std::string line;

        std::getline(file, line);
        nbrOfMap = std::stoi(line.substr(0, line.find(";")));
        m_size = sf::Vector2i(std::stoi(line.substr(line.find(";") + 1, line.find("x"))),
                std::stoi(line.substr(line.find("x") + 1, line.length())));
        setup(nbrOfMap);
        while ( std::getline(file, line) )
        {
            if (indexLine == m_size.y){
                indexLine = 0;
                currentMap++;
            }
            if (line.at(0) == '#')
                addSprite(line.substr(1, line.length()), currentMap);
            else{
                if (currentMap == nbrOfMap)
                    continue;
                addLineAt(currentMap, indexLine, line);
                indexLine++;
            }
        }
        return true;
    }

    void LevelMap::setup(int len)
    {
        int size = m_size.x * m_size.y;
        m_spritesCount = 0;
        m_sprites.resize(0);
        m_tileMap.reserve(len);
        for (int x = 0; x < len; x++){
            m_tileMap.push_back(new int[sizeof(int) * size]);
            for(int i = 0; i < size ; i++){
                m_tileMap[x][i] = 0;
            }
        }
        m_tileMap.resize(len);
    }


    void LevelMap::addLineAt(int map, int index, std::string & line)
    {
        int indexInTile = index * m_size.x;
        std::string delimiter = ",";
        size_t pos = 0;
        while ((pos = line.find(delimiter)) != std::string::npos) {
            m_tileMap[map][indexInTile++] = std::stoi(line.substr(0, pos));
            line.erase(0, pos + delimiter.length());
        }
        m_tileMap[map][indexInTile] = std::stoi(line);
    }

    void LevelMap::addSprite(std::string line, int map)
    {
        octo::ByteArray image;
        sf::Vector2f    pos;
        sf::Vector2f    topLeftRec;
        sf::Vector2f    sizeRec;
        sf::RectangleShape  rec;

        int index = std::stoi(line.substr(0, line.find("(")));
        line.erase(0, line.find("(") + 1);
        pos.x = std::stoi(line.substr(0, line.find(";")));
        line.erase(0, line.find(";") + 1);
        pos.y = std::stoi(line.substr(0, line.find(")")));
        if (line.find("[")){
            line.erase(0, line.find("[") + 1);
            topLeftRec.x = std::stoi(line.substr(0, line.find("/")));
            line.erase(0, line.find("/") + 1);
            topLeftRec.y = std::stoi(line.substr(0, line.find("]")));
            line.erase(0, line.find("[") + 1);
            sizeRec.x = std::stoi(line.substr(0, line.find("/")));
            line.erase(0, line.find("/") + 1);
            sizeRec.y = std::stoi(line.substr(0, line.find("]")));
            rec.setPosition(topLeftRec);
            rec.setSize(sizeRec);
            rec.setFillColor(sf::Color::Transparent);
            rec.setOutlineThickness(5.0f);
        }
        m_sprites.push_back(SpriteTrigger(pos, index, rec , map));
        m_spritesCount++;
    }
}
