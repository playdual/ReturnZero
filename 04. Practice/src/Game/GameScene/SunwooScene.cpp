#include "stdafx.h"
#include "SunwooScene.h"
#include "Game/GameObject/SunwooRect.h"
bool SunwooScene::init()
{
	std::shared_ptr<Object> obj = std::make_shared<SunwooRect>();

	obj->init();
	objs.push_back(obj);

	for (int y = 0; y < 100; ++y) {
		for (int x = 0; x < 100; ++x) {

			std::shared_ptr<Tile> tile = std::make_shared<Tile>();
			tile->init(TileType::TileTypeFloor, nullptr, false, true, x, y);
			Tiles.push_back(tile);
		}
	}
	return true;
}

void SunwooScene::update(float _deltaTime)
{
	for (auto& obj : objs)
		obj->update(_deltaTime);
	for (auto& Tile : Tiles)
		Tile->update(_deltaTime);
}

void SunwooScene::release()
{
}

void SunwooScene::render(HDC hdc)
{
	for (auto& Tile : Tiles)
	Tile->render(hdc);

	//for (int y = 0; y < 100; ++y) {
	//	for (int x = 0; x < 100; ++x) {
	//		tile->render(hdc);
	//		
	//	}
	//}

	for (auto& obj : objs)
		obj->render(hdc);
}

void SunwooScene::afterRender(HDC hdc)
{
	



}

void SunwooScene::debugRender(HDC hdc)
{
	for (auto& obj : objs)
		obj->debugRender(hdc);
}
