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
	
	m_map = MAPMANGER->findMap("test");
	return true;
}


void TownScene::update(float _deltaTime)
{
	m_player->update(_deltaTime);
	m_map->update(_deltaTime);
}

void TownScene::render(HDC hdc)
{
	
}

void TownScene::afterRender(HDC hdc)
{
}

void TownScene::debugRender(HDC hdc)
{
	m_map->debugRender(hdc);
	m_player->debugRender(hdc);
}

void TownScene::release()
{
}
