#include "stdafx.h"
#include "item.h"

Item::Item(ItemType _type , Image* _img, UTIL::IRECT _rect, std::string _name,
	int _count, int _price, std::string _description)
	: m_type(_type), m_img(_img), m_iRect(_rect),m_ItemName(_name),
	  m_count(_count), m_price(_price), m_description(_description)
{
}

Item::~Item()
{
}

//bool Item::init()
//{
//	
//	return true;
//}
//
//void Item::update(float _deltaTime)
//{
//}
//
//void Item::render(HDC hdc)
//{
//}
//
//void Item::afterRender(HDC hdc)
//{
//}
//
//void Item::debugRender(HDC hdc)
//{
//}
