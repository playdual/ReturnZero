#pragma once
//寃뚯엫 ?댁뿉???곗씠??Enum怨?援ъ“泥??깆쓣 ?뺤쓽 ?⑸땲??
#define PLAYER_OFFSETY -25
#define TILE_WIDTH 75
#define TILE_HEIGHT 75


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

PocketSkill tackleProto("몸통박치기", 25, 25, 20, 100, SkillType::SkillAttibuteNormal, SkillClassify::SkillTypeNormal);
PocketSkill scratchProto("할퀴기", 15, 15, 40, 100, SkillType::SkillAttibuteNormal, SkillClassify::SkillTypeNormal);
PocketSkill quickAttackProto("전광석화", 20, 20, 45, 90, SkillType::SkillAttibuteNormal, SkillClassify::SkillTypeNormal);
PocketSkill megaPunchProto("메가톤펀치", 5, 5, 85, 80, SkillType::SkillAttibuteNormal, SkillClassify::SkillTypeNormal);

PocketSkill emberProto("불꽃세례", 15, 15, 50, 90, SkillType::SkillAttibuteFire, SkillClassify::SkillTypeSpecial);
PocketSkill flameThrowerProto("화염방사", 10, 10, 65, 80, SkillType::SkillAttibuteFire, SkillClassify::SkillTypeNormal);
PocketSkill fireBlastProto("불대문자", 5, 5, 100, 70, SkillType::SkillAttibuteFire, SkillClassify::SkillTypeSpecial);

PocketSkill waterSaluteProto("물대포", 15, 15, 50, 90, SkillType::SkillAttibuteWater, SkillClassify::SkillTypeSpecial);
PocketSkill brineProto("소금물", 10, 10, 65, 80, SkillType::SkillAttibuteWater, SkillClassify::SkillTypeSpecial);
PocketSkill hydroPumpProto("하이드로펌프", 5, 5, 100, 70, SkillType::SkillAttibuteWater, SkillClassify::SkillTypeNormal);

PocketSkill vineWhipProto("덩쿨채찍", 15, 15, 50, 90, SkillType::SkillAttibuteGrass, SkillClassify::SkillTypeNormal);
PocketSkill razorLeafProto("잎날가르기", 10, 10, 65, 80, SkillType::SkillAttibuteGrass, SkillClassify::SkillTypeNormal);
PocketSkill solarBeamProto("솔라빔", 5, 5, 100, 60, SkillType::SkillAttibuteGrass, SkillClassify::SkillTypeSpecial);


PocketSkill thunderWaveProto("전기자석파", 15, 15, 50, 90, SkillType::SkillAttibuteElectric, SkillClassify::SkillTypeSpecial);
PocketSkill thunderboltProto("십만볼트", 10, 10, 70, 80, SkillType::SkillAttibuteElectric, SkillClassify::SkillTypeSpecial);
PocketSkill thunderProto("번개", 5, 5, 110, 70, SkillType::SkillAttibuteElectric, SkillClassify::SkillTypeNormal);


PocketSkill wingAttackProto("날개치기", 15, 15, 50, 90, SkillType::SkillAttibuteFly, SkillClassify::SkillTypeNormal);
PocketSkill airSlashProto("에어슬래시", 10, 10, 60, 85, SkillType::SkillAttibuteFly, SkillClassify::SkillTypeNormal);
PocketSkill hurricaneProto("폭풍", 5, 5, 110, 70, SkillType::SkillAttibuteFly, SkillClassify::SkillTypeSpecial);


