#include "stdafx.h"
#include "TownScene.h"

TownScene::TownScene()
{
}


TownScene::~TownScene()
{
}

bool TownScene::init()
{
	SOUNDMANAGER->playSound("bgsound", Channel::eChannelBgm);
	m_image = IMAGEMANAGER->findImage("bg");
	m_count = 0;
	return true;
}

void TownScene::update(float _deltaTime)
{
	SOUNDMANAGER->update();
	if (KEYMANAGER->isOnceKeyDown(P1_LEFT))
	{
		BATTLEMANAGER->battleStart();
	}
	m_count++;
}

void TownScene::render(HDC hdc)
{
	m_image->render(hdc);
	char str[111];
	wsprintf(str, "%d", m_count);
	TextOut(hdc, 200, 200, str, strlen(str));
}

void TownScene::afterRender(HDC hdc)
{
}

void TownScene::debugRender(HDC hdc)
{
}

void TownScene::release()
{
}
