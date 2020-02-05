#pragma once
//게임 내에서 쓰이는 Enum과 구조체 등을 정의 합니다.

enum class TileType
{
	TileTypeFloor,
	TileTypeHouse,
	TileTypeBush,
	TileTypeTree
};

#define TILE_WIDTH 50
#define TILE_HEIGHT 50