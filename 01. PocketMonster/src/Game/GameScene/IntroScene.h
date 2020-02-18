#pragma once
#include "Scene.h"


class IntroScene :
	public Scene
{
public:
	IntroScene();
	virtual ~IntroScene();

public:
	bool init() override;
	void release() override;

public:
	void update(float _deltaTime) override;
	void render(HDC hdc) override;
	void afterRender(HDC hdc) override;
	void debugRender(HDC hdc) override;



private:
	Image* m_IntroBg;
	Image* m_IntroFire;
	Image* m_pokemonMark;
	Image* m_pushStart;
	Image* m_notice;
	Image* m_alpha;
	Image* m_alphaTwo;

	UTIL::IRECT m_FireOne;
	UTIL::IRECT m_FireTwo;

	float pastTime = 0.f;
	float pastTime1 = 0.f;
	float frameDelay = 0.2f;
	int m_pocketMonFrameIdx = 0;
	int m_pocketMonMarkFrameIdx = 0;
	int m_pushTemp;
	int m_page = 0;
	int m_alphaValue = 255;
	int m_alphaValueTwo = 0;

	bool isPushButton = false;
	bool isStart = false;
	bool isStartGame = false;
};