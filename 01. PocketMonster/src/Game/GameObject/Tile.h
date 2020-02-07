#pragma once
#include"Game/GameTypes.h"
#include"Common/SystemManagers.h"
class Tile
{
public:
	Tile();
	~Tile();

	void init(TileType _type, Image* _img, bool _isAfterRender, bool _isMovable, int _BlockPostionX, int _BlockPostionY);
	void update(float _deltaTime);
	void render(HDC hdc);
	void debugRender(HDC hdc);


private:
	UTIL::IRECT m_absTile;
	UTIL::IRECT m_outputTile;
	bool isCanprint = false;

	TileType m_Type;
	Image* m_img;
	bool isAfterRender;
	bool isMovable;
	int m_BlockPositionX;
	int m_BlockPositionY;


};