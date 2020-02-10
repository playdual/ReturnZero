#include "stdafx.h"
#include "TownScene.h"
#include "Common/GameManagers.h"

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

	if (KEYMANAGER->isOnceKeyDown(GAME_MENU)) {
		SCENEMANAGER->scenePush("inven");
	}

	//배틀
	if (m_player->getisBattle())
	{
		BATTLEMANAGER->battleStart();
		m_player->BattleEnd();
	}

	if (m_player->getisChangeMap()) 
	{
		auto tile = MAPMANGER->getCurMap()->getSpecifyTile(m_player->getPlayerBlockX(), m_player->getPlayerBlockY());
		m_map = MAPMANGER->findMap(tile.getNextMapKey());
		m_player->reLocate(tile.getNextMapIdx().x, tile.getNextMapIdx().y);
		m_player->MoveSetZero();
		m_player->isNotChangeMap();
	}

	
}

void TownScene::render(HDC hdc)
{
	m_map->render(hdc);
	m_player->render(hdc);
	
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
