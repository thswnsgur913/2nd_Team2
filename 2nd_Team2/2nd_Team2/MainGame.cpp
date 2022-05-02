#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"

#include "GameClient.h"
#include "EndingScene.h"


// OBJ
#include "Player.h"
#include "Item.h"
#include "BehaviorA.h"
#include "BehaviorB.h"
#include "BehaviorC.h"
#include "BehaviorBoss.h"
#include "ObjLine.h"
#include "MovePlatform.h"

// UI
#include "FrontUI.h"
#include "BackUI.h"
#include "WeaponBag.h"

#include "BmpMgr.h"

int CMainGame::Life = 3;
int CMainGame::TotalKillCount = 0;
int CMainGame::KillCount = 0;
int CMainGame::BossCount = BOSS_APPEAR_COUNT;

bool CMainGame::bBoss = false;
long int CMainGame::Score = 0;
int CMainGame::Level = 1;
int CMainGame::PlayTime = 0;
float CMainGame::DeadTime = 0.f;

const float CMainGame::StageDeadTime = 100.f;

CMainGame::CMainGame()
	: m_dwTime(GetTickCount()),
	  m_bMonsterOnOff(false)
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::ResourceLoad() {
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map.bmp", L"Map");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/DragonL.bmp", L"BossMonster");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BatL.bmp", L"MonsterA");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/ScolpionL.bmp", L"MonsterB");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BearL.bmp", L"MonsterC");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/KirbySuperR.bmp", L"PlayerSuperR");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/KirbySuperL.bmp", L"PlayerSuperL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/KirbyWingR.bmp", L"PlayerWingR");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/KirbyWingL.bmp", L"PlayerWingL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/KirbyR.bmp", L"PlayerR");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/KirbyNormalR.bmp", L"PlayerNormalR");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/KirbyL.bmp", L"PlayerL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/KirbyNormalL.bmp", L"PlayerNormalL");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/LifeItem.bmp", L"ITEM_LIFE");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/GodModeItem.bmp", L"ITEM_GOD");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CoinItem.bmp", L"ITEM_SCORE");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/TimeItem.bmp", L"ITEM_CLOCK");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/HammerItem.bmp", L"ITEM_WEAPON_HAMMER");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/LanceItem.bmp", L"ITEM_WEAPON_LANCE");

}

void CMainGame::Initialize(void)
{
	ResourceLoad();

	m_player = dynamic_cast<CPlayer*>(CAbstractFactory<CPlayer>::Create());

	CObjManager::Instance()->AddObject(OBJ_PLAYER, m_player);
	
	CObj* newBackUI = CAbstractFactory<CBackUI>::Create();
	m_backUI = dynamic_cast<CBackUI*>(newBackUI);

	CreateMonster(MONSTER_C, 6800.f, 300.f);

	CreateMonster(MONSTER_B, 5500.f, 0.f);
	CreateMonster(MONSTER_B, 6000.f, 0.f);

	CreateMonster(MONSTER_B, 5200.f, 100.f);
	CreateMonster(MONSTER_B, 4700.f, 200.f);
	CreateMonster(MONSTER_B, 3700.f, 300.f);

	CreateMonster(MONSTER_A, 8000.f, 300.f);
	CreateMonster(MONSTER_A, 8200.f, 300.f);
	CreateMonster(MONSTER_A, 8400.f, 300.f);
	CreateMonster(MONSTER_A, 10400.f, 300.f);

	CreateMonster(MONSTER_BOSS, 15700.f, 200.f);

	CUIManager::Instance()->AddUI(UI_BACK, m_backUI);
	CUIManager::Instance()->AddUI(UI_FRONT, CAbstractFactory<CFrontUI>::Create());

	CObj* newTimeProgress = CAbstractFactory<CProgressBar>::Create();
	m_timeProgress = dynamic_cast<CProgressBar*>(newTimeProgress);
	DeadTime = StageDeadTime;
	m_timeProgress->InitProgress({ WINCX * 0.5f, 140.f }, {500.f, 50.f}, DeadTime, StageDeadTime);
	CUIManager::Instance()->AddUI(UI_FRONT, newTimeProgress);

	CUIManager::Instance()->AddUI(UI_FRONT, CAbstractFactory<CWeaponBag>::Create());

	m_timer = new CTimer;
	m_timer->StartTimer(ENERMY_PER_SECOND, [&]() {
	});

	m_player->Set_pos(50, 100);

	CObjManager::Instance()->AddMap(
		new CLinePlat(
			vector<LINEPOINT>{
				{ -100, 350 },
				{ 300, 350 },
				{ 300, 550 },
				{ 400, 550 },
				{ 550, 350 },
				{ 3500, 350 },

				{ 3500, 1000 },
				{ -100, 1000 },
				{ -100, 350 }
		})
	);

	CObjManager::Instance()->AddObject(OBJ_WALL,
		CObjLine::Create({ -100, 350 }, { -100, 1000 }
	));

	CObjManager::Instance()->AddObject(OBJ_WALL,
		CObjLine::Create({ 3500, 350 }, { 3500, 1000 }
	));

	CObjManager::Instance()->AddObject(OBJ_WALL,
		CObjLine::Create({ 300, 350 }, { 300, 550 }
	));

	CObjManager::Instance()->AddMap(
		new CLinePlat(
			vector<LINEPOINT>{
				{ 3700, 350 },
				{ 4200, 350 },
				{ 4200, 250 },
				{ 4700, 250 },
				{ 4700, 150 },
				{ 5200, 150 },
				{ 5200, 50 },
				{ 6200, 50 },
				{ 6700, 350 },
				{ 7200, 350 },
				{ 7200, 1000 },
				{ 3700, 1000 },
				{ 3700, 350 }
		})
	);

	CObjManager::Instance()->AddObject(OBJ_WALL,
		CObjLine::Create({ 3700, 350 }, { 3700, 1000 }
	));

	CObjManager::Instance()->AddObject(OBJ_WALL,
		CObjLine::Create({ 7200, 350 }, { 7200, 1000 }
	));

	CObjManager::Instance()->AddObject(OBJ_WALL,
		CObjLine::Create({ 4200, 350 }, { 4200, 250 }
	));

	CObjManager::Instance()->AddObject(OBJ_WALL,
		CObjLine::Create({ 4700, 250 }, { 4700, 150 }
	));

	CObjManager::Instance()->AddObject(OBJ_WALL,
		CObjLine::Create({ 5200, 150 }, { 5200, 50 }
	));

	CObjManager::Instance()->AddMap(
		new CLinePlat(
			vector<LINEPOINT>{
				{ 7400, 350 },
				{ 10400, 350 },
				{ 10400, 1000 },
				{ 7400, 1000 },
				{ 7400, 350 }
		})
	);

	CObjManager::Instance()->AddObject(OBJ_WALL,
		CObjLine::Create({ 7400, 350 }, { 7400, 1000 }
	));

	CObjManager::Instance()->AddObject(OBJ_WALL,
		CObjLine::Create({ 10400, 350 }, { 10400, 1000 }
	));

	CObjManager::Instance()->AddMap(
		new CLinePlat(
			vector<LINEPOINT>{
				{ 10600, 350 },
				{ 10900, 350 },
				{ 10900, 1000 },
				{ 10600, 1000 },
				{ 10600, 350 }
		})
	);

	CObjManager::Instance()->AddObject(OBJ_WALL,
		CObjLine::Create({ 10600, 350 }, { 10600, 1000 }
	));

	CObjManager::Instance()->AddObject(OBJ_WALL,
		CObjLine::Create({ 10900, 350 }, { 10900, 1000 }
	));

	CMovePlatform* movePlatform;
	movePlatform = new CMovePlatform;
	movePlatform->Initialize();
	movePlatform->Set_pos(10900 + 180 + 10, 350);
	movePlatform->SetDirection({ 1, 0 });
	movePlatform->SetArea({ 10950, 0, 11700, 1000});
	CObjManager::Instance()->AddObject(OBJ_OBSTACLE, movePlatform);

	movePlatform = new CMovePlatform;
	movePlatform->Initialize();
	movePlatform->Set_pos(12600 - 180 - 10, 350);
	movePlatform->SetDirection({ -1, 0 });
	movePlatform->SetArea({ 11700, 0, 12550, 1000 });
	movePlatform->Set_Speed(5.f);
	CObjManager::Instance()->AddObject(OBJ_OBSTACLE, movePlatform);


	CObjManager::Instance()->AddMap(
		new CLinePlat(
			vector<LINEPOINT>{
				{ 12600, 350 },
				{ 12900, 350 },
				{ 12900, 1000 },
				{ 12600, 1000 },
				{ 12600, 350 }
		})
	);


	CObjManager::Instance()->AddObject(OBJ_WALL,
		CObjLine::Create({ 12600, 350 }, { 12600, 1000 }
	));

	CObjManager::Instance()->AddObject(OBJ_WALL,
		CObjLine::Create({ 12900, 350 }, { 12900, 1000 }
	));

	movePlatform = new CMovePlatform;
	movePlatform->Initialize();
	movePlatform->Set_pos(12900 + 180 + 100, 500);
	movePlatform->SetDirection({ 0, 1 });
	movePlatform->SetSize(180.f, 50.f);
	movePlatform->SetArea({ 12000, 350, 13900, 1000 });
	CObjManager::Instance()->AddObject(OBJ_OBSTACLE, movePlatform);


	movePlatform = new CMovePlatform;
	movePlatform->Initialize();
	movePlatform->Set_pos(13900 - 180 - 100, 500);
	movePlatform->SetDirection({ 0, 1 });
	movePlatform->SetSize(180.f, 50.f);
	movePlatform->SetArea({ 12000, 350, 13900, 1000 });
	CObjManager::Instance()->AddObject(OBJ_OBSTACLE, movePlatform);

	CObjManager::Instance()->AddMap(
		new CLinePlat(
			vector<LINEPOINT>{
				{ 13900, 350 },
				{ 14400, 350 },
				{ 14400, 450 },
				{ 14500, 450 },
				{ 14500, 550 },
				{ 14600, 550 },

				{ 14600, 1500 },
				{ 13900, 1500 },
				{ 13900, 350 },
		})
	);

	CObjManager::Instance()->AddObject(OBJ_WALL,
		CObjLine::Create({ 13900, 350 }, { 13900, 1500 }
	));

	CObjManager::Instance()->AddObject(OBJ_WALL,
		CObjLine::Create({ 14600, 350 }, { 14600, 1500 }
	));

	CObjManager::Instance()->AddObject(OBJ_WALL,
		CObjLine::Create({ 14400, 350 }, { 14400, 450 }
	));

	CObjManager::Instance()->AddObject(OBJ_WALL,
		CObjLine::Create({ 14500, 450 }, { 14500, 550 }
	));

	CObjManager::Instance()->AddMap(
		new CLinePlat(
			vector<LINEPOINT>{
				{ 14700, 550 },
				{ 16400, 550 },
				{ 16400, 0 },
				{ 16700, 0 },

				{ 16700, 1500 },
				{ 14700, 1500 },
				{ 14700, 550 },
		})
	);

	CObjManager::Instance()->AddObject(OBJ_WALL,
		CObjLine::Create({ 16400, 550 }, { 16400, 0 }
	));

	CObjManager::Instance()->AddObject(OBJ_WALL,
		CObjLine::Create({ 14700, 550 }, { 14700, 1500 }
	));


	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEM_SCORE, { 600.f, 200.f }));
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEM_SCORE, { 800.f, 200.f }));
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEM_SCORE, { 1000.f, 200.f }));
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEM_SCORE, { 1200.f, 200.f }));
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEM_SCORE, { 1400.f, 200.f }));
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEM_SCORE, { 1600.f, 200.f }));
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEM_SCORE, { 1800.f, 200.f }));
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEM_SCORE, { 2000.f, 200.f }));
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEM_SCORE, { 2200.f, 200.f }));
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEM_SCORE, { 2400.f, 200.f }));
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEM_SCORE, { 2600.f, 200.f }));
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEM_SCORE, { 2800.f, 200.f }));
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEM_SCORE, { 3000.f, 200.f }));
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEM_SCORE, { 3200.f, 200.f }));

	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEMTYPE::ITEM_WEAPON_HAMMER, { 400.f, 200.f }));

	m_player->SetDeadY(1800.f);
}

void CMainGame::Update(void)
{
	PlayTime += g_dwDeltaTime;
	CObjManager::Instance()->Update();
	CUIManager::Instance()->Update();

	DeadTime -= 0.01f;
	if (DeadTime <= 0 && m_player) {
		m_player->Die();
		DeadTime = StageDeadTime;
	}

	m_timeProgress->SetCurrent(DeadTime);

	if (!CObjManager::Instance()->GetPlayer()) {
		m_player = nullptr;
	}

	if (m_bossMosnter && !CObjManager::Instance()->ContainsCheck(OBJ_MONSTER, m_bossMosnter)) {
		m_bossMosnter = nullptr;
		g_gameClient->LoadScene(new CEndingScene);
	}

	const int mapHalfHeight = 250;

	if (m_player) {
		RandomMonster();

		m_timer->Update();
	}

}

void CMainGame::Late_Update(void)
{
	CObjManager::Instance()->Late_Update();
}

void CMainGame::Render(HDC hdc)
{
	CUIManager::Instance()->BackRender(hdc);

	CObjManager::Instance()->Render(hdc);

	CUIManager::Instance()->FrontRender(hdc);
}

void CMainGame::Release(void)
{
}

void CMainGame::RandomMonster(void)
{

}

void CMainGame::CreateMonster(MONSTERTYPE _type, float _fXpoint, float _fYpoint)
{
	switch (_type)
	{
	case MONSTER_A:
		m_monster = CAbstractFactory<CBehaviorA>::Create(_fXpoint, _fYpoint);
		break;

	case MONSTER_B:
		m_monster = CAbstractFactory<CBehaviorB>::Create(_fXpoint, _fYpoint);
		break;

	case MONSTER_C:
		m_monster = CAbstractFactory<CBehaviorC>::Create(_fXpoint, _fYpoint);
		break;

	case MONSTER_BOSS:
		m_monster = CAbstractFactory<CBehaviorBoss>::Create(_fXpoint, _fYpoint);
		m_bossMosnter = m_monster;
		break;
	}

	dynamic_cast<CMonster*>(m_monster)->BehaviorStart(m_player);
	CObjManager::Instance()->AddObject(OBJ_MONSTER, m_monster);
}
