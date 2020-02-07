#pragma once
#include "Game/GameObject/Items/Item.h"

class StateHeal
	: public Item
{
public:
	StateHeal(ItemType _type , Image* _img, UTIL::IRECT _rect, std::string _name,
		int _count, int _price, std::string _description );
	~StateHeal();

	virtual bool init() override;
	virtual void update(float _deltaTime) override;

	virtual void render(HDC hdc) override;
	virtual void afterRender(HDC hdc) override;
	virtual void debugRender(HDC hdc) override;

private:

};

