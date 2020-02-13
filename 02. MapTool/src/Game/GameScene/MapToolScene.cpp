#include "stdafx.h"
#include "MapToolScene.h"

bool MapToolScene::init()
{
	//tileSetup
	for (int i = 0; i < mapHeight; ++i) {
		for (int j = 1; j <= mapWidth; ++j) {
			std::string key = "TechoTown_" + std::to_string(i * mapWidth + j) + "t";
			auto tile = std::make_shared<Tile>();
			tile->init(TileType::TileTypeFloor, IMAGEMANAGER->findImage(key), false, true, (j - 1), i);
			m_Tiles.push_back(tile);
		}
	}


	//ButtonSetup
	//always
	clientRect = UTIL::IRectMake(UIOffset, -10, WINSIZEX - UIOffset, WINSIZEY + 20);
	saveSelectRect = UTIL::IRectMake(1100, 600, 100, 100);
	loadSelectRect = UTIL::IRectMake(1300, 600, 100, 100);
	backButtonRect = UTIL::IRectMake(1400, 0, 50, 50);
	resetTileButtonRect = UTIL::IRectMake(1350, 0, 50, 50);
	resetSpecifyButtonRect = UTIL::IRectMake(1300, 0, 50, 50);
	pageFrontButton = UTIL::IRectMake(1100, 500, 50, 50);
	pageBackButton = UTIL::IRectMake(1300, 500, 50, 50);

	//in each case
	tileSelectRect = UTIL::IRectMake(1150, 100, 200, 100);
	treeSelectRect = UTIL::IRectMake(1150, 200, 200, 100);
	bushSelectRect = UTIL::IRectMake(1150, 300, 200, 100);
	setSpecifyRect = UTIL::IRectMake(1150, 400, 200, 100);
	setNextMapButtonRect = UTIL::IRectMake(1150, 200, 200, 100);
	setActivateNextMapRect = UTIL::IRectMake(1150, 500, 200, 50);


	setPocketMonButtonRect = UTIL::IRectMake(1150, 300, 200, 100);

	//TileBlockSetup
	treeVectorInit(5);
	tileVectorInit(5);
	bushVectorInit(5);
	resetTileSelectedAttribute();

	return true;

}

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
	tileVectorPush("TownTile", TileType::TileTypeFloor, 2, 13, false);
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

	resetTileUpdate();
	resetSpecifyUpdate();
	saveLoadUpdate();

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
	TextOut(hdc, inSelectStrX, inSelectStrY, inBushSelectStr, strlen(inBushSelectStr));
	for (auto& e : bushVector[bushSelectPage]) {
		if (e.img)
			e.img->render(hdc, e.inUIpositionX, e.inUIpositionY);
		else
			UTIL::DrawRect(hdc, e.rect);
	}
	UTIL::DrawColorEllipse(hdc, pageBackButton, RGB(255, 255, 0), true);
	UTIL::DrawColorEllipse(hdc, pageFrontButton, RGB(0, 255, 255), true);
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
	TextOut(hdc, inSelectStrX, inSelectStrY, inTreeSelectStr, strlen(inBushSelectStr));
	for (auto& e : treeVector[treeSelectPage]) {
		if (e.img)
			e.img->render(hdc, e.inUIpositionX, e.inUIpositionY);
		else
			UTIL::DrawRect(hdc, e.rect);
	}
	UTIL::DrawColorEllipse(hdc, pageBackButton, RGB(255, 255, 0), true);
	UTIL::DrawColorEllipse(hdc, pageFrontButton, RGB(0, 255, 255), true);
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
	TextOut(hdc, inSelectStrX, inSelectStrY, inTileSelectStr, strlen(inBushSelectStr));
	for (auto& e : tileVector[tileSelectPage]) {
		if (e.img)
			e.img->render(hdc, e.inUIpositionX, e.inUIpositionY);
		else
			UTIL::DrawRect(hdc, e.rect);
	}
	UTIL::DrawColorEllipse(hdc, pageBackButton, RGB(255, 255, 0), true);
	UTIL::DrawColorEllipse(hdc, pageFrontButton, RGB(0, 255, 255), true);
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
			isSetPocketMon = true;
			settedSpecifyStr = settedPocketMon + " " + std::to_string(settedPocketMonLevel);
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
			settedSpecifyStr = settedNextMap + " " + std::to_string(settedNextMapIdx.x) + " " 
				+ std::to_string(settedNextMapIdx.y);
		}
	}
}

void MapToolScene::specifyRender(HDC hdc)
{
	UTIL::DrawRect(hdc, setPocketMonButtonRect);
	TextOut(hdc, setPocketMonButtonRect.left + textOffsetX, setPocketMonButtonRect.top + textOffsetY,
		specifyPocketStr, strlen(specifyPocketStr));
	UTIL::DrawRect(hdc, setNextMapButtonRect);
	TextOut(hdc, setNextMapButtonRect.left + textOffsetX, setNextMapButtonRect.top + textOffsetY,
		specifyNextMapStr, strlen(specifyNextMapStr));

	TextOut(hdc, setNextMapButtonRect.left - 100 + textOffsetX, 100,
		settedInfo, strlen(settedInfo));
	TextOut(hdc, setNextMapButtonRect.left + textOffsetX, 100,
		settedSpecifyStr.c_str(), settedSpecifyStr.length());
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
		}
	}
}

void MapToolScene::resetSpecifyRender(HDC hdc)
{
	UTIL::DrawColorRect(hdc, resetSpecifyButtonRect, RGB(125, 10, 19));
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
		}
	}
}

void MapToolScene::backButtonRender(HDC hdc)
{
	UTIL::DrawColorRect(hdc, backButtonRect, RGB(255, 0, 255), true);
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

	backButtonRender(hdc);
	resetTileRender(hdc);
	resetSpecifyRender(hdc);
	saveLoadRender(hdc);

	if (m_settedNextMap && !m_setStartPos && !m_setAfterRenderImage) {
		UTIL::DrawColorRect(hdc, setActivateNextMapRect, RGB(255, 0, 255), true);
	}
	if (m_setStartPos && !m_settedNextMap && !m_setAfterRenderImage) {
		UTIL::DrawColorRect(hdc, setActivateNextMapRect, RGB(0, 255, 255), true);
	}
	if (m_setAfterRenderImage && !m_setStartPos && !m_settedNextMap) {
		UTIL::DrawColorRect(hdc, setActivateNextMapRect, RGB(255, 255, 0), true);
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
					if (m_setStartPos) {
						if (tile->setStartBlock()) {
							mapStartX = tile->m_BlockPositionX;
							mapStartY = tile->m_BlockPositionY;
						}					
					}

					if (m_settedNextMap)
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
	if (KEYMANAGER->isOnceKeyDown(GAME_W))
		m_settedColor = !m_settedColor;
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
	std::string readMapName;
	std::cin >> readMapName;
	JSONMANAGER->MapDataRead(readMapName);
	MessageBox(m_hWnd, "save succefully done", "saved", MB_OK);
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