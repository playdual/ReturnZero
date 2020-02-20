#pragma once
#include "Game/GameScene/Scene.h"
#include "Game/GameObject/Items/Inventory.h"
#include "Game/GameObject/Character/player.h"

enum SELLDECISION
{
	INVEN_YES = 0 , INVEN_NO
};

struct InventoryResult {
	//std::shre usedImtem = nullptr;
	

};

class InvenScene 
	: public Scene
{
public:
	InvenScene(std::shared_ptr<Inventory> _inven);
	~ InvenScene();

public:
	virtual bool init() override;
	virtual bool init(void* _info, bool isOnBattle) override;
	virtual void update(float _deltaTime) override;

public:
	virtual void release() override;
	virtual void render(HDC hdc) override;
	virtual void afterRender(HDC hdc) override;
	virtual void debugRender(HDC hdc) override;


public:

	// 디폴트 파는 씬
	void sellPotion();
	void setSettedItem();
	void sellImport();
	void sellPokeBall();
	void setSellInven(bool _isSell) { m_isSell = _isSell; }

	// 디폴트 아이템 획득씬
	void buyPotionScene(HDC hdc); // 상점에서 팔때
	void buyPotionFirstScene(HDC hdc);
	void buyPotionSecondScene(HDC hdc);
	ItemInfo getItemInfo();

private:
	void checkSceneChangeInfo();

private:
	std::shared_ptr<Inventory> m_inven;
	SELLDECISION sellDecision;

	Image* m_BackGround;
	
	// 인벤창 가방 이미지 //
	Image* m_ItemBag;
	Image* m_ImportBag;
	Image* m_PokeBallBag;
	// 인벤 태그 이미지 //
	Image* m_ItemTag;
	Image* m_ImporTag;
	Image* m_PokeBallTag;
	//  인벤 화살표 UI 이미지 //
	Image* m_nextArrow;
	Image* m_beforeArrow;
	// 인벤 선택 메뉴
	Image* m_ItemInvenMenu;
	Image* m_otherInvenMenu;
	Image* m_battleSceneInvenMenu;

	Image* m_invenMenuBottom;
	Image* m_currentPointer;

	// 아이템 파는 작업
	Image* m_moneyBox;
	Image* m_yesOrNoBox;
	Image* m_NpcBox;
	Image* m_currentArrow;
	bool	m_isSell = false;
	int		m_sellCount = 0;
	bool	m_isSellSecond = false;
	int		m_count = 0;

	INVENSCENETYPE m_invenSceneType;
	//인벤씬 변경시 사용할 카운트
	int		invenSceneCount;
	bool	isChangeScene;

	// UI 카운트 작업
	int		moveCount ;
	bool	isUp;

	// 상점 연습 작업
	int ShopCount;

	// 인벤이 배틀씬 중 켜지느냐? 아니냐 / 타운씬에서 켜지느냐? 아니냐
	bool isTownInven;
	bool isBattleInven;


	//아이템 버릴때 쓰는 문장
	std::string  m_throwItem[5] = { "몇개 버릴까요?", "개 버려도" , "괜찮겠습니까?" , "를(을)" ,"개 버렸습니다."};
	std::string  m_throwAnser[2] = { "예", "아니오" };
	bool m_isThrowItem;
	int m_throwItemCount;
	

	std::string  m_itemChoiceMenu[5] = { "쓴다" , "건네다" , "버린다" , "그만둠" , "어떻게 할까요?" };
	std::string  m_importChoiceMenu[4] = { "쓴다" , "등록" , "그만둠", "어떻게 할까요?" };
	std::string  m_ballChoiceMenu[4] = { "건네다" , "버린다" , "그만둠", "어떻게 할까요?" };

	std::string m_battleSceneItemMenu[3] = { "쓴다" , "그만둠" , "어떻게 할까요?" };
	std::string m_battleSceneImportMenu[2] = { "그만둠" , "어떻게 할까요?" };
	std::string m_select[2] = { "예" , "아니오" };
	std::string m_money[2] = { "돈" , "원" };
	std::string m_sellItem[3] = { "이로구나~"," 건네주고", " 을 받았다!!" };
	
	// 메뉴창 작업
	int pointerCount;
	bool m_isMainClose = false;

	//샵이랑 연계
	std::string sellItem;

	void printTextConsequentlyFirst(HDC hdc, std::string _wantText, int _destX, int _destY);
	void printTextConsequentlySecond(HDC hdc, std::string _wantText, int _destX, int _destY);
	void resetPrintText();
private:
	ItemInfo m_settedItemInfo;
	std::shared_ptr<player> m_player;
	std::string printText[2] = { "", };
	bool printFirstComplete = false;
	bool printSecondComplete = false;
	bool isSellFirst = false;
	float m_deltaTime;
	float pastTime = 0.f;
	float addCharDelay = 0.1f;
	int firstTextIndex = 0;
	int secondTextIndex = 0;
	int returnMoney = 0;
	int sellAfterMoney = 0;

};

