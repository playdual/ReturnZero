#pragma once
#include "Game/GameObject/Object.h"
#include "Common/SystemManagers.h"
#include "Game/GameObject/Items/Inventory.h"
#include "Game/GameObject/Pocketmon/PocketMon.h"

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

public:
	int getCountPocketMon() { return Pocketmons.size(); }
	void setMoney(int moneyValue) { m_money = moneyValue; }
	int getMoney() { return m_money; }


public:
	void OnObjectEvent();
	void ObjectHandle(std::string objName);
	int getPlayRectX();
	int getPlayRectY();
	int getPlayerBlockX() { return m_blockPositionX; }
	int getPlayerBlockY() { return m_blockPositionY; }
	void reLocate(int blockX, int blockY);
	void isBattleStart();
	bool getisBattle() { return isBattle; }
	void BattleEnd() { isBattle = false; isAnotherMove = false; }
	void MoveSetZero();
	bool getisChangeMap();
	void isNotChangeMap();
	bool getisAfter();
	bool getisMenu();
	void setisMenu(bool ismenuvalue);
	void checkAndActivateNPC();
	std::vector<std::shared_ptr<class PocketMon>>& getPocketmons() { return Pocketmons; }
	void pushBackPocketmon(PocketMon _pocketmon);
	void setisMoveStop(bool moveValue) { isMoveStop = moveValue; }
private:
	//Object EventHandle Func
	void MoundJumpDown();

private:
	void moveLogic();
	void moveLeftLogic();
	void moveRightLogic();
	void moveUpLogic();
	void moveDownLogic();
	
private:
	UTIL::IRECT m_playerRect;
	UTIL::IRECT m_outPlayerRect;


	HDC viewhdc;

	Image* m_bg;
	Image* m_chat;
	Image* m_chatCursor;
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

	bool isMoveLeftTest = false;
	bool isOnNpcEvent = false;

	bool isLeft = false;
	bool isRight = false;
	bool isUp = false;
	bool isDown = false;
	Direction curDir;

	bool isAfter = true;
	bool isOnStrPrintEvent = false;
	std::string printOriginalStr;
	float m_CurrentTime=0;
	
	int count;
	int m_BattleStart;
	bool isBattle=false;
	bool isBattleTemp=false;
	bool isMoveStop = false;
	//status == 遺덈같??
	//badge
	//
	//QUESTSTATE == 遺덈같??
	int m_money=1000;
	int m_blockPositionX;
	int m_blockPositionY;

	//Change Map
	bool isChangeMap = false;

	//chat
	int isCursortemp = 0;
	bool isCursor = false;
	

	//Menu
	bool ismenu = false;

	//player image
	Image* m_playerImg;
	Image* m_playerShadow;
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
	std::shared_ptr<class Inventory> Inven;


	//Object EventHandle Var
	bool isOnObjectEvent = false;
	bool isOnMoundJumpDown = false;
	bool isOnMoundJumpUp = false;

	int jumpStartPosX;
	int jumpStartPosY;
	int jumpDx;
	int jumpDy;
};
