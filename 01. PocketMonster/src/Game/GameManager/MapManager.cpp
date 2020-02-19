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

	addDefaultNPC();
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
	std::string prevMapName;
	if(curMap != nullptr)
		prevMapName = curMap->m_mapName;
	auto map = MapList.find(mapKey);
	if (map == MapList.end()) {
		return curMap;
	}

	curMap = map->second;
	
	if (curMap->m_mapName == "Route01") {
		SOUNDMANAGER->stopChannel(Channel::eChannelBgm);
		SOUNDMANAGER->playSound("Route", Channel::eChannelBgm);
	}
	if (prevMapName == "Route01" && curMap->m_mapName == "TechoTown") {
		SOUNDMANAGER->stopChannel(Channel::eChannelBgm);
		SOUNDMANAGER->playSound("NewBarkTown", Channel::eChannelBgm);
	}
	return map->second;

}


TileType MapManager::getTileTypeFromIndex(int _x, int _y)
{
	if (curMap == nullptr)
		return TileType::TileTypeOutRange;
	return curMap->getTileTypeFromIdex(_x, _y);
}

std::string MapManager::getObjectNameFromIndex(int _x, int _y)
{
	return curMap->m_tiles[_x + _y * curMap->m_width].objName;
}

std::string MapManager::getNPCName(int _x, int _y)
{
	auto& NPCs = curMap->m_NPCs;

	for (auto& npc : NPCs) 
	{
		if (npc->m_blockPositionX == _x && npc->m_blockPositionY == _y) 
		{
			return npc->m_Name;
		}
	}
	return "";
}

bool MapManager::ActivateNPC(std::string _name, Direction _dir)
{
	auto& NPCs = curMap->m_NPCs;
	for (auto& npc : NPCs) {
		if (npc->m_Name == _name) {
			npc->activateNPC(_dir);
			curNpc = npc;
			return true;
		}
	}
	curNpc = nullptr;
	return false;
}

void MapManager::addDefaultNPC()
{
	auto npc1 = std::make_shared<NPC>(5, 4, "GrandFather", NPCEventType::NPCShop, true);
	Senario tempSenario;
	npc1->addSenario("default", tempSenario);

	auto npc2 = std::make_shared<NPC>(7, 4, "Mother");
	tempSenario.clear();
	tempSenario.push_back({ L"엄마 : 그래...", L"남자는 언젠가" });
	tempSenario.push_back({ L"모험을 떠나는 거야!", L"TV에서 그랬어..." });
	tempSenario.push_back({ L"오박사님이 널 찾고계셔!", L""});
	npc2->addSenario("default", tempSenario);

	auto npc3 = std::make_shared<NPC>(7, 4, "ProfO");
	tempSenario.clear();
	tempSenario.push_back({ L"오.. 레드군..", L"남자는 언젠가" });
	tempSenario.push_back({ L"모험을 떠나는 거야!", L"TV에서 그랬어..." });
	tempSenario.push_back({ L"너희 엄마가 널 찾고계셔!", L"" });
	npc3->addSenario("default", tempSenario);

	findMap("RivalHouse")->addNPC(npc1);
	findMap("RedHouse1F")->addNPC(npc2);
	findMap("ProfOHouse")->addNPC(npc3);
}
