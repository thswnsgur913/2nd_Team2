#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"

// OBJ
#include "Player.h"
#include "Item.h"
#include "BehaviorBoss.h"

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

	m_backUI = dynamic_cast<CBackUI*>(CAbstractFactory<CBackUI>::Create());
	CUIManager::Instance()->AddUI(UI_BACK, m_backUI);
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

	CLinePlat* plat = new CLinePlat;
	plat->Initialize();
	m_map.push_back(plat);
	
	dynamic_cast<CPlayer*>(m_player)->Set_line(plat);

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

	const int mapHalfHeight = 250;

	if (m_player) {
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

	for (auto& plat : m_map) {
		plat->Render(hdc);
	}
}

void CMainGame::Release(void)
{
}
