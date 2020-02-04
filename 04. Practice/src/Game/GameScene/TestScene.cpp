#include "stdafx.h"
#include "TestScene.h"
#include "Game/GameObject/Rect.h"

bool TestScene::init()
{
	std::shared_ptr<Object> obj = std::make_shared<Rect>();
	obj->init();
	objs.push_back(obj);
	return true;

}

void TestScene::update(float _deltaTime)
{
	for (auto& obj : objs)
		obj->update(_deltaTime);
}

void TestScene::release()
{
}

void TestScene::render(HDC hdc)
{
	for (auto& obj : objs)
		obj->render(hdc);
}

void TestScene::afterRender(HDC hdc)
{
	for (auto& obj : objs)
		obj->afterRender(hdc);
}

void TestScene::debugRender(HDC hdc)
{
	for (auto& obj : objs)
		obj->debugRender(hdc);
}
