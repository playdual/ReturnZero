#pragma once
#include"Game/GameTypes.h"
#include"Common/SystemManagers.h"

class Tile
{
public:
	Tile() {};
	~Tile() {};

	void init(TileType _type, class Image* _img, bool _isAfterRender, bool _isMovable, int _BlockPostionX, int _BlockPostionY);
	void update(float _deltaTime);
	void render(HDC hdc);
	void specialRender(HDC hdc);

public:
	void setColor();
	void setAttributeTile(TileAttribute _attribute);
	bool setStartBlock() { 
		isStartBlock = !isStartBlock; 
		return isStartBlock;
	}
	void resetAttribute();

	void pushInnerPocketMon(std::string _pocketName, int _pocketLevel);
	void setNextMap(std::string _mapName, int _startBlockPositionX, int _startBlockPositionY);
	void setNextMapActivate();

public:
	UTIL::IRECT m_absTile;
	UTIL::IRECT m_outputTile;
	bool isCanprint = false;

	TileType m_Type;
	Image* m_img = nullptr;
	bool isAfterRender;
	bool isMovable;
	bool isStartBlock = false;
	int m_BlockPositionX;
	int m_BlockPositionY;
	
	COLORREF color = RGB(255, 255, 255);

public:
	std::vector<std::pair<std::string, int>> m_innerPocketMonInfo;
	std::string m_nextMapName;
	std::string nextMapInfoStr;
	std::string tileImageKey;
	POINT m_nextMapStartIdx;
};