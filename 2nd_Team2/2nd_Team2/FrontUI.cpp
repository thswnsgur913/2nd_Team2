#include "stdafx.h"
#include "MainGame.h"
#include "FrontUI.h"

#include "Player.h"

CFrontUI::CFrontUI():
	m_player(nullptr) {
}


CFrontUI::~CFrontUI()
{
}

void CFrontUI::Initialize() {
	m_player = dynamic_cast<CPlayer*>(CObjManager::Instance()->GetPlayer());

	m_playTimeLabel = new CLabel;
	m_playTimeLabel->Set_pos(WINCX - 20, 40);
		m_playTimeLabel->SetAlign(CLabel::alignType::ALIGN_RIGHT)
		.SetFontSize(30)
		.SetColor(RGB(255, 255, 255));

	m_lifeLabel = new CLabel;
	m_lifeLabel->Set_pos(20, 40);
	m_lifeLabel->SetAlign(CLabel::alignType::ALIGN_LEFT)
		.SetFontSize(30)
		.SetColor(RGB(255, 255, 255));

	m_gameOverLabel = new CLabel(L"GAME OVER");
	m_gameOverLabel->Set_pos(static_cast<int>(WINCX * 0.5), static_cast<int>(WINCY * 0.5));
	m_gameOverLabel->SetFontSize(80);

	m_scoreTitle = new CLabel(L"Score");
	m_scoreTitle->Set_pos(static_cast<int>(WINCX * 0.5), 30);
	m_scoreTitle->SetFontSize(20)
		.SetColor(RGB(255, 255, 255));

	m_scoreLabel = new CLabel;
	m_scoreLabel->Set_pos(static_cast<int>(WINCX * 0.5), 50);
	m_scoreLabel->SetFontSize(20)
		.SetColor(RGB(255, 255, 255));
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
	HBRUSH	brush;
	HGDIOBJ hOldBrush;
	brush = CreateSolidBrush(RGB(0, 0, 0));
	hOldBrush = SelectObject(hdc, brush);

	TCHAR	szBuff[32] = L"";

	Rectangle(hdc, 0, 0, WINCX, 80);

	SelectObject(hdc, hOldBrush);
	DeleteObject(brush);


	if (!CObjManager::Instance()->GetPlayer()) {
		m_player = nullptr;
		m_gameOverLabel->Render(hdc);
	}

	swprintf_s(szBuff, L"Life : %d", CMainGame::Life);
	m_lifeLabel->SetText(szBuff);
	m_lifeLabel->Render(hdc);

	swprintf_s(szBuff, L"%d", CMainGame::Score);
	m_scoreLabel->SetText(szBuff);
	m_scoreLabel->Render(hdc);

	m_scoreTitle->Render(hdc);

	swprintf_s(szBuff, L"KILL : %d", CMainGame::TotalKillCount);
	TextOut(hdc, 650, 950, szBuff, lstrlen(szBuff));

	//PLAYER level
	swprintf_s(szBuff, L"LEVEL %d", CMainGame::Level);
	TextOutW(hdc, 350, 950, szBuff, lstrlen(szBuff));

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount()) {
		swprintf_s(szBuff, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, szBuff);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

	int currentPlayTime = CMainGame::PlayTime;
	int microsecond = currentPlayTime % 1000;
	currentPlayTime /= 1000;

	int second = currentPlayTime % 60;
	currentPlayTime /= 60;

	int minute = currentPlayTime % 60;

	swprintf_s(szBuff, L"PlayTime: %02d:%02d", minute, second);
	m_playTimeLabel->SetText(szBuff);
	m_playTimeLabel->Render(hdc);
}

void CFrontUI::Release() {
}