#include "stdafx.h"
#include "Cloud.h"


CCloud::CCloud() {
}


CCloud::~CCloud() {
}


void CCloud::Initialize() {
	m_tInfo.fWidth = 100.f;
	m_tInfo.fHeight = 50.f;
};

int CCloud::Update() {
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX -= m_fSpeed;
	if (m_tInfo.fX < -100) {
		m_tInfo.fX = WINCX + 100;
	}
	Update_Rect();
	
	return OBJ_NOEVENT;

};

void CCloud::Late_Update() {


};

void CCloud::Render(HDC hDC) {
	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
	HGDIOBJ oldBrush = SelectObject(hDC, brush);

	HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	HGDIOBJ oldPen = SelectObject(hDC, pen);

	// 力老 哭率
	Ellipse(hDC, m_tRect.left, m_tRect.top+10, m_tRect.right-60, m_tRect.bottom);
	// 啊款单
	Ellipse(hDC, m_tRect.left+10, m_tRect.top, m_tRect.right-10, m_tRect.bottom);
	// 力老 坷弗率
	Ellipse(hDC, m_tRect.left+40, m_tRect.top-10, m_tRect.right, m_tRect.bottom);

	SelectObject(hDC, oldBrush);
	SelectObject(hDC, oldPen);

	DeleteObject(brush);
	DeleteObject(pen);
};

void CCloud::Release() {
};