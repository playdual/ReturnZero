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

bool InvenScene::init()
{
	//상점 연습 작업
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
	m_InvenMenu = IMAGEMANAGER->findImage("인벤메뉴");
	m_invenMenuBottom = IMAGEMANAGER->findImage("인벤메뉴상세");

	m_invenSceneType = ITEM;    // 디폴트 아이템창  = ITEM
	invenSceneCount = 0;		// 아이템창 렌더 시켜줄 카운트

	isChangeScene = false; 
	
	// 우선 isBattleScene은 false 처리  = Battle일 경우 창이 틀림0
	isBattleScene = false;		


	return true;
}

void InvenScene::update(float _deltaTime)
{
	m_inven->update(_deltaTime);
	
	if (m_inven->getCloseInven())
	{
		m_inven->setCloseInven(false);
		m_inven->setSameNameInven(false);
		m_inven->setItemCount(0);
		SCENEMANAGER->scenePop();
	}

	if (KEYMANAGER->isOnceKeyDown(P1_RIGHT))
	{
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

	if (KEYMANAGER->isOnceKeyDown(P1_LEFT))
	{
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
	if (KEYMANAGER->isOnceKeyDown(P1_Z))
		isBattleScene = true;



	// 인벤에서 물건 파는거 연습
	if (KEYMANAGER->isOnceKeyDown(P1_q))
	{
		if(m_inven->m_isItemTag)
			sellPotion();

		if (m_inven->m_isImportTag)
			sellImport();

		if (m_inven->m_isPokeBallTag)
			sellPokeBall();
	}
	
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
		
		if (isBattleScene)
		{
			m_InvenMenu->render(hdc, WINSIZEX / 2 + 200, WINSIZEY / 2 + 10);
			m_invenMenuBottom->render(hdc, 170, WINSIZEY / 2 + 173);
			for (int i = 0; i < 4; i++)
			{
				UTIL::PrintText(hdc, m_invenChoiceMenu[i].c_str(), "소야바른9", WINSIZEX / 2 + 315, WINSIZEY / 2 + 74 + (i * 70), 50, RGB(0, 0, 0));
			}
		}

		break;

	case IMPORT:
		m_ImportBag->render(hdc, 20, 155);
		m_ImporTag->render(hdc, 15, 5);
		m_inven->importRender(hdc);
		isChangeScene = true;

		// 움직이는 작업을 해야함
		m_nextArrow->render(hdc, 250 + moveCount, WINSIZEY / 2 - 110);
		m_beforeArrow->render(hdc, 10 - moveCount, WINSIZEY / 2 - 110);
		break;

	case POKEBALL:
		m_PokeBallBag->render(hdc, 20, 160);
		m_PokeBallTag->render(hdc, 15, 5);
		m_inven->pokeBallRender(hdc);

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

			a = (*item)->getItemNum();
			b = (*(item+1))->getItemNum();

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
void InvenScene::menuChoice()
{
	int countTemp = 0;
	auto& itemVector = m_inven->getItemPotion();

	for (auto item = itemVector.begin(); item != itemVector.end();)
	{
		// 닫기버튼은 예외처리 해야함
		if (m_inven->m_itemCount == (*item)->getItemNum())
		{
			// UTIL::PrintText()
		}
	}
}


