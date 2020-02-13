#pragma once
#include "Scene.h"
#include "Game/GameObject/Pocketmon/PocketMon.h"

class PocketmoninfoScene : public Scene
{
public:
	PocketmoninfoScene(std::vector<std::shared_ptr<PocketMon>>& _Pocketmons);
	~PocketmoninfoScene();

public:
	bool init() override;
	void update(float _deltaTime) override;
	void release() override;

	void render(HDC hdc) override;
	void afterRender(HDC hdc) override;
	void debugRender(HDC hdc) override;

private:
	Image* m_Base;
	Image* m_mainOn;
	Image* m_mainOff;
	Image* m_sub0On;
	Image* m_sub0Off;
	Image* m_sub1On;
	Image* m_sub1Off;
	Image* m_sub2On;
	Image* m_sub2Off;
	Image* m_sub3On;
	Image* m_sub3Off;
	Image* m_sub4On;
	Image* m_sub4Off;
	Image* m_cancleOn;
	Image* m_cancleOff;
	Image* m_sexMan;
	Image* m_sexWoman;

	Image* m_mainHpBarGreen;
	Image* m_sub0HpBarGreen;
	Image* m_sub1HpBarGreen;
	Image* m_sub2HpBarGreen;
	Image* m_sub3HpBarGreen;
	Image* m_sub4HpBarGreen;
	Image* m_mainHpBarYellow;
	Image* m_sub0HpBarYellow;
	Image* m_sub1HpBarYellow;
	Image* m_sub2HpBarYellow;
	Image* m_sub3HpBarYellow;
	Image* m_sub4HpBarYellow;
	Image* m_mainHpBarRed;
	Image* m_sub0HpBarRed;
	Image* m_sub1HpBarRed;
	Image* m_sub2HpBarRed;
	Image* m_sub3HpBarRed;
	Image* m_sub4HpBarRed;


	UTIL::IRECT m_mainRect;
	UTIL::IRECT m_mainIconRect;
	UTIL::IRECT m_subRect0;
	UTIL::IRECT m_subIconRect0;
	UTIL::IRECT m_subRect1;
	UTIL::IRECT m_subIconRect1;
	UTIL::IRECT m_subRect2;
	UTIL::IRECT m_subIconRect2;
	UTIL::IRECT m_subRect3;
	UTIL::IRECT m_subIconRect3;
	UTIL::IRECT m_subRect4;
	UTIL::IRECT m_subIconRect4;
	UTIL::IRECT m_cancle;


	int m_indexCursor;
	int m_indexCursorMax;
	int m_pocketMonFrameIdx = 0;
	float frameDelay = 0.5f;
	float pastTime = 0.f;

	std::vector<std::shared_ptr<PocketMon>>& Pocketmons;
};