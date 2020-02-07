#include "stdafx.h"
#include "player.h"
#include "Common/GameManagers.h"

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
	std::cout << "sunwoo Scene init!" << std::endl;
	m_outPlayerRect = UTIL::IRectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, TILE_WIDTH, TILE_HEIGHT);
	CAMERAMANAGER->setCameraFocus(&m_playerRect.centerX, &m_playerRect.centerY,WINSIZEX/2,WINSIZEY/2);
	CAMERAMANAGER->update();
	bgX = 0;
	bgY = 0;

	//player img
	m_playerImg = IMAGEMANAGER->addFrameImage("playerimg", "images/player.bmp", 244, 260, 4, 3, true, RGB(255, 0, 255));

	//player Base Arrow img

	//int arrlen[] = { 1,2,3,7,8 };
	//ANIMATIONMANAGER->addAnimation("ani2", "camel", arrlen, 3, 5, true);

	int down[] = { 0 };
	int up[] = { 1 };
	int left[] = { 2 };
	int right[] = { 3 };
	ANIMANAGER->addAnimation("playerDown", "playerimg", down, 1, 1, true);
	ANIMANAGER->addAnimation("playerUp", "playerimg", up, 1, 1, true);
	ANIMANAGER->addAnimation("playerLeft", "playerimg", left, 1, 1, true);
	ANIMANAGER->addAnimation("playerRight", "playerimg", right, 1, 1, true);

	//player Move Arrow img
	ANIMANAGER->addAnimation("playerMoveDown", "playerimg", 4, 5, 1 , false, true);
	ANIMANAGER->addAnimation("playerMoveUp", "playerimg", 6, 7, 1, false, true);
	ANIMANAGER->addAnimation("playerMoveLeft", "playerimg", 8, 9, 1, false, true);
	ANIMANAGER->addAnimation("playerMoveRight", "playerimg", 10, 11, 1, false, true);


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

	m_playerBeforeArrowMemory = 0;
	m_playerCurrentArrowMemory = 0;
	return true;
}

void player::update(float _deltaTime)
{

	if(!isBattle)
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
		isLeft = false;

		if(m_playerBeforeArrowMemory==2 && m_playerCurrentArrowMemory==2)
		{
			m_blockPositionX -= 1;

			if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY) == TileType::TileTypeTree)
			{
				m_blockPositionX += 1;
			}
			else
			{
				m_playerRectMemory = m_playerRect.left;
				isAnotherMove = true;
				isMoveLeft = true;
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

			if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY) == TileType::TileTypeBush)
			{
				isBattleStart();
			}


			isLeft = true;
			isRight = false;
			isUp = false;
			isDown = false;
			isAnotherMove = false;
			isMoveLeft = false;

		}
	}
	if (KEYMANAGER->isOnceKeyUp(P1_LEFT))
	{
		
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
		isRight = false;

		if (m_playerBeforeArrowMemory == 3 && m_playerCurrentArrowMemory == 3)
		{
			m_blockPositionX += 1;

			if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY) == TileType::TileTypeTree)
			{
				m_blockPositionX -= 1;
			}
			else
			{
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
			if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY) == TileType::TileTypeBush)
			{
				isBattleStart();
			}

			isLeft = false;
			isRight = true;
			isUp = false;
			isDown = false;
			isMoveRight = false;
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
		isUp = false;

		if (m_playerBeforeArrowMemory == 1 && m_playerCurrentArrowMemory == 1)
		{
			m_blockPositionY -= 1;

			if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY) == TileType::TileTypeTree)
			{
				m_blockPositionY += 1;
			}
			else
			{
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

			if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY) == TileType::TileTypeBush)
			{
				isBattleStart();
			}
			isLeft = false;
			isRight = false;
			isUp = true;
			isDown = false;
			isMoveUp = false;
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
	}
	else if (KEYMANAGER->isStayKeyDown(P1_DOWN) && !isMoveDown && !isAnotherMove && m_CurrentTime >0.2f)
	{
		m_playerCurrentArrowMemory = 0;
		isDown = false;

		if (m_playerBeforeArrowMemory == 0 && m_playerCurrentArrowMemory == 0)
		{
			m_blockPositionY += 1;

			if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY) == TileType::TileTypeTree)
			{
				m_blockPositionY -= 1;
			}
			else
			{
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
			m_playerRect.moveDown(5);
		}
		else
		{

			if (MAPMANGER->getTileTypeFromIndex(m_blockPositionX, m_blockPositionY) == TileType::TileTypeBush)
			{
				isBattleStart();
			}
			isLeft = false;
			isRight = false;
			isUp = false;
			isDown = true;
			isMoveDown = false;
			isAnotherMove = false;


			
		}
	}
		if (isMoveDown)ANIMANAGER->start("playerMoveDown");
		else if (!isMoveDown)ANIMANAGER->stop("playerMoveDown");
		if (isMoveUp)ANIMANAGER->start("playerMoveUp");
		else if (!isMoveUp)ANIMANAGER->stop("playerMoveUp");
		if (isMoveLeft)ANIMANAGER->start("playerMoveLeft");
		else if (!isMoveLeft)ANIMANAGER->stop("playerMoveLeft");
		if (isMoveRight)ANIMANAGER->start("playerMoveRight");
		else if (!isMoveRight)ANIMANAGER->stop("playerMoveRight");

		if (isDown)ANIMANAGER->start("playerDown");
		else if (!isDown)ANIMANAGER->stop("playerDown");
		if (isUp)ANIMANAGER->start("playerUp");
		else if (!isUp)ANIMANAGER->stop("playerUp");
		if (isLeft)ANIMANAGER->start("playerLeft");
		else if (!isLeft)ANIMANAGER->stop("playerLeft");
		if (isRight)ANIMANAGER->start("playerRight");
		else if (!isRight)ANIMANAGER->stop("playerRight");
	}

	if (isBattle)
	{
	
		isMoveLeft = false;
		isMoveRight = false;
		isMoveUp = false;
		isMoveDown = false;
		isBattle = false;
		BATTLEMANAGER->battleStart();

	}
	CAMERAMANAGER->update();
}

void player::render(HDC hdc)
{
	
}

void player::afterRender(HDC hdc)
{

}

void player::debugRender(HDC hdc)
{
	//player
	UTIL::DrawColorRect(hdc, m_outPlayerRect, RGB(153, 255, 30), true);
	if (isMoveDown)
		m_playerImg->aniRender(hdc, m_outPlayerRect.left, m_outPlayerRect.top, m_aniplayerMoveDown);
	else if (isMoveUp)
		m_playerImg->aniRender(hdc, m_outPlayerRect.left, m_outPlayerRect.top, m_aniplayerMoveUp);
	else if (isMoveLeft)
		m_playerImg->aniRender(hdc, m_outPlayerRect.left, m_outPlayerRect.top, m_aniplayerMoveLeft);
	else if (isMoveRight)
		m_playerImg->aniRender(hdc, m_outPlayerRect.left, m_outPlayerRect.top, m_aniplayerMoveRight);
	else if (isDown)
		m_playerImg->aniRender(hdc, m_outPlayerRect.left, m_outPlayerRect.top, m_aniplayerDown);
	else if (isUp)
		m_playerImg->aniRender(hdc, m_outPlayerRect.left, m_outPlayerRect.top, m_aniplayerUp);
	else if (isLeft)
		m_playerImg->aniRender(hdc, m_outPlayerRect.left, m_outPlayerRect.top, m_aniplayerLeft);
	else if (isRight)
		m_playerImg->aniRender(hdc, m_outPlayerRect.left, m_outPlayerRect.top, m_aniplayerRight);

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

		if (m_BattleStart < 7)
		{
			isBattle = true;
	
		}
		else
		{
			isBattle = false;
		
		}
	}
}






