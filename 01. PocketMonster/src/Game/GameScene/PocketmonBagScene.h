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

	UTIL::IRECT m_mainRect;
	UTIL::IRECT m_subRect0;
	UTIL::IRECT m_subRect1;
	UTIL::IRECT m_subRect2;
	UTIL::IRECT m_subRect3;
	UTIL::IRECT m_subRect4;


	int m_indexCursor;
	int m_indexCursorMax;

	std::vector<std::shared_ptr<PocketMon>>& Pocketmons;
};