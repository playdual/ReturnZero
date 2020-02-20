#include "stdafx.h"
#include "PocketmonBagScene.h"
#include "Common/SystemManagers.h"
#include "Game/GameManager/ItemManager.h"

PocketmoninfoScene::PocketmoninfoScene(std::vector<std::shared_ptr<PocketMon>>& _Pocketmons)
	: Pocketmons(_Pocketmons)
{
}

PocketmoninfoScene::~PocketmoninfoScene()
{
}

bool PocketmoninfoScene::init()
{
	//temp
	//isFromBattle = true;

	m_Base = IMAGEMANAGER->findImage("Base");

	m_mainRect = UTIL::IRectMake(5, 78, 318, 220);
	m_mainIconRect = UTIL::IRectMake(56, 175, 90, 90);
	m_mainOn = IMAGEMANAGER->findImage("mainOn");
	m_mainOff = IMAGEMANAGER->findImage("mainOff");

	m_subRect0 = UTIL::IRectMake(365, 37, 500, 100);
	m_subIconRect0 = UTIL::IRectMake(409, 55, 90, 90);
	m_sub0On = IMAGEMANAGER->findImage("sun0On");
	m_sub0Off = IMAGEMANAGER->findImage("sun0Off");

	m_subRect1 = UTIL::IRectMake(365, 153, 500, 100);
	m_subIconRect1 = UTIL::IRectMake(409, 171, 90, 90);
	m_sub1On = IMAGEMANAGER->findImage("sun1On");
	m_sub1Off = IMAGEMANAGER->findImage("sun1Off");

	m_subRect2 = UTIL::IRectMake(365, 269, 500, 100);
	m_subIconRect2 = UTIL::IRectMake(409, 277, 90, 90);
	m_sub2On = IMAGEMANAGER->findImage("sun2On");
	m_sub2Off = IMAGEMANAGER->findImage("sun2Off");

	m_subRect3 = UTIL::IRectMake(365, 385, 500, 100);
	m_subIconRect3 = UTIL::IRectMake(409, 393, 90, 90);
	m_sub3On = IMAGEMANAGER->findImage("sun3On");
	m_sub3Off = IMAGEMANAGER->findImage("sun3Off");

	m_subRect4 = UTIL::IRectMake(365, 501, 500, 100);
	m_subIconRect4 = UTIL::IRectMake(409, 505, 90, 90);
	m_sub4On = IMAGEMANAGER->findImage("sun4On");
	m_sub4Off = IMAGEMANAGER->findImage("sun4Off");

	m_cancle = UTIL::IRectMake(770, 625, 100, 50);
	m_cancleOn = IMAGEMANAGER->findImage("cancleOn");
	m_cancleOff = IMAGEMANAGER->findImage("cancleOff");

	m_sexMan = IMAGEMANAGER->findImage("ManSex");
	m_sexWoman = IMAGEMANAGER->findImage("WomanSex");

	m_mainHpBarGreen = IMAGEMANAGER->findImage("BagHpBarGreen");
	m_sub0HpBarGreen = IMAGEMANAGER->findImage("BagHpBarGreen");
	m_sub1HpBarGreen = IMAGEMANAGER->findImage("BagHpBarGreen");
	m_sub2HpBarGreen = IMAGEMANAGER->findImage("BagHpBarGreen");
	m_sub3HpBarGreen = IMAGEMANAGER->findImage("BagHpBarGreen");
	m_sub4HpBarGreen = IMAGEMANAGER->findImage("BagHpBarGreen");
	m_mainHpBarYellow = IMAGEMANAGER->findImage("BagHpBarYellow");
	m_sub0HpBarYellow = IMAGEMANAGER->findImage("BagHpBarYellow");
	m_sub1HpBarYellow = IMAGEMANAGER->findImage("BagHpBarYellow");
	m_sub2HpBarYellow = IMAGEMANAGER->findImage("BagHpBarYellow");
	m_sub3HpBarYellow = IMAGEMANAGER->findImage("BagHpBarYellow");
	m_sub4HpBarYellow = IMAGEMANAGER->findImage("BagHpBarYellow");
	m_mainHpBarRed = IMAGEMANAGER->findImage("BagHpBarRed");
	m_sub0HpBarRed = IMAGEMANAGER->findImage("BagHpBarRed");
	m_sub1HpBarRed = IMAGEMANAGER->findImage("BagHpBarRed");
	m_sub2HpBarRed = IMAGEMANAGER->findImage("BagHpBarRed");
	m_sub3HpBarRed = IMAGEMANAGER->findImage("BagHpBarRed");
	m_sub4HpBarRed = IMAGEMANAGER->findImage("BagHpBarRed");
	m_mainSwapOn = IMAGEMANAGER->findImage("mainSwapOn");
	m_mainSwapOff = IMAGEMANAGER->findImage("mainSwapOff");
	m_sub0SwapOn = IMAGEMANAGER->findImage("subSwapOn");
	m_sub0SwapOff = IMAGEMANAGER->findImage("subSwapOff");
	m_sub1SwapOn = IMAGEMANAGER->findImage("subSwapOn");
	m_sub1SwapOff = IMAGEMANAGER->findImage("subSwapOff");
	m_sub2SwapOn = IMAGEMANAGER->findImage("subSwapOn");
	m_sub2SwapOff = IMAGEMANAGER->findImage("subSwapOff");
	m_sub3SwapOn = IMAGEMANAGER->findImage("subSwapOn");
	m_sub3SwapOff = IMAGEMANAGER->findImage("subSwapOff");
	m_sub4SwapOn = IMAGEMANAGER->findImage("subSwapOn");
	m_sub4SwapOff = IMAGEMANAGER->findImage("subSwapOff");
	m_PokemonDie = IMAGEMANAGER->findImage("PokemonDie");

	m_Menu = IMAGEMANAGER->findImage("PokemonMenuimg");
	m_fromBattleMenu = IMAGEMANAGER->findImage("FromBattleMenuimg");
	m_MenuCursor = IMAGEMANAGER->findImage("PokemonMenuindeximg");
	m_fromBattleCursor = IMAGEMANAGER->findImage("PokemonMenuindeximg");

	m_indexCursor = 0;

	m_InBagMenuIndex = 0;

	m_indexCursorMenu1 = 0;
	m_indexCursorMenu1Max = 0;;

	m_isOnbattle = false;
	return true;
}

bool PocketmoninfoScene::init(void* _info, bool isOnbattle)
{
	init();
	m_isOnbattle = isOnbattle;

	if (_info != nullptr)
	{
		int infoType = *(int*)_info;
		switch (infoType)
		{
		case INFO_ITEM:
			rendedItemInfo = (ItemInfo*)_info;
			break;
		case INFO_FROMBATTLE:
			isFromBattle = true;
			delete (ChangeSceneFromBattle*)_info;
			break;
		default:
			break;
		}
	}
	return true;
}

void PocketmoninfoScene::update(float _deltaTime)
{
	if (KEYMANAGER->isStayKeyDown(P1_A))
	{
		Pocketmons[0]->m_currentHp -= 1;
	}

	if (isItemUse && m_isOnbattle) {
		if (isItemUse && KEYMANAGER->isOnceKeyDown(P1_Z)) {
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			isItemUse = false;
			m_isOnbattle = false;

			auto temp = new UsedItemInfo;
			if (isEffectionItem)
				temp->isUsed = true;
			else
				temp->isUsed = false;

			//일단은 사용한걸로
		/*	temp->isUsed = true;*/
			temp->itemKey = rendedItemInfo->name;
			m_sceneResult = (void*)temp;
			SCENEMANAGER->scenePop(true);
		}
	}

	pastTime += _deltaTime;
	if (pastTime > frameDelay) {
		if (m_pocketMonFrameIdx == 0) {
			m_pocketMonFrameIdx = 1;
		}
		else {
			m_pocketMonFrameIdx = 0;
		}
		pastTime = 0;
	}

	//temp
	if (KEYMANAGER->isOnceKeyDown(P1_USEITEM)) {
		Pocketmons.pop_back();
	}//




	//인덱스 커서 0아래면 최대로 또는 그 반대
	if (m_indexCursor < 0)
	{
		m_indexCursor = m_indexCursorMax;
	}
	else if (m_indexCursor > m_indexCursorMax)
	{
		m_indexCursor = 0;
	}

	if (m_indexCursorMenu1 < 0)
	{
		m_indexCursorMenu1 = m_indexCursorMenu1Max;
	}
	else if (m_indexCursorMenu1 > m_indexCursorMenu1Max)
	{
		m_indexCursorMenu1 = 0;
	}


	//메뉴 인덱스 0
	if (m_InBagMenuIndex == 0 && !isItemUse && !isMaxRecovery)
	{

		if (KEYMANAGER->isOnceKeyDown(P1_UP))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			m_indexCursor--;
		}
		else if (KEYMANAGER->isOnceKeyDown(P1_DOWN))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			m_indexCursor++;
		}

		//마지막 인덱스는 취소키
		m_indexCursorMax = Pocketmons.size();

		//취소일때 확인누르면 기본화면으로 돌아가기
		if (m_indexCursor == Pocketmons.size() && KEYMANAGER->isOnceKeyDown(P1_Z) && !m_isOnbattle)
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			SCENEMANAGER->scenePop();
		}
		else if (m_indexCursor == Pocketmons.size() && KEYMANAGER->isStayKeyDown(P1_Z) && m_isOnbattle)
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			auto* temp = new UsedItemInfo;
			temp->isUsed = false;
			temp->infoType = INFO_USEDITEM;
			m_sceneResult = (void*)temp;
			SCENEMANAGER->scenePop(true);
		
		}

		//X누르면 기본화면으로 돌아가기
		if (KEYMANAGER->isOnceKeyDown(P1_X) && !m_isOnbattle)
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			SCENEMANAGER->scenePop();
		}
		else if (KEYMANAGER->isStayKeyDown(P1_X) && m_isOnbattle)
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			auto* temp = new UsedItemInfo;
			temp->infoType = INFO_USEDITEM;
			temp->isUsed = false;
			m_sceneResult = temp;
			SCENEMANAGER->scenePop(true);
		}

		//Z를 누르면 포켓몬 관한 메뉴가 나오기
		if (m_indexCursor != m_indexCursorMax && !m_isOnbattle && !isFromBattle)
		{
			if (KEYMANAGER->isOnceKeyDown(P1_Z))
			{
				SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);
				m_InBagMenuIndex = 1;
			}
			
		}
		//배틀에서 바로 인벤으로 넘어왔을때 포켓몬 선택시 관련메뉴 나오게하기
		if (isFromBattle && m_indexCursor != m_indexCursorMax && m_isOnbattle)
		{
			if (KEYMANAGER->isOnceKeyDown(P1_Z))
			{
				SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);
				m_InBagMenuIndex = 5;
			}		
		}


		//배틀씬에서 인벤씬에서 넘어왔을 때 포켓몬한테 아이템 사용
		if (m_indexCursor != m_indexCursorMax && m_isOnbattle && !isFromBattle && KEYMANAGER->isOnceKeyDown(P1_Z))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			isItemUse = true;
			realRecovery = Pocketmons[m_indexCursor]->m_maxHp - Pocketmons[m_indexCursor]->m_currentHp;
	
			if (realRecovery > rendedItemInfo->healPoint)
				realRecovery = rendedItemInfo->healPoint;
			m_memoryHp = Pocketmons[m_indexCursor]->m_currentHp + realRecovery;
			if (realRecovery == 0) 
			{
				isEffectionItem = false;
			}
			else 
			{
				SOUNDMANAGER->playSound("Heal", Channel::eChannelEffect);
				isEffectionItem = true;			
			}
			
			isMaxRecovery = true;

			//Pocketmons[m_indexCursor]->m_currentHp += rendedItemInfo->healPoint;
		}
	}
	if (isMaxRecovery)
	{
		//stop을 배틀끝날때 해줘야함
		if(Pocketmons[m_indexCursor]->m_currentHp<m_memoryHp)
		Pocketmons[m_indexCursor]->m_currentHp += 1;
		if (Pocketmons[m_indexCursor]->m_currentHp >= m_memoryHp)
			isMaxRecovery = false;
	}


	//메뉴 인덱스 1
	if (m_InBagMenuIndex == 1 && isSwap == false)
	{
		m_MenuRect = UTIL::IRectMake(775, 400, 100, 100);
		m_MenuCursorRect = UTIL::IRectMake(795, 450 + m_indexCursorMenu1 * 70, 50, 50);

		if (KEYMANAGER->isOnceKeyDown(P1_UP) && isSwap == false)
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			m_indexCursorMenu1--;

		}
		else if (KEYMANAGER->isOnceKeyDown(P1_DOWN) && isSwap == false)
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			m_indexCursorMenu1++;
		}

		m_swapIndexFirst = m_indexCursor;

		m_indexCursorMenu1Max = 3;

		if (m_indexCursorMenu1 == 0 && KEYMANAGER->isOnceKeyDown(P1_Z))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			//상태보기
		}
		if (m_indexCursorMenu1 == 1 && KEYMANAGER->isOnceKeyDown(P1_Z))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			//순서변경
			isSwap = true;
		}
		if (m_indexCursorMenu1 == 2 && KEYMANAGER->isOnceKeyDown(P1_Z))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			//지닌물건
		}

		//그만둔다
		if (KEYMANAGER->isOnceKeyDown(P1_X))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			isSwap = false;
			m_InBagMenuIndex = 0;
		}
		if (m_indexCursorMenu1 == 3 && KEYMANAGER->isOnceKeyDown(P1_Z))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			isSwap = false;
			m_InBagMenuIndex = 0;
		}


	}
	//메뉴인덱스5 (배틀에서 바로온 메뉴목록)
	if (m_InBagMenuIndex == 5 && !isSwap)
	{
		m_fromBattleMenuRect = UTIL::IRectMake(775, 520, 100, 100);
		m_fromBattleCursorRect = UTIL::IRectMake(795, 550 + m_indexCursorMenu1 * 70, 50, 50);

		if (KEYMANAGER->isOnceKeyDown(P1_UP))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			m_indexCursorMenu1--;

		}
		else if (KEYMANAGER->isOnceKeyDown(P1_DOWN))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			m_indexCursorMenu1++;
		}

		m_swapIndexFirst = m_indexCursor;

		m_indexCursorMenu1Max = 1;

		if (m_indexCursorMenu1 == 0 && KEYMANAGER->isOnceKeyDown(P1_Z))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);
			isSwap = true;
			//순서변경
		}
	
		//그만둔다
		if (KEYMANAGER->isOnceKeyDown(P1_X))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			isSwap = false;
			SCENEMANAGER->scenePop();
		}
		if (m_indexCursorMenu1 == 1 && KEYMANAGER->isOnceKeyDown(P1_Z))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			isSwap = false;
			SCENEMANAGER->scenePop();
		}

	}

	if (isSwap == true)
	{
		m_swapIndexMax = Pocketmons.size();

		if (KEYMANAGER->isOnceKeyDown(P1_X))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			isSwap = false;
			m_InBagMenuIndex = 0;
		}

		if (KEYMANAGER->isOnceKeyDown(P1_UP))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			m_swapIndexSecond--;

		}
		else if (KEYMANAGER->isOnceKeyDown(P1_DOWN))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			m_swapIndexSecond++;
		}

		if (m_swapIndexSecond < 0)
		{
			m_swapIndexSecond = m_swapIndexMax;
		}
		else if (m_swapIndexSecond > m_swapIndexMax)
		{
			m_swapIndexSecond = 0;
		}

		if (m_swapIndexSecond == m_swapIndexMax)
		{
			if (KEYMANAGER->isOnceKeyDown(P1_Z))
			{
				isSwap = false;
				m_InBagMenuIndex = 0;
			}
		}

		if (KEYMANAGER->isOnceKeyDown(P1_Z))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);
			if (m_swapIndexFirst == m_swapIndexSecond)
			{
				m_InBagMenuIndex = 0;
				isSwap = false;
			}

			else if (m_swapIndexFirst != m_swapIndexSecond)
			{
				std::swap(Pocketmons[m_swapIndexFirst], Pocketmons[m_swapIndexSecond]);
				m_InBagMenuIndex = 0;
				isSwap = false;

				if (isFromBattle)
				{
					ChangePocketInfo* info = new ChangePocketInfo;
					info->isChanged = true;
					m_sceneResult = (void*)info;
					SCENEMANAGER->scenePop(true);
					isFromBattle = false;
				}
			}
		}


		if (m_swapIndexSecond == m_swapIndexMax && KEYMANAGER->isOnceKeyDown(P1_Z))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			m_InBagMenuIndex = 0;
		}


	}

	//if (Pocketmons[0]->m_currentHp <= 0)isDieMain = true;
	//if (Pocketmons[1]->m_currentHp <= 0)isDieSub0 = true;
	//if (Pocketmons[2]->m_currentHp <= 0)isDieSub1 = true;
	//if (Pocketmons[3]->m_currentHp <= 0)isDieSub2 = true;
	//if (Pocketmons[4]->m_currentHp <= 0)isDieSub3 = true;
	//if (Pocketmons[5]->m_currentHp <= 0)isDieSub4 = true;
}

void PocketmoninfoScene::release()
{
}

void PocketmoninfoScene::render(HDC hdc)
{
	m_Base->render(hdc);

	if (m_isOnbattle == false)
	{
		if (m_InBagMenuIndex == 0)
		{
			UTIL::PrintText(hdc, "포켓몬을 선택해 주십시오", "소야바른9", 45, 650, 80, RGB(208, 208, 200), true, RGB(160, 112, 240));
			UTIL::PrintText(hdc, "포켓몬을 선택해 주십시오", "소야바른9", 40, 650, 80, RGB(50, 50, 50), true, RGB(160, 112, 240));
		}
	}
	if (isFromBattle && !isSwap)
	{
		UTIL::PrintText(hdc, "포켓몬을 선택해 주십시오", "소야바른9", 45, 650, 80, RGB(208, 208, 200), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, "포켓몬을 선택해 주십시오", "소야바른9", 40, 650, 80, RGB(50, 50, 50), true, RGB(160, 112, 240));
	
		if (m_InBagMenuIndex == 5 && !isSwap)
		{
			/*if (m_InBagMenuIndex == 1 && isSwap == false && !m_isOnbattle && !isFromBattle)
			{*/
				m_fromBattleMenu->render(hdc, m_fromBattleMenuRect.left, m_fromBattleMenuRect.top);
				m_fromBattleCursor->render(hdc, m_fromBattleCursorRect.left, m_fromBattleCursorRect.top);

				UTIL::PrintText(hdc, "교체한다", "소야바른9", 835, 550, 70, RGB(208, 208, 200), true, RGB(160, 112, 240));
				UTIL::PrintText(hdc, "교체한다", "소야바른9", 830, 550, 70, RGB(0, 0, 0), true, RGB(160, 112, 240));
				UTIL::PrintText(hdc, "그만둔다", "소야바른9", 835, 620, 70, RGB(208, 208, 200), true, RGB(160, 112, 240));
				UTIL::PrintText(hdc, "그만둔다", "소야바른9", 830, 620, 70, RGB(0, 0, 0), true, RGB(160, 112, 240));
		}

	}


	if (m_isOnbattle && !isItemUse && !isFromBattle)
	{
		UTIL::PrintText(hdc, "누구에게 사용할까?", "소야바른9", 45, 650, 80, RGB(208, 208, 200), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, "누구에게 사용할까?", "소야바른9", 40, 650, 80, RGB(50, 50, 50), true, RGB(160, 112, 240));
	}


	//포켓몬 선택
	if (m_InBagMenuIndex == 1 && isSwap == false && !m_isOnbattle)
	{
		UTIL::PrintText(hdc, Pocketmons[m_indexCursor]->m_name.c_str(), "소야바른9", 45, 650, 80, RGB(208, 208, 200), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, Pocketmons[m_indexCursor]->m_name.c_str(), "소야바른9", 40, 650, 80, RGB(50, 50, 50), true, RGB(160, 112, 240));

		UTIL::PrintText(hdc, "을(를) 어떻게 할까?", "소야바른9", 255, 650, 80, RGB(208, 208, 200), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, "을(를) 어떻게 할까?", "소야바른9", 250, 650, 80, RGB(50, 50, 50), true, RGB(160, 112, 240));
	}

	int cnt = 0;
	for (auto e : Pocketmons)
	{
		//UTIL::PrintText(hdc, e->m_name.c_str(), "소야바른9", 100, 100 + cnt * 70, 30);
		if ((m_InBagMenuIndex == 0 || m_InBagMenuIndex == 1 || m_InBagMenuIndex == 5) && !isSwap && m_indexCursor == 0)
		{
			m_mainOn->render(hdc, m_mainRect.left - 5, m_mainRect.top + 2);
		}
		else if ((m_InBagMenuIndex == 0 || m_InBagMenuIndex == 1 || m_InBagMenuIndex == 5) && !isSwap && m_indexCursor != 0)
		{
			m_mainOff->render(hdc, m_mainRect.left, m_mainRect.top + 3);
		}

		if (Pocketmons.size() >= 2)
		{
			if ((m_InBagMenuIndex == 0 || m_InBagMenuIndex == 1 || m_InBagMenuIndex == 5) && !isSwap && m_indexCursor == 1)
			{
				m_sub0On->render(hdc, m_subRect0.left, m_subRect0.top);
			}
			else if ((m_InBagMenuIndex == 0 || m_InBagMenuIndex == 1 || m_InBagMenuIndex == 5) && !isSwap && m_indexCursor != 1)
			{
				m_sub0Off->render(hdc, m_subRect0.left, m_subRect0.top);
			}
			else if ((m_InBagMenuIndex == 1 || m_InBagMenuIndex == 5) && isSwap && m_swapIndexSecond != 1 )
			{
				m_sub0Off->render(hdc, m_subRect0.left, m_subRect0.top);
			}

		}

		if (Pocketmons.size() >= 3)
		{

			if ((m_InBagMenuIndex == 0 || m_InBagMenuIndex == 1 || m_InBagMenuIndex == 5) && !isSwap && m_indexCursor == 2)
			{
				m_sub1On->render(hdc, m_subRect1.left, m_subRect1.top);
			}
			else if ((m_InBagMenuIndex == 0 || m_InBagMenuIndex == 1 || m_InBagMenuIndex == 5) && !isSwap && m_indexCursor != 2)
			{
				m_sub1Off->render(hdc, m_subRect1.left, m_subRect1.top);
			}
			else if ((m_InBagMenuIndex == 1 || m_InBagMenuIndex == 5) && isSwap && m_swapIndexSecond != 2)
			{
				m_sub1Off->render(hdc, m_subRect1.left, m_subRect1.top);
			}
		}

		if (Pocketmons.size() >= 4)
		{

			if ((m_InBagMenuIndex == 0 || m_InBagMenuIndex == 1 || m_InBagMenuIndex == 5) && !isSwap && m_indexCursor == 3)
			{
				m_sub2On->render(hdc, m_subRect2.left, m_subRect2.top);
			}
			else if ((m_InBagMenuIndex == 0 || m_InBagMenuIndex == 1 || m_InBagMenuIndex == 5) && !isSwap && m_indexCursor != 3)
			{
				m_sub2Off->render(hdc, m_subRect2.left, m_subRect2.top);
			}
			else if ((m_InBagMenuIndex == 1 || m_InBagMenuIndex == 5) && isSwap && m_swapIndexSecond != 3)
			{
				m_sub2Off->render(hdc, m_subRect2.left, m_subRect2.top);
			}
		}

		if (Pocketmons.size() >= 5)
		{

			if ((m_InBagMenuIndex == 0 || m_InBagMenuIndex == 1 || m_InBagMenuIndex == 5) && !isSwap && m_indexCursor == 4)
			{
				m_sub3On->render(hdc, m_subRect3.left, m_subRect3.top);
			}
			else if ((m_InBagMenuIndex == 0 || m_InBagMenuIndex == 1 || m_InBagMenuIndex == 5) && !isSwap && m_indexCursor != 4)
			{
				m_sub3Off->render(hdc, m_subRect3.left, m_subRect3.top);
			}
			else if ((m_InBagMenuIndex == 1 || m_InBagMenuIndex == 5) && isSwap && m_swapIndexSecond != 4)
			{
				m_sub3Off->render(hdc, m_subRect3.left, m_subRect3.top);
			}
		}

		if (Pocketmons.size() >= 6)
		{

			if ((m_InBagMenuIndex == 0 || m_InBagMenuIndex == 1 || m_InBagMenuIndex == 5) && !isSwap && m_indexCursor == 5)
			{
				m_sub4On->render(hdc, m_subRect4.left, m_subRect4.top);
			}
			else if ((m_InBagMenuIndex == 0 || m_InBagMenuIndex == 1 || m_InBagMenuIndex == 5) && !isSwap && m_indexCursor != 5)
			{
				m_sub4Off->render(hdc, m_subRect4.left, m_subRect4.top);
			}
			else if ((m_InBagMenuIndex == 1 || m_InBagMenuIndex == 5) && isSwap && m_swapIndexSecond != 5)
			{
				m_sub4Off->render(hdc, m_subRect4.left, m_subRect4.top);
			}
		}

		if (isSwap)
		{
			if (m_InBagMenuIndex == 1)
			{
				UTIL::PrintText(hdc, "어디로 이동할까?", "소야바른9", 45, 650, 80, RGB(208, 208, 200), true, RGB(160, 112, 240));
				UTIL::PrintText(hdc, "어디로 이동할까?", "소야바른9", 40, 650, 80, RGB(0, 0, 0), true, RGB(160, 112, 240));
			}
			else if (m_InBagMenuIndex == 5)
			{
				UTIL::PrintText(hdc, "어떤 포켓몬과 교체할까?", "소야바른9", 45, 650, 80, RGB(208, 208, 200), true, RGB(160, 112, 240));
				UTIL::PrintText(hdc, "어떤 포켓몬과 교체할까?", "소야바른9", 40, 650, 80, RGB(0, 0, 0), true, RGB(160, 112, 240));
			}

			if (m_swapIndexFirst == 0 && m_swapIndexFirst == m_swapIndexSecond)
			{
				m_mainSwapOn->render(hdc, m_mainRect.left - 5, m_mainRect.top + 2);
				if (m_swapIndexSecond == m_swapIndexMax)m_cancleOn->render(hdc, m_cancle.left, m_cancle.top);
				else if (m_swapIndexSecond != m_swapIndexMax)m_cancleOff->render(hdc, m_cancle.left, m_cancle.top);

			}
			else if (m_swapIndexFirst == 0 && m_swapIndexFirst != m_swapIndexSecond)
			{
				m_mainSwapOff->render(hdc, m_mainRect.left, m_mainRect.top + 3);

				if (m_swapIndexSecond == m_swapIndexMax)m_cancleOn->render(hdc, m_cancle.left, m_cancle.top);
				else if (m_swapIndexSecond != m_swapIndexMax)m_cancleOff->render(hdc, m_cancle.left, m_cancle.top);

				if (m_swapIndexMax == 1);//1마리
				if (m_swapIndexMax >= 2)//2마리
				{
					if (m_swapIndexSecond == 1)m_sub0SwapOn->render(hdc, m_subRect0.left, m_subRect0.top);
				}
				if (m_swapIndexMax >= 3)//3마리
				{
					if (m_swapIndexSecond == 2)m_sub1SwapOn->render(hdc, m_subRect1.left, m_subRect1.top);
				}
				if (m_swapIndexMax >= 4)//4마리
				{
					if (m_swapIndexSecond == 3)m_sub2SwapOn->render(hdc, m_subRect2.left, m_subRect2.top);
				}
				if (m_swapIndexMax >= 5)//5마리
				{
					if (m_swapIndexSecond == 4)m_sub3SwapOn->render(hdc, m_subRect3.left, m_subRect3.top);
				}
				if (m_swapIndexMax >= 6)//6마리
				{
					if (m_swapIndexSecond == 5)m_sub4SwapOn->render(hdc, m_subRect4.left, m_subRect4.top);
				}
			}
		}
	}

	//
	Pocketmons[0]->m_pocketmonIconImg->frameRender(hdc, m_mainIconRect.left, m_mainIconRect.top, m_pocketMonFrameIdx, 0);
	UTIL::PrintText(hdc, Pocketmons[0]->m_name.c_str(), "소야바른9", 175, 170, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
	UTIL::PrintText(hdc, Pocketmons[0]->m_name.c_str(), "소야바른9", 170, 170, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));

	std::string m_mainlevel = std::to_string(Pocketmons[0]->m_level);
	UTIL::PrintText(hdc, m_mainlevel.c_str(), "소야바른9", 210, 215, 70, RGB(112, 112, 112), true, RGB(160, 112, 240));
	UTIL::PrintText(hdc, m_mainlevel.c_str(), "소야바른9", 205, 215, 70, RGB(255, 255, 255), true, RGB(160, 112, 240));

	std::string m_mainCurrentHp = std::to_string(Pocketmons[0]->m_currentHp);
	UTIL::PrintText(hdc, m_mainCurrentHp.c_str(), "소야바른9", 165, 300, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
	UTIL::PrintText(hdc, m_mainCurrentHp.c_str(), "소야바른9", 160, 300, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));
	std::string m_mainMaxHp = std::to_string(Pocketmons[0]->m_maxHp);
	UTIL::PrintText(hdc, m_mainMaxHp.c_str(), "소야바른9", 280, 300, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
	UTIL::PrintText(hdc, m_mainMaxHp.c_str(), "소야바른9", 275, 300, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));

	if ((float)Pocketmons[0]->m_currentHp / (float)Pocketmons[0]->m_maxHp > 0.5)
		m_mainHpBarGreen->render(hdc, 130, 283, 0, 0, 208 * (float)Pocketmons[0]->m_currentHp / (float)Pocketmons[0]->m_maxHp, 15);
	else if ((float)Pocketmons[0]->m_currentHp / (float)Pocketmons[0]->m_maxHp <= 0.5 && (float)Pocketmons[0]->m_currentHp / (float)Pocketmons[0]->m_maxHp > 0.1)
		m_mainHpBarYellow->render(hdc, 130, 283, 0, 0, 208 * (float)Pocketmons[0]->m_currentHp / (float)Pocketmons[0]->m_maxHp, 15);
	else if ((float)Pocketmons[0]->m_currentHp / (float)Pocketmons[0]->m_maxHp <= 0.1)
		m_mainHpBarRed->render(hdc, 130, 283, 0, 0, 208 * (float)Pocketmons[0]->m_currentHp / (float)Pocketmons[0]->m_maxHp, 15);

	if (Pocketmons[0]->m_currentHp <= 0)Pocketmons[0]->m_currentHp = 0;
	if (Pocketmons[0]->m_currentHp >= Pocketmons[0]->m_maxHp)Pocketmons[0]->m_currentHp = Pocketmons[0]->m_maxHp;


	if (Pocketmons[0]->gender)m_sexWoman->render(hdc, 300, 220);
	else m_sexMan->render(hdc, 300, 225);
	//


	if (Pocketmons.size() >= 2)
	{
		Pocketmons[1]->m_pocketmonIconImg->frameRender(hdc, m_subIconRect0.left, m_subIconRect0.top, m_pocketMonFrameIdx, 0);
		UTIL::PrintText(hdc, Pocketmons[1]->m_name.c_str(), "소야바른9", 550, 50, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, Pocketmons[1]->m_name.c_str(), "소야바른9", 545, 50, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));

		std::string m_sub0level = std::to_string(Pocketmons[1]->m_level);
		UTIL::PrintText(hdc, m_sub0level.c_str(), "소야바른9", 585, 95, 70, RGB(112, 112, 112), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, m_sub0level.c_str(), "소야바른9", 580, 95, 70, RGB(255, 255, 255), true, RGB(160, 112, 240));

		std::string m_sub0CurrentHp = std::to_string(Pocketmons[1]->m_currentHp);
		UTIL::PrintText(hdc, m_sub0CurrentHp.c_str(), "소야바른9", 825, 95, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, m_sub0CurrentHp.c_str(), "소야바른9", 820, 95, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));
		std::string m_sub0MaxHp = std::to_string(Pocketmons[1]->m_maxHp);
		UTIL::PrintText(hdc, m_sub0MaxHp.c_str(), "소야바른9", 935, 95, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, m_sub0MaxHp.c_str(), "소야바른9", 930, 95, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));

		if ((float)Pocketmons[1]->m_currentHp / (float)Pocketmons[1]->m_maxHp > 0.5)
			m_sub0HpBarGreen->render(hdc, 782, 81, 0, 0, 208 * (float)Pocketmons[1]->m_currentHp / (float)Pocketmons[1]->m_maxHp, 15);
		else if ((float)Pocketmons[1]->m_currentHp / (float)Pocketmons[1]->m_maxHp <= 0.5 && (float)Pocketmons[1]->m_currentHp / (float)Pocketmons[1]->m_maxHp > 0.1)
			m_sub0HpBarYellow->render(hdc, 782, 81, 0, 0, 208 * (float)Pocketmons[1]->m_currentHp / (float)Pocketmons[1]->m_maxHp, 15);
		else if ((float)Pocketmons[1]->m_currentHp / (float)Pocketmons[1]->m_maxHp <= 0.1)
			m_sub0HpBarRed->render(hdc, 782, 81, 0, 0, 208 * (float)Pocketmons[1]->m_currentHp / (float)Pocketmons[1]->m_maxHp, 15);

		if (Pocketmons[1]->m_currentHp <= 0)Pocketmons[1]->m_currentHp = 0;
		if (Pocketmons[1]->m_currentHp >= Pocketmons[1]->m_maxHp)Pocketmons[1]->m_currentHp = Pocketmons[1]->m_maxHp;

		if (Pocketmons[1]->gender)m_sexWoman->render(hdc, 675, 105);
		else m_sexMan->render(hdc, 675, 105);
	}
	if (Pocketmons.size() >= 3)
	{
		Pocketmons[2]->m_pocketmonIconImg->frameRender(hdc, m_subIconRect1.left, m_subIconRect1.top, m_pocketMonFrameIdx, 0);
		UTIL::PrintText(hdc, Pocketmons[2]->m_name.c_str(), "소야바른9", 550, 166, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, Pocketmons[2]->m_name.c_str(), "소야바른9", 545, 166, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));

		std::string m_sub1level = std::to_string(Pocketmons[2]->m_level);
		UTIL::PrintText(hdc, m_sub1level.c_str(), "소야바른9", 585, 211, 70, RGB(112, 112, 112), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, m_sub1level.c_str(), "소야바른9", 580, 211, 70, RGB(255, 255, 255), true, RGB(160, 112, 240));

		std::string m_sub1CurrentHp = std::to_string(Pocketmons[2]->m_currentHp);
		UTIL::PrintText(hdc, m_sub1CurrentHp.c_str(), "소야바른9", 825, 211, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, m_sub1CurrentHp.c_str(), "소야바른9", 820, 211, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));
		std::string m_sub1MaxHp = std::to_string(Pocketmons[2]->m_maxHp);
		UTIL::PrintText(hdc, m_sub1MaxHp.c_str(), "소야바른9", 935, 211, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, m_sub1MaxHp.c_str(), "소야바른9", 930, 211, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));

		if ((float)Pocketmons[2]->m_currentHp / (float)Pocketmons[2]->m_maxHp > 0.5)
			m_sub1HpBarGreen->render(hdc, 782, 197, 0, 0, 208 * (float)Pocketmons[2]->m_currentHp / (float)Pocketmons[2]->m_maxHp, 15);
		else if ((float)Pocketmons[2]->m_currentHp / (float)Pocketmons[2]->m_maxHp <= 0.5 && (float)Pocketmons[2]->m_currentHp / (float)Pocketmons[2]->m_maxHp > 0.1)
			m_sub1HpBarYellow->render(hdc, 782, 197, 0, 0, 208 * (float)Pocketmons[2]->m_currentHp / (float)Pocketmons[2]->m_maxHp, 15);
		else if ((float)Pocketmons[2]->m_currentHp / (float)Pocketmons[2]->m_maxHp <= 0.1)
			m_sub1HpBarRed->render(hdc, 782, 197, 0, 0, 208 * (float)Pocketmons[2]->m_currentHp / (float)Pocketmons[2]->m_maxHp, 15);

		if (Pocketmons[2]->m_currentHp <= 0)Pocketmons[2]->m_currentHp = 0;
		if (Pocketmons[2]->m_currentHp >= Pocketmons[2]->m_maxHp)Pocketmons[2]->m_currentHp = Pocketmons[2]->m_maxHp;

		if (Pocketmons[2]->gender)m_sexWoman->render(hdc, 675, 221);
		else m_sexMan->render(hdc, 675, 221);
	}
	if (Pocketmons.size() >= 4)
	{
		Pocketmons[3]->m_pocketmonIconImg->frameRender(hdc, m_subIconRect2.left, m_subIconRect2.top, m_pocketMonFrameIdx, 0);
		UTIL::PrintText(hdc, Pocketmons[3]->m_name.c_str(), "소야바른9", 550, 282, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, Pocketmons[3]->m_name.c_str(), "소야바른9", 545, 282, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));

		std::string m_sub2level = std::to_string(Pocketmons[3]->m_level);
		UTIL::PrintText(hdc, m_sub2level.c_str(), "소야바른9", 585, 327, 70, RGB(112, 112, 112), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, m_sub2level.c_str(), "소야바른9", 580, 327, 70, RGB(255, 255, 255), true, RGB(160, 112, 240));

		std::string m_sub2CurrentHp = std::to_string(Pocketmons[3]->m_currentHp);
		UTIL::PrintText(hdc, m_sub2CurrentHp.c_str(), "소야바른9", 825, 327, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, m_sub2CurrentHp.c_str(), "소야바른9", 820, 327, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));
		std::string m_sub2MaxHp = std::to_string(Pocketmons[3]->m_maxHp);
		UTIL::PrintText(hdc, m_sub2MaxHp.c_str(), "소야바른9", 935, 327, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, m_sub2MaxHp.c_str(), "소야바른9", 930, 327, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));

		if ((float)Pocketmons[3]->m_currentHp / (float)Pocketmons[3]->m_maxHp > 0.5)
			m_sub2HpBarGreen->render(hdc, 782, 313, 0, 0, 208 * (float)Pocketmons[3]->m_currentHp / (float)Pocketmons[3]->m_maxHp, 15);
		else if ((float)Pocketmons[3]->m_currentHp / (float)Pocketmons[3]->m_maxHp <= 0.5 && (float)Pocketmons[3]->m_currentHp / (float)Pocketmons[3]->m_maxHp > 0.1)
			m_sub2HpBarYellow->render(hdc, 782, 313, 0, 0, 208 * (float)Pocketmons[3]->m_currentHp / (float)Pocketmons[3]->m_maxHp, 15);
		else if ((float)Pocketmons[3]->m_currentHp / (float)Pocketmons[3]->m_maxHp <= 0.1)
			m_sub2HpBarRed->render(hdc, 782, 313, 0, 0, 208 * (float)Pocketmons[3]->m_currentHp / (float)Pocketmons[3]->m_maxHp, 15);

		if (Pocketmons[3]->m_currentHp <= 0)Pocketmons[3]->m_currentHp = 0;
		if (Pocketmons[3]->m_currentHp >= Pocketmons[3]->m_maxHp)Pocketmons[3]->m_currentHp = Pocketmons[3]->m_maxHp;


		if (Pocketmons[3]->gender)m_sexWoman->render(hdc, 675, 337);
		else m_sexMan->render(hdc, 675, 337);
	}
	if (Pocketmons.size() >= 5)
	{
		Pocketmons[4]->m_pocketmonIconImg->frameRender(hdc, m_subIconRect3.left, m_subIconRect3.top, m_pocketMonFrameIdx, 0);
		UTIL::PrintText(hdc, Pocketmons[4]->m_name.c_str(), "소야바른9", 550, 398, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, Pocketmons[4]->m_name.c_str(), "소야바른9", 545, 398, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));

		std::string m_sub3level = std::to_string(Pocketmons[4]->m_level);
		UTIL::PrintText(hdc, m_sub3level.c_str(), "소야바른9", 585, 443, 70, RGB(112, 112, 112), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, m_sub3level.c_str(), "소야바른9", 580, 443, 70, RGB(255, 255, 255), true, RGB(160, 112, 240));

		std::string m_sub3CurrentHp = std::to_string(Pocketmons[4]->m_currentHp);
		UTIL::PrintText(hdc, m_sub3CurrentHp.c_str(), "소야바른9", 825, 443, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, m_sub3CurrentHp.c_str(), "소야바른9", 820, 443, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));
		std::string m_sub3MaxHp = std::to_string(Pocketmons[4]->m_maxHp);
		UTIL::PrintText(hdc, m_sub3MaxHp.c_str(), "소야바른9", 935, 443, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, m_sub3MaxHp.c_str(), "소야바른9", 930, 443, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));

		if ((float)Pocketmons[4]->m_currentHp / (float)Pocketmons[4]->m_maxHp > 0.5)
			m_sub3HpBarGreen->render(hdc, 782, 429, 0, 0, 208 * (float)Pocketmons[4]->m_currentHp / (float)Pocketmons[4]->m_maxHp, 15);
		else if ((float)Pocketmons[4]->m_currentHp / (float)Pocketmons[4]->m_maxHp <= 0.5 && (float)Pocketmons[4]->m_currentHp / (float)Pocketmons[4]->m_maxHp > 0.1)
			m_sub3HpBarYellow->render(hdc, 782, 429, 0, 0, 208 * (float)Pocketmons[4]->m_currentHp / (float)Pocketmons[4]->m_maxHp, 15);
		else if ((float)Pocketmons[4]->m_currentHp / (float)Pocketmons[4]->m_maxHp <= 0.1)
			m_sub3HpBarRed->render(hdc, 782, 429, 0, 0, 208 * (float)Pocketmons[4]->m_currentHp / (float)Pocketmons[4]->m_maxHp, 15);

		if (Pocketmons[4]->m_currentHp <= 0)Pocketmons[4]->m_currentHp = 0;
		if (Pocketmons[4]->m_currentHp >= Pocketmons[4]->m_maxHp)Pocketmons[4]->m_currentHp = Pocketmons[4]->m_maxHp;


		if (Pocketmons[4]->gender)m_sexWoman->render(hdc, 675, 453);
		else m_sexMan->render(hdc, 675, 453);
	}
	if (Pocketmons.size() >= 6)
	{
		Pocketmons[5]->m_pocketmonIconImg->frameRender(hdc, m_subIconRect4.left, m_subIconRect4.top, m_pocketMonFrameIdx, 0);
		UTIL::PrintText(hdc, Pocketmons[5]->m_name.c_str(), "소야바른9", 550, 514, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, Pocketmons[5]->m_name.c_str(), "소야바른9", 545, 514, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));

		std::string m_sub4level = std::to_string(Pocketmons[5]->m_level);
		UTIL::PrintText(hdc, m_sub4level.c_str(), "소야바른9", 585, 559, 70, RGB(112, 112, 112), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, m_sub4level.c_str(), "소야바른9", 580, 559, 70, RGB(255, 255, 255), true, RGB(160, 112, 240));

		std::string m_sub4CurrentHp = std::to_string(Pocketmons[5]->m_currentHp);
		UTIL::PrintText(hdc, m_sub4CurrentHp.c_str(), "소야바른9", 825, 559, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, m_sub4CurrentHp.c_str(), "소야바른9", 820, 559, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));
		std::string m_sub4MaxHp = std::to_string(Pocketmons[5]->m_maxHp);
		UTIL::PrintText(hdc, m_sub4MaxHp.c_str(), "소야바른9", 935, 559, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, m_sub4MaxHp.c_str(), "소야바른9", 930, 559, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));

		if ((float)Pocketmons[5]->m_currentHp / (float)Pocketmons[5]->m_maxHp > 0.5)
			m_sub4HpBarGreen->render(hdc, 782, 545, 0, 0, 208 * (float)Pocketmons[5]->m_currentHp / (float)Pocketmons[5]->m_maxHp, 15);
		else if ((float)Pocketmons[5]->m_currentHp / (float)Pocketmons[5]->m_maxHp <= 0.5 && (float)Pocketmons[5]->m_currentHp / (float)Pocketmons[5]->m_maxHp > 0.1)
			m_sub4HpBarYellow->render(hdc, 782, 545, 0, 0, 208 * (float)Pocketmons[5]->m_currentHp / (float)Pocketmons[5]->m_maxHp, 15);
		else if ((float)Pocketmons[5]->m_currentHp / (float)Pocketmons[5]->m_maxHp <= 0.1)
			m_sub4HpBarRed->render(hdc, 782, 545, 0, 0, 208 * (float)Pocketmons[5]->m_currentHp / (float)Pocketmons[5]->m_maxHp, 15);

		if (Pocketmons[5]->m_currentHp <= 0)Pocketmons[5]->m_currentHp = 0;
		if (Pocketmons[5]->m_currentHp >= Pocketmons[5]->m_maxHp)Pocketmons[5]->m_currentHp = Pocketmons[5]->m_maxHp;

		if (Pocketmons[5]->gender)m_sexWoman->render(hdc, 675, 569);
		else m_sexMan->render(hdc, 675, 569);


	}

	if (m_indexCursor == Pocketmons.size() && m_InBagMenuIndex != 5 && !isSwap)
	{
		m_cancleOn->render(hdc, m_cancle.left, m_cancle.top);
	}
	else if(m_indexCursor != Pocketmons.size() && m_InBagMenuIndex != 5 && !isSwap)
	{
		m_cancleOff->render(hdc, m_cancle.left, m_cancle.top);

	}
	//if (m_indexCursor == Pocketmons.size() && m_InBagMenuIndex == 5 && isSwap)
	//{
	//	m_cancleOn->render(hdc, m_cancle.left, m_cancle.top);
	//}
	//else if (m_indexCursor != Pocketmons.size() && m_InBagMenuIndex == 5 && isSwap)
	//{
	//	m_cancleOff->render(hdc, m_cancle.left, m_cancle.top);
	//}

	if (m_InBagMenuIndex == 1 && isSwap == false && !m_isOnbattle && !isFromBattle)
	{
		m_Menu->render(hdc, m_MenuRect.left, m_MenuRect.top);
		m_MenuCursor->render(hdc, m_MenuCursorRect.left, m_MenuCursorRect.top);

		UTIL::PrintText(hdc, "상태보기", "소야바른9", 835, 440, 70, RGB(208, 208, 200), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, "상태보기", "소야바른9", 830, 440, 70, RGB(0, 0, 0), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, "순서변경", "소야바른9", 835, 510, 70, RGB(208, 208, 200), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, "순서변경", "소야바른9", 830, 510, 70, RGB(0, 0, 0), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, "지닌물건", "소야바른9", 835, 580, 70, RGB(208, 208, 200), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, "지닌물건", "소야바른9", 830, 580, 70, RGB(0, 0, 0), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, "그만둔다", "소야바른9", 835, 650, 70, RGB(208, 208, 200), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, "그만둔다", "소야바른9", 830, 650, 70, RGB(0, 0, 0), true, RGB(160, 112, 240));

	}



	if (m_InBagMenuIndex == 0 || isSwap == true)
	{
		UTIL::PrintText(hdc, "취소", "소야바른9", 900, 655, 75, RGB(112, 112, 112), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, "취소", "소야바른9", 895, 655, 75, RGB(255, 255, 255), true, RGB(160, 112, 240));
	}

	if (m_isOnbattle && isSwap)
	{
		UTIL::PrintText(hdc, "취소", "소야바른9", 900, 655, 75, RGB(112, 112, 112), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, "취소", "소야바른9", 895, 655, 75, RGB(255, 255, 255), true, RGB(160, 112, 240));
	}

	if (isItemUse && !isMaxRecovery)
	{

		if (realRecovery > 0)
		{
			UTIL::PrintText(hdc, Pocketmons[m_indexCursor]->m_name.c_str(), "소야바른9", 25, 650, 80, RGB(208, 208, 208), true, RGB(160, 112, 240));
			UTIL::PrintText(hdc, Pocketmons[m_indexCursor]->m_name.c_str(), "소야바른9", 20, 650, 80, RGB(0, 0, 0), true, RGB(160, 112, 240));

			UTIL::PrintText(hdc, "의 HP가 ", "소야바른9", 185, 650, 80, RGB(208, 208, 208), true, RGB(160, 112, 240));
			UTIL::PrintText(hdc, "의 HP가 ", "소야바른9", 180, 650, 80, RGB(50, 50, 50), true, RGB(160, 112, 240));


			std::string m_HpRecover = std::to_string(rendedItemInfo->healPoint);
			UTIL::PrintText(hdc, m_HpRecover.c_str(), "소야바른9", 385, 650, 80, RGB(208, 208, 208), true, RGB(160, 112, 240));
			UTIL::PrintText(hdc, m_HpRecover.c_str(), "소야바른9", 380, 650, 80, RGB(50, 50, 50), true, RGB(160, 112, 240));

			UTIL::PrintText(hdc, " 회복 되었다!", "소야바른9", 465, 650, 80, RGB(208, 208, 208), true, RGB(160, 112, 240));
			UTIL::PrintText(hdc, " 회복 되었다!", "소야바른9", 460, 650, 80, RGB(50, 50, 50), true, RGB(160, 112, 240));
		}
		else if(realRecovery <= 0)
		{
			UTIL::PrintText(hdc, "효과가 없는 것 같다...", "소야바른9", 25, 650, 80, RGB(208, 208, 208), true, RGB(160, 112, 240));
			UTIL::PrintText(hdc, "효과가 없는 것 같다...", "소야바른9", 20, 650, 80, RGB(0, 0, 0), true, RGB(160, 112, 240));
		}
	}

	if (Pocketmons[0]->m_currentHp <= 0)
	{
		m_PokemonDie->render(hdc, 165, 220);
	}
}



void PocketmoninfoScene::afterRender(HDC hdc)
{
}

void PocketmoninfoScene::debugRender(HDC hdc)
{
	UTIL::DrawColorRect(hdc, m_mainRect, false, false);
	UTIL::DrawColorRect(hdc, m_subRect0, false, false);
	UTIL::DrawColorRect(hdc, m_subRect1, false, false);
	UTIL::DrawColorRect(hdc, m_subRect2, false, false);
	UTIL::DrawColorRect(hdc, m_subRect3, false, false);
	UTIL::DrawColorRect(hdc, m_subRect4, false, false);

	UTIL::DrawColorRect(hdc, m_mainIconRect, false, false);
	UTIL::DrawColorRect(hdc, m_subIconRect0, false, false);
	UTIL::DrawColorRect(hdc, m_subIconRect1, false, false);
	UTIL::DrawColorRect(hdc, m_subIconRect2, false, false);
	UTIL::DrawColorRect(hdc, m_subIconRect3, false, false);
	UTIL::DrawColorRect(hdc, m_subIconRect4, false, false);
	UTIL::DrawColorRect(hdc, m_cancle, false, false);

}
