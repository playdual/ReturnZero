#include "stdafx.h"
#include "sceneManager.h"
#include "Game/GameScene/BattleScene.h"
DEFINITION_SINGLE(SceneManager)

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

bool SceneManager::init()
{
	_currentScene = nullptr;
	return true;
}

void SceneManager::release()
{
	for (auto iter = _mSceneList.begin(); iter != _mSceneList.end(); ) {
		if (iter->second != nullptr){
			if (iter->second == _currentScene)
				iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mSceneList.erase(iter);
		}
		else iter++;
	}
	_mSceneList.clear();
}

void SceneManager::update(float deltaTime)
{
	if (_currentScene)
		_currentScene->update(deltaTime);
}

void SceneManager::render(HDC hdc)
{
	if (_currentScene)
		_currentScene->render(hdc);
}

void SceneManager::afterRender(HDC hdc)
{
	if (_currentScene)
		_currentScene->afterRender(hdc);
}

void SceneManager::debugRender(HDC hdc)
{
	if (_currentScene)
		_currentScene->debugRender(hdc);
}

Scene * SceneManager::addScene(std::string sceneName, Scene* scene) {
	
	if(!scene) 
		return nullptr;
	
	_mSceneList.insert(make_pair(sceneName, scene));
 	return scene;
}

bool SceneManager::changeScene(std::string sceneName)
{
	miSceneList find = _mSceneList.find(sceneName);

	//占쏙옙찾占쏙옙占쏙옙 E_FAIL
	if (find == _mSceneList.end())
		return false;

	//占쌕꾸뤄옙占승억옙占쏙옙 占쏙옙占쏙옙占쏙옙繭占?占쏙옙占싣듸옙 E_FAIL
	if (find->second == _currentScene)
		return false;

	//占쏙옙占쏙옙占쏙옙占?占쌉다몌옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙 占쏙옙占쏙옙 占십깍옙화占싹곤옙 占쏙옙占쏙옙占쏙옙占쏙옙.
	if (SUCCEEDED(find->second->init()))
	{
		//혹占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쌍다몌옙 占쏙옙占쏙옙占쏙옙
		if (_currentScene)_currentScene->release();

		_currentScene = find->second;
		return S_OK;
	}

	return false;
}

bool SceneManager::scenePush(std::string sceneName)
{
	auto find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end())
		return false;

	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;
		sceneStack.push(find->second);

		return true;
	}
}

bool SceneManager::battleScenePush(std::shared_ptr<player> _player, std::shared_ptr<player> _npc)
{
	auto find = _mSceneList.find("battle");

	if (SUCCEEDED(find->second->init(_player, _npc)))
	{
		_currentScene = find->second;
		sceneStack.push(find->second);

		return true;
	}
	return false;
}

bool SceneManager::battleScenePush(std::shared_ptr<player> _player, PocketMon & _pocketMon)
{
	auto find = _mSceneList.find("battle");

	if (SUCCEEDED(find->second->init(_player, _pocketMon)))
	{
		_currentScene = find->second;
		sceneStack.push(find->second);

		return true;
	}
}

bool SceneManager::scenePop()
{
	if (sceneStack.size() > 1) {
		sceneStack.top()->release();
		sceneStack.pop();
		_currentScene = sceneStack.top();
	}
	return true;
}

ItemInfo SceneManager::scenePop(bool _isGetInfom)
{
	ItemInfo ret;
	if (sceneStack.size() > 1) {
		ret = sceneStack.top()->getItemInfo();
		sceneStack.top()->release();
		sceneStack.pop();
		_currentScene = sceneStack.top();
	}
	return ret;
}

