#include "stdafx.h"
#include "WeaponBag.h"


CWeaponBag::CWeaponBag():
	GAP(5)
{
}


CWeaponBag::~CWeaponBag()
{
	Release();
}

void CWeaponBag::Initialize() {
	m_tInfo.fWidth = 100.f;
	m_tInfo.fHeight = 100.f;
	
	m_tInfo.fX = (m_tInfo.fWidth * 0.5f) + 20;
	m_tInfo.fY = WINCY - (m_tInfo.fHeight * 0.5f) - 20;

	Update_Rect();
}

int CWeaponBag::Update() {
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CWeaponBag::Late_Update() {
}

void CWeaponBag::Render(HDC hdc) {
	//Frame
	Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	Rectangle(hdc, m_tRect.left + GAP, m_tRect.top + GAP, m_tRect.right - GAP, m_tRect.bottom - GAP);

	DrawHammer(hdc);

	// shape
	switch (m_weapon) {
	case CPlayer::WEAPONID::HAMMER:
		DrawHammer(hdc);
		break;

	case CPlayer::WEAPONID::LANCE:
		DrawLance(hdc);
		break;
	}


}

void CWeaponBag::DrawHammer(HDC hdc) {
	HBRUSH brush;
	HGDIOBJ oldBrush;

	brush = CreateSolidBrush(RGB(150, 75, 0));
	oldBrush = SelectObject(hdc, brush);

	Rectangle(hdc, m_tRect.left + GAP + 35, m_tRect.top + GAP + 5, m_tRect.right - GAP - 35, m_tRect.bottom - GAP - 5);
	SelectObject(hdc, oldBrush);
	DeleteObject(brush);

	brush = CreateSolidBrush(RGB(0, 0, 0));
	oldBrush = SelectObject(hdc, brush);

	Rectangle(hdc, m_tRect.left + GAP + 5, m_tRect.top + GAP + 10, m_tRect.right - GAP - 5, m_tRect.top + GAP + 50);
	SelectObject(hdc, oldBrush);
	DeleteObject(brush);
}

void CWeaponBag::DrawLance(HDC hdc) {
	HBRUSH brush;
	HGDIOBJ oldBrush;

	brush = CreateSolidBrush(RGB(150, 75, 0));
	oldBrush = SelectObject(hdc, brush);

	Rectangle(hdc, m_tRect.left + GAP + 40, m_tRect.top + GAP + 5, m_tRect.right - GAP - 40, m_tRect.bottom - GAP - 5);
	SelectObject(hdc, oldBrush);
	DeleteObject(brush);
}

void CWeaponBag::Release() {
}
