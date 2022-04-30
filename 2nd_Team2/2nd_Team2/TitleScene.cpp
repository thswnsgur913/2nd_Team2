#include "stdafx.h"
#include "TitleScene.h"
#include "GameClient.h"
#include "MainGame.h"
#include "KeyMgr.h"

CTitleScene::CTitleScene():
	m_currentMenuSelect(0) {
}


CTitleScene::~CTitleScene() {

}

void CTitleScene::Initialize(void) {
	m_SelectHighlight.fX = WINCX * 0.5;
	m_SelectHighlight.fY = (WINCY - 100) + (m_currentMenuSelect * 50.f);
	TargetHighlightPosition.x = m_SelectHighlight.fX;
	TargetHighlightPosition.y = m_SelectHighlight.fY;

	m_SelectHighlight.fCX = 200.f;
	m_SelectHighlight.fCY = 50.f;
};

void CTitleScene::Update(void) {
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE)) {
		RunSeleteMenu();
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_UP)) {
		++m_currentMenuSelect;
		m_currentMenuSelect = m_currentMenuSelect % MENU_LENGTH;
		
		TargetHighlightPosition.y = (WINCY - 100) + (m_currentMenuSelect * 50.f);
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN)) {
		--m_currentMenuSelect;
		if (m_currentMenuSelect < 0)
			m_currentMenuSelect = MENU_LENGTH - 1;

		TargetHighlightPosition.y = (WINCY - 100) + (m_currentMenuSelect * 50.f);
	}

	float width = TargetHighlightPosition.x - m_SelectHighlight.fX;
	float height = TargetHighlightPosition.y - m_SelectHighlight.fY;
	float distance = sqrtf((width * width) + (height * height));
	
	if (distance > 0)
		m_SelectHighlight.fY += (height / distance) * 5.f;
};

void CTitleScene::Late_Update(void) {

};

void CTitleScene::Render(HDC hdc) {
	HBRUSH	brush;
	HGDIOBJ h_old_brush;
	brush = CreateSolidBrush(RGB(255, 255, 255));
	h_old_brush = SelectObject(hdc, brush);
	Rectangle(hdc, 0, 0, WINCX, WINCY);
	SelectObject(hdc, h_old_brush);
	DeleteObject(brush);

	int selectBarHalfWidth = static_cast<int>(m_SelectHighlight.fCX * 0.5f);
	int selectBarHalfHeight = static_cast<int>(m_SelectHighlight.fCY * 0.5f);
	Rectangle(hdc, m_SelectHighlight.fX - selectBarHalfWidth, m_SelectHighlight.fY - selectBarHalfHeight, m_SelectHighlight.fX + selectBarHalfWidth, m_SelectHighlight.fY + selectBarHalfHeight);


	TCHAR szBuff[32] = L"";

	swprintf_s(szBuff, L"select : %d", m_currentMenuSelect);
	TextOut(hdc, static_cast<int>(WINCX * 0.5) - 50, 20, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"Test");
	TextOut(hdc, static_cast<int>(WINCX * 0.5) - 30, 80, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"게임시작");
	TextOut(hdc, static_cast<int>(WINCX * 0.5) - 30, WINCY - 110, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"게임종료");
	TextOut(hdc, static_cast<int>(WINCX * 0.5) - 30, WINCY - 60, szBuff, lstrlen(szBuff));
};

void CTitleScene::Release(void) {

};

void CTitleScene::RunSeleteMenu() {
	switch (m_currentMenuSelect) {
		case START:
			g_gameClient->LoadScene(new CMainGame);
			break;

		case QUIT:
			PostQuitMessage(0);
			break;
	}
}