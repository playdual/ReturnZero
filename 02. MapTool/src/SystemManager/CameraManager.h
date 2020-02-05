#pragma once

class CameraManager {
public:
	void init();
	void update();
	void release();

public:
	void moveCamera(int _distX, int _distY);
	void setCameraTarget(UTIL::IRECT& _rect, int _cameraTargetOffSetX = 0, int _cameraTargetOffSetY = 0, bool _baseCenter = false);
	void setCameraTarget(int* _x, int* _y, int _cameraTargetOffSetX = 0, int _cameraTargetOffSetY = 0);
	void setCameraTarget(RECT& _rect, int _cameraTargetOffSetX = 0, int _cameraTargetOffSetY = 0);
	void releaseCameraTarget();

public:
	std::pair<int, int> getRelativePosition(const UTIL::IRECT& _rect, bool& _isCanPrinted);
	std::pair<int, int> getRelativePosition(const RECT& _rect, bool& _isCanPrinted);
	std::pair<int, int> getRelativePosition(int _posX, int _posY, bool& _isCanPrinted);
	std::pair<int, int> getRelativePosition(int _posX, int _posY);
	POINT getRelativePosition(const POINT& _pos, bool& _isCanPrinted);

	void setRelativePosition(const UTIL::IRECT& _absRect, UTIL::IRECT& _outRect, bool& _isCanPrinted);
	void setRelativePosition(const RECT& _absRect, RECT& _outRect,bool& _isCanPrinted);
	void setRelativePosition(int _absX, int _absY, int& _relaX, int& _relaY, bool& _isCanPrinted);
	void setRelativePosition(int _absX, int _absY, int& _relaX, int& _relaY);
	void setRelativePosition(const POINT& _absPos, POINT& _outPos, bool& _isCanPrinted);

private:
	int cameraX = 0;
	int cameraY = 0;
	int* targetedX = nullptr;
	int* targetedY = nullptr;
	int cameraTargetOffSetX = 0;
	int cameraTargetOffSetY = 0;

private:
	DECLARE_SINGLE(CameraManager)
};

#define CAMEARAMANAGER CameraManager::GetInst()