#include "stdafx.h"
#include "CameraManager.h"
#include "Common/UTILS.h"
DEFINITION_SINGLE(CameraManager)

void CameraManager::init()
{
}

void CameraManager::release()
{
}

void CameraManager::update()
{
}

void CameraManager::render()
{
}

void CameraManager::rectInCamera(UTIL::IRECT& outRect, const UTIL::IRECT& realRect, bool& isOutput)
{
	if (realRect.left - *m_CameraX <= 1024 && realRect.top - *m_CameraY <= 768)
	{
		outRect.left = realRect.left - *m_CameraX;
		outRect.right = realRect.right - *m_CameraX;
		outRect.top = realRect.top - *m_CameraY;
		outRect.bottom = realRect.bottom - *m_CameraY;

		isOutput = true;
		return;
	}
	isOutput = false;
}

void CameraManager::setPosition(int* _posX, int* _posY)
{
	m_CameraX = _posX;
	m_CameraY = _posY;
}
