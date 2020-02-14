#include "stdafx.h"
#include "JsonRWManager.h"
#include "../../vendor/Json/inc/json.h"
#include "Game/GameObject/Map.h"
#include "Game/GameObject/Tile.h"

DEFINITION_SINGLE(JsonRWManager)

JsonRWManager::JsonRWManager()
{
}

JsonRWManager::~JsonRWManager()
{
}


void JsonRWManager::MapDataWrite(std::string _name, std::vector<std::shared_ptr<Tile>>& map, 
	int width, int height, int startX, int startY)
{
	Json::Value root;
	root["mapName"] = _name;
	root["startX"] = startX;
	root["startY"] = startY;
	root["mapWidth"] = width;
	root["mapHeight"] = height;
	std::string innerPocketName = "innerPocketName-";
	std::string innerPocketLevel = "innerPocketLevel-";
	for (int i = 0; i < map.size(); ++i) {
		Json::Value tile;
		std::string s = std::to_string(i);
		tile["type"] = (int)map[i]->m_Type;
		tile["bPosX"] = map[i]->m_BlockPositionX;
		tile["bPosY"] = map[i]->m_BlockPositionY;
		tile["imageKey"] = map[i]->tileImageKey;
		tile["nextMapName"] = "";
		if (map[i]->m_nextMapName != "") {
			tile["nextMapName"] = map[i]->m_nextMapName;
			tile["nextMapX"] = map[i]->m_nextMapStartIdx.x;
			tile["nextMapY"] = map[i]->m_nextMapStartIdx.y;
		}
		tile["afterRenderImageKey"] = "";
		if (map[i]->m_afterImage) {
			tile["afterRenderImageKey"] = map[i]->afterRenderImageKey;
		}
		if (map[i]->m_Type == TileType::TileTypeObject) {
			tile["objName"] = map[i]->objName;
		}
		tile["innerPocketMonCnt"] = map[i]->m_innerPocketMonInfo.size();
		for (int j = 0; j < map[i]->m_innerPocketMonInfo.size(); ++j) {
			tile[innerPocketName + std::to_string(j)] = map[i]->m_innerPocketMonInfo[j].first;
			tile[innerPocketLevel + std::to_string(j)] = map[i]->m_innerPocketMonInfo[j].second;
		}
		root[s] = tile;
	}
	std::string filename = "../01. PocketMonster/Map/" + _name + ".json";
	std::ofstream output(filename, std::ios::out);
	output << root;
	output.close();

}

Map JsonRWManager::MapDataRead(std::string _name)
{
	std::string filename = "../01. PocketMonster/Map/" + _name + ".json";
	std::ifstream input(filename, std::ios::binary);

	Json::Value root;
	Json::Reader reader;
	reader.parse(input, root);
	input.close();

	Map map;

	std::string mapName = root["mapName"].asString();

	int width = root["mapWidth"].asInt();
	int height = root["mapHeight"].asInt();
	map.m_playerStartPositionX = root["startX"].asInt();
	map.m_playerStartPositionY = root["startY"].asInt();

	int size = width * height;
	map.m_height = height;
	map.m_width = width;
	map.m_tiles.resize(size);

	std::string innerPocketName = "innerPocketName-";
	std::string innerPocketLevel = "innerPocketLevel-";
	for(int i = 0 ; i < size; ++i) {
		std::string s = std::to_string(i);
		Tile tile;
		tile.m_Type = (TileType)root[s]["type"].asInt();
		if (tile.m_Type == TileType::TileTypeObject) {
			tile.objName = root[s]["objName"].asString();
		}
		tile.m_BlockPositionX = root[s]["bPosX"].asInt();
		tile.m_BlockPositionY = root[s]["bPosY"].asInt();
		tile.tileImageKey = root[s]["imageKey"].asString();
		tile.afterRenderImageKey = root[s]["afterRenderImageKey"].asString();

		tile.m_nextMapName = root[s]["nextMapName"].asString();
		if (tile.m_nextMapName != "") {
			tile.m_nextMapStartIdx.x = root[s]["nextMapX"].asInt();
			tile.m_nextMapStartIdx.y = root[s]["nextMapY"].asInt();
		}
		int innerPocketCount = root[s]["innerPocketMonCnt"].asInt();
		for (int j = 0; j < innerPocketCount; ++j) {
			std::string name = root[s][innerPocketName + std::to_string(j)].asString();
			int level = root[s][innerPocketLevel + std::to_string(j)].asInt();
			tile.m_innerPocketMonInfo.push_back(std::make_pair(name, level));
		}
		map.m_tiles[i] = tile;
	}
	return map;
}

