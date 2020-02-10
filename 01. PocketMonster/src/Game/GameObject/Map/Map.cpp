#include "stdafx.h"
#include "Map.h"


void Map::init(char * _fileName)
{
	//for test
	if (_fileName == nullptr) {
		m_width = 15;
		m_height = 15;
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
}

TileType Map::getTileTypeFromIdex(int _x, int _y)
{
	if (_x < 0 || _y < 0)
		return TileType::TileTypeOutRange;
	if(_x >= m_width || _y >= m_height)
		return TileType::TileTypeOutRange;
	return m_tiles[_x + _y * m_height].m_Type;
}

Tile& Map::getSpecifyTile(int _blockPositionX, int _blockPositionY)
{
	return m_tiles[_blockPositionX + _blockPositionY * m_height];
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
