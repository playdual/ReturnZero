#include "stdafx.h"
#include "ItemManager.h"
#include "SystemManager/ImageManager.h"
#include "Game/GameObject/Items/Potion.h"

// 싱글톤을 할때는 cpp 파일에 적어줘야 한다.
DEFINITION_SINGLE(ItemManager)
ItemManager::ItemManager(){}
ItemManager::~ItemManager() {}
// 싱글톤을 할때는 cpp 파일에 적어줘야 한다.

bool ItemManager::init()
{
	addPotionItem("초급 Hp포션", WINSIZEX / 2, 100, 400, 80, "초급 Hp포션", 3, 50, " 포켓몬의 체력을 30만큼 회복 시켜준다.", 30, 0);
	addPotionItem("초급 Powe	rUp 포션", WINSIZEX / 2, 100, 400, 80, "초급 PowerUp 포션", 3, 50, " 포켓몬의 공격력을 5만큼 올려 준다.", 0, 5);
	

	return true;
}

void ItemManager::addPotionItem(std::string _itemKey,/* char* _imageName,*/ int _x, int _y, int _imageW, int _imageH, 
	std::string _itemName, int _count, int _price, std::string _descript, int _healHp, int _hitDamage)
{
	std::shared_ptr<Item> temp = std::make_shared<Potion>(
		ItemType::ItemTypePotion, UTIL::IRectMake(_x, _y , _imageW, _imageH),
		_itemName, _count, _price, _descript, _healHp, _hitDamage);

	m_ItemList.insert(std::make_pair(_itemKey, temp));
}

//void ItemManager::addPokemonBallItem(std::string _itemKey, int _x, int _y, int _imageW, int _imageH, std::string _itemName, int _count, int _price, std::string _descript, int _random)
//{
//	/*std::shared_ptr<Item> temp = std::make_shared<Potion>(
//		ItemType::ItemTypePotion, UTIL::IRectMake(_x, _y, _imageW, _imageH),
//		_itemName, _count, _price, _descript,_random);
//
//	m_ItemList.insert(std::make_pair(_itemKey, temp));*/
//}

std::shared_ptr<Item> ItemManager::findItem(std::string _itemKey)
{
	auto& ret = m_ItemList.find(_itemKey);
	if (ret == m_ItemList.end())
		return nullptr;
	return ret->second;
}                       
