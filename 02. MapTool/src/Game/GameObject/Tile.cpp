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

	m_absTile.left = _BlockPositionX * TILE_WIDTH;
	m_absTile.right = _BlockPositionX * TILE_WIDTH + TILE_WIDTH;
	m_absTile.top = _BlockPositionY * TILE_HEIGHT;
	m_absTile.bottom = _BlockPositionY * TILE_HEIGHT + TILE_HEIGHT;
	
}

void Tile::update(float _deltaTime)
{
	CAMEARAMANAGER->setRelativePosition(m_absTile, m_outputTile, isCanprint);
}

void Tile::render(HDC hdc)
{
	UTIL::DrawColorRect(hdc, m_absTile, true, RGB(255, 0, 0));
}
