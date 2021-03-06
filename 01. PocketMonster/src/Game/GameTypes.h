﻿#pragma once
//寃뚯엫 ?댁뿉???곗씠??Enum怨?援ъ“泥??깆쓣 ?뺤쓽 ?⑸땲??
#define PLAYER_OFFSETY -27
#define TILE_WIDTH 60
#define TILE_HEIGHT 60

#define INFO_ITEM		1
#define INFO_CHANGEPOKE 2
#define INFO_USEDITEM	3
#define INFO_FROMBATTLE 4

enum class TileType
{
	TileTypeFloor,
	TileTypeHouse,
	TileTypeBush,
	TileTypeTree,
	TileTypeNextMap,
	TileTypeOutRange,
	TileTypeObject,
	TileTypeNone
};
enum class SkillType
{
	SkillAttibuteFire,
	SkillAttibuteStone,
	SkillAttibuteWater,
	SkillAttibuteGrass,
	SkillAttibuteFly,
	SkillAttibuteElectric,
	SkillAttibuteNormal	
};

enum class SkillClassify
{
	SkillTypeNormal,
	SkillTypeSpecial
};

enum class ItemType
{
	ItemTypeClose = 0,
	ItemTypePotion,				 // ?뚮났??
	ITemTypeStatePotion,		 // stateHealPotion
	ItemTypeBall,				 // ?ъ폆紐щ낵
	ItemTypeImportant,		     // 以묒슂???꾩씠???
	ItemTypeSkillMachine,		 // ?ㅽ궗 癒몄떊
	ItemTypeEquipable,			 // 臾쇨굔 ?μ갑
	ItemTypeAbilityPotion,		 // ?λ젰 ?μ긽 ?ъ뀡
	ItemTypeNone
};

enum Direction
{
	DirectionDown,
	DirectionUp,
	DirectionLeft,
	DirectionRight
};

enum class PockemonAttibute
{
	PockemonAttibuteFire,
	PockemonAttibuteStone,
	PockemonAttibuteWater,
	PockemonAttibuteGrass,
	PockemonAttibuteFly,
	PockemonAttibuteElectric,
	PockemonAttibuteNormal
	
};

enum class Skill
{
	Nomal,                                                                                                                                                                                                                                                                                                                                                                                                                                 
	Skill1,
	Skill2,
	SkillMachine_1 ,
	SkillMachine_2
};

enum KINDCOUNT
{
	ITEMKIND = 1, NAME, IMAGES, RECTX, RECTY, WIDTH, HEIGHT,
	COUNT, PRICE, DESCRIPTION, HEALHP, DAMAGE, ADDABILITY, ATIBUTEKIND ,RANDOM , REVOLUTION
};
enum ITEMCOUNT
{
	EXIT = 1, BALL , HEALPOTION, STATEPOTION, NUTRIENT, SKILLMACHINE ,IMPORTITEM
};

struct itemText {
	int					  itemKind[100];	//1
	std::string				  name[100];	//2
	std::string		 imageFileName[800];	// images
	int						 rectX[100];	//3
	int						 rectY[100];	//4
	int						 width[100];	//5	
	int						height[100];	//6
	int						 count[100];	//7
	int					  	 price[100];	//8
	std::string		   description[300];	//9
	int						healHp[100];	//10
	int						damage[100];	//11
	int					addAbility[100];	//12
	PockemonAttibute   atibuteKind[100];	//13
	int			 poketCatchPercent[100];	//14
	bool				revolution[100];	//15
};

struct PocketSkill 
{
	std::string name;				//이름
	int maxpp;						//최대 스킬 사용횟수
	int currentpp;					//현재 스킬 사용횟수
	int power;						//위력
	int hit;						//명중률
	SkillType skilltype;			//스킬속성
	SkillClassify skillclassify;	//물공/특공
	PocketSkill(std::string _name, int _maxpp, int _currentpp, int _power,
		int _hit, SkillType _skillType, SkillClassify _skillClassify)
	{
		name = _name;
		maxpp = _maxpp;
		currentpp = _currentpp;
		power = _power;
		hit = _hit;
		skilltype = _skillType;
		skillclassify = _skillClassify;
	}
};

struct ItemInfo
{
	int				InfoType = INFO_ITEM;
	std::string		name;
	int				healPoint;
	int				catchRatio;
	ItemInfo() 
		: name("")
	{}
};
struct ChangePocketInfo
{
	int	infoType = INFO_CHANGEPOKE;
	bool isChanged;
};
struct UsedItemInfo
{
	int infoType = INFO_USEDITEM;
	bool isUsed;
	int poketIndex;
	std::string itemKey;
};

struct ChangeSceneFromBattle
{
	int infoType = INFO_FROMBATTLE;
};

struct MenuBar {
	std::string menuName;
	int menuNum;
	MenuBar(std::string _name, int _num) 
		: menuName(_name), menuNum(_num)
	{}
};

// 인벤씬 타입 //
enum INVENSCENETYPE
{
	ITEM = 0 , IMPORT , POKEBALL
};

enum class NPCEventType
{
	NPCShop,
	NPCPocketCenter,
	NPCNone
};

typedef std::vector<std::pair<std::wstring, std::wstring>> Senario;