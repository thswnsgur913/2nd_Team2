#include "stdafx.h"
#include "WeaponBag.h"


CWeaponBag::CWeaponBag()
{
}


CWeaponBag::~CWeaponBag()
{
	Release();
}

void CWeaponBag::Initialize() {
	float gap = 10.f;
	m_tInfo.fWidth = 100.f;
	m_tInfo.fHeight = 100.f;
	
	m_tInfo.fX = (m_tInfo.fWidth * 0.5f) + gap;
	m_tInfo.fY = WINCY - (m_tInfo.fHeight * 0.5f) - gap;

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
}

void CWeaponBag::Release() {
}

void CWeaponBag::CollisionEnter(CObj* _sour) {
}