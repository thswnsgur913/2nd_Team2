#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"

// OBJ
#include "Player.h"
#include "Item.h"
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
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_player = CAbstractFactory<CPlayer>::Create();
	CObjManager::Instance()->AddObject(OBJ_PLAYER, m_player);
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(ITEM_LIFE,	{ 100.f, 200.f }));
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(ITEM_CLOCK,	{ 200.f, 200.f }));
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(ITEM_SCORE,	{ 300.f, 200.f }));
	//CObjManager::Instance()->AddObject(OBJ_OBSTACLE, CObjLine::Create());

	CUIManager::Instance()->AddUI(UI_BACK, CAbstractFactory<CBackUI>::Create());
	CUIManager::Instance()->AddUI(UI_FRONT, CAbstractFactory<CFrontUI>::Create());

	CObj* newTimeProgress = CAbstractFactory<CProgressBar>::Create();
	m_timeProgress = dynamic_cast<CProgressBar*>(newTimeProgress);

	m_test = 100.f;
	DeadTime = m_test;
	m_timeProgress->InitProgress({ WINCX * 0.5f, 140.f }, {500.f, 50.f}, m_test, m_test);
	CUIManager::Instance()->AddUI(UI_FRONT, newTimeProgress);

	CUIManager::Instance()->AddUI(UI_FRONT, CAbstractFactory<CWeaponBag>::Create());


	m_monster = CAbstractFactory<CBehaviorBoss>::Create();
	dynamic_cast<CBehaviorBoss*>(m_monster)->BehaviorStart(m_player);
	CObjManager::Instance()->AddObject(OBJ_MONSTER, m_monster);

	m_timer = new CTimer;
	m_timer->StartTimer(ENERMY_PER_SECOND, [&]() {
	
	});

	m_map.push_back(
		new CLinePlat(
			vector<LINEPOINT>{
				{ -100.f, (float) WINCY - 250.f },
				{ 300.f, (float) WINCY - 250.f },
				{ 300.f, (float)WINCY - 150.f },
				{ 600.f,(float)WINCY - 150.f },
		})
	);

	m_map.push_back(
		new CLinePlat(
			vector<LINEPOINT>{
				//{ 300.f, (float) WINCY - 150.f },
				{ 600.f,(float) WINCY - 150.f },
				{ 1100.f,(float) WINCY - 400.f },
				{ 1400.f,(float) WINCY - 400.f },//6번 좌표
				{ 1400.f, (float)WINCY + 500.f },
				{ 1600.f,(float)WINCY + 500.f },
				{ 1600.f,(float)WINCY - 400.f },
				{ 1600.f,(float)WINCY - 400.f },
		})
	);

	m_map.push_back(
		new CLinePlat(
			vector<LINEPOINT>{
				//{ 1400.f, (float)WINCY + 500.f },
				//{ 1600.f,(float)WINCY + 500.f },
				{ 1600.f,(float) WINCY - 400.f },
				{ 1800.f,(float) WINCY - 400.f },//10번 좌표
				{ 1800.f, (float) WINCY - 250.f },
				{ 1900.f,(float) WINCY - 150.f },
				{ 2100.f,(float) WINCY - 150.f },//13번 좌표.
				{ 2100.f,(float) WINCY + 500.f },
				{ 2300.f,(float)WINCY + 500.f },
		})
	);

	m_map.push_back(
		new CLinePlat(
			vector<LINEPOINT>{
				{ 2300.f, (float)WINCY + 500.f },
				{ 2300.f, (float)WINCY - 250.f },//16번 좌표
				{ 2500.f,(float)WINCY - 250.f },
				{ 2600.f,(float)WINCY - 350.f },
				{ 2700.f,(float)WINCY - 350.f },//19번 마지막 좌표,계단 시작좌표.
												//1,2스테이지 사이의 계단(upstair)
				{ 2700.f,(float)WINCY - 450.f },//1번 계단.
				{ 2800.f,(float)WINCY - 450.f },
				{ 2800.f,(float)WINCY - 550.f },//2번 계단.
				{ 2900.f,(float)WINCY - 550.f },
				{ 2900.f,(float)WINCY - 650.f },//3번 계단.
				{ 3000.f,(float)WINCY - 650.f },
				{ 3000.f,(float)WINCY - 750.f },//4번 계단.
				{ 3100.f,(float)WINCY - 750.f },
				{ 3100.f,(float)WINCY - 850.f },//5번 계단.
				{ 3200.f,(float)WINCY - 850.f }
		})
	);

	// 플레이어가 살아있는 동안에 한해서 일정 거리를 달리면
	// 새로 추가로 생성하는게 좋을거 같다. 예를들면 if문 추가, for문 추가.
	// bool타입을 추가해서 스테이지를 update에서 추가생성.

	//2스테이지: SKY시작.
	m_map.push_back(
		new CLinePlat(
			vector<LINEPOINT>{
				{ 3200.f, (float)WINCY - 850.f },
				{ 3500.f,(float)WINCY - 850.f },//2번 좌표
				{ 3500.f,(float)WINCY + 500.f },
				{ 3700.f,(float)WINCY + 500.f },
				{ 3700.f,(float)WINCY - 850.f },
				{ 3900.f,(float)WINCY - 850.f },//6번 좌표
				{ 3900.f,(float)WINCY + 500.f },
				{ 4900.f,(float)WINCY + 500.f },
				{ 4900.f,(float)WINCY - 850.f },
				{ 5100.f,(float)WINCY - 850.f },//10번 좌표
				{ 5100.f,(float)WINCY + 500.f },
				{ 5700.f,(float)WINCY + 500.f },
				{ 5700.f,(float)WINCY - 850.f },//13번 좌표
				{ 6000.f,(float)WINCY - 850.f },//14번 마지막 좌표,계단 시작좌표.
												//2,3스테이지 사이의 계단(upstair)
				{ 6000.f,(float)WINCY - 750.f },//1번 계단.
				{ 6100.f,(float)WINCY - 750.f },
				{ 6100.f,(float)WINCY - 650.f },//2번 계단.
				{ 6200.f,(float)WINCY - 650.f },
				{ 6200.f,(float)WINCY - 550.f },//3번 계단.
				{ 6300.f,(float)WINCY - 550.f },
				{ 6300.f,(float)WINCY - 450.f },//4번 계단.
				{ 6400.f,(float)WINCY - 450.f },
				{ 6400.f,(float)WINCY - 350.f },//5번 계단.
				{ 6500.f,(float)WINCY - 350.f },
				{ 6500.f,(float)WINCY - 250.f },//6번 계단.
				{ 6600.f,(float)WINCY - 250.f },
				{ 6600.f,(float)WINCY - 150.f },//7번 계단.
				{ 6700.f,(float)WINCY - 150.f },
				{ 6700.f,(float)WINCY - 50.f },//8번 계단.
				{ 6800.f,(float)WINCY - 50.f },
				{ 6800.f,(float)WINCY + 50.f },//9번 계단.
				{ 6900.f,(float)WINCY + 50.f },
				{ 6900.f,(float)WINCY + 150.f },//10번 계단.
				{ 7000.f,(float)WINCY + 150.f }
					//계단을 아예 직선으로?push_back이 줄어들수있음.
		}
	));

	//3스테이지: UNDERGROUND시작.
	m_map.push_back(
		new CLinePlat(
			vector<LINEPOINT> {
				{ 7000.f, (float)WINCY + 150.f },
				{ 7500.f,(float)WINCY + 150.f },
				{ 7500.f,(float)WINCY + 200.f },
				{ 7800.f,(float)WINCY + 200.f },//4번 좌표
				{ 7800.f,(float)WINCY + 300.f },
				{ 8300.f,(float)WINCY + 300.f },
				{ 8300.f,(float)WINCY + 200.f },//7번 좌표
				{ 8400.f,(float)WINCY + 200.f },
				{ 8700.f,(float)WINCY + 500.f },
				{ 8800.f,(float)WINCY + 500.f },//10번 좌표
				{ 8800.f,(float)WINCY + 1000.f },
				{ 9000.f,(float)WINCY + 1000.f },
				{ 9000.f,(float)WINCY + 500.f },//13번 좌표
				{ 9100.f,(float)WINCY + 500.f },
				{ 9100.f,(float)WINCY + 400.f },
				{ 9300.f,(float)WINCY + 400.f },//16번 좌표
				{ 9300.f,(float)WINCY + 1000.f },
				{ 9500.f,(float)WINCY + 1000.f },
				{ 9500.f,(float)WINCY + 700.f },
				{ 9600.f,(float)WINCY + 700.f },//20번 좌표
				{ 9600.f,(float)WINCY + 1000.f },
				{ 9800.f,(float)WINCY + 1000.f },
				{ 9800.f,(float)WINCY + 700.f },
				{ 9900.f,(float)WINCY + 700.f },//24번 좌표
				{ 9900.f,(float)WINCY + 1000.f },
				{ 10100.f,(float)WINCY + 1000.f },
				{ 10100.f,(float)WINCY + 700.f },
				{ 10200.f,(float)WINCY + 700.f },//28번 좌표
				{ 10200.f,(float)WINCY + 1000.f },
				{ 10400.f,(float)WINCY + 1000.f },
				{ 10400.f,(float)WINCY + 700.f },//31번 좌표
				{ 10600.f,(float)WINCY + 500.f },//32번 마지막 좌표,계단 시작좌표.
												 //3,4스테이지 사이의 계단(upstair)
												 //{ 6000.f,(float)WINCY - 750.f },//1번 계단.
												 //{ 6100.f,(float)WINCY - 750.f },
												 //{ 6100.f,(float)WINCY - 650.f },//2번 계단.
												 //{ 6200.f,(float)WINCY - 650.f },
												 //{ 6200.f,(float)WINCY - 550.f },//3번 계단.
												 //{ 6300.f,(float)WINCY - 550.f },
												 //{ 6300.f,(float)WINCY - 450.f },//4번 계단.
												 //{ 6400.f,(float)WINCY - 450.f },
												 //{ 6400.f,(float)WINCY - 350.f },//5번 계단.
												 //{ 6500.f,(float)WINCY - 350.f },
			}
		)
	);
}

void CMainGame::Update(void)
{
	PlayTime += g_dwDeltaTime;
	CObjManager::Instance()->Update();

	DeadTime -= DeadTime > 0 ? 0.01f : 0.f;
	m_timeProgress->SetCurrent(DeadTime);

	if (!CObjManager::Instance()->GetPlayer()) {
		m_player = nullptr;
	}

	if (CObjManager::Instance()->GetPlayer()) {
		m_timer->Update();

		for (auto& plat : m_map) {
			if (plat->Collision_Line(m_player)) {
				m_player->CollisionEnter(plat);
			};
		}
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

	for (auto& plat : m_map) {
		plat->Render(hdc);
	}
}

void CMainGame::Release(void)
{
}
