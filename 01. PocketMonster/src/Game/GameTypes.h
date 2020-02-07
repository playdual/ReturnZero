#pragma once
//게임 내에서 쓰이는 Enum과 구조체 등을 정의 합니다.

enum class TileType
{
	TileTypeFloor,
	TileTypeHouse,
	TileTypeBush,
	TileTypeTree,
	TileTypeOutRange,
	TileTypeNone
};

#define TILE_WIDTH 100
#define TILE_HEIGHT 100

enum class ItemType
{
	ItemTypePotion= 0,			 // 회복템
	ITemTypeStatePotion,		 // stateHealPotion
	ItemTypeBall,				 // 포켓몬볼
	ItemTypeImportant,		     // 중요한 아이템??
	ItemTypeSkillMachine,		 // 스킬 머신
	ItemTypeEquipable,			 // 물건 장착
	ItemTypeAbilityPotion,		 // 능력 향상 포션
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
};
