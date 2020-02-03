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
	SOUNDMANAGER->playSound("배경음", Channel::eChannelBgm);
	image = IMAGEMANAGER->findImage("배경");
	return true;
}

void TownScene::update(float _deltaTime)
{
	SOUNDMANAGER->update();
}

void TownScene::render(HDC hdc)
{
	image->render(hdc);
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
