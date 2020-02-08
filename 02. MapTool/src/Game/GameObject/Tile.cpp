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
	if (isCanprint) {
		if (m_img) {
			m_img->render(hdc, m_outputTile.left, m_outputTile.top);
		}
		else {
			UTIL::DrawColorRect(hdc, m_outputTile, true, color);
		}	
	}
}

void Tile::setColor()
{
	if (isCanprint) {
		if (color == RGB(255, 255, 255)) {
			color = RGB(255, 0, 255);
		}
		else {
			color = RGB(255, 255, 255);
		}
	}
}

void Tile::setAttributeTile(TileAttribute _attribute)
{
	m_Type = _attribute.type;
	switch (_attribute.type)
	{
	case TileType::TileTypeFloor:
		isMovable = true;
		break;
	case TileType::TileTypeHouse:
		isMovable = false;
		break;
	case TileType::TileTypeBush:
		isMovable = true;
		break;
	case TileType::TileTypeTree:
		isMovable = false;
		break;
	}
	isAfterRender = _attribute.isAfterRender;
	m_img = IMAGEMANAGER->findImage(_attribute.tileKeyname);
}

void Tile::resetAttribute()
{
	SAFE_DELETE(m_img);
	isMovable = false;
	isAfterRender = false;
	m_Type = TileType::TileTypeNone;

}
