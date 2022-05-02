#include "stdafx.h"
#include "TitleScene.h"
#include "GameClient.h"
#include "MainGame.h"
#include "EndingScene.h"
#include "KeyMgr.h"
#include "Label.h"

#include "BmpMgr.h"

CTitleScene::CTitleScene():
	m_currentMenuSelect(0),
	MenubarStartY(WINCY - 200),
	MenuItemHieght(50),
	MenuItemItemGap(20),
	m_bSeleted(false),
	m_bBarVisible(false),
	m_animeCount(0) {
}

CTitleScene::~CTitleScene() {

}

void CTitleScene::Initialize(void) {

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Title.bmp", L"Title");

	m_SelectHighlight.fX = WINCX * 0.5;
	m_SelectHighlight.fY = MenubarStartY + (m_currentMenuSelect * (MenuItemHieght + MenuItemItemGap));
	TargetHighlightPosition.x = m_SelectHighlight.fX;
	TargetHighlightPosition.y = m_SelectHighlight.fY;

	m_SelectHighlight.fWidth = 300.f;
	m_SelectHighlight.fHeight = MenuItemHieght;

	CLabel* title = new CLabel(L"코딩의 섬", L"맑은 고딕");
	title->Set_pos(static_cast<int>(WINCX * 0.5), 220);
	title->SetFontSize(120);
	CUIManager::Instance()->AddUI(UI_FRONT, title);

	CLabel* subTitle = new CLabel(L"2조의 무시무시한");
	subTitle->Set_pos(static_cast<int>(WINCX * 0.5) - 190, 160);
	subTitle->SetFontSize(25) \
	.SetAlign(CLabel::alignType::ALIGN_LEFT);

	CUIManager::Instance()->AddUI(UI_FRONT, subTitle);

	CLabel* menuItem1 = new CLabel(L"게임시작");
	menuItem1->Set_pos(static_cast<int>(WINCX * 0.5), MenubarStartY);
	menuItem1->SetFontSize(30);
	CUIManager::Instance()->AddUI(UI_FRONT, menuItem1);

	CLabel* menuItem2 = new CLabel(L"게임종료");
	menuItem2->Set_pos(static_cast<int>(WINCX * 0.5), MenubarStartY + (MenuItemHieght + MenuItemItemGap));
	menuItem2->SetFontSize(30);
	CUIManager::Instance()->AddUI(UI_FRONT, menuItem2);

	seletedAnimeTimer = new CTimer;
};

void CTitleScene::Update(void) {
	if (seletedAnimeTimer)
		seletedAnimeTimer->Update();

	float width = TargetHighlightPosition.x - m_SelectHighlight.fX;
	float height = TargetHighlightPosition.y - m_SelectHighlight.fY;
	float distance = sqrtf((width * width) + (height * height));

	if (distance > 0)
		m_SelectHighlight.fY += (height / distance) * 5.f;

	if (m_bSeleted)
		return;

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE) || CKeyMgr::Get_Instance()->Key_Down(VK_RETURN)) {
		RunSeleteMenu();
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_UP)) {
		++m_currentMenuSelect;
		m_currentMenuSelect = m_currentMenuSelect % MENU_LENGTH;
		
		TargetHighlightPosition.y = MenubarStartY + (m_currentMenuSelect * (MenuItemHieght + MenuItemItemGap));
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN)) {
		--m_currentMenuSelect;
		if (m_currentMenuSelect < 0)
			m_currentMenuSelect = MENU_LENGTH - 1;

		TargetHighlightPosition.y = MenubarStartY + (m_currentMenuSelect * (MenuItemHieght + MenuItemItemGap));
	}

};

void CTitleScene::Late_Update(void) {

};

void CTitleScene::Render(HDC hdc) {

	HBRUSH	brush;
	HGDIOBJ hOldBrush;
	brush = CreateSolidBrush(RGB(255, 255, 255));
	hOldBrush = SelectObject(hdc, brush);

	Rectangle(hdc, 0, 0, WINCX, WINCY);

	SelectObject(hdc, hOldBrush);
	DeleteObject(brush);

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Title");
	BitBlt(hdc, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	if (m_bBarVisible) {
		brush = CreateSolidBrush(RGB(0, 0, 0));
		hOldBrush = SelectObject(hdc, brush);
	}

	int selectBarHalfWidth = static_cast<int>(m_SelectHighlight.fWidth * 0.5f);
	int selectBarHalfHeight = static_cast<int>(m_SelectHighlight.fHeight * 0.5f);
	Rectangle(hdc, static_cast<int>(m_SelectHighlight.fX) - selectBarHalfWidth, m_SelectHighlight.fY - selectBarHalfHeight, m_SelectHighlight.fX + selectBarHalfWidth, m_SelectHighlight.fY + selectBarHalfHeight);

	if (m_bBarVisible) {
		SelectObject(hdc, hOldBrush);
		DeleteObject(brush);
	}

	/*

	TCHAR szBuff[32] = L"";

	swprintf_s(szBuff, L"select : %d", m_currentMenuSelect);
	TextOut(hdc, static_cast<int>(WINCX * 0.5) - 50, 20, szBuff, lstrlen(szBuff));

	*/

	CUIManager::Instance()->FrontRender(hdc);
};

void CTitleScene::Release(void) {

};

void CTitleScene::RunSeleteMenu() {
	m_bSeleted = true;

	seletedAnimeTimer->StartTimer(0.05f, [&]() {
		if (m_animeCount >= 4) {
			switch (m_currentMenuSelect) {
			case START:
				g_gameClient->LoadScene(new CMainGame);
				break;

			case QUIT:
				PostQuitMessage(0);
				break;
			}

			Safe_Delete(seletedAnimeTimer);
			return;
		}
		
		m_bBarVisible = !m_bBarVisible;
		++m_animeCount;
	});

	
}