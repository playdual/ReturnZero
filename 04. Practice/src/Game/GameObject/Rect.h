#pragma once
#include "Object.h"

class Rect
	: public Object
{
public:
	bool init() override;
	void update(float _deltaTime) override;

public:
	void render(HDC hdc) override;
	void afterRender(HDC hdc) override;
	void debugRender(HDC hdc) override;

private:
	UTIL::IRECT rect;
};