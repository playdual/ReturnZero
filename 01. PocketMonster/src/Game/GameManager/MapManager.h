#pragma once
#include "Game/GameObject/Map/Map.h"
#include "Game/GameObject/Character/player.h"

class MapManager
{
public:
	void init();
	void release();

public:
	void addMap(std::string mapKey, std::string fileName);
	std::shared_ptr<class Map> findMap(std::string mapKey);
	std::shared_ptr<Map> getCurMap() { return curMap; }
	Tile& getNextMapKey(int _x, int _y) { return curMap->getSpecifyTile(_x, _y); }
	std::string getCurMapName() { return curMap->m_mapName; }

public:
	TileType getTileTypeFromIndex(int _x, int _y);
	std::string getObjectNameFromIndex(int _x, int _y);
	std::string getNPCName(int _x, int _y);
	std::shared_ptr<NPC> getCurNpc() { return curNpc; }
	std::shared_ptr<player> getPlayer() { return m_Player; }
	void connectPlayerInfo(std::shared_ptr<player> _player) { m_Player = _player; }
	bool ActivateNPC(std::string _name, Direction _dir);

private:
	void addDefaultNPC();

private:
	std::map<std::string, std::shared_ptr<Map>> MapList;
	std::shared_ptr<Map> curMap;
	std::shared_ptr<NPC> curNpc;
	std::shared_ptr<player> m_Player;

private:
	DECLARE_SINGLE(MapManager)
};

#define MAPMANGER MapManager::GetInst()
