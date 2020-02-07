#include "stdafx.h"
#include "MainGame.h"
#include "GameScene/TownScene.h"
#include "GameScene/BattleScene.h"

MainGame::MainGame()
{ 
	
}
MainGame::~MainGame()
{
	
}

HRESULT MainGame::init()
{
	GameNode::init();
	MAPMANGER->init();

	//add Scene
	IMAGEMANAGER->addImage("bg", "Images/temp.bmp", 0, 0, WINSIZEX, WINSIZEY);
	SOUNDMANAGER->addStream("bgs", "Sounds/NewBarkTown.mp3", true);

	SCENEMANAGER->addScene("town", new TownScene);
	SCENEMANAGER->addScene("battle", new BattleScene);
	SCENEMANAGER->scenePush("town");


	inven = std::make_shared<Inventory>();
	inven->init();

	SCENEMANAGER->addScene("인벤씬",new InvenScene(inven));
 	SCENEMANAGER->changeScene("인벤씬"); 
	
	sceneInit = true;





	return S_OK;
}

void MainGame::release()
{
	GameNode::release();
	MAPMANGER->release();
	MAPMANGER->Destroy();
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

	//SCENEMANAGER->render(getMemDC());
	//SCENEMANAGER->afterRender(getMemDC());
	//EFFECTMANAGER->render(getMemDC());
	//if(m_showRect)
	//	SCENEMANAGER->debugRender(getMemDC());
	//if (m_showFPS)
	//	TIMEMANAGER->render(getMemDC());

	//getBackBuffer()->render(getHDC(), 0, 0);

	//invenScene->debugRender(getHDC());
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
