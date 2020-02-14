#pragma once
#include "Tile.h"

class Map
{
public:
	Map() {};
	~Map() {};

public:
	void init(std::string _fileName);
	TileType getTileTypeFromIdex(int _x, int _y);
	std::vector<class Tile>& getTiles() { return m_tiles; }

public:
	void render(HDC hdc);
	void update(float _deltaTime);
	void debugRender(HDC hdc);
	void afterRender(HDC hdc);

public:
	int m_width;
	int m_height;
	int m_playerStartPositionX;
	int m_playerStartPositionY;

	std::vector<Tile> m_tiles;
};