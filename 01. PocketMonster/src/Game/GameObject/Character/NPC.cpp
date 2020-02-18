#include "stdafx.h"
#include "NPC.h"
#include "Common/SystemManagers.h"

NPC::NPC()
{
}

NPC::NPC(int _bPosX, int _bPosY, std::string _name)
{
	m_Img[DirectionUp] = IMAGEMANAGER->findImage(_name + "Back");
	m_Img[DirectionDown] = IMAGEMANAGER->findImage(_name + "Front");
	m_Img[DirectionLeft] = IMAGEMANAGER->findImage(_name + "Left");
	m_Img[DirectionRight] = IMAGEMANAGER->findImage(_name + "Right");
	m_Name = _name;

	m_blockPositionX = _bPosX;
	m_blockPositionY = _bPosY;
	m_PrintDirection = DirectionDown;

	m_absRect.left = _bPosX * TILE_WIDTH;
	m_absRect.right = _bPosX * TILE_WIDTH + TILE_WIDTH;
	m_absRect.top = _bPosY * TILE_HEIGHT;
	m_absRect.bottom = _bPosY * TILE_HEIGHT + TILE_HEIGHT;
}

bool NPC::init()
{
	return false;
}

void NPC::update(float _deltaTime)
{
	CAMERAMANAGER->rectInCamera(m_outRect, m_absRect, isCanprint);
	if (!isActivate) {
		if (UTIL::GetRndInt(100) <= 2) {
			m_PrintDirection = (Direction)UTIL::GetRndInt(4);
		}
	}
}

void NPC::render(HDC hdc)
{
	if (isCanprint)
	{
		m_Img[m_PrintDirection]->render(hdc, (m_outRect.left - 10), (m_outRect.top - 20) + 40, 0, 40, 80, 40);
	}
}

void NPC::afterRender(HDC hdc)
{
	if (isCanprint)
	{
		m_Img[m_PrintDirection]->render(hdc, (m_outRect.left - 10), (m_outRect.top - 20), 0, 0, 80, 40);
	}
}

void NPC::debugRender(HDC hdc)
{
	if (isCanprint)
	{
		UTIL::DrawColorRect(hdc, m_outRect, RGB(123, 41, 78), true);
	}
}

void NPC::addScript(std::string _scriptKey, std::string _firstLine, std::string _secondLine)
{
}

void NPC::activateNPC(Direction _dir)
{
	isActivate = true;
	switch (_dir)
	{
	case DirectionDown:
		m_PrintDirection = DirectionUp;
		break;
	case DirectionUp:
		m_PrintDirection = DirectionDown;
		break;
	case DirectionLeft:
		m_PrintDirection = DirectionRight;
		break;
	case DirectionRight:
		m_PrintDirection = DirectionLeft;
		break;
	}
}
