#pragma once
#include"Game/GameTypes.h"
#include"Common/SystemManagers.h"
#include "Game/GameObject/Pocketmon/PocketMon.h"

class Tile
{
public:
	Tile();
	~Tile();

	void init(TileType _type, Image* _img, bool _isAfterRender, bool _isMovable, int _BlockPostionX, int _BlockPostionY
		, std::string _nextMapKey = "", int _x = 0, int _y = 0);
	void update(float _deltaTime);
	void render(HDC hdc);
	void debugRender(HDC hdc);
	void afterRender(HDC hdc);
	
	int getOutputTileY();
	std::string getNextMapKey() { return m_nextMapKey; }
	POINT getNextMapIdx() { return m_nextMapStartIdx; }

public:
	int m_BlockPositionX;
	int m_BlockPositionY;
	TileType m_Type;

private:
	UTIL::IRECT m_absTile;
	UTIL::IRECT m_outputTile;
	bool isCanprint = false;

	Image* m_img;
	Image* m_Tile1;
	Image* m_Bush1;
	Image* m_Tree1;
	bool isAfterRender;
	bool isMovable;

	//포켓몬의 키값 이름, 포켓몬의 래벨
	std::vector<std::pair<std::string, int>> m_innerPocketMonInfo;
	std::string m_nextMapKey;
	POINT m_nextMapStartIdx;
};
