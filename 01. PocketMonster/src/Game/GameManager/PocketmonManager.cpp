
#include "stdafx.h"
#include "PocketmonManager.h"
#include "Common/SystemManagers.h"

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

DEFINITION_SINGLE(PocketmonManager)

PocketmonManager::PocketmonManager()
{
}

PocketmonManager::~PocketmonManager()
{
}


HRESULT PocketmonManager::init()
{
	IMAGEMANAGER->addImage("pailiFront", "Images/pocketmons/pailiFront.bmp", 60*3, 61*3, true, RGB(255, 0, 255));

	for (int i = 0; i < 5; i++)
	{
		PocketMon pocket;

		pocket.m_state = true;
		pocket.m_name = "파이리";
		pocket.m_customName = "영환파이리";
		pocket.gender = false;
		pocket.m_level = UTIL::GetRndIntFromTo(3,7);
		pocket.m_maxHp = UTIL::GetRndIntFromTo(26,35);
		pocket.m_currentHp = pocket.m_maxHp;
		pocket.m_atk = UTIL::GetRndIntFromTo(12,15);
		pocket.m_def = UTIL::GetRndIntFromTo(7, 9);
		pocket.m_specialAtk = UTIL::GetRndIntFromTo(15,19);
		pocket.m_specialDef = UTIL::GetRndIntFromTo(15,19);
		pocket.m_dex = UTIL::GetRndIntFromTo(17, 19);
		pocket.m_maxExp = UTIL::GetRndIntFromTo(742, 800);
		pocket.m_currentExp = 0;
		pocket.skill_1 = "불꽃세례";
		//pocket.skill_1force = 40;

		pocketmonVector.push_back(pocket);
	}

	
	return S_OK;
}

void PocketmonManager::release()
{
}

void PocketmonManager::update(float deltaTime)
{
}

void PocketmonManager::render(HDC hdc)
{
}

void PocketmonManager::afterRender(HDC hdc)
{
}

void PocketmonManager::debugRender(HDC hdc)
{
}

PocketMon PocketmonManager::getPocketmonInform()
{
	int i = UTIL::GetRndIntFromTo(0, pocketmonVector.size()-1);
	return pocketmonVector[i];
}

PocketMon PocketmonManager::genPocketMon(std::string _name, int level)
{
	if (_name == "파이리")
		return genCharmander(level);
	else if (_name == "이상해씨")
		return genBulbasaur(level);
	else if (_name == "꼬부기")
		return genSquirtle(level);
	else if (_name == "구구")
		return genPidgey(level);
	else if (_name == "피카츄")
		return genPikachu(level);
	else if (_name == "캐터피")
		return genCaterpie(level);
	else if (_name == "꼬렛")
		return genRattata(level);
	else if (_name == "식스테일")
		return genVulpix(level);
	else if (_name == "뚜벅초")
		return genOddish(level);
	else if (_name == "발챙이")
		return genPoliwag(level);
}

PocketMon PocketmonManager::genCharmander(int level)
{
	PocketMon pocket;
	pocket.m_name = "파이리";
	pocket.m_customName = "";
	pocket.m_level = level;
	pocket.m_maxHp = 20 + level * 6;
	pocket.m_currentHp = pocket.m_maxHp;
	pocket.m_maxExp = level * 20 + level * 2;
	pocket.m_currentExp = 0;
	pocket.m_wildExp = level * 10 + level * 1;
	pocket.m_atk = 5 + level * 2;
	pocket.m_specialAtk = 6 + level * 3;
	pocket.m_def = 3 + level * 2;
	pocket.m_specialDef = 4 + level * 2;
	pocket.m_Attribute = PockemonAttibute::PockemonAttibuteFire;
	pocket.m_speed = 2 * level;
	pocket.gender = true;
	pocket.m_pocketmonFrontImg = NULL;
	pocket.m_pocketmonBackImg = NULL;

	pocket.skillList.push_back(tackleProto);
	if(level>7)pocket.skillList.push_back(emberProto);
	if(level>13)pocket.skillList.push_back(flameThrowerProto);
	if(level>30)pocket.skillList.push_back(fireBlastProto);

	
	return pocket;
}

PocketMon PocketmonManager::genBulbasaur(int level)
{
	PocketMon pocket;
	pocket.m_name = "이상해씨";
	pocket.m_customName = "";
	pocket.m_level = level;
	pocket.m_maxHp = 22 + level * 6;
	pocket.m_currentHp = pocket.m_maxHp;
	pocket.m_maxExp = level * 20 + level * 2;
	pocket.m_currentExp = 0;
	pocket.m_wildExp = level * 10 + level * 1;
	pocket.m_atk = 6 + level * 2;
	pocket.m_specialAtk = 5 + level * 3;
	pocket.m_def = 3 + level * 3;
	pocket.m_specialDef = 3 + level * 3;
	pocket.m_Attribute = PockemonAttibute::PockemonAttibuteGrass;
	pocket.m_speed = 10 + level;
	pocket.gender = true;
	pocket.m_pocketmonFrontImg = NULL;
	pocket.m_pocketmonBackImg = NULL;

	pocket.skillList.push_back(tackleProto);
	if (level > 7)pocket.skillList.push_back(vineWhipProto);
	if (level > 13)pocket.skillList.push_back(razorLeafProto);
	if (level > 30)pocket.skillList.push_back(solarBeamProto);

	return pocket;
}

PocketMon PocketmonManager::genSquirtle(int level)
{
	PocketMon pocket;
	pocket.m_name = "꼬부기";
	pocket.m_customName = "";
	pocket.m_level = level;
	pocket.m_maxHp = 21 + level * 6;
	pocket.m_currentHp = pocket.m_maxHp;
	pocket.m_maxExp = level * 20 + level * 2;
	pocket.m_currentExp = 0;
	pocket.m_wildExp = level * 10 + level * 1;
	pocket.m_atk = 1 + level * 3;
	pocket.m_specialAtk = 3 + level * 2;
	pocket.m_def = 3 + level * 3;
	pocket.m_specialDef = 4 + level * 3;
	pocket.m_Attribute = PockemonAttibute::PockemonAttibuteWater;
	pocket.m_speed = level+level;
	pocket.gender = false;
	pocket.m_pocketmonFrontImg = NULL;
	pocket.m_pocketmonBackImg = NULL;

	pocket.skillList.push_back(tackleProto);
	if (level > 7)pocket.skillList.push_back(waterSaluteProto);
	if (level > 13)pocket.skillList.push_back(brineProto);
	if (level > 30)pocket.skillList.push_back(hydroPumpProto);

	return pocket;
}

PocketMon PocketmonManager::genPidgey(int level)
{
	PocketMon pocket;
	pocket.m_name = "구구";
	pocket.m_customName = "";
	pocket.m_level = level;
	pocket.m_maxHp = 22 + level * 6;
	pocket.m_currentHp = pocket.m_maxHp;
	pocket.m_maxExp = level * 20 + level * 2;
	pocket.m_currentExp = 0;
	pocket.m_wildExp = level * 10 + level * 1;
	pocket.m_atk = 5 + level*1 ;
	pocket.m_specialAtk = 3 + level * 2;
	pocket.m_def = 3 + level * 2;
	pocket.m_specialDef = 4 + level * 2;
	pocket.m_Attribute = PockemonAttibute::PockemonAttibuteFly;
	pocket.m_speed = 3 + level +level;
	pocket.gender = true;
	pocket.m_pocketmonFrontImg = NULL;
	pocket.m_pocketmonBackImg = NULL;

	pocket.skillList.push_back(quickAttackProto);
	if (level > 7)pocket.skillList.push_back(wingAttackProto);
	if (level > 13)pocket.skillList.push_back(airSlashProto);
	if (level > 30)pocket.skillList.push_back(hurricaneProto);


	return pocket;
}

PocketMon PocketmonManager::genPikachu(int level)
{
	PocketMon pocket;
	pocket.m_name = "피카츄";
	pocket.m_customName = "";
	pocket.m_level = level;
	pocket.m_maxHp = 19 + level * 5;
	pocket.m_currentHp = pocket.m_maxHp;
	pocket.m_maxExp = level * 20 + level * 2;
	pocket.m_currentExp = 0;
	pocket.m_wildExp = level * 11 + level * 1;
	pocket.m_atk = 1 + level * 2;
	pocket.m_specialAtk = 1 + level * 3;
	pocket.m_def = 1 + level * 2;
	pocket.m_specialDef = 2 + level * 2;
	pocket.m_Attribute = PockemonAttibute::PockemonAttibuteElectric;
	pocket.m_speed = 5 + level + level;
	pocket.gender = false;
	pocket.m_pocketmonFrontImg = NULL;
	pocket.m_pocketmonBackImg = NULL;

	pocket.skillList.push_back(quickAttackProto);
	if (level > 7)pocket.skillList.push_back(thunderWaveProto);
	if (level > 13)pocket.skillList.push_back(thunderboltProto);
	if (level > 30)pocket.skillList.push_back(thunderProto);


	return pocket;
}

PocketMon PocketmonManager::genCaterpie(int level)
{
	PocketMon pocket;
	pocket.m_name = "캐터피";
	pocket.m_customName = "";
	pocket.m_level = level;
	pocket.m_maxHp = 13 + level * 5;
	pocket.m_currentHp = pocket.m_maxHp;
	pocket.m_maxExp = level * 20 + level * 2;
	pocket.m_currentExp = 0;
	pocket.m_wildExp = level * 9 + level * 1;
	pocket.m_atk = 3 + level * 1;
	pocket.m_specialAtk = 3 + level * 2;
	pocket.m_def = 1 + level * 2;
	pocket.m_specialDef = 1 + level * 3;
	pocket.m_Attribute = PockemonAttibute::PockemonAttibuteNormal;
	pocket.m_speed = 4 + level;
	pocket.gender = false;
	pocket.m_pocketmonFrontImg = NULL;
	pocket.m_pocketmonBackImg = NULL;

	pocket.skillList.push_back(tackleProto);
	if (level > 4)pocket.skillList.push_back(scratchProto);
	if (level > 10)pocket.skillList.push_back(quickAttackProto);
	if (level > 20)pocket.skillList.push_back(megaPunchProto);



	return pocket;
}

PocketMon PocketmonManager::genRattata(int level)
{
	PocketMon pocket;
	pocket.m_name = "꼬렛";
	pocket.m_customName = "";
	pocket.m_level = level;
	pocket.m_maxHp = 13 + level * 5;
	pocket.m_currentHp = pocket.m_maxHp;
	pocket.m_maxExp = level * 20 + level * 2;
	pocket.m_currentExp = 0;
	pocket.m_wildExp = level * 8 + level * 1;
	pocket.m_atk = 6 + level * 1;
	pocket.m_specialAtk = 4 + level * 2;
	pocket.m_def = 2 + level * 2;
	pocket.m_specialDef = 4 + level * 3;
	pocket.m_Attribute = PockemonAttibute::PockemonAttibuteNormal;
	pocket.m_speed = 5 + level;
	pocket.gender = false;
	pocket.m_pocketmonFrontImg = NULL;
	pocket.m_pocketmonBackImg = NULL;

	pocket.skillList.push_back(tackleProto);
	if (level > 4)pocket.skillList.push_back(scratchProto);
	if (level > 10)pocket.skillList.push_back(quickAttackProto);
	if (level > 20)pocket.skillList.push_back(megaPunchProto);



	return pocket;
}

PocketMon PocketmonManager::genVulpix(int level)
{
	PocketMon pocket;
	pocket.m_name = "식스테일";
	pocket.m_customName = "";
	pocket.m_level = level;
	pocket.m_maxHp = 14 + level * 5;
	pocket.m_currentHp = pocket.m_maxHp;
	pocket.m_maxExp = level * 20 + level * 2;
	pocket.m_currentExp = 0;
	pocket.m_wildExp = level * 10 + level * 1;
	pocket.m_atk = 3 + level * 2;
	pocket.m_specialAtk = 3 + level * 2;
	pocket.m_def = 2 + level * 2;
	pocket.m_specialDef = 2 + level * 3;
	pocket.m_Attribute = PockemonAttibute::PockemonAttibuteFire;
	pocket.m_speed = 2*level;
	pocket.gender = true;
	pocket.m_pocketmonFrontImg = NULL;
	pocket.m_pocketmonBackImg = NULL;

	pocket.skillList.push_back(quickAttackProto);
	if (level > 7)pocket.skillList.push_back(emberProto);
	if (level > 15)pocket.skillList.push_back(flameThrowerProto);
	if (level > 23)pocket.skillList.push_back(fireBlastProto);

	return pocket;
}

PocketMon PocketmonManager::genOddish(int level)
{
	PocketMon pocket;
	pocket.m_name = "뚜벅초";
	pocket.m_customName = "";
	pocket.m_level = level;
	pocket.m_maxHp = 14 + level * 5;
	pocket.m_currentHp = pocket.m_maxHp;
	pocket.m_maxExp = level * 20 + level * 2;
	pocket.m_currentExp = 0;
	pocket.m_wildExp = level * 10 + level * 1;
	pocket.m_atk = 2 + level * 2;
	pocket.m_specialAtk = 2 + level * 2;
	pocket.m_def = 2 + level * 2;
	pocket.m_specialDef = 2 + level * 3;
	pocket.m_Attribute = PockemonAttibute::PockemonAttibuteGrass;
	pocket.m_speed = 2 * level;
	pocket.gender = true;
	pocket.m_pocketmonFrontImg = NULL;
	pocket.m_pocketmonBackImg = NULL;

	pocket.skillList.push_back(tackleProto);
	if (level > 6)pocket.skillList.push_back(vineWhipProto);
	if (level > 13)pocket.skillList.push_back(razorLeafProto);
	if (level > 25)pocket.skillList.push_back(solarBeamProto);

	return pocket;
}

PocketMon PocketmonManager::genPoliwag(int level)
{
	PocketMon pocket;
	pocket.m_name = "발챙이";
	pocket.m_customName = "";
	pocket.m_level = level;
	pocket.m_maxHp = 14 + level * 5;
	pocket.m_currentHp = pocket.m_maxHp;
	pocket.m_maxExp = level * 20 + level * 2;
	pocket.m_currentExp = 0;
	pocket.m_wildExp = level * 10 + level * 1;
	pocket.m_atk = 3 + level * 2;
	pocket.m_specialAtk = 3 + level * 2;
	pocket.m_def = 2 + level * 2;
	pocket.m_specialDef = 2 + level * 2;
	pocket.m_Attribute = PockemonAttibute::PockemonAttibuteWater;
	pocket.m_speed = 2 * level;
	pocket.gender = true;
	pocket.m_pocketmonFrontImg = NULL;
	pocket.m_pocketmonBackImg = NULL;

	pocket.skillList.push_back(tackleProto);
	if (level > 6)pocket.skillList.push_back(waterSaluteProto);
	if (level > 13)pocket.skillList.push_back(brineProto);
	if (level > 25)pocket.skillList.push_back(hydroPumpProto);

	return pocket;
}

