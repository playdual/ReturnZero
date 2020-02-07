#pragma once
#include "stdafx.h"

class Scene {
public:
 	Scene() {};
	virtual ~Scene() {};

public:
	virtual bool init() = 0;
	//virtual bool init(std::shared_ptr<player> _player) = 0;
	virtual void update(float _deltaTime) = 0;
	virtual void release() = 0;

public:
	virtual void render(HDC hdc) = 0;
	virtual void afterRender(HDC hdc) = 0;
	virtual void debugRender(HDC hdc) = 0;

public:
	virtual LRESULT SceneProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};