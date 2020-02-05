#pragma once
#include "Game/GameObject/Object.h"
#include"Common/SystemManagers.h"

class SunwooRect
	: public Object
{
public:
	bool init() override;
	void update(float _deltaTime) override;

public:
	void render(HDC hdc) override;
	void afterRender(HDC hdc) override;
	void debugRender(HDC hdc) override;

	int* CenterX(UTIL::IRECT rect);
	int* CenterY(UTIL::IRECT rect);

	//void rectInCamera(UTIL::IRECT& outRect, const UTIL::IRECT& realRect, bool& isOutput);

private:
	UTIL::IRECT m_playerRect;
	UTIL::IRECT m_outPlayerRect;

	UTIL::IRECT m_obstacleRect;	
	UTIL::IRECT m_outObstacleRect;
	bool isObstacleOut = false;

	UTIL::IRECT m_obstacleRect2;
	UTIL::IRECT m_outObstacleRect2;
	bool isObstacleOut2 = false;


	Image* m_bg;
	int bgX;
	int bgY;
	int bgOutX;
	int bgOutY;
	//float m_cameraX;
	//float m_cameraY;
};