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
	void addMenu(MenuBar _newMenu);
	void delMenu(std::string _menuName);
	void menuUpdate();

private:
	Image* image;
	std::shared_ptr<player> m_player;
	std::shared_ptr<Map> m_map;

	//Menu
	UTIL::IRECT m_menurect;
	UTIL::IRECT m_IndexMenuRect;
	int m_menuIndex;
	int m_menuIndexMax;
	Image* m_menuImg;
	Image* m_IndexMenuImg;
	bool isPocketmonMenuOn = false;

	std::vector<MenuBar> Menu;
};