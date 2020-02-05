#include"stdafx.h"
#include "BattleManager.h"

DEFINITION_SINGLE(BattleManager)

BattleManager::BattleManager()
{
}

BattleManager::~BattleManager()
{
}

HRESULT BattleManager::init()
{
	testRect = UTIL::IRectMake(100, 100, 100, 100);
	return true;
}

void BattleManager::release()
{
}

void BattleManager::update(float deltaTime)
{
}

void BattleManager::render(HDC hdc)
{
	testRect = UTIL::IRectMake(100, 100, 100, 100);
	UTIL::DrawColorRect(hdc, testRect, true, RGB(150, 150, 150));
}

void BattleManager::afterRender(HDC hdc)
{
}

void BattleManager::debugRender(HDC hdc)
{
}
