#include "stdafx.h"
#include "BackUI.h"


CBackUI::CBackUI()
{
}


CBackUI::~CBackUI()
{
}

void CBackUI::Initialize() {
}

int CBackUI::Update() {
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBackUI::Late_Update() {
}

void CBackUI::Render(HDC hdc) {
	HBRUSH	brush;
	HGDIOBJ h_old_brush;
	brush = CreateSolidBrush(RGB(0, 0, 105));
	h_old_brush = SelectObject(hdc, brush);
	Rectangle(hdc, 0, 0, WINCX, WINCY);
	SelectObject(hdc, h_old_brush);
	DeleteObject(brush);
}

void CBackUI::Release() {
}

void CBackUI::CollisionEnter(CObj* _sour) {
}