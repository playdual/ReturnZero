#include "stdafx.h"
#include "MonsterBall.h"
#include "Common/SystemManagers.h"

MonsterBall::MonsterBall(ItemType _type, Image* _img, UTIL::IRECT _rect, std::string _name, int _count, int _price, std::string _description , int _poketCatchPercent)
	:Item(_type, _img, _rect, _name, _count, _price, _description), m_poketCatchPercent(_poketCatchPercent)
{
	m_itemInfo.name = _name;
}

MonsterBall::~MonsterBall()
{
}

bool MonsterBall::init()
{
	return true;
}

void MonsterBall::update(float _deltaTime)
{
}

void MonsterBall::render(HDC hdc)
{
	if (m_img != nullptr)
		m_img->render(hdc, 35, WINSIZEY - 160);
}

void MonsterBall::afterRender(HDC hdc)
{
}

void MonsterBall::debugRender(HDC hdc)
{
	UTIL::DrawRect(hdc, m_iRect);
}
