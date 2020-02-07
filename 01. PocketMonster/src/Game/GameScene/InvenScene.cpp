#include "stdafx.h"
#include "InvenScene.h"


InvenScene::InvenScene(std::shared_ptr<Inventory> _inven)
{
	m_inven = _inven;				// 클래스를 넘겨 받아서 저장하고 있다.
}

InvenScene::~InvenScene()
{
}

bool InvenScene::init()
{
	return true;
}

void InvenScene::update(float _deltaTime)
{
	
}

void InvenScene::release()
{
}

void InvenScene::render(HDC hdc)
{
	
}

void InvenScene::afterRender(HDC hdc)
{
}

void InvenScene::debugRender(HDC hdc)
{
	m_inven->debugRender(hdc);
} 
