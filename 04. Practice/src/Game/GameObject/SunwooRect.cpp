#include "stdafx.h"
#include "SunwooRect.h"


bool SunwooRect::init()
{
	
	m_playerRect = UTIL::IRectMakeCenter(WINSIZEX/2, WINSIZEY/2, 150, 150);
	m_outPlayerRect = UTIL::IRectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 150, 150);
	m_obstacleRect = UTIL::IRectMakeCenter(WINSIZEX / 2 + 500, WINSIZEY /  2 -100, 150, 150);
	m_obstacleRect2 = UTIL::IRectMakeCenter(WINSIZEX / 2 + 1000, WINSIZEY /  2 -100, 150, 150);

	CAMERAMANAGER->setPosition(&m_playerRect.left, &m_playerRect.top);
	
	bgX = 0;
	bgY = 0;
	m_bg =IMAGEMANAGER->addImage("bg", "Images/bg.bmp", bgX, bgY, WINSIZEX*2,WINSIZEY*2,true, RGB(255, 0, 255));
	return true;
}

void SunwooRect::update(float _deltaTime)
{
	if (KEYMANAGER->isStayKeyDown(P1_LEFT))
	{
		m_playerRect.moveLeft(2);
	}
	if (KEYMANAGER->isStayKeyDown(P1_RIGHT))
	{
		m_playerRect.moveRight(2);
	}
	if (KEYMANAGER->isStayKeyDown(P1_UP))
	{
		m_playerRect.moveUp(2);
	}
	if (KEYMANAGER->isStayKeyDown(P1_DOWN))
	{
		m_playerRect.moveDown(2);
	}
	CAMERAMANAGER->update();

	auto[x, y] = CAMERAMANAGER->pointInCamera(bgX, bgY);

	bgOutX = x;
	bgOutY = y;

	//output obstacle
	//rectInCamera(m_obstacle, true);
	CAMERAMANAGER->rectInCamera(m_outObstacleRect, m_obstacleRect, isObstacleOut);
	CAMERAMANAGER->rectInCamera(m_outObstacleRect2, m_obstacleRect2, isObstacleOut2);

//	RECT temp;
//	if(IntersectRect(&temp, &m_rect,))
}

void SunwooRect::render(HDC hdc)
{
	m_bg->render(hdc, bgOutX, bgOutY);
	//player
	UTIL::DrawColorRect(hdc, m_outPlayerRect, true, RGB(153, 255, 30));
	//obstacle
	if (isObstacleOut)
	{
		UTIL::DrawColorRect(hdc, m_outObstacleRect, true, RGB(255, 100, 100));

	}
	if (isObstacleOut2)
	{
		UTIL::DrawColorRect(hdc, m_outObstacleRect2, true, RGB(5, 255, 100));
	}
	
}

void SunwooRect::afterRender(HDC hdc)
{

}

void SunwooRect::debugRender(HDC hdc)
{
}

int* SunwooRect::CenterX(UTIL::IRECT rect)
{
	int* CenterX;
	CenterX = (&rect.left + (&rect.right - &rect.left) / 2);

	return CenterX;
}

int* SunwooRect::CenterY(UTIL::IRECT rect)
{
	int* CenterY;
	CenterY = (&rect.top + (&rect.bottom - &rect.top) / 2);

	return CenterY;
}




