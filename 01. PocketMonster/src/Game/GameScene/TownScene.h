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
	void onMenu();


private:
	Image* image;
	std::shared_ptr<player> m_player;
	std::shared_ptr<Map> m_map;

	//Menu
	UTIL::IRECT m_menurect;
	UTIL::IRECT m_IndexMenuRect;
	
	UTIL::IRECT m_SceneChange[512];

	int m_menuIndex;
	int m_menuIndexMax;
	int PlaytimeMin;
	int PlaytimeSec;
	int x;
	int y;
	int j;
	int reportCnt=0;
	Image* m_menuImg;
	Image* m_IndexMenuImg;
	Image* m_TrainnerCard;
	Image* m_TrainnerCardPlayer;
	Image* m_PokemonBelt;
	Image* m_chat;
	bool isPocketmonMenuOn = false;
	bool isTrainnerCard = false;
	bool isColon = false;
	bool isBattle = false;
	bool isReport = false;
	std::vector<MenuBar> Menu;
};