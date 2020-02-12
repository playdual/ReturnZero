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
	m_menurect = UTIL::IRectMake(WINSIZEX / 2 + 200, 10, 300, 530);
	m_menuImg = IMAGEMANAGER->addImage("menuimg", "images/menu.bmp", 300, 530, true, RGB(255, 0, 255));

	m_IndexMenuRect = UTIL::IRectMake(WINSIZEX / 2 + 230, 70, 15, 20);
	m_IndexMenuImg = IMAGEMANAGER->addImage("menuindeximg", "images/menuindex.bmp", 30, 50, true, RGB(255, 0, 255));
	//기본 메뉴 인덱스
	m_menuIndex = 0;
	//최대 메뉴갯수
	

	Menu.push_back(MenuBar("리포트", 3));
	Menu.push_back(MenuBar("설정", 4));
	Menu.push_back(MenuBar("가방", 1));
	Menu.push_back(MenuBar("닫기", 5));
	Menu.push_back(MenuBar("플레이어", 2));
	
	menuUpdate();
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

	//야생배틀
	if (m_player->getisBattle())
	{
		Tile& curTile = m_map->getSpecifyTile(m_player->getPlayerBlockX(), m_player->getPlayerBlockY());
		auto innerPocketmon = curTile.getInnerPocketMon();
		BATTLEMANAGER->battleStart(m_player, nullptr, innerPocketmon.first, innerPocketmon.second);
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

	if (m_player->getisMenu())
	{
		
		if (KEYMANAGER->isOnceKeyDown(P1_DOWN))
		{
			m_menuIndex++;
		}
		else if (KEYMANAGER->isOnceKeyDown(P1_UP))
		{
			m_menuIndex--;
		}

		if (m_menuIndex < 0)
		{
			m_menuIndex = m_menuIndexMax;
		}
		else if (m_menuIndex > m_menuIndexMax)
		{
			m_menuIndex = 0;
		}

		//메뉴인덱스(화살표)
		m_IndexMenuRect = UTIL::IRectMake(WINSIZEX / 2 + 230, 70 + m_menuIndex * 70, 15, 20);

		//포켓몬 메뉴바 추가 삭제 알고리즘
		if (m_player->getCountPocketMon() == 0) {
			delMenu("포켓몬");
			isPocketmonMenuOn = false;
		}
		else {
			if (isPocketmonMenuOn == false) {
				addMenu(MenuBar("포켓몬", 0));
				isPocketmonMenuOn = true;
			}
		}

		//메뉴끄기
		if (Menu[m_menuIndex].menuName == "포켓몬" && KEYMANAGER->isOnceKeyDown(P1_Z))
		{
			SCENEMANAGER->scenePush("PocketmonBagScene");
		}


		if (Menu[m_menuIndex].menuName == "닫기" && KEYMANAGER->isOnceKeyDown(P1_Z))
		{
			m_player->setisMenu(false);
		}

		
	}

	menuUpdate();
	
}

void TownScene::render(HDC hdc)
{
	m_map->render(hdc);
	m_player->render(hdc);


}

void TownScene::afterRender(HDC hdc)
{
	m_map->afterRender(hdc);

	//메뉴
	if (m_player->getisMenu())
	{
		m_menuImg->render(hdc, m_menurect.left, m_menurect.top);

		m_IndexMenuImg->render(hdc, m_IndexMenuRect.left, m_IndexMenuRect.top);

		int cnt = 0;
		for (auto it = Menu.begin(); it != Menu.end(); ++it)
		{
			UTIL::PrintText(hdc, (*it).menuName.c_str(), "소야바른9", WINSIZEX / 2 + 270, 65 + cnt * 70, 65, RGB(0, 0, 0));
			cnt++;
		}
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

void TownScene::addMenu(MenuBar _newMenu)
{
	Menu.push_back(_newMenu);
	menuUpdate();
}

void TownScene::delMenu(std::string _menuName)
{
	for (auto menubar = Menu.begin(); menubar != Menu.end(); ++menubar) {
		if (menubar->menuName == _menuName) {
			Menu.erase(menubar);
			break;
		}
	}
	menuUpdate();
}

void TownScene::menuUpdate()
{
	std::sort(Menu.begin(), Menu.end(), [](const MenuBar& _e1, const MenuBar& _e2) {
		if (_e1.menuNum < _e2.menuNum)
			return true;
		return false;
		});
	m_menuIndexMax = Menu.size()-1;
}

void TownScene::release()
{
}
