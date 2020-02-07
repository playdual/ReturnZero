#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
}

Tile::~Tile()
{
}

void Tile::init(TileType _type, Image* _img, bool _isAfterRender, bool _isMovable, int _BlockPositionX, int _BlockPositionY)
{
	m_Type = _type;
	m_img = _img;
	isAfterRender = _isAfterRender;
	isMovable = _isMovable;
	m_BlockPositionX = _BlockPositionX;
	m_BlockPositionY = _BlockPositionY;

	m_absTile.left = _BlockPositionX * TILE_WIDTH ;
	m_absTile.right = _BlockPositionX * TILE_WIDTH + TILE_WIDTH;
	m_absTile.top = _BlockPositionY * TILE_HEIGHT;
	m_absTile.bottom = _BlockPositionY * TILE_HEIGHT + TILE_HEIGHT;


}

void Tile::update(float _deltaTime)
{
	CAMERAMANAGER->rectInCamera(m_outputTile, m_absTile, isCanprint);

}

void Tile::render(HDC hdc)
{
	
}

void Tile::debugRender(HDC hdc)
{
	if (isCanprint)
	{

		UTIL::DrawColorRect(hdc, m_outputTile, false, RGB(255, 255, 255));

		//sprintf_s(str, "(%d , %d)", _BlockPositionX,_BlockPositionY);
		//TextOut(hdc, _BlockPositionX * TILE_WIDTH + TILE_OFFSETX + TILE_WIDTH / 2, _BlockPositionY * TILE_HEIGHT + TILE_OFFSETY + TILE_HEIGHT / 2, str, strlen(str));
	}
}
