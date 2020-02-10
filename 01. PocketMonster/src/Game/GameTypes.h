#pragma once
//寃뚯엫 ?댁뿉???곗씠??Enum怨?援ъ“泥??깆쓣 ?뺤쓽 ?⑸땲??

enum class TileType
{
	TileTypeFloor,
	TileTypeHouse,
	TileTypeBush,
	TileTypeTree,
	TileTypeNextMap,
	TileTypeOutRange,
	TileTypeNone
};

#define TILE_WIDTH 100
#define TILE_HEIGHT 100

enum class ItemType
{
	ItemTypePotion= 0,			 // ?뚮났??
	ITemTypeStatePotion,		 // stateHealPotion
	ItemTypeBall,				 // ?ъ폆紐щ낵
	ItemTypeImportant,		     // 以묒슂???꾩씠???
	ItemTypeSkillMachine,		 // ?ㅽ궗 癒몄떊
	ItemTypeEquipable,			 // 臾쇨굔 ?μ갑
	ItemTypeAbilityPotion,		 // ?λ젰 ?μ긽 ?ъ뀡
};


enum class PockemonAttibute
{
	PockemonAttibuteFire,
	PockemonAttibuteStone,
	PockemonAttibuteWater,
	PockemonAttibuteGrass
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
	COUNT, PRICE, DESCRIPTION, HEALHP, DAMAGE, ADDABILITY, ATIBUTEKIND
};
enum ITEMCOUNT
{
	EXIT = 0, BALL , HEALPOTION, STATEPOTION, NUTRIENT, SKILLMACHINE
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
	std::string		   description[100];	//9
	int						healHp[100];	//10
	int						damage[100];	//11
	int					addAbility[100];	//12
	PockemonAttibute	atibuteKind[100];	//13
};
