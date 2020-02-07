#include "stdafx.h"
#include "StateHeal.h"

StateHeal::StateHeal(ItemType _type, Image* _img, UTIL::IRECT _rect, std::string _name, int _count, int _price, std::string _description)
	:Item(_type, _img , _rect, _name, _count, _price, _description)
{
}

StateHeal::~StateHeal()
{
}

bool StateHeal::init()
{
	return true;
}

void StateHeal::update(float _deltaTime)
{
}

void StateHeal::render(HDC hdc)
{
}

void StateHeal::afterRender(HDC hdc)
{
}

void StateHeal::debugRender(HDC hdc)
{
}
