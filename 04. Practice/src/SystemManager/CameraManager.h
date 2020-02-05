#pragma once
class CameraManager
{
public:
	void init();
	void release();
	void update();
	void render();

	void rectInCamera(UTIL::IRECT& outRect, const UTIL::IRECT& realRect, bool& isOutput);
	void setPosition(int* _posX, int* _posY);
	
	int getCameraX() { return *m_CameraX; }
	int getCameraY() { return *m_CameraY; }

private:
	int* m_CameraX;
	int* m_CameraY;
	
	
private:
	DECLARE_SINGLE(CameraManager)
};

#define CAMERAMANAGER CameraManager::GetInst()
