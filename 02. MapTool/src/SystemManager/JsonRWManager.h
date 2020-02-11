#pragma once
#include "Game/GameObject/Tile.h"
#include "Game/GameObject/Map.h"

class JsonRWManager
{
public:
	class Map MapDataRead(std::string _name);
	void MapDataWrite(std::string _name, std::vector<std::shared_ptr<class Tile>>& map, int width, int height, int startX, int startY);


private:
	DECLARE_SINGLE(JsonRWManager)
};

#define JSONMANAGER JsonRWManager::GetInst()

