﻿#include "stdafx.h"
#include "Tile.h"

void Tile::init()
{
	m_absTile.left = m_BlockPositionX * TILE_WIDTH;
	m_absTile.right = m_BlockPositionX * TILE_WIDTH + TILE_WIDTH;
	m_absTile.top = m_BlockPositionY * TILE_HEIGHT;
	m_absTile.bottom = m_BlockPositionY * TILE_HEIGHT + TILE_HEIGHT;

	if (tileImageKey != "") {
		m_img = IMAGEMANAGER->findImage(tileImageKey + 't');
	}

	if (afterRenderImageKey != "") {
		hasAfterRender = true;
		m_afterImage = IMAGEMANAGER->findImage(afterRenderImageKey + 't');
	}
	if (m_nextMapName != ""){
		nextMapInfoStr = m_nextMapName + " " + std::to_string(m_nextMapStartIdx.x) + 
			" " + std::to_string(m_nextMapStartIdx.y);
	}
}

void Tile::init(TileType _type, std::string _imgKey, int _BlockPositionX, int _BlockPositionY)
{
	m_Type = _type;
	if (_imgKey != "") {
		m_img = IMAGEMANAGER->findImage(_imgKey);
		_imgKey.pop_back();
		tileImageKey = _imgKey;
	}
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
	else if (m_nextMapName == "") {
		nextMapInfoStr = "";
	}
	/*if (m_img == nullptr) {
		tileImageKey = "";
	}
	if (!hasAfterRender) {
		afterRenderImageKey = "";
		m_afterImage = nullptr;
	}*/
}

void Tile::render(HDC hdc)
{
	if (isCanprint) {
		if (m_img) {
			m_img->render(hdc, m_outputTile.left, m_outputTile.top, 0, 0, 100, 100);
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
		DrawRect(hdc, m_outputTile, true);
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
	if (_attribute.type == TileType::TileTypeNone) {
		m_Type = _attribute.type;
		resetAttribute();
	}
	else {
		hasAfterRender = _attribute.isAfterRender;
		if (!hasAfterRender)
			m_Type = _attribute.type;
		if (_attribute.tileKeyname != "") {
			if (hasAfterRender) {
				m_afterImage = IMAGEMANAGER->findImage(_attribute.tileKeyname);
				afterRenderImageKey = _attribute.tileKeyname;
				afterRenderImageKey.pop_back();
			}
			else {
				m_img = IMAGEMANAGER->findImage(_attribute.tileKeyname);
				tileImageKey = _attribute.tileKeyname;
				tileImageKey.pop_back();
			}
		}
		else {
			m_img = nullptr;
			tileImageKey = "";
		}
	}
}

void Tile::resetAttribute()
{
	m_img = nullptr;
	m_afterImage = nullptr;
	hasAfterRender = false;
	isStartBlock = false;
	m_nextMapName = "";
	tileImageKey = "";
	afterRenderImageKey = "";
	m_nextMapStartIdx.x = 0;
	m_nextMapStartIdx.y = 0;
	objName = "";
	m_innerPocketMonInfo.clear();
}

void Tile::resetInnerAttribute()
{
	isStartBlock = false;

	m_nextMapName = "";
	afterRenderImageKey = "";
	objName = "";
	m_afterImage = nullptr;
	hasAfterRender = false;
	m_nextMapStartIdx.x = 0;
	m_nextMapStartIdx.y = 0;
	m_innerPocketMonInfo.clear();
}

void Tile::setObj(std::string _objName)
{
	m_Type = TileType::TileTypeObject;
	objName = _objName;
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

void Tile::afterRender(HDC hdc) 
{
	if (isCanprint && hasAfterRender) {
		if (m_afterImage) {
			m_afterImage->render(hdc, m_outputTile.left, m_outputTile.top);
			UTIL::PrintText(hdc, "after!", "명조", m_outputTile.left + 70, m_outputTile.top + 90, 10);
		}
	}
	if (isCanprint && tileImageKey != "") {
		UTIL::PrintText(hdc, tileImageKey.c_str(), "명조", m_outputTile.left, m_outputTile.top + 80, 10);
	}
	if (isCanprint && objName != "") {
		UTIL::PrintText(hdc, objName.c_str(), "명조", m_outputTile.left + 10, m_outputTile.top + 20, 15, false, RGB(0, 0, 0));
	}

	if (isCanprint) {
		switch (m_Type)
		{
		case TileType::TileTypeFloor:
			UTIL::PrintText(hdc, "Floor", "명조", m_outputTile.left, m_outputTile.top + 90, 10);
			break;
		case TileType::TileTypeHouse:
			UTIL::PrintText(hdc, "House", "명조", m_outputTile.left, m_outputTile.top + 90, 10);
			break;
		case TileType::TileTypeBush:
			UTIL::PrintText(hdc, "Bush", "명조", m_outputTile.left, m_outputTile.top + 90, 10);
			break;
		case TileType::TileTypeTree:
			UTIL::PrintText(hdc, "Tree", "명조", m_outputTile.left, m_outputTile.top + 90, 10);
			break;
		case TileType::TileTypeNextMap:
			UTIL::PrintText(hdc, "NextMap", "명조", m_outputTile.left, m_outputTile.top + 90, 10);
			break;
		case TileType::TileTypeObject:
			UTIL::PrintText(hdc, "object", "명조", m_outputTile.left, m_outputTile.top + 90, 10);
			break;
		case TileType::TileTypeOutRange:
			UTIL::PrintText(hdc, "OutRange", "명조", m_outputTile.left, m_outputTile.top + 90, 10);
			break;
		}
	}
}