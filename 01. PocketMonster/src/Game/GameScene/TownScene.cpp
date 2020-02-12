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
	
	m_map = MAPMANGER->findMap("TestTown");
	m_player->reLocate(m_map->getStartPositionX(), m_map->getStartPositionY());
	m_player->init();
	
	//menu
	m_menurect = UTIL::IRectMake(WINSIZEX / 2 + 50, 10, 450, 650);
	m_menuImg = IMAGEMANAGER->addImage("menuimg", "images/menu.bmp", 450, 650, true, RGB(255, 0, 255));

	return true;
}


void TownScene::update(float _deltaTime)
{
	m_player->update(_deltaTime);
	m_map->setPlayerPosition(m_player->getPlayerBlockX(), m_player->getPlayerBlockY());
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

	m_map->setisAfter(m_player->getisAfter());
	
}

void TownScene::render(HDC hdc)
{
	m_map->render(hdc);
	m_player->render(hdc);

	if (m_player->getisMenu())
	{
		m_menuImg->render(hdc, m_menurect.left, m_menurect.top);
	}
	//if (m_player->getisMenu())
	//{
	//	m_menuImg->render(hdc,m_player->getPlayRectX(),m_player->getPlayerBlockY());
	//}

}

void TownScene::afterRender(HDC hdc)
{
	
	m_map->afterRender(hdc);

	if (m_player->getisMenu())
	{
		m_menuImg->render(hdc, m_menurect.left, m_menurect.top);
	}
	

}

void TownScene::debugRender(HDC hdc)
{
	m_map->debugRender(hdc);
	m_player->debugRender(hdc);

	if (m_player->getisMenu())
	{
		UTIL::DrawColorRect(hdc, m_menurect, RGB(255, 255, 0), true);
	}
}

void TownScene::release()
{
}
