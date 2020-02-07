#include "stdafx.h"
#include "InvenScene.h"
#include "Common/SystemManagers.h"

InvenScene::InvenScene(std::shared_ptr<Inventory> _inven)
{
	m_inven = _inven;				// 클래스를 넘겨 받아서 저장하고 있다.
}

InvenScene::~InvenScene()
{
}

bool InvenScene::init()
{
	m_BackGround = IMAGEMANAGER->addImage("인벤토리씬", "Images/InvenScene.bmp",0,0, WINSIZEX, WINSIZEY);
	//ITEMMANAGER->init();
	return true;
}

void InvenScene::update(float _deltaTime)
{
	m_inven->update(_deltaTime);
	if (KEYMANAGER->isOnceKeyDown(P1_X)){
		SCENEMANAGER->scenePop();
	}
}

void InvenScene::release()
{
}

void InvenScene::render(HDC hdc)
{
	//이렇게 랜더 하지 말것,
	//IMAGEMANAGER->render("인벤토리씬", hdc);

	//이렇게 렌더 할것
	m_BackGround->render(hdc);
	m_inven->debugRender(hdc);
}

void InvenScene::afterRender(HDC hdc)
{
}

void InvenScene::debugRender(HDC hdc)
{
	// 이건 필요없는거라 지워야 해용
	for (int i = 0; i < 5; i++)
	{
		UTIL::IRECT(WINSIZEX / 2, 100 + (i * 80), 400, 80);
	}
} 
