#include "stdafx.h"
#include "Potion.h"


Potion::Potion(ItemType _type, UTIL::IRECT _rect, std::string _name, int _count, 
	int _price, std::string _description, int _healHp, int _hitDamage)
	: Item(_type/*,_img */, _rect, _name, _count, _price, _description), m_healHp(_healHp), m_hitDamage(_hitDamage)
{
}

Potion::~Potion()
{
	
}

bool Potion::init()
{       

	return true;
}

void Potion::update(float _deltaTime)
{
}

void Potion::render(HDC hdc)
{

}

void Potion::afterRender(HDC hdc)
{
}

void Potion::debugRender(HDC hdc)
{
	UTIL::drawRect(hdc, m_iRect);
}
