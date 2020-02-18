#include "stdafx.h"
#include "Nutrient.h"
#include "Common/SystemManagers.h"

Nutrient::Nutrient(ItemType _type, Image* _img, UTIL::IRECT _rect, std::string _name, int _count, int _price, std::string _description, bool _isEvolution)
	:Item(_type, _img , _rect, _name, _count, _price, _description), m_isEvolution( _isEvolution)
{

}

Nutrient::~Nutrient()
{
}

bool Nutrient::init()
{
	return true;
}

void Nutrient::update(float _deltaTime)
{
}

void Nutrient::render(HDC hdc)
{
	if (m_img != nullptr)
		m_img->render(hdc, 35, WINSIZEY - 160);
}

void Nutrient::afterRender(HDC hdc)
{
}

void Nutrient::debugRender(HDC hdc)
{
}
