#pragma once
#include "Game/GameObject/Map/Map.h"
#include "Game/GameObject/Map/Tile.h"

class JsonRWManager
{
public:
	bool init();
	void release();

public:
	class Map MapDataRead(std::string _name);
	void MapDataWrite(std::string _name, std::vector<std::shared_ptr<class Tile>>& map, int width, int height, int startX, int startY);


private:
	DECLARE_SINGLE(JsonRWManager)
};

#define JSONMANAGER JsonRWManager::GetInst()

