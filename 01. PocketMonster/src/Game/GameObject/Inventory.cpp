#include "stdafx.h"
#include "Inventory.h"
#include "Game/GameManager/ItemManager.h"
Inventory::Inventory()
{

}

Inventory::~Inventory()
{
}

bool Inventory::init()
{
	m_item.push_back(ITEMMANAGER->findItem("초급 Hp포션"));
	m_item.push_back(ITEMMANAGER->findItem("초급 PowerUp 포션"));

	return true;
}

void Inventory::update(float _deltaTime)
{

}

void Inventory::render(HDC hdc)
{
	
}

void Inventory::afterRender(HDC hdc)
{
}

void Inventory::debugRender(HDC hdc)
{
	//std::string str;
	//int count;

	//for (auto&HealPotion : m_item)
	//{
	//	str = HealPotion->getItemName();
	//	count =  HealPotion->getCount();
	//	UTIL::drawRect(hdc, HealPotion->getRect());
	//	// potion name show
	//	TextOut(hdc, HealPotion->getRect().left + 20, HealPotion->getRect().top + 30, str.c_str(), str.length());
	//	// count name show
	//	TextOut(hdc, HealPotion->getRect().left + 300, HealPotion->getRect().top + 30, std::to_string(count).c_str(), std::to_string(count).length());
	//}
}
