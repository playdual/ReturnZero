#include "stdafx.h"
#include "ItemManager.h"
#include "SystemManager/ImageManager.h"
#include "Game/GameObject/Items/Potion.h"

// �̱����� �Ҷ��� cpp ���Ͽ� ������� �Ѵ�.
DEFINITION_SINGLE(ItemManager)
ItemManager::ItemManager(){}
ItemManager::~ItemManager() {}
// �̱����� �Ҷ��� cpp ���Ͽ� ������� �Ѵ�.

bool ItemManager::init()
{
	addPotionItem("�ʱ� Hp����", WINSIZEX / 2, 100, 400, 80, "�ʱ� Hp����", 3, 50, " ���ϸ��� ü���� 30��ŭ ȸ�� �����ش�.", 30, 0);
	addPotionItem("�ʱ� Powe	rUp ����", WINSIZEX / 2, 100, 400, 80, "�ʱ� PowerUp ����", 3, 50, " ���ϸ��� ���ݷ��� 5��ŭ �÷� �ش�.", 0, 5);
	

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
