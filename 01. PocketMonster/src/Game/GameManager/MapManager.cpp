#include "stdafx.h"
#include "MapManager.h"
#include "Common/SystemManagers.h"
DEFINITION_SINGLE(MapManager)

MapManager::MapManager() {}
MapManager::~MapManager() {}

void MapManager::init()
{
	addMap("TestTown", "TestTown");
	addMap("TestTown2", "TestTown2");
}

void MapManager::release()
{
	MapList.clear();
}


void MapManager::addMap(std::string mapKey, std::string fileName)
{
	std::shared_ptr<Map> map = std::make_shared<Map>(JSONMANAGER->MapDataRead(fileName));
	MapList.insert(std::make_pair(mapKey, map));
}

std::shared_ptr<Map> MapManager::findMap(std::string mapKey)
{
	auto map = MapList.find(mapKey);
	if (map == MapList.end())
		return nullptr;

	curMap = map->second;
	return map->second;
}

TileType MapManager::getTileTypeFromIndex(int _x, int _y)
{
	if (curMap == nullptr)
		return TileType::TileTypeOutRange;
	return curMap->getTileTypeFromIdex(_x, _y);
}
