#pragma once
#include "Common/GameNode.h"

class MainGame :  public GameNode
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
	float deltaTime;
};

