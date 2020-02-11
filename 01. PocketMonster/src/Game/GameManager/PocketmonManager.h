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

	PocketMon genPocketMon(std::string _name, int level);


public:
	PocketMon genCharmander(int level);//파이리
	PocketMon genBulbasaur(int level);//이상해씨
	PocketMon genSquirtle(int level);//꼬부기
	PocketMon genPidgey(int level);//구구
	PocketMon genPikachu(int level);//피카츄
	PocketMon genCaterpie(int level);//캐터피
	PocketMon genRattata(int level);//꼬렛
	PocketMon genVulpix(int level);//식스테일
	PocketMon genOddish(int level);//뚜벅초
	PocketMon genPoliwag(int level);//발챙이

private:
	std::vector<std::shared_ptr<PocketMon>> playerPocketmonVector;
	std::vector<std::shared_ptr<PocketMon>> npcPocketmonVector;
	std::vector<std::shared_ptr<PocketMon>> wildPocketmonVector;

private:
	DECLARE_SINGLE(PocketmonManager)
};

#define POCKETMONMANAGER PocketmonManager::GetInst()

