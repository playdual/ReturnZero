#pragma once

class CameraManager {
public:
	void init();
	void init(RECT& _cameraBox, int _cameraX, int _cameraY);
	void init(int _cameraBoxLeft, int _cameraBoxTop, int _cameraBoxRight, int _cameraBoxBottom, int cameraX, int cameraY);
	void update();
	void release();
	void ExtraRender(HDC hdc);

public:
	void moveCamera(int _distX, int _distY);
	void setCameraFocus(UTIL::IRECT& _rect, int _cameraTargetOffSetX = 0, int _cameraTargetOffSetY = 0, bool _baseCenter = false);
	void setCameraFocus(int* _x, int* _y, int _cameraTargetOffSetX = 0, int _cameraTargetOffSetY = 0);
	void setCameraFocus(RECT& _rect, int _cameraTargetOffSetX = 0, int _cameraTargetOffSetY = 0);
	void releaseCameraFocus();
	void setExtra(int _x = 300, int _y = 300);
	void setCameraBox(RECT& _rect);
	void setCameraBox(UTIL::IRECT& _rect);
	void setCameraBox(int _left, int _top, int _right, int _bottom);

public:
	std::pair<int, int> getRelativePosition(const UTIL::IRECT& _rect, bool& _isCanPrinted);
	std::pair<int, int> getRelativePosition(const RECT& _rect, bool& _isCanPrinted);
	std::pair<int, int> getRelativePosition(int _posX, int _posY, bool& _isCanPrinted);
	std::pair<int, int> getRelativePosition(int _posX, int _posY);
	POINT getRelativePosition(const POINT& _pos, bool& _isCanPrinted);
	int getRelativeX(const int _x);
	int getRelativeY(const int _y);

	void setRelativePosition(const UTIL::IRECT& _absRect, UTIL::IRECT& _outRect, bool& _isCanPrinted);
	void setRelativePosition(const RECT& _absRect, RECT& _outRect,bool& _isCanPrinted);
	void setRelativePosition(int _absX, int _absY, int& _relaX, int& _relaY, bool& _isCanPrinted);
	void setRelativePosition(int _absX, int _absY, int& _relaX, int& _relaY);
	void setRelativePosition(const POINT& _absPos, POINT& _outPos, bool& _isCanPrinted);
	void setRelativeX(int& _x);
	void setRelativeY(int& _y);

private:
	int cameraX = 0;
	int cameraY = 0;
	int* targetedX = nullptr;
	int* targetedY = nullptr;
	int cameraTargetOffSetX = 0;
	int cameraTargetOffSetY = 0;
	int extraX = 100;
	int extraY = 100;

	RECT cameraBox;
	//¿©¹é¿ë
	RECT cameraExtraLeft;
	RECT cameraExtraTop;
	RECT cameraExtraRight;
	RECT cameraExtraBottom;
	const int cameraExtraCover = 5;

private:
	DECLARE_SINGLE(CameraManager)
};

#define CAMEARAMANAGER CameraManager::GetInst()