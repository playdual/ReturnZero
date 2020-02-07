#pragma once
//게임 내에서 쓰이는 Enum과 구조체 메크로 등을 정의 합니다.

#define TILESIZE 32 //오른쪽 화면 타일 사이즈
#define TILEX 20	//왼쪽화면 타일 사이즈 X
#define TILEY 20	//왼쪽화면 타일 사이즈 Y
#define TILE_WIDTH 100
#define TILE_HEIGHT 100


#define TILESIZEX TILEX * TILESIZE
#define TILESIZEY TILEY * TILESIZE

//ȭ�� ������ �̹��� Ÿ�� ����
#define SAMPLETILEX 20
#define SAMPLETILEY 8

enum class TileType
{
	TileTypeFloor,
	TileTypeHouse,
	TileTypeBush,
	TileTypeTree
};

//맵툴에서 사용할 녀석
enum CTRL
{
	CTRL_SAVE,
	CTRL_LOAD,
	CTRL_TERRAINDRAW,
	CTRL_OBJDRAW,
	CTRL_ERASER,
	CTRL_MAP1,
	CTRL_MAP2,
	CTRL_END
};

//����(EX.������ ���带 ���� �ϰų� �̵��� �� ���� �������)
enum TERRAIN
{
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_END
};

//������Ʈ(EX :�������ʿ� ��ġ. �����̰ų� �μ����ų� �ϴ� �༮ ��� ��ȭ�� �ټ� �ִ� ��ü)
enum OBJECT
{
	OBJ_BLOCK1,
	OBJ_BLOCK3,
	OBJ_BLOCKS,
	OBJ_FLAG1,
	OBJ_FLAG2,
	OBJ_TANK1,
	OBJ_TANK2,
	OBJ_NONE
};
//��ġ ��ǥ
enum POS
{
	POS_FLAG1,
	POS_FLAG2,
	POS_TANK1,
	POS_TANK2

};
//Ÿ�� ����ü
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;

	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
};
//�̹��� Ÿ�� ����ü
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;

};
//���� Ÿ�� ����ü
struct tagCurrentTile
{
	int x;
	int y;
};
