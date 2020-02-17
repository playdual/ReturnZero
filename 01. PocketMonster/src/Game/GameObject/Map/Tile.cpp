#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
}

Tile::~Tile()
{
}

void Tile::init()
{
	m_img = IMAGEMANAGER->findImage(tileImageKey);

	if (m_img->getMaxFrameX() > 2)
		isFrame = true;

	if (afterRenderImageKey != "") {
		m_afterRenderImg = IMAGEMANAGER->findImage(afterRenderImageKey);
		isAfterRender = true;
	}
	m_absTile.left = m_BlockPositionX * TILE_WIDTH;
	m_absTile.right = m_BlockPositionX * TILE_WIDTH + TILE_WIDTH;
	m_absTile.top = m_BlockPositionY * TILE_HEIGHT;
	m_absTile.bottom = m_BlockPositionY * TILE_HEIGHT + TILE_HEIGHT;

	switch (m_Type)
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
	case TileType::TileTypeNextMap:
		isMovable = true;
		break;
	case TileType::TileTypeOutRange:
		isMovable = false;
		break;
	case TileType::TileTypeNone:
		isMovable = false;
		break;
	}
}

void Tile::init(TileType _type, Image* _img, bool _isAfterRender, bool _isMovable, int _BlockPositionX, int _BlockPositionY, std::string _nextMapKey,
	int _x, int _y)
{
	//Image Null
	//m_NextMap1 = IMAGEMANAGER->addImage("NextMap1", "images/.bmp", TILE_WIDTH, TILE_HEIGHT, true, RGB(255, 0, 255));


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

	if (m_Type == TileType::TileTypeNextMap) {
		m_nextMapKey = _nextMapKey;
		m_nextMapStartIdx.x = _x;
		m_nextMapStartIdx.y = _y;
	}

}

void Tile::update(float _deltaTime)
{
	CAMERAMANAGER->rectInCamera(m_outputTile, m_absTile, isCanprint);
	framePast += _deltaTime;
	if (frameDelay < framePast) {
		curIdx++;
		if (curIdx > m_img->getMaxFrameX())
			curIdx = 0;
		framePast = 0.f;
	}
}

void Tile::render(HDC hdc)
{
	if (isCanprint)
	{
		//flower or water
		if (isFrame)
			m_img->frameRender(hdc, m_outputTile.left, m_outputTile.top, curIdx, 0);
		else
			m_img->render(hdc, m_outputTile.left, m_outputTile.top);
	}
}

void Tile::debugRender(HDC hdc)
{
	if (isCanprint)
	{
		switch (m_Type)
		{
		case TileType::TileTypeFloor:
			UTIL::DrawColorRect(hdc, m_outputTile, RGB(255, 255, 255), false);
			break;
		case TileType::TileTypeHouse:
			UTIL::DrawColorRect(hdc, m_outputTile, RGB(255, 0, 0), false);
			break;
		case TileType::TileTypeNextMap:
			UTIL::DrawColorRect(hdc, m_outputTile, RGB(0, 0, 0), false);
			break;
		case TileType::TileTypeBush:
			UTIL::DrawColorRect(hdc, m_outputTile, RGB(0, 255, 0), false);
			break;
		case TileType::TileTypeTree:
			UTIL::DrawColorRect(hdc, m_outputTile, RGB(0, 0, 255), false);
			break;
		case TileType::TileTypeObject:
			UTIL::DrawColorRect(hdc, m_outputTile, RGB(10, 150, 245), true);
			break;
		case TileType::TileTypeOutRange:
			UTIL::DrawColorRect(hdc, m_outputTile, RGB(255, 0, 0), false);
			break;
		}
	}
}

void Tile::afterRender(HDC hdc)
{
	if (isCanprint && isAfterRender) {
		if (m_afterRenderImg)
			m_afterRenderImg->render(hdc, m_outputTile.left, m_outputTile.top);
	}

}

int Tile::getOutputTileY()
{
	return m_outputTile.centerY;
}

std::pair<std::string, int> Tile::getInnerPocketMon()
{
	if (m_innerPocketmonInfo.size() == 0) {
		return { "", 0 };
	}
	else {
		int returnIdex = UTIL::GetRndInt(m_innerPocketmonInfo.size());
		return m_innerPocketmonInfo[returnIdex];
	}
}
