#pragma once

enum class ITEM_TYPE
{
	ITEM_TYPE_RECOVERY = 0,			 // 회복템
	ITEM_TYPE_BALL,				     // 포켓몬볼
	ITEM_TYPE_IMPORTANT,		     // 중요한 아이템??
	ITEM_TYPE_SKILL_MACHINE,		     // 스킬 머신
	ITEM_TPYE_EQUIPABLE,			 // 물건 장착
	ITEM_TYPE_ABILITY_POTION,		 // 능력 향상 포션
	DEFAULT
};


enum class POCKETMON_ATTRIBUTE
{
	POCKETMON_ATTRIBUTE_FIRE,
	POCKETMON_ATTRIBUTE_STONE,
	POCKETMON_ATTRIBUTE_WATER,
	POCKETMON_ATTRIBUTE_GRASS
};

enum class SKILL
{
	SCRACH ,                                                                                                                                                                                                                                                                                                                                                                                                                                 
	HOWL ,
	FIRE ,
	SKILL_MACHINE_1 ,
	SKILL_MACHINE_2
};