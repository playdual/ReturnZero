#include "stdafx.h"
#include "Tile.h"

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
	if (TileType::TileTypeBush != m_Type)
		m_innerPocketMonInfo.clear();
	if (m_Type != TileType::TileTypeNextMap) {
		m_nextMapName = "";
		m_nextMapStartIdx.x = -1;
		m_nextMapStartIdx.y = -1;
	}
}

void Tile::render(HDC hdc)
{
	if (isCanprint) {
		if (m_img) {
			m_img->render(hdc, m_outputTile.left, m_outputTile.top);
		}
		else {
			UTIL::DrawColorRect(hdc, m_outputTile, color, true);
		}	
		if (m_innerPocketMonInfo.size()) {
			for (int i = 0; i < m_innerPocketMonInfo.size(); ++i) {
				UTIL::PrintText(hdc, m_innerPocketMonInfo[i].first.c_str(), "명조",
					m_outputTile.left + 5, m_outputTile.top + i * 20, 10, RGB(0, 0, 0), true);
			}
		}
	}
}

void Tile::specialRender(HDC hdc)
{
	if (isCanprint) {
		if (TileType::TileTypeNextMap == m_Type) {
			UTIL::DrawColorRect(hdc, UTIL::IRECT(m_outputTile.left, m_outputTile.top,
				m_outputTile.left + 10, m_outputTile.top + 10),
				RGB(0, 0, 0), true);
			UTIL::PrintText(hdc, nextMapInfoStr.c_str(), "명조",
				m_outputTile.left + 5, m_outputTile.top, 10, RGB(0, 0, 0), true);
		}
		if (isStartBlock) {
			UTIL::DrawColorCircle(hdc, UTIL::Circle(m_outputTile.left + 5, m_outputTile.top + 5, 5), RGB(255, 0, 255), true);
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
	case TileType::TileTypeNextMap:
		isMovable = true;
		break;
	case TileType::TileTypeNone:
		resetAttribute();
		break;
	}
	isAfterRender = _attribute.isAfterRender;
	if (_attribute.tileKeyname != "") {
		m_img = IMAGEMANAGER->findImage(_attribute.tileKeyname);
		tileImageKey = _attribute.tileKeyname;
		tileImageKey.pop_back();
	}	
}

void Tile::resetAttribute()
{
	m_img = nullptr;
	isMovable = false;
	isAfterRender = false;
	isStartBlock = false;
}

void Tile::pushInnerPocketMon(std::string _pocketName, int _pocketLevel)
{
	if (m_Type == TileType::TileTypeBush) {
		if (_pocketName == "") {
			m_innerPocketMonInfo.clear();
		}
		for (int i = 0; i < m_innerPocketMonInfo.size(); ++i)
			if (m_innerPocketMonInfo[i].first == _pocketName)
				return;
		m_innerPocketMonInfo.push_back(std::make_pair(_pocketName, _pocketLevel));
	}
}

void Tile::setNextMap(std::string _mapName, int _startBlockPositionX, int _startBlockPositionY)
{
	if (m_Type == TileType::TileTypeNextMap) {
		if (m_nextMapName == "") {
			m_nextMapName = _mapName;
			m_nextMapStartIdx.x = _startBlockPositionX;
			m_nextMapStartIdx.y = _startBlockPositionY;
			nextMapInfoStr += _mapName + " : " + std::to_string(_startBlockPositionX) + " " + std::to_string(_startBlockPositionY);
		}
	}
}

void Tile::setNextMapActivate()
{
	m_Type = TileType::TileTypeNextMap;
}

