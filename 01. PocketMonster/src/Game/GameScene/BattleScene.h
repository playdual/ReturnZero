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

	//init�ȿ� �� �����
	/*
	1. ��� �̹��� ���� (���ο��� �ε����� �����ϰ� �� �� ����)
	2. 
	*/

	//update�ȿ� �� �����
	/*
	1. ��� ��
	*/
};

