#pragma once
#include "Item.h"
#include "Items/Potion.h"
#include "PocketMon.h"
#include "Game/GameManager/ItemManager.h"

class Inventory 
{
public:
	Inventory();
	~Inventory();

	bool init();
	void update(float _deltaTime);

	void render(HDC hdc);
	void afterRender(HDC hdc);
	void debugRender(HDC hdc);



	std::vector<std::shared_ptr<Item>> m_item;
};

