#pragma once
#include "Game/GameScene/Scene.h"
#include "Game/GameObject/Items/Inventory.h"

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

	//이거는 왜 public으로 둔것?? 그럴필요가 없군요.
	// 멤버 변수는 무조건(은 아니지만) private으로 둘것...

private:
	std::shared_ptr<Inventory> m_inven;
	Image* m_BackGround;
};

