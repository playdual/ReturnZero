#pragma once
#include "Game/GameScene/Scene.h"
#include "Game/GameObject/Items/Inventory.h"
#include "Game/GameManager/ItemManager.h"
#include "Game/GameObject/Character/player.h"

enum SHOPMAINMENU
{
	FIRSTMENU = 0 ,BUYITEM , SELLITEM ,  NOTHING
};

class shopScene  
	: public Scene
{
public:
	shopScene(std::shared_ptr<Inventory> _inven );
	~shopScene();


public:
	virtual bool init() override;
	virtual bool init(void* _info, bool isOnBattle) override;
	virtual void update(float _deltaTime) override;
	virtual void release() override;

public:
	virtual void render(HDC hdc) override;
	virtual void afterRender(HDC hdc) override;
	virtual void debugRender(HDC hdc) override;
	void firstRender(HDC hdc);
	void buyRender(HDC hdc);
	void sellRender(HDC hdc);
	void quitRender(HDC hdc);
	void currentPointerCount();  // 화살표 방향 카운트 처리 함수

private:
	std::shared_ptr<Inventory> m_inven;
	std::vector<std::shared_ptr<Item>> m_shopItem;
	SHOPMAINMENU shopMainMenu;

	//이미지 리소스
	Image* m_friendlyShop;
	Image* m_npcTalkBox;
	Image* m_moneyStatus;
	Image* m_shopMainMenu;
	Image* m_shopItemListMenu;
	Image* m_currentPoint;
	
	// shop처음 충돌처리 대화
	bool m_isFirstTalk;

	// shop 메인 메뉴 ( 사러왔다 , 팔러 왔다 , 아닙니다. )
	bool m_isBuyItemShow;
	bool m_isSellItemShow;
	bool m_isQuitShop;

	// shop 사러왔음 ( 그만둔다 -> 보여주는 대화상자)
	bool m_isShowOutTalk; 

	// 인벤에 있는 아이템 팔때 
	bool m_isSellChoiceItem;
	bool m_isSellCheckItem;
	bool m_isSellCompleteItem;

	// 화살 포인터
	int m_pointerCount;

	// 스트링형태를 char 형으로 하나씩 받아 한글자씩 보여주기 위해
	char m_stringInput[100];  
	int m_charCount;

	// 대사 모음
	std::string m_wellomeShop[2] = { "어서 오세요!" , "무엇을 도와 드릴까요?" }; // 처음에 npc와 충돌처리 났을 때
	std::string m_otherHelpShop[2] = { "그 밖에 저희가 " ,"뭐 도와드릴 건 없습니까?" }; // 그만둔다 했을때
	std::string m_menu[3] = { "사러 왔다" , "팔러 왔다" , "아닙니다" };  // 메인메뉴 
	std::string m_sellItemCheck[4] = { "파시겠습니까?","입니다" , "을 ", " 원 에 팔았다!" }; //물건을 샀을때 
	std::string m_buyItem[8] =
	{ "(를)을" , "몇개 구입하시겠습니까?" , "개 갖고 있음","개로군요." ,
		"총 ", "원입니다.","네 여기 있습니다.", "대단히 감사합니다." }; // 아이템 구매 1번째 창
	std::string m_select[2] = { "예" , "아니오" }; // 구매하시겠습니까? 답변
	std::string m_outShop = { "또 오세요!" };  // 메인메뉴에서 아닙니다.일때
	std::string m_money[2] = { "돈" , "원" };

};

