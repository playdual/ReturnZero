#pragma once
#include"Game/GameObject/Character.h"
class BattleManager
{

public:
	HRESULT init();
	void release();

	void update(float deltaTime);
	void render(HDC hdc);
	void afterRender(HDC hdc);
	void debugRender(HDC hdc);

private:
	UTIL::IRECT testRect;

	std::shared_ptr<Character> m_player;

private:
	DECLARE_SINGLE(BattleManager)
};

#define BATTLEMANAGER BattleManager::GetInst()
