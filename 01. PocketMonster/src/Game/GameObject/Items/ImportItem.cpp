#include "stdafx.h"
#include "ImportItem.h"

ImportItem::ImportItem(ItemType _type, Image * _potionImage, UTIL::IRECT _rect, std::string _name, int _count, int _price, std::string _description)
	:Item(_type, _potionImage, _rect, _name, _count, _price, _description)
{
}

ImportItem::~ImportItem()
{
}

bool ImportItem::init()
{
	return true;
}

void ImportItem::update(float _deltaTime)
{
}

void ImportItem::render(HDC hdc)
{
	if (m_img != nullptr)
		m_img->render(hdc, 35, WINSIZEY - 160);
}

void ImportItem::afterRender(HDC hdc)
{
}

void ImportItem::debugRender(HDC hdc)
{
	UTIL::DrawRect(hdc, m_iRect);
}
