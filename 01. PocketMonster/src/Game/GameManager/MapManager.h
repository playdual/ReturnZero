#pragma once
#include "Game/GameObject/Tile.h"

class MapManager
{
public:
	void init();
	void release();

public:
	void addMap(std::string mapKey, char* fileName);
	std::vector<Tile>& findMap(std::string mapKey);
	std::vector<Tile>& getCurMap() { return curMap; }


private:
	std::map<std::string, std::vector<Tile>> MapList;
	std::vector<Tile> curMap;

private:
	DECLARE_SINGLE(MapManager)
};

#define MAPMANGER MapManager::GetInst()
