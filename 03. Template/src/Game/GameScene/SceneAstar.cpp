#include "stdafx.h"
#include "SceneAstar.h"

bool Astar::init()
{
	astarState = ASTAR_STATE_END;
	type = TILE_TYPE_EMPTY;
	color = RGB(255, 255, 255);

	startPointSet = false;
	endPointSet = false;
	
	for (int i = 0; i < TILE_Y; ++i) {
		for (int j = 0; j < TILE_X; ++j) {
			tile[i][j].type = TILE_TYPE_EMPTY;
			tile[i][j].color = RGB(255, 255, 255);
			tile[i][j].color = RGB(255, 255, 255);
			tile[i][j].parent = nullptr;
			tile[i][j].F = BIGNUM;
			tile[i][j].H = 0;
			tile[i][j].i = i;
			tile[i][j].j = j;
			tile[i][j].rc = UTIL::RectMake(WINSIZEX - (TILE_X + 1) * WIDTH + WIDTH * j,
				WINSIZEX/2 - TILE_Y / 2 * HEIGHT + HEIGHT*i, WIDTH, HEIGHT);
		}
	}

	//for(int i = 0 ; i < )

	return true;
}

void Astar::release()
{
}

void Astar::update(float _deltaTime)
{
	if (astarState == ASTAR_STATE_END)
		tileComposition();
	if (KEYMANAGER->isOnceKeyDown(P1_EVENT) && startPointSet 
		&& endPointSet && astarState == ASTAR_STATE_END) {
		tileInitilizing();
	}
	if (KEYMANAGER->isOnceKeyDown(P1_UP)) {
		openList.clear();
		closedList.clear();
		init();
	}

	if (astarState == ASTAR_STATE_END || ASTAR_STATE_FOUND ||
		ASTAR_STATE_NOWAY) {
		return;
	}
	addOpenList();
	calcF();
	calcH();
	addClosedList();
	checkArrive();
}

void Astar::render(HDC hdc)
{
	TextOut(hdc, 15, 75, "1 : 지우개", strlen("1 : 지우개"));
	TextOut(hdc, 15, 95, "2 : 시작", strlen("2 : 시작"));
	TextOut(hdc, 15, 115, "3 : 끝", strlen("3 : 끝"));
	TextOut(hdc, 15, 135, "4 : 장애물", strlen("4 : 장애물"));
	TextOut(hdc, 15, 155, "5 : 초기화", strlen("5 : 초기화"));

	char str[128];
	if (astarState == ASTAR_STATE_END)
		sprintf_s(str, "스페이스 눌러");
	if (astarState == ASTAR_STATE_FOUND)
		sprintf_s(str, "찾음");
	if (astarState == ASTAR_STATE_NOWAY)
		sprintf_s(str, "길없다");
	if (astarState == ASTAR_STATE_SEARCHING)
		sprintf_s(str, "찾고있음");

	TextOut(hdc, 15, 200, str, strlen(str));
	//newFont; //= CreateFont(9, 0, 0, 0, FW_NORMAL, false, false, ,"굴림");
	//oldFont = (HFONT)SelectObject(hdc, newFont);

	for (int i = 0; i < TILE_Y; ++i) {
		for (int j = 0; j < TILE_X; ++j) {
			UTIL::DrawColorRect(hdc, tile[i][j].rc, true, tile[i][j].color);
			if (tile[i][j].parent == nullptr)
				continue;
		}
	}
	for (int i = 0; i < 5; ++i) {
		if (i == 0){
			UTIL::BeginSolidColor(hdc, &newBrush, RGB(0, 255, 0));
			UTIL::DrawRect(hdc, rc[i]);
			sprintf_s(str, "시작점");
			DeleteObject(newBrush);
		}
		if (i == 1) {
			UTIL::BeginSolidColor(hdc, &newBrush, RGB(255, 0, 0));
			UTIL::DrawRect(hdc, rc[i]);
			sprintf_s(str, "도착");
			DeleteObject(newBrush);
		}
		if (i == 2) {
			UTIL::BeginSolidColor(hdc, &newBrush, RGB(255, 242, 0));
			UTIL::DrawRect(hdc, rc[i]);
			sprintf_s(str, "openList");
			DeleteObject(newBrush);
		}
		if (i == 3) {
			UTIL::BeginSolidColor(hdc, &newBrush, RGB(255, 0, 255));
			UTIL::DrawRect(hdc, rc[i]);
			sprintf_s(str, "closeList");
			DeleteObject(newBrush);
		}
		if (i == 4) {
			UTIL::BeginSolidColor(hdc, &newBrush, RGB(255, 100, 100));
			UTIL::DrawRect(hdc, rc[i]);
			sprintf_s(str, "path");
			DeleteObject(newBrush);
		}
		TextOut(hdc, rc[i].right + 5, rc[i].top + 5, str, strlen(str));
	}
}

void Astar::debugRender(HDC hdc)
{
}

void Astar::afterRender(HDC hdc)
{
}

void Astar::tileComposition()
{
	//비어있을때
	if (KEYMANAGER->isOnceKeyDown(P1_UP)) {
		type = TILE_TYPE_EMPTY;
		color = RGB(255, 255, 255);
	}

	//스타트일때
	else if (KEYMANAGER->isOnceKeyDown(P1_DOWN)) {
		type = TILE_TYPE_START;
		color = RGB(100, 255, 100);
	}
	//엔드일때
	else if (KEYMANAGER->isOnceKeyDown(P1_LEFT)) {
		type = TILE_TYPE_END;
		color = RGB(255, 0, 0);
	}
	//장애물일때
	else if (KEYMANAGER->isOnceKeyDown(P1_RIGHT)) {
		type = TILE_TYPE_WALL;
		color = RGB(255, 255, 0);
	}
	if (KEYMANAGER->isStayKeyDown(GAME_LMOUSE)) {
		for (int i = 0; i < TILE_Y; ++i) {
			for (int j = 0; j < TILE_X; ++j) {
				if (PtInRect(&tile[i][j].rc, m_ptMouse)) {
					if (tile[i][j].type == TILE_TYPE_START) 
						startPointSet = false;
					if (tile[i][j].type == TILE_TYPE_END)
						startPointSet = false;

					tile[i][j].type = type;
					tile[i][j].color = color;

					if (type == TILE_TYPE_START)
					{
						if (startPointSet) {
							tile[starty][startx].color = RGB(255, 0, 255);
							tile[starty][startx].type = TILE_TYPE_EMPTY;
						}
						startPointSet = true;
						startx = j;
						starty = i;
					}
					if (type == TILE_TYPE_END) {
						endx = j;
						endy = i;
						endPointSet = true;
						/*if (endPointSet) {
							tile[endy][endx].color = RGB(255, 0, 255);
							tile[endy][endx].type = TILE_TYPE_EMPTY;
						}
						*/
					}

				}
			}
		}
	}
	astarState = ASTAR_STATE_SEARCHING;
	lastIndex = 0;
}

void Astar::tileInitilizing()
{
	for (int i = 0; i < TILE_X; ++i) {
		for (int j = 0; j < TILE_Y; ++j) {
			if (tile[i][j].type == TILE_TYPE_EMPTY) {
				tile[i][j].walkable = true;
				tile[i][j].listOn = false;
			}
			if (tile[i][j].type == TILE_TYPE_WALL) {
				tile[i][j].walkable = false;
				tile[i][j].listOn = false;
			}
			if (tile[i][j].type == TILE_TYPE_START) {
				tile[i][j].walkable = true;
				tile[i][j].listOn = true;

				closedList.push_back(&tile[i][j]);
			}
			/*if (tile[i][j].type == TILE_TYPE_START) {
				tile[i][j].walkable = true;
				tile[i][j].listOn = true;
			}*/
		}
	}
}

void Astar::addOpenList()
{
	Ci = closedList[lastIndex]->i;
	Cj = closedList[lastIndex]->j;
	Cg = closedList[lastIndex]->G;

	if (Ci != 0) {
		if (tile[Ci - 1][Cj].walkable) { 
			//오픈 리스트에 포함이 안되어 있는 타일
			if (!tile[Ci - 1][Cj].listOn) { 
				tile[Ci - 1][Cj].listOn = true;
				tile[Ci - 1][Cj].color = RGB(220, 255, 220);
				tile[Ci - 1][Cj].G = Cg + 10;
				tile[Ci - 1][Cj].parent = closedList[lastIndex];
				openList.push_back(&tile[Ci - 1][Cj]);
			}
			// 오픈 리스트에 포함되어 있는 타일
			else { 
				if (Cg + 10 < tile[Ci - 1][Cj].G) {
					// 기존 g값보다 새로 계산한 G값이 작다면
					tile[Ci - 1][Cj].G = Cg + 10;
					tile[Ci - 1][Cj].parent = closedList[lastIndex];
				}
				else {

				}
			}
		}
		if (Cj != 0) {
			//좌상단 타일의 왼쪽이나 아래에 벽이 없다면
			if (tile[Ci - 1][Cj - 1].walkable && tile[Ci][Cj].walkable && tile[Ci][Cj - 1].walkable) {
				if (!tile[Ci - 1][Cj - 1].listOn) {
					tile[Ci - 1][Cj - 1].listOn = true;
					tile[Ci - 1][Cj - 1].color = RGB(220, 255, 220);
					tile[Ci - 1][Cj - 1].G = Cg + 14;
					tile[Ci - 1][Cj - 1].parent = closedList[lastIndex];
					closedList.push_back(&tile[Ci - 1][Cj - 1]);
				}
				else {
					if (Cg + 14 < tile[Ci - 1][Cj - 1].G) {
						tile[Ci - 1][Cj - 1].G = Cg + 14;
						tile[Ci - 1][Cj - 1].parent = closedList[lastIndex];
					}
				}
			}
		}
		if (Cj != TILE_X - 1) {
			//우상단 타일의 왼쪽이나 아래에 벽이 없다면
			if (tile[Ci - 1][Cj + 1].walkable && tile[Ci - 1][Cj].walkable && tile[Ci][Cj + 1].walkable) {
				if (!tile[Ci - 1][Cj + 1].listOn) {
					tile[Ci - 1][Cj + 1].listOn = true;
					tile[Ci - 1][Cj + 1].color = RGB(220, 255, 220);
					tile[Ci - 1][Cj + 1].G = Cg + 14;
					tile[Ci - 1][Cj + 1].parent = closedList[lastIndex];
					closedList.push_back(&tile[Ci - 1][Cj + 1]);
				}
				else 
				{
					if (Cg + 14 < tile[Ci - 1][Cj + 1].G) {
						tile[Ci - 1][Cj + 1].G = Cg + 14;
						tile[Ci - 1][Cj + 1].parent = closedList[lastIndex];
					}
				}
			}
		}
	}
	if (Cj != 0) {
		if (tile[Ci][Cj - 1].walkable) {
			if (!tile[Ci][Cj - 1].listOn) {
				tile[Ci][Cj - 1].listOn = true;
				tile[Ci][Cj - 1].color = RGB(220, 255, 220);
				tile[Ci][Cj - 1].G = Cg + 10;
				tile[Ci][Cj - 1].parent = closedList[lastIndex];
				openList.push_back(&tile[Ci][Cj - 1]);
			}
			else {
				if (Cg + 10 < tile[Ci][Cj - 1].G ) {
					tile[Ci][Cj - 1].G = Cg + 10;
					tile[Ci][Cj - 1].parent = closedList[lastIndex];
				}
			}
		}
	}
	//우측 타일이 마지막열이 아니라면
	if (Cj != TILE_X - 1) {
		if (tile[Ci][Cj + 1].walkable) {
			if (!tile[Ci][Cj + 1].listOn) {
				tile[Ci][Cj + 1].listOn = true;
				tile[Ci][Cj + 1].color = RGB(220, 255, 220);
				tile[Ci][Cj + 1].G = Cg + 10;
				tile[Ci][Cj + 1].parent = closedList[lastIndex];
				openList.push_back(&tile[Ci][Cj + 1]);
			}
			else {
				if (Cg + 10 < tile[Ci][Cj + 1].G) {
					tile[Ci][Cj + 1].G = Cg + 10;
					tile[Ci][Cj + 1].parent = closedList[lastIndex];
				}
			}
		}
	}
	//마지막 행이 아니라면
	if (Ci != TILE_Y - 1) {
		if (tile[Ci + 1][Cj].walkable) {
			if (!tile[Ci + 1][Cj].listOn) {
				tile[Ci + 1][Cj].listOn = true;
				tile[Ci + 1][Cj].color = RGB(220, 255, 220);
				tile[Ci + 1][Cj].G = Cg + 10;
				tile[Ci + 1][Cj].parent = closedList[lastIndex];
				openList.push_back(&tile[Ci + 1][Cj]);
			}
			else {
				if (Cg + 10 < tile[Ci + 1][Cj].G) {
					tile[Ci + 1][Cj].G = Cg + 10;
					tile[Ci + 1][Cj].parent = closedList[lastIndex];
				}
			}
		}
		if (Cj != 0) {
			//좌하단 타일의 오른쪽이나 위에 벽이 없다면
			if (tile[Ci + 1][Cj - 1].walkable && tile[Ci + 1][Cj].walkable && tile[Ci][Cj - 1].walkable) {
				if (!tile[Ci + 1][Cj - 1].listOn) {
					tile[Ci + 1][Cj - 1].listOn = true;
					tile[Ci + 1][Cj - 1].color = RGB(220, 255, 220);
					tile[Ci + 1][Cj - 1].G = Cg + 14;
					tile[Ci + 1][Cj - 1].parent = closedList[lastIndex];
					openList.push_back(&tile[Ci + 1][Cj - 1]);
				}
				else {
					if (Cg + 14 < tile[Ci + 1][Cj - 1].G) {
						tile[Ci + 1][Cj - 1].G = Cg + 14;
						tile[Ci + 1][Cj - 1].parent = closedList[lastIndex];
					}
				}
			}
		}
		//우하단 마지막 열이 아니라면
		if (Cj != TILE_X - 1) {
			if (tile[Ci + 1][Cj + 1].walkable && tile[Ci + 1][Cj].walkable && tile[Ci][Cj + 1].walkable) {
				if (!tile[Ci + 1][Cj + 1].listOn) {
					tile[Ci + 1][Cj + 1].listOn = true;
					tile[Ci + 1][Cj + 1].color = RGB(220, 255, 220);
					tile[Ci + 1][Cj + 1].G = Cg + 14;
					tile[Ci + 1][Cj + 1].parent = closedList[lastIndex];
					openList.push_back(&tile[Ci + 1][Cj + 1]);
				}
				else {
					if (Cg + 14 < tile[Ci + 1][Cj + 1].G) {
						tile[Ci + 1][Cj + 1].G = Cg + 14;
						tile[Ci + 1][Cj + 1].parent = closedList[lastIndex];
					}
				}
			}
		}
	}

}

void Astar::addClosedList()
{
	if (openList.size() == 0) {
		astarState = ASTAR_STATE_NOWAY;
		return;
	}
	int index = 0;
	int lowest = BIGNUM;

	for (int i = 0; i < openList.size(); ++i) {
		if (openList[i]->F < lowest) {
			lowest = openList[i]->F;
			index = i;
		}
	}
	openList[index]->color = RGB(180, 180, 255);
	closedList.push_back(openList[index]);
	openList.erase(openList.begin() + index);

	lastIndex++;
}

void Astar::calcH()
{
	for (int i = 0; i < openList.size(); ++i) {
		int vertical = endx - openList[i]->j * 10;
		int horizental = endy - openList[i]->i * 10;

		if (vertical < 0)
			vertical = -vertical;
		if (horizental < 0)
			horizental = -horizental;
		openList[i]->H - vertical + horizental;
	}
}

void Astar::calcF()
{
	for (int i = 0; i < openList.size(); ++i) {
		openList[i]->F = openList[i]->G + openList[i]->H;
	}
}

void Astar::checkArrive()
{
	if (closedList[lastIndex]->i == endy && closedList[lastIndex]->j == endx) {
		astarState = ASTAR_STATE_FOUND;
		closedList[lastIndex]->color = RGB(0, 0, 0);
		showWay(closedList[lastIndex]);
	}
}

void Astar::showWay(AstarTile * tile)
{
	if (!((tile->i == endy) && (tile->j == endx)))
		tile->color = RGB(255, 180, 180);
	tile = tile->parent;
	
	if (tile->parent == nullptr) 
		return;
	else
		showWay(tile);
}
