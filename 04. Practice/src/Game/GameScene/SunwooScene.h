#pragma once
#include "Game/GameScene/Scene.h"
#include "Game/GameObject/Tile.h"

class SunwooScene
	: public Scene
{
public:
	SunwooScene() {}
	~SunwooScene() {}
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

	std::vector<std::shared_ptr<Tile>> Tiles;


};