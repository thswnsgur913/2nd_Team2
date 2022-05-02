#include "stdafx.h"
#include "Effect.h"
#include "LinePlat.h"


CEffect::CEffect() {
}


CEffect::~CEffect() {
}

void CEffect::Initialize() {
	m_tInfo.fWidth = 10.f;
	m_tInfo.fHeight = 10.f;

	m_tInfo.fColWidth = 10.f;
	m_tInfo.fColHeight = 10.f;

	m_fSpeed = 8.f;
};

int CEffect::Update() {
	if (m_bDead) {
		return OBJ_DEAD;
	}

	if (m_tInfo.fWidth >= m_effectEndSize.fX && m_tInfo.fHeight >= m_effectEndSize.fY) {
		m_bDead = true;
	}

	m_tInfo.fWidth += m_fSpeed;
	m_tInfo.fHeight += m_fSpeed;

	Update_Rect();

	return OBJ_NOEVENT;
};

void CEffect::Late_Update() {

};

void CEffect::Render(HDC hDC) {
	HBRUSH	brush = CreateSolidBrush(RGB(255, 0, 0));
	HGDIOBJ h_old_brush = SelectObject(hDC, brush);

	int	iScrollX = (int)CScrollMgr::Get_Scroll()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Scroll()->Get_ScrollY();

	Ellipse(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	SelectObject(hDC, h_old_brush);

	DeleteObject(brush);
};

void CEffect::Release() {

};

void CEffect::CollisionEnter(CObj* _sour) {
};
