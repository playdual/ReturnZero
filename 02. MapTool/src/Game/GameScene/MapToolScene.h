#pragma once

#include "Scene.h"
#include "Game/GameObject/Tile.h"

class MapToolScene
	: public Scene
{

public:
	bool init() override;
	void update(float _deltaTime) override;
	void release() override;

public:
	void render(HDC hdc) override;
	void afterRender(HDC hdc) override;
	void debugRender(HDC hdc) override;

public:
	//virtual LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

private:
	std::vector<std::shared_ptr<Tile>> m_Tiles;
};