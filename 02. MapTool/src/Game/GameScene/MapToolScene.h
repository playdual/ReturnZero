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
	void cameraMove();

private:
	int m_prevMouseX;
	int m_prevMousey;
	int m_pickedMouseX;
	int m_pickedMouseY;

private:
	bool m_isSettedMove = false;
	bool m_isMouseMoveActive = false;
	bool m_settedColor = false;

	UTIL::IRECT m_selectRect;
	bool onSelect;
	bool startedSelect;

private:
	UTIL::IRECT clientRect;

public:
	//virtual LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

private:
	std::vector<std::shared_ptr<Tile>> m_Tiles;
};