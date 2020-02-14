#include "stdafx.h"
#include "player.h"
#include "Common/GameManagers.h"
#include "Game/GameScene/PocketmonBagScene.h"

player::player()
{
	/*m_blockPositionX = blockX;
	m_blockPositionY = blockY;

	m_playerRect.left = blockX * TILE_WIDTH;
	m_playerRect.right = blockX * TILE_WIDTH + TILE_WIDTH;
	m_playerRect.top = blockY * TILE_HEIGHT;
	m_playerRect.bottom = blockY * TILE_HEIGHT + TILE_HEIGHT;

	m_outPlayerRect = UTIL::IRectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);*/
}


player::~player()
{
}

bool player::init()
{
	std::cout << "Player init!" << std::endl;
	m_outPlayerRect = UTIL::IRectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, TILE_WIDTH, TILE_HEIGHT);
	CAMERAMANAGER->setCameraFocus(&m_playerRect.centerX, &m_playerRect.centerY,WINSIZEX/2,WINSIZEY/2);
	CAMERAMANAGER->update();
	bgX = 0;
	bgY = 0;

	

	//player img
	m_playerImg = IMAGEMANAGER->addFrameImage("playerimg", "images/newPlayer.bmp", 305, 510, 4, 5, true, RGB(255, 0, 255));

	int down[] = { 0 };
	int up[] = { 1 };
	int left[] = { 2 };
	int right[] = { 3 };
	ANIMANAGER->addAnimation("playerDown", "playerimg", down, 1, 1, true);
	ANIMANAGER->addAnimation("playerUp", "playerimg", up, 1, 1, true);
	ANIMANAGER->addAnimation("playerLeft", "playerimg", left, 1, 1, true);
	ANIMANAGER->addAnimation("playerRight", "playerimg", right, 1, 1, true);

	//player Move Arrow img
	ANIMANAGER->addAnimation("playerMoveDown", "playerimg", 4, 7, 4 , false, true);
	ANIMANAGER->addAnimation("playerMoveUp", "playerimg", 8, 11, 4, false, true);
	ANIMANAGER->addAnimation("playerMoveLeft", "playerimg", 12, 15, 4, false, true);
	ANIMANAGER->addAnimation("playerMoveRight", "playerimg", 16, 19, 4, false, true);


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

	Pocketmons.push_back(std::make_shared<PocketMon>(POCKETMONMANAGER->genPocketMon("Charmander", 15)));
	Pocketmons.push_back(std::make_shared<PocketMon>(POCKETMONMANAGER->genPocketMon("Squirtle", 31)));
	/*Pocketmons.push_back(std::make_shared<PocketMon>(POCKETMONMANAGER->genPocketMon("Bulbasaur", 8)));
	Pocketmons.push_back(std::make_shared<PocketMon>(POCKETMONMANAGER->genPocketMon("Pidgey", 8)));
	Pocketmons.push_back(std::make_shared<PocketMon>(POCKETMONMANAGER->genPocketMon("Poliwag", 8)));
	Pocketmons.push_back(std::make_shared<PocketMon>(POCKETMONMANAGER->genPocketMon("Pikachu", 8)));*/

	m_playerBeforeArrowMemory = 0;
	m_playerCurrentArrowMemory = 0;

	SCENEMANAGER->addScene("PocketmonBagScene", new PocketmoninfoScene(Pocketmons));

	return true;
}

void player::update(float _deltaTime)
{
	//temp
	if (KEYMANAGER->isOnceKeyDown(P1_USEITEM)) {
		Pocketmons.push_back(std::make_shared<PocketMon>(POCKETMONMANAGER->genPocketMon("Squirtle", 31)));
	}
	if (!ismenu)
	{	if (KEYMANAGER->isOnceKeyDown(GAME_MENU))
		{
			ismenu = true;
		}
	}
	else if (ismenu)
	{
		if (KEYMANAGER->isOnceKeyDown(GAME_MENUPROTO) || KEYMANAGER->isOnceKeyDown(P1_X))
		{
			ismenu = false;
		}
	}

	if(!isBattle && !ismenu)
	{
		m_CurrentTime += _deltaTime;


	if (KEYMANAGER->isOnceKeyDown(P1_LEFT) && m_playerBeforeArrowMemory != 2)
	{
		m_playerBeforeArrowMemory = 2;
		isLeft = true;
		isRight = false;
		isUp = false;
		isDown = false;

		m_CurrentTime = 0;

	}
	else if (KEYMANAGER->isStayKeyDown(P1_LEFT) && !isMoveLeft && !isAnotherMove && m_CurrentTime>0.2f)
	{
		m_playerCurrentArrowMemory = 2;
	

		if(m_playerBeforeArrowMemory==2 && m_playerCurrentArrowMemory==2)
		{
			
			if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX-1, m_blockPositionY) == TileType::TileTypeFloor||
				MAPMANGER->getTileTypeFromIndex(m_blockPositionX-1, m_blockPositionY) == TileType::TileTypeNextMap ||
				MAPMANGER->getTileTypeFromIndex(m_blockPositionX-1, m_blockPositionY) == TileType::TileTypeBush )
			{
				isLeft = false;
				m_playerRectMemory = m_playerRect.left;
				isAnotherMove = true;
				isMoveLeft = true;
				isMoveLeftTest = true;
			}
		}
	}
	if (isMoveLeft)
	{

		if (m_playerRect.left > m_playerRectMemory - TILE_WIDTH)
		{
			m_playerRect.moveLeft(5);
		}
		else
		{

			if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX-1, m_blockPositionY) == TileType::TileTypeBush)
			{
				isBattleStart();
			}

			else if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX-1, m_blockPositionY) == TileType::TileTypeNextMap)
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

	if (KEYMANAGER->isOnceKeyDown(P1_RIGHT) && m_playerBeforeArrowMemory != 3)
	{
		m_playerBeforeArrowMemory = 3;
		isLeft = false;
		isRight = true;
		isUp = false;
		isDown = false;
		m_CurrentTime = 0;

	}
	else if (KEYMANAGER->isStayKeyDown(P1_RIGHT) && !isMoveRight && !isAnotherMove && m_CurrentTime > 0.2f)
	{
		m_playerCurrentArrowMemory = 3;
		

		if (m_playerBeforeArrowMemory == 3 && m_playerCurrentArrowMemory == 3)
		{

			if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX + 1, m_blockPositionY) == TileType::TileTypeFloor ||
				MAPMANGER->getTileTypeFromIndex(m_blockPositionX + 1, m_blockPositionY) == TileType::TileTypeNextMap ||
				MAPMANGER->getTileTypeFromIndex(m_blockPositionX + 1, m_blockPositionY) == TileType::TileTypeBush )
			{
				isRight = false;
				m_playerRectMemory = m_playerRect.right;
				isAnotherMove = true;
				isMoveRight = true;
				
			}
		}
	}
	if (isMoveRight)
	{
	
		if (m_playerRect.right < m_playerRectMemory + TILE_WIDTH)
		{
			m_playerRect.moveRight(5);
		}
		else
		{
			if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX+1, m_blockPositionY) == TileType::TileTypeBush)
			{
				isBattleStart();
			}

			else if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX+1, m_blockPositionY) == TileType::TileTypeNextMap)
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
	if (KEYMANAGER->isOnceKeyDown(P1_UP) && m_playerBeforeArrowMemory != 1 )
	{
		m_playerBeforeArrowMemory = 1;
		isLeft = false;
		isRight = false;
		isUp = true;
		isDown = false;
		m_CurrentTime = 0;
	}
	else if (KEYMANAGER->isStayKeyDown(P1_UP) && !isMoveUp && !isAnotherMove && m_CurrentTime >0.2f)
	{
		m_playerCurrentArrowMemory = 1;
	

		if (m_playerBeforeArrowMemory == 1 && m_playerCurrentArrowMemory == 1)
		{
		
			if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY - 1) == TileType::TileTypeFloor ||
				MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY - 1) == TileType::TileTypeNextMap ||
				MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY - 1) == TileType::TileTypeBush )
			{
				isUp = false;
				m_playerRectMemory = m_playerRect.top;
				isAnotherMove = true;
				isMoveUp = true;
			}
		}
	}
	if (isMoveUp)
	{
		if (m_playerRect.top > m_playerRectMemory - TILE_HEIGHT)
		{
			m_playerRect.moveUp(5);
		}
		else
		{

			if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY-1) == TileType::TileTypeBush)
			{
				isBattleStart();
			}

			else if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY-1) == TileType::TileTypeNextMap)
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
	if (KEYMANAGER->isOnceKeyDown(P1_DOWN) && m_playerBeforeArrowMemory != 0)
	{
		m_playerBeforeArrowMemory = 0;
		isLeft = false;
		isRight = false;
		isUp = false;
		isDown = true;
		m_CurrentTime = 0;
	}
	else if (KEYMANAGER->isStayKeyDown(P1_DOWN) && !isMoveDown && !isAnotherMove && m_CurrentTime >0.2f)
	{
		m_playerCurrentArrowMemory = 0;
	

		if (m_playerBeforeArrowMemory == 0 && m_playerCurrentArrowMemory == 0)
		{

			if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY + 1) == TileType::TileTypeFloor ||
				MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY + 1) == TileType::TileTypeNextMap ||
				MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY + 1) == TileType::TileTypeBush )
			{
				isDown = false;
				m_playerRectMemory = m_playerRect.bottom;
				isAnotherMove = true;
				isMoveDown = true;
			}
		}
	}
	if (isMoveDown)
	{
		if (m_playerRect.bottom < m_playerRectMemory + TILE_HEIGHT)
		{
			isAfter = false;
			m_playerRect.moveDown(5);
		}
		else
		{

			if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY+1) == TileType::TileTypeBush)
			{
				isBattleStart();
			}

			else if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY+1) == TileType::TileTypeNextMap)
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
		if (isMoveDown)ANIMANAGER->resume("playerMoveDown");
		else if (!isMoveDown)ANIMANAGER->pause("playerMoveDown");
		if (isMoveUp)ANIMANAGER->resume("playerMoveUp");
		else if (!isMoveUp)ANIMANAGER->pause("playerMoveUp");
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

	if (isMoveDown)
		m_playerImg->aniRender(hdc, m_outPlayerRect.left, m_outPlayerRect.top+ PLAYER_OFFSETY, m_aniplayerMoveDown);
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
		srand(time(NULL));
		m_BattleStart = rand() % 10;

		if (m_BattleStart < 3)
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



