#pragma once
#include "Game/GameObject/Pocketmon/PocketMon.h"

/*
기능
1. 포켓몬들의 기본 정보를 보관하고 있다.
2. 플레이어와 타운,  npc에 포켓몬의 정보를 복사해서 보내준다
3. 벡터 1, 2, 3번 컨테이너에는 태초마을에서 플레이어가 선택하게 되는 포켓몬 정보가 들어있다.
4. 포켓몬 레벨 확인 및 능력치 상승
*/
class PocketmonManager
{
	
public:
	HRESULT init();
	void release();

	void update(float deltaTime);
	void render(HDC hdc);
	void afterRender(HDC hdc);
	void debugRender(HDC hdc);

	PocketMon getPocketmonInform(int i);

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
	std::vector<PocketMon> pocketmonVector;

private:
	DECLARE_SINGLE(PocketmonManager)
};

#define POCKETMONMANAGER PocketmonManager::GetInst()

