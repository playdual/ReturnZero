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
	BATTLEMANAGER->init();
	
	return true;
}

void TownScene::update(float _deltaTime)
{
	SOUNDMANAGER->update();
}

void TownScene::render(HDC hdc)
{
	m_image->render(hdc);
	BATTLEMANAGER->render(hdc);
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
