#include "stdafx.h"
#include "SunwooScene.h"
#include "Game/GameObject/SunwooRect.h"
bool SunwooScene::init()
{
	std::shared_ptr<Object> obj = std::make_shared<SunwooRect>();
	obj->init();
	objs.push_back(obj);
	return true;
}

void SunwooScene::update(float _deltaTime)
{
	for (auto& obj : objs)
		obj->update(_deltaTime);
}

void SunwooScene::release()
{
}

void SunwooScene::render(HDC hdc)
{
	for (auto& obj : objs)
		obj->render(hdc);
}

void SunwooScene::afterRender(HDC hdc)
{
	for (auto& obj : objs)
		obj->afterRender(hdc);
}

void SunwooScene::debugRender(HDC hdc)
{
	for (auto& obj : objs)
		obj->debugRender(hdc);
}
