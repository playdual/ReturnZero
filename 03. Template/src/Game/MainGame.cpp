#include "stdafx.h"
#include "MainGame.h"
#include "GameScene/SampleScene.h"
#include "GameScene/SceneAstar.h"
//#include "../example/ExScene/ExAnimationManagerScene.h"
//#include "../example/ExScene/ExEffectManagerScene.h"

MainGame::MainGame()
{
}
MainGame::~MainGame()
{
}

HRESULT MainGame::init()
{
	GameNode::init();
	
	//add Scene
	IMAGEMANAGER->addImage("?щ굹", "../00. Common/Images/?щ굹.bmp", 0, 0, WINSIZEX, WINSIZEY);
	SOUNDMANAGER->addStream("諛곌꼍??, "../00. Common/Sounds/?섎쭔遊?mp3", true);

	SCENEMANAGER->addScene("Sample", new SampleScene);
	SCENEMANAGER->changeScene("Sample");

	auto astar = new Astar;
	astar.init();
	SCENEMANAGER->addScene("astar", new astar);
	SCENEMANAGER->changeScene("astar");



	sceneInit = true;
	return S_OK;
}

void MainGame::release()
{
	GameNode::release();
}  

void MainGame::update()
{
	if (KEYMANAGER->isOnceKeyDown(GAME_RECTMODE))
		m_showRect = !m_showRect;
	if (KEYMANAGER->isOnceKeyDown(GAME_SHOWFPS))
		m_showFPS = !m_showFPS;

	TIMEMANAGER->update(60.f);
	deltaTime = TIMEMANAGER->getElapsedTime();
	EFFECTMANAGER->update();
	SCENEMANAGER->update(deltaTime);
	ANIMANAGER->update(deltaTime);
}

void MainGame::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	SCENEMANAGER->render(getMemDC());
	SCENEMANAGER->afterRender(getMemDC());
	EFFECTMANAGER->render(getMemDC());
	if(m_showRect)
		SCENEMANAGER->debugRender(getMemDC());
	if (m_showFPS)
		TIMEMANAGER->render(getMemDC());

	getBackBuffer()->render(getHDC(), 0, 0);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	if (sceneInit)
		return SCENEMANAGER->getCurScene()->SceneProc(hWnd, iMessage, wParam, lParam);
	else {
		switch (iMessage)
		{
		case WM_MOUSEMOVE:
			m_ptMouse.x = LOWORD(lParam);
			m_ptMouse.y = HIWORD(lParam);
			break;
		case WM_DESTROY:
			m_bLoop = false;
			PostQuitMessage(0);
			break;
		}
	}	
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}