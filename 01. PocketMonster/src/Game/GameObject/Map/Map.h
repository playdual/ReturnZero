﻿#pragma once

#include "Tile.h"
#include "Game/GameObject/Character/NPC.h"

class Map
{
public:
	Map();
	Map(const Map& map);
	~Map();

public:
	void init(char* _fileName);
	TileType getTileTypeFromIdex(int _x, int _y);
	std::vector<class Tile>& getTiles() { return m_tiles; }
	Tile& getSpecifyTile(int _blockPositionX, int _blockPositionY);
	void setPlayerPosition(int _x, int _y);
	int getStartPositionX() { return m_playerStartPositionX; }
	int getStartPositionY() { return m_playerStartPositionY; }
	void setisAfter(bool isAfterValue) { isAfter = isAfterValue; }
	void addNPC(std::shared_ptr<NPC> _npc) { m_NPCs.push_back(_npc); }

public:
	void render(HDC hdc);
	void update(float _deltaTime);
	void debugRender(HDC hdc);
	void afterRender(HDC hdc);

private:
	int m_width;
	int m_height;

	int m_playerPositionX;
	int m_playerPositionY;

	int m_playerStartPositionX;
	int m_playerStartPositionY;

	bool isAfter=true;
	std::vector<Tile> m_tiles;
	std::string m_mapName;
	std::vector<std::shared_ptr<NPC>> m_NPCs;

	//tilesVector
	friend class JsonRWManager;
	friend class MapManager;
};
