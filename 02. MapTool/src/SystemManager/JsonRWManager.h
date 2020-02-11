#pragma once
#include "Game/GameObject/Tile.h"
class JsonRWManager
{
public:
	void MapDataWrite(std::string _name, Map& map);
	Map MapDataRead(std::string _name);


private:
	DECLARE_SINGLE(JsonRWManager)
};

#define JONMANAGER JsonRWManager::GetInst()

