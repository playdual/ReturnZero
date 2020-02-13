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

	void myloadImage(std::string defaultName, std::string path, int _size);

public:
	HRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) override;

private:
	float deltaTime;
};

