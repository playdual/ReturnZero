#include "stdafx.h"
#include "Rect.h"

bool Rect::init()
{
	rect = UTIL::IRectMakeCenter(300, 300, 100, 100);
	return true;
}

void Rect::update(float _deltaTime)
{
	if (KEYMANAGER->isStayKeyDown(P1_UP)) {
		rect.moveUp(3);
	}
	if (KEYMANAGER->isStayKeyDown(P1_DOWN)) {
		rect.moveDown(3);
	}
	if (KEYMANAGER->isStayKeyDown(P1_LEFT)) {
		rect.moveLeft(3);
	}
	if (KEYMANAGER->isStayKeyDown(P1_RIGHT)) {
		rect.moveRight(3);
	}
}

void Rect::render(HDC hdc)
{
	UTIL::DrawColorRect(hdc, rect, true, RGB(255, 0, 255));
}

void Rect::afterRender(HDC hdc)
{
}

void Rect::debugRender(HDC hdc)
{
	
}
