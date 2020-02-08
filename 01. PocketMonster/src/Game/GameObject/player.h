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
	void isBattleStart();
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
	int m_playerCurrentArrowMemory; //Up = 0, Down = 1, Left = 2, Right =3
	int m_playerBeforeArrowMemory; //Up = 0, Down = 1, Left = 2, Right =3

	bool isEqulArrow=false;

	bool isMoveLeft=false;
	bool isMoveRight=false;
	bool isMoveUp=false;
	bool isMoveDown=false;
	bool isAnotherMove = false;

	bool isLeft = false;
	bool isRight = false;
	bool isUp = false;
	bool isDown = false;

	float m_CurrentTime=0;
	
	int count;
	int m_BattleStart;
	bool isBattle=false;
	bool isBattleTemp=false;
	//status == 불배열
	//badge
	//
	//QUESTSTATE == 불배열
	//money == int
	int m_blockPositionX;
	int m_blockPositionY;


	//player image
	Image* m_playerImg;
	Animation* m_aniplayer;
	Animation* m_aniplayerDown;
	Animation* m_aniplayerUp;
	Animation* m_aniplayerLeft;
	Animation* m_aniplayerRight;
	Animation* m_aniplayerMoveDown;
	Animation* m_aniplayerMoveUp;
	Animation* m_aniplayerMoveLeft;
	Animation* m_aniplayerMoveRight;

	

	std::vector<std::shared_ptr<PocketMon>> Pocketmons;
	std::shared_ptr<Inventory> Inven;

};