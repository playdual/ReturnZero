#include "stdafx.h"
#include "IntroScene.h"

IntroScene::IntroScene()
{
}

IntroScene::~IntroScene()
{
}

bool IntroScene::init()
{
	SOUNDMANAGER->playSound("Title", Channel::eChannelBgm);
	m_IntroBg = IMAGEMANAGER->findImage("introBg");
	m_IntroFire =IMAGEMANAGER->findImage("introFire");
	m_pokemonMark = IMAGEMANAGER->findImage("pokemonMark");
	m_pushStart = IMAGEMANAGER->findImage("pushStart");
	m_notice = IMAGEMANAGER->findImage("Notice");
	m_alpha = IMAGEMANAGER->findImage("alpha");
	m_alphaTwo = IMAGEMANAGER->findImage("alpha");
	m_FireOne = UTIL::IRectMake(-15, 343, 300, 300);
	m_FireTwo = UTIL::IRectMake(902, 343, 300, 300);
	return true;
}

void IntroScene::release()
{
}

void IntroScene::update(float _deltaTime)
{
	if (m_page == 0)
	{
		if (KEYMANAGER->isOnceKeyDown(P1_Z) || KEYMANAGER->isOnceKeyDown(GAME_MENU))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);
			m_page = 1;
		}


		m_pushTemp = TIMEMANAGER->getWorldTime();

		if (m_pushTemp % 2 == 0)
		{
			isPushButton = true;
		}
		else
		{
			isPushButton = false;
		}
		pastTime += _deltaTime;
		if (pastTime > frameDelay) {
			if (m_pocketMonFrameIdx == 0) {
				m_pocketMonFrameIdx = 1;
			}
			else if (m_pocketMonFrameIdx == 1)
			{
				m_pocketMonFrameIdx = 2;
			}
			else if (m_pocketMonFrameIdx == 2)
			{
				m_pocketMonFrameIdx = 0;
			}

			pastTime = 0;
		}

		pastTime1 += _deltaTime;
		if (pastTime1 > frameDelay) {
			if (m_pocketMonMarkFrameIdx == 0) {
				m_pocketMonMarkFrameIdx = 1;
			}
			else if (m_pocketMonMarkFrameIdx == 1)
			{
				m_pocketMonMarkFrameIdx = 2;
			}
			else if (m_pocketMonMarkFrameIdx == 2)
			{
				m_pocketMonMarkFrameIdx = 3;
			}
			else if (m_pocketMonMarkFrameIdx == 3)
			{
				m_pocketMonMarkFrameIdx = 4;
			}
			else if (m_pocketMonMarkFrameIdx == 4)
			{
				m_pocketMonMarkFrameIdx = 5;
			}
			else if (m_pocketMonMarkFrameIdx == 5)
			{
				m_pocketMonMarkFrameIdx = 0;
			}

			pastTime1 = 0;
		}
	}

	if (m_page == 1)
	{
		SOUNDMANAGER->stopChannel(Channel::eChannelBgm);
		if(m_alphaValue>0)m_alphaValue -= 1;

		if (KEYMANAGER->isOnceKeyDown(P1_Z))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);
			isStartGame = true;
		}
	}

	if (isStartGame)
	{
		if (m_alphaValueTwo < 255)m_alphaValueTwo += 1;
	}

	if (m_alphaValueTwo >= 255)
	{
		SCENEMANAGER->changeScene("town");
	}



}

void IntroScene::render(HDC hdc)
{
	if (m_page == 0)
	{
		m_IntroBg->render(hdc, 0, 0);
		m_IntroFire->frameRender(hdc, m_FireOne.left, m_FireOne.top, 0, m_pocketMonFrameIdx);
		m_IntroFire->frameRender(hdc, m_FireTwo.left, m_FireTwo.top, 0, m_pocketMonFrameIdx);
		m_pokemonMark->frameRender(hdc, 30, 60, m_pocketMonMarkFrameIdx, 0);

		if (isPushButton)
		{
			m_pushStart->render(hdc, WINSIZEX / 2 - 220, -5);
		}
	}
	if (m_page == 1)
	{

		m_notice->render(hdc, 0, 0);
		UTIL::PrintText(hdc, "Notice", "소야바른9", WINSIZEX/2-75, 0,90, RGB(208, 208, 200), true, RGB(0, 0, 0));
		UTIL::PrintText(hdc, "Notice", "소야바른9", WINSIZEX/2-80, 0,90, RGB(0, 0, 0), true, RGB(0, 0, 0));

		UTIL::PrintText(hdc, "당신은 이제 포켓몬 세계의 주인공이 됩니다.", "소야바른9", 85, 150, 70, RGB(208, 208, 200), true, RGB(0, 0, 0));
		UTIL::PrintText(hdc, "당신은 이제 포켓몬 세계의 주인공이 됩니다.", "소야바른9", 80, 150, 70, RGB(0, 0, 0), true, RGB(0, 0, 0));

		UTIL::PrintText(hdc, "주인공이 된 당신은 숲 풀이나 동굴 등에서", "소야바른9", 85, 230, 70, RGB(208, 208, 200), true, RGB(0, 0, 0));
		UTIL::PrintText(hdc, "주인공이 된 당신은 숲 풀이나 동굴 등에서", "소야바른9", 80, 230, 70, RGB(0, 0, 0), true, RGB(0, 0, 0));


		UTIL::PrintText(hdc, "포켓몬을 만나고, 전투를 하거나 친구가 될 수", "소야바른9", 85, 310, 70, RGB(208, 208, 200), true, RGB(0, 0, 0));
		UTIL::PrintText(hdc, "포켓몬을 만나고, 전투를 하거나 친구가 될 수", "소야바른9", 80, 310, 70, RGB(0, 0, 0), true, RGB(0, 0, 0));

		UTIL::PrintText(hdc, "있습니다.", "소야바른9", 85, 390, 70, RGB(208, 208, 200), true, RGB(0, 0, 0));
		UTIL::PrintText(hdc, "있습니다.", "소야바른9", 80, 390, 70, RGB(0, 0, 0), true, RGB(0, 0, 0));

		UTIL::PrintText(hdc, "포켓몬과의 처음 조우하는 설레는 만남을 ", "소야바른9", 85, 470, 70, RGB(208, 208, 200), true, RGB(0, 0, 0));
		UTIL::PrintText(hdc, "포켓몬과의 처음 조우하는 설레는 만남을 ", "소야바른9", 80, 470, 70, RGB(0, 0, 0), true, RGB(0, 0, 0));

		UTIL::PrintText(hdc, "지금부터 시작해보세요!", "소야바른9", 85, 550, 70, RGB(208, 208, 200), true, RGB(0, 0, 0));
		UTIL::PrintText(hdc, "지금부터 시작해보세요!", "소야바른9", 80, 550, 70, RGB(0, 0, 0), true, RGB(0, 0, 0));

		UTIL::PrintText(hdc, "Team - Return Zero", "소야바른9", 455, 650, 70, RGB(208, 208, 200), true, RGB(0, 0, 0));
		UTIL::PrintText(hdc, "Team - Return Zero", "소야바른9", 450, 650, 70, RGB(0, 0, 0), true, RGB(0, 0, 0));

		if(m_alphaValue != 0)
		m_alpha->alphaRender(hdc, 0, 0, m_alphaValue);

		if (isStartGame)
		{
			m_alphaTwo->alphaRender(hdc, 0, 0, m_alphaValueTwo);
		}

		
	}
}

void IntroScene::afterRender(HDC hdc)
{
}

void IntroScene::debugRender(HDC hdc)
{
}
