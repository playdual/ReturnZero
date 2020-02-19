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
	bool init(void* _info, bool isOnbattle) override;
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
	Image* m_Menu;
	Image* m_MenuCursor;
	Image* m_fromBattleMenu;
	Image* m_fromBattleCursor;

	Image* m_mainSwapOn;
	Image* m_mainSwapOff;
	Image* m_sub0SwapOn;
	Image* m_sub0SwapOff;
	Image* m_sub1SwapOn;
	Image* m_sub1SwapOff;
	Image* m_sub2SwapOn;
	Image* m_sub2SwapOff;
	Image* m_sub3SwapOn;
	Image* m_sub3SwapOff;
	Image* m_sub4SwapOn;
	Image* m_sub4SwapOff;
	Image* m_PokemonDie;

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

	UTIL::IRECT m_MenuRect;
	UTIL::IRECT m_MenuCursorRect;
	UTIL::IRECT m_fromBattleMenuRect;
	UTIL::IRECT m_fromBattleCursorRect;



	int m_indexCursor;
	int m_indexCursorMax;

	int m_indexCursorMenu1;
	int m_indexCursorMenu1Max;

	int m_pocketMonFrameIdx = 0;

	int m_InBagMenuIndex;
	int m_InBagMenuFromBattleIndex;

	bool isSwap = false;
	bool isDieMain = false;
	bool isDieSub0 = false;
	bool isDieSub1 = false;
	bool isDieSub2 = false;
	bool isDieSub3 = false;
	bool isDieSub4 = false;

	int m_swapIndexFirst;
	int m_swapIndexSecond;
	int m_swapIndexMax;
	int realRecovery;
	int m_memoryHp;
	float frameDelay = 0.5f;
	float pastTime = 0.f;

	bool m_isOnbattle = false;
	bool isItemUse = false;
	bool isEffectionItem = false;
	bool isMaxRecovery = false;
	bool isFromBattle = false;


	ItemInfo* rendedItemInfo = nullptr;
	std::vector<std::shared_ptr<PocketMon>>& Pocketmons;
};
