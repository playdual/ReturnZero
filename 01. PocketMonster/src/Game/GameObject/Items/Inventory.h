#pragma once
#include "Item.h"
#include "Game/GameObject/Pocketmon/PocketMon.h"

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

	int		itemNum;
	bool	nextText;

	std::vector<std::shared_ptr<Item>> m_item;
};

