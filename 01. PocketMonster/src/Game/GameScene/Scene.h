#pragma once
#include "stdafx.h"
#include "Game/GameObject/Pocketmon/PocketMon.h"
#include "Game/GameObject/Character/player.h"

#include "Game/GameTypes.h"
class Scene {
public:
 	Scene() {};
	virtual ~Scene() {};

public:
	virtual bool init() = 0;
	virtual bool init(std::shared_ptr<class player> _player, std::shared_ptr<player> _npc) { return true; };
	virtual bool init(std::shared_ptr<player> _player, class PocketMon& _pocketmon) { return true; };
	virtual bool init(void* _info, bool isOnBattle) { return true; }
	virtual void update(float _deltaTime) = 0;
	virtual void release() = 0;

public:
	virtual void render(HDC hdc) = 0;
	virtual void afterRender(HDC hdc) = 0;
	virtual void debugRender(HDC hdc) = 0;
	virtual void* getResult() { return m_sceneResult; }
	void isOnChange() { isUpdateLastSceneData = false; }

protected:
	void* m_sceneResult = nullptr;
	bool isUpdateLastSceneData = false;

protected:
	bool isFromBattleScene = false;   // 공통 

public:
	virtual LRESULT SceneProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};
