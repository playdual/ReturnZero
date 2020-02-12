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
	cameraBox.left = 0;
	cameraBox.top = 0;
	cameraBox.right = 0;
	cameraBox.bottom = 0;

	cameraX = 0;
	cameraY = 0;
}

void CameraManager::init(RECT & _cameraBox, int _cameraX, int _cameraY)
{
	cameraBox.left = _cameraBox.left;
	cameraBox.top = _cameraBox.top;
	cameraBox.right = _cameraBox.right;
	cameraBox.bottom = _cameraBox.bottom;

	cameraX = _cameraX;
	cameraY = _cameraY;
}

void CameraManager::init(int _cameraBoxLeft, int _cameraBoxTop, int _cameraBoxRight, int _cameraBoxBottom, int _cameraX, int _cameraY)
{
	cameraBox.left = _cameraBoxLeft;
	cameraBox.top = _cameraBoxTop;
	cameraBox.right = _cameraBoxRight;
	cameraBox.bottom = _cameraBoxBottom;

	cameraX = _cameraX;
	cameraY = _cameraY;
}

void CameraManager::release()
{
}

void CameraManager::ExtraRender(HDC hdc)
{
	UTIL::DrawColorRect(hdc, cameraExtraLeft, true, RGB(255, 255, 255));
	UTIL::DrawColorRect(hdc, cameraExtraTop, true, RGB(255, 255, 255));
	UTIL::DrawColorRect(hdc, cameraExtraRight, true, RGB(255, 255, 255));
	UTIL::DrawColorRect(hdc, cameraExtraBottom, true, RGB(255, 255, 255));
}

void CameraManager::setCameraFocus(int * _x, int * _y, int _cameraTargetOffSetX, int _cameraTargetOffSetY)
{
	targetedX = _x;
	targetedY = _y;
	cameraTargetOffSetX = _cameraTargetOffSetX;
	cameraTargetOffSetY = _cameraTargetOffSetY;
}

void CameraManager::setCameraFocus(UTIL::IRECT & _rect, int _cameraTargetOffSetX, int _cameraTargetOffSetY, bool _baseCenter)
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

void CameraManager::setCameraFocus(RECT & _rect, int _cameraTargetOffSetX, int _cameraTargetOffSetY)
{
	targetedX = (int*)&_rect.left;
	targetedY = (int*)&_rect.top;
	cameraTargetOffSetX = _cameraTargetOffSetX;
	cameraTargetOffSetY = _cameraTargetOffSetY;
}


void CameraManager::releaseCameraFocus()
{
	targetedX = nullptr;
	targetedY = nullptr;
	cameraTargetOffSetX = 0;
	cameraTargetOffSetX = 0;
}

void CameraManager::setExtra(int _x, int _y)
{
	extraX = _x;
	extraY = _y;
}

void CameraManager::setCameraBox(RECT & _rect)
{
	cameraBox.left = _rect.left;
	cameraBox.top = _rect.top;
	cameraBox.right = _rect.right;
	cameraBox.bottom = _rect.bottom;

	cameraExtraLeft.left = 0;
	cameraExtraLeft.top = 0;
	cameraExtraLeft.right = _rect.left;
	cameraExtraLeft.bottom = WINSIZEY;

	cameraExtraTop.left = _rect.left - cameraExtraCover;
	cameraExtraTop.top = 0;
	cameraExtraTop.right = _rect.right + cameraExtraCover;
	cameraExtraTop.bottom = _rect.top;

	cameraExtraBottom.left = _rect.left - cameraExtraCover;
	cameraExtraBottom.top = _rect.bottom;
	cameraExtraBottom.right = _rect.right + cameraExtraCover;
	cameraExtraBottom.bottom = WINSIZEY;

	cameraExtraRight.left = _rect.right;
	cameraExtraRight.top = 0;
	cameraExtraRight.right = WINSIZEX;
	cameraExtraRight.bottom = WINSIZEY;
}

void CameraManager::setCameraBox(UTIL::IRECT & _rect)
{
	cameraBox.left = _rect.left;
	cameraBox.top = _rect.top;
	cameraBox.right = _rect.right;
	cameraBox.bottom = _rect.bottom;

	cameraExtraLeft.left = 0;
	cameraExtraLeft.top = 0;
	cameraExtraLeft.right = _rect.left;
	cameraExtraLeft.bottom = WINSIZEY;

	cameraExtraTop.left = _rect.left - cameraExtraCover;
	cameraExtraTop.top = 0;
	cameraExtraTop.right = _rect.right + cameraExtraCover;
	cameraExtraTop.bottom = _rect.top;

	cameraExtraBottom.left = _rect.left - cameraExtraCover;
	cameraExtraBottom.top = _rect.bottom;
	cameraExtraBottom.right = _rect.right + cameraExtraCover;
	cameraExtraBottom.bottom = WINSIZEY;

	cameraExtraRight.left = _rect.right;
	cameraExtraRight.top = 0;
	cameraExtraRight.right = WINSIZEX;
	cameraExtraRight.bottom = WINSIZEY;
}

void CameraManager::setCameraBox(int _left, int _top, int _right, int _bottom)
{
	cameraBox.left = _left;
	cameraBox.top = _top;
	cameraBox.right = _right;
	cameraBox.bottom = _bottom;

	cameraExtraLeft.left = 0;
	cameraExtraLeft.top = 0;
	cameraExtraLeft.right = _left;
	cameraExtraLeft.bottom = WINSIZEY;

	cameraExtraTop.left = _left - cameraExtraCover;
	cameraExtraTop.top = 0;
	cameraExtraTop.right = _right + cameraExtraCover;
	cameraExtraTop.bottom = _top;

	cameraExtraBottom.left = _left - cameraExtraCover;
	cameraExtraBottom.top = _bottom;
	cameraExtraBottom.right = _right + cameraExtraCover;
	cameraExtraBottom.bottom = WINSIZEY;

	cameraExtraRight.left = _right;
	cameraExtraRight.top = 0;
	cameraExtraRight.right = WINSIZEX;
	cameraExtraRight.bottom = WINSIZEY;
}

void CameraManager::moveCamera(int _distX, int _distY)
{
	cameraX += _distX;
	cameraY += _distY;
}

void CameraManager::update(HDC _hdc)
{
	/*PatBlt(_hdc, cameraX, cameraY, WINSIZEX, WINSIZEY, BLACKNESS);
	SetViewportOrgEx(_hdc, -cameraX, -cameraY, NULL);

*/
}

std::pair<int, int> CameraManager::getRelativePosition(const UTIL::IRECT & _rect, bool & _isCanPrinted)
{
	_isCanPrinted = false;
	int relativeX = _rect.left - cameraX;
	int relativeY = _rect.top - cameraY;

	if ((-extraX  <= relativeX && relativeX <= WINSIZEX) &&
		(-extraY  <= relativeY && relativeY <= WINSIZEY))
		_isCanPrinted = true;

	return {relativeX, relativeY};
}

std::pair<int, int> CameraManager::getRelativePosition(const RECT & _rect, bool & _isCanPrinted)
{
	_isCanPrinted = false;
	int relativeX = _rect.left - cameraX;
	int relativeY = _rect.top - cameraY;
	if ((-extraX + cameraBox.left <= relativeX && relativeX <= cameraBox.right) &&
		(-extraY + cameraBox.top <= relativeY && relativeY <= cameraBox.bottom))
		_isCanPrinted = true;

	return { relativeX, relativeY };
}

std::pair<int, int> CameraManager::getRelativePosition(int _posX, int _posY, bool & _isCanPrinted)
{
	_isCanPrinted = false;
	int relativeX = _posX - cameraX;
	int relativeY = _posY - cameraY;
	if ((-extraX + cameraBox.left <= relativeX && relativeX <= cameraBox.right) &&
		(-extraY + cameraBox.top <= relativeY && relativeY <= cameraBox.bottom))
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
	if ((-extraX + cameraBox.left <= relaPos.x && relaPos.x <= cameraBox.right) &&
		(-extraY + cameraBox.top <= relaPos.y && relaPos.y <= cameraBox.bottom))
		_isCanPrinted = true;
	return relaPos;
}

int CameraManager::getRelativeX(const int _x)
{
	int x = _x - cameraX;
	return x;
}

int CameraManager::getRelativeY(const int _y)
{
	int y = _y - cameraY;
	return y;
}

void CameraManager::setRelativePosition(const UTIL::IRECT & _absRect, UTIL::IRECT & _outRect, bool & _isCanPrinted)
{
	_isCanPrinted = false;
	_outRect.left = _absRect.left - cameraX;
	_outRect.top = _absRect.top - cameraY;
	_outRect.right = _absRect.right - cameraX;
	_outRect.bottom = _absRect.bottom - cameraY;

	if ((-extraX <= _outRect.left && _outRect.left <= uiX) &&
		(-extraY <= _outRect.top && _outRect.top <= WINSIZEY))
		_isCanPrinted = true;
}

void CameraManager::setRelativePosition(const RECT & _absRect, RECT & _outRect, bool & _isCanPrinted)
{
	_isCanPrinted = false;
	_outRect.left = _absRect.left - cameraX;
	_outRect.top = _absRect.top - cameraY;
	_outRect.right = _absRect.right - cameraX;
	_outRect.bottom = _absRect.bottom - cameraY;

	if ((-extraX + cameraBox.left <= _outRect.left && _outRect.left <= cameraBox.right) &&
		(-extraY + cameraBox.top <= _outRect.top && _outRect.top <= cameraBox.bottom))
		_isCanPrinted = true;
}

void CameraManager::setRelativePosition(int _absX, int _absY, int & _relaX, int & _relaY, bool & _isCanPrinted)
{
	_isCanPrinted = false;
	_relaX = _absX - cameraX;
	_relaY = _absY - cameraX;
	if ((-extraX + cameraBox.left <= _relaX && _relaX <= cameraBox.right) &&
		(-extraY + cameraBox.top <= _relaY && _relaY <= cameraBox.bottom))
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
	if ((-extraX + cameraBox.left <= _outPos.x && _outPos.x <= cameraBox.right) &&
		(-extraY + cameraBox.top <= _outPos.y && _outPos.y <= cameraBox.bottom))
		_isCanPrinted = true;
}

void CameraManager::setRelativeX(int & _x)
{
	_x = _x - cameraX;
}

void CameraManager::setRelativeY(int & _y)
{
	_y = _y - cameraY;
}
