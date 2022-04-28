#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"

#include "Player.h"

int CMainGame::TotalKillCount = 0;
int CMainGame::KillCount = 0;
int CMainGame::BossCount = BOSS_APPEAR_COUNT;

bool CMainGame::bBoss = false;
long int CMainGame::Score = 0;
int CMainGame::Level = 1;
int CMainGame::PlayTime = 0;

CMainGame::CMainGame()
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * 64);
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

	CPlayer* player = dynamic_cast<CPlayer*>(m_player);

	m_timer = new CTimer;
	m_timer->StartTimer(ENERMY_PER_SECOND, [&]() {
	
	});
}

void CMainGame::Update(void)
{
	PlayTime += g_dwDeltaTime;
	CObjManager::Instance()->Update();

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
	
	BackgroundRender(backHDC);

	CObjManager::Instance()->Render(backHDC);

	UIRender(backHDC);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, backHDC, 0, 0, SRCCOPY);
	DeleteObject(SelectObject(backHDC, backBitmapStage));
	DeleteDC(backHDC);
}

void CMainGame::Release(void)
{
	CObjManager::Instance()->Destroy();
	ReleaseDC(g_hWnd, m_hDC);
}

void CMainGame::BackgroundRender(HDC hDC) {
	HBRUSH	brush;
	HGDIOBJ h_old_brush;
	brush = CreateSolidBrush(RGB(0, 0, 105));
	h_old_brush = SelectObject(hDC, brush);
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	SelectObject(hDC, h_old_brush);
	DeleteObject(brush);
}

void CMainGame::UIRender(HDC hDC) {
	TCHAR	szBuff[32] = L"";
	swprintf_s(szBuff, L"SCORE : %d", Score);
	TextOut(hDC, WINCX - 100, 50, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"KILL : %d", TotalKillCount);
	TextOut(hDC, 650, 950, szBuff, lstrlen(szBuff));

	//PLAYER level
	swprintf_s(szBuff, L"LEVEL %d", Level);
	TextOutW(hDC, 350, 950, szBuff, lstrlen(szBuff));

	int currentPlayTime = PlayTime;
	int microsecond = currentPlayTime % 10;
	currentPlayTime /= 10;

	int second = currentPlayTime % 60;
	currentPlayTime /= 60;

	int minute = currentPlayTime % 60;

	swprintf_s(szBuff, L"PlayTime: %02d:%02d", minute, second);
	TextOut(hDC, WINCX * 0.5 - 50, 50, szBuff, lstrlen(szBuff));

	if (!CObjManager::Instance()->GetPlayer())
	{
		swprintf_s(szBuff, L"GAME OVER");
		TextOut(hDC, static_cast<int>(WINCX * 0.5f) - 50, static_cast<int>(WINCY * 0.5f), szBuff, lstrlen(szBuff));
	}

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount()) {
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}
}
