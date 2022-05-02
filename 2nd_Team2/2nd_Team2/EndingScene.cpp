#include "stdafx.h"
#include "EndingScene.h"
#include "Label.h"
#include "UIManager.h"
#include "BmpMgr.h"

CEndingScene::CEndingScene() {
}

CEndingScene::~CEndingScene() {

}

void CEndingScene::Initialize(void) {

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ground.bmp", L"ending");

	CLabel* title = new CLabel(L"축하합니다", L"맑은 고딕");
	title->Set_pos(static_cast<int>(WINCX * 0.5), static_cast<int>(WINCY * 0.5) - 90);
	title->SetFontSize(80);
	CUIManager::Instance()->AddUI(UI_FRONT, title);

	CLabel* subTitle = new CLabel(L"게임 클리어");
	subTitle->Set_pos(static_cast<int>(WINCX * 0.5), static_cast<int>(WINCY * 0.5));
	subTitle->SetFontSize(120);

	CUIManager::Instance()->AddUI(UI_FRONT, subTitle);
};

void CEndingScene::Update(void) {
};

void CEndingScene::Late_Update(void) {

};

void CEndingScene::Render(HDC hdc) {
	HBRUSH	brush;
	HGDIOBJ hOldBrush;
	brush = CreateSolidBrush(RGB(255, 255, 255));
	hOldBrush = SelectObject(hdc, brush);

	Rectangle(hdc, 0, 0, WINCX, WINCY);

	SelectObject(hdc, hOldBrush);
	DeleteObject(brush);

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ending");
	BitBlt(hdc, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CUIManager::Instance()->FrontRender(hdc);
};

void CEndingScene::Release(void) {

};