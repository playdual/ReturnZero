#include "stdafx.h"
#include "JsonRWManager.h"
#include "../../vendor/Json/inc/json.h"
#include <fstream>

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
		if (map[i]->m_nextMapKey != "") {
			tile["nextMapName"] = map[i]->m_nextMapKey;
			tile["nextMapX"] = map[i]->m_nextMapStartIdx.x;
			tile["nextMapY"] = map[i]->m_nextMapStartIdx.y;
		}		
		tile["innerPocketMonCnt"] = map[i]->m_innerPocketmonInfo.size();
		for (int j = 0; j < map[i]->m_innerPocketmonInfo.size(); ++j) {
			tile[innerPocketName + std::to_string(j)] = map[i]->m_innerPocketmonInfo[j].first;
			tile[innerPocketLevel + std::to_string(j)] = map[i]->m_innerPocketmonInfo[j].second;
		}
		root[s] = tile;
	}
	std::string filename = "Map/" + _name + ".json";
	std::ofstream output(filename, std::ios::out);
	output << root;
	output.close();

}

bool JsonRWManager::init()
{
	return true;
}

void JsonRWManager::release()
{
}

Map JsonRWManager::MapDataRead(std::string _name)
{
	std::string filename = "Map/" + _name + ".json";
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
		tile.m_BlockPositionX = root[s]["bPosX"].asInt();
		tile.m_BlockPositionY = root[s]["bPosY"].asInt();
		tile.tileImageKey = root[s]["imageKey"].asString();
		tile.m_nextMapKey = root[s]["nextMapName"].asString();
		if (tile.m_nextMapKey != "") {
			tile.m_nextMapStartIdx.x = root[s]["nextMapX"].asInt();
			tile.m_nextMapStartIdx.y = root[s]["nextMapY"].asInt();
		}

		int innerPocketCount = root[s]["innerPocketMonCnt"].asInt();
		for (int j = 0; j < innerPocketCount; ++j) {
			std::string name = root[s][innerPocketName + std::to_string(j)].asString();
			int level = root[s][innerPocketLevel + std::to_string(j)].asInt();
			tile.m_innerPocketmonInfo.push_back(std::make_pair(name, level));
		}
		map.m_tiles[i] = tile;
	}
	return map;
}

