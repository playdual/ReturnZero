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
	ITEMMANAGER->init(); // 여기에 Itemmanager을 인잇하고
	m_isCloseInven = false;
	m_isSameNameClose = false;
	m_itemCount = 0;

	//사고팔고 임시 작업
	isItemDelete = false;


	// 인벤 태그 체크
	m_isItemTag = true;
	m_isImportTag = false;
	m_isPokeBallTag = false;

	// 아이템 태그 카운트 선언 //
	itemNum = 0;
	count = 0;
	insertNum = 0;
	m_itemInit = false;
	m_isItemTagCheck = true;

	// 퀘스트 아이템 태그 카운트 선언 //
	m_importNum = 0;
	m_importCount = 0;
	m_isImportInit = false;
	m_isImportTagCheck = false;
	m_importPlaceCount = 0;
	// 포켓몬볼 아이템 태그 카운트 선언 //
	m_pokeBallNum = 0;		//들어오는 아이템 번호 순서
	m_pokeBallCount = 0;	// 현재 인벤에서 보여줄 아이템 표시 변수
	m_pokePlaceCount = 0;   // 렉트 위치값 변경을 위한 변수
	m_isPokeBallInit = false;

	// 인벤에서 메뉴창이 뜨면 카운트를 막아야한다.
	m_isOpenMenu = false;

	//nextText = true;

	// =============== Item =============== //
	m_potionItem.push_back(ITEMMANAGER->findItem("상처약"));
	m_potionItem.push_back(ITEMMANAGER->findItem("좋은상처약"));
	m_potionItem.push_back(ITEMMANAGER->findItem("풀회복약"));
	m_potionItem.push_back(ITEMMANAGER->findItem("닫기"));

	// =============== ball =============== //
	m_pockeBallItem.push_back(ITEMMANAGER->findItem("몬스터볼"));
	m_pockeBallItem.push_back(ITEMMANAGER->findItem("몬스터볼닫기"));

	// =============== Import =============== //
	m_importItem.push_back(ITEMMANAGER->findItem("오박사의소포"));
	m_importItem.push_back(ITEMMANAGER->findItem("임폴트닫기"));

	// ============= Ui ==================== //
	m_currentArrow = IMAGEMANAGER->findImage("현재아이템표시");

	itemTagInit();

	return true;
}


void Inventory::update(float _deltaTime)
{
	// 첫번째 m_itemName 을 담을 변수
	std::string temp;

	if (m_isChangeitemCount)
	{
		isItemDelete = true;
		for (int i = 0; i < m_potionItem.size(); ++i)
		{
			m_potionItem[i]->setItemNum(i);
			if(i == 4)
				m_isChangeitemCount = false;
		}
	}

	// add item to inven (change Rect width, height) 
	if (!m_isOpenMenu)
	{
		if (KEYMANAGER->isOnceKeyDown(P1_DOWN))
		{
			// 아이템 목록 체크 //
			if (m_isItemTag)
			{
				for (auto&item : m_potionItem)
				{
					if (item->m_itemNum == m_itemCount)
					{
						if (item->m_ItemName != "닫기")
						{
							m_itemCount++;
							break;
						}
					}
				}
			}
			// 임포트 아이템 순서 //
			if (m_isImportTag)
			{
				for (auto&item : m_importItem)
				{
					if (item->m_itemNum == m_importCount)
					{
						if (item->m_ItemName != "임폴트닫기")
						{
							m_importCount++;
							break;
						}
					}
				}
			}
			// 포켓볼 아이템 순서 //
			 if (m_isPokeBallTag)
			{
				for (auto&item : m_pockeBallItem)
				{
					if (item->m_itemNum == m_pokeBallCount)
					{
						if (item->m_ItemName != "몬스터볼닫기")
						{
							m_pokeBallCount++;
							break;
						}
					}
				}
			}
		}

		if (!m_isOpenMenu)
		{
			if (KEYMANAGER->isOnceKeyDown(P1_UP))
			{
				if (m_isItemTag)
				{
					for (auto&item : m_potionItem)
					{
						if (item->m_itemNum == m_itemCount)
						{
							if (item->m_itemNum == 0)
						      // 첫번째 아이템 이름을 담아서 예외처리 해준다.
								temp = item->m_ItemName;
							if (item->m_ItemName != temp)
							{
								m_itemCount--;
								break;
							}
						}
					}
				}

				// 임포트 아이템 순서 //
				if (m_isImportTag)
				{
					for (auto&item : m_importItem)
					{
						if (item->m_itemNum == m_importCount)
						{
							// 마지막 아이템 네임인 닫기를 만나면 카운트를 세지 않도록 해준다.
							if (item->m_itemNum == 0)
								temp = item->m_ItemName;

							if (item->m_ItemName != temp)
							{
								m_importCount--;
								break;
							}
						}
					}
				}

				else if (m_isPokeBallTag)
				{
					for (auto&item : m_pockeBallItem)
					{
						if (item->m_itemNum == m_pokeBallCount)
						{
							if (item->m_itemNum == 0)
								temp = item->m_ItemName;
							if (item->m_ItemName != temp)
							{
								m_pokeBallCount--;
								break;
							}
						}
					}
				}
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
	std::string descrip;
	std::string multiPly;

	if (isItemDelete)
	{
		count = 0;
		itemNum = 0;
		m_itemInit = false;
		itemTagInit();
		isItemDelete = false;
	}

	// show text 선언 //
	for (auto&HealPotion : m_potionItem)
	{
		str = HealPotion->getItemName();
		insertNum =  HealPotion->getCount();
		multiPly = "x";

		// potion name show
		UTIL::PrintText(hdc, str.c_str(), "소야바른9",
			HealPotion->getRect().left + 20, HealPotion->getRect().top + 30, 40, RGB(0, 0, 0), true);
		
		// count name show //
		if (HealPotion->m_ItemName != "닫기")
		UTIL::PrintText(hdc, std::to_string(insertNum).c_str(), "소야바른9",
			HealPotion->getRect().left + 500, HealPotion->getRect().top + 30, 40, RGB(0, 0, 0), true);
		
		// description text show //
		if (HealPotion->m_ItemName != "닫기")
		{
		UTIL::PrintText(hdc, multiPly.c_str(), "소야바른9",
			HealPotion->getRect().left + 400, HealPotion->getRect().top + 30, 40, RGB(0, 0, 0), true);
		}
	}

	for (auto& item : m_potionItem) {
		if (item->m_itemNum == m_itemCount ) {

			UTIL::PrintText(hdc, item->getDescript().c_str(), "소야바른9", 
			WINSIZEX / 2 - 300, WINSIZEY - 130, 40, RGB(255, 255, 255), true);

			item->render(hdc);	
			//m_currentArrow->render(hdc, 100, 100);
			m_currentArrow->render(hdc, 350, 30 + (m_itemCount * 80));
	
			//코드는 다음과 같이 짜시오...
			if (item->m_ItemName == "닫기")
			{
				if(KEYMANAGER->isOnceKeyDown(P1_Z))
				m_isCloseInven = true;
			}
		}
	}
}

void Inventory::importRender(HDC hdc)
{
	if (isItemDelete)
	{
		m_importPlaceCount = 0;
		m_importNum = 0;
		ImportTagInit();
		m_isImportInit = false;
		isItemDelete = false;
	}
		ImportTagInit();
	
	// show text 선언 //
	std::string str;
	int count;
	std::string descrip;
	std::string multiPly;
	std::string close;

	// show text 선언 //

	for (auto&importItem : m_importItem)
	{
		str = importItem->getItemName();
		count = importItem->getCount();
		multiPly = "x";

		// potion name show
		if(importItem->m_ItemName != "임폴트닫기")
		UTIL::PrintText(hdc, str.c_str(), "소야바른9",
			importItem->getRect().left + 20, importItem->getRect().top + 30, 40, RGB(0, 0, 0), true);
		else
		{
		 close = "닫기";
		 UTIL::PrintText(hdc, close.c_str(), "소야바른9",
			 importItem->getRect().left + 20, importItem->getRect().top + 30, 40, RGB(0, 0, 0), true);
		}

		// count name show //
		if (importItem->m_ItemName != "임폴트닫기")
		UTIL::PrintText(hdc, std::to_string(count).c_str(), "소야바른9",
			importItem->getRect().left + 500, importItem->getRect().top + 30, 40, RGB(0, 0, 0), true);


		// description text show //
		if (importItem->m_ItemName != "임폴트닫기")
		{
		UTIL::PrintText(hdc, multiPly.c_str(), "소야바른9",
			importItem->getRect().left + 400, importItem->getRect().top + 30, 40, RGB(0, 0, 0), true);
		}

	}

	for (auto& item : m_importItem) {
		if (item->m_itemNum == m_importCount) {

			UTIL::PrintText(hdc, item->getDescript().c_str(), "소야바른9",
				WINSIZEX / 2 - 300, WINSIZEY - 130, 40, RGB(255, 255, 255), true);

			//코드는 다음과 같이 짜시오...
			item->render(hdc);
			m_currentArrow->render(hdc, 350, 30 + (m_importCount * 80));

			if (item->m_ItemName == "임폴트닫기")
			{
				if (KEYMANAGER->isOnceKeyDown(P1_Z))
					m_isCloseInven = true;
				//m_itemCount  = 0;
			}
		}
	}
}

void Inventory::pokeBallRender(HDC hdc)
{
	if (isItemDelete)
	{
		m_pokePlaceCount = 0;
		m_pokeBallNum = 0;
		pocketBallTagInit();
		m_isPokeBallInit = false;
		isItemDelete = false;
	}

	pocketBallTagInit();
	 
	// show text 선언 //
	std::string str;
	int count;
	std::string descrip;
	std::string multiPly;
	std::string close;

	// show text 선언 //

	for (auto&pokeBallItem : m_pockeBallItem)
	{
		str = pokeBallItem->getItemName();
		count = pokeBallItem->getCount();
		multiPly = "x";

		// potion name show
		if (pokeBallItem->m_ItemName != "몬스터볼닫기")
			UTIL::PrintText(hdc, str.c_str(), "소야바른9",
				pokeBallItem->getRect().left + 20, pokeBallItem->getRect().top + 30, 40, RGB(0, 0, 0), true);
		else
		{
			close = "닫기";
			UTIL::PrintText(hdc, close.c_str(), "소야바른9",
				pokeBallItem->getRect().left + 20, pokeBallItem->getRect().top + 30, 40, RGB(0, 0, 0), true);
		}

		// count name show //
		if (pokeBallItem->m_ItemName != "몬스터볼닫기")
			UTIL::PrintText(hdc, std::to_string(count).c_str(), "소야바른9",
				pokeBallItem->getRect().left + 500, pokeBallItem->getRect().top + 30, 40, RGB(0, 0, 0), true);


		// description text show //
		if (pokeBallItem->m_ItemName != "몬스터볼닫기")
		{
			UTIL::PrintText(hdc, multiPly.c_str(), "소야바른9",
			pokeBallItem->getRect().left + 400, pokeBallItem->getRect().top + 30, 40, RGB(0, 0, 0), true);
		}
	}

	for (auto& item : m_pockeBallItem) {
		if (item->m_itemNum == m_pokeBallCount) {

			UTIL::PrintText(hdc, item->getDescript().c_str(), "소야바른9",
				WINSIZEX / 2 - 300, WINSIZEY - 130, 40, RGB(255, 255, 255), true);

			item->render(hdc);
			m_currentArrow->render(hdc, 350, 30 + (m_pokeBallCount * 80));

			if (item->m_ItemName == "몬스터볼닫기")
			{
				if (KEYMANAGER->isOnceKeyDown(P1_Z))
					m_isCloseInven = true;
				//m_itemCount  = 0;
			}
		}
	}
}

// 아이템 순서대로 위치 잡고 랜더 해주기 //
void Inventory::itemTagInit()
{
	count = 0;
	for (auto&item : m_potionItem)
	{    // Item을 erase하게 될경우 다시 RECT값을 초기화 해준후 자리를 재배치 해준다.
		if (isItemDelete)
		{
			item->m_iRect.left		= 412;
			item->m_iRect.top		= 50;
			item->m_iRect.right		= 812;
			item->m_iRect.bottom	= 130;
		}
		
		if (!m_itemInit)
		{
			item->m_iRect.top = item->getRect().top + (count * 80);
			item->m_iRect.bottom = item->getRect().bottom + (count * 80);
			item->setRect(item->m_iRect);
			item->m_itemNum = itemNum;
			count++;
			itemNum++;

			if (item->m_ItemName == "닫기")
			m_itemInit = true;
		}
	}
}

void Inventory::ImportTagInit()
{
	for (auto&item : m_importItem)
	{
		if (isItemDelete)
		{
			item->m_iRect.left = 412;
			item->m_iRect.top = 50;
			item->m_iRect.right = 812;
			item->m_iRect.bottom = 130;
		}
		if (!m_isImportInit)
		{
			item->m_iRect.top = item->getRect().top + (m_importPlaceCount * 80);
			item->m_iRect.bottom = item->getRect().bottom + (m_importPlaceCount * 80);
			item->setRect(item->m_iRect);
			item->m_itemNum = m_importNum;
			m_importPlaceCount++;
			m_importNum++;

			if (item->m_ItemName == "임폴트닫기")
				m_isImportInit = true;
		}
	}
}

void Inventory::pocketBallTagInit()
{
	for (auto&item : m_pockeBallItem)
	{
		if (isItemDelete)
		{
			item->m_iRect.left = 412;
			item->m_iRect.top = 50;
			item->m_iRect.right = 812;
			item->m_iRect.bottom = 130;
		}
		if (!m_isPokeBallInit)
		{
			item->m_iRect.top = item->getRect().top + (m_pokePlaceCount * 80);
			item->m_iRect.bottom = item->getRect().bottom + (m_pokePlaceCount * 80);
			item->setRect(item->m_iRect);
			item->m_itemNum = m_pokeBallNum;
			m_pokePlaceCount++;
			m_pokeBallNum++;

			if (item->m_ItemName == "몬스터볼닫기")
				m_isPokeBallInit = true;
		}
	}
}

void Inventory::sellItem()
{
	

}


