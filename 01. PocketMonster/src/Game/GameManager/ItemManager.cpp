#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include "ItemManager.h"
#include "SystemManager/ImageManager.h"
#include "Game/GameObject/Items/Potion.h"
#include "Game/GameObject/Items/MonsterBall.h"
#include "Game/GameObject/Items/StateHeal.h"
#include "Game/GameObject/Items/Nutrient.h"
#include "Game/GameObject/Items/SkillMachine.h"


using namespace std;

enum KINDCOUNT
{
	ITEMKIND = 1, NAME, RECTX, RECTY, WIDTH, HEIGHT,
	COUNT, PRICE, DESCRIPTION, HEALHP, DAMAGE, ADDABILITY, ATIBUTEKIND
};
enum ITEMCOUNT
{
	BALL =1 , HEALPOTION , STATEPOTION , NUTRIENT, SKILLMACHINE
};

struct itemText {
	int					  itemKind[100];	//1
	std::string				  name[100];	//2
	int						 rectX[100];	//3
	int						 rectY[100];	//4
	int						 width[100];	//5	
	int						height[100];	//6
	int						 count[100];	//7
	int					  	 price[100];	//8
	std::string		   description[100];	//9
	int						healHp[100];	//10
	int						damage[100];	//11
	int					addAbility[100];	//12
	PockemonAttibute	atibuteKind[100];	//13
};

// ======= 전역 ======
itemText itemPotion;
int m_itemCount = 14;
// ======= 전역 ======

// 싱글톤을 할때는 cpp 파일에 적어줘야 한다.
DEFINITION_SINGLE(ItemManager)
ItemManager::ItemManager(){}
ItemManager::~ItemManager() {}
// 싱글톤을 할때는 cpp 파일에 적어줘야 한다.

bool ItemManager::init()
{
	itemTextInit();
	
	for (int i = 0; i < m_itemCount; i++)
	{
		switch (itemPotion.itemKind[i])
		{
		case BALL:
			addPokemonBallItem(itemPotion.name[i], WINSIZEX / 2, itemPotion.rectY[i],
			itemPotion.width[i], itemPotion.height[i], itemPotion.name[i],
			itemPotion.count[i], itemPotion.price[i], itemPotion.description[i] ,30);


		case HEALPOTION:
			addPotionItem(itemPotion.name[i], WINSIZEX / 2, itemPotion.rectY[i],
			itemPotion.width[i], itemPotion.height[i], itemPotion.name[i],
			itemPotion.count[i], itemPotion.price[i], itemPotion.description[i], itemPotion.healHp[i], itemPotion.damage[i]);
			break;

		case STATEPOTION:
			addStateHeal(itemPotion.name[i], WINSIZEX / 2, itemPotion.rectY[i],
			itemPotion.width[i], itemPotion.height[i], itemPotion.name[i],
			itemPotion.count[i], itemPotion.price[i], itemPotion.description[i]);
			break;


		case NUTRIENT:
			addNutrient(itemPotion.name[i], WINSIZEX / 2, itemPotion.rectY[i],
			itemPotion.width[i], itemPotion.height[i], itemPotion.name[i],
			itemPotion.count[i], itemPotion.price[i], itemPotion.description[i] , itemPotion.addAbility[i]);
			break;

			//std::string _itemKey, PockemonAttibute _pokemonAttibute, int _x, int _y,
		case SKILLMACHINE:
			addSkillMachine(itemPotion.name[i],itemPotion.atibuteKind[i], WINSIZEX / 2, itemPotion.rectY[i],
			itemPotion.width[i], itemPotion.height[i], itemPotion.name[i],
			itemPotion.count[i], itemPotion.price[i], itemPotion.description[i], itemPotion.damage[i]);
			break;



		default:
			break;
		}
	}

	//addPotionItem("초급 Hp포션", WINSIZEX / 2, 100, 400, 80, "초급 Hp포션", 3, 50, " 포켓몬의 체력을 30만큼 회복 시켜준다.", 30, 0);
	//addPotionItem("초급 Powe	rUp 포션", WINSIZEX / 2, 100, 400, 80, "초급 PowerUp 포션", 3, 50, " 포켓몬의 공격력을 5만큼 올려 준다.", 0, 5);
	
	return true;
}
 void ItemManager::addPokemonBallItem(std::string _itemKey, int _x, int _y, int _imageW, int _imageH, std::string _itemName, int _count, int _price, std::string _descript, int _random)
 {
 	std::shared_ptr<Item> temp = std::make_shared<MonsterBall>(
 		ItemType::ItemTypeBall, UTIL::IRectMake(_x, _y, _imageW, _imageH),
 		_itemName, _count, _price, _descript,_random);
 
 	m_ItemList.insert(std::make_pair(_itemKey, temp));
 }

void ItemManager::addPotionItem(std::string _itemKey,/* char* _imageName,*/ int _x, int _y, int _imageW, int _imageH, 
	std::string _itemName, int _count, int _price, std::string _descript, int _healHp, int _hitDamage)
{
	std::shared_ptr<Item> temp = std::make_shared<Potion>(
		ItemType::ItemTypePotion, UTIL::IRectMake(_x, _y , _imageW, _imageH),
		_itemName, _count, _price, _descript, _healHp, _hitDamage);

	m_ItemList.insert(std::make_pair(_itemKey, temp));
}

void ItemManager::addStateHeal(std::string _itemKey, int _x, int _y, int _imageW, int _imageH, std::string _itemName, int _count, int _price, std::string _descript)
{
	std::shared_ptr<Item> temp = std::make_shared<StateHeal>(
		ItemType::ITemTypeStatePotion, UTIL::IRectMake(_x, _y, _imageW, _imageH),
		_itemName, _count, _price , _descript);

	m_ItemList.insert(std::make_pair(_itemKey, temp));
}

void ItemManager::addNutrient(std::string _itemKey, int _x, int _y, int _imageW, int _imageH, std::string _itemName, int _count, int _price, std::string _descript, int _addAbility)
{
	std::shared_ptr<Item> temp = std::make_shared<Nutrient>(
		ItemType::ItemTypeAbilityPotion, UTIL::IRectMake(_x, _y, _imageW, _imageH),
		_itemName, _count, _price, _descript, _addAbility);

	m_ItemList.insert(std::make_pair(_itemKey, temp));
}

void ItemManager::addSkillMachine(std::string _itemKey, PockemonAttibute _pokemonAttibute, int _x, int _y, int _imageW, int _imageH, std::string _itemName, int _count, int _price, std::string _descript, int _damage)
{
	PockemonAttibute pockeAttibue;
	 
	std::shared_ptr<Item> temp = std::make_shared<SkillMachine>(
		ItemType::ItemTypeSkillMachine,
		pockeAttibue = _pokemonAttibute,
		UTIL::IRectMake(_x, _y, _imageW, _imageH),
		_itemName, _count, _price, _descript, _damage);

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
	char myInputStr[5000];
	strcpy(myInputStr, inputStr.c_str());
	//cout << myInputStr << endl;

	char *ptr = strtok(myInputStr, "#");
	int count = 0;

	while (ptr != NULL)
	{
		char spaceBar = *ptr;
		count++;

		for (int i = 0; i < 14; i++)
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
				cout << "ITEMKIND : " << itemPotion.itemKind[i] << endl;
				ptr = strtok(NULL, "#");

			case NAME:
				itemPotion.name[i] = ptr;
				cout << "NAME : " << itemPotion.name[i] << endl;
				ptr = strtok(NULL, "#");


			if (itemPotion.itemKind[i] == 5)
			{
			case ATIBUTEKIND:
				itemPotion.atibuteKind[i] = (PockemonAttibute)atoi(ptr);
				cout << "ATIBUTE : " << (int)itemPotion.atibuteKind[i] << endl;
				ptr = strtok(NULL, "#");
			}

			case RECTX:
				itemPotion.rectX[i] = atoi(ptr);
				cout << "RECTX : " << itemPotion.rectX[i] << endl;
				ptr = strtok(NULL, "#");

			case RECTY:
				itemPotion.rectY[i] = atoi(ptr);
				cout << "RECTY : " << itemPotion.rectY[i] << endl;
				ptr = strtok(NULL, "#");

			case WIDTH:
				itemPotion.width[i] = atoi(ptr);
				cout << "WIDTH : " << itemPotion.width[i] << endl;
				ptr = strtok(NULL, "#");

			case HEIGHT:
				itemPotion.height[i] = atoi(ptr);
				cout << "HEIGHT : " << itemPotion.height[i] << endl;
				ptr = strtok(NULL, "#");


			case COUNT:
				itemPotion.count[i] = atoi(ptr);
				cout << "COUNT : " << itemPotion.count[i] << endl;
				ptr = strtok(NULL, "#");


			case PRICE:
				itemPotion.price[i] = atoi(ptr);
				cout << "PRICE : " << itemPotion.price[i] << endl;
				ptr = strtok(NULL, "#");


			case DESCRIPTION:
				itemPotion.description[i] = ptr;
				cout << "DESCRIPTION : " << itemPotion.description[i] << endl;
				ptr = strtok(NULL, "#");

				if (itemPotion.itemKind[i] == 2)
				{
			case HEALHP:
				itemPotion.healHp[i] = atoi(ptr);
				cout << "HEALHP : " << itemPotion.healHp[i] << endl;
				ptr = strtok(NULL, "#");

				}

				if (itemPotion.itemKind[i] == 2 || itemPotion.itemKind[i] == 5)
				{
			case DAMAGE:
				itemPotion.damage[i] = atoi(ptr);
				cout << "DAMAGE : " << itemPotion.damage[i] << endl;
				ptr = strtok(NULL, "#");

				}

				if (itemPotion.itemKind[i] == 4)
				{
			case ADDABILITY:
				itemPotion.addAbility[i] = atoi(ptr);
				cout << "ADDABILITY : " << itemPotion.addAbility[i] << endl;
				ptr = strtok(NULL, "#");

				}
			default:
				count = 0;
				cout << endl;
			}
		}
		ptr = strtok(NULL, "#");
	}
}
