#include "stdafx.h"
#include "player.h"
#include "Common/GameManagers.h"
#include "Game/GameScene/PocketmonBagScene.h"

player::player()
{
}


player::~player()
{
}

bool player::init()
{
	std::cout << "Player init!" << std::endl;
	m_outPlayerRect = UTIL::IRectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, TILE_WIDTH, TILE_HEIGHT);
	CAMERAMANAGER->setCameraFocus(&m_playerRect.centerX, &m_playerRect.centerY, WINSIZEX / 2, WINSIZEY / 2);
	CAMERAMANAGER->update();
	bgX = 0;
	bgY = 0;

	//player img
	m_playerImg = IMAGEMANAGER->findImage("playerimg");
	m_playerShadow = IMAGEMANAGER->findImage("playerShadow");

	int down[] = { 0 };
	int up[] = { 1 };
	int left[] = { 2 };
	int right[] = { 3 };
	ANIMANAGER->addAnimation("playerDown", "playerimg", down, 1, 1, true);
	ANIMANAGER->addAnimation("playerUp", "playerimg", up, 1, 1, true);
	ANIMANAGER->addAnimation("playerLeft", "playerimg", left, 1, 1, true);
	ANIMANAGER->addAnimation("playerRight", "playerimg", right, 1, 1, true);

	//player Move Arrow img
	ANIMANAGER->addAnimation("playerMoveDown", "playerimg", 4, 7, 8, false, true);
	ANIMANAGER->addAnimation("playerMoveUp", "playerimg", 8, 11, 8, false, true);
	ANIMANAGER->addAnimation("playerMoveLeft", "playerimg", 12, 15, 8, false, true);
	ANIMANAGER->addAnimation("playerMoveRight", "playerimg", 16, 19, 8, false, true);


	m_aniplayerDown = ANIMANAGER->findAnimation("playerDown");
	m_aniplayerUp = ANIMANAGER->findAnimation("playerUp");
	m_aniplayerLeft = ANIMANAGER->findAnimation("playerLeft");
	m_aniplayerRight = ANIMANAGER->findAnimation("playerRight");

	m_aniplayerMoveDown = ANIMANAGER->findAnimation("playerMoveDown");
	m_aniplayerMoveUp = ANIMANAGER->findAnimation("playerMoveUp");
	m_aniplayerMoveLeft = ANIMANAGER->findAnimation("playerMoveLeft");
	m_aniplayerMoveRight = ANIMANAGER->findAnimation("playerMoveRight");

	//player Base Arrow(Start)
	isDown = true;
	curDir = DirectionDown;

	Pocketmons.push_back(std::make_shared<PocketMon>(POCKETMONMANAGER->genPocketMon("Rattata", 30)));
	Pocketmons.push_back(std::make_shared<PocketMon>(POCKETMONMANAGER->genPocketMon("Squirtle", 31)));


	m_playerBeforeArrowMemory = 0;
	m_playerCurrentArrowMemory = 0;

	SCENEMANAGER->addScene("PocketmonBagScene", new PocketmoninfoScene(Pocketmons));

	return true;
}

void player::moveLogic()
{
	//temp
	if (KEYMANAGER->isOnceKeyDown(P1_USEITEM)) {
		Pocketmons.push_back(std::make_shared<PocketMon>(POCKETMONMANAGER->genPocketMon("Squirtle", 31)));
	}
	if (!ismenu)
	{
		if (KEYMANAGER->isOnceKeyDown(GAME_MENU))
		{
			SOUNDMANAGER->playSound("Menu", Channel::eChannelEffect);

	static std::string npcName;
	//Move left
	if (isMoveLeft)
	{
		if (KEYMANAGER->isOnceKeyDown(GAME_MENUPROTO) || KEYMANAGER->isOnceKeyDown(P1_X))
		{
			SOUNDMANAGER->playSound("Menu", Channel::eChannelEffect);

		if (m_playerRect.left > m_playerRectMemory - TILE_WIDTH)
		{
			m_playerRect.moveLeft(5);
		}
		else
		{

			if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX - 1, m_blockPositionY) == TileType::TileTypeBush)
			{
				isBattleStart();
			}

			else if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX - 1, m_blockPositionY) == TileType::TileTypeNextMap)
			{
				isChangeMap = true;
			}
			//이동을 다했다면
			isLeft = true;
			isRight = false;
			isUp = false;
			isDown = false;
			isAnotherMove = false;
			m_blockPositionX -= 1;
			isMoveLeft = false;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(P1_LEFT) && m_playerBeforeArrowMemory != 2)
	{
		m_playerBeforeArrowMemory = 2;
		isLeft = true;
		isRight = false;
		isUp = false;
		isDown = false;
		curDir = DirectionLeft;
		m_CurrentTime = 0;

	}
	else if (KEYMANAGER->isStayKeyDown(P1_LEFT) && !isMoveLeft && !isAnotherMove && m_CurrentTime > 0.2f)
	{
		m_playerCurrentArrowMemory = 2;
		if (m_playerBeforeArrowMemory == 2 && m_playerCurrentArrowMemory == 2)
		{
			TileType type = MAPMANGER->getTileTypeFromIndex(m_blockPositionX - 1, m_blockPositionY);
			npcName = MAPMANGER->getNPCName(m_blockPositionX - 1, m_blockPositionY);
			if ((type == TileType::TileTypeFloor || type == TileType::TileTypeNextMap 
				|| type == TileType::TileTypeBush) && npcName == "")
			{
				isLeft = false;
				m_playerRectMemory = m_playerRect.left;
				isAnotherMove = true;
				isMoveLeft = true;
				isMoveLeftTest = true;
				curDir = DirectionLeft;
			}
			else if (type == TileType::TileTypeObject)
			{
				ObjectHandle(MAPMANGER->getObjectNameFromIndex(m_blockPositionX - 1, m_blockPositionY));

				if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX - 1, m_blockPositionY) == TileType::TileTypeFloor ||
					MAPMANGER->getTileTypeFromIndex(m_blockPositionX - 1, m_blockPositionY) == TileType::TileTypeNextMap ||
					MAPMANGER->getTileTypeFromIndex(m_blockPositionX - 1, m_blockPositionY) == TileType::TileTypeBush)
				{
					isLeft = false;
					m_playerRectMemory = m_playerRect.left;
					isAnotherMove = true;
					isMoveLeft = true;
					isMoveLeftTest = true;
				}
				if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX - 1, m_blockPositionY) == TileType::TileTypeNextMap)
					SOUNDMANAGER->playSound("MapMove", Channel::eChannelEffect);
			}
		}
	}

	//Move Right
	if (isMoveRight)
	{

		if (m_playerRect.right < m_playerRectMemory + TILE_WIDTH)
		{
			m_playerRect.moveRight(5);
		}
		else
		{
			if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX + 1, m_blockPositionY) == TileType::TileTypeBush)
			{
				isBattleStart();
			}

			else if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX + 1, m_blockPositionY) == TileType::TileTypeNextMap)
			{
				isChangeMap = true;
			}

			isLeft = false;
			isRight = true;
			isUp = false;
			isDown = false;
			isMoveRight = false;
			m_blockPositionX += 1;
			isAnotherMove = false;


		}
	}
	if (KEYMANAGER->isOnceKeyDown(P1_RIGHT) && m_playerBeforeArrowMemory != 3)
	{
		m_playerBeforeArrowMemory = 3;
		isLeft = false;
		isRight = true;
		isUp = false;
		isDown = false;
		m_CurrentTime = 0;
		curDir = DirectionRight;
	}
	else if (KEYMANAGER->isStayKeyDown(P1_RIGHT) && !isMoveRight && !isAnotherMove && m_CurrentTime > 0.2f)
	{
		m_playerCurrentArrowMemory = 3;


		if (m_playerBeforeArrowMemory == 3 && m_playerCurrentArrowMemory == 3)
				}
				if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX + 1, m_blockPositionY) == TileType::TileTypeNextMap)
					SOUNDMANAGER->playSound("MapMove", Channel::eChannelEffect);
			}
		}
		
		if (isMoveUp)
		{
			TileType type = MAPMANGER->getTileTypeFromIndex(m_blockPositionX + 1, m_blockPositionY);
			npcName = MAPMANGER->getNPCName(m_blockPositionX + 1, m_blockPositionY);
			if ((type == TileType::TileTypeFloor || type == TileType::TileTypeNextMap
				|| type == TileType::TileTypeBush) && npcName == "")
			{
				isRight = false;
				m_playerRectMemory = m_playerRect.right;
				isAnotherMove = true;
				isMoveRight = true;
				curDir = DirectionRight;
			}
			else if (type == TileType::TileTypeObject)
			{
				ObjectHandle(MAPMANGER->getObjectNameFromIndex(m_blockPositionX + 1, m_blockPositionY));
			}
		}
	}

	//Move Up
	if (isMoveUp)
	{
		if (m_playerRect.top > m_playerRectMemory - TILE_HEIGHT)
		{
			m_playerRect.moveUp(5);
		}
		else
		{

			if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY - 1) == TileType::TileTypeBush)
			{
				isBattleStart();
			}

			else if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY - 1) == TileType::TileTypeNextMap)
			{
				isChangeMap = true;
			}

			isLeft = false;
			isRight = false;
			isUp = true;
			isDown = false;
			m_blockPositionY -= 1;
			isAnotherMove = false;
			isMoveUp = false;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(P1_UP) && m_playerBeforeArrowMemory != 1)
	{
		m_playerBeforeArrowMemory = 1;
		isLeft = false;
		isRight = false;
		isUp = true;
		isDown = false;
		curDir = DirectionUp;
		m_CurrentTime = 0;
	}
	else if (KEYMANAGER->isStayKeyDown(P1_UP) && !isMoveUp && !isAnotherMove && m_CurrentTime > 0.2f)
	{
		m_playerCurrentArrowMemory = 1;


		if (m_playerBeforeArrowMemory == 1 && m_playerCurrentArrowMemory == 1)
				if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY - 1) == TileType::TileTypeFloor ||
					MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY - 1) == TileType::TileTypeNextMap ||
					MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY - 1) == TileType::TileTypeBush)
				{
					isUp = false;
					m_playerRectMemory = m_playerRect.top;
					isAnotherMove = true;
					isMoveUp = true;
				}
				if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY -1) == TileType::TileTypeNextMap)
					SOUNDMANAGER->playSound("MapMove", Channel::eChannelEffect);
			}
		}
		
		if (isMoveDown)
		{
			TileType type = MAPMANGER->getTileTypeFromIndex(m_blockPositionX , m_blockPositionY - 1);
			npcName = MAPMANGER->getNPCName(m_blockPositionX, m_blockPositionY - 1);
			if ((type == TileType::TileTypeFloor || type == TileType::TileTypeNextMap
				|| type == TileType::TileTypeBush) && npcName == "")
			{
				isUp = false;
				m_playerRectMemory = m_playerRect.top;
				isAnotherMove = true;
				isMoveUp = true;
				curDir = DirectionUp;
			}
			else if (type == TileType::TileTypeObject)
			{
				ObjectHandle(MAPMANGER->getObjectNameFromIndex(m_blockPositionX, m_blockPositionY - 1));
			}
		}
	}


	//Down Move
	if (isMoveDown)
	{
		if (m_playerRect.bottom < m_playerRectMemory + TILE_HEIGHT)
		{
			isAfter = false;
			m_playerRect.moveDown(5);
		}
		else
		{

			if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY + 1) == TileType::TileTypeBush)
			{
				isBattleStart();
			}

			else if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY + 1) == TileType::TileTypeNextMap)
			{
				isChangeMap = true;
			}

			isAfter = true;
			isLeft = false;
			isRight = false;
			isUp = false;
			isDown = true;
			m_blockPositionY += 1;
			isMoveDown = false;
			isAnotherMove = false;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(P1_DOWN) && m_playerBeforeArrowMemory != 0)
	{
		m_playerBeforeArrowMemory = 0;
		isLeft = false;
		isRight = false;
		isUp = false;
		isDown = true;
		m_CurrentTime = 0;
		curDir = DirectionDown;
	}
	else if (KEYMANAGER->isStayKeyDown(P1_DOWN) && !isMoveDown && !isAnotherMove && m_CurrentTime > 0.2f)
	{
		m_playerCurrentArrowMemory = 0;
		if (m_playerBeforeArrowMemory == 0 && m_playerCurrentArrowMemory == 0)
		{
			TileType type = MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY + 1);
			npcName = MAPMANGER->getNPCName(m_blockPositionX, m_blockPositionY + 1);
			if ((type == TileType::TileTypeFloor || type == TileType::TileTypeNextMap
				|| type == TileType::TileTypeBush) && npcName == "")
			{
				isDown = false;
				m_playerRectMemory = m_playerRect.bottom;
				isAnotherMove = true;
				isMoveDown = true;
				curDir = DirectionDown;
			}
			else if (type == TileType::TileTypeObject)
			{
				ObjectHandle(MAPMANGER->getObjectNameFromIndex(m_blockPositionX , m_blockPositionY + 1));

				if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY + 1) == TileType::TileTypeFloor ||
					MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY + 1) == TileType::TileTypeNextMap ||
					MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY + 1) == TileType::TileTypeBush)
				{
					isDown = false;
					m_playerRectMemory = m_playerRect.bottom;
					isAnotherMove = true;
					isMoveDown = true;
				}
				if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY + 1) == TileType::TileTypeNextMap)
					SOUNDMANAGER->playSound("MapMove", Channel::eChannelEffect);
			}
		}
	}

	//NPC Activat
	if (KEYMANAGER->isOnceKeyDown(P1_Z)) {
		checkAndActivateNPC();
	}


	//animation handle
	if (isMoveDown)ANIMANAGER->resume("playerMoveDown");
	else if (!isMoveDown)ANIMANAGER->pause("playerMoveDown");

	if (isMoveUp)ANIMANAGER->resume("playerMoveUp");
	else if (!isMoveUp)
		ANIMANAGER->pause("playerMoveUp");

	if (isMoveLeft)ANIMANAGER->resume("playerMoveLeft");
	else if (!isMoveLeft)ANIMANAGER->pause("playerMoveLeft");

	if (isMoveRight)ANIMANAGER->resume("playerMoveRight");
	else if (!isMoveRight)ANIMANAGER->pause("playerMoveRight");

	if (isDown)ANIMANAGER->resume("playerDown");
	else if (!isDown)ANIMANAGER->pause("playerDown");

	if (isUp)ANIMANAGER->resume("playerUp");
	else if (!isUp)ANIMANAGER->pause("playerUp");

	if (isLeft)ANIMANAGER->resume("playerLeft");
	else if (!isLeft)ANIMANAGER->pause("playerLeft");

	if (isRight)ANIMANAGER->resume("playerRight");
	else if (!isRight)ANIMANAGER->pause("playerRight");
}

void player::update(float _deltaTime)
{
	//temp
	if (KEYMANAGER->isOnceKeyDown(P1_USEITEM)) {
		Pocketmons.push_back(std::make_shared<PocketMon>(POCKETMONMANAGER->genPocketMon("Squirtle", 31)));
	}
	if (!ismenu)
	{
		if (KEYMANAGER->isOnceKeyDown(GAME_MENU))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			ismenu = true;
		}
	}
	else if (ismenu)
	{
		if (KEYMANAGER->isOnceKeyDown(GAME_MENUPROTO) || KEYMANAGER->isOnceKeyDown(P1_X))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);

			ismenu = false;
		}
	}

	//배틀중이 아니고, 메뉴를 열지 않았고, 오브젝트 이벤트 중이 아니라면
	if (!isBattle && !ismenu && !isOnObjectEvent && !isOnNpcEvent)
	{
		m_CurrentTime += _deltaTime;
		moveLogic(); // 이동 로직 실행
	}

	if (isOnObjectEvent)
	{
		OnObjectEvent();
	}

	if (isOnNpcEvent) {
		isOnNpcEvent = MAPMANGER->getCurNpc()->isOnActevated();
	}

	if (isBattle)
	{
		isMoveLeft = false;
		isMoveRight = false;
		isMoveUp = false;
		isMoveDown = false;

	}
	CAMERAMANAGER->update();	
}

void player::render(HDC hdc)
{


	//player
	if (isOnMoundJumpDown) {
		m_playerShadow->render(hdc, m_outPlayerRect.left, WINSIZEY / 2);
		m_playerImg->aniRender(hdc, m_outPlayerRect.left, m_outPlayerRect.top + PLAYER_OFFSETY, m_aniplayerMoveDown);
	}
	else if (isMoveDown)
		m_playerImg->aniRender(hdc, m_outPlayerRect.left, m_outPlayerRect.top + PLAYER_OFFSETY, m_aniplayerMoveDown);
	else if (isMoveUp)
		m_playerImg->aniRender(hdc, m_outPlayerRect.left, m_outPlayerRect.top + PLAYER_OFFSETY, m_aniplayerMoveUp);
	else if (isMoveLeft)
		m_playerImg->aniRender(hdc, m_outPlayerRect.left, m_outPlayerRect.top + PLAYER_OFFSETY, m_aniplayerMoveLeft);
	else if (isMoveRight)
		m_playerImg->aniRender(hdc, m_outPlayerRect.left, m_outPlayerRect.top + PLAYER_OFFSETY, m_aniplayerMoveRight);
	else if (isDown)
		m_playerImg->aniRender(hdc, m_outPlayerRect.left, m_outPlayerRect.top + PLAYER_OFFSETY, m_aniplayerDown);
	else if (isUp)
		m_playerImg->aniRender(hdc, m_outPlayerRect.left, m_outPlayerRect.top + PLAYER_OFFSETY, m_aniplayerUp);
	else if (isLeft)
		m_playerImg->aniRender(hdc, m_outPlayerRect.left, m_outPlayerRect.top + PLAYER_OFFSETY, m_aniplayerLeft);
	else if (isRight)
		m_playerImg->aniRender(hdc, m_outPlayerRect.left, m_outPlayerRect.top + PLAYER_OFFSETY, m_aniplayerRight);

	

}

void player::afterRender(HDC hdc)
{
}

void player::debugRender(HDC hdc)
{
	UTIL::DrawColorRect(hdc, m_outPlayerRect, RGB(153, 255, 30), true);

}


void player::OnObjectEvent()
{
	if (isOnMoundJumpDown)
		MoundJumpDown();

}

void player::ObjectHandle(std::string objName)
{
	if (objName == "UpDownMound") {
		if (curDir == DirectionDown) {
			isOnObjectEvent = true;
			isOnMoundJumpDown = true;
			jumpStartPosY = m_playerRect.bottom;
			jumpStartPosX = 0;
			jumpDx = 0;
			jumpDy = 0;
			ANIMANAGER->start("playerMoveDown");
		}
	}
}




int player::getPlayRectX()
{
	return m_playerRect.centerX;
}

int player::getPlayRectY()
{

	return m_playerRect.centerY;
}

void player::reLocate(int blockX, int blockY)
{

	m_blockPositionX = blockX;
	m_blockPositionY = blockY;

	m_playerRect.left = blockX * TILE_WIDTH;
	m_playerRect.right = blockX * TILE_WIDTH + TILE_WIDTH;
	m_playerRect.top = blockY * TILE_HEIGHT;
	m_playerRect.bottom = blockY * TILE_HEIGHT + TILE_HEIGHT;

	m_playerRect.centerX = m_playerRect.left + (m_playerRect.right - m_playerRect.left) / 2;
	m_playerRect.centerY = m_playerRect.top + (m_playerRect.bottom - m_playerRect.top) / 2;
}

void player::isBattleStart()
{
	if (isBattle == false)
	{
		m_BattleStart = UTIL::GetRndInt(100);

		if (m_BattleStart < 100)
		{
			isBattle = true;
		}
		else
		{
			isBattle = false;
		}
	}
}

void player::MoveSetZero()
{

	isMoveDown = false;
	isMoveUp = false;
	isMoveLeft = false;
	isMoveRight = false;
	isAnotherMove = false;

}

bool player::getisChangeMap()
{
	return isChangeMap;
}

void player::isNotChangeMap()
{
	isChangeMap = false;
}

bool player::getisAfter()
{
	return isAfter;
}

bool player::getisMenu()
{
	return ismenu;
}

void player::setisMenu(bool ismenuvalue)
{
	ismenu = ismenuvalue;
}

void player::checkAndActivateNPC()
{
	std::string npcName;
	switch (curDir)
	{
	case DirectionDown:
		npcName = MAPMANGER->getNPCName(m_blockPositionX, m_blockPositionY + 1);
		break;
	case DirectionUp:
		npcName = MAPMANGER->getNPCName(m_blockPositionX, m_blockPositionY - 1);
		break;
	case DirectionLeft:
		npcName = MAPMANGER->getNPCName(m_blockPositionX - 1, m_blockPositionY);
		break;
	case DirectionRight:
		npcName = MAPMANGER->getNPCName(m_blockPositionX + 1, m_blockPositionY);
		break;
	}
	isOnNpcEvent = MAPMANGER->ActivateNPC(npcName, curDir);
}

void player::MoundJumpDown()
{
	m_playerRect.moveDown(5);
	jumpDx += 5;
	if (jumpDx <= TILE_HEIGHT)
	{
		m_outPlayerRect.moveUp(3);
	}
	else if(jumpDx < TILE_HEIGHT * 2)
	{
		m_outPlayerRect.moveDown(3);
	}

	if (jumpDx == TILE_HEIGHT * 2) {
		m_outPlayerRect = UTIL::IRectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, TILE_WIDTH, TILE_HEIGHT);
		isOnObjectEvent = false;
		isOnMoundJumpDown = false;
		m_blockPositionY += 2;
	}
void player::pushBackPocketmon(PocketMon _pocketmon)
{
	Pocketmons.push_back(std::make_shared<PocketMon>(_pocketmon));
}



