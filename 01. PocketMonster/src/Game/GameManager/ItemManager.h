#pragma once
#include "Game/GameObject/Item.h"

class ItemManager
{
public:
	bool init();

public:
	void addPotionItem(std::string _itemKey,/* char* _imageName,*/ int _x , int _y ,int _imageW, int _imageH, 
		std::string _itemName, int _count , int _price, std::string _descript , int _healHp, int _hitDamage);

	//void addPokemonBallItem(std::string _itemKey,/* char* _imageName,*/ int _x, int _y, int _imageW, int _imageH,
	//	std::string _itemName, int _count, int _price, std::string _descript, int _random);

	std::shared_ptr<Item> findItem(std::string _itemKey);
	std::map<std::string ,std::shared_ptr<Item>> m_ItemList;
	
private:

private:
	DECLARE_SINGLE(ItemManager)
};
#define ITEMMANAGER ItemManager::GetInst()
