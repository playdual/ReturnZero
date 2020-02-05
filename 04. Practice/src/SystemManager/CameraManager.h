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
	
	int getCameraX() { return m_cameraX; }
	int getCameraY() { return m_cameraY; }

private:
	int* m_targetedCameraX;
	int* m_targetedCameraY;
	
	int m_cameraX;
	int m_cameraY;
	
private:
	DECLARE_SINGLE(CameraManager)
};




#define CAMERAMANAGER CameraManager::GetInst()
