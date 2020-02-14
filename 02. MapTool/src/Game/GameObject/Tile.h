#pragma once
#include"Game/GameTypes.h"
#include"Common/SystemManagers.h"

class Tile
{
public:
	Tile() {};
	~Tile() {};

	void init(TileType _type, std::string _imgKey, int _BlockPostionX, int _BlockPostionY);
	void init();
	void update(float _deltaTime);
	void render(HDC hdc);
	void specialRender(HDC hdc);
	void afterRender(HDC hdc);

public:
	void setColor();
	void setAttributeTile(TileAttribute _attribute);
	bool setStartBlock() { 
		isStartBlock = !isStartBlock; 
		return isStartBlock;
	}
	void resetAttribute();
	void resetInnerAttribute();

	void setObj(std::string _objName);
	void pushInnerPocketMon(std::string _pocketName, int _pocketLevel);
	void setNextMap(std::string _mapName, int _startBlockPositionX, int _startBlockPositionY);
	void setNextMapActivate();
	void setTileType(TileType _type) {
		m_Type = _type;
	}

public:
	UTIL::IRECT m_absTile;
	UTIL::IRECT m_outputTile;
	bool isCanprint = false;

	TileType m_Type;
	Image* m_img = nullptr;
	Image* m_afterImage = nullptr;
	bool hasAfterRender;
	bool isStartBlock = false;
	int m_BlockPositionX;
	int m_BlockPositionY;
	
	COLORREF color = RGB(255, 255, 255);

public:
	std::vector<std::pair<std::string, int>> m_innerPocketMonInfo;
	std::string m_nextMapName;
	std::string nextMapInfoStr;
	std::string tileImageKey;
	std::string afterRenderImageKey;
	std::string objName;
	POINT m_nextMapStartIdx;
};