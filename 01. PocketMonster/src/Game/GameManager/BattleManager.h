#pragma once
#include "Game/GameObject/Character/Character.h"
#include "Game/GameObject/PocketMon/PocketMon.h"

class BattleManager
{

public:
	HRESULT init();
	void release();

	void update(float deltaTime);
	void render(HDC hdc);
	void afterRender(HDC hdc);
	void debugRender(HDC hdc);

	void battleStart();

private:
	UTIL::IRECT testRect;
	std::shared_ptr<Character> m_player;

	//std::vector<std::shared_ptr<PocketMon>> playerPocketmonVector;

private:
	DECLARE_SINGLE(BattleManager)
};

#define BATTLEMANAGER BattleManager::GetInst()
