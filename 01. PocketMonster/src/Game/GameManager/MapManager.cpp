#include "stdafx.h"
#include "MapManager.h"
DEFINITION_SINGLE(MapManager)

MapManager::MapManager() {}
MapManager::~MapManager() {}

void MapManager::init()
{
	std::vector<Tile> world;
	for (int i = 0; i < 30; ++i) {
		for (int j = 0; j < 30; ++j) {
			Tile temp;
			temp.init(TileType::TileTypeFloor, nullptr, false, true, j, i);
			world.push_back(temp);
		}
	}
	std::vector<Tile> house;
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j) {
			Tile temp;
			temp.init(TileType::TileTypeFloor, nullptr, false, true, j, i);
			house.push_back(temp);
		}
	}
	std::vector<Tile> test;
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j) {
			Tile temp;
			if (i == 3 || i == 4) {
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
			test.push_back(temp);
		}
	}
	MapList.insert(make_pair("world", world));
	MapList.insert(make_pair("house", house));
	MapList.insert(make_pair("test", test));
}

void MapManager::release()
{
	MapList.clear();
}


void MapManager::addMap(std::string mapKey, char* fileName)
{
	
}

std::vector<Tile>& MapManager::findMap(std::string mapKey)
{
	auto map = MapList.find(mapKey);
	if (map == MapList.end())
		return std::vector<Tile>();

	curMap = map->second;
	return map->second;
}

TileType MapManager::getTileTypeFromIndex(int _x, int _y)
{
	for (int i = 0; i < curMap.size(); ++i) {
		if (curMap[i].m_BlockPositionX == _x && curMap[i].m_BlockPositionY == _y) {
			return curMap[i].m_Type;
		}
	}
}
