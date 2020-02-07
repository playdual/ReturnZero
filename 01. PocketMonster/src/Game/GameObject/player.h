#pragma once
#include "Game/GameObject/Object.h"
#include"Common/SystemManagers.h"
#include"Inventory.h"
#include"PocketMon.h"
class player
	: public Object
{
public:
	player();
	~player();


	bool init() override;
	void update(float _deltaTime) override;

public:
	void render(HDC hdc) override;
	void afterRender(HDC hdc) override;
	void debugRender(HDC hdc) override;

	int getPlayRectX();
	int getPlayRectY();
	void reLocate(int blockX, int blockY);
	//void rectInCamera(UTIL::IRECT& outRect, const UTIL::IRECT& realRect, bool& isOutput);
private:
	UTIL::IRECT m_playerRect;
	UTIL::IRECT m_outPlayerRect;

	UTIL::IRECT m_obstacleRect;	
	UTIL::IRECT m_outObstacleRect;
	bool isObstacleOut = false;

	UTIL::IRECT m_obstacleRect2;
	UTIL::IRECT m_outObstacleRect2;
	bool isObstacleOut2 = false;

	HDC viewhdc;

	Image* m_bg;
	int bgX;
	int bgY;
	int bgOutX;
	int bgOutY;

	int m_playerRectMemory;
	bool isMoveLeft=false;
	bool isMoveRight=false;
	bool isMoveUp=false;
	bool isMoveDown=false;
	bool isAnotherMove = false;


	int count;
	//status == 불배열
	//badge
	//
	//QUESTSTATE == 불배열
	//money == int
	int m_blockPositionX;
	int m_blockPositionY;



	//float m_cameraX;
	//float m_cameraY;

	std::vector<std::shared_ptr<PocketMon>> Pocketmons;
	std::shared_ptr<Inventory> Inven;

};