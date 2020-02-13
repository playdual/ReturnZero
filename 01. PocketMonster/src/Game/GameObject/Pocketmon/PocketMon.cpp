#include "stdafx.h"
#include "PocketMon.h"

PocketMon::PocketMon()
{
}

PocketMon::PocketMon(const PocketMon& _pocket)
{
	m_state = _pocket.m_state;
	m_name = _pocket.m_name;
	m_customName = _pocket.m_customName;
	m_level = _pocket.m_level;
	m_maxHp = _pocket.m_maxHp;
	m_currentHp = _pocket.m_currentHp;
	m_maxExp = _pocket.m_maxExp;
	m_currentExp = _pocket.m_currentExp;
	m_wildExp = _pocket.m_wildExp;
	m_atk = _pocket.m_atk;
	m_specialAtk = _pocket.m_specialAtk;
	m_def = _pocket.m_def;
	m_specialDef = _pocket.m_specialDef;
	m_Attribute = _pocket.m_Attribute;
	m_speed = _pocket.m_speed;
	gender = _pocket.gender;
	m_pocketmonFrontImg = _pocket.m_pocketmonFrontImg;
	m_pocketmonBackImg = _pocket.m_pocketmonBackImg;
	m_pocketmonIconImg = _pocket.m_pocketmonIconImg;
	for (auto e : _pocket.skillList) {
		skillList.push_back(e);
	}
}

PocketMon::~PocketMon()
{
}

bool PocketMon::init()
{
	return false;
}

void PocketMon::update(float _deltaTime)
{
}

void PocketMon::render(HDC hdc)
{
}

void PocketMon::afterRender(HDC hdc)
{
}

void PocketMon::debugRender(HDC hdc)
{
}

void PocketMon::skillEffect(int _skillNum)
{
}
