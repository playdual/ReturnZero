#include "stdafx.h"
#include "MainGame.h"
#include "Common/GameManagers.h"
#include "GameScene/TownScene.h"
#include "GameScene/BattleScene.h"
#include "GameScene/InvenScene.h"
#include "GameObject/Items/Inventory.h"
#include "Game/GameScene/shopScene.h"

MainGame::MainGame()
{ 
	
}

MainGame::~MainGame()
{
	
}

void MainGame::myloadImage(std::string defaultName, std::string path, int _size)
{
	std::string bmp = ".bmp";
	path += '/';
	for (int i = 1; i <= _size; ++i) {
		std::string key = defaultName + std::to_string(i);
		IMAGEMANAGER->addImage(key, (path + key + bmp).c_str(), TILE_WIDTH, TILE_HEIGHT, true, RGB(255, 0, 255));
	}
}

HRESULT MainGame::init()
{
	GameNode::init();
	myloadImage("BigTree",			"Images/afterRender", 2);
	myloadImage("profOhouseTop",	"Images/afterRender", 7);
	myloadImage("House0",			"Images/afterRender", 5);
	myloadImage("BedTop", "Images/afterRender", 3);
	myloadImage("Carpet", "Images/Tile/GeneralTile", 3);
	myloadImage("SpacialMachineTop", "Images/afterRender", 2);
	myloadImage("BookShelf2Top", "Images/afterRender", 2);

	myloadImage("TechoTown_",	"Images/TechoTown", 480);
	myloadImage("ProfOHouse_",	"Images/Tile/TechoTownInner/ProfOHouse", 169);
	myloadImage("RedHouse_1F_", "Images/Tile/TechoTownInner/RedHouse_1F", 120);
	myloadImage("RedHouse_2F_", "Images/Tile/TechoTownInner/RedHouse_2F", 99);
	myloadImage("RivalHouse_",	"Images/Tile/TechoTownInner/RivalHouse", 118);
	myloadImage("Route01_",		"Images/Route01", 960);

	IMAGEMANAGER->addImage("OutOfRange", "Images/Tile/GeneralTile/OutOfRange.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TreePotTop", "Images/afterRender/TreePotTop.bmp", TILE_WIDTH, TILE_HEIGHT, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TvTop", "Images/afterRender/TvTop.bmp", TILE_WIDTH, TILE_HEIGHT, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("MailBox2",		"Images/afterRender/MailBox2.bmp", TILE_WIDTH, TILE_HEIGHT, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("trainersMan",	"Images/Trainers/trainers_man.bmp", 64 * 3, 64 * 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pailiFront",	"Images/pocketmons/pailiFront.bmp", 60 * 3, 61 * 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pailiBack",		"Images/pocketmons/pailiBack.bmp", 61 * 3, 61 * 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pikachuFront",	"Images/pocketmons/PikachuFront.bmp", 61 * 3, 61 * 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("GrassTile1",	"images/GrassTile1.bmp",		TILE_WIDTH, TILE_HEIGHT, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Bush1",			"images/Bush1.bmp",				TILE_WIDTH, TILE_HEIGHT, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Tree1",			"images/Tree1.bmp",				TILE_WIDTH, TILE_HEIGHT + 23, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Flower",	"Images/Tile/Object/Flower1Frame.bmp", TILE_WIDTH * 5, TILE_HEIGHT, 5, 1, true, RGB(255, 0, 255));

	//rsc
	IMAGEMANAGER->addImage("인벤토리씬",		"Images/InvenScene.bmp",		0, 0, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->addImage("아이템창",		"Images/itemBag.bmp",			62 * 5, 64 * 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("임폴트창",		"Images/importBag.bmp",			62 * 5, 64 * 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("포케볼창",		"Images/ballBag.bmp",			62 * 5, 64 * 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아이템창태그",	"Images/ItemsTag.bmp",			67 * 5, 34 * 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("임폴트창태그",	"Images/KeyItemsTag.bmp",		67 * 5, 34 * 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("포케볼창태그",	"Images/BallTag.bmp",			67 * 5, 34 * 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("이전화면표시",	"Images/BefoeImage.bmp",		18 * 5, 17 * 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("다음화면표시",	"Images/NextImage.bmp",			18 * 5, 17 * 5, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("현재아이템표시", "Images/itemPointer.bmp",		28 * 4, 28 * 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아이템인벤메뉴", "Images/menu.bmp", 63 * 5, 63 * 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("그외인벤메뉴", "Images/menu.bmp", 63 * 5, 63 * 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("배틀씬인벤메뉴", "Images/menu.bmp", 63 * 5, 68 * 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인벤메뉴상세", "Images/invenMenuBottom.bmp", 182 * 3, 29 * 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("playerimg", "images/newPlayer2.bmp", 64 * 4, 440, 4, 5, true, RGB(255, 0, 255));
	
	// shopImages
	IMAGEMANAGER->addImage("프랜들리샵", "Images/friendShop.bmp", 176 * 4, 132 * 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("프랜들리샵확대", "Images/friendShop.bmp", 792, 594, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("상점NPC대화상자", "Images/talkBox.bmp", 246 * 4, 46 * 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("상점메인메뉴", "Images/menu.bmp", 63 * 7, 63 * 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("상점돈상태창", "Images/moneyBox.bmp", 417, 218, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("상점아이템메뉴리스트", "Images/shopBuyIItemList.bmp", 600, 500, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("상점아이템사기메뉴바텀", "Images/shopBuyItemBottom.bmp", 240*5, 48*5, true, RGB(255, 0, 255));


	//pocketmon Img
	IMAGEMANAGER->addImage("CharmanderFront",		"images/pocketmons/CharmanderFront.bmp", 100*2, 100 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("CharmanderBack",		"images/pocketmons/CharmanderBack.bmp", 100 * 2, 100 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CharmanderIcon",	"images/pocketmons/CharmanderIcon.bmp", 230, 115, 2, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("BulbasaurFront",		"images/pocketmons/BulbasaurFront.bmp", 100 * 2, 100 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BulbasaurBack",			"images/pocketmons/BulbasaurBack.bmp", 100 * 2, 100 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BulbasaurIcon",	"images/pocketmons/BulbasaurIcon.bmp", 230, 115, 2, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("SquirtleFront",			"images/pocketmons/SquirtleFront.bmp", 100 * 2 , 100 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("SquirtleBack",			"images/pocketmons/SquirtleBack.bmp", 100 * 2, 100 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SquirtleIcon",		"images/pocketmons/SquirtleIcon.bmp", 230, 115, 2, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("PidgeyFront",			"images/pocketmons/PidgeyFront.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PidgeyBack",			"images/pocketmons/PidgeyBack.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PidgeyIcon",		"images/pocketmons/PidgeyIcon.bmp", 230, 115, 2, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("PikachuFront",			"images/pocketmons/PikachuFront.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PikachuBack",			"images/pocketmons/PikachuBack.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PikachuIcon",		"images/pocketmons/PikachuIcon.bmp", 230, 115, 2, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("CaterpieFront",			"images/pocketmons/CaterpieFront.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("CaterpieBack",			"images/pocketmons/CaterpieBack.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CaterpieIcon",		"images/pocketmons/CaterpieIcon.bmp", 230, 115, 2, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("RattataFront",			"images/pocketmons/RattataFront.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("RattataBack",			"images/pocketmons/RattataBack.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RattataIcon",		"images/pocketmons/RattataIcon.bmp", 230, 115, 2, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("VulpixFront",			"images/pocketmons/VulpixFront.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("VulpixBack",			"images/pocketmons/VulpixBack.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("VulpixIcon",		"images/pocketmons/VulpixIcon.bmp", 230, 115, 2, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("OddishFront",			"images/pocketmons/OddishFront.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("OddishBack",			"images/pocketmons/OddishBack.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("OddishIcon",		"images/pocketmons/OddishIcon.bmp", 230, 115, 2, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("PoliwagFront",			"images/pocketmons/PoliwagFront.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PoliwagBack",			"images/pocketmons/PoliwagBack.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PoliwagIcon",		"images/pocketmons/PoliwagIcon.bmp", 230, 115, 2, 1, true, RGB(255, 0, 255));

	//pocketMon Sex
	IMAGEMANAGER->addImage("WomanSex",				"images/sexwoman.bmp", 30, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ManSex",				"images/sexman.bmp", 30, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("playerShadow",			"images/playerShadow.bmp", TILE_WIDTH, TILE_HEIGHT, true, RGB(255, 0, 255));

	//pocketMon Bag UI
	IMAGEMANAGER->addImage("Base",			"images/poketmonbagBase.bmp",		0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mainOn",		"images/pocketmonBagMainOn.bmp",	0, 0, 368, 287, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mainOff",		"images/pocketmonBagMainOff.bmp",	0, 0, 367, 286, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("sun0On",		"images/pocketmonBagSubOn.bmp",		0, 0, 651, 119, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("sun0Off",		"images/pocketmonBagSubOff.bmp",	0, 0, 651, 119, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("sun1On",		"images/pocketmonBagSubOn.bmp",		0, 0, 651, 119, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("sun1Off",		"images/pocketmonBagSubOff.bmp",	0, 0, 651, 119, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("sun2On",		"images/pocketmonBagSubOn.bmp",		0, 0, 651, 119, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("sun2Off",		"images/pocketmonBagSubOff.bmp",	0, 0, 651, 119, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("sun3On",		"images/pocketmonBagSubOn.bmp",		0, 0, 651, 119, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("sun3Off",		"images/pocketmonBagSubOff.bmp",	0, 0, 651, 119, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("sun4On",		"images/pocketmonBagSubOn.bmp",		0, 0, 651, 119, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("sun4Off",		"images/pocketmonBagSubOff.bmp",	0, 0, 651, 119, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("cancleOn",		"images/cancleon.bmp",				0, 0, 250, 130, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("cancleOff",		"images/cancleoff.bmp",				0, 0, 250, 130, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("mainSwapOn", "images/pocketmonBagMainSwapChoose.bmp",			0, 0, 368, 287, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mainSwapOff", "images/pocketmonBagMainSwapUnChoose.bmp",		0, 0, 367, 286, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("subSwapOn", "images/pocketmonBagSubSwapChoose.bmp",		0, 0, 651, 119, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("subSwapOff", "images/pocketmonBagSubSwapUnChoose.bmp",	0, 0, 651, 119, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("BagHpBarGreen",	"images/HpBarGreen.bmp",			0, 0, 208, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BagHpBarYellow","images/HpBarYellow.bmp",			0, 0, 208, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BagHpBarRed",	"images/HpBarRed.bmp",				0, 0, 208, 15, true, RGB(255, 0, 255));
	
	//Pokemon Status
	IMAGEMANAGER->addImage("PokemonDie", "images/PokemonDie.bmp", 0, 0, 110, 50, true, RGB(255, 0, 255));

	//Menu and Cursor
	IMAGEMANAGER->addImage("MainMenuimg",			"images/menu.bmp",			0,0, 300, 530, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PokemonMenuimg",		"images/menu.bmp",			0,0, 250, 360, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("menuindeximg",			"images/menuindex.bmp",		0,0, 30, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PokemonMenuindeximg",	"images/menuindex.bmp",		0,0, 30, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TrainnerCardimg",		"images/TrainnerCard.bmp",	0,0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TrainnerCardplayerimg",	"images/playerCard.bmp",	0,0, 150, 350, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TrainnerCardBelt",		"images/PokemonBelt.bmp",	0,0, 1000, 95, true, RGB(255, 0, 255));

	//NPC
	IMAGEMANAGER->addImage("GrandFatherFront", "Images/NPC/GrandFatherFront.bmp", 0, 0, 80, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("GrandFatherBack", "Images/NPC/GrandFatherBack.bmp", 0, 0, 80, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("GrandFatherLeft", "Images/NPC/GrandFatherLeft.bmp", 0, 0, 80, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("GrandFatherRight", "Images/NPC/GrandFatherRight.bmp", 0, 0, 80, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("MotherFront", "Images/NPC/MotherFront.bmp", 0, 0, 80, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("MotherBack", "Images/NPC/MotherBack.bmp", 0, 0, 80, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("MotherLeft", "Images/NPC/MotherLeft.bmp", 0, 0, 80, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("MotherRight", "Images/NPC/MotherRight.bmp", 0, 0, 80, 80, true, RGB(255, 0, 255));

	//sound
	SOUNDMANAGER->addStream("NewBarkTown", "Sounds/NewBarkTown.mp3", true);
	SOUNDMANAGER->addStream("Battle", "Sounds/Battle.mp3", true);
	SOUNDMANAGER->addStream("Ok", "Sounds/Ok.mp3", false);
	
	//=============
	// battle Ui //
	//=============
	IMAGEMANAGER->addImage("battleTemp", "images/battleTemp2.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("backGroundImg", "images/BattleUi/backGroundImg.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("enemyStatus",	"images/BattleUi/enemyStatus.bmp",	0, 0, 100*4+24, 29*4+22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("playerStatus",	"images/BattleUi/playerStatus.bmp",	0, 0, 104*4+29, 37*4+30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("arrow",	"images/BattleUi/arrow.bmp",				0, 0, 6*5, 10*5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("explainRect",	"images/BattleUi/explainRect.bmp",	240*4+64, 48*4+38, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("npcPocketmonBall",	"images/BattleUi/npcPocketmonBall.bmp",	0, 0, 104, 12, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("playerPocketmonBall",	"images/BattleUi/playerPocketmonBall.bmp",	0, 0, 104, 12, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("skillSelect",	"images/BattleUi/skillSelect.bmp",	0, 0, 240*4+64, 48*4+38, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stayArrow",	"images/BattleUi/stayArrow.bmp",		0, 0, 10*4, 6*4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("enemyBottom",	"images/BattleUi/enemyBottom.bmp",	0, 0, 128*4+34, 34*4+20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("playerBottom",	"images/BattleUi/playerBottom.bmp",	0, 0, 120*4+34, 15*4+20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("currentExp", "images/BattleUi/currentExp.bmp",	    0, 0, 7*4+246, 2*4+1, true, RGB(255, 0, 255));	
	IMAGEMANAGER->addImage("greenHpBar", "images/BattleUi/greenHpBar.bmp",	    0, 0, 9*3+246, 3*5, true, RGB(255, 0, 255));	
	IMAGEMANAGER->addImage("levelUpRect", "images/BattleUi/levelUpPopUp.bmp",    0, 0, 389, 491, true, RGB(255, 0, 255));	
	IMAGEMANAGER->addImage("ball", "images/BattleUi/ball.bmp",    0, 0, 12*4, 12*4, true, RGB(255, 0, 255));	
	IMAGEMANAGER->addImage("catchSuccess", "images/BattleUi/catchSuccess.bmp",    0, 0, 16*4, 16*4, true, RGB(255, 0, 255));	
	EFFECTMANAGER->addEffect("catchSuccessEffect", "Images/BattleUi/catchSuccessEffect.bmp", 32*3, 24*3, 32*3, 12*3, 1, 0.1f, 100);


	//==============
	// battle ani //
	//==============
	IMAGEMANAGER->addFrameImage("trainerThrowBall", "Images/Trainers/trainersThrowBall.bmp", 320+5*140, 64*3+18, 5, 1, true, RGB(255, 0, 255));
	ANIMANAGER->addDefAnimation("trainerThrowBallAni", "trainerThrowBall", 5, false, false);
	//IMAGEMANAGER->addFrameImage("trainerThrowBall", "images/Trainers/trainerThrowBall.bmp", 320, 64, 5, 1, true, RGB(255, 0, 255));
	//ANIMANAGER->addDefAnimation("trainerThrowBallAni", "trainerThrowBall", 2, false, false);
	/*IMAGEMANAGER->addFrameImage("trainerThrowBall", "images/Trainers/trainerThrowBall.bmp", 320, 64, 5, 1, true, RGB(255, 0, 255));
	ANIMANAGER->addDefAnimation("trainerThrowBallAni", "trainerThrowBall", 2, false, false);*/
	
	IMAGEMANAGER->addFrameImage("throwBall", "Images/BattleUi/throwBall.bmp", 1888, 341, 8, 1, true, RGB(255, 0, 255));
	ANIMANAGER->addDefAnimation("throwBallAni", "throwBall", 5, false, false);

	IMAGEMANAGER->addFrameImage("ballOpen", "Images/BattleUi/ballOpen.bmp", 12*4, 45*4, 1, 3, true, RGB(255, 0, 255));
	ANIMANAGER->addDefAnimation("ballOpenAni", "ballOpen", 10, true, false);

	IMAGEMANAGER->addFrameImage("shakeBall", "Images/BattleUi/shakeBall.bmp", 112 * 4, 48 * 4, 7, 3, true, RGB(255, 0, 255));
	ANIMANAGER->addDefAnimation("shakeBallAni", "shakeBall", 20, false, false);

	IMAGEMANAGER->addFrameImage("pocketmonCatchEffect", "Images/BattleUi/pocketmonCatchEffect.bmp", 2000, 120, 8, 1, true, RGB(255, 0, 255));
	ANIMANAGER->addDefAnimation("pocketmonCatchEffectAni", "pocketmonCatchEffect", 10, false, false);


	//
	MAPMANGER->init();
	ITEMMANAGER->init();
	POCKETMONMANAGER->init();

	//add Scene
	IMAGEMANAGER->addImage("bg", "Images/temp.bmp", 0, 0, WINSIZEX, WINSIZEY);
	SOUNDMANAGER->addStream("bgs", "Sounds/NewBarkTown.mp3", true);
	IMAGEMANAGER->addImage("현재아이템표시", "Images/itemPointer.bmp", 28 * 5, 28 * 5, true, RGB(255, 0, 255));
	std::shared_ptr<Inventory> inven = std::make_shared<Inventory>();
	inven->init();
	SCENEMANAGER->addScene("town", new TownScene);
	SCENEMANAGER->addScene("battle", new BattleScene);
	SCENEMANAGER->addScene("inven", new InvenScene(inven));
	SCENEMANAGER->addScene("friendlyShop", new shopScene(inven));
	SCENEMANAGER->scenePush("town");
	sceneInit = true;

	//now! our First Sound!
	//SOUNDMANAGER->playSound("NewBarkTown", Channel::eChannelBgm);
	


	return S_OK;
}

void MainGame::release()
{
	GameNode::release();
	MAPMANGER->release();
	POCKETMONMANAGER->release();
	ITEMMANAGER->release();
	BATTLEMANAGER->release();

	MAPMANGER->Destroy();
	POCKETMONMANAGER->Destroy();
	ITEMMANAGER->Destroy();
	BATTLEMANAGER->Destroy();
}  

void MainGame::update()
{
	if (KEYMANAGER->isOnceKeyDown(GAME_RECTMODE))
		m_showRect = !m_showRect;
	if (KEYMANAGER->isOnceKeyDown(GAME_SHOWFPS))
		m_showFPS = !m_showFPS;
	
	TIMEMANAGER->update(60.f);
	deltaTime = TIMEMANAGER->getElapsedTime();
	EFFECTMANAGER->update();
	SCENEMANAGER->update(deltaTime);	ANIMANAGER->update(deltaTime);
	
}

void MainGame::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);

	SCENEMANAGER->render(getMemDC());
	SCENEMANAGER->afterRender(getMemDC());
	EFFECTMANAGER->render(getMemDC());
	if(m_showRect)
		SCENEMANAGER->debugRender(getMemDC());
	if (m_showFPS)
		TIMEMANAGER->render(getMemDC());

	getBackBuffer()->render(getHDC(), 0, 0);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	if (sceneInit)
		return SCENEMANAGER->getCurScene()->SceneProc(hWnd, iMessage, wParam, lParam);
	else {
		switch (iMessage)
		{
		case WM_MOUSEMOVE:
			m_ptMouse.x = LOWORD(lParam);
			m_ptMouse.y = HIWORD(lParam);
			break;
		case WM_DESTROY:
			m_bLoop = false;
			PostQuitMessage(0);
			break;
		}
	}	
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
