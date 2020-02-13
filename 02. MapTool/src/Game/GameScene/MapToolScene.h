#pragma once

#include "Scene.h"
#include "Game/GameObject/Tile.h"
#include "Game/GameObject/Map.h"

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
	MapToolScene(std::string _mapName,int _width, int _height) {
		mapName = _mapName;
		mapWidth = _width;
		mapHeight = _height;
	}
	~MapToolScene() {}

public:
	bool init() override;
	void update(float _deltaTime) override;
	void release() override;
	void cameraMove();

public:
	void render(HDC hdc) override;
	void afterRender(HDC hdc) override;
	void debugRender(HDC hdc) override;

public:
	void treeVectorInit(int _pageCount);
	void tileVectorInit(int _pageCount);
	void bushVectorInit(int _pageCount);

public:
	void UIupdate();
	void UIrender(HDC hdc);
	void TileWindowUpdate(float _deltaTime);
	void TileWindowRender(HDC hdc);

	//always
	void mainSelectUpdate();
	void mainSelectRender(HDC hdc);
	void resetTileUpdate();
	void resetTileRender(HDC hdc);
	void backButtonUpdate();
	void backButtonRender(HDC hdc);
	void saveLoadUpdate();
	void saveLoadRender(HDC hdc);
	void resetSpecifyUpdate();
	void resetSpecifyRender(HDC hdc);
	void loadMap();
	void saveMap();
	

	//in each case
	void bushSelectUpdate();
	void bushSelectRender(HDC hdc);
	void treeSelectUpdate();
	void treeSelectRender(HDC hdc);
	void tileSelectUpdate();
	void tileSelectRender(HDC hdc);
	void specifyUpdate();
	void specifyRender(HDC hdc);
	void activateSetNextMapBlock();
	void activateSetStartPos();
	void activateSetAfterRender();


	void tileVectorPush(std::string imageKey, TileType _type, int page, int _size, bool _afterRender);
	void treeVectorPush(std::string imageKey, TileType _type, int page, int _size, bool _afterRender);
	void bushVectorPush(std::string imageKey, TileType _type, int page, int _size, bool _afterRender);

private:
	int m_prevMouseX;
	int m_prevMousey;
	int m_pickedMouseX;
	int m_pickedMouseY;

	bool m_isSettedMove = false;
	bool m_isMouseMoveActive = false;
	bool m_settedColor = false;

	UTIL::IRECT m_selectRect;
	bool onSelect;
	bool startedSelect;

	bool isSetAttribute = true;
	bool isSetPocketMon = false;
	bool isSetNextMap = false;

	//UI
private:
	bool m_mainSelect = true;
	bool m_tileSelect = false;
	bool m_treeSelect = false;
	bool m_bushSelect = false;
	bool m_specifySelect = false;
	bool m_nextMapSelect = false;
	bool m_setStartPos = false;
	bool m_setAfterRenderImage = false;

private:
	//mainMenu
	UTIL::IRECT tileSelectRect;
	UTIL::IRECT treeSelectRect;
	UTIL::IRECT bushSelectRect;
	UTIL::IRECT setSpecifyRect;
	UTIL::IRECT setActivateNextMapRect;

	//always
	UTIL::IRECT clientRect;
	UTIL::IRECT backButtonRect;
	UTIL::IRECT resetTileButtonRect;
	UTIL::IRECT resetSpecifyButtonRect;
	UTIL::IRECT saveSelectRect;
	UTIL::IRECT loadSelectRect;

	//in each case
	UTIL::IRECT pageFrontButton;
	UTIL::IRECT pageBackButton;
	UTIL::IRECT setNextMapButtonRect;
	UTIL::IRECT setPocketMonButtonRect;

	bool tileSelectRectSetted;
	bool treeSelectRectSetted;
	bool bushSelectRectSetted;
	bool setSpecifyRectSetted;
	bool resetTileButtonRectSetted;
	bool backButtonRectSetted;

	char* tileSelectStr = "tileSelect";
	char* treeSelectStr = "treeSelect";
	char* bushSelectStr = "bushSelect";
	char* saveSelectStr = "saveSelect";
	char* loadSelectStr = "loadSelect";
	char* inTileSelectStr = "choose tile type";
	char* inTreeSelectStr = "choose tree type";
	char* inBushSelectStr = "choose bush type";
	char* specifyPocketStr = "input pocketMonInfo";
	char* specifyNextMapStr = "input nextMapInfo";
	char* specifySelectStr = "specify tile type";
	char* settedInfo = "setted info : ";

	const int textOffsetX = 20;
	const int textOffsetY = 25;
	const int inSelectStrX = 1200;
	const int inSelectStrY = 20;
	const int inUiTileWidth = 50;
	const int inUiTileHeight = 50;
	const int UIOffset = 1000;

	bool m_settedPocketMon = false;
	bool m_settedNextMap = false;

	std::string settedNextMap;
	POINT settedNextMapIdx;
	std::string settedPocketMon;
	int settedPocketMonLevel;
	std::string settedSpecifyStr;

private:
	std::vector<std::vector<SelectTileData>> tileVector;
	std::vector<std::vector<SelectTileData>> treeVector;
	std::vector<std::vector<SelectTileData>> bushVector;
	int tileSelectPage;
	int tileSelectPageMax;
	int treeSelectPage;
	int treeSelectPageMax;
	int bushSelectPage;
	int bushSelectPageMax;

private:
	TileAttribute selectedAttribute;
	void resetTileSelectedAttribute();

private:
	int mapWidth;
	int mapHeight;
	int mapStartX;
	int mapStartY;
	std::string mapName;
	std::vector<std::shared_ptr<Tile>> m_Tiles;
};