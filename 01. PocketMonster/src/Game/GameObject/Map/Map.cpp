#include "stdafx.h"
#include "Map.h"


void Map::init(char * _fileName)
{
	//for test
	if (_fileName == nullptr) {
		m_width = 15;
		m_height = 15;
		for (int i = 0; i < m_width; ++i) {
			for (int j = 0; j < m_height; ++j) {
				Tile temp;
				if ((i == 0 && j==0)||(i==0&& j==1))
				{
					temp.init(TileType::TileTypeNextMap, nullptr, false, false, j, i, "test2", 1, 2);

				}
				else if (i == 3 || i == 4)
				{
					if (j == 3 || j == 4) {
						temp.init(TileType::TileTypeBush, nullptr, false, true, j, i);
					}
					else if (j == 7 || j == 8) {
						temp.init(TileType::TileTypeTree, nullptr, false, false, j, i);
					}
					else
					{
						temp.init(TileType::TileTypeFloor, nullptr, false, true, j, i);
					}
				}
				else {
					temp.init(TileType::TileTypeFloor, nullptr, false, true, j, i);
				}
				m_tiles.push_back(temp);
			}
		}
	}
}

TileType Map::getTileTypeFromIdex(int _x, int _y)
{
	if (_x * m_width + _y * m_height > m_width * m_height)
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
