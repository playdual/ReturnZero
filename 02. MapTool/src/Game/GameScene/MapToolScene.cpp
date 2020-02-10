#include "stdafx.h"
#include "MapToolScene.h"

bool MapToolScene::init()
{
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j) {
			auto tile = std::make_shared<Tile>();
			tile->init(TileType::TileTypeFloor, nullptr, false, true, j, i);
			m_Tiles.push_back(tile);
		}
	}
	clientRect = UTIL::IRectMake(1000, -10, WINSIZEX - 1000, WINSIZEY + 20);
	tileSelectRect = UTIL::IRectMake(1150, 100, 200, 100);
	treeSelectRect = UTIL::IRectMake(1150, 200, 200, 100);
	bushSelectRect = UTIL::IRectMake(1150, 300, 200, 100);
	saveSelectRect = UTIL::IRectMake(1100, 600, 100, 100);
	loadSelectRect = UTIL::IRectMake(1300, 600, 100, 100);
	backButtonRect = UTIL::IRectMake(1400, 0, 50, 50);
	resetTileButtonRect = UTIL::IRectMake(1350, 0, 50, 50);

	treeVectorInit(1);
	tileVectorInit(1);
	bushVectorInit(1);
	resetSelectedAttribute();

	return true;

}

void MapToolScene::update(float _deltaTime)
{
	cameraMove();

	if (!m_isSettedMove) {
		if(KEYMANAGER->isStayKeyDown(GAME_LMOUSE)) {
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
		else if(onSelect){
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
	for (auto& tile : m_Tiles) {
		tile->render(hdc);
	}
	if(startedSelect)
		UTIL::DrawRect(hdc, m_selectRect);
	
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
	treeSelectPage = _pageCount;
	treeVector.resize(_pageCount);
	for (int i = 0; i < _pageCount; ++i) {
		treeVector[i].resize(25);
		for (int j = 0; j < 25; ++j) {
			treeVector[i][j].inUIpositionX = (i % 5) * inUiTileWidth + 1100;
			treeVector[i][j].inUIpositionY = (i / 5) * inUiTileHeight + 100;
			treeVector[i][j].rect = UTIL::IRectMake(treeVector[i][j].inUIpositionX, treeVector[i][j].inUIpositionY,
				inUiTileWidth, inUiTileHeight);
		}
	}
	TileType type = TileType::TileTypeTree;
	treeVector[0][0].setTileAttribute("Tree1", type, false);
}

void MapToolScene::tileVectorInit(int _pageCount)
{
	tileSelectPage = _pageCount;
	tileVector.resize(_pageCount);
	for (int i = 0; i < _pageCount; ++i) {
		tileVector[i].resize(25);
		for (int j = 0; j < 25; ++j) {
			tileVector[i][j].inUIpositionX = (i % 5) * inUiTileWidth + 1100;
			tileVector[i][j].inUIpositionY = (i / 5) * inUiTileHeight + 100;
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
	bushSelectPage = _pageCount;
	bushVector.resize(_pageCount);
	for (int i = 0; i < _pageCount; ++i) {
		bushVector[i].resize(25);
		for (int j = 0; j < 25; ++j) {
			tileVector[i][j].inUIpositionX = (i % 5) * inUiTileWidth + 1100;
			tileVector[i][j].inUIpositionY = (i / 5) * inUiTileHeight + 100;
			tileVector[i][j].rect = UTIL::IRectMake(tileVector[i][j].inUIpositionX, tileVector[i][j].inUIpositionY,
				inUiTileWidth, inUiTileHeight);
		}
	}
	TileType type = TileType::TileTypeBush;
	bushVector[0][0].setTileAttribute("Bush1", type, false);
}

void MapToolScene::UIupdate()
{
	resetTileUpdate();

	if (m_mainSelect)
		mainSelectUpdate();
	if (m_bushSelect)
		bushSelectUpdate();
	if (m_treeSelect)
		treeSelectUpdate();
	if (m_tileSelect)
		tileSelectUpdate();

	saveLoadUpdate();
}

void MapToolScene::mainSelectUpdate()
{
	if (KEYMANAGER->isStayKeyDown(GAME_LMOUSE)) {
		if (UTIL::isPointRectCollision(m_ptMouse, tileSelectRect)) {
			m_tileSelect = true;
			m_mainSelect = false;
		}
		if (UTIL::isPointRectCollision(m_ptMouse, treeSelectRect)) {
			m_treeSelect = true;
			m_mainSelect = false;
		}
		if (UTIL::isPointRectCollision(m_ptMouse, bushSelectRect)) {
			m_bushSelect = true;
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
}

void MapToolScene::bushSelectUpdate()
{
	backButtonUpdate();
	if (KEYMANAGER->isStayKeyDown(GAME_LMOUSE))
	{
		for (auto& e : bushVector[page]) {
			if (UTIL::isPointRectCollision(m_ptMouse, e.rect)) {
				selectedAttribute = e.attribute;
				break;
			}
		}
	}
}

void MapToolScene::bushSelectRender(HDC hdc)
{
	TextOut(hdc, inSelectStrX, inSelectStrY, inBushSelectStr, strlen(inBushSelectStr));
	for (auto& e : bushVector)
		e.img->render(hdc, e.inUIpositionX, e.inUIpositionY);
}

void MapToolScene::treeSelectUpdate()
{
	backButtonUpdate();
	if (KEYMANAGER->isStayKeyDown(GAME_LMOUSE)) {
		for (auto& e : treeVector) {
			if (UTIL::isPointRectCollision(m_ptMouse, e.rect)) {
				selectedAttribute = e.attribute;
				break;
			}
		}
	}
}

void MapToolScene::treeSelectRender(HDC hdc)
{
	TextOut(hdc, inSelectStrX, inSelectStrY, inTreeSelectStr, strlen(inBushSelectStr));
	for (auto& e : treeVector)
		e.img->render(hdc, e.inUIpositionX, e.inUIpositionY);
}

void MapToolScene::tileSelectUpdate()
{
	backButtonUpdate();
	if (KEYMANAGER->isStayKeyDown(GAME_LMOUSE)) {
		for (auto& e : tileVector) {
			if (UTIL::isPointRectCollision(m_ptMouse, e.rect)) {
				selectedAttribute = e.attribute;
				break;
			}
		}
	}
}

void MapToolScene::tileSelectRender(HDC hdc)
{
	TextOut(hdc, inSelectStrX, inSelectStrY, inTileSelectStr, strlen(inBushSelectStr));
	for (auto& e : tileVector)
		e.img->render(hdc, e.inUIpositionX, e.inUIpositionY);
}

void MapToolScene::resetTileUpdate()
{
	if (KEYMANAGER->isStayKeyDown(GAME_LMOUSE)) {
		if (UTIL::isPointRectCollision(m_ptMouse, resetTileButtonRect)) {
			resetSelectedAttribute();
		}
	}
}

void MapToolScene::resetTileRender(HDC hdc)
{
	UTIL::DrawColorRect(hdc, resetTileButtonRect, true, RGB(0, 255, 255));
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

void MapToolScene::backButtonUpdate()
{
	if (KEYMANAGER->isStayKeyDown(GAME_LMOUSE)) {
		if (UTIL::isPointRectCollision(m_ptMouse, backButtonRect)) {
			m_mainSelect = true;
			m_bushSelect = false;
			m_treeSelect = false;
			m_tileSelect = false;
		}
	}
}

void MapToolScene::backButtonRender(HDC hdc)
{
	UTIL::DrawColorRect(hdc, backButtonRect, true, RGB(255, 0, 255));
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

	backButtonRender(hdc);
	resetTileRender(hdc);
	saveLoadRender(hdc);
}

void MapToolScene::loadMap()
{
}

void MapToolScene::saveMap()
{
}

void MapToolScene::resetSelectedAttribute()
{
	selectedAttribute.tileKeyname = "";
	selectedAttribute.isAfterRender = false;
	selectedAttribute.type = TileType::TileTypeNone;
}
