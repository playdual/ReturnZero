#pragma once
#include "Game/GameObject/Items/Item.h"

class MonsterBall
	: public Item
{
public:
	MonsterBall(ItemType _type , Image* _img, UTIL::IRECT _rect, std::string _name,
		int _count, int _price, std::string _description, int _poketCatchPercent);
	~ MonsterBall();

	virtual bool init() override;
	virtual void update(float _deltaTime) override;

	virtual void render(HDC hdc) override;
	virtual void afterRender(HDC hdc) override;
	virtual void debugRender(HDC hdc) override;

private:
	int m_poketCatchPercent;
};

