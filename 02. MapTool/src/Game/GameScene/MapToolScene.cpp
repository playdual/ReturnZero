#include "stdafx.h"
#include "MapToolScene.h"

bool MapToolScene::init()
{
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			auto tile = std::make_shared<Tile>();
			tile->init(TileType::TileTypeFloor, nullptr, false, true, j, i);
			m_Tiles.push_back(tile);
		}
	}
	clientRect = UTIL::IRectMake(1000, -10, WINSIZEX - 1000, WINSIZEY + 20);

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
					tile->setColor();
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
					tile->setColor();
				}
			}
		}		
	}


	for (auto& tile : m_Tiles)
		tile->update(_deltaTime);

}

void MapToolScene::release()
{
}

void MapToolScene::render(HDC hdc)
{
	for (auto& tile : m_Tiles) {
		tile->render(hdc);
	}
	if(startedSelect)
		UTIL::DrawRect(hdc, m_selectRect);
	UTIL::DrawRect(hdc, clientRect);
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
