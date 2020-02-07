#pragma once
#include "Game/GameObject/Pocketmon/PocketMon.h"

class PocketmonManager
{
	
public:
	HRESULT init();
	void release();

	void update(float deltaTime);
	void render(HDC hdc);
	void afterRender(HDC hdc);
	void debugRender(HDC hdc);

	std::shared_ptr<PocketMon> getPlayerPocketmon();
	std::shared_ptr<PocketMon> getNpcPocketmon();
	std::shared_ptr<PocketMon> getWildPocketmon();

	//void battleStart();

private:
	std::vector<std::shared_ptr<PocketMon>> playerPocketmonVector;
	std::vector<std::shared_ptr<PocketMon>> npcPocketmonVector;
	std::vector<std::shared_ptr<PocketMon>> wildPocketmonVector;

private:
	DECLARE_SINGLE(PocketmonManager)
};

#define POCKETMONMANAGER PocketmonManager::GetInst()

