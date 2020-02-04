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

private:
	UTIL::IRECT m_rect;
	UTIL::IRECT m_obstacle;
	Image* m_bg;
	float m_cameraX;
	float m_cameraY;
};