#include "stdafx.h"
#include "Close.h"

Close::Close(ItemType _type, Image * _potionImage, UTIL::IRECT _rect, std::string _name, int _count, int _price, std::string _description)
	:Item(_type, _potionImage, _rect, _name, _count, _price, _description)
{
}

Close::~Close()
{
}

bool Close::init()
{
	return true;
}

void Close::update(float _deltaTime)
{
}

void Close::render(HDC hdc)
{
	if (m_img != nullptr)
		m_img->render(hdc, 35, WINSIZEY - 160);
}

void Close::afterRender(HDC hdc)
{
}

void Close::debugRender(HDC hdc)
{
	UTIL::DrawRect(hdc, m_iRect);
}
