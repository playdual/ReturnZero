#include "stdafx.h"
#include "InvenScene.h"


InvenScene::InvenScene(std::shared_ptr<Inventory> _inven)
{
	m_inven = _inven;				// Ŭ������ �Ѱ� �޾Ƽ� �����ϰ� �ִ�.
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
