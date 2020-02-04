#include "stdafx.h"
#include "SunwooRect.h"


bool SunwooRect::init()
{
	m_rect = UTIL::IRectMakeCenter(WINSIZEX/2, WINSIZEY/2, 150, 150);
	m_obstacle = UTIL::IRectMakeCenter(WINSIZEX / 2 + 300, WINSIZEY / 2 -100, 150, 150);

	m_bg =IMAGEMANAGER->addImage("bg", "Images/bg.bmp", 0, 0,WINSIZEX*2,WINSIZEY*2,true, RGB(255, 0, 255));

	return true;
}

void SunwooRect::update(float _deltaTime)
{
	if (KEYMANAGER->isStayKeyDown(P1_LEFT))
	{
		m_cameraX -= 2;
		//m_rect.moveLeft(5);
	}
	if (KEYMANAGER->isStayKeyDown(P1_RIGHT))
	{
		m_cameraX += 2;
	}
	if (KEYMANAGER->isStayKeyDown(P1_UP))
	{
		m_cameraY -= 2;

	}
	if (KEYMANAGER->isStayKeyDown(P1_DOWN))
	{
		m_cameraY += 2;
	}

}

void SunwooRect::render(HDC hdc)
{
	m_bg->render(hdc,-m_cameraX,-m_cameraY);

	UTIL::DrawColorRect(hdc, m_rect, true, RGB(153, 255, 30));
	UTIL::DrawColorRect(hdc, m_obstacle, true, RGB(255, 0, 30));
}

void SunwooRect::afterRender(HDC hdc)
{

}

void SunwooRect::debugRender(HDC hdc)
{
}
