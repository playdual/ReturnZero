#include "stdafx.h"
#include "Nutrient.h"

Nutrient::Nutrient(ItemType _type, UTIL::IRECT _rect, std::string _name, int _count, int _price, std::string _description, int _addAbility)
	:Item(_type/*,_img */, _rect, _name, _count, _price, _description), m_addAbility(_addAbility)
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
}

void Nutrient::afterRender(HDC hdc)
{
}

void Nutrient::debugRender(HDC hdc)
{
}
