#include "stdafx.h"
#include "TownScene.h"

TownScene::TownScene()
{
}


TownScene::~TownScene()
{
}

bool TownScene::init()
{
	//player init
	m_player = std::make_shared<player>();
	m_player->reLocate(3, 3);
	m_player->init();
	
	//map init
	for (int y = 0; y < 15; ++y) {
		for (int x = 0; x < 15; ++x) {
			Tile temptile;
			temptile.init(TileType::TileTypeFloor, nullptr, false, true, x, y);
			m_map.push_back(temptile);
		}
	}
	return true;
}


void TownScene::update(float _deltaTime)
{
	m_player->update(_deltaTime);
	for (auto& Tile : m_map)
		Tile.update(_deltaTime);
}

void TownScene::render(HDC hdc)
{
	
}

void TownScene::afterRender(HDC hdc)
{
}

void TownScene::debugRender(HDC hdc)
{
	for (auto& Tile : m_map)
		Tile.debugRender(hdc);
	m_player->debugRender(hdc);
}

void TownScene::release()
{
}
