#include "stdafx.h"
#include "MapToolScene.h"

bool MapToolScene::init()
{
	//tileSetup
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j) {
			auto tile = std::make_shared<Tile>();
			tile->init(TileType::TileTypeFloor, nullptr, false, true, j, i);
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
	setPocketMonButtonRect = UTIL::IRectMake(1150, 400, 200, 100);

	//TileBlockSetup
	treeVectorInit(3);
	tileVectorInit(3);
	bushVectorInit(3);
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
	treeVector[0][0].setTileAttribute("Tree1", type, false);
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
	if (m_bushSelect)
		bushSelectUpdate();
	if (m_treeSelect)
		treeSelectUpdate();
	if (m_specifySelect)
		specifyUpdate();

	resetTileUpdate();
	resetSpecifyUpdate();
	saveLoadUpdate();

}

void MapToolScene::mainSelectUpdate()
{
	if (UTIL::isPointRectCollision(m_ptMouse, tileSelectRect)) {
		tileSelectRectSetted = true;
	}
	else if (UTIL::isPointRectCollision(m_ptMouse, treeSelectRect)) {
		treeSelectRectSetted = true;
	}
	else if (UTIL::isPointRectCollision(m_ptMouse, bushSelectRect)) {
		bushSelectRectSetted = true;
	}
	else if (UTIL::isPointRectCollision(m_ptMouse, setSpecifyRect)) {
		setSpecifyRectSetted = true;
	}
	else {
		tileSelectRectSetted = false;
		treeSelectRectSetted = false;
		bushSelectRectSetted = false;
		setSpecifyRectSetted = false;
	}

	if (tileSelectRectSetted) {
		if (KEYMANAGER->isStayKeyDown(GAME_LMOUSE)) {
			m_tileSelect = true;
			m_mainSelect = false;
		}
	}
	if (treeSelectRectSetted) {
		if (KEYMANAGER->isStayKeyDown(GAME_LMOUSE)) {
			m_treeSelect = true;
			m_mainSelect = false;
		}
	}
	if (bushSelectRectSetted) {
		if (KEYMANAGER->isStayKeyDown(GAME_LMOUSE)) {
			m_bushSelect = true;
			m_mainSelect = false;
		}
	}
	if (bushSelectRectSetted) {
		if (KEYMANAGER->isStayKeyDown(GAME_LMOUSE)) {
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
				break;
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(GAME_LPAGE)) {
		bushSelectPage -= 1;
		if (bushSelectPage < 0)
			bushSelectPage = bushSelectPageMax - 1;
	}
	if (KEYMANAGER->isStayKeyDown(GAME_RPAGE)) {
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
				break;
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(GAME_LPAGE)) {
		treeSelectPage -= 1;
		if (treeSelectPage < 0)
			treeSelectPage = bushSelectPageMax - 1;
	}
	if (KEYMANAGER->isStayKeyDown(GAME_RPAGE)) {
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
	if (KEYMANAGER->isStayKeyDown(GAME_LMOUSE)) {
		for (auto& e : tileVector[tileSelectPage]) {
			if (UTIL::isPointRectCollision(m_ptMouse, e.rect)) {
				selectedAttribute = e.attribute;
				break;
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(GAME_LPAGE)) {
		tileSelectPage -= 1;
		if (tileSelectPage < 0)
			tileSelectPage = bushSelectPageMax - 1;
	}
	if (KEYMANAGER->isStayKeyDown(GAME_RPAGE)) {
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
	if (KEYMANAGER->isStayKeyDown(GAME_LMOUSE)) {
		if (UTIL::isPointRectCollision(m_ptMouse, setPocketMonButtonRect)) {
			std::cin >> settedPocketMon;
			std::cin >> settedPocketMonLevel;
			m_settedPocketMon = true;
		}
		if (UTIL::isPointRectCollision(m_ptMouse, setNextMapButtonRect)) {
			std::cin >> settedNextMap;
			std::cin >> settedNextMapIdx.x;
			std::cin >> settedNextMapIdx.y;
			m_settedNextMap = true;
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
}

void MapToolScene::resetTileUpdate()
{
	if (UTIL::isPointRectCollision(m_ptMouse, resetTileButtonRect)) {
		resetTileButtonRectSetted = true;
	}
	if (KEYMANAGER->isStayKeyDown(GAME_LMOUSE)) {
		if (resetTileButtonRectSetted)
			resetTileSelectedAttribute();
	}
}

void MapToolScene::resetTileRender(HDC hdc)
{
	UTIL::DrawColorRect(hdc, resetTileButtonRect, RGB(0, 255, 255), true);
}

void MapToolScene::saveLoadUpdate()
{
	if (KEYMANAGER->isStayKeyDown(GAME_LMOUSE)) {
		if (UTIL::isPointRectCollision(m_ptMouse, saveSelectRect)) {
			saveMap();
		}
		if (UTIL::isPointRectCollision(m_ptMouse, loadSelectRect)) {
			loadMap();
		}
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
	if (KEYMANAGER->isStayKeyDown(GAME_LMOUSE)) {
		if (UTIL::isPointRectCollision(m_ptMouse, resetSpecifyButtonRect)) {
			settedNextMap = "";
			settedNextMapIdx.x = 0;
			settedNextMapIdx.y = 0;
			settedPocketMon = "";
			settedPocketMonLevel = 0;
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
		backButtonRectSetted = true;
	}
	else {
		backButtonRectSetted = false;
	}

	if (backButtonRectSetted) {
		if (KEYMANAGER->isStayKeyDown(GAME_LMOUSE)) {
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
					tile->setAttributeTile(selectedAttribute);
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
	}
	if (startedSelect)
		UTIL::DrawRect(hdc, m_selectRect);
}

void MapToolScene::loadMap()
{
}

void MapToolScene::saveMap()
{
}

void MapToolScene::resetTileSelectedAttribute()
{
	selectedAttribute.tileKeyname = "";
	selectedAttribute.isAfterRender = false;
	selectedAttribute.type = TileType::TileTypeNone;
	m_settedNextMap = false;
	m_settedPocketMon = false;

}