#pragma once
#include "Game/GameScene/Scene.h"
#include "Game/GameObject/Character/player.h"
#include "Game/GameObject/Pocketmon/PocketMon.h"

class SceneManager {
public:
	bool init();
	void release();

public:
	void update(float deltaTime);
	void render(HDC hdc);
	void afterRender(HDC hdc);
	void debugRender(HDC hdc);

public:
	class Scene* addScene(std::string sceneName, Scene* scene);
	bool changeScene(std::string sceneName);
	Scene* getCurScene() { return _currentScene; }
	bool scenePush(std::string sceneName);
	bool battleScenePush(std::shared_ptr<player> _player, std::shared_ptr<player> _npc);
	bool battleScenePush(std::shared_ptr<player> _player, PocketMon& _pocketMon);
	
	bool scenePop();
	bool scenePop(bool _dummy);
	bool scenePush(std::string sceneName, void* pushInfo, bool isOnBattleScene);
	void eraseLastInfo();
	void* getLastSceneReturnInfo() { return m_lastSceneReturnInfo; }

private:
	typedef std::map<std::string, Scene*> mSceneList;
	typedef std::map<std::string, Scene*>::iterator miSceneList;

private:
	Scene* _currentScene = nullptr;
	mSceneList _mSceneList;
	std::stack<Scene*> sceneStack;
	void* m_lastSceneReturnInfo = nullptr;

private:
	DECLARE_SINGLE(SceneManager)
};

#define SCENEMANAGER SceneManager::GetInst()
