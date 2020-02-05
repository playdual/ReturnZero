#include "stdafx.h"
#include "CameraManager.h"
DEFINITION_SINGLE(CameraManager)

CameraManager::CameraManager() 
{
}

CameraManager::~CameraManager()
{
}

void CameraManager::init() 
{
}

void CameraManager::release()
{
}

void CameraManager::setCameraTarget(int * _x, int * _y, int _cameraTargetOffSetX, int _cameraTargetOffSetY)
{
	targetedX = _x;
	targetedY = _y;
	cameraTargetOffSetX = _cameraTargetOffSetX;
	cameraTargetOffSetY = _cameraTargetOffSetY;
}

void CameraManager::setCameraTarget(UTIL::IRECT & _rect, int _cameraTargetOffSetX, int _cameraTargetOffSetY, bool _baseCenter)
{
	targetedX = &_rect.left;
	targetedY = &_rect.top;
	if (_baseCenter) {
		targetedX = &_rect.centerX;
		targetedY = &_rect.centerY;
	}	
	cameraTargetOffSetX = _cameraTargetOffSetX;
	cameraTargetOffSetY = _cameraTargetOffSetY;
}

void CameraManager::setCameraTarget(RECT & _rect, int _cameraTargetOffSetX, int _cameraTargetOffSetY)
{
	targetedX = (int*)&_rect.left;
	targetedY = (int*)&_rect.top;
	cameraTargetOffSetX = _cameraTargetOffSetX;
	cameraTargetOffSetY = _cameraTargetOffSetY;
}


void CameraManager::releaseCameraTarget()
{
	targetedX = nullptr;
	targetedY = nullptr;
	cameraTargetOffSetX = 0;
	cameraTargetOffSetX = 0;
}

void CameraManager::moveCamera(int _distX, int _distY)
{
	cameraX += _distX;
	cameraY += _distY;
}

void CameraManager::update()
{
	if (targetedX) {
		cameraX = *targetedX - cameraTargetOffSetX;
		cameraY = *targetedY - cameraTargetOffSetY;
	}
}

std::pair<int, int> CameraManager::getRelativePosition(const UTIL::IRECT & _rect, bool & _isCanPrinted)
{
	_isCanPrinted = false;
	int relativeX = _rect.left - cameraX;
	int relativeY = _rect.top - cameraY;
	if ((0 < relativeX && relativeX < WINSIZEX) && (0 < relativeY && relativeY < WINSIZEY))
		_isCanPrinted = true;

	return {relativeX, relativeY};
}

std::pair<int, int> CameraManager::getRelativePosition(const RECT & _rect, bool & _isCanPrinted)
{
	_isCanPrinted = false;
	int relativeX = _rect.left - cameraX;
	int relativeY = _rect.top - cameraY;
	if ((0 < relativeX && relativeX < WINSIZEX) && (0 < relativeY && relativeY < WINSIZEY))
		_isCanPrinted = true;

	return { relativeX, relativeY };
}

std::pair<int, int> CameraManager::getRelativePosition(int _posX, int _posY, bool & _isCanPrinted)
{
	_isCanPrinted = false;
	int relativeX = _posX - cameraX;
	int relativeY = _posY - cameraY;
	if ((0 < relativeX && relativeX < WINSIZEX) && (0 < relativeY && relativeY < WINSIZEY))
		_isCanPrinted = true;

	return { relativeX, relativeY };
}

std::pair<int, int> CameraManager::getRelativePosition(int _posX, int _posY)
{
	int relativeX = _posX - cameraX;
	int relativeY = _posY - cameraY;

	return { relativeX, relativeY };
}

POINT CameraManager::getRelativePosition(const POINT & _pos, bool & _isCanPrinted)
{
	_isCanPrinted = false;
	POINT relaPos;
	relaPos.x = _pos.x - cameraX;
	relaPos.y = _pos.y - cameraY;
	if ((0 < relaPos.x && relaPos.x < WINSIZEX) && (0 < relaPos.y && relaPos.y < WINSIZEY))
		_isCanPrinted = true;
	return relaPos;
}

void CameraManager::setRelativePosition(const UTIL::IRECT & _absRect, UTIL::IRECT & _outRect, bool & _isCanPrinted)
{
	_isCanPrinted = false;
	_outRect.left = _absRect.left - cameraX;
	_outRect.top = _absRect.top - cameraY;
	_outRect.right = _absRect.right - cameraX;
	_outRect.bottom = _absRect.bottom - cameraY;

	if ((0 < _outRect.left && _outRect.left < WINSIZEX) && (0 < _outRect.top && _outRect.top < WINSIZEY))
		_isCanPrinted = true;
}

void CameraManager::setRelativePosition(const RECT & _absRect, RECT & _outRect, bool & _isCanPrinted)
{
	_isCanPrinted = false;
	_outRect.left = _absRect.left - cameraX;
	_outRect.top = _absRect.top - cameraY;
	_outRect.right = _absRect.right - cameraX;
	_outRect.bottom = _absRect.bottom - cameraY;

	if ((0 < _outRect.left && _outRect.left < WINSIZEX) && (0 < _outRect.top && _outRect.top < WINSIZEY))
		_isCanPrinted = true;
}

void CameraManager::setRelativePosition(int _absX, int _absY, int & _relaX, int & _relaY, bool & _isCanPrinted)
{
	_isCanPrinted = false;
	_relaX = _absX - cameraX;
	_relaY = _absY - cameraX;
	if ((0 < _relaX && _relaX < WINSIZEX) && (0 < _relaY && _relaY < WINSIZEY))
		_isCanPrinted = true;
}

void CameraManager::setRelativePosition(int _absX, int _absY, int & _relaX, int & _relaY)
{
	_relaX = _absX - cameraX;
	_relaY = _absY - cameraX;
}

void CameraManager::setRelativePosition(const POINT & _absPos, POINT & _outPos, bool & _isCanPrinted)
{
	_isCanPrinted = false;
	_outPos.x = _absPos.x - cameraX;
	_outPos.y = _absPos.y - cameraY;
	if ((0 < _outPos.x && _outPos.x < WINSIZEX) && (0 < _outPos.y && _outPos.y < WINSIZEY))
		_isCanPrinted = true;
}