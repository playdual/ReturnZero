#include "stdafx.h"
#include "Paili.h"

bool Paili::init()
{
	EFFECTMANAGER->addEffect("파이리스킬1", "images/pailiSkill_1.bmp", 35, 150, 35, 30, 1, 0.1f, 100);
	m_level = 1;
	//m_pocketmonFrontImg;
	//m_pocketmonBackImg;
	m_name = "파이리";
	m_customName = "영환리";
	//m_Attribute;
	gender = true;
	m_level = 10;
	m_maxHp = 29;
	m_currentHp = 29;
	m_atk = 15;
	m_def = 13;
	m_specialAtk = 17;
	m_specialDef = 17;
	m_dex = 19;
	m_maxExp = 742;
	m_currentExp = 0;

	skillMotionOn = false;
	return true;
}

void Paili::update(float _deltaTime)
{
}

void Paili::render(HDC hdc)
{
}

void Paili::afterRender(HDC hdc)
{
}

void Paili::debugRender(HDC hdc)
{
}

void Paili::skillEffect(int _skillNum)
{
	if (_skillNum == 1)
	{
		EFFECTMANAGER->play("파이리스킬1", 410, 329);
		skillMotionOn = EFFECTMANAGER->getIsPlay();
	}
	if (_skillNum == 2) 
	{

	}
	if (_skillNum == 3) 
	{

	}
	if (_skillNum == 4) 
	{

	}
}
