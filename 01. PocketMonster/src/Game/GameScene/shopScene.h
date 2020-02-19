#pragma once
#include "Game/GameScene/Scene.h"
#include "Game/GameObject/Items/Inventory.h"
#include "Game/GameManager/ItemManager.h"
#include "Game/GameObject/Character/player.h"

enum DECISIONMAKING
{ 
	YES = 0, NO
};
enum SHOPITEM
{
	MONSTERBALL = 0 , MEDICINE , GOODMEDICINE , LEVELUPCANDY , CLOSE
};

enum SHOPMAINMENU
{
	FIRSTMENU = 0 ,BUYITEM , SELLITEM ,  NOTHING, DEFAULT
};

class shopScene  
	: public Scene
{
public:
	shopScene(std::shared_ptr<Inventory> _inven );
	~shopScene();


public:
	virtual bool init() override;
	virtual void update(float _deltaTime) override;
	virtual void release() override;

public:
	virtual void render(HDC hdc) override;
	virtual void afterRender(HDC hdc) override;
	virtual void debugRender(HDC hdc) override;
	void firstRender(HDC hdc);

	/* buy */
	void buyRender(HDC hdc);
	void buySecondRender(HDC hdc);
	void buyThirdRender(HDC hdc);

	void sellRender(HDC hdc);
	void quitRender(HDC hdc);

	void printTextConsequentlyFirst(HDC hdc, std::string _wantText, int _destX, int _destY);
	void printTextConsequentlySecond(HDC hdc, std::string _wantText, int _destX, int _destY);
	void resetPrintText();

private:
	std::shared_ptr<Inventory> m_inven;
	std::vector<std::shared_ptr<Item>> m_shopItem;
	std::shared_ptr<player> m_player;
	SHOPMAINMENU shopMainMenu;
	SHOPITEM m_shopBuyItem;
	DECISIONMAKING m_decision;

	//이미지 리소스
	Image* m_friendlyShop;
	Image* m_npcTalkBox;
	Image* m_moneyStatus;
	Image* m_shopMainMenu;
	Image* m_currentPoint;
	
	/* BuyItem */
	Image* m_shopItemListMenu;
	Image* m_shopBuyItemBottom;
	Image* m_frinedlyShopBlowUp;
	Image* m_buyItemCount;
	Image* m_invenHaveItemCheck;
	Image* m_upArrow;
	Image* m_downArrow;
	Image* m_npcFrontTalkBox;
	Image* m_yesOrNoBox;
	
	// arrow Count
	int m_arrowCount = 0;
	bool m_isMaxCount = false;
	int m_itemCount = 1;
	bool m_isPlusFlow = false;

	// shop에 처음 들어왔을때
	bool m_ShopIn;
	// shop처음 충돌처리 대화
	bool m_isFirstTalk;

	// shop 메인 메뉴 ( 사러왔다 , 팔러 왔다 , 아닙니다. )
	bool m_isBuyItemShow;
	bool m_isSellItemShow;
	bool m_isQuitShop;

	// shop Buy 아이템을 골랐을때
	bool m_isBuyItemChoice;  /* buySecondRender() */
	bool m_isBuyItemCheck;	 /* buyThircRender() */

	// shop 에서 Item을 살때
	int m_ItemListNum;
	

	// shop 에서 ITem을 살때 (아이템 설명 문장 나눠주기위해)
	std::string shopItemDes_pokeBall[2] = { "", };
	std::string shopItemDes_Medicine[2] = { "", };
	std::string shopItemDes_GoodMedicine[2] = { "", };
	std::string shopItemDes_FireStone[2] = { "", };

	// 인벤에 있는 아이템 팔때 
	bool m_isSellChoiceItem;
	bool m_isSellCheckItem;
	bool m_isSellCompleteItem;

	// 화살 포인터
	int m_pointerCount;

	// 스트링형태를 char 형으로 하나씩 받아 한글자씩 보여주기 위해
	int		 m_charCount;
	bool     m_startTime;
	bool	 m_nextTalk;
	int		 m_count;
	int		 m_forCount;

	//문자열을 순차척으로 출력하기 위한 변수
	float addCharDelay = 0.1f;
	float pastTime = 0.f;
	int printStrLength;
	int firstTextIndex = 0;
	int secondTextIndex = 0;

	bool printFirstComplete = false;
	bool printSecondComplete = false;
	std::string printText[2] = { "", };
	float m_deltaTime;

	int wellcomeShopStrIndex = 0;
	int textCount = 0;
	int itemCountPrice = 0;

	// 대사 모음
	std::string m_wellomeShop[2] = { "WellCOME!" , "무엇을 도와 드릴까요?" }; // 처음에 npc와 충돌처리 났을 때
	std::string m_otherHelpShop[2] = { "그 밖에 저희가 " ,"뭐 도와드릴 건 없습니까?" }; // 그만둔다 했을때
	std::string m_menu[3] = { "사러 왔다" , "팔러 왔다" , "아닙니다" };  // 메인메뉴 
	std::string m_sellItemCheck[4] = { "파시겠습니까?","입니다" , "을 ", " 원 에 팔았다!" }; //물건을 샀을때 
	std::string m_buyItem[8] =
	{ "(를)을" , "몇개 구입하시겠습니까?" , "개 갖고 있음"," 개로군요." ,
		"총 ", "원입니다.","네 여기 있습니다.", "대단히 감사합니다." }; // 아이템 구매 1번째 창
	std::string m_select[2] = { "예" , "아니오" }; // 구매하시겠습니까? 답변
	std::string m_outShop = { "또 오세요!" };  // 메인메뉴에서 아닙니다.일때
	std::string m_money[2] = { "돈" , "원" };
	std::string m_printStr;
	//std::string str = "X0";

private:
	std::vector<std::string> talk; 
	void stringSplit();
	void buyItemChoice();
};

