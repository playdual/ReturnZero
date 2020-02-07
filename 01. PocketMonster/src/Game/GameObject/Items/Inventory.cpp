#include "stdafx.h"
#include "Inventory.h"
#include "Common/SystemManagers.h"
#include "Game/GameManager/ItemManager.h"

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}

bool Inventory::init()
{
	itemNum = 0;
	nextText = true;

	m_item.push_back(ITEMMANAGER->findItem("상처약"));
	m_item.push_back(ITEMMANAGER->findItem("좋은상처약"));
	m_item.push_back(ITEMMANAGER->findItem("풀회복약"));
	

	int count = 0;
	for (auto&item : m_item)
	{
		item->m_iRect.top = item->getRect().top + (count * 80);
		item->m_iRect.bottom = item->getRect().bottom + (count * 80);
		item->setRect(item->m_iRect);
		item->m_itemNum = itemNum;
		count++;
		itemNum++;
	}

	return true;
}

int itemCount = 0;
void Inventory::update(float _deltaTime)
{
	// add item to inven (change Rect width, height) 
	if (KEYMANAGER->isOnceKeyDown(P1_DOWN))
	{
		for (auto&item : m_item)
		{
			if (item->m_itemNum == itemCount)
			{
				itemCount++;
				break;
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown(P1_UP))
	{
		for (auto&item : m_item)
		{
			if (item->m_itemNum == itemCount)
			{
				itemCount--;
				break;
			}
		}
	}
}

void Inventory::render(HDC hdc)
{
	
}

void Inventory::afterRender(HDC hdc)
{
}

void Inventory::debugRender(HDC hdc)
{
	// show text 선언 //
	std::string str;
	int count;
	std::string descrip;
	std::string multiPly;

	// show text 선언 //

	for (auto&HealPotion : m_item)
	{
		str = HealPotion->getItemName();
		count =  HealPotion->getCount();
		multiPly = "x";

		
		//UTIL::drawRect(hdc, HealPotion->getRect());
		// potion name show
		UTIL::PrintText(hdc, str.c_str(), "소야바른9",
			HealPotion->getRect().left + 20, HealPotion->getRect().top + 30, 40, RGB(0, 0, 0), true);
		
		// count name show //
		UTIL::PrintText(hdc, std::to_string(count).c_str(), "소야바른9",
			HealPotion->getRect().left + 500, HealPotion->getRect().top + 30, 40, RGB(0, 0, 0), true);
		
		// description text show //
		UTIL::PrintText(hdc, multiPly.c_str(), "소야바른9",
			HealPotion->getRect().left + 400, HealPotion->getRect().top + 30, 40, RGB(0, 0, 0), true);

	}

	//변수명 저렇게 짓지마시오 : desText -> 의미 불분명
	//그리고 아이템들이니까 items라고 짓던가 vectorItem이런식으로 지으시오
	for (auto& item : m_item) {
		if (item->m_itemNum == itemCount) {

			UTIL::PrintText(hdc, item->getDescript().c_str(), "소야바른9", 
				WINSIZEX / 2 - 300, WINSIZEY - 130, 40, RGB(255, 255, 255), true);


			//코드는 다음과 같이 짜시오...
			item->render(hdc);		

		}
	}
}
