#pragma once
#include "Scene.h"

#define TILE_X 10
#define TILE_Y 10
#define WIDTH 35
#define HEIGHT 35
#define BIGNUM 5000

enum TILE_TYPE
{
	TILE_TYPE_EMPTY, // 지나 갈수 있음
	TILE_TYPE_START,
	TILE_TYPE_END,
	TILE_TYPE_WALL
};

enum ASTAR_STATE
{
	ASTAR_STATE_SEARCHING,
	ASTAR_STATE_FOUND,
	ASTAR_STATE_NOWAY,
	ASTAR_STATE_END
};

struct AstarTile {
	RECT rc;
	bool walkable;
	bool listOn;
	int i, j;
	int F, G, H;
	char str[255];
	TILE_TYPE type;
	COLORREF color;
	AstarTile* parent;

};

class Astar
	: public Scene
{
public:
	bool init();
	void release();
	void update(float _deltaTime);
	void render(HDC hdc);
	void debugRender(HDC hdc);
	void afterRender(HDC hdc);

	void tileComposition();
	void tileInitilizing();

	void addOpenList();
	void addClosedList();	//가장 작은 F값 선택후 추가
	void calcH();
	void calcF();
	void checkArrive();		//
	void showWay(AstarTile* tile);

private:

	AstarTile tile[TILE_Y][TILE_X];
	std::vector<AstarTile*> openList;
	std::vector<AstarTile*> closedList;

	ASTAR_STATE astarState;
	TILE_TYPE type;
	COLORREF color;

	int startx, starty;	//시작점
	int endx, endy;		//도착점
	int lastIndex;		//나중에 추가된 클로즈 리스트의 인덱스
	bool startPointSet;
	bool endPointSet;

	int Ci;
	int Cj;
	int Cg;

	RECT rc[6];
	HBRUSH newBrush;
	HBRUSH oldBrush;
	HFONT newFont, oldFont;

};