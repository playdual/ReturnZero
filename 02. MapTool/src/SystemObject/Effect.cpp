﻿#include "stdafx.h"
#include "Effect.h"
#include "Animation.h"
#include "Image.h"

Effect::Effect()
	:_effectImage(nullptr)
	,_effectAni(nullptr)
	,_isRunning(NULL)
	,_x(0)
	,_y(0)
{
}
Effect::~Effect()
{
}

HRESULT Effect::init(Image * effectImage, int frameW, int frameH, int FPS, float elapsedTime)
{

	//이펙트 이미지가 없을때 바로 리턴
	if (!effectImage)
		return E_FAIL;
	_effectImage = effectImage;
	_elapsedTime = elapsedTime;
	_isRunning = false;
	//이펙트 애니메이션이 없으면 새로 생성!
	if (!_effectAni)_effectAni = new Animation;

	_effectAni->init(_effectImage->getWidth(), _effectImage->getHeight(), frameW, frameH);
	_effectAni->setDefPlayFrame();
	_effectAni->setFPS(FPS);
	return S_OK;
}

void Effect::release()
{
	SAFE_DELETE(_effectAni);

}

void Effect::update()
{
	if (_isRunning)
	{
		_effectAni->frameUpdate(_elapsedTime);
	}
	//이펙트 애니메이션이 종료가 되면 멈추자
	if (!_effectAni->isPlay())
		stopEffect();
}
void Effect::render(HDC _hdc)
{
	if (_isRunning)
	{
		_effectImage->aniRender(_hdc, _x, _y, _effectAni);
	}
}

void Effect::startEffect(int x, int y)
{
	//위치 좌표를 센터 좌표로 만들기
	_x = x - (_effectAni->getFrameWidth() / 2);
	_y = y - (_effectAni->getFrameHeight() / 2);

	_isRunning = true;
	_effectAni->start();


}
void Effect::stopEffect()
{
	_isRunning = false;
}
