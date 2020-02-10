#pragma once

#include "Tile.h"

class Map
{
public:
	void init(char* _fileName);
	TileType getTileTypeFromIdex(int _x, int _y);
	std::vector<class Tile>& getTiles() { return m_tiles; }
	Tile& getSpecifyTile(int _blockPositionX, int _blockPositionY);

public:
	void render(HDC hdc);
	void update(float _deltaTime);
	void debugRender(HDC hdc);
	void afterRender(HDC hdc);

private:
	int m_width;
	int m_height;

	std::vector<Tile> m_tiles;
};