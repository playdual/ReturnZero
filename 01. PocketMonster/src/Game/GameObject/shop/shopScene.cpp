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

	// 화살 포인터(카운트)
	m_pointerCount			= 0;

	// string -> char [ 한글자씩 보여주기 위해 받아준다. ]
	m_stringInput[100]		= { 0, };
	m_charCount				= 0;

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
	if(KEYMANAGER->isOnceKeyDown(GAME_MENU))
	shopMainMenu = FIRSTMENU;

	// npc 대사 카운트
	if (m_charCount < 10)
		m_charCount++;
	else if (m_charCount >= 10)
		m_charCount = 0;

	


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
	// npc 대사
	for (int i = 0; i < 2; i++)
	{
		const char* pch[30] = { " " };
		//  %%%%%%%%%%%%%%% 여기 작업해야함~!%%%%%%%%%%%%%%%%  //
		pch[30] = m_wellomeShop[i].c_str();
		for (int j = 0; j < m_wellomeShop[i].length() - 1; j++)
		{
			if (m_charCount == 10)
			{
				UTIL::PrintText(hdc, pch[j], "소야바른9", 90 , WINSIZEY - 216 + ( 60 * i), 65, RGB(0, 0, 0), true);
			}
		}

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

void shopScene::afterRender(HDC hdc)
{
}

void shopScene::debugRender(HDC hdc)
{
}






