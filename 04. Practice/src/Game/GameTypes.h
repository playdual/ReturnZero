#pragma once
//게임 내에서 쓰이는 Enum과 구조체 등을 정의 합니다.

enum class TileType
{
	TileTypeFloor,
	TileTypeHouse,
	TileTypeBush,
	TileTypeTree
};

#define TILE_WIDTH 100
#define TILE_HEIGHT 100
#define TILE_OFFSETX -38
#define TILE_OFFSETY 33
