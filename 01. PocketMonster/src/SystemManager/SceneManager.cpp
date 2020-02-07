#include "stdafx.h"
#include "sceneManager.h"
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

	//��ã���� E_FAIL
	if (find == _mSceneList.end())
		return false;

	//�ٲٷ��¾��� ������̶� ���Ƶ� E_FAIL
	if (find->second == _currentScene)
		return false;

	//������� �Դٸ� ������ ���� �� ���� �ʱ�ȭ�ϰ� ��������.
	if (SUCCEEDED(find->second->init()))
	{
		//Ȥ�� ������ ���� �ִٸ� ������
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

bool SceneManager::scenePop()
{
	if (sceneStack.size() > 1) {
		sceneStack.top()->release();
		sceneStack.pop();
		_currentScene = sceneStack.top();
	}
	return false;
}
