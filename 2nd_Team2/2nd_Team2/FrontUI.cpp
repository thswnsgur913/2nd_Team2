#include "stdafx.h"
#include "MainGame.h"
#include "FrontUI.h"


CFrontUI::CFrontUI()
{
}


CFrontUI::~CFrontUI()
{
}

void CFrontUI::Initialize() {
}

int CFrontUI::Update() {
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CFrontUI::Late_Update() {
}

void CFrontUI::Render(HDC hdc) {
	TCHAR	szBuff[32] = L"";

	swprintf_s(szBuff, L"Life : %d", CMainGame::Life);
	TextOut(hdc, 50, 50, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"SCORE : %d", CMainGame::Score);
	TextOut(hdc, static_cast<int>(WINCX * 0.5f) - 50, 50, szBuff, lstrlen(szBuff));

	int currentPlayTime = CMainGame::PlayTime;
	int microsecond = currentPlayTime % 10;
	currentPlayTime /= 10;

	int second = currentPlayTime % 60;
	currentPlayTime /= 60;

	int minute = currentPlayTime % 60;

	swprintf_s(szBuff, L"PlayTime: %02d:%02d", minute, second);
	TextOut(hdc, static_cast<int>(WINCX * 0.5) - 50, 80, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"KILL : %d", CMainGame::TotalKillCount);
	TextOut(hdc, 650, 950, szBuff, lstrlen(szBuff));

	//PLAYER level
	swprintf_s(szBuff, L"LEVEL %d", CMainGame::Level);
	TextOutW(hdc, 350, 950, szBuff, lstrlen(szBuff));

	if (!CObjManager::Instance()->GetPlayer())
	{
		swprintf_s(szBuff, L"GAME OVER");
		TextOut(hdc, static_cast<int>(WINCX * 0.5f) - 50, static_cast<int>(WINCY * 0.5f), szBuff, lstrlen(szBuff));
	}

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount()) {
		swprintf_s(szBuff, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, szBuff);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}
}

void CFrontUI::Release() {
}

void CFrontUI::CollisionEnter(CObj* _sour) {
}