#include "stdafx.h"
#include "MapToolScene.h"
#include "../../vendor/Json/inc/json.h"

//general
void MapToolScene::update(float _deltaTime)
{
	cameraMove();
	if (m_ptMouse.x < UIOffset)
		TileWindowUpdate(_deltaTime);
	else
		UIupdate();
}

void MapToolScene::release()
{
	treeVector.clear();
	tileVector.clear();
	bushVector.clear();
}

void MapToolScene::render(HDC hdc)
{
	TileWindowRender(hdc);
	UIrender(hdc);
}

void MapToolScene::afterRender(HDC hdc)
{
	for (auto&e : m_Tiles)
		e->afterRender(hdc);
}

void MapToolScene::debugRender(HDC hdc)
{
}

bool MapToolScene::init()
{
	//tileSetup
	if (mapName == "TechoTown") {
		for (int i = 0; i < mapHeight; ++i) {
			for (int j = 1; j <= mapWidth; ++j) {
				std::string key = "TechoTown_" + std::to_string(i * mapWidth + j) + "t";
				auto tile = std::make_shared<Tile>();
				tile->init(TileType::TileTypeFloor, key, (j - 1), i);
				m_Tiles.push_back(tile);
			}
		}
	}
	else if (mapName == "RedHouse2F") {
		for (int i = 0; i < 9; ++i) {
			for (int j = 1; j <= 11; ++j) {
				std::string key = "RedHouse2F_" + std::to_string(i * mapWidth + j) + "t";
				auto tile = std::make_shared<Tile>();
				tile->init(TileType::TileTypeFloor, key, (j - 1), i);
				m_Tiles.push_back(tile);
			}
		}
	}
	else {
		for (int i = 0; i < mapHeight; ++i) {
			for (int j = 0; j < mapWidth; ++j) {
				auto tile = std::make_shared<Tile>();
				tile->init(TileType::TileTypeNone, "", j, i);
				m_Tiles.push_back(tile);
			}
		}
	}
	


	//ButtonSetup
	//always
	clientRect = UTIL::IRectMake(UIOffset, -10, WINSIZEX - UIOffset, WINSIZEY + 20);
	saveSelectRect = UTIL::IRectMake(1300, 700, 100, 100);
	loadSelectRect = UTIL::IRectMake(1400, 700, 100, 100);
	pageFrontButton = UTIL::IRectMake(1100, 500, 50, 50);
	pageBackButton = UTIL::IRectMake(1300, 500, 50, 50);
	resetSpecifyButtonRect = UTIL::IRectMake(1300, 0, 50, 50);
	resetTileButtonRect = UTIL::IRectMake(1350, 0, 50, 50);
	backButtonRect = UTIL::IRectMake(1400, 0, 50, 50);
	resetInnerAttributeRect = UTIL::IRectMake(1250, 0, 50, 50);
	pointResetInnerAttributeRect = UTIL::IRectMakeCenter(resetInnerAttributeRect.centerX, resetInnerAttributeRect.centerY, 10, 10);

	//in each case
	tileSelectRect = UTIL::IRectMake(1150, 100, 200, 100);
	treeSelectRect = UTIL::IRectMake(1150, 200, 200, 100);
	bushSelectRect = UTIL::IRectMake(1150, 300, 200, 100);
	setSpecifyRect = UTIL::IRectMake(1150, 400, 200, 100);
	setTileTypeRect = UTIL::IRectMake(1150, 500, 200, 100);
	setNextMapButtonRect = UTIL::IRectMake(1150, 120, 200, 100);
	setPocketMonButtonRect = UTIL::IRectMake(1150, 220, 200, 100);
	setObjectButtonRect = UTIL::IRectMake(1150, 320, 200, 100);

	tileTypeFloorRect		= UTIL::IRectMake(1100, 200, 75, 75);
	tileTypeHouseRect		= UTIL::IRectMake(1200, 200, 75, 75);
	tileTypeBushRect		= UTIL::IRectMake(1300, 200, 75, 75);
	tileTypeTreeRect		= UTIL::IRectMake(1400, 200, 75, 75);
	tileTypeNextMapRect		= UTIL::IRectMake(1100, 300, 75, 75);
	tileTypeOutRangeRect	= UTIL::IRectMake(1200, 300, 75, 75);
	tileTypeObjectRect	= UTIL::IRectMake(1300, 300, 75, 75);
	setActivateNextMapRect = UTIL::IRectMake(1150, 500, 200, 50);


	//TileBlockSetup
	treeVectorInit(6);
	tileVectorInit(6);
	bushVectorInit(6);
	resetTileSelectedAttribute();

	return true;

}


void MapToolScene::cameraMove()
{
	if (KEYMANAGER->isStayKeyDown(P1_LEFT))
		CAMEARAMANAGER->moveCamera(-3, 0);
	if (KEYMANAGER->isStayKeyDown(P1_RIGHT))
		CAMEARAMANAGER->moveCamera(3, 0);
	if (KEYMANAGER->isStayKeyDown(P1_UP))
		CAMEARAMANAGER->moveCamera(0, -3);
	if (KEYMANAGER->isStayKeyDown(P1_DOWN))
		CAMEARAMANAGER->moveCamera(0, 3);

	if (KEYMANAGER->isStayKeyDown(P1_EVENT)) {
		m_isSettedMove = true;
	}
	else if (m_isSettedMove) {
		m_isSettedMove = false;
	}
	if (m_isSettedMove) {
		if (KEYMANAGER->isStayKeyDown(GAME_LMOUSE)) {
			m_isMouseMoveActive = true;
		}
		else if (m_isMouseMoveActive) {
			m_isMouseMoveActive = false;
		}
	}
	if (m_isSettedMove && m_isMouseMoveActive) {
		if (m_prevMouseX != m_ptMouse.x || m_prevMousey != m_ptMouse.y) {
			CAMEARAMANAGER->moveCamera(m_prevMouseX - m_ptMouse.x, m_prevMousey - m_ptMouse.y);
		}
	}

	m_prevMouseX = m_ptMouse.x;
	m_prevMousey = m_ptMouse.y;
}

void MapToolScene::treeVectorPush(std::string imageKey, TileType _type, int page, int _size, bool _afterRender)
{
	for (int i = 1; i <= _size; ++i) {
		std::string Key = imageKey + std::to_string(i);
		treeVector[page][(i - 1)].setTileAttribute(Key, _type, false);
	}
}
void MapToolScene::treeVectorInit(int _pageCount)
{
	treeSelectPage = 0;
	treeSelectPageMax = _pageCount;
	treeVector.resize(_pageCount);
	for (int i = 0; i < _pageCount; ++i) {
		treeVector[i].resize(25);
		for (int j = 0; j < 25; ++j) {
			treeVector[i][j].inUIpositionX = (j % 5) * inUiTileWidth + 1100;
			treeVector[i][j].inUIpositionY = (j / 5) * inUiTileHeight + 100;
			treeVector[i][j].rect = UTIL::IRectMake(treeVector[i][j].inUIpositionX, treeVector[i][j].inUIpositionY,
				inUiTileWidth, inUiTileHeight);
		}
	}
	TileType type = TileType::TileTypeTree;
	treeVector[0][0].setTileAttribute("Tree1Bottom", type, false);
	treeVector[0][1].setTileAttribute("Tree1Top", type, false);
	treeVectorPush("BigTree", type, 1, 2, false);

}

void MapToolScene::tileVectorPush(std::string imageKey,  TileType _type, int page, int _size, bool _afterRender)
{
	for (int i = 1; i <= _size; ++i) {
		std::string Key = imageKey + std::to_string(i);
		tileVector[page][(i - 1)].setTileAttribute(Key, _type, false);
	}
}

void MapToolScene::tileVectorInit(int _pageCount)
{
	tileSelectPage = 0;
	tileSelectPageMax = _pageCount;
	tileVector.resize(_pageCount);
	for (int i = 0; i < _pageCount; ++i) {
		tileVector[i].resize(25);
		for (int j = 0; j < 25; ++j) {
			tileVector[i][j].inUIpositionX = (j % 5) * inUiTileWidth + 1100;
			tileVector[i][j].inUIpositionY = (j / 5) * inUiTileHeight + 100;
			tileVector[i][j].rect = UTIL::IRectMake(tileVector[i][j].inUIpositionX, tileVector[i][j].inUIpositionY,
				inUiTileWidth, inUiTileHeight);
		}
	}

	TileType type = TileType::TileTypeFloor;

	//TODO : add another tile
	tileVector[0][0].setTileAttribute("GrassTile1", type, false);
	std::string House = "House";
	for (int i = 0; i < 5; ++i) {
		for (int j = 1; j < 6; ++j) {
			std::string HouseKey = House + std::to_string(i) + std::to_string(j);
			tileVector[1][i + (j - 1) * 5].setTileAttribute(HouseKey, TileType::TileTypeHouse, false);
		}
	}	
	tileVector[0][1].setTileAttribute("Flower", TileType::TileTypeFloor, false);
	tileVectorPush("TownTile", TileType::TileTypeFloor, 2, 13, false);
	tileVectorPush("MailBox", TileType::TileTypeObject, 3, 2, false);
	tileVectorPush("profOhouseTop", TileType::TileTypeHouse, 4, 7,  false);
	tileVectorPush("House0", TileType::TileTypeFloor, 5, 5, false);
}

void MapToolScene::bushVectorPush(std::string imageKey, TileType _type, int page, int _size, bool _afterRender)
{
	for (int i = 1; i <= _size; ++i) {
		std::string Key = imageKey + std::to_string(i);
		bushVector[page][(i - 1)].setTileAttribute(Key, _type, false);
	}
}

void MapToolScene::bushVectorInit(int _pageCount)
{
	bushSelectPage = 0;
	bushSelectPageMax = _pageCount;
	bushVector.resize(_pageCount);
	for (int i = 0; i < _pageCount; ++i) {
		bushVector[i].resize(25);
		for (int j = 0; j < 25; ++j) {
			bushVector[i][j].inUIpositionX = (j % 5) * inUiTileWidth + 1100;
			bushVector[i][j].inUIpositionY = (j / 5) * inUiTileHeight + 100;
			bushVector[i][j].rect = UTIL::IRectMake(tileVector[i][j].inUIpositionX, tileVector[i][j].inUIpositionY,
				inUiTileWidth, inUiTileHeight);
		}
	}
	TileType type = TileType::TileTypeBush;
	bushVector[0][0].setTileAttribute("Bush1", type, false);
}

void MapToolScene::UIupdate()
{
	if (m_mainSelect)
		mainSelectUpdate();

	if (m_tileSelect)
		tileSelectUpdate();
	if (m_bushSelect)
		bushSelectUpdate();
	if (m_treeSelect)
		treeSelectUpdate();
	if (m_specifySelect)
		specifyUpdate();
	if (m_typeSelect)
		typeSelectUpdate();

	resetTileUpdate();
	resetSpecifyUpdate();
	saveLoadUpdate();
	resetInnerAttributeUpdate();

	if (KEYMANAGER->isOnceKeyDown(GAME_K)) {
		activateSetNextMapBlock();
	}
	if (KEYMANAGER->isOnceKeyDown(GAME_L)) {
		activateSetStartPos();
	}
	if (KEYMANAGER->isOnceKeyDown(GAME_J)) {
		activateSetAfterRender();
	}
	if (m_setAfterRenderImage) {
		selectedAttribute.isAfterRender = true;
	}
	else {
		selectedAttribute.isAfterRender = false;
	}

}

void MapToolScene::mainSelectUpdate()
{
	if (UTIL::isPointRectCollision(m_ptMouse, tileSelectRect)) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			m_tileSelect = true;
			m_mainSelect = false;
		}
	}
	if (UTIL::isPointRectCollision(m_ptMouse, treeSelectRect)) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			m_treeSelect = true;
			m_mainSelect = false;

		}
	}
	if (UTIL::isPointRectCollision(m_ptMouse, bushSelectRect)) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			m_bushSelect = true;
			m_mainSelect = false;

		}
	}
	if (UTIL::isPointRectCollision(m_ptMouse, setSpecifyRect)) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			m_specifySelect = true;
			m_mainSelect = false;
		}
	}
	if (UTIL::isPointRectCollision(m_ptMouse, setTileTypeRect)) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			m_typeSelect = true;
			m_mainSelect = false;
		}
	}
}

void MapToolScene::mainSelectRender(HDC hdc)
{
	UTIL::DrawRect(hdc, tileSelectRect);
	TextOut(hdc, tileSelectRect.left + textOffsetX, tileSelectRect.top + textOffsetY,
		tileSelectStr, strlen(tileSelectStr));
	UTIL::DrawRect(hdc, treeSelectRect);
	TextOut(hdc, treeSelectRect.left + textOffsetX, treeSelectRect.top + textOffsetY,
		treeSelectStr, strlen(treeSelectStr));
	UTIL::DrawRect(hdc, bushSelectRect);
	TextOut(hdc, bushSelectRect.left + textOffsetX, bushSelectRect.top + textOffsetY,
		bushSelectStr, strlen(bushSelectStr));
	UTIL::DrawRect(hdc, setSpecifyRect);
	TextOut(hdc, setSpecifyRect.left + textOffsetX, setSpecifyRect.top + textOffsetY,
		specifySelectStr, strlen(specifySelectStr));
	UTIL::DrawRect(hdc, setTileTypeRect);
	TextOut(hdc, setTileTypeRect.left + textOffsetX, setTileTypeRect.top + textOffsetY,
		"TileType Select", strlen("TileType Select"));
}

void MapToolScene::bushSelectUpdate()
{
	backButtonUpdate();
	if (KEYMANAGER->isStayKeyDown(GAME_LMOUSE)) {
		for (auto& e : bushVector[bushSelectPage]) {
			if (UTIL::isPointRectCollision(m_ptMouse, e.rect)) {
				selectedAttribute = e.attribute;
				isSetAttribute = true;
				isSetNextMap = false;
				isSetPocketMon = false;
				break;
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown(GAME_LPAGE)) {
		bushSelectPage -= 1;
		if (bushSelectPage < 0)
			bushSelectPage = bushSelectPageMax - 1;
	}
	if (KEYMANAGER->isOnceKeyDown(GAME_RPAGE)) {
		bushSelectPage += 1;
		if (bushSelectPage >= bushSelectPageMax)
			bushSelectPage = 0;
	}
}

void MapToolScene::bushSelectRender(HDC hdc)
{
	for (auto& e : bushVector[bushSelectPage]) {
		if (e.img)
			e.img->render(hdc, e.inUIpositionX, e.inUIpositionY);
		else
			UTIL::DrawRect(hdc, e.rect);
	}
	UTIL::PrintText(hdc, "PageFront : ]", "명조", pageBackButton.left, pageBackButton.top - 20);
	UTIL::PrintText(hdc, "Pageback : [", "명조", pageBackButton.left, pageBackButton.top);
}

void MapToolScene::treeSelectUpdate()
{
	backButtonUpdate();
	if (KEYMANAGER->isStayKeyDown(GAME_LMOUSE)) {
		for (auto& e : treeVector[treeSelectPage]) {
			if (UTIL::isPointRectCollision(m_ptMouse, e.rect)) {
				selectedAttribute = e.attribute;
				isSetAttribute = true;
				isSetNextMap = false;
				isSetPocketMon = false;
				break;
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown(GAME_LPAGE)) {
		treeSelectPage -= 1;
		if (treeSelectPage < 0)
			treeSelectPage = bushSelectPageMax - 1;
	}
	if (KEYMANAGER->isOnceKeyDown(GAME_RPAGE)) {
		treeSelectPage += 1;
		if (treeSelectPage >= bushSelectPageMax)
			treeSelectPage = 0;
	}
}

void MapToolScene::treeSelectRender(HDC hdc)
{
	for (auto& e : treeVector[treeSelectPage]) {
		if (e.img)
			e.img->render(hdc, e.inUIpositionX, e.inUIpositionY, 0, 0, 50, 50);
		else
			UTIL::DrawRect(hdc, e.rect);
	}
	UTIL::PrintText(hdc, "PageFront : ]", "명조", pageBackButton.left, pageBackButton.top - 20);
	UTIL::PrintText(hdc, "Pageback : [", "명조", pageBackButton.left, pageBackButton.top);
}

void MapToolScene::tileSelectUpdate()
{
	backButtonUpdate();
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
		for (auto& e : tileVector[tileSelectPage]) {
			if (UTIL::isPointRectCollision(m_ptMouse, e.rect)) {
				selectedAttribute = e.attribute;
				isSetAttribute = true;
				isSetNextMap = false;
				isSetPocketMon = false;
				break;
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown(GAME_LPAGE)) {
		tileSelectPage -= 1;
		if (tileSelectPage < 0)
			tileSelectPage = bushSelectPageMax - 1;
	}
	if (KEYMANAGER->isOnceKeyDown(GAME_RPAGE)) {
		tileSelectPage += 1;
		if (tileSelectPage >= bushSelectPageMax)
			tileSelectPage = 0;
	}
}

void MapToolScene::tileSelectRender(HDC hdc)
{
	for (auto& e : tileVector[tileSelectPage]) {
		if (e.img)
			e.img->render(hdc, e.inUIpositionX, e.inUIpositionY, 0, 0, 50, 50);
		else
			UTIL::DrawRect(hdc, e.rect);
	}
	UTIL::PrintText(hdc, "PageFront : ]", "명조", pageBackButton.left, pageBackButton.top - 20);
	UTIL::PrintText(hdc, "Pageback : [", "명조", pageBackButton.left, pageBackButton.top);
}

void MapToolScene::specifyUpdate()
{
	backButtonUpdate();
	if (UTIL::isPointRectCollision(m_ptMouse, setPocketMonButtonRect)) {
		if (KEYMANAGER->isOnceKeyDown(GAME_LMOUSE)) {
			std::cin >> settedPocketMon;
			std::cin >> settedPocketMonLevel;
			isSetAttribute = false;
			isSetNextMap = false;
			isSetObj = false;
			isSetPocketMon = true;
			settedSpecifyStr = "PocketMon : " + settedPocketMon + " " + std::to_string(settedPocketMonLevel);
		}
	}
	if(UTIL::isPointRectCollision(m_ptMouse, setNextMapButtonRect)){
		if (KEYMANAGER->isOnceKeyDown(GAME_LMOUSE)) {
			std::cin >> settedNextMap;
			std::cin >> settedNextMapIdx.x;
			std::cin >> settedNextMapIdx.y;
			isSetAttribute = false;
			isSetNextMap = true;
			isSetPocketMon = false;
			isSetObj = false;
			settedSpecifyStr = "Next Map : " + settedNextMap + " " + std::to_string(settedNextMapIdx.x) + " " 
				+ std::to_string(settedNextMapIdx.y);
		}
	}
	if (UTIL::isPointRectCollision(m_ptMouse, setObjectButtonRect)) {
		if (KEYMANAGER->isOnceKeyDown(GAME_LMOUSE)) {
			std::cin >> settedObjName;
			isSetObj = true;
			isSetAttribute = false;
			isSetNextMap = false;
			isSetPocketMon = false;
			settedSpecifyStr = "ObjName : " + settedObjName;
		}
	}
}
void MapToolScene::typeSelectRender(HDC hdc)
{
	UTIL::DrawRect(hdc, tileTypeFloorRect);
	UTIL::PrintText(hdc, "Floor", "명조", tileTypeFloorRect.left, tileTypeFloorRect.top + 10, 10);
	UTIL::DrawRect(hdc, tileTypeHouseRect);
	UTIL::PrintText(hdc, "House", "명조", tileTypeHouseRect.left, tileTypeHouseRect.top + 10, 10);
	UTIL::DrawRect(hdc, tileTypeBushRect);
	UTIL::PrintText(hdc, "Bush", "명조", tileTypeBushRect.left, tileTypeBushRect.top + 10, 10);
	UTIL::DrawRect(hdc, tileTypeTreeRect);
	UTIL::PrintText(hdc, "Tree", "명조", tileTypeTreeRect.left, tileTypeTreeRect.top + 10, 10);
	UTIL::DrawRect(hdc, tileTypeNextMapRect);
	UTIL::PrintText(hdc, "NextMap", "명조", tileTypeNextMapRect.left, tileTypeNextMapRect.top + 10, 10);
	UTIL::DrawRect(hdc, tileTypeOutRangeRect);
	UTIL::PrintText(hdc, "OutRange", "명조", tileTypeOutRangeRect.left, tileTypeOutRangeRect.top + 10, 10);
	UTIL::DrawRect(hdc, tileTypeObjectRect);
	UTIL::PrintText(hdc, "Object", "명조", tileTypeObjectRect.left, tileTypeObjectRect.top + 10, 10);
	UTIL::DrawColorRect(hdc, PointSelectedTypeRect, RGB(0, 0, 0), true);
}				

void MapToolScene::specifyRender(HDC hdc)
{
	UTIL::DrawRect(hdc, setPocketMonButtonRect);
	TextOut(hdc, setPocketMonButtonRect.left + textOffsetX, setPocketMonButtonRect.top + textOffsetY,
		specifyPocketStr, strlen(specifyPocketStr));
	UTIL::DrawRect(hdc, setNextMapButtonRect);
	TextOut(hdc, setNextMapButtonRect.left + textOffsetX, setNextMapButtonRect.top + textOffsetY,
		specifyNextMapStr, strlen(specifyNextMapStr));
	UTIL::DrawRect(hdc, setObjectButtonRect);
	TextOut(hdc, setObjectButtonRect.left + textOffsetX, setObjectButtonRect.top + textOffsetY,
		"Input Obj Name", strlen("Input Obj Name"));


	TextOut(hdc, setNextMapButtonRect.left - 100 + textOffsetX, 100,
		settedInfo, strlen(settedInfo));
	TextOut(hdc, setNextMapButtonRect.left + textOffsetX, 100,
		settedSpecifyStr.c_str(), settedSpecifyStr.length());
}

void MapToolScene::typeSelectUpdate()
{
	backButtonUpdate();
	if(UTIL::isPointRectCollision(m_ptMouse, tileTypeFloorRect)) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			selectedTileType = TileType::TileTypeFloor;
			PointSelectedTypeRect = UTIL::IRectMakeCenter(tileTypeFloorRect.centerX, tileTypeFloorRect.centerY, 10, 10);
			settedTileType = true;
		}
	}
	if (UTIL::isPointRectCollision(m_ptMouse, tileTypeHouseRect)) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			selectedTileType = TileType::TileTypeHouse;
			PointSelectedTypeRect = UTIL::IRectMakeCenter(tileTypeHouseRect.centerX, tileTypeHouseRect.centerY, 10, 10);
			settedTileType = true;
		}
	}
	if (UTIL::isPointRectCollision(m_ptMouse, tileTypeBushRect)) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			selectedTileType = TileType::TileTypeBush;
			PointSelectedTypeRect = UTIL::IRectMakeCenter(tileTypeBushRect.centerX, tileTypeBushRect.centerY, 10, 10);
			settedTileType = true;
		}
	}
	if (UTIL::isPointRectCollision(m_ptMouse, tileTypeTreeRect)) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			selectedTileType = TileType::TileTypeTree;
			PointSelectedTypeRect = UTIL::IRectMakeCenter(tileTypeTreeRect.centerX, tileTypeTreeRect.centerY, 10, 10);
			settedTileType = true;
		}
	}
	if (UTIL::isPointRectCollision(m_ptMouse, tileTypeNextMapRect)) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			selectedTileType = TileType::TileTypeNextMap;
			PointSelectedTypeRect = UTIL::IRectMakeCenter(tileTypeNextMapRect.centerX, tileTypeNextMapRect.centerY, 10, 10);
			settedTileType = true;
		}
	}
	if (UTIL::isPointRectCollision(m_ptMouse, tileTypeOutRangeRect)) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			selectedTileType = TileType::TileTypeOutRange;
			PointSelectedTypeRect = UTIL::IRectMakeCenter(tileTypeOutRangeRect.centerX, tileTypeOutRangeRect.centerY, 10, 10);
			settedTileType = true;
		}
	}
	if (UTIL::isPointRectCollision(m_ptMouse, tileTypeObjectRect)) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			selectedTileType = TileType::TileTypeObject;
			PointSelectedTypeRect = UTIL::IRectMakeCenter(tileTypeObjectRect.centerX, tileTypeObjectRect.centerY, 10, 10);
			settedTileType = true;
		}
	}
}

void MapToolScene::activateSetNextMapBlock()
{
	if (!m_setStartPos && !m_setAfterRenderImage) {
		m_settedNextMap = !m_settedNextMap;
	}
}

void MapToolScene::activateSetStartPos()
{
	if (!m_settedNextMap && !m_setAfterRenderImage) {
		m_setStartPos = !m_setStartPos;
	}
}

void MapToolScene::activateSetAfterRender()
{
	if (!m_setStartPos && !m_settedNextMap) {
		m_setAfterRenderImage = !m_setAfterRenderImage;
	}
}

void MapToolScene::resetTileUpdate()
{
	if (UTIL::isPointRectCollision(m_ptMouse, resetTileButtonRect)) {
		resetTileButtonRectSetted = true;
	}
	else {
		resetTileButtonRectSetted = false;
	}
	if (resetTileButtonRectSetted) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			resetTileSelectedAttribute();
		}
	}
}

void MapToolScene::resetTileRender(HDC hdc)
{
	UTIL::DrawColorRect(hdc, resetTileButtonRect, RGB(0, 255, 255), true);
	UTIL::PrintText(hdc, "ResetTile", "명조", resetTileButtonRect.left, resetTileButtonRect.top + 10, 10);
}
void MapToolScene::resetSpecifyRender(HDC hdc)
{
	UTIL::DrawColorRect(hdc, resetSpecifyButtonRect, RGB(125, 10, 19), true);
	UTIL::PrintText(hdc, "ResetSpecify", "명조", resetSpecifyButtonRect.left, resetSpecifyButtonRect.top, 10);
}
void MapToolScene::resetInnerAttributeRender(HDC hdc)
{
	UTIL::DrawColorRect(hdc, resetInnerAttributeRect, RGB(13, 234, 140), true);
	UTIL::PrintText(hdc, "ResetAttribute", "명조", resetInnerAttributeRect.left, resetInnerAttributeRect.top + 10, 10);
	if (m_resetInnerAttribute) {
		UTIL::DrawColorRect(hdc, pointResetInnerAttributeRect, RGB(0, 0, 0), true);
	}
}
void MapToolScene::backButtonRender(HDC hdc)
{
	UTIL::DrawColorRect(hdc, backButtonRect, RGB(255, 0, 255), true);
	UTIL::PrintText(hdc, "Back", "명조", backButtonRect.left, backButtonRect.top, 10);
}

void MapToolScene::resetInnerAttributeUpdate()
{
	if (UTIL::isPointRectCollision(m_ptMouse, resetInnerAttributeRect)) {
		if (KEYMANAGER->isOnceKeyDown(GAME_RMOUSE)) {
			m_resetInnerAttribute = !m_resetInnerAttribute;
		}
	}
}



void MapToolScene::backButtonUpdate()
{
	if (UTIL::isPointRectCollision(m_ptMouse, backButtonRect)) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			m_mainSelect = true;
			m_treeSelect = false;
			m_bushSelect = false;
			m_tileSelect = false;
			m_specifySelect = false;
			m_typeSelect = false;
			if (settedTileType) {
				selectedTileType = TileType::TileTypeNone;
				PointSelectedTypeRect = UTIL::IRectMakeCenter(0, 0, 0, 0);
				settedTileType = false;
			}
		}
	}
}


void MapToolScene::saveLoadUpdate()
{
	if (UTIL::isPointRectCollision(m_ptMouse, saveSelectRect)) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			saveMap();
	}
	if (UTIL::isPointRectCollision(m_ptMouse, loadSelectRect)) {
		if(GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			loadMap();
	}
}

void MapToolScene::saveLoadRender(HDC hdc)
{
	UTIL::DrawRect(hdc, saveSelectRect);
	TextOut(hdc, saveSelectRect.left + textOffsetX, saveSelectRect.top + textOffsetY,
		saveSelectStr, strlen(saveSelectStr));
	UTIL::DrawRect(hdc, loadSelectRect);
	TextOut(hdc, loadSelectRect.left + textOffsetX, loadSelectRect.top + textOffsetY,
		loadSelectStr, strlen(loadSelectStr));
}

void MapToolScene::resetSpecifyUpdate()
{
	if (UTIL::isPointRectCollision(m_ptMouse, resetSpecifyButtonRect)) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			settedNextMap = "";
			settedNextMapIdx.x = 0;
			settedNextMapIdx.y = 0;
			settedPocketMon = "";
			settedPocketMonLevel = 0;
			settedSpecifyStr = "";
			isSetAttribute = true;
			isSetPocketMon = false;
			isSetNextMap = false;
			isSetObj = false;
		}
	}
}





void MapToolScene::UIrender(HDC hdc)
{
	UTIL::DrawRect(hdc, clientRect);

	if (m_mainSelect)
		mainSelectRender(hdc);

	if (m_bushSelect)
		bushSelectRender(hdc); 
	if (m_treeSelect)
		treeSelectRender(hdc);
	if (m_tileSelect)
		tileSelectRender(hdc);
	if (m_specifySelect)
		specifyRender(hdc);
	if (m_typeSelect)
		typeSelectRender(hdc);

	backButtonRender(hdc);
	resetTileRender(hdc);
	resetSpecifyRender(hdc);
	saveLoadRender(hdc);
	resetInnerAttributeRender(hdc);

	if (m_settedNextMap && !m_setStartPos && !m_setAfterRenderImage) {
		UTIL::DrawColorRect(hdc, setActivateNextMapRect, RGB(255, 0, 255), true);
		UTIL::PrintText(hdc, "Set next map", "명조", setActivateNextMapRect.left + 30, setActivateNextMapRect.top + 20);
	}
	if (m_setStartPos && !m_settedNextMap && !m_setAfterRenderImage) {
		UTIL::DrawColorRect(hdc, setActivateNextMapRect, RGB(0, 255, 255), true);
		UTIL::PrintText(hdc, "Set Start Pos", "명조", setActivateNextMapRect.left + 30, setActivateNextMapRect.top + 20);
	}
	if (m_setAfterRenderImage && !m_setStartPos && !m_settedNextMap) {
		UTIL::DrawColorRect(hdc, setActivateNextMapRect, RGB(255, 255, 0), true);
		UTIL::PrintText(hdc, "Set AfterRender Image", "명조", setActivateNextMapRect.left + 30, setActivateNextMapRect.top + 20);
	}

}

void MapToolScene::TileWindowUpdate(float _deltaTime)
{
	if (!m_isSettedMove) {
		if (KEYMANAGER->isStayKeyDown(GAME_LMOUSE)) {
			if (!onSelect) {
				onSelect = true;
				m_selectRect.left = m_ptMouse.x;
				m_selectRect.top = m_ptMouse.y;
			}
			else {
				startedSelect = true;
				m_selectRect.right = m_ptMouse.x;
				m_selectRect.bottom = m_ptMouse.y;
			}
		}
		else if (onSelect) {
			onSelect = false;
			startedSelect = false;
			m_selectRect.alignment();
			for (auto& tile : m_Tiles) {
				if (UTIL::isRectRectCollision(m_selectRect, tile->m_outputTile)) {
					if (m_resetInnerAttribute) {
						tile->resetInnerAttribute();
					}
					else if (settedTileType) {
						tile->setTileType(selectedTileType);
					}
					else if (m_setStartPos) {
						if (tile->setStartBlock()) {
							mapStartX = tile->m_BlockPositionX;
							mapStartY = tile->m_BlockPositionY;
						}					
					}
					else if (isSetObj) {
						tile->setObj(settedObjName);
					}
					else if (m_settedNextMap)
						tile->setNextMapActivate();
					else if (isSetAttribute)
						tile->setAttributeTile(selectedAttribute);
					else if (isSetPocketMon)
						tile->pushInnerPocketMon(settedPocketMon, settedPocketMonLevel);
					else if (isSetNextMap)
						tile->setNextMap(settedNextMap, settedNextMapIdx.x, settedNextMapIdx.y);		
				}
			}
			m_selectRect.reset();
		}
	}
	if (m_settedColor && !m_isSettedMove) {
		if (KEYMANAGER->isOnceKeyDown(GAME_LMOUSE)) {
			for (auto& tile : m_Tiles) {
				if (UTIL::isPointRectCollision(m_ptMouse, tile->m_outputTile)) {
					tile->setAttributeTile(selectedAttribute);
				}
			}
		}
	}
	for (auto& tile : m_Tiles)
		tile->update(_deltaTime);
}

void MapToolScene::TileWindowRender(HDC hdc)
{
	//tile Render
	for (auto& tile : m_Tiles) {
		tile->render(hdc);
		tile->specialRender(hdc);
	}
	if (startedSelect)
		UTIL::DrawRect(hdc, m_selectRect);
}

void MapToolScene::loadMap()
{
	/*JSONMANAGER->MapDataRead(readMapName);
	MessageBox(m_hWnd, "save succefully done", "saved", MB_OK);*/
	std::string readMapName;
	std::cin >> readMapName;

	std::string filename = "../01. PocketMonster/Map/" + readMapName + ".json";
	std::ifstream input(filename, std::ios::binary);

	Json::Value root;
	Json::Reader reader;
	bool result = reader.parse(input, root);
	if (!result) {
		std::cout << reader.getFormatedErrorMessages() << std::endl;
	}
	input.close();

	mapName = root["mapName"].asString();

	int width = root["mapWidth"].asInt();
	int height = root["mapHeight"].asInt();
	mapStartX = root["startX"].asInt();
	mapStartY = root["startY"].asInt();
	int startIndex = mapStartX * width + mapStartY;

	int size = width * height;
	mapWidth = width;
	mapHeight = height;
	m_Tiles.clear();
	m_Tiles.resize(size);

	std::string innerPocketName = "innerPocketName-";
	std::string innerPocketLevel = "innerPocketLevel-";
	for (int i = 0; i < size; ++i) {
		std::string s = std::to_string(i);
		std::shared_ptr<Tile> tile = std::make_shared<Tile>();
		tile->m_Type = (TileType)root[s]["type"].asInt();
		if (tile->m_Type == TileType::TileTypeObject) {
			tile->objName = root[s]["objName"].asString();
		}
		if (i == startIndex) {
			tile->isStartBlock = true;
		}
		tile->m_BlockPositionX = root[s]["bPosX"].asInt();
		tile->m_BlockPositionY = root[s]["bPosY"].asInt();
		tile->tileImageKey = root[s]["imageKey"].asString();
		tile->afterRenderImageKey = root[s]["afterRenderImageKey"].asString();

		tile->m_nextMapName = root[s]["nextMapName"].asString();
		if (tile->m_nextMapName != "") {
			tile->m_nextMapStartIdx.x = root[s]["nextMapX"].asInt();
			tile->m_nextMapStartIdx.y = root[s]["nextMapY"].asInt();
		}
		int innerPocketCount = root[s]["innerPocketMonCnt"].asInt();
		for (int j = 0; j < innerPocketCount; ++j) {
			std::string name = root[s][innerPocketName + std::to_string(j)].asString();
			int level = root[s][innerPocketLevel + std::to_string(j)].asInt();
			tile->m_innerPocketMonInfo.push_back(std::make_pair(name, level));
		}
		tile->init();
		m_Tiles[i] = tile;
	}

}

void MapToolScene::saveMap()
{
	JSONMANAGER->MapDataWrite(mapName, m_Tiles, mapWidth, mapHeight, mapStartX, mapStartY);
	MessageBox(m_hWnd, "save succefully done", "saved", MB_OK);
}

void MapToolScene::resetTileSelectedAttribute()
{
	selectedAttribute.tileKeyname = "";
	selectedAttribute.isAfterRender = false;
	selectedAttribute.type = TileType::TileTypeNone;
	isSetAttribute = true;
	isSetNextMap = false;
	isSetPocketMon = false;
	m_settedNextMap = false;
	m_setStartPos = false;
}