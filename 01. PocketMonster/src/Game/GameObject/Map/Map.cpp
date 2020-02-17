#include "stdafx.h"
#include "Map.h"

Map::Map()
{

}
Map::Map(const Map& map) 
{
	m_width = map.m_width;
	m_height = map.m_height;


	m_playerStartPositionX = map.m_playerStartPositionX;
	m_playerStartPositionY = map.m_playerStartPositionY;
	m_playerPositionX = m_playerStartPositionX;
	m_playerPositionY = m_playerStartPositionX;

	m_tiles = map.m_tiles;
	for (auto& e : m_tiles) {
		e.init();
	}
}

Map::~Map()
{
}

void Map::init(char * _fileName)
{
	//for test
	if (_fileName == nullptr) {
		m_width = 15;
		m_height = 15;
		m_playerStartPositionX = 4;
		m_playerStartPositionY = 4;
		for (int y = 0; y < m_width; ++y) {
			for (int x = 0; x < m_height; ++x) {
				Tile temp;
				if ((y == 1 && x==1) || (y==1 && x==2))
				{
					temp.init(TileType::TileTypeNextMap, nullptr, false, true, x, y, "test2", 2, 2);

				}
				else if ((y == 3 && x==3) || (y == 3 && x == 4))
				{
					temp.init(TileType::TileTypeBush, nullptr, false, true, x, y);
				}
				else if ((y == 3 && x == 7) || (y == 3 &&x == 8))
				{
					temp.init(TileType::TileTypeTree, nullptr, false, false, x, y);
				}
				else if (y == 0 && x==0)
				{
					temp.init(TileType::TileTypeOutRange, nullptr, false, false, x, y);
				}
				else
				{
					temp.init(TileType::TileTypeFloor, nullptr, false, true, x, y);
				}
				
				
				m_tiles.push_back(temp);
			}
		}
	}
	m_playerPositionX = m_playerStartPositionX;
	m_playerPositionY = m_playerStartPositionY;
}

TileType Map::getTileTypeFromIdex(int _x, int _y)
{
	if (_x < 0 || _y < 0)
		return TileType::TileTypeOutRange;
	if(_x >= m_width || _y >= m_height)
		return TileType::TileTypeOutRange;
	return m_tiles[_x + _y * m_width].m_Type;
}

Tile& Map::getSpecifyTile(int _blockPositionX, int _blockPositionY)
{
	return m_tiles[_blockPositionX + _blockPositionY * m_width];
}

void Map::setPlayerPosition(int _x, int _y)
{
	m_playerPositionX = _x;
	m_playerPositionY = _y;
}

void Map::render(HDC hdc)
{

	for (auto& tile : m_tiles) 
			tile.render(hdc);

}

void Map::update(float _deltaTime)
{
	
	for (auto& tile : m_tiles)
		tile.update(_deltaTime);

	
}

void Map::debugRender(HDC hdc)
{
	for (auto& tile : m_tiles)
		tile.debugRender(hdc);
}

void Map::afterRender(HDC hdc)
{
	for (auto& tile : m_tiles)
		tile.afterRender(hdc);
}

