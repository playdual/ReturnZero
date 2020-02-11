#pragma once
#include "Game/GameObject/Tile.h"

class JsonRWManager
{
public:
	void MapDataWrite(std::string _name, std::vector<std::shared_ptr<class Tile>>& map, int width, int height, int startX, int startY);
	void MapDataRead(std::string _name);


private:
	DECLARE_SINGLE(JsonRWManager)
};

#define JSONMANAGER JsonRWManager::GetInst()

