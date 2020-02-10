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
	void afterRender(HDC hdc);

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



};