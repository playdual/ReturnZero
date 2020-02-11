#include "stdafx.h"
#include "MainGame.h"
#include "Common/GameManagers.h"
#include "GameScene/TownScene.h"
#include "GameScene/BattleScene.h"
#include "GameScene/InvenScene.h"
#include "GameObject/Items/Inventory.h"

MainGame::MainGame()
{ 
	
}

MainGame::~MainGame()
{
	
}

HRESULT MainGame::init()
{
	GameNode::init();
	//rsc loading

	IMAGEMANAGER->addImage("pailiFront", "Images/pocketmons/pailiFront.bmp", 60 * 3, 61 * 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pikachu", "Images/pocketmons/PikachuFront.bmp", 61 * 3, 61 * 3, true, RGB(255, 0, 255));

	MAPMANGER->init();
	ITEMMANAGER->init();
	POCKETMONMANAGER->init();




	//add Scene
	IMAGEMANAGER->addImage("bg", "Images/temp.bmp", 0, 0, WINSIZEX, WINSIZEY);
	SOUNDMANAGER->addStream("bgs", "Sounds/NewBarkTown.mp3", true);
	std::shared_ptr<Inventory> inven = std::make_shared<Inventory>();
	inven->init();

	SCENEMANAGER->addScene("town", new TownScene);
	SCENEMANAGER->addScene("battle", new BattleScene);
	SCENEMANAGER->addScene("inven",new InvenScene(inven));
	SCENEMANAGER->scenePush("town");

	SCENEMANAGER->changeScene("town");
	sceneInit = true;

	return S_OK;
}

void MainGame::release()
{
	GameNode::release();
	MAPMANGER->release();
	POCKETMONMANAGER->release();
	ITEMMANAGER->release();

	MAPMANGER->Destroy();
	POCKETMONMANAGER->Destroy();
	ITEMMANAGER->Destroy();
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
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);

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
