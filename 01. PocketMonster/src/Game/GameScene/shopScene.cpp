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
	m_shopItem.push_back(ITEMMANAGER->findItem("닫기"));

	// 이미지 리소스 
	m_friendlyShop			= IMAGEMANAGER->findImage("프랜들리샵");
	m_frinedlyShopBlowUp	= IMAGEMANAGER->findImage("프랜들리샵확대");
	m_npcTalkBox			= IMAGEMANAGER->findImage("상점NPC대화상자");
	m_moneyStatus			= IMAGEMANAGER->findImage("상점돈상태창");
	m_shopMainMenu			= IMAGEMANAGER->findImage("상점메인메뉴");
	m_shopItemListMenu		= IMAGEMANAGER->findImage("상점아이템메뉴리스트");
	m_currentPoint			= IMAGEMANAGER->findImage("현재아이템표시");
	m_shopBuyItemBottom		= IMAGEMANAGER->findImage("상점아이템사기메뉴바텀");

	// bool값 초기화
	m_ShopIn				= true;
	m_isFirstTalk			= false;
	m_isBuyItemShow			= false;
	m_isSellItemShow		= false;
	m_isQuitShop			= false;
	m_isShowOutTalk			= false;
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
	if (printSecondComplete == true && m_pointerCount == BUYITEM)
	{
		if (KEYMANAGER->isOnceKeyDown(P1_Z))
		{
			shopMainMenu = BUYITEM;
			m_pointerCount = 0;
		}
	}

	if (shopMainMenu == BUYITEM)
	{
		 if (KEYMANAGER->isOnceKeyDown(P1_DOWN) && m_pointerCount < 3)
	    	m_pointerCount++;
	    if (KEYMANAGER->isOnceKeyDown(P1_UP) && m_pointerCount > 0)
	    	m_pointerCount--;
	}

}

void shopScene::release()
{
}

void shopScene::render(HDC hdc)
{
	if(m_ShopIn) { m_friendlyShop->render(hdc, 160, 110);}

	switch (shopMainMenu)
	{
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
	// 이미지 && 텍스트 랜더 
	m_frinedlyShopBlowUp->render(hdc, 0,100);
	m_shopItemListMenu->render(hdc, WINSIZEX / 2 - 90, -5);
	m_shopBuyItemBottom->render(hdc, 0, WINSIZEY - 280);
	m_moneyStatus->render(hdc,0, 5);
	// 플레이어 돈 넣어주기

	// 아이템 목록 랜더
	

	for (int i = 0; i < 4; i++)
	{
		UTIL::PrintText(hdc, m_shopItem[i]->getItemName().c_str(), "소야바른9", WINSIZEX/2 - 20 , 40 + (i*70), 65, RGB(0, 0, 0), true);		
	}

	switch (m_pointerCount)
	{
	case MONSTERBALL:
		m_currentPoint->render(hdc, WINSIZEX / 2 - 95, 10 + (m_pointerCount * 70));
		break;

	case MEDICINE:
		m_currentPoint->render(hdc, WINSIZEX / 2 - 95, 10 + (m_pointerCount * 70));
		break;

	case GOODMEDICINE:
		m_currentPoint->render(hdc, WINSIZEX / 2 - 95, 10 + (m_pointerCount * 70));
		break;

	case LEVELUPCANDY:
		m_currentPoint->render(hdc, WINSIZEX / 2 - 95, 10 + (m_pointerCount * 70));
		break;

	case CLOSE:
		m_currentPoint->render(hdc, WINSIZEX / 2 - 95, 10 + (m_pointerCount * 70));
		break;

	default:
		break;
	}
}

void shopScene::sellRender(HDC hdc)
{
}

void shopScene::quitRender(HDC hdc)
{
}

void shopScene::afterRender(HDC hdc)
{
}

void shopScene::debugRender(HDC hdc)
{
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