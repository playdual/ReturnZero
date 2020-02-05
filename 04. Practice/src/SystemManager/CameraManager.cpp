#include "stdafx.h"
#include "CameraManager.h"
DEFINITION_SINGLE(CameraManager)

CameraManager::CameraManager() {}
CameraManager::~CameraManager() {}

void CameraManager::init()
{
}

void CameraManager::release()
{
}

void CameraManager::update()
{
	m_cameraX = *m_targetedCameraX - WINSIZEX / 2;
	m_cameraY = *m_targetedCameraY - WINSIZEY / 2;
}

void CameraManager::render()
{
}

void CameraManager::rectInCamera(UTIL::IRECT& outRect, const UTIL::IRECT& realRect, bool& isOutput)
{
	if (realRect.left - m_cameraX <= 1024 && realRect.top - m_cameraY <= 768)
	{
		outRect.left = realRect.left - m_cameraX;
		outRect.right = realRect.right - m_cameraX;
		outRect.top = realRect.top - m_cameraY;
		outRect.bottom = realRect.bottom - m_cameraY;

		isOutput = true;
		return;
	}
	isOutput = false;
}

std::pair<int, int> CameraManager::pointInCamera(int x, int y)
{
	int retX = x - m_cameraX;
	int retY = y - m_cameraY;

	return {retX, retY};
}


void CameraManager::setPosition(int* _posX, int* _posY)
{
	m_targetedCameraX = _posX;
	m_targetedCameraY = _posY;

	m_cameraX = *_posX - WINSIZEX / 2;
	m_cameraY = *_posY - WINSIZEY / 2;
}
