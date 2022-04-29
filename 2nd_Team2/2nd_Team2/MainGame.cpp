#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"

// OBJ
#include "Player.h"
#include "Item.h"

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
	m_hDC = GetDC(g_hWnd);
	
	m_player = CAbstractFactory<CPlayer>::Create();
	CObjManager::Instance()->AddObject(OBJ_PLAYER, m_player);
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(ITEM_LIFE,	{ 100.f, 200.f }));
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(ITEM_CLOCK,	{ 200.f, 200.f }));
	CObjManager::Instance()->AddObject(OBJ_ITEM, CItem::Create(ITEM_SCORE,	{ 300.f, 200.f }));


	CUIManager::Instance()->AddUI(UI_BACK, CAbstractFactory<CBackUI>::Create());
	CUIManager::Instance()->AddUI(UI_FRONT, CAbstractFactory<CFrontUI>::Create());

	CObj* newTimeProgress = CAbstractFactory<CProgressBar>::Create();
	m_timeProgress = dynamic_cast<CProgressBar*>(newTimeProgress);

	m_test = 100.f;
	DeadTime = m_test;
	m_timeProgress->InitProgress({ WINCX * 0.5f, 140.f }, {500.f, 50.f}, m_test, m_test);
	CUIManager::Instance()->AddUI(UI_FRONT, newTimeProgress);

	CUIManager::Instance()->AddUI(UI_FRONT, CAbstractFactory<CWeaponBag>::Create());


	m_timer = new CTimer;
	m_timer->StartTimer(ENERMY_PER_SECOND, [&]() {
	
	});
}

void CMainGame::Update(void)
{
	PlayTime += g_dwDeltaTime;
	CObjManager::Instance()->Update();

	DeadTime -= DeadTime > 0 ? 0.01f : 0.f;
	m_timeProgress->SetCurrent(static_cast<int>(DeadTime));

	if (!CObjManager::Instance()->GetPlayer()) {
		m_player = nullptr;
	}

	if (CObjManager::Instance()->GetPlayer()) {
		m_timer->Update();
	}
}

void CMainGame::Late_Update(void)
{
	CObjManager::Instance()->Late_Update();
}

void CMainGame::Render(void)
{
	HBITMAP backBitmap = NULL;
	HBITMAP backBitmapStage = NULL;
	HDC backHDC = CreateCompatibleDC(m_hDC);
	backBitmap = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	backBitmapStage = (HBITMAP)SelectObject(backHDC, backBitmap);

	CUIManager::Instance()->BackRender(backHDC);

	CObjManager::Instance()->Render(backHDC);

	CUIManager::Instance()->FrontRender(backHDC);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, backHDC, 0, 0, SRCCOPY);
	DeleteObject(SelectObject(backHDC, backBitmapStage));
	DeleteDC(backHDC);
}

void CMainGame::Release(void)
{
	CObjManager::Instance()->Destroy();
	ReleaseDC(g_hWnd, m_hDC);
}
