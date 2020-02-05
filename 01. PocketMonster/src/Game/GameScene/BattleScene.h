#pragma once
#include "Scene.h"
class BattleScene
	:public Scene
{
public:
	BattleScene();
	virtual ~BattleScene();

public:
	bool init() override;
	void release() override;

public:
	void update(float _deltaTime) override;
	void render(HDC hdc) override;
	void afterRender(HDC hdc) override;
	void debugRender(HDC hdc) override;

	//init안에 들어갈 내용들
	/*
	1. 배경 이미지 저장 (메인에서 로딩으로 진행하게 될 수 있음)
	2. 
	*/

	//update안에 들어갈 내용들
	/*
	1. 배경 이
	*/
};

