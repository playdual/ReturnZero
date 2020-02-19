#pragma once
#include "Game/GameObject/Object.h"

class NPC
	: public Object
{
public:
	NPC();
	NPC(int _bPosX, int _bPosY, std::string _name, NPCEventType _anotherEventType = NPCEventType::NPCNone, bool _ADHD = false);

public:
	virtual bool init() override;
	virtual void update(float _deltaTime) override;

public:
	virtual void render(HDC hdc) override;
	virtual void afterRender(HDC hdc) override;
	virtual void debugRender(HDC hdc) override;

public:
	void addSenario(std::string _scriptKey, Senario _senario);
	void activateNPC(Direction _dir);
	bool isOnActevated() { return isActivate; }
	void connectPocketInfo(std::vector<std::shared_ptr<class PocketMon>> _pokemons) { playerPokemons = _pokemons; }

private:
	void updateSenario(float _deltaTime);
	void updateShopEvent(float _deltaTime);
	void resetSenarioIndexData();
	void updateDialArrowPosition();

	//포켓몬 센터용 함수
private:
	void selectActionUpdate();
	void selectActionRender(HDC _hdc);
	void curePocket();

	//포켓몬 센터용 변수
private:
	class Image* m_SelectPointer;
	bool isOnSelectAction = false;
	std::vector<std::shared_ptr<PocketMon>> playerPokemons;
	std::string cureStr = "예";
	std::string noncureStr = "아니오";
	int SelectArrowY1 = 360;
	int SelectArrowY2 = 420;
	int curArrowY = 360;

	//AlphaEffect
private:
	Image* alphaEffect;
	int curAlpha = 0;
	bool isOnAlphaEffect = false;
	bool completeAlphaEffect = false;
	bool negative = false;
	void alphaUpdate();

private:
	Image* m_Img[4];
	Image* m_Dialog;
	Image* m_DialCopleteArrow;
	Image* m_SelectBox;
	UTIL::IRECT m_absRect;
	UTIL::IRECT m_outRect;
	UTIL::IRECT m_DialCompleteArrowRect;

	std::map<std::string, Senario> m_Scripts;
	Senario m_curSenario;
	std::string m_Name;

	Direction m_PrintDirection;
	Direction m_DefaultDirection;
	int m_blockPositionX;
	int m_blockPositionY;
	bool isADHD = false;
	bool isCanprint = false;
	bool isActivate = false;
	bool hasAnotherEvent = false;
	NPCEventType anoterEventType = NPCEventType::NPCNone;



	//시나리오 출력용
private:
	bool onSenarioPrint = false;

	float addCharacterDelay = 0.1f;
	float pastTime = 0.f;

	std::wstring firstOutStr;
	std::wstring secondOutStr;

	bool completedFirstOut = false;
	bool completedSecondOut = false;
	
	int firstStrIndex = 0;
	int secondStrIndex = 0;
	int senarioIndex = 0;
	int movedArrowDist = 0;
	int arrowDirection = 1;
	const int dialArrowDistLimit = 7;

private:
	friend class MapManager;
};
