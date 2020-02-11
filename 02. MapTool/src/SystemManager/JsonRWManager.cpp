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
		if (map[i]->m_nextMapName != "") {
			tile["nextMapName"] = map[i]->m_nextMapName;
			tile["nextMapX"] = map[i]->m_nextMapStartIdx.x;
			tile["nextMapY"] = map[i]->m_nextMapStartIdx.y;
		}		
		tile["innerPocketMonCnt"] = map[i]->m_innerPocketMonInfo.size();
		for (int j = 0; j < map[i]->m_innerPocketMonInfo.size(); ++j) {
			tile[innerPocketName + std::to_string(j)] = map[i]->m_innerPocketMonInfo[j].first;
			tile[innerPocketLevel + std::to_string(j)] = map[i]->m_innerPocketMonInfo[j].second;
		}
		root[s] = tile;
	}
	std::string filename = _name + ".json";
	std::ofstream output(filename, std::ios::out);
	output << root;
	output.close();

}

void JsonRWManager::MapDataRead(std::string _name)
{
}

