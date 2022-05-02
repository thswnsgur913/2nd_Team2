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
	CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create({ 300.f, (float)WINCY - 250.f },{ 300.f, (float)WINCY - 150.f }));

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
				{ -100.f, (float) WINCY - 250.f },
				{ 300.f, (float) WINCY - 250.f },
		})
	);

	CObjManager::Instance()->AddMap(
		new CLinePlat(
			vector<LINEPOINT>{
				{ 300.f, (float) WINCY - 150.f },
				{ 600.f,(float) WINCY - 150.f },
				{ 1100.f,(float) WINCY - 400.f },
				{ 1400.f,(float) WINCY - 400.f },//6���� ��
			/*	{ 1400.f, (float)WINCY + 500.f },
				{ 1600.f,(float)WINCY + 500.f },
				{ 1600.f,(float)WINCY - 400.f },*/
		})
	);

	CObjManager::Instance()->AddMap(
		new CLinePlat(
			vector<LINEPOINT>{
				{ 1400.f, (float)WINCY + 500.f },
				{ 1600.f,(float)WINCY + 500.f },
	})
	);

	CObjManager::Instance()->AddMap(
		new CLinePlat(
			vector<LINEPOINT>{
				//{ 1400.f, (float)WINCY + 500.f },
				//{ 1600.f,(float)WINCY + 500.f },
				{ 1600.f,(float) WINCY - 400.f },
				{ 1800.f,(float) WINCY - 400.f },//10���� ��
				{ 1800.f, (float) WINCY - 250.f },
				{ 1900.f,(float) WINCY - 150.f },
				{ 2100.f,(float) WINCY - 150.f },//13���� ��
				{ 2100.f,(float) WINCY + 500.f },
				{ 2300.f,(float)WINCY + 500.f },
		})
	);

	CObjManager::Instance()->AddMap(
		new CLinePlat(
			vector<LINEPOINT>{
				{ 2300.f, (float)WINCY + 500.f },
				{ 2300.f, (float)WINCY - 250.f },//16���� ��
				{ 2500.f,(float)WINCY - 250.f },
				{ 2600.f,(float)WINCY - 350.f },
				{ 2700.f,(float)WINCY - 350.f },//19�� ������ ��ǥ,��� ������ǥ.
												//1,2�������� ������ ���(upstair)
				{ 2700.f,(float)WINCY - 450.f },//1�� ���.
				{ 2800.f,(float)WINCY - 450.f },
				{ 2800.f,(float)WINCY - 550.f },//2�� ���.
				{ 2900.f,(float)WINCY - 550.f },
				{ 2900.f,(float)WINCY - 650.f },//3�� ���.
				{ 3000.f,(float)WINCY - 650.f },
				{ 3000.f,(float)WINCY - 750.f },//4�� ���.
				{ 3100.f,(float)WINCY - 750.f },
				{ 3100.f,(float)WINCY - 850.f },//5�� ���.
				{ 3200.f,(float)WINCY - 850.f }
		})
	);

	// �÷��̾ ����ִ� ���ȿ� ���ؼ� ���� �Ÿ��� �޸���
	// ���� �߰��� �����ϴ°� ������ ����. ������� if�� �߰�, for�� �߰�.
	// boolŸ���� �߰��ؼ� ���������� update���� �߰�����.

	//2��������: SKY����.
	CObjManager::Instance()->AddMap(
		new CLinePlat(
			vector<LINEPOINT>{
				{ 3200.f, (float)WINCY - 850.f },
				{ 3500.f,(float)WINCY - 850.f },//2�� ��ǥ
				{ 3500.f,(float)WINCY + 500.f },
				{ 3700.f,(float)WINCY + 500.f },
				{ 3700.f,(float)WINCY - 850.f },
				{ 3900.f,(float)WINCY - 850.f },//6�� ��ǥ
				{ 3900.f,(float)WINCY + 500.f },
				{ 4900.f,(float)WINCY + 500.f },
				{ 4900.f,(float)WINCY - 850.f },
				{ 5100.f,(float)WINCY - 850.f },//10�� ��ǥ
				{ 5100.f,(float)WINCY + 500.f },
				{ 5700.f,(float)WINCY + 500.f },
				{ 5700.f,(float)WINCY - 850.f },//13�� ��ǥ
				{ 6000.f,(float)WINCY - 850.f },//14�� ������ ��ǥ,��� ������ǥ.
												//2,3�������� ������ ���(upstair)
				{ 6000.f,(float)WINCY - 750.f },//1�� ���.
				{ 6100.f,(float)WINCY - 750.f },
				{ 6100.f,(float)WINCY - 650.f },//2�� ���.
				{ 6200.f,(float)WINCY - 650.f },
				{ 6200.f,(float)WINCY - 550.f },//3�� ���.
				{ 6300.f,(float)WINCY - 550.f },
				{ 6300.f,(float)WINCY - 450.f },//4�� ���.
				{ 6400.f,(float)WINCY - 450.f },
				{ 6400.f,(float)WINCY - 350.f },//5�� ���.
				{ 6500.f,(float)WINCY - 350.f },
				{ 6500.f,(float)WINCY - 250.f },//6�� ���.
				{ 6600.f,(float)WINCY - 250.f },
				{ 6600.f,(float)WINCY - 150.f },//7�� ���.
				{ 6700.f,(float)WINCY - 150.f },
				{ 6700.f,(float)WINCY - 50.f },//8�� ���.
				{ 6800.f,(float)WINCY - 50.f },
				{ 6800.f,(float)WINCY + 50.f },//9�� ���.
				{ 6900.f,(float)WINCY + 50.f },
				{ 6900.f,(float)WINCY + 150.f },//10�� ���.
				{ 7000.f,(float)WINCY + 150.f }
					//����� �ƿ� ��������?push_back�� �پ�������.
		}
	));

	//3��������: UNDERGROUND����.
	CObjManager::Instance()->AddMap(
		new CLinePlat(
			vector<LINEPOINT> {
				{ 7000.f, (float)WINCY + 150.f },
				{ 7500.f,(float)WINCY + 150.f },
				{ 7500.f,(float)WINCY + 200.f },
				{ 7800.f,(float)WINCY + 200.f },//4�� ��ǥ
				{ 7800.f,(float)WINCY + 300.f },
				{ 8300.f,(float)WINCY + 300.f },
				{ 8300.f,(float)WINCY + 200.f },//7�� ��ǥ
				{ 8400.f,(float)WINCY + 200.f },
				{ 8700.f,(float)WINCY + 500.f },
				{ 8800.f,(float)WINCY + 500.f },//10�� ��ǥ
				{ 8800.f,(float)WINCY + 1000.f },
				{ 9000.f,(float)WINCY + 1000.f },
				{ 9000.f,(float)WINCY + 500.f },//13�� ��ǥ
				{ 9100.f,(float)WINCY + 500.f },
				{ 9100.f,(float)WINCY + 400.f },
				{ 9300.f,(float)WINCY + 400.f },//16�� ��ǥ
				{ 9300.f,(float)WINCY + 1000.f },
				{ 9500.f,(float)WINCY + 1000.f },
				{ 9500.f,(float)WINCY + 700.f },
				{ 9600.f,(float)WINCY + 700.f },//20�� ��ǥ
				{ 9600.f,(float)WINCY + 1000.f },
				{ 9800.f,(float)WINCY + 1000.f },
				{ 9800.f,(float)WINCY + 700.f },
				{ 9900.f,(float)WINCY + 700.f },//24�� ��ǥ
				{ 9900.f,(float)WINCY + 1000.f },
				{ 10100.f,(float)WINCY + 1000.f },
				{ 10100.f,(float)WINCY + 700.f },
				{ 10200.f,(float)WINCY + 700.f },//28�� ��ǥ
				{ 10200.f,(float)WINCY + 1000.f },
				{ 10400.f,(float)WINCY + 1000.f },
				{ 10400.f,(float)WINCY + 700.f },//31�� ��ǥ
				{ 10600.f,(float)WINCY + 500.f },//32�� ������ ��ǥ,��� ������ǥ.
												 //3,4�������� ������ ���(upstair)
												 //{ 6000.f,(float)WINCY - 750.f },//1�� ���.
												 //{ 6100.f,(float)WINCY - 750.f },
												 //{ 6100.f,(float)WINCY - 650.f },//2�� ���.
												 //{ 6200.f,(float)WINCY - 650.f },
												 //{ 6200.f,(float)WINCY - 550.f },//3�� ���.
												 //{ 6300.f,(float)WINCY - 550.f },
												 //{ 6300.f,(float)WINCY - 450.f },//4�� ���.
												 //{ 6400.f,(float)WINCY - 450.f },
												 //{ 6400.f,(float)WINCY - 350.f },//5�� ���.
												 //{ 6500.f,(float)WINCY - 350.f },
			}
		)
	);
}

void CMainGame::Update(void)
{
	PlayTime += g_dwDeltaTime;
	CObjManager::Instance()->Update();

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
	if (m_dwTime + 5000 < GetTickCount())
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
