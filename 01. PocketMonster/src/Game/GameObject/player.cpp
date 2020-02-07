#include "stdafx.h"
#include "player.h"
#include <iostream>

player::player()
{
	/*m_blockPositionX = blockX;
	m_blockPositionY = blockY;

	m_playerRect.left = blockX * TILE_WIDTH;
	m_playerRect.right = blockX * TILE_WIDTH + TILE_WIDTH;
	m_playerRect.top = blockY * TILE_HEIGHT;
	m_playerRect.bottom = blockY * TILE_HEIGHT + TILE_HEIGHT;

	m_outPlayerRect = UTIL::IRectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);*/
}

player::~player()
{
}

bool player::init()
{
	std::cout << "sunwoo Scene init!" << std::endl;
	m_outPlayerRect = UTIL::IRectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, TILE_WIDTH, TILE_HEIGHT);
	CAMERAMANAGER->setCameraFocus(&m_playerRect.centerX, &m_playerRect.centerY,WINSIZEX/2,WINSIZEY/2);
	CAMERAMANAGER->update();
	bgX = 0;
	bgY = 0;
	return true;
}

void player::update(float _deltaTime)
{

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
	CAMERAMANAGER->update();
}

void player::render(HDC hdc)
{

	

}

void player::afterRender(HDC hdc)
{

}

void player::debugRender(HDC hdc)
{
	//player
	UTIL::DrawColorRect(hdc, m_outPlayerRect, true, RGB(153, 255, 30));
}

int player::getPlayRectX()
{
	return m_playerRect.centerX;
}

int player::getPlayRectY()
{

	return m_playerRect.centerY;
}

void player::reLocate(int blockX, int blockY)
{
	
	m_blockPositionX = blockX;
	m_blockPositionY = blockY;

	m_playerRect.left = blockX * TILE_WIDTH;
	m_playerRect.right = blockX * TILE_WIDTH + TILE_WIDTH;
	m_playerRect.top = blockY * TILE_HEIGHT;
	m_playerRect.bottom = blockY * TILE_HEIGHT + TILE_HEIGHT;

	m_playerRect.centerX = m_playerRect.left + (m_playerRect.right - m_playerRect.left) / 2;
	m_playerRect.centerY = m_playerRect.top + (m_playerRect.bottom - m_playerRect.top) / 2;
}





