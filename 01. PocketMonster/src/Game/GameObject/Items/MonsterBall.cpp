#include "stdafx.h"
#include "MonsterBall.h"

MonsterBall::MonsterBall(ItemType _type, UTIL::IRECT _rect, std::string _name, int _count, int _price, std::string _description)
	:Item(_type/*,_img */, _rect, _name, _count, _price, _description)
{
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
}

void MonsterBall::afterRender(HDC hdc)
{
}

void MonsterBall::debugRender(HDC hdc)
{
}
