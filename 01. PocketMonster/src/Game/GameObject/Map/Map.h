#pragma once

#include "Tile.h"

class Map
{
public:
	void init(char* _fileName);
	TileType getTileTypeFromIdex(int _x, int _y);
	std::vector<class Tile>& getTiles() { return m_tiles; }
	Tile& getSpecifyTile(int _blockPositionX, int _blockPositionY);
	void setPlayerPosition(int _x, int _y);
	int getStartPositionX() { return m_playerStartPositionX; }
	int getStartPositionY() { return m_playerStartPositionY; }
	void setisAfter(bool isAfterValue) { isAfter = isAfterValue; }


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
	//tilesVector
};