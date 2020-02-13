﻿#pragma once
#include "Game/GameScene/Scene.h"
#include "Game/GameObject/Items/Inventory.h"

class InvenScene 
	: public Scene
{
public:
	InvenScene(std::shared_ptr<Inventory> _inven);
	~ InvenScene();

public:
	virtual bool init() override;
	virtual void update(float _deltaTime) override;
	virtual void release() override;

	virtual void render(HDC hdc) override;
	virtual void afterRender(HDC hdc) override;
	virtual void debugRender(HDC hdc) override;

	// 디폴트 파는 씬
	void sellPotion();
	void sellImport();
	void sellPokeBall();

	// 디폴트 아이템 획득씬
	void buyPotionScene();
	void buyImportItem();
	void buyPokeBallItem();

	// 아이템 메뉴 
	void menuChoice(HDC hdc);


private:
	std::shared_ptr<Inventory> m_inven;
	Image* m_BackGround;
	
	// 인벤창 가방 이미지 //
	Image* m_ItemBag;
	Image* m_ImportBag;
	Image* m_PokeBallBag;
	// 인벤 태그 이미지 //
	Image* m_ItemTag;
	Image* m_ImporTag;
	Image* m_PokeBallTag;
	//  인벤 화살표 UI 이미지 //
	Image* m_nextArrow;
	Image* m_beforeArrow;
	// 인벤 선택 메뉴
	Image* m_InvenMenu;
	Image* m_invenMenuBottom;
	Image* m_currentPointer;

	INVENSCENETYPE m_invenSceneType;
	//인벤씬 변경시 사용할 카운트
	int		invenSceneCount;
	bool	isChangeScene;

	// UI 카운트 작업
	int		moveCount ;
	bool	isUp;

	// 상점 연습 작업
	int ShopCount;

	// 인벤이 배틀씬 중 켜지느냐? 아니냐 / 타운씬에서 켜지느냐? 아니냐
	bool isBattleScene;
	std::string  m_invenChoiceMenu[5] = { "쓴다" , "건네다" , "버린다" , "그만둠" , "어떻게 할까요?" };

	// 메뉴창 작업
	int pointerCount;

};

