#include "stdafx.h"
#include "MainGame.h"
#include "GameScene/MapToolScene.h"

MainGame::MainGame()
{
}
MainGame::~MainGame()
{
}
void MainGame::myloadImage(std::string defaultName, std::string path, int _size)
{
	std::string bmp = ".bmp";
	path += '/';
	for (int i = 1; i <= _size; ++i) {
		std::string key = defaultName + std::to_string(i);
		IMAGEMANAGER->addImage(key, (path + key + bmp).c_str(), 50, 50, true, RGB(255, 0, 255));
		std::string tKey = key + 't';
		IMAGEMANAGER->addImage(tKey, (path + key + bmp).c_str(), 100, 100, true, RGB(255, 0, 255));
	}
}

HRESULT MainGame::init()
{
	GameNode::init();
	//add rsc
	IMAGEMANAGER->addImage("Bush1",			"Images/Tile/Bush/Bush1.bmp", 50, 50);
	IMAGEMANAGER->addImage("Bush1t",		"Images/Tile/Bush/Bush1.bmp", 100, 100);
	IMAGEMANAGER->addImage("GrassTile1",	"Images/Tile/GrassTile/GrassTile1.bmp", 50, 50);
	IMAGEMANAGER->addImage("GrassTile1t",	"Images/Tile/GrassTile/GrassTile1.bmp", 100, 100);
	IMAGEMANAGER->addImage("Tree1Bottom",	"Images/Tile/Tree/Tree1Bottom.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Tree1Bottomt",	"Images/Tile/Tree/Tree1Bottom.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Tree1Top",		"Images/Tile/Tree/Tree1Top.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Tree1Topt",		"Images/Tile/Tree/Tree1Top.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TvTop",			"Images/afterRender/TvTop.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TvTopt",		"Images/afterRender/TvTop.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Flower",	"Images/Tile/Object/Flower1Frame.bmp", 250, 50, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Flowert",	"Images/Tile/Object/Flower1Frame.bmp", 500, 100, 5, 1, true, RGB(255, 0, 255));

	std::string house = "House";
	std::string BuildingPath = "Images/Tile/Buildings/";
	std::string bmp = ".bmp";
	for (int i = 0; i < 5; ++i) {
		for (int j = 1; j < 6; ++j) {
			std::string HouseKey = house + std::to_string(i) + std::to_string(j);
			IMAGEMANAGER->addImage(HouseKey, (BuildingPath + HouseKey + bmp).c_str(),  50, 50, true, RGB(255, 0, 255));
			std::string tHouseKey = HouseKey + 't';
			IMAGEMANAGER->addImage(tHouseKey, (BuildingPath + HouseKey + bmp).c_str(), 100, 100, true, RGB(255, 0, 255));
		}
	}

	myloadImage("RedHouse_2F_", "Images/Tile/TechoTownInner/RedHouse_2F", 100);
	myloadImage("profOhouseTop", "Images/afterRender", 7);
	myloadImage("House0", "Images/afterRender", 5);
	myloadImage("TechoTown_", "Images/TechoTown", 480);
	myloadImage("MailBox", "Images/Tile/Object", 2);
	myloadImage("BigTree", "Images/afterRender", 2);
	myloadImage("BedTop", "Images/afterRender", 3);

	std::string name;
	int width, height;
	//std::cin >> name >> width >> height;

	//add Scene
	SCENEMANAGER->addScene("MapTool", new MapToolScene(name, width, height));
	CAMEARAMANAGER->setCameraBox(100, 100, 1200, 700);
	SCENEMANAGER->changeScene("MapTool");

	return S_OK;
}

void MainGame::release()
{
	GameNode::release();
}  

void MainGame::update()
{
	GameNode::update();
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
	if (SCENEMANAGER->getCurScene()) {
		return SCENEMANAGER->getCurScene()->MainProc(hWnd, iMessage, wParam, lParam);
	}
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
		return DefWindowProc(hWnd, iMessage, wParam, lParam);
	}
}