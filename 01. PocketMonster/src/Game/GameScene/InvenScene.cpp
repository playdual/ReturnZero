#include "stdafx.h"
#include "InvenScene.h"
#include "Game/GameObject/Items/Item.h"


InvenScene::InvenScene(std::shared_ptr<Inventory> _inven)
{
	m_inven = _inven;				// 클래스를 넘겨 받아서 저장하고 있다.
}

InvenScene::~InvenScene()
{
}

bool InvenScene::init(void * _info, bool isOnBattle)
{
	init();
	isFromBattleScene = isOnBattle;
	return true;
}

bool InvenScene::init()
{
	//상점 연습 작업
	isFromBattleScene = false;
	isUpdateLastSceneData = false;
	ShopCount = 0;

	moveCount = 0;
	isUp = true;
	// 인벤창 가방 이미지 add //
	m_BackGround = IMAGEMANAGER->findImage("인벤토리씬");
	m_ItemBag = IMAGEMANAGER->findImage("아이템창");
	m_ImportBag = IMAGEMANAGER->findImage("임폴트창");
	m_PokeBallBag = IMAGEMANAGER->findImage("포케볼창");
	// 인벤 태그 이미지 add // 
	m_ItemTag = IMAGEMANAGER->findImage("아이템창태그");
	m_ImporTag = IMAGEMANAGER->findImage("임폴트창태그");
	m_PokeBallTag = IMAGEMANAGER->findImage("포케볼창태그");
	//인벤 화살표시 이미지//
	m_beforeArrow = IMAGEMANAGER->findImage("이전화면표시");
	m_nextArrow = IMAGEMANAGER->findImage("다음화면표시");
	// 인벤 선택 메뉴
	m_ItemInvenMenu = IMAGEMANAGER->findImage("아이템인벤메뉴");
	m_otherInvenMenu = IMAGEMANAGER->findImage("그외인벤메뉴");
	m_invenMenuBottom = IMAGEMANAGER->findImage("인벤메뉴상세");
	m_currentPointer = IMAGEMANAGER->findImage("현재아이템표시");
	m_battleSceneInvenMenu = IMAGEMANAGER->findImage("배틀씬인벤메뉴");

	m_invenSceneType = ITEM;    // 디폴트 아이템창  = ITEM
	invenSceneCount = 0;		// 아이템창 렌더 시켜줄 카운트

	isChangeScene = false;

	// 우선 isTownInven은 false 처리  = Battle일 경우 창이 틀림0
	isTownInven = false;
	isBattleInven = false;

	// 인벤 선택 메뉴
	pointerCount = 0;

	// 아이템을 버리겠습니까?
	m_isThrowItem = false;
	m_throwItemCount = 0;

	return true;
}

void InvenScene::checkSceneChangeInfo() {
	//lastScene info가 nullptr아니라면
	//변경된 사항이 있다는 것이고, 우리는 이를 처리해 주어야 한다.
	void* temp = SCENEMANAGER->getLastSceneReturnInfo();
	
	//처리를 위한 지역변수
	bool isUsed = false;
	std::string usedItem;

	if (temp != nullptr)
	{
		int lastSceneInfoType = *((int*)temp);

		switch (lastSceneInfoType)
		{
		case INFO_USEDITEM:
			isUsed = ((UsedItemInfo*)temp)->isUsed;
			usedItem = ((UsedItemInfo*)temp)->itemKey;
			break;
		}
		
	}
	//정보를 확인했으면, 지워주고 isUpdateLastSceneData를 true로 만들어 주자(씬이 변경되고 한번만 체크해 주면 되므로)
	SCENEMANAGER->eraseLastInfo();
	isUpdateLastSceneData = true;

	if (isUsed == true && isFromBattleScene)
	{
		auto& items = m_inven->getItemPotion();
		for (auto item = items.begin(); item != items.end(); item++)
		{
			if ((*item)->m_ItemName == usedItem)
			{
				(*item)->m_count -= 1;
				if ((*item)->m_count <= 0)
				{
					items.erase(item);
				}

				auto temp = new UsedItemInfo;
				temp->itemKey = usedItem;
				temp->isUsed = true;
				m_sceneResult = temp;
				SCENEMANAGER->scenePop(true);
				return;
			}
		}
	}
}

void InvenScene::update(float _deltaTime)
{
	if (isUpdateLastSceneData == false)
		checkSceneChangeInfo();

	m_inven->update(_deltaTime);
	//isFromBattleScene = true로 임시로 만든 키
	if (KEYMANAGER->isOnceKeyDown(P1_P))
	{
		isFromBattleScene = true;
		isTownInven = false;
	}


	if (m_inven->getOpenMenu() == false)
	{
		if (KEYMANAGER->isOnceKeyDown(P1_X))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			SCENEMANAGER->scenePop();
		}
	}
	if (m_inven->getCloseInven())
	{
		m_inven->setCloseInven(false);
		m_inven->setSameNameInven(false);
		m_inven->setItemCount(0);
		SCENEMANAGER->scenePop();
	}

	if (m_inven->getOpenMenu() == false)
	{
		if (KEYMANAGER->isOnceKeyDown(P1_RIGHT))
		{
			pointerCount = 0;

			if (invenSceneCount == 2)
			{
				invenSceneCount = 2;
				m_inven->m_itemCount = 0;
			}
			else
				invenSceneCount++;

			if (m_inven->m_isItemTag)
			{
				m_inven->m_isItemTag = false;
				m_inven->m_isImportTag = true;
				m_inven->setItemCount(false);
				m_inven->setImportTag(true);
			}
			else if (m_inven->m_isImportTag)
			{
				m_inven->m_isImportTag = false;
				m_inven->m_isPokeBallTag = true;
			}

			if (m_inven->m_isPokeBallTag)
				return;
		}
	}


	if (m_inven->getOpenMenu() == false)
	{
		if (KEYMANAGER->isOnceKeyDown(P1_LEFT))
		{
			pointerCount = 0;

			if (invenSceneCount != 0)
			{
				m_inven->m_itemCount = 0;
				invenSceneCount--;
			}
			else
				invenSceneCount = 0;

			if (m_inven->m_isItemTag)
				return;

			if (m_inven->m_isItemTag == false && m_inven->m_isImportTag == true)
			{
				m_inven->m_isItemTag = true;
				m_inven->m_isImportTag = false;
			}
			if (m_inven->m_isImportTag == false && m_inven->m_isPokeBallTag == true)
			{
				m_inven->m_isImportTag = true;
				m_inven->m_isPokeBallTag = false;
			}
		}
	}
	// UI 모션 작업
	if (isUp)
	{
		if (moveCount < 20)
			moveCount++;
		if (moveCount == 20)
			isUp = false;
	}
	else
	{
		if (moveCount >= 0)
			moveCount--;
		if (moveCount == 0)
			isUp = true;
	}
	// 인벤씬에서 메뉴 나오게 하는 작업

	if (!isTownInven && m_inven->getOpenMenu() == false && m_isMainClose)
	{
		if (KEYMANAGER->isOnceKeyDown(P1_Z))
		{
			m_isMainClose = false;
			SCENEMANAGER->scenePop();
		}
	}

	if (!isTownInven && !isFromBattleScene)
	{
		if (KEYMANAGER->isOnceKeyDown(P1_Z))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			isTownInven = true;
			m_inven->setIsOpenMenu(true);
		}
	}

	if (m_inven->getOpenMenu() == true && isTownInven == true)
	{
		if (KEYMANAGER->isOnceKeyDown(P1_UP))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			if (pointerCount != 0)
				pointerCount--;
		}
		if (KEYMANAGER->isOnceKeyDown(P1_DOWN))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			if (pointerCount != 3 && invenSceneCount == 0 ||
				pointerCount != 2 && invenSceneCount == 1 ||
				pointerCount != 2 && invenSceneCount == 2)
				pointerCount++;
		}

		// 타운인벤메뉴일 경우 메뉴에 따른 상호작용 //
		if (pointerCount == 3 && invenSceneCount == 0 ||
			pointerCount == 2 && invenSceneCount == 1 ||
			pointerCount == 2 && invenSceneCount == 2)
		{
			if (KEYMANAGER->isOnceKeyDown(P1_Z))
			{
				SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

				pointerCount = 0;
				isTownInven = false;
				m_inven->setIsOpenMenu(false);
			}
		}

		if (pointerCount == 2 && invenSceneCount == 0)
		{
			if (KEYMANAGER->isOnceKeyDown(P1_Z))
			{
				SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

				m_isThrowItem = true;
			}
		}

		//  그만하기 외 count 값 빼주기
		if (pointerCount != 3 && invenSceneCount == 0)
		{
			if (KEYMANAGER->isOnceKeyDown(P1_Z))
			{
				SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

				sellPotion();
			}
		}
		if (pointerCount != 2 && invenSceneCount == 1)
		{
			if (KEYMANAGER->isOnceKeyDown(P1_Z))
			{
				SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

				sellImport();
			}
		}
		if (pointerCount != 2 && invenSceneCount == 2)
		{
			if (KEYMANAGER->isOnceKeyDown(P1_Z))
			{
				SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

				sellPokeBall();
			}
		}


		if (KEYMANAGER->isOnceKeyDown(P1_X))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			isTownInven = false;
			m_inven->setIsOpenMenu(false);
		}
	}
	// ===================== 배틀인벤메뉴일 경우 메뉴에 따른 상호작용 ===================== //
	if (m_inven->getOpenMenu() == false && isFromBattleScene == true)
	{
		if (!isBattleInven)
		{
			if (KEYMANAGER->isOnceKeyDown(P1_Z))
			{
				SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

				isBattleInven = true;
				m_inven->setIsOpenMenu(true);
			}
		}
	}
	if (m_inven->getOpenMenu() == true && isFromBattleScene == true)
	{
		if (KEYMANAGER->isOnceKeyDown(P1_UP))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			if (pointerCount != 0)
				pointerCount--;
		}
		if (KEYMANAGER->isOnceKeyDown(P1_DOWN))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			if (pointerCount == 0 && invenSceneCount != 1)
				pointerCount++;
		}
		if (pointerCount == 1 && invenSceneCount == 0 ||
			pointerCount == 0 && invenSceneCount == 1 ||
			pointerCount == 1 && invenSceneCount == 2)
		{
			if (KEYMANAGER->isOnceKeyDown(P1_Z))
			{
				SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

				isBattleInven = false;
				m_inven->setIsOpenMenu(false);
				isFromBattleScene = false;
			}
		}
		// 배틀씬에서 아이템 쓴다를 선택한다.
		if (KEYMANAGER->isOnceKeyDown(P1_Z))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			std::cout << "인배틀씬 아이템을 사용합니다." << std::endl;
			if (pointerCount == 0 && invenSceneCount == 0)
			{
				setSettedItem();
				ItemInfo* temp = new ItemInfo;
				temp->name = m_settedItemInfo.name;
				temp->healPoint = m_settedItemInfo.healPoint;
				temp->catchRatio = m_settedItemInfo.catchRatio;
				// 씬넘기기전에 현재 씬정보를 m_sceneResult에 남겨둔다(void*)로 캐스팅한다.
				m_sceneResult = (void*)temp;
				SCENEMANAGER->scenePush("PocketmonBagScene", temp, isFromBattleScene);
				return;
			}
			if (pointerCount == 0 && invenSceneCount == 2)
			{
				setSettedItem();
				ItemInfo* temp = new ItemInfo;
				temp->name = m_settedItemInfo.name;
				temp->catchRatio = m_settedItemInfo.catchRatio;
				// 씬넘기기전에 현재 씬정보를 m_sceneResult에 남겨둔다(void*)로 캐스팅한다.
				m_sceneResult = (void*)temp;
				sellPokeBall();
				SCENEMANAGER->scenePop(true);

				return;
			}

		}
	}
	// ====================== 아이템 버리기 카운트 ==================== //t
	if (m_isThrowItem)
	{
		if (KEYMANAGER->isOnceKeyDown(P1_DOWN))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			m_throwItemCount++;
		}
		if (KEYMANAGER->isOnceKeyUp(P1_UP))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			if (m_throwItemCount != 0)
				m_throwItemCount--;
		}

	}

	//  =======================  인벤에서 물건 파는거 연습 ======================= //
	if (KEYMANAGER->isOnceKeyDown(P1_Q))
	{
		if (m_inven->m_isItemTag)
			sellPotion();

		if (m_inven->m_isImportTag)
			sellImport();

		if (m_inven->m_isPokeBallTag)
			sellPokeBall();
	}
	//  =======================  인벤에서 물건 파는거 연습 ======================= //
}


void InvenScene::release()
{

}

void InvenScene::render(HDC hdc)
{

	m_BackGround->render(hdc);

	switch (invenSceneCount)
	{
	case ITEM:
		m_ItemBag->render(hdc, 20, 160);
		m_ItemTag->render(hdc, 15, 5);
		if (isChangeScene)
		{
			m_inven->m_itemInit = false;
			isChangeScene = false;
		}
		m_inven->debugRender(hdc);

		// 움직이는 작업을 해야함 //
		m_nextArrow->render(hdc, 250 + moveCount, WINSIZEY / 2 - 110);

		// =============== 타운에서 인벤 꺼냈을때 메뉴창 =============== //
		if (isTownInven)
		{
			auto& itemVector = m_inven->getItemPotion();

			for (auto item = itemVector.begin(); item != itemVector.end();)
			{
				if ((*item)->getItemNum() == m_inven->m_itemCount && (*item)->getItemName() == "닫기")
				{
					m_inven->setIsOpenMenu(false);
					isTownInven = false;
					m_isMainClose = true;
					m_inven->m_isItemTag = true;
				}
				if ((*item)->getItemNum() == m_inven->m_itemCount && (*item)->getItemName() != "닫기")
				{
					if (!m_isThrowItem)
						m_ItemInvenMenu->render(hdc, WINSIZEX / 2 + 200, WINSIZEY / 2);

					m_invenMenuBottom->render(hdc, 170, WINSIZEY / 2 + 173);
					item++;
				}

				else item++;
			}

			for (int i = 0; i < 5; i++)
			{
				for (auto item = itemVector.begin(); item != itemVector.end();)
				{
					if ((*item)->getItemNum() == m_inven->m_itemCount && (*item)->getItemName() != "닫기")
					{
						if (i <= 3)
						{
							if (!m_isThrowItem)
							{
								UTIL::PrintText(hdc, m_itemChoiceMenu[i].c_str(), "소야바른9", WINSIZEX / 2 + 315, WINSIZEY / 2 + 55 + (i * 75), 55, RGB(0, 0, 0));
								m_currentPointer->render(hdc, WINSIZEX / 2 + 230, WINSIZEY / 2 + 20 + (pointerCount * 75));
							}
						}
						if (i == 4)
						{
							if (m_inven->m_itemCount == (*item)->getItemNum())
							{
								UTIL::PrintText(hdc, (*item)->getItemName().c_str(), "소야바른9", 200, WINSIZEY - 170, 55, RGB(0, 0, 0), true);
								if (!m_isThrowItem)
									UTIL::PrintText(hdc, m_itemChoiceMenu[i].c_str(), "소야바른9", 200, WINSIZEY - 100, 55, RGB(0, 0, 0), true);
								break;
							}
						}
						item++;
					}
					else
						item++;
				}
			}
		}

		// =============== 배틀씬에서 인벤 꺼냈을때 메뉴창 =============== //

		if (isBattleInven)
		{
			auto& itemVector = m_inven->getItemPotion();

			for (auto item = itemVector.begin(); item != itemVector.end();)
			{
				if ((*item)->getItemNum() == m_inven->m_itemCount && (*item)->getItemName() == "닫기")
				{
					m_inven->setIsOpenMenu(false);
					isTownInven = false;
					m_isMainClose = true;
					m_inven->m_isItemTag = true;
				}
				if ((*item)->getItemNum() == m_inven->m_itemCount && (*item)->getItemName() != "닫기")
				{
					m_battleSceneInvenMenu->render(hdc, WINSIZEX / 2 + 200, WINSIZEY / 2 + 167);
					m_invenMenuBottom->render(hdc, 170, WINSIZEY / 2 + 173);
					item++;
				}

				else item++;
			}

			for (int i = 0; i < 3; i++)
			{
				for (auto item = itemVector.begin(); item != itemVector.end();)
				{
					if ((*item)->getItemNum() == m_inven->m_itemCount && (*item)->getItemName() != "닫기")
					{
						if (i <= 1)
						{
							UTIL::PrintText(hdc, m_battleSceneItemMenu[i].c_str(), "소야바른9", WINSIZEX / 2 + 315, WINSIZEY / 2 + 210 + (i * 75), 55, RGB(0, 0, 0));
							m_currentPointer->render(hdc, WINSIZEX / 2 + 230, WINSIZEY / 2 + 170 + (pointerCount * 75));
						}
						if (i == 2)
						{
							if (m_inven->m_itemCount == (*item)->getItemNum())
							{
								UTIL::PrintText(hdc, (*item)->getItemName().c_str(), "소야바른9", 200, WINSIZEY - 170, 55, RGB(0, 0, 0), true);
								UTIL::PrintText(hdc, m_battleSceneItemMenu[i].c_str(), "소야바른9", 200, WINSIZEY - 100, 55, RGB(0, 0, 0), true);
								break;
							}
						}
						item++;
					}
					else
						item++;
				}
			}
		}
		break;

	case IMPORT:
		m_ImportBag->render(hdc, 20, 155);
		m_ImporTag->render(hdc, 15, 5);
		m_inven->importRender(hdc);
		isChangeScene = true;

		if (isTownInven)
		{
			auto& itemVector = m_inven->getImportItem();

			for (auto item = itemVector.begin(); item != itemVector.end();)
			{
				if ((*item)->getItemNum() == m_inven->m_importCount && (*item)->getItemName() == "임폴트닫기")
				{
					m_inven->setIsOpenMenu(false);
					isTownInven = false;
					m_isMainClose = true;
					m_inven->m_isImportTag = true;
					m_inven->m_itemCount = 0;
				}
				if ((*item)->getItemNum() == m_inven->m_importCount && (*item)->getItemName() != "임폴트닫기")
				{
					m_otherInvenMenu->render(hdc, WINSIZEX / 2 + 200, WINSIZEY / 2 + 60);
					m_invenMenuBottom->render(hdc, 170, WINSIZEY / 2 + 173);
					item++;
				}

				else item++;
			}

			for (int i = 0; i < 4; i++)
			{
				for (auto item = itemVector.begin(); item != itemVector.end();)
				{
					if ((*item)->getItemNum() == m_inven->m_importCount && (*item)->getItemName() != "임폴트닫기")
					{
						if (i <= 2)
						{
							UTIL::PrintText(hdc, m_importChoiceMenu[i].c_str(), "소야바른9", WINSIZEX / 2 + 315, WINSIZEY / 2 + 115 + (i * 75), 55, RGB(0, 0, 0));
							m_currentPointer->render(hdc, WINSIZEX / 2 + 230, WINSIZEY / 2 + 75 + (pointerCount * 75));
						}
						if (i == 3)
						{
							if (m_inven->m_importCount == (*item)->getItemNum())
							{
								UTIL::PrintText(hdc, (*item)->getItemName().c_str(), "소야바른9", 200, WINSIZEY - 170, 55, RGB(0, 0, 0), true);
								UTIL::PrintText(hdc, m_importChoiceMenu[i].c_str(), "소야바른9", 200, WINSIZEY - 100, 55, RGB(0, 0, 0), true);
								break;
							}
						}
						item++;
					}
					else
						item++;
				}
			}
		}
		// =============== 배틀씬에서 인벤 꺼냈을때 메뉴창 =============== //
		if (isBattleInven)
		{
			auto& itemVector = m_inven->getImportItem();

			for (auto item = itemVector.begin(); item != itemVector.end();)
			{
				if ((*item)->getItemNum() == m_inven->m_importCount && (*item)->getItemName() == "임폴트닫기")
				{
					m_inven->setIsOpenMenu(false);
					isTownInven = false;
					m_isMainClose = true;
					m_inven->m_isImportTag = true;
				}
				if ((*item)->getItemNum() == m_inven->m_importCount && (*item)->getItemName() != "임폴트닫기")
				{
					m_battleSceneInvenMenu->render(hdc, WINSIZEX / 2 + 200, WINSIZEY / 2 + 167);
					m_invenMenuBottom->render(hdc, 170, WINSIZEY / 2 + 173);
					item++;
				}

				else item++;
			}

			for (int i = 0; i < 2; i++)
			{
				for (auto item = itemVector.begin(); item != itemVector.end();)
				{
					if ((*item)->getItemNum() == m_inven->m_importCount && (*item)->getItemName() != "임폴트닫기")
					{
						if (i == 0)
						{
							UTIL::PrintText(hdc, m_battleSceneImportMenu[i].c_str(), "소야바른9", WINSIZEX / 2 + 315, WINSIZEY / 2 + 245 + (i * 75), 55, RGB(0, 0, 0));
							m_currentPointer->render(hdc, WINSIZEX / 2 + 230, WINSIZEY / 2 + 210 + (pointerCount * 75));
						}
						if (i == 1)
						{
							if (m_inven->m_importCount == (*item)->getItemNum())
							{
								UTIL::PrintText(hdc, (*item)->getItemName().c_str(), "소야바른9", 200, WINSIZEY - 170, 55, RGB(0, 0, 0), true);
								UTIL::PrintText(hdc, m_battleSceneImportMenu[i].c_str(), "소야바른9", 200, WINSIZEY - 100, 55, RGB(0, 0, 0), true);
								break;
							}
						}
						item++;
					}
					else
						item++;
				}
			}
		}

		// 움직이는 작업을 해야함
		m_nextArrow->render(hdc, 250 + moveCount, WINSIZEY / 2 - 110);
		m_beforeArrow->render(hdc, 10 - moveCount, WINSIZEY / 2 - 110);
		break;

	case POKEBALL:
		m_PokeBallBag->render(hdc, 20, 160);
		m_PokeBallTag->render(hdc, 15, 5);
		m_inven->pokeBallRender(hdc);

		if (isTownInven)
		{
			auto& itemVector = m_inven->getPokeBall();

			for (auto item = itemVector.begin(); item != itemVector.end();)
			{
				if ((*item)->getItemNum() == m_inven->m_pokeBallCount && (*item)->getItemName() == "몬스터볼닫기")
				{
					m_inven->setIsOpenMenu(false);
					isTownInven = false;
					m_isMainClose = true;
					m_inven->m_isPokeBallTag = true;
				}
				if ((*item)->getItemNum() == m_inven->m_pokeBallCount && (*item)->getItemName() != "몬스터볼닫기")
				{
					m_otherInvenMenu->render(hdc, WINSIZEX / 2 + 200, WINSIZEY / 2 + 60);
					m_invenMenuBottom->render(hdc, 170, WINSIZEY / 2 + 173);
					item++;
				}

				else item++;
			}

			for (int i = 0; i < 4; i++)
			{
				for (auto item = itemVector.begin(); item != itemVector.end();)
				{
					if ((*item)->getItemNum() == m_inven->m_pokeBallCount && (*item)->getItemName() != "몬스터볼닫기")
					{
						if (i <= 2)
						{
							UTIL::PrintText(hdc, m_ballChoiceMenu[i].c_str(), "소야바른9", WINSIZEX / 2 + 315, WINSIZEY / 2 + 115 + (i * 75), 55, RGB(0, 0, 0));
							m_currentPointer->render(hdc, WINSIZEX / 2 + 230, WINSIZEY / 2 + 75 + (pointerCount * 75));
						}
						if (i == 3)
						{
							if (m_inven->m_pokeBallCount == (*item)->getItemNum())
							{
								UTIL::PrintText(hdc, (*item)->getItemName().c_str(), "소야바른9", 200, WINSIZEY - 170, 55, RGB(0, 0, 0), true);
								UTIL::PrintText(hdc, m_ballChoiceMenu[i].c_str(), "소야바른9", 200, WINSIZEY - 100, 55, RGB(0, 0, 0), true);
								break;
							}
						}
						item++;
					}
					else
						item++;
				}
			}
		}
		// =============== 배틀씬에서 인벤 꺼냈을때 메뉴창 =============== //
		if (isBattleInven)
		{
			auto& itemVector = m_inven->getPokeBall();

			for (auto item = itemVector.begin(); item != itemVector.end();)
			{
				if ((*item)->getItemNum() == m_inven->m_pokeBallCount && (*item)->getItemName() == "몬스터볼닫기")
				{
					m_inven->setIsOpenMenu(false);
					isTownInven = false;
					m_isMainClose = true;
					m_inven->m_isPokeBallTag = true;
				}
				if ((*item)->getItemNum() == m_inven->m_pokeBallCount && (*item)->getItemName() != "몬스터볼닫기")
				{
					m_battleSceneInvenMenu->render(hdc, WINSIZEX / 2 + 200, WINSIZEY / 2 + 167);
					m_invenMenuBottom->render(hdc, 170, WINSIZEY / 2 + 173);
					item++;
				}

				else item++;
			}

			for (int i = 0; i < 3; i++)
			{
				for (auto item = itemVector.begin(); item != itemVector.end();)
				{
					if ((*item)->getItemNum() == m_inven->m_pokeBallCount && (*item)->getItemName() != "몬스터볼닫기")
					{
						if (i <= 1)
						{
							UTIL::PrintText(hdc, m_battleSceneItemMenu[i].c_str(), "소야바른9", WINSIZEX / 2 + 315, WINSIZEY / 2 + 210 + (i * 75), 55, RGB(0, 0, 0));
							m_currentPointer->render(hdc, WINSIZEX / 2 + 230, WINSIZEY / 2 + 170 + (pointerCount * 75));
						}
						if (i == 2)
						{
							if (m_inven->m_pokeBallCount == (*item)->getItemNum())
							{
								UTIL::PrintText(hdc, (*item)->getItemName().c_str(), "소야바른9", 200, WINSIZEY - 170, 55, RGB(0, 0, 0), true);
								UTIL::PrintText(hdc, m_battleSceneItemMenu[i].c_str(), "소야바른9", 200, WINSIZEY - 100, 55, RGB(0, 0, 0), true);
								break;
							}
						}
						item++;
					}
					else
						item++;
				}
			}
		}

		// =============== 아이템 버리는 작업 =============== //
		if (m_isThrowItem)
		{
			std::string frontNum = "X 00";
			std::string Num = std::to_string(m_throwItemCount);

			m_battleSceneInvenMenu->render(hdc, WINSIZEX / 2 + 200, WINSIZEY / 2 + 167);
			auto& itemVector = m_inven->getItemPotion();

			for (auto item = itemVector.begin(); item != itemVector.end();)
			{
				if (m_inven->m_itemCount == (*item)->getItemNum())
				{
					UTIL::PrintText(hdc, (*item)->getItemName().c_str(), "소야바른9", 200, WINSIZEY - 170, 55, RGB(0, 0, 0), true);
					UTIL::PrintText(hdc, Num.c_str(), "소야바른9", 250, WINSIZEY - 170, 55, RGB(0, 0, 0), true);
					UTIL::PrintText(hdc, m_throwItem[0].c_str(), "소야바른9", 200, WINSIZEY - 100, 55, RGB(0, 0, 0), true);

					UTIL::PrintText(hdc, frontNum.c_str(), "소야바른9", 250, WINSIZEY - 170, 55, RGB(0, 0, 0), true);
					m_currentPointer->render(hdc, WINSIZEX / 2 + 230, WINSIZEY / 2 + 210 + (pointerCount * 75));
					item++;

					break;
				}
				else item++;
			}


		}














		// 움직이는 작업을 해야함
		m_beforeArrow->render(hdc, 10 - moveCount, WINSIZEY / 2 - 110);
		break;

	default:
		break;
	}

}

void InvenScene::afterRender(HDC hdc)
{
}

void InvenScene::debugRender(HDC hdc)
{
}

// ================인벤 파는 작업 ==================== //
void InvenScene::sellPotion()
{
	int countTemp = 0;
	auto& itemVector = m_inven->getItemPotion();
	int temp, a, b;

	for (auto item = itemVector.begin(); item != itemVector.end();)
	{
		// 닫기버튼은 예외처리 해야함
		if (m_inven->m_itemCount == (*item)->getItemNum() && (*item)->getItemName() != "닫기")
		{
			countTemp = (*item)->getCount();
			countTemp--;
			(*item)->m_count = countTemp;
			// 한번 다시 보기(아이템 인포 넣어주기) //
			m_settedItemInfo = (*item)->getItemInfo();
			// 한번 다시 보기(아이템 인포 넣어주기) //
			a = (*item)->getItemNum();
			b = (*(item + 1))->getItemNum();

			if (countTemp == 0)
			{
				temp = a;
				a = b;
				b = temp;

				item = itemVector.erase(item);
				(*(item))->setItemNum(b);
				m_inven->setIsDeleteItem(true);
			}
			item++;
		}
		else item++;
	}
}

void InvenScene::setSettedItem()
{
	int countTemp = 0;
	auto& itemVector = m_inven->getItemPotion();
	int temp, a, b;

	for (auto item = itemVector.begin(); item != itemVector.end();)
	{
		// 닫기버튼은 예외처리 해야함
		if (m_inven->m_itemCount == (*item)->getItemNum() && (*item)->getItemName() != "닫기")
		{
			countTemp = (*item)->getCount();
			(*item)->m_count = countTemp;
			// 한번 다시 보기(아이템 인포 넣어주기) //
			m_settedItemInfo = (*item)->getItemInfo();
			return;
		}
		else item++;
	}
}

void InvenScene::sellImport()
{
	int countTemp = 0;
	auto& itemVector = m_inven->getImportItem();
	int temp, a, b;

	for (auto item = itemVector.begin(); item != itemVector.end();)
	{
		// 닫기버튼은 예외처리 해야함
		if (m_inven->m_importCount == (*item)->getItemNum() && (*item)->getItemName() != "임폴트닫기")
		{
			countTemp = (*item)->getCount();
			countTemp--;
			(*item)->m_count = countTemp;

			a = (*item)->getItemNum();
			b = (*(item + 1))->getItemNum();

			if (countTemp == 0)
			{
				temp = a;
				a = b;
				b = temp;

				item = itemVector.erase(item);
				(*(item))->setItemNum(b);
				m_inven->setIsDeleteItem(true);
			}
			item++;
		}
		else item++;
	}
}

void InvenScene::sellPokeBall()
{
	int countTemp = 0;
	auto& itemVector = m_inven->getPokeBall();
	int temp, a, b;

	for (auto item = itemVector.begin(); item != itemVector.end();)
	{
		// 닫기버튼은 예외처리 해야함
		if (m_inven->m_pokeBallCount == (*item)->getItemNum() && (*item)->getItemName() != "몬스터볼닫기")
		{
			countTemp = (*item)->getCount();
			countTemp--;
			(*item)->m_count = countTemp;

			a = (*item)->getItemNum();
			b = (*(item + 1))->getItemNum();

			if (countTemp == 0)
			{
				temp = a;
				a = b;
				b = temp;

				item = itemVector.erase(item);
				(*(item))->setItemNum(b);
				m_inven->setIsDeleteItem(true);
			}
			item++;
		}
		else item++;
	}
}
// ================인벤 파는 작업 ==================== //




ItemInfo InvenScene::getItemInfo()
{
	return m_settedItemInfo;
}

