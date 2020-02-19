#include "stdafx.h"
#include "TownScene.h"
#include "Common/GameManagers.h"

TownScene::TownScene()
{
}


TownScene::~TownScene()
{
}

bool TownScene::init()
{
	SOUNDMANAGER->playSound("NewBarkTown", Channel::eChannelBgm);
	m_chat = IMAGEMANAGER->findImage("상점NPC대화상자");
	battleInit = IMAGEMANAGER->findImage("BattleInit");
	//player init
	m_player = std::make_shared<player>();

	m_map = MAPMANGER->findMap("RedHouse2F");
	MAPMANGER->connectPlayerInfo(m_player);
	m_player->reLocate(m_map->getStartPositionX(), m_map->getStartPositionY());
	m_player->init();

	//menus
	m_menurect = UTIL::IRectMake(WINSIZEX / 2 + 200, 10, 300, 530);
	m_menuImg = IMAGEMANAGER->findImage("MainMenuimg");

	m_IndexMenuRect = UTIL::IRectMake(WINSIZEX / 2 + 230, 70, 15, 20);
	m_IndexMenuImg = IMAGEMANAGER->findImage("menuindeximg");
	//기본 메뉴 인덱스
	m_menuIndex = 0;

	//트레이너 카드 이미지
	m_TrainnerCard = IMAGEMANAGER->findImage("TrainnerCardimg");
	m_TrainnerCardPlayer = IMAGEMANAGER->findImage("TrainnerCardplayerimg");
	m_PokemonBelt = IMAGEMANAGER->findImage("TrainnerCardBelt");

	//최대 메뉴갯수
	Menu.push_back(MenuBar("리포트", 3));
//	Menu.push_back(MenuBar("설정", 4));
	Menu.push_back(MenuBar("가방", 1));
	Menu.push_back(MenuBar("닫기", 5));
	Menu.push_back(MenuBar("플레이어", 2));




	menuUpdate();
	return true;
}

//menu 관련
void TownScene::menuUpdate()
{
	std::sort(Menu.begin(), Menu.end(), [](const MenuBar& _e1, const MenuBar& _e2) {
		if (_e1.menuNum < _e2.menuNum)
			return true;
		return false;
	});
	m_menuIndexMax = Menu.size() - 1;
}
void TownScene::onMenu()
{


	if (!isTrainnerCard && !isReport)
	{
		if (KEYMANAGER->isOnceKeyDown(P1_DOWN))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);
			m_menuIndex++;
		}
		else if (KEYMANAGER->isOnceKeyDown(P1_UP))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);
			m_menuIndex--;
		}

		if (m_menuIndex < 0)
		{
			m_menuIndex = m_menuIndexMax;
		}
		else if (m_menuIndex > m_menuIndexMax)
		{
			m_menuIndex = 0;
		}

		//메뉴인덱스(화살표)
		m_IndexMenuRect = UTIL::IRectMake(WINSIZEX / 2 + 230, 70 + m_menuIndex * 70, 15, 20);

		//포켓몬 메뉴바 추가 삭제 알고리즘
		if (m_player->getCountPocketMon() == 0) {
			delMenu("포켓몬");
			isPocketmonMenuOn = false;
		}
		else {
			if (isPocketmonMenuOn == false) {
				addMenu(MenuBar("포켓몬", 0));
				isPocketmonMenuOn = true;
			}
		}

		if (Menu[m_menuIndex].menuName == "포켓몬" && KEYMANAGER->isOnceKeyDown(P1_Z))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);
			SCENEMANAGER->scenePush("PocketmonBagScene");
		}
		if (Menu[m_menuIndex].menuName == "가방" && KEYMANAGER->isOnceKeyDown(P1_Z))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);
			SCENEMANAGER->scenePush("inven");
		}

		if (Menu[m_menuIndex].menuName == "닫기" && KEYMANAGER->isOnceKeyDown(P1_Z))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);
			m_player->setisMenu(false);
		}

		if (Menu[m_menuIndex].menuName == "플레이어" && KEYMANAGER->isOnceKeyDown(P1_Z))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);
			isTrainnerCard = true;
		}

		if (Menu[m_menuIndex].menuName == "리포트" && KEYMANAGER->isOnceKeyDown(P1_Z))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);
		
			isReport = true;
			m_player->setisMoveStop(true);
		}

		if (Menu[m_menuIndex].menuName == "설정" && KEYMANAGER->isOnceKeyDown(P1_Z))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);
		}
	}
}
void TownScene::update(float _deltaTime)
{
	if (isBattle)
	{
		pastTime += _deltaTime;
		if (pastTime > battleInitFrameDelay) {
			pastTime = 0.f;
			battleInitIdex++;
			if (battleInitIdex >= battleInit->getMaxFrameX()) {
				Tile& curTile = m_map->getSpecifyTile(m_player->getPlayerBlockX(), m_player->getPlayerBlockY());
				auto innerPocketmon = curTile.getInnerPocketMon();
				if (innerPocketmon.first != "")
					BATTLEMANAGER->battleStart(m_player, nullptr, innerPocketmon.first, innerPocketmon.second);
				m_player->BattleEnd();
				isBattle = false;
				battleInitIdex = 0;
			}
		}
		return;
	}

	if (!isBattle) {
		if (!SOUNDMANAGER->isPlaying(Channel::eChannelBgm)) {
			if (MAPMANGER->getCurMapName() == "Route01")
				SOUNDMANAGER->playSound("Route", Channel::eChannelBgm);
			if (MAPMANGER->getCurMapName() == "TechoTown")
				SOUNDMANAGER->playSound("NewBarkTown", Channel::eChannelBgm);
		}
	}	
	PlaytimeSec = TIMEMANAGER->getWorldTime();
	if (PlaytimeSec > 59)PlaytimeSec %= 60;
	PlaytimeMin = TIMEMANAGER->getWorldTime() / 60;
	if (PlaytimeSec % 2 == 0)isColon = true;
	else isColon = false;

	if (isReport)
	{
		reportCnt += 1;
	}

	if (reportCnt == 180)
	{
		SOUNDMANAGER->playSound("Report", Channel::eChannelEffect);
	}
	else if (reportCnt >= 250)
	{
		isReport = false;
		m_player->setisMoveStop(false);
		reportCnt = 0;
	}

	if (isTrainnerCard)
	{
		if (KEYMANAGER->isOnceKeyDown(GAME_MENU) || KEYMANAGER->isOnceKeyDown(P1_X))
		{
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);
			isTrainnerCard = false;
		}
	}

	//temp handle last info : 타운씬에서는 아직까진 이전 씬정보를 사용할 필요가 없다.
	if (SCENEMANAGER->getLastSceneReturnInfo() != nullptr)
	{
		SCENEMANAGER->eraseLastInfo();
	}

	//player와 map 업데이트
	m_player->update(_deltaTime);
	m_map->setPlayerPosition(m_player->getPlayerBlockX(), m_player->getPlayerBlockY());
	m_map->update(_deltaTime);


	//야생배틀
	if (m_player->getisBattle())
	{
		SOUNDMANAGER->stopChannel(Channel::eChannelBgm);				//start를 배틀끝날때 해줘야함
		SOUNDMANAGER->playSound("Battle", Channel::eChannelBattleBgm);	//stop을 배틀끝날때 해줘야함
		isBattle = true;
	}
	

	//맵 체인지 확인
	if (m_player->getisChangeMap())
	{
		auto tile = MAPMANGER->getCurMap()->getSpecifyTile(m_player->getPlayerBlockX(), m_player->getPlayerBlockY());
		std::string nextMapName = tile.getNextMapKey();

		m_map = MAPMANGER->findMap(nextMapName);
		m_player->reLocate(tile.getNextMapIdx().x, tile.getNextMapIdx().y);
		m_player->MoveSetZero();
		m_player->isNotChangeMap();
	}

	//메뉴 열때
	if (m_player->getisMenu())
	{
		onMenu();
		menuUpdate();
	}
}

void TownScene::render(HDC hdc)
{

	if (!isTrainnerCard)
	{
		m_map->render(hdc);
		m_player->render(hdc);
	}
	if (isTrainnerCard)
	{
		m_TrainnerCard->render(hdc, 0, 0);
		m_TrainnerCardPlayer->render(hdc, 750, 200);

		UTIL::PrintText(hdc, "IDNo · 50726", "소야바른9", 590, 60, 80, RGB(208, 208, 200), true, RGB(0, 0, 0));
		UTIL::PrintText(hdc, "IDNo · 50726", "소야바른9", 585, 60, 80, RGB(96, 96, 96), true, RGB(0, 0, 0));

		UTIL::PrintText(hdc, "이름   플레이어", "소야바른9", 115, 160, 80, RGB(208, 208, 200), true, RGB(0, 0, 0));
		UTIL::PrintText(hdc, "이름   플레이어", "소야바른9", 110, 160, 80, RGB(96, 96, 96), true, RGB(0, 0, 0));

		UTIL::PrintText(hdc, "돈", "소야바른9", 115, 300, 80, RGB(208, 208, 200), true, RGB(0, 0, 0));
		UTIL::PrintText(hdc, "돈", "소야바른9", 110, 300, 80, RGB(96, 96, 96), true, RGB(0, 0, 0));

		std::string m_moneyCpy = std::to_string(m_player->getMoney());
		UTIL::PrintText(hdc, m_moneyCpy.c_str(), "소야바른9", 425, 300, 80, RGB(208, 208, 208), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, m_moneyCpy.c_str(), "소야바른9", 420, 300, 80, RGB(96, 96, 96), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, "원", "소야바른9", 595, 300, 80, RGB(208, 208, 208), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, "원", "소야바른9", 590, 300, 80, RGB(96, 96, 96), true, RGB(160, 112, 240));

		UTIL::PrintText(hdc, "포켓몬 도감", "소야바른9", 115, 390, 80, RGB(208, 208, 200), true, RGB(0, 0, 0));
		UTIL::PrintText(hdc, "포켓몬 도감", "소야바른9", 110, 390, 80, RGB(96, 96, 96), true, RGB(0, 0, 0));

		UTIL::PrintText(hdc, "151 마리", "소야바른9", 435, 390, 80, RGB(208, 208, 200), true, RGB(0, 0, 0));
		UTIL::PrintText(hdc, "151 마리", "소야바른9", 430, 390, 80, RGB(96, 96, 96), true, RGB(0, 0, 0));

		UTIL::PrintText(hdc, "플레이 시간", "소야바른9", 115, 470, 80, RGB(208, 208, 200), true, RGB(0, 0, 0));
		UTIL::PrintText(hdc, "플레이 시간", "소야바른9", 110, 470, 80, RGB(96, 96, 96), true, RGB(0, 0, 0));

		std::string m_timeMin = std::to_string(PlaytimeMin);
		std::string m_timeSec = std::to_string(PlaytimeSec);

		UTIL::PrintText(hdc, m_timeMin.c_str(), "소야바른9", 455, 470, 80, RGB(208, 208, 200), true, RGB(0, 0, 0));
		UTIL::PrintText(hdc, m_timeMin.c_str(), "소야바른9", 450, 470, 80, RGB(96, 96, 96), true, RGB(0, 0, 0));

		if (isColon)
		{
			UTIL::PrintText(hdc, " : ", "소야바른9", 495, 470, 80, RGB(208, 208, 200), true, RGB(0, 0, 0));
			UTIL::PrintText(hdc, " : ", "소야바른9", 490, 470, 80, RGB(96, 96, 96), true, RGB(0, 0, 0));
		}
		UTIL::PrintText(hdc, m_timeSec.c_str(), "소야바른9", 535, 470, 80, RGB(208, 208, 200), true, RGB(0, 0, 0));
		UTIL::PrintText(hdc, m_timeSec.c_str(), "소야바른9", 530, 470, 80, RGB(96, 96, 96), true, RGB(0, 0, 0));

		m_PokemonBelt->render(hdc, 15, 620);
	}
}

void TownScene::afterRender(HDC hdc)
{
	if (!isTrainnerCard)
	{
		m_map->afterRender(hdc);

		//메뉴
		if (m_player->getisMenu())
		{
			m_menuImg->render(hdc, m_menurect.left, m_menurect.top);

			m_IndexMenuImg->render(hdc, m_IndexMenuRect.left, m_IndexMenuRect.top);

			int cnt = 0;
			for (auto it = Menu.begin(); it != Menu.end(); ++it)
			{
				UTIL::PrintText(hdc, (*it).menuName.c_str(), "소야바른9", WINSIZEX / 2 + 270, 65 + cnt * 70, 65, RGB(0, 0, 0));
				cnt++;
			}
		}
	}
	m_player->afterRender(hdc);

	if (isReport && reportCnt <= 150)
	{
		m_chat->render(hdc, 0, 590);

		UTIL::PrintText(hdc, "리포트를 쓰는 중 입니다.", "소야바른9", 55, 625, 65, RGB(208, 208, 200), true, RGB(0, 0, 0));
		UTIL::PrintText(hdc, "리포트를 쓰는 중 입니다.", "소야바른9", 50, 625, 65, RGB(0, 0, 0), true, RGB(0, 0, 0));

		UTIL::PrintText(hdc, "잠시만 기다려주세요...", "소야바른9", 55, 695, 65, RGB(208, 208, 200), true, RGB(0, 0, 0));
		UTIL::PrintText(hdc, "잠시만 기다려주세요...", "소야바른9", 50, 690, 65, RGB(0, 0, 0), true, RGB(0, 0, 0));
	}
	else if (isReport && reportCnt > 150)
	{
		m_chat->render(hdc, 0, 590);
		UTIL::PrintText(hdc, "리포트를 꼼꼼히 기록했다!", "소야바른9", 55, 625, 65, RGB(208, 208, 200), true, RGB(0, 0, 0));
		UTIL::PrintText(hdc, "리포트를 꼼꼼히 기록했다!", "소야바른9", 50, 625, 65, RGB(0, 0, 0), true, RGB(0, 0, 0));
	}
	if (isBattle) {
		battleInit->frameRender(hdc, 0, 0, battleInitIdex, 0);
	}
}

void TownScene::debugRender(HDC hdc)
{
	m_map->debugRender(hdc);
	m_player->debugRender(hdc);

	if (m_player->getisMenu())
	{
		UTIL::DrawColorRect(hdc, m_menurect, RGB(255, 255, 0), true);
	}
}

void TownScene::addMenu(MenuBar _newMenu)
{
	Menu.push_back(_newMenu);
	menuUpdate();
}

void TownScene::delMenu(std::string _menuName)
{
	for (auto menubar = Menu.begin(); menubar != Menu.end(); ++menubar) {
		if (menubar->menuName == _menuName) {
			Menu.erase(menubar);
			break;
		}
	}
	menuUpdate();
}

void TownScene::release()
{
}
