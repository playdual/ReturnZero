#pragma once
#include "Game/GameObject/Inventory.h"
#include "Game/GameObject/Item.h"
#include "Game/GameScene/Scene.h"

class InvenScene 
	: public Scene
{
public:
	InvenScene(std::shared_ptr<Inventory> _inven);
	~ InvenScene();

public:
	virtual bool init() override;
	virtual void update(float _deltaTime) override;
	virtual void release() override;

	virtual void render(HDC hdc) override;
	virtual void afterRender(HDC hdc) override;
	virtual void debugRender(HDC hdc) override;

	std::shared_ptr<Inventory> m_inven;
};

