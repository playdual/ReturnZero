#include "stdafx.h"
#include "MapToolScene.h"

bool MapToolScene::init()
{
	for (int i = 0; i < 300; ++i) {
		for (int j = 0; j < 300; ++j) {
			auto tile = std::make_shared<Tile>();
			tile->init(TileType::TileTypeFloor, nullptr, false, true, j, i);
			m_Tiles.push_back(tile);
		}
	}
	return true;
}

void MapToolScene::update(float _deltaTime)
{
}

void MapToolScene::release()
{
}

void MapToolScene::render(HDC hdc)
{
	for (auto& tile : m_Tiles) {
		tile->render(hdc);
	}
}

void MapToolScene::afterRender(HDC hdc)
{
}

void MapToolScene::debugRender(HDC hdc)
{
}
