#include "stdafx.h"
#include "Potion.h"
#include "Common/SystemManagers.h"

Potion::Potion(ItemType _type, Image* _potionImage, UTIL::IRECT _rect, std::string _name, int _count,
	int _price, std::string _description, int _healHp, int _hitDamage )
	: Item(_type, _potionImage, _rect, _name, _count, _price, _description), m_healHp(_healHp), m_hitDamage(_hitDamage),m_potionImage(_potionImage)
{
	m_itemInfo.type = _type;
	m_itemInfo.name = _name;
	m_itemInfo.healHp = _healHp;
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
	if (m_img != nullptr)
		m_img->render(hdc, 35, WINSIZEY - 160);
}

void Potion::afterRender(HDC hdc)
{
}

void Potion::debugRender(HDC hdc)
{
	UTIL::DrawRect(hdc, m_iRect);
}
