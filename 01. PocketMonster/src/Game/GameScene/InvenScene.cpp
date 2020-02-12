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

	m_invenSceneType = ITEM;    // 디폴트 아이템창  = ITEM
	invenSceneCount = 0;		// 아이템창 렌더 시켜줄 카운트
	isChangeScene = false;
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
	    {
	    	moveCount++;
	    }
		if (moveCount == 20)
			isUp = false;
	}
	else
	{
		if (moveCount >= 0)
		{
			moveCount--;
		}
		if (moveCount == 0)
			isUp = true;
	}

	if (ShopCount < 1)
	{
		//sellScene();
		//ShopCount++;
	}
}

void InvenScene::release()
{
}

void InvenScene::render(HDC hdc)
{
	
	//이렇게 랜더 하지 말것,
	//IMAGEMANAGER->render("인벤토리씬", hdc);

	//이렇게 렌더 할것
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
		
		// 움직이는 작업을 해야함
		m_nextArrow->render(hdc,250 +moveCount , WINSIZEY /2 -110 );
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
	/*	m_inven->m_isPokeBallInit = false;*/

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

void InvenScene::sellScene()
{
	int countTemp = 0;
	auto& itemVector = m_inven->getItemPotion();

	for (auto item = itemVector.begin() ;  item != itemVector.end(); )
	{
		if ((*item)->getItemName() == "상처약")
		{
			countTemp = (*item)->getCount();
			countTemp--;
			(*item)->m_count = countTemp;
			
			if (countTemp == 0) {
				item = itemVector.erase(item);
			}
		}
		else item++;

		
	}
}


