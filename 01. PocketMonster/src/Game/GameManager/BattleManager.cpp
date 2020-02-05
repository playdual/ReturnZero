#include"stdafx.h"
#include "BattleManager.h"
#include "Common/SystemManagers.h"

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
	m_player = std::make_shared<Character>();
	m_player->init();
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
	char str[100];
	wsprintf(str, "%s", m_player->getName().c_str());
	TextOut(hdc, 100, 100, str, strlen(str));
}

void BattleManager::afterRender(HDC hdc)
{
}

void BattleManager::debugRender(HDC hdc)
{
}

void BattleManager::battleStart()
{
	SCENEMANAGER->scenePush("battle");
}
