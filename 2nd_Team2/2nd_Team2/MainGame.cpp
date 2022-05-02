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
	: m_dwTime(GetTickCount())
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{

	m_player = dynamic_cast<CPlayer*>(CAbstractFactory<CPlayer>::Create());

	////Stage1 : LAND의 수직 라인들.
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 300.f, (float)WINCY - 250.f },{ 300.f, (float)WINCY - 150.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 1400.f, (float)WINCY - 400.f },{ 1400.f, (float)WINCY + 500.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 1600.f,(float)WINCY + 500.f },{ 1600.f,(float)WINCY - 400.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 1800.f,(float)WINCY - 400.f },{ 1800.f, (float)WINCY - 250.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 2100.f,(float)WINCY - 150.f },{ 2100.f,(float)WINCY + 500.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 2300.f, (float)WINCY + 500.f },{ 2300.f, (float)WINCY - 250.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 2700.f, (float)WINCY - 350.f }, { 2700.f,(float)WINCY - 450.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 2800.f,(float)WINCY - 450.f },{ 2800.f,(float)WINCY - 550.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 2900.f,(float)WINCY - 550.f },{ 2900.f,(float)WINCY - 650.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 3000.f,(float)WINCY - 650.f },{ 3000.f,(float)WINCY - 750.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 3100.f,(float)WINCY - 750.f },{ 3100.f,(float)WINCY - 850.f }));
	////Stage2 : SKY의 수직 라인들.
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 3500.f,(float)WINCY - 850.f },{ 3500.f,(float)WINCY + 500.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 3700.f,(float)WINCY + 500.f },{ 3700.f,(float)WINCY - 850.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 3900.f,(float)WINCY - 850.f },{ 3900.f,(float)WINCY + 500.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 4900.f,(float)WINCY + 500.f },{ 4900.f,(float)WINCY - 850.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 5100.f,(float)WINCY - 850.f },{ 5100.f,(float)WINCY + 500.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 5700.f,(float)WINCY + 500.f },{ 5700.f,(float)WINCY - 850.f }));

	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 6000.f, (float)WINCY - 850.f }, { 6000.f,(float)WINCY - 750.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 6100.f,(float)WINCY - 750.f },{ 6100.f,(float)WINCY - 650.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 6200.f, (float)WINCY - 650.f },{ 6200.f,(float)WINCY - 550.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 6300.f,(float)WINCY - 550.f },{ 6300.f,(float)WINCY - 450.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 6400.f,(float)WINCY - 450.f },{ 6400.f,(float)WINCY - 350.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 6500.f,(float)WINCY - 350.f },{ 6500.f,(float)WINCY - 250.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 6600.f,(float)WINCY - 250.f },{ 6600.f,(float)WINCY - 150.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 6700.f,(float)WINCY - 150.f },{ 6700.f,(float)WINCY - 50.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 6800.f,(float)WINCY - 50.f },{ 6800.f,(float)WINCY + 50.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 6900.f,(float)WINCY + 50.f },{ 6900.f,(float)WINCY + 150.f }));
	////Stage3 : UNDERGROUND의 수직 라인들.
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 7500.f, (float)WINCY + 150.f },{ 7500.f,(float)WINCY + 200.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 7800.f,(float)WINCY + 200.f }, { 7800.f,(float)WINCY + 300.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 8300.f,(float)WINCY + 300.f },{ 8300.f,(float)WINCY + 200.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 8800.f,(float)WINCY + 500.f },{ 8800.f,(float)WINCY + 1000.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 9000.f,(float)WINCY + 1000.f },{ 9000.f,(float)WINCY + 500.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 9100.f,(float)WINCY + 500.f },{ 9100.f,(float)WINCY + 400.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 9300.f,(float)WINCY + 400.f },{ 9300.f,(float)WINCY + 1000.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 9500.f, (float)WINCY + 1000.f },{ 9500.f,(float)WINCY + 700.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 9600.f,(float)WINCY + 700.f },{ 9600.f,(float)WINCY + 1000.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 9800.f,(float)WINCY + 1000.f },{ 9800.f,(float)WINCY + 700.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 9900.f,(float)WINCY + 700.f },{ 9900.f,(float)WINCY + 1000.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 10100.f,(float)WINCY + 1000.f },{ 10100.f,(float)WINCY + 700.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 10200.f,(float)WINCY + 700.f },{ 10200.f,(float)WINCY + 1000.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 10400.f,(float)WINCY + 1000.f },{ 10400.f,(float)WINCY + 700.f }));


	CObjManager::Instance()->AddObject(OBJ_PLAYER, m_player);
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEM_LIFE,	{ 100.f, 200.f }));
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEM_CLOCK,	{ 300.f, 200.f }));
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEM_SCORE,	{ 500.f, 200.f }));

	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEMTYPE::ITEM_GOD , { 700.f, 200.f }));
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEMTYPE::ITEM_WEAPON_HAMMER, { 900.f, 200.f }));
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(CItem::ITEMTYPE::ITEM_WEAPON_LANCE, { 1100.f, 200.f }));

	m_backUI = dynamic_cast<CBackUI*>(CAbstractFactory<CBackUI>::Create());
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

	RandomMonster();

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
	if (m_dwTime + 1000 < GetTickCount())
	{
		srand((unsigned int)time((nullptr)));
		int iRanMon = rand() % 4 + 1;
		switch (iRanMon)
		{
		case 1:
			CreateMonster(MONSTER_A); // A
			break;

		case 2:
			CreateMonster(MONSTER_B); // B
			break;

		case 3:
			CreateMonster(MONSTER_C); // C
			break;

		case 4:
			CreateMonster(MONSTER_BOSS); // BOSS
			break;
		}

		m_dwTime = GetTickCount();
	}
}

void CMainGame::CreateMonster(MONSTERTYPE _type)
{
	switch (_type)
	{
	case MONSTER_A:
		m_monster = CAbstractFactory<CBehaviorA>::Create((m_player->Get_Info().fX + 650.f));
		dynamic_cast<CBehaviorA*>(m_monster)->BehaviorStart(m_player);
		CObjManager::Instance()->AddObject(OBJ_MONSTER, m_monster);
		break;

	case MONSTER_B:
		m_monster = CAbstractFactory<CBehaviorB>::Create((m_player->Get_Info().fX + 650.f));
		dynamic_cast<CBehaviorB*>(m_monster)->BehaviorStart(m_player);
		CObjManager::Instance()->AddObject(OBJ_MONSTER, m_monster);
		break;

	case MONSTER_C:
		m_monster = CAbstractFactory<CBehaviorC>::Create((m_player->Get_Info().fX + 650.f));
		dynamic_cast<CBehaviorC*>(m_monster)->BehaviorStart(m_player);
		CObjManager::Instance()->AddObject(OBJ_MONSTER, m_monster);
		break;

	case MONSTER_BOSS:
		m_monster = CAbstractFactory<CBehaviorBoss>::Create((m_player->Get_Info().fX + 650.f));
		dynamic_cast<CBehaviorBoss*>(m_monster)->BehaviorStart(m_player);
		CObjManager::Instance()->AddObject(OBJ_MONSTER, m_monster);
		break;
	}
}
