#include "stdafx.h"
#include "SunwooRect.h"


bool SunwooRect::init()
{
	
	m_playerRect = UTIL::IRectMakeCenter(WINSIZEX/2, WINSIZEY/2, 100, 100);
	m_outPlayerRect = UTIL::IRectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);
	m_obstacleRect = UTIL::IRectMakeCenter(WINSIZEX / 2 + 300, WINSIZEY /  2 -100, 100, 100);
	m_obstacleRect2 = UTIL::IRectMakeCenter(WINSIZEX / 2 + 1000, WINSIZEY /  2 -100, 100, 100);

	//CAMERAMANAGER->setPosition(&m_playerRect.centerX, &m_playerRect.centerY);
	bgX = 0;
	bgY = 0;
	m_bg =IMAGEMANAGER->addImage("bg", "Images/bg.bmp", bgX, bgY, WINSIZEX*2,WINSIZEY*2,true, RGB(255, 0, 255));
	return true;
}

void SunwooRect::update(float _deltaTime)
{

	SetViewportOrgEx(GetDC(m_hWnd), 50, 50, NULL);
	

	if (KEYMANAGER->isStayKeyDown(P1_LEFT)&&!isMoveLeft&&!isAnotherMove)
	{
		m_playerRectMemory = m_playerRect.left;
		isAnotherMove = true;
		isMoveLeft = true;
	}
	if (isMoveLeft)
	{
		if (m_playerRect.left > m_playerRectMemory - TILE_WIDTH)
		{
			m_playerRect.moveLeft(5);
		}
		else
		{
			isMoveLeft = false;
			isAnotherMove = false;
		}
	}
	if (KEYMANAGER->isStayKeyDown(P1_RIGHT)&&!isMoveRight&&!isAnotherMove)
	{
		m_playerRectMemory = m_playerRect.right;
		isAnotherMove = true;
		isMoveRight = true;
	}
	if (isMoveRight)
	{
		if (m_playerRect.right < m_playerRectMemory + TILE_WIDTH)
		{
			m_playerRect.moveRight(5);
		}
		else
		{
			isMoveRight = false;
			isAnotherMove = false;
		}
	}
	if (KEYMANAGER->isStayKeyDown(P1_UP) && !isMoveUp&&!isAnotherMove)
	{
		m_playerRectMemory = m_playerRect.top;
		isAnotherMove = true;
		isMoveUp = true;
	}
	if (isMoveUp)
	{
		if (m_playerRect.top > m_playerRectMemory - TILE_HEIGHT)
		{
			m_playerRect.moveUp(5);
		}
		else
		{
			isMoveUp = false;
			isAnotherMove = false;
		}
	}
	if (KEYMANAGER->isStayKeyDown(P1_DOWN)&&!isMoveDown&&!isAnotherMove)
	{
		m_playerRectMemory = m_playerRect.bottom;
		isAnotherMove = true;
		isMoveDown = true;
	}
	if (isMoveDown)
	{
		if (m_playerRect.bottom < m_playerRectMemory + TILE_HEIGHT)
		{
			m_playerRect.moveDown(5);
		}
		else
		{
			isMoveDown = false;
			isAnotherMove = false;
		}
	}
	//CAMERAMANAGER->update();

	//auto[x, y] = CAMERAMANAGER->pointInCamera(bgX, bgY);

	//bgOutX = x;
	//bgOutY = y;

	//output obstacle
	//rectInCamera(m_obstacle, true);
	
	//wntjr
	//CAMERAMANAGER->rectInCamera(m_outObstacleRect, m_obstacleRect, isObstacleOut);
	//CAMERAMANAGER->rectInCamera(m_outObstacleRect2, m_obstacleRect2, isObstacleOut2);

//	RECT temp;
//	if(IntersectRect(&temp, &m_rect,))
}

void SunwooRect::render(HDC hdc)
{

	//m_bg->render(hdc, bgOutX, bgOutY);
	//player
	UTIL::DrawColorRect(hdc, m_playerRect, true, RGB(153, 255, 30));
	//obstacle
	/*if (isObstacleOut)
	{*/
		UTIL::DrawColorRect(hdc, m_obstacleRect, true, RGB(255, 100, 100));

	//}
	//if (isObstacleOut2)
	//{
		UTIL::DrawColorRect(hdc, m_obstacleRect2, true, RGB(5, 255, 100));
	//}
	
}

void SunwooRect::afterRender(HDC hdc)
{

}

void SunwooRect::debugRender(HDC hdc)
{
}





