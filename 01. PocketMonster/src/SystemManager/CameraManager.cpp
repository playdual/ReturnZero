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
	m_cameraX = *m_FocucedCameraX - m_cameraOffsetX_FromTarget;
	m_cameraY = *m_FocucedCameraY - m_cameraOffsetY_FromTarget;
}


void CameraManager::rectInCamera(UTIL::IRECT& outRect, const UTIL::IRECT& realRect, bool& isOutput)
{
	isOutput = false;
	outRect.left = realRect.left - m_cameraX;
	outRect.top = realRect.top - m_cameraY;
	outRect.right = realRect.right - m_cameraX;
	outRect.bottom = realRect.bottom - m_cameraY;

	if (((- m_outputExtra <= outRect.left) && (outRect.left <= WINSIZEX)) &&
		((-m_outputExtra <= outRect.top)&&(outRect.top<=WINSIZEY)))
		isOutput = true;
}

void CameraManager::setCameraFocus(int * _targetX, int * _targetY, int _cameraOffsetX, int _cameraOffsetY)
{
	m_FocucedCameraX = _targetX;
	m_FocucedCameraY = _targetY;
	m_cameraOffsetX_FromTarget = _cameraOffsetX;
	m_cameraOffsetY_FromTarget = _cameraOffsetY;
}




