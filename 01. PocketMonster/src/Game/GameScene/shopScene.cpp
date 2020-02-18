#include "stdafx.h"
#include "shopScene.h"

shopScene::shopScene(std::shared_ptr<Inventory> _inven)
{
	m_inven = _inven;
}

shopScene::~shopScene()
{
}

bool shopScene::init()
{
	m_player = std::make_shared<player>();
	//m_player->init();

	// 아이템 PUSH
	m_shopItem.push_back(ITEMMANAGER->findItem("몬스터볼"));
	m_shopItem.push_back(ITEMMANAGER->findItem("상처약"));
	m_shopItem.push_back(ITEMMANAGER->findItem("좋은상처약"));
	m_shopItem.push_back(ITEMMANAGER->findItem("불꽃의돌"));
	m_shopItem.push_back(ITEMMANAGER->findItem("닫기"));

	// 아이템 순서 재정의
	for (int i = 0; i < 5; i++)
	{
		m_shopItem[i]->setItemNum(i);
	}

	// 이미지 리소스 
	m_friendlyShop			= IMAGEMANAGER->findImage("프랜들리샵");
	m_frinedlyShopBlowUp	= IMAGEMANAGER->findImage("프랜들리샵확대");
	m_npcTalkBox			= IMAGEMANAGER->findImage("상점NPC대화상자");
	m_moneyStatus			= IMAGEMANAGER->findImage("상점돈상태창");
	m_shopMainMenu			= IMAGEMANAGER->findImage("상점메인메뉴");
	m_shopItemListMenu		= IMAGEMANAGER->findImage("상점아이템메뉴리스트");
	m_currentPoint			= IMAGEMANAGER->findImage("현재아이템표시");
	m_shopBuyItemBottom		= IMAGEMANAGER->findImage("상점아이템사기메뉴바텀");
	m_upArrow				= IMAGEMANAGER->findImage("위로화살표");
	m_downArrow				= IMAGEMANAGER->findImage("아래화살표");
	m_invenHaveItemCheck	= IMAGEMANAGER->findImage("상점인벤체크박스");
	m_npcFrontTalkBox		= IMAGEMANAGER->findImage("상점두번째NPC대화상자");
	m_buyItemCount			= IMAGEMANAGER->findImage("상점아이템카운트박스");

	// bool값 초기화
	m_ShopIn				= true;
	m_isFirstTalk			= false;
	m_isBuyItemShow			= false;
	m_isSellItemShow		= false;
	m_isQuitShop			= false;
	m_isBuyItemChoice		= false;
	m_isSellChoiceItem		= false;
	m_isSellCheckItem		= false;
	m_isSellCompleteItem	= false;
	m_startTime				= false;

	// 화살 포인터(카운트)
	m_pointerCount			= 1;

	// string -> char [ 한글자씩 보여주기 위해 받아준다. ]
	m_nextTalk				= false;
	m_charCount				= 0;
	m_printStr				= { "", };
	m_count					= 0;
	m_forCount				= 0;
	printStrLength = m_wellomeShop[1].length();

	//디폴트 설정
	shopMainMenu = DEFAULT;

	// BUYITEM 할때 아이템 넘버 체크

	return true;
}

bool shopScene::init(void * _info, bool isOnBattle)
{
	init();
	return true;
}

void shopScene::update(float _deltaTime)
{ 
	m_deltaTime = _deltaTime;
	
	/* 아이템 카운트 */
	if (m_isBuyItemChoice)
	{
		if ((m_shopItem[m_pointerCount]->getPrice() * m_itemCount) <= m_player->getMoney() && !m_isPlusFlow )
		{
			itemCountPrice = m_shopItem[m_pointerCount]->getPrice() * m_itemCount;
		}
		 if (itemCountPrice + m_shopItem[m_pointerCount]->getPrice() > m_player->getMoney())
		{
			m_isPlusFlow = true;
		}
	}

	/* 화살 애니메이션 */
	if (m_isBuyItemChoice)
	{
		if (m_arrowCount < 20 && !m_isMaxCount)
		{
			m_arrowCount++;
			if(m_arrowCount == 20)
			 m_isMaxCount = true;
		}
	    if (m_isMaxCount)
	    {
	    	m_arrowCount--;
	    	if (m_arrowCount == 0)
	    		m_isMaxCount = false;
	    }
	}
	/* 화살 애니메이션 */


	if (KEYMANAGER->isOnceKeyDown(GAME_MENU))
	{
		shopMainMenu = FIRSTMENU;
		m_startTime = true;
	}
	
	//if (KEYMANAGER->isOnceKeyDown(P1_Z)) {
	//	resetPrintText();
	//}

	// 샵 메인메뉴 ( 사러왔다 , 팔러 왔다 , 아닙니다. ) -> 지목할 currentImage포인터
	if (printSecondComplete && shopMainMenu == FIRSTMENU)
	{
	    if (KEYMANAGER->isOnceKeyDown(P1_DOWN) && m_pointerCount < 3)
	    	m_pointerCount++;
	    if (KEYMANAGER->isOnceKeyDown(P1_UP) && m_pointerCount > 1)
	    	m_pointerCount--;
	}

	if (shopMainMenu == BUYITEM && !m_isBuyItemChoice)
	{
		 if (KEYMANAGER->isOnceKeyDown(P1_DOWN) && m_pointerCount < 4)
	    	m_pointerCount++;
	    if (KEYMANAGER->isOnceKeyDown(P1_UP) && m_pointerCount > 0)
	    	m_pointerCount--;
	}
	if (m_isBuyItemChoice)
	{
		if (KEYMANAGER->isOnceKeyDown(P1_DOWN) && !m_isPlusFlow)
			m_itemCount++;
		if (KEYMANAGER->isOnceKeyDown(P1_UP) && m_itemCount >= 1)
		{
			if(m_itemCount > 1)
			m_itemCount--;

			m_isPlusFlow = false;
		}
	}

	// ======================== KEYMANAGER->isOnceKeyDown(P1_Z) 키 모음 ======================== //
	/*  BUYITEM 관련된  Z */
	if (printSecondComplete == true && m_pointerCount == BUYITEM && !m_isBuyItemShow)
	{
		if (KEYMANAGER->isOnceKeyDown(P1_Z))
		{
			shopMainMenu = BUYITEM;
			m_pointerCount = 0;
		}
	}
	if (m_isBuyItemShow == true && m_pointerCount == CLOSE && KEYMANAGER->isOnceKeyDown(P1_Z))
	{
	    shopMainMenu = FIRSTMENU; 
	    m_pointerCount = 1;
		m_isBuyItemShow = false;
	}

	if (!m_isBuyItemChoice && shopMainMenu == BUYITEM && m_pointerCount != CLOSE && KEYMANAGER->isOnceKeyDown(P1_Z))
		m_isBuyItemChoice = true;


	/* 초기 메인메뉴 NOTHING */
	if (printSecondComplete == true && m_pointerCount == NOTHING && shopMainMenu == FIRSTMENU)
	{
		if (KEYMANAGER->isOnceKeyDown(P1_Z))
		{
			shopMainMenu = DEFAULT;
			m_ShopIn = true;
			m_pointerCount = 1;
		}
	}
	// ======================== KEYMANAGER->isOnceKeyDown(P1_Z) 키 모음 ======================== //
	//if (printSecondComplete == true && shopMainMenu == DEFAULT)
	//{
	//	if (KEYMANAGER->isOnceKeyDown(P1_Z) && m_pointerCount == DEFAULT)
	//	{
	//		m_ShopIn = true;
	//		m_pointerCount = 1;
	//	}
	//}


}

void shopScene::release()
{
}

void shopScene::render(HDC hdc)
{
	switch (shopMainMenu)
	{
	case DEFAULT:
		if (m_ShopIn) { m_friendlyShop->render(hdc, 160, 110); }
		break;

	case FIRSTMENU:
		firstRender(hdc);
		break;

	case BUYITEM:
		m_ShopIn = false;
		 buyRender(hdc);
		break;

	case SELLITEM:
		m_ShopIn = false;
		sellRender(hdc);
		break;

	case NOTHING:
		m_ShopIn = false;
		quitRender(hdc);
		break;

	default:
		break;
	}
}

void shopScene::firstRender(HDC hdc)
{
	// 첫번째 메인 npc 박스 
	m_friendlyShop->render(hdc, 160, 110);
	m_npcTalkBox->render(hdc,  20 , WINSIZEY - 250);

	if (printSecondComplete)
	{
		m_shopMainMenu->render(hdc, 20, 20);
		UTIL::PrintText(hdc, m_menu[0].c_str(), "소야바른9", 100, 50, 65, RGB(0, 0, 0), true);
		UTIL::PrintText(hdc, m_menu[1].c_str(), "소야바른9", 100, 120, 65, RGB(0, 0, 0), true);
		UTIL::PrintText(hdc, m_menu[2].c_str(), "소야바른9", 100, 190, 65, RGB(0, 0, 0), true);

		switch (m_pointerCount)
		{
		case BUYITEM:
			m_currentPoint->render(hdc, 20, 10);
			//shopMainMenu = BUYITEM;
			break;

		case SELLITEM:
			m_currentPoint->render(hdc, 20, 85);
			//shopMainMenu = SELLITEM;
			break;

		case NOTHING:
			m_currentPoint->render(hdc, 20, 155);
			//shopMainMenu = NOTHING;
			break;

		default:
			break;
		}
	}

	if (!m_isFirstTalk)
	{
		printTextConsequentlyFirst(hdc, m_wellomeShop[0], 80, WINSIZEY - 210);
		printTextConsequentlySecond(hdc, m_wellomeShop[1], 80, WINSIZEY - 150);
	}
}

void shopScene::buyRender(HDC hdc)
{
	stringSplit();
	m_isBuyItemShow = true;

	// 이미지 && 텍스트 랜더 
	m_frinedlyShopBlowUp->render(hdc, 0,100);
	m_shopItemListMenu->render(hdc, WINSIZEX / 2 - 90, -5);
	m_shopBuyItemBottom->render(hdc, 0, WINSIZEY - 280);
	m_moneyStatus->render(hdc,0, 5);

	// 아이템 목록 랜더
	for (int i = 0; i < 5; i++)
	{
		UTIL::PrintText(hdc, m_shopItem[i]->getItemName().c_str(), "소야바른9", WINSIZEX/2 - 20 , 40 + (i*70), 65, RGB(0, 0, 0), true);		
		if (i < 4)
		{
			UTIL::PrintText(hdc,std::to_string( m_shopItem[i]->getPrice()).c_str(), "소야바른9", WINSIZEX/2 +280, 40 + (i * 70), 65, RGB(0, 0, 0), true);
			UTIL::PrintText(hdc, m_money[1].c_str(), "소야바른9", WINSIZEX/2 +400, 40 + (i * 70), 65, RGB(0, 0, 0), true);
		}
	}
	
	// 플레어 소지금 랜더
	UTIL::PrintText(hdc, std::to_string(m_player->getMoney()).c_str(), "소야바른9", 200, 120, 70, RGB(0, 0, 0), true);
	UTIL::PrintText(hdc, m_money[0].c_str(), "소야바른9", 40, 40, 90, RGB(0, 0, 0), true);
	UTIL::PrintText(hdc, m_money[1].c_str(), "소야바른9", 335, 115, 70, RGB(0, 0, 0), true);

	switch (m_pointerCount)
	{
	case MONSTERBALL:
		m_currentPoint->render(hdc, WINSIZEX / 2 - 95, 10 + (m_pointerCount * 70));
		m_shopItem[0]->getImage()->render(hdc, 52, WINSIZEY - 210);
		UTIL::PrintText(hdc, shopItemDes_pokeBall[0].c_str(), "소야바른9", 200, WINSIZEY - 230 , 70, RGB(255, 255, 255), true);
		UTIL::PrintText(hdc, shopItemDes_pokeBall[1].c_str(), "소야바른9", 200, WINSIZEY - 150 , 70, RGB(255, 255, 255), true);
		if (m_isBuyItemChoice) buyNextRender(hdc);
		break;

	case MEDICINE:
		m_currentPoint->render(hdc, WINSIZEX / 2 - 95, 10 + (m_pointerCount * 70));
		m_shopItem[1]->getImage()->render(hdc, 52, WINSIZEY - 210);
		UTIL::PrintText(hdc, shopItemDes_Medicine[0].c_str(), "소야바른9", 200, WINSIZEY - 230, 68, RGB(255, 255, 255), true);
		UTIL::PrintText(hdc, shopItemDes_Medicine[1].c_str(), "소야바른9", 200, WINSIZEY - 150, 68, RGB(255, 255, 255), true);
		if (m_isBuyItemChoice) buyNextRender(hdc);
		break;

	case GOODMEDICINE:
		m_currentPoint->render(hdc, WINSIZEX / 2 - 95, 10 + (m_pointerCount * 70));
		m_shopItem[2]->getImage()->render(hdc, 52, WINSIZEY - 210);
		UTIL::PrintText(hdc, shopItemDes_GoodMedicine[0].c_str(), "소야바른9", 200, WINSIZEY - 230, 68, RGB(255, 255, 255), true);
		UTIL::PrintText(hdc, shopItemDes_GoodMedicine[1].c_str(), "소야바른9", 200, WINSIZEY - 150, 68, RGB(255, 255, 255), true);
		if (m_isBuyItemChoice) buyNextRender(hdc);
		break;

	case LEVELUPCANDY:
		m_currentPoint->render(hdc, WINSIZEX / 2 - 95, 10 + (m_pointerCount * 70));
		m_shopItem[3]->getImage()->render(hdc, 52, WINSIZEY - 210);
		UTIL::PrintText(hdc, shopItemDes_FireStone[0].c_str(), "소야바른9", 200, WINSIZEY - 230, 68, RGB(255, 255, 255), true);
		UTIL::PrintText(hdc, shopItemDes_FireStone[1].c_str(), "소야바른9", 200, WINSIZEY - 150, 68, RGB(255, 255, 255), true);
		if (m_isBuyItemChoice) buyNextRender(hdc);
		break;

	case CLOSE:
		m_currentPoint->render(hdc, WINSIZEX / 2 - 95, 10 + (m_pointerCount * 70));
		m_shopItem[4]->getImage()->render(hdc, 52, WINSIZEY - 210);
		UTIL::PrintText(hdc, m_shopItem[4]->getDescript().c_str(), "소야바른9", 200, WINSIZEY - 190, 68, RGB(255, 255, 255), true);
		break;

	default:
		break;
	}
}

void shopScene::sellRender(HDC hdc)
void shopScene::buyNextRender(HDC hdc)
{
}
	std::string str = "X0";
	str += std::to_string(m_itemCount).c_str();

	/* 랜더 부분 */
	m_npcFrontTalkBox->render(hdc, 0, WINSIZEY - 270);
	m_invenHaveItemCheck->render(hdc, 10, WINSIZEY / 2 - 20);
	m_buyItemCount->render(hdc, WINSIZEX / 2 + 95, WINSIZEY / 2 - 100);
	m_upArrow->render(hdc, WINSIZEX / 2 + 155, WINSIZEY / 2 - 100 - m_arrowCount);
	m_downArrow->render(hdc, WINSIZEX / 2 + 155, WINSIZEY / 2 + 30 + m_arrowCount);

	UTIL::PrintText(hdc, str.c_str(), "소야바른9", WINSIZEX/2 + 140, WINSIZEY /2 - 15, 70, RGB(0, 0, 0), true);
	if(itemCountPrice < 1000)
	UTIL::PrintText(hdc, std::to_string(itemCountPrice).c_str(), "소야바른9", WINSIZEX/2 + 320, WINSIZEY /2 - 15, 70, RGB(0, 0, 0), true);
	else
		UTIL::PrintText(hdc, std::to_string(itemCountPrice).c_str(), "소야바른9", WINSIZEX/2 + 300, WINSIZEY /2 - 15, 70, RGB(0, 0, 0), true);
	
	UTIL::PrintText(hdc, m_money[1].c_str(), "소야바른9", WINSIZEX/2 + 430, WINSIZEY /2 - 15, 70, RGB(0, 0, 0), true);

void shopScene::quitRender(HDC hdc)
{
}

void shopScene::sellRender(HDC hdc)
{
}

void shopScene::quitRender(HDC hdc)
{
}

void shopScene::buyItemChoice()
{

}

void shopScene::printTextConsequentlyFirst(HDC hdc, std::string _wantText, int _destX, int _destY)
{
	if (printFirstComplete == false) 
	{
		if (KEYMANAGER->isOnceKeyDown(P1_X))
		{
			printText[0] = _wantText;
			printFirstComplete = true;
		}
		pastTime += m_deltaTime;
		if (addCharDelay < pastTime)
		{
			pastTime = 0.f;
			if (printText[0].length() < _wantText.length())
				printText[0] += _wantText[firstTextIndex++];
			else
				printFirstComplete = true;
		}
	}
	UTIL::PrintText(hdc, printText[0].c_str(), "소야바른9", _destX, _destY, 60, RGB(0, 0, 0), true);
}

void shopScene::printTextConsequentlySecond(HDC hdc, std::string _wantText, int _destX, int _destY)
{
	if (printFirstComplete == true && printSecondComplete == false)
	{
		if (KEYMANAGER->isOnceKeyDown(P1_X))
		{
			printText[1] = _wantText;
			printSecondComplete = true;
		}
		pastTime += m_deltaTime;
		if (addCharDelay < pastTime)
		{
			pastTime = 0.f;
			if (printText[1].length() < _wantText.length())
				printText[1] += _wantText[secondTextIndex++];
			else
				printSecondComplete = true;
		}
	}
	UTIL::PrintText(hdc, printText[1].c_str(), "소야바른9", _destX, _destY, 60, RGB(0, 0, 0), true);
}
void shopScene::resetPrintText()
{
	printText[0] = "";
	printText[1] = "";

	printFirstComplete = false;
	printSecondComplete = false;

	firstTextIndex = 0;
	secondTextIndex = 0;
}

void shopScene::stringSplit()
{
	// string 문자열 자르기
	/* 포켓몬볼 */
	shopItemDes_pokeBall[0] = m_shopItem[0]->getDescript().substr(0, 36);
	shopItemDes_pokeBall[1] = m_shopItem[0]->getDescript().substr(37, 21);

	/* 상처약 */
	shopItemDes_Medicine[0] = m_shopItem[1]->getDescript().substr(0, 20);
	shopItemDes_Medicine[1] = m_shopItem[1]->getDescript().substr(21, 38);

	/* 더 좋은 상처약 */
	shopItemDes_GoodMedicine[0] = m_shopItem[2]->getDescript().substr(0, 20);
	shopItemDes_GoodMedicine[1] = m_shopItem[2]->getDescript().substr(21, 38);

	/* 불꽃의돌 */
	shopItemDes_FireStone[0] = m_shopItem[3]->getDescript().substr(0, 31);
	shopItemDes_FireStone[1] = m_shopItem[3]->getDescript().substr(32, 50);

}
void shopScene::afterRender(HDC hdc)
{
}

void shopScene::debugRender(HDC hdc)
{
}


