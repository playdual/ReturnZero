#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include "ItemManager.h"
#include "Common/SystemManagers.h"
#include "Game/GameObject/Items/Potion.h"
#include "Game/GameObject/Items/MonsterBall.h"
#include "Game/GameObject/Items/StateHeal.h"
#include "Game/GameObject/Items/Nutrient.h"
#include "Game/GameObject/Items/SkillMachine.h"
#include "Game/GameObject/Items/Close.h"
#include "Game/GameObject/Items/ImportItem.h"

// 싱글톤을 할때는 cpp 파일에 적어줘야 한다.
DEFINITION_SINGLE(ItemManager)

// 싱글톤을 할때는 cpp 파일에 적어줘야 한다.
DEFINITION_SINGLE(ItemManager)

ItemManager::ItemManager() {}
ItemManager::~ItemManager() {}
// 싱글톤을 할때는 cpp 파일에 적어줘야 한다.
using namespace std;


bool ItemManager::init()
{
	itemTextInit();

	for (int i = 0; i < m_itemCount; i++)
	{
		switch (itemPotion.itemKind[i])
		{
		case EXIT :
			addClose(itemPotion.name[i], itemPotion.imageFileName[i].c_str(), WINSIZEX / 2 - 100, itemPotion.rectY[i],
				itemPotion.width[i], itemPotion.height[i], itemPotion.name[i],
				itemPotion.count[i], itemPotion.price[i], itemPotion.description[i]);
			break;

		case BALL:
			addPokemonBallItem(itemPotion.name[i], itemPotion.imageFileName[i].c_str(),WINSIZEX / 2 - 100, itemPotion.rectY[i],
				itemPotion.width[i], itemPotion.height[i], itemPotion.name[i],
				itemPotion.count[i], itemPotion.price[i], itemPotion.description[i],itemPotion.random[i]);
			break;

		case HEALPOTION:
			addPotionItem(itemPotion.name[i], itemPotion.imageFileName[i].c_str(), WINSIZEX / 2 - 100, itemPotion.rectY[i],
				itemPotion.width[i], itemPotion.height[i], itemPotion.name[i],
				itemPotion.count[i], itemPotion.price[i], itemPotion.description[i], itemPotion.healHp[i], itemPotion.damage[i]);
			break;

		case STATEPOTION:
			addStateHeal(itemPotion.name[i], WINSIZEX / 2 - 100, itemPotion.rectY[i],
				itemPotion.width[i], itemPotion.height[i], itemPotion.name[i],
				itemPotion.count[i], itemPotion.price[i], itemPotion.description[i]);
			break;

		case NUTRIENT:
			addNutrient(itemPotion.name[i], WINSIZEX / 2 - 100, itemPotion.rectY[i],
				itemPotion.width[i], itemPotion.height[i], itemPotion.name[i],
				itemPotion.count[i], itemPotion.price[i], itemPotion.description[i], itemPotion.addAbility[i]);
			break;

			//std::string _itemKey, PockemonAttibute _pokemonAttibute, int _x, int _y,
		case SKILLMACHINE:
			addSkillMachine(itemPotion.name[i], itemPotion.atibuteKind[i], WINSIZEX / 2, itemPotion.rectY[i],
				itemPotion.width[i], itemPotion.height[i], itemPotion.name[i],
				itemPotion.count[i], itemPotion.price[i], itemPotion.description[i], itemPotion.damage[i]);
			break;

		case IMPORTITEM:
			addImportItem(itemPotion.name[i], itemPotion.imageFileName[i].c_str(), WINSIZEX / 2 - 100, itemPotion.rectY[i],
				itemPotion.width[i], itemPotion.height[i], itemPotion.name[i],
				itemPotion.count[i], itemPotion.price[i], itemPotion.description[i]);
			break;

		default:
			break;
		}
	}

	//addPotionItem("초급 Hp포션", WINSIZEX / 2, 100, 400, 80, "초급 Hp포션", 3, 50, " 포켓몬의 체력을 30만큼 회복 시켜준다.", 30, 0);
	//addPotionItem("초급 Powe	rUp 포션", WINSIZEX / 2, 100, 400, 80, "초급 PowerUp 포션", 3, 50, " 포켓몬의 공격력을 5만큼 올려 준다.", 0, 5);

	return true;
}
void ItemManager::addClose(std::string _itemKey,const char * _imageName, int _x, int _y, int _imageW, int _imageH,
	std::string _itemName, int _count, int _price, std::string _descript)
{
	if (_imageName != NULL)
		IMAGEMANAGER->addImage(_itemKey, _imageName, 100, 100);

	std::shared_ptr<Item> temp = std::make_shared<Close>(
		ItemType::ItemTypeClose,
		IMAGEMANAGER->findImage(_itemKey),
		UTIL::IRectMake(_x, _y, _imageW, _imageH),
		_itemName, _count, _price, _descript);
	
	m_ItemList.insert(std::make_pair(_itemKey, temp));
}
void ItemManager::addPokemonBallItem(std::string _itemKey, const char * _imageName, int _x, int _y, int _imageW, int _imageH,
	std::string _itemName, int _count, int _price, std::string _descript, int _random)
{
	if (_imageName != NULL)
		IMAGEMANAGER->addImage(_itemKey, _imageName, 100, 100);

	std::shared_ptr<Item> temp = std::make_shared<MonsterBall>(
		ItemType::ItemTypeBall,
		IMAGEMANAGER->findImage(_itemKey),
		UTIL::IRectMake(_x, _y, _imageW, _imageH),
		_itemName, _count, _price, _descript, _random);

	m_ItemList.insert(std::make_pair(_itemKey, temp));
}

void ItemManager::addPotionItem(std::string _itemKey, const char* _imageName, int _x, int _y, int _imageW, int _imageH,
	std::string _itemName, int _count, int _price, std::string _descript, int _healHp, int _hitDamage)
{
	if (_imageName != NULL)
		IMAGEMANAGER->addImage(_itemKey, _imageName, 100, 100);

	std::shared_ptr<Item> temp = std::make_shared<Potion>(
		ItemType::ItemTypePotion,
		IMAGEMANAGER->findImage(_itemKey),
		UTIL::IRectMake(_x, _y, _imageW, _imageH),
		_itemName, _count, _price, _descript, _healHp, _hitDamage);

	m_ItemList.insert(std::make_pair(_itemKey, temp));
}

void ItemManager::addStateHeal(std::string _itemKey, int _x, int _y, int _imageW, int _imageH, std::string _itemName, int _count, int _price, std::string _descript)
{
	//나중에 작업하시오,,
	/*std::shared_ptr<Item> temp = std::make_shared<StateHeal>(
		ItemType::ITemTypeStatePotion, UTIL::IRectMake(_x, _y, _imageW, _imageH),
		_itemName, _count, _price, _descript);

	m_ItemList.insert(std::make_pair(_itemKey, temp));*/
}

void ItemManager::addNutrient(std::string _itemKey, int _x, int _y, int _imageW, int _imageH, std::string _itemName, int _count, int _price, std::string _descript, int _addAbility)
{
	//나중에 작업하시오,,
	/*std::shared_ptr<Item> temp = std::make_shared<Nutrient>(
		ItemType::ItemTypeAbilityPotion, UTIL::IRectMake(_x, _y, _imageW, _imageH),
		_itemName, _count, _price, _descript, _addAbility);

	m_ItemList.insert(std::make_pair(_itemKey, temp));*/
}

void ItemManager::addSkillMachine(std::string _itemKey, PockemonAttibute _pokemonAttibute, int _x, int _y, int _imageW, int _imageH, std::string _itemName, int _count, int _price, std::string _descript, int _damage)
{
	//나중에 작업하시오,,
	/*PockemonAttibute pockeAttibue;

	std::shared_ptr<Item> temp = std::make_shared<SkillMachine>(
		ItemType::ItemTypeSkillMachine,
		pockeAttibue = _pokemonAttibute,
		UTIL::IRectMake(_x, _y, _imageW, _imageH),
		_itemName, _count, _price, _descript, _damage);

	m_ItemList.insert(std::make_pair(_itemKey, temp));*/
}

void ItemManager::addImportItem(std::string _itemKey, const char * _imageName, int _x, int _y, int _imageW, int _imageH, std::string _itemName, int _count, int _price, std::string _descript)
{
	if (_imageName != NULL)
		IMAGEMANAGER->addImage(_itemKey, _imageName, 100, 100);

	std::shared_ptr<Item> temp = std::make_shared<ImportItem>(
		ItemType::ItemTypeImportant,
		IMAGEMANAGER->findImage(_itemKey),
		UTIL::IRectMake(_x, _y, _imageW, _imageH),
		_itemName, _count, _price, _descript);

	m_ItemList.insert(std::make_pair(_itemKey, temp));
}

std::shared_ptr<Item> ItemManager::findItem(std::string _itemKey)
{
	auto& ret = m_ItemList.find(_itemKey);
	if (ret == m_ItemList.end())
		return nullptr;
	return ret->second;
}
//[ itemTextFile init ]=================================

void ItemManager::itemTextInit()
{
	std::string str;
	std::string inputStr;
	KINDCOUNT kindCount;
	kindCount = ITEMKIND;

	ifstream readFile;
	readFile.open("Text/itemList.txt");

	if (readFile.is_open())
	{
		while (!readFile.eof())
		{
			getline(readFile, str);
			readFile.imbue(std::locale("kor"));
			inputStr += str;
			inputStr += "\n";
		}
		readFile.close();
	}
	char myInputStr[10000];
	strcpy(myInputStr, inputStr.c_str());

	char *ptr = strtok(myInputStr, "#");

	int count = 0;

	while (*ptr != '\n')
	{
		char spaceBar = *ptr;
 		count++;

		for (int i = 0; i < m_itemCount; i++)
		{
			if (spaceBar == '\n')
			{
				count = 0;
				ptr = strtok(NULL, "#");
			}
			switch (kindCount)
			{
			case ITEMKIND:
				itemPotion.itemKind[i] = atoi(ptr);
				ptr = strtok(NULL, "#");

			case NAME:
				itemPotion.name[i] = ptr;
				ptr = strtok(NULL, "#");

 			if (itemPotion.itemKind[i] == 1 || itemPotion.itemKind[i] == 3 
 				|| itemPotion.itemKind[i] == 2 || itemPotion.itemKind[i] == 7)
			{
			case IMAGES:
				itemPotion.imageFileName[i] = ptr;
				ptr = strtok(NULL, "#");
			}

			if (itemPotion.itemKind[i] == 6)
			{
			case ATIBUTEKIND:
				itemPotion.atibuteKind[i] = (PockemonAttibute)atoi(ptr);
				ptr = strtok(NULL, "#");
			}

			case RECTX:
				itemPotion.rectX[i] = atoi(ptr);
				ptr = strtok(NULL, "#");

			case RECTY:
				itemPotion.rectY[i] = atoi(ptr);
				ptr = strtok(NULL, "#");

			case WIDTH:
				itemPotion.width[i] = atoi(ptr);
				ptr = strtok(NULL, "#");

			case HEIGHT:
				itemPotion.height[i] = atoi(ptr);
				ptr = strtok(NULL, "#");

			if (itemPotion.itemKind[i] != 6)
			{
			    case COUNT:
			    itemPotion.count[i] = atoi(ptr);
			    ptr = strtok(NULL, "#");
			}

			case PRICE:
				itemPotion.price[i] = atoi(ptr);
				ptr = strtok(NULL, "#");

			case DESCRIPTION:
				itemPotion.description[i] = ptr;
				ptr = strtok(NULL, "#");

			if (itemPotion.itemKind[i] == 3)
			{
			case HEALHP:
				itemPotion.healHp[i] = atoi(ptr);
				ptr = strtok(NULL, "#");
			}

			if (itemPotion.itemKind[i] == 3 || itemPotion.itemKind[i] == 6)
			{
			case DAMAGE:
				itemPotion.damage[i] = atoi(ptr);
				ptr = strtok(NULL, "#");
			}

			if (itemPotion.itemKind[i] == 5)
			{
			case ADDABILITY:
				itemPotion.addAbility[i] = atoi(ptr);
				ptr = strtok(NULL, "#");

			}

			if (itemPotion.itemKind[i] == 2)
			{
			case RANDOM :
				itemPotion.random[i] = atoi(ptr);
				ptr = strtok(NULL, "#");
			}
			default:
				count = 0;
				//cout << endl;
			}
		}
		//ptr = strtok(NULL, "#");
	}
}
