#pragma once
#include "Scene.h"

class TestScene 
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


private:
	std::vector<std::shared_ptr<Object>> objs;

};