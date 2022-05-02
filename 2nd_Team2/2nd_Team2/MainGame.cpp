#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"

// OBJ
#include "Player.h"
#include "Item.h"
#include "BehaviorA.h"
#include "BehaviorB.h"
#include "BehaviorC.h"
#include "BehaviorBoss.h"
#include "ObjLine.h"

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

CMainGame::CMainGame()
	: m_dwTime(GetTickCount()),
	  m_bMonsterOnOff(false)
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	
	m_player = dynamic_cast<CPlayer*>(CAbstractFactory<CPlayer>::Create());


	CObjManager::Instance()->AddObject(OBJ_PLAYER, m_player);
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEM_LIFE,	{ 100.f, 200.f }));
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEM_CLOCK,	{ 300.f, 200.f }));
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEM_SCORE,	{ 500.f, 200.f }));

	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEMTYPE::ITEM_GOD , { 700.f, 200.f }));
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEMTYPE::ITEM_WEAPON_HAMMER, { 900.f, 200.f }));
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEMTYPE::ITEM_WEAPON_LANCE, { 1100.f, 200.f }));

	CObj* newBackUI = CAbstractFactory<CBackUI>::Create();
	m_backUI = dynamic_cast<CBackUI*>(newBackUI);

	CreateMonster(MONSTER_A,500.f);
	CreateMonster(MONSTER_B,1000.f);
	CreateMonster(MONSTER_C,1500.f);
	CreateMonster(MONSTER_BOSS, 2000.f);

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

	CObjManager::Instance()->AddObject(OBJ_OBSTACLE,
		CObjLine::Create({ -100, 350 }, { -100, 1000 }
	));

	CObjManager::Instance()->AddObject(OBJ_OBSTACLE,
		CObjLine::Create({ 3500, 350 }, { 3500, 1000 }
	));

	CObjManager::Instance()->AddObject(OBJ_OBSTACLE,
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

	CObjManager::Instance()->AddObject(OBJ_OBSTACLE,
		CObjLine::Create({ 3700, 350 }, { 3700, 1000 }
	));

	CObjManager::Instance()->AddObject(OBJ_OBSTACLE,
		CObjLine::Create({ 7200, 350 }, { 7200, 1000 }
	));

	CObjManager::Instance()->AddObject(OBJ_OBSTACLE,
		CObjLine::Create({ 4200, 350 }, { 4200, 250 }
	));

	CObjManager::Instance()->AddObject(OBJ_OBSTACLE,
		CObjLine::Create({ 4700, 250 }, { 4700, 150 }
	));

	CObjManager::Instance()->AddObject(OBJ_OBSTACLE,
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

	CObjManager::Instance()->AddObject(OBJ_OBSTACLE,
		CObjLine::Create({ 7400, 350 }, { 7400, 1000 }
	));

	CObjManager::Instance()->AddObject(OBJ_OBSTACLE,
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

	CObjManager::Instance()->AddObject(OBJ_OBSTACLE,
		CObjLine::Create({ 10600, 350 }, { 10600, 1000 }
	));

	CObjManager::Instance()->AddObject(OBJ_OBSTACLE,
		CObjLine::Create({ 10900, 350 }, { 10900, 1000 }
	));

	//////////////////////// 임시

	CObjManager::Instance()->AddMap(
		new CLinePlat(
			vector<LINEPOINT>{
				{ 11000, 350 },
				{ 12400, 350 },
				{ 12400, 1000 },
				{ 11000, 1000 },
				{ 11000, 350 }
		})
	);

	///////////////////////////

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

	CObjManager::Instance()->AddObject(OBJ_OBSTACLE,
		CObjLine::Create({ 12600, 350 }, { 12600, 1000 }
	));

	CObjManager::Instance()->AddObject(OBJ_OBSTACLE,
		CObjLine::Create({ 12900, 350 }, { 12900, 1000 }
	));

	//////////////////////// 임시

	CObjManager::Instance()->AddMap(
		new CLinePlat(
			vector<LINEPOINT>{
				{ 13100, 350 },
				{ 13700, 350 },
				{ 13700, 1000 },
				{ 13100, 1000 },
				{ 13100, 350 }
		})
	);

	///////////////////////////

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

	CObjManager::Instance()->AddObject(OBJ_OBSTACLE,
		CObjLine::Create({ 13900, 350 }, { 13900, 1500 }
	));

	CObjManager::Instance()->AddObject(OBJ_OBSTACLE,
		CObjLine::Create({ 14600, 350 }, { 14600, 1500 }
	));

	CObjManager::Instance()->AddObject(OBJ_OBSTACLE,
		CObjLine::Create({ 14400, 350 }, { 14400, 450 }
	));

	CObjManager::Instance()->AddObject(OBJ_OBSTACLE,
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

	CObjManager::Instance()->AddObject(OBJ_OBSTACLE,
		CObjLine::Create({ 16400, 550 }, { 16400, 0 }
	));

	CObjManager::Instance()->AddObject(OBJ_OBSTACLE,
		CObjLine::Create({ 14700, 550 }, { 14700, 1500 }
	));
}

void CMainGame::Update(void)
{
	PlayTime += g_dwDeltaTime;
	CObjManager::Instance()->Update();
	CUIManager::Instance()->Update();


	DeadTime -= 0.01f;
	if (DeadTime <= 0 && m_player) {
		m_player->Set_Damage();
		DeadTime = StageDeadTime;
	}

	m_timeProgress->SetCurrent(DeadTime);

	if (!CObjManager::Instance()->GetPlayer()) {
		m_player = nullptr;
	}

	const int mapHalfHeight = 250;

	if (m_player) {
		for (auto& iter : CObjManager::Instance()->GetLine())
		{
			dynamic_cast<CObjLine*>(iter)->Collision_OBJLINE(m_player);
		}
		RandomMonster();
		m_backUI->SetPlayerDepth(static_cast<int>((m_player->Get_Info().fY - mapHalfHeight) / 10));
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

void CMainGame::CreateMonster(MONSTERTYPE _type, float _fXpoint)
{
	switch (_type)
	{
	case MONSTER_A:
		m_monster = CAbstractFactory<CBehaviorA>::Create(_fXpoint);
		dynamic_cast<CBehaviorA*>(m_monster)->BehaviorStart(m_player);
		CObjManager::Instance()->AddObject(OBJ_MONSTER, m_monster);
		break;

	case MONSTER_B:
		m_monster = CAbstractFactory<CBehaviorB>::Create(_fXpoint);
		dynamic_cast<CBehaviorB*>(m_monster)->BehaviorStart(m_player);
		CObjManager::Instance()->AddObject(OBJ_MONSTER, m_monster);
		break;

	case MONSTER_C:
		m_monster = CAbstractFactory<CBehaviorC>::Create(_fXpoint);
		dynamic_cast<CBehaviorC*>(m_monster)->BehaviorStart(m_player);
		CObjManager::Instance()->AddObject(OBJ_MONSTER, m_monster);
		break;
	}
}
