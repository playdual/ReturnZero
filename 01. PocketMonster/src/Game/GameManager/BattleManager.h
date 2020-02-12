#pragma once
#include "Game/GameObject/Character/Character.h"
#include "Game/GameObject/PocketMon/PocketMon.h"
#include "Game/GameObject/Character/player.h"

class BattleManager
{

public:
	HRESULT init();
	void release();

	void update(float deltaTime);
	void render(HDC hdc);
	void afterRender(HDC hdc);
	void debugRender(HDC hdc);

	void battleStart(); // for Test
	void battleStart(std::shared_ptr<player> _player, std::shared_ptr<player> _npc, std::string _pocketmonName = "", int _level = 0);

private:
	UTIL::IRECT testRect;
	std::shared_ptr<Character> m_player;

	//std::vector<std::shared_ptr<PocketMon>> playerPocketmonVector;

private:
	DECLARE_SINGLE(BattleManager)
};

#define BATTLEMANAGER BattleManager::GetInst()
