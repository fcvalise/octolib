#include <LevelMap.hpp>
#include <iostream>
#include <sstream>

namespace octo
{
	std::size_t LevelMap::getMapCount() const
	{
		return m_tileMap.depth();
	}

	sf::Vector2i const & LevelMap::getMapSize() const
	{
		return m_size;
	}

	Array3D<LevelMap::TileType> const & LevelMap::getMap() const
	{
		return m_tileMap;
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

	void LevelMap::getSpritesByName(std::string name, std::vector<LevelMap::SpriteTrigger *> & sprites)
	{
		sprites.clear();
		std::size_t i = 0;
		for (auto & sprite : m_sprites){
			if (sprite.name == name){
				sprites.push_back(&sprite);
				i++;
			}
		}
		sprites.resize(i);
	}

	void LevelMap::getSpritesByIndexMap(std::size_t index, std::vector<LevelMap::SpriteTrigger *> & sprites)
	{
		sprites.clear();
		std::size_t i = 0;
		for (auto & sprite : m_sprites){
			if (sprite.mapIndex == index){
				sprites.push_back(&sprite);
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
		std::size_t			indexLine = 0;
		std::size_t			currentMap = 0;
		std::size_t			nbrOfMap = 0;
		std::string			line;
		std::size_t			lastFind;
		m_spritesCount = 0;

		std::getline(file, line);
		lastFind = line.find(';');
		nbrOfMap = std::stoi(line.substr(0, lastFind));
		line.erase(0, lastFind + 1);
		lastFind = line.find('x');
		m_size = sf::Vector2i(std::stoi(line.substr(0 , lastFind)),
				std::stoi(line.substr(lastFind + 1, line.length())));
		setup(nbrOfMap);
		while ( std::getline(file, line) )
		{
			if (indexLine == static_cast<std::size_t>(m_size.y)){
				indexLine = 0;
				currentMap++;
			}
			if (line.at(0) == '#')
				addSprite(line , currentMap);
			else{
				if (currentMap == nbrOfMap)
					continue;
				addLineAt(currentMap, indexLine, line);
				indexLine++;
			}
		}
		return true;
	}

	void LevelMap::setup(std::size_t len)
	{
		m_spritesCount = 0;
		m_sprites.resize(0);
		m_tileMap.resize(m_size.x, m_size.y, len);
	}

	void LevelMap::addLineAt(std::size_t map, std::size_t index, std::string & line)
	{
		char		delimiter = ',';
		std::size_t	pos = 0;
		std::size_t	i = 0;
			while ((pos = line.find(delimiter)) != std::string::npos){
				m_tileMap.set(i++, index, map , static_cast<TileType>(std::stoi(line.substr(0, pos))));
				line.erase(0, pos + 1);
			}
		m_tileMap.set(i, index, map, static_cast<TileType>(std::stoi(line)));
	}
#include <iostream>
	void LevelMap::addSprite(std::string & line, std::size_t map)
	{
		octo::ByteArray		image;
		sf::Vector2f		pos;
		sf::Vector2f		topLeftRec;
		sf::Vector2f		sizeRec;
		sf::FloatRect			rec;
		std::size_t				lastFind;
		std::string				name;

		lastFind = line.find('(');
		name = line.substr(1, lastFind - 1);
		line.erase(0, lastFind + 1);
		lastFind = line.find(';');
		pos.x = std::stoi(line.substr(0, lastFind));
		line.erase(0, lastFind + 1);
		lastFind = line.find(')');
		pos.y = std::stoi(line.substr(0, lastFind));
		lastFind = line.find('[');
		if (lastFind != std::string::npos){
			line.erase(0, lastFind + 1);
			lastFind = line.find('/');
			topLeftRec.x = std::stoi(line.substr(0, lastFind));
			line.erase(0, lastFind + 1);
			lastFind = line.find(']');
			topLeftRec.y = std::stoi(line.substr(0, lastFind));
			line.erase(0, lastFind + 1);
			lastFind = line.find('[');
			if (lastFind != std::string::npos){
				line.erase(0, lastFind + 1);
				lastFind = line.find('/');
				sizeRec.x = std::stoi(line.substr(0, lastFind));
				line.erase(0, lastFind + 1);
				lastFind = line.find(']');
				sizeRec.y = std::stoi(line.substr(0, lastFind));
				rec = sf::FloatRect(topLeftRec, sizeRec);
			}
		}
		m_sprites.push_back(SpriteTrigger(pos, name, rec, map));
		m_spritesCount++;
	}
}
