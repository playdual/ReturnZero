#pragma once
#include "Scene.h"
#include "Game/GameObject/player.h"
#include "Game/GameObject/Tile.h"

class TownScene :
	public Scene 
{
public:
	TownScene();
	virtual ~TownScene();

public:
	bool init() override;
	void release() override;

public:
	void update(float _deltaTime) override;
	void render(HDC hdc) override;
	void afterRender(HDC hdc) override;
	void debugRender(HDC hdc) override;

private:
	Image* image;
	std::shared_ptr<player> m_player;
	std::vector < Tile > m_map;
};