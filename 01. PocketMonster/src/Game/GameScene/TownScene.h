#pragma once
#include "Scene.h"
#include "Game/GameObject/Character/player.h"
#include "Game/GameObject/Map/Map.h"

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
	std::shared_ptr<Map> m_map;

	//Menu
	UTIL::IRECT m_menurect;
	Image* m_menuImg;
};