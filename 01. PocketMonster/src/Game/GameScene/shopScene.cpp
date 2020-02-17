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
	// 아이템 PUSH
	m_shopItem.push_back(ITEMMANAGER->findItem("몬스터볼"));
	m_shopItem.push_back(ITEMMANAGER->findItem("상처약"));
	m_shopItem.push_back(ITEMMANAGER->findItem("좋은상처약"));
	m_shopItem.push_back(ITEMMANAGER->findItem("닫기"));

	// 이미지 리소스 
	m_friendlyShop			= IMAGEMANAGER->findImage("프랜들리샵");
	m_npcTalkBox			= IMAGEMANAGER->findImage("상점NPC대화상자");
	m_moneyStatus			= IMAGEMANAGER->findImage("상점돈상태창");
	m_shopMainMenu			= IMAGEMANAGER->findImage("상점메인메뉴");
	m_shopItemListMenu		= IMAGEMANAGER->findImage("상점아이템메뉴리스트");
	m_currentPoint			= IMAGEMANAGER->findImage("현재아이템표시");

	// bool값 초기화
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
	m_pointerCount			= 0;

	// string -> char [ 한글자씩 보여주기 위해 받아준다. ]
	m_nextTalk				= false;
	m_charCount				= 0;
	m_printStr				= { "", };
	m_count					= 0;
	m_forCount				= 0;
	printStrLength = m_wellomeShop[1].length();

	return true;
}

bool shopScene::init(void * _info, bool isOnBattle)
{
	init();
	return true;
}

void shopScene::update(float _deltaTime)
{
	// npc대화 시작
	m_deltaTime = _deltaTime;

	if (KEYMANAGER->isOnceKeyDown(GAME_MENU))
	{
		shopMainMenu = FIRSTMENU;
		m_startTime = true;
	}
	
	talkCount();

	if (KEYMANAGER->isOnceKeyDown(P1_Z)) {
		resetPrintText();
	}

}

void shopScene::release()
{
}

void shopScene::render(HDC hdc)
{
	m_friendlyShop->render(hdc, 160 , 110 );
	
	switch (shopMainMenu)
	{
	case FIRSTMENU:
		firstRender(hdc);
		break;

	case BUYITEM:
		buyRender(hdc);
		break;

	case SELLITEM:
		sellRender(hdc);
		break;

	case NOTHING:
		quitRender(hdc);
		break;

	default:
		break;
	}
}

void shopScene::firstRender(HDC hdc)
{
	// 첫번째 메인 npc 박스 
	m_npcTalkBox->render(hdc,  20 , WINSIZEY - 250);

	if (!m_isFirstTalk)
	{
		printTextConsequentlyFirst(hdc, m_wellomeShop[0], 50, WINSIZEY - 200);
		printTextConsequentlySecond(hdc, m_wellomeShop[1], 150, WINSIZEY - 140);
	}
}

void shopScene::buyRender(HDC hdc)
{
}

void shopScene::sellRender(HDC hdc)
{
}

void shopScene::quitRender(HDC hdc)
{
}

void shopScene::currentPointerCount()
{
}

void shopScene::talkCount()
{
	if (m_charCount < 50)
		m_charCount++;
	else if (m_charCount >= 50)
	{
		m_charCount = 0;
		m_nextTalk = true;
	}
}

void shopScene::afterRender(HDC hdc)
{
}

void shopScene::debugRender(HDC hdc)
{
}

void shopScene::NpcTalkVowel()
{
	//inOderText(printText, talk[0], 0, printComplete, addCharDelay, pastTime, textIndex, printStrLength);
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
	UTIL::PrintText(hdc, printText[0].c_str(), "소야바른9", _destX, _destY, 65, RGB(0, 0, 0), true);
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
	UTIL::PrintText(hdc, printText[1].c_str(), "소야바른9", _destX, _destY, 65, RGB(0, 0, 0), true);
}