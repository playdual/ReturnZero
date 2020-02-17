#include "stdafx.h"
#include "MapManager.h"
#include "Common/SystemManagers.h"
DEFINITION_SINGLE(MapManager)

MapManager::MapManager() {}
MapManager::~MapManager() {}

void MapManager::init()
{
	addMap("TechoTown", "TechoTown");
	addMap("RedHouse1F", "RedHouse1F");
	addMap("RedHouse2F", "RedHouse2F");
	addMap("RivalHouse", "RivalHouse");
	addMap("ProfOHouse", "ProfOHouse");
	addMap("Route01", "Route01");
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
	if (map == MapList.end()) {
		return curMap;
	}

	curMap = map->second;
	return map->second;
}

TileType MapManager::getTileTypeFromIndex(int _x, int _y)
{
	if (curMap == nullptr)
		return TileType::TileTypeOutRange;
	return curMap->getTileTypeFromIdex(_x, _y);
}
