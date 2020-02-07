#pragma once
#include "Common/GameNode.h"
#include "GameScene/InvenScene.h"
#include "Game/GameObject/Inventory.h"

class MainGame 
	: public GameNode
{
private:

public:
	MainGame();
	~MainGame();

	HRESULT init() override;	
	void release() override;
	void update() override;
	void render() override;

	bool sceneInit = false;

public:
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

private:
	std::shared_ptr<Inventory> inven;
	std::shared_ptr<InvenScene> invenScene;
	float deltaTime;
};

