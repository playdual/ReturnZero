#pragma once

#include "Scene.h"
#include "Game/GameObject/Tile.h"

struct SelectTileData {
	int inUIpositionX, inUIpositionY;
	UTIL::IRECT rect;
	class Image* img;
	std::string UiImageKey;
	TileAttribute attribute;

	void setTileAttribute(std::string _keyName, TileType _type, bool _isAfterRender) {
		UiImageKey = _keyName;
		img = IMAGEMANAGER->findImage(UiImageKey);
		attribute.isAfterRender = _isAfterRender;
		attribute.type = _type;
		attribute.tileKeyname = UiImageKey + 't';
	}
};

class MapToolScene
	: public Scene
{
public:
	MapToolScene() {}
	~MapToolScene() {}

public:
	bool init() override;
	void update(float _deltaTime) override;
	void release() override;

public:
	void render(HDC hdc) override;
	void afterRender(HDC hdc) override;
	void debugRender(HDC hdc) override;
	void cameraMove();

public:
	void treeVectorInit(int _pageCount);
	void tileVectorInit(int _pageCount);
	void bushVectorInit(int _pageCount);

public:
	void UIupdate();
	void UIrender(HDC hdc);


	void mainSelectUpdate();
	void mainSelectRender(HDC hdc);
	void bushSelectUpdate();
	void bushSelectRender(HDC hdc);
	void treeSelectUpdate();
	void treeSelectRender(HDC hdc);
	void tileSelectUpdate();
	void tileSelectRender(HDC hdc);
	void resetTileUpdate();
	void resetTileRender(HDC hdc);

	void saveLoadUpdate();
	void saveLoadRender(HDC hdc);
	void backButtonUpdate();
	void backButtonRender(HDC hdc);

	void loadMap();
	void saveMap();

private:
	int m_prevMouseX;
	int m_prevMousey;
	int m_pickedMouseX;
	int m_pickedMouseY;

private:
	bool m_isSettedMove = false;
	bool m_isMouseMoveActive = false;
	bool m_settedColor = false;

	UTIL::IRECT m_selectRect;
	bool onSelect;
	bool startedSelect;

	//for menu
private:
	bool m_mainSelect = true;
	bool m_tileSelect = false;
	bool m_treeSelect = false;
	bool m_bushSelect = false;

private:
	UTIL::IRECT clientRect;
	UTIL::IRECT tileSelectRect;
	UTIL::IRECT treeSelectRect;
	UTIL::IRECT bushSelectRect;
	UTIL::IRECT saveSelectRect;
	UTIL::IRECT loadSelectRect;
	UTIL::IRECT backButtonRect;
	UTIL::IRECT resetTileButtonRect;

private:
	char* tileSelectStr = "tileSelect";
	char* treeSelectStr = "treeSelect";
	char* bushSelectStr = "bushSelect";
	char* saveSelectStr = "saveSelect";
	char* loadSelectStr = "loadSelect";

	char* inTileSelectStr = "choose tile type";
	char* inTreeSelectStr = "choose tree type";
	char* inBushSelectStr = "choose bush type";
	const int textOffsetX = 50;
	const int textOffsetY = 25;
	const int inSelectStrX = 1200;
	const int inSelectStrY = 20;
	const int inUiTileWidth = 50;
	const int inUiTileHeight = 50;

private:
	std::vector<std::vector<SelectTileData>> tileVector;
	std::vector<std::vector<SelectTileData>> treeVector;
	std::vector<std::vector<SelectTileData>> bushVector;

	int tileSelectPage;
	int treeSelectPage;
	int bushSelectPage;

private:
	TileAttribute selectedAttribute;
	void resetSelectedAttribute();

public:
	//virtual LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

private:
	std::vector<std::shared_ptr<Tile>> m_Tiles;
};