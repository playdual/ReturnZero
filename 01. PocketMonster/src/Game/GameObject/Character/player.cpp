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

	m_chat = IMAGEMANAGER->findImage("상점NPC대화상자");
	m_chatCursor = IMAGEMANAGER->findImage("DialCopleteArrow");

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

	Pocketmons.push_back(std::make_shared<PocketMon>(POCKETMONMANAGER->genPocketMon("Pikachu", 30)));
	Pocketmons.push_back(std::make_shared<PocketMon>(POCKETMONMANAGER->genPocketMon("Squirtle", 31)));


	m_playerBeforeArrowMemory = 0;
	m_playerCurrentArrowMemory = 0;

	SCENEMANAGER->addScene("PocketmonBagScene", new PocketmoninfoScene(Pocketmons));

	return true;
}

//move logic
void player::moveLeftLogic()
{
	//왼쪽으로 이동중
	if (isMoveLeft)
	{
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

	//방향 바꾸기 로직
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
	//이동 여부를 확인
	else if (KEYMANAGER->isStayKeyDown(P1_LEFT) && !isMoveLeft && !isAnotherMove && m_CurrentTime > 0.2f)
	{
		m_playerCurrentArrowMemory = 2;
		if (m_playerBeforeArrowMemory == 2 && m_playerCurrentArrowMemory == 2)
		{
			TileType type = MAPMANGER->getTileTypeFromIndex(m_blockPositionX - 1, m_blockPositionY);
			auto npcName = MAPMANGER->getNPCName(m_blockPositionX - 1, m_blockPositionY);
			if ((type == TileType::TileTypeFloor || type == TileType::TileTypeNextMap
				|| type == TileType::TileTypeBush) && npcName == "")
			{
				isLeft = false;
				m_playerRectMemory = m_playerRect.left;
				isAnotherMove = true;
				isMoveLeft = true;
				curDir = DirectionLeft;
			}
			else if (type == TileType::TileTypeObject)
			{
				ObjectHandle(MAPMANGER->getObjectNameFromIndex(m_blockPositionX - 1, m_blockPositionY));
			}
			if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX - 1, m_blockPositionY) == TileType::TileTypeNextMap)
				SOUNDMANAGER->playSound("MapMove", Channel::eChannelEffect);
		}
	}
}
void player::moveRightLogic()
{
	//오른쪽으로 이동중
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

	//방향 바꾸기 로직
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
	//이동 여부를 확인
	else if (KEYMANAGER->isStayKeyDown(P1_RIGHT) && !isMoveRight && !isAnotherMove && m_CurrentTime > 0.2f)
	{
		m_playerCurrentArrowMemory = 3;
		if (m_playerBeforeArrowMemory == 3 && m_playerCurrentArrowMemory == 3)
		{
			TileType type = MAPMANGER->getTileTypeFromIndex(m_blockPositionX + 1, m_blockPositionY);
			auto npcName = MAPMANGER->getNPCName(m_blockPositionX + 1, m_blockPositionY);
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
			if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX + 1, m_blockPositionY) == TileType::TileTypeNextMap)
				SOUNDMANAGER->playSound("MapMove", Channel::eChannelEffect);
		}
	}
}
void player::moveUpLogic()
{
	//위로 이동중
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

	//방향 바꾸기 로직
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
	//이동 여부를 확인
	else if (KEYMANAGER->isStayKeyDown(P1_UP) && !isMoveUp && !isAnotherMove && m_CurrentTime > 0.2f)
	{
		m_playerCurrentArrowMemory = 1;

		if (m_playerBeforeArrowMemory == 1 && m_playerCurrentArrowMemory == 1)
		{
			TileType type = MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY - 1);
			auto npcName = MAPMANGER->getNPCName(m_blockPositionX, m_blockPositionY - 1);
			if ((type == TileType::TileTypeFloor || type == TileType::TileTypeNextMap
				|| type == TileType::TileTypeBush) && npcName == "")
			{
				isUp= false;
				m_playerRectMemory = m_playerRect.top;
				isAnotherMove = true;
				isMoveUp= true;
				curDir = DirectionUp;
			}
			else if (type == TileType::TileTypeObject)
			{
				ObjectHandle(MAPMANGER->getObjectNameFromIndex(m_blockPositionX, m_blockPositionY - 1));
			}
			if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY - 1) == TileType::TileTypeNextMap)
				SOUNDMANAGER->playSound("MapMove", Channel::eChannelEffect);
		}
	}
}
void player::moveDownLogic()
{
	//아래로 이동중
	if (isMoveDown)
	{
		if (m_playerRect.bottom < m_playerRectMemory + TILE_HEIGHT)
		{
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

	//방향 바꾸기 로직
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
	//이동 여부를 확인
	else if (KEYMANAGER->isStayKeyDown(P1_DOWN) && !isMoveDown && !isAnotherMove && m_CurrentTime > 0.2f)
	{
		m_playerCurrentArrowMemory = 0;
		if (m_playerBeforeArrowMemory == 0 && m_playerCurrentArrowMemory == 0)
		{
			TileType type = MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY + 1);
			auto npcName = MAPMANGER->getNPCName(m_blockPositionX, m_blockPositionY + 1);
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
				ObjectHandle(MAPMANGER->getObjectNameFromIndex(m_blockPositionX, m_blockPositionY + 1));
			}
			if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY + 1) == TileType::TileTypeNextMap)
				SOUNDMANAGER->playSound("MapMove", Channel::eChannelEffect);
		}
	}
}
void player::moveLogic()
{
	std::string npcName;
	
	//Move left
	moveLeftLogic();
	moveRightLogic();
	moveUpLogic();
	moveDownLogic();
	

	//NPC Activat
	if (KEYMANAGER->isOnceKeyDown(P1_Z)) 
	{
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
	isCursortemp = TIMEMANAGER->getWorldTime();
	if (isCursortemp % 2 == 0)
	{
		isCursor = true;
	}
	else
	{
		isCursor = false;
	}

	//temp
	if (KEYMANAGER->isOnceKeyDown(P1_USEITEM)) {
		Pocketmons.push_back(std::make_shared<PocketMon>(POCKETMONMANAGER->genPocketMon("Squirtle", 31)));
	}
	if (!ismenu)
	{
		if (!isMoveStop && KEYMANAGER->isOnceKeyDown(GAME_MENU))
		{
			SOUNDMANAGER->playSound("Menu", Channel::eChannelEffect);

			ismenu = true;
		}
	}
	else if (ismenu)
	{
		if (!isMoveStop && KEYMANAGER->isOnceKeyDown(GAME_MENU) || KEYMANAGER->isOnceKeyDown(P1_X))
		{
			SOUNDMANAGER->playSound("Menu", Channel::eChannelEffect);

			ismenu = false;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(P1_B)) {
		isBattle = true;
	}

	//배틀중이 아니고, 메뉴를 열지 않았고, 오브젝트 이벤트 중이 아니고, 이동중지 상태가 아니라면
	if (!isBattle && !ismenu && !isOnObjectEvent && !isOnNpcEvent && !isMoveStop)
	{
		m_CurrentTime += _deltaTime;
		moveLogic(); // 이동 로직 실행
	}
	if (isOnStrPrintEvent)
	{
		isMoveStop = true;

		if (KEYMANAGER->isOnceKeyDown(P1_X))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);
			isOnStrPrintEvent = false;
			isMoveStop = false;
		}
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

	if (isOnStrPrintEvent)
	{
		m_chat->render(hdc, 0, 590);
		UTIL::PrintText(hdc, printOriginalStr.c_str(), "소야바른9", 55, 625, 65, RGB(208, 208, 200), true, RGB(0, 0, 0));
		UTIL::PrintText(hdc, printOriginalStr.c_str(), "소야바른9", 50, 625, 65, RGB(0, 0, 0), true, RGB(0, 0, 0));

		if (isCursor)
		{
			m_chatCursor->render(hdc, 512, 713);
		}
	}
	else if (!isOnStrPrintEvent)
	{
		printOriginalStr = "";
	}
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
	else
	{
		

		if (objName == "TV")
		{
			isOnStrPrintEvent = true;
			isMoveStop = true;
			printOriginalStr = "반짝이는 티비다!";
		}
		else if(objName == "SuzaeComputer")
		{
			isOnStrPrintEvent = true;
			isMoveStop = true;
			printOriginalStr = "내 컴퓨터는 386이다... 그냥 끄자.";
		}
		else if (objName == "Bed")
		{
			isOnStrPrintEvent = true;
			isMoveStop = true;
			printOriginalStr = "푹신한 침대가 잘 정돈되어있다.";
		}
		else if (objName == "BookShelf")
		{
			isOnStrPrintEvent = true;
			isMoveStop = true;
			printOriginalStr = "포켓몬대백과라는 책이 눈에 띈다.";
		}
		else if (objName == "Drawer")
		{
			isOnStrPrintEvent = true;
			isMoveStop = true;
			printOriginalStr = "서랍이 잠겨있다.";
		}
		else if (objName == "Desk")
		{
			isOnStrPrintEvent = true;
			isMoveStop = true;
			printOriginalStr = "최신형 책상이다.";
		}
		else if (objName == "Map")
		{
			isOnStrPrintEvent = true;
			isMoveStop = true;
			printOriginalStr = "우리나라 지도가 그려져 있다.";
		}
		else if (objName == "Nintendo")
		{
			isOnStrPrintEvent = true;
			isMoveStop = true;
			printOriginalStr = "최신형 닌텐도 게임기가 있다!";
		}
		else if (objName == "Sink")
		{
			isOnStrPrintEvent = true;
			isMoveStop = true;
			printOriginalStr = "어머니 설거지를 도와드려야 할텐데...";
		}
		else if (objName == "Cabinet")
		{
			isOnStrPrintEvent = true;
			isMoveStop = true;
			printOriginalStr = "이쁜 식기류가 나열 되어있다.";
		}
		else if (objName == "PictureFrame")
		{
			isOnStrPrintEvent = true;
			isMoveStop = true;
			printOriginalStr = "선생님의 리즈시절 사진이 걸려있다.";
		}
		else if (objName == "Table")
		{
			isOnStrPrintEvent = true;
			isMoveStop = true;
			printOriginalStr = "테이블을 닦아야 할텐데...";
		}
		else if (objName == "ScheduleBoard")
		{
			isOnStrPrintEvent = true;
			isMoveStop = true;
			printOriginalStr = "이번주는 코딩공부로 꽉차 있다.";
		}
		else if (objName == "BookShelf2")
		{
			isOnStrPrintEvent = true;
			isMoveStop = true;
			printOriginalStr = "박사님의 비밀책장에는 무엇이...";
		}
		else if (objName == "PocketDesk")
		{
			isOnStrPrintEvent = true;
			isMoveStop = true;
			printOriginalStr = "포켓몬을 처음 골랐던 책상이다.";
		}
		else if (objName == "SpacialMachine")
		{
			isOnStrPrintEvent = true;
			isMoveStop = true;
			printOriginalStr = "박사님이 이상한 음모를 꾸미는 것 같다.";
		}
		else if (objName == "ResearchData")
		{
			isOnStrPrintEvent = true;
			isMoveStop = true;
			printOriginalStr = "포켓몬은 동물일까? 라는 연구자료다.";
		}
		else if (objName == "MileStone")
		{
		isOnStrPrintEvent = true;
		isMoveStop = true;
		printOriginalStr = "이곳의 위치를 알려주는 이정표이다.";
		}
		else if (objName == "MileStone2")
		{
		isOnStrPrintEvent = true;
		isMoveStop = true;
		printOriginalStr = "이곳은 태초마을.";
		}
		else if (objName == "TreePot")
		{
		isOnStrPrintEvent = true;
		isMoveStop = true;
		printOriginalStr = "잎을 꺾지 말자. 식물을 사랑하자.";
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

		if (m_BattleStart < 10)
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
	else if (jumpDx < TILE_HEIGHT * 2)
	{
		m_outPlayerRect.moveDown(3);
	}

	if (jumpDx == TILE_HEIGHT * 2) {
		m_outPlayerRect = UTIL::IRectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, TILE_WIDTH, TILE_HEIGHT);
		isOnObjectEvent = false;
		isOnMoundJumpDown = false;
		m_blockPositionY += 2;
	}
}

void player::pushBackPocketmon(PocketMon _pocketmon)
{
	Pocketmons.push_back(std::make_shared<PocketMon>(_pocketmon));
}



