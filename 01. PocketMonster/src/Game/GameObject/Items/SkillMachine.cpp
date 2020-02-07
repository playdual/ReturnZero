#include "stdafx.h"
#include "SkillMachine.h"

SkillMachine::SkillMachine(ItemType _type, PockemonAttibute _kind,UTIL::IRECT _rect, std::string _name, int _count, int _price, std::string _description, int _damage)
	:Item(_type/*,_img */, _rect, _name, _count, _price, _description), pockemonKind(_kind), m_damage(_damage)
{

}

SkillMachine::~SkillMachine()
{
}

bool SkillMachine::init()
{
	return true;
}

void SkillMachine::update(float _deltaTime)
{
}

void SkillMachine::render(HDC hdc)
{
}

void SkillMachine::afterRender(HDC hdc)
{
}

void SkillMachine::debugRender(HDC hdc)
{


}
