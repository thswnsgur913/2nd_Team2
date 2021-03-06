#include "stdafx.h"
#include "ProgressBar.h"


CProgressBar::CProgressBar() {
}


CProgressBar::~CProgressBar() {
	Release();
}

void CProgressBar::Initialize() {
}

int CProgressBar::Update() {
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CProgressBar::Late_Update() {
}

void CProgressBar::Render(HDC hdc) {
	HBRUSH	brush;
	HGDIOBJ oldBrush;
	brush = CreateSolidBrush(RGB(255, 0, 0));

	//Frame
	Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	// progress
	oldBrush = SelectObject(hdc, brush);
	Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.left + static_cast<int>(m_tInfo.fWidth * m_rate), m_tRect.bottom);

	SelectObject(hdc, oldBrush);
	DeleteObject(brush);
}

void CProgressBar::Release() {
}

void CProgressBar::InitProgress(const Vector2D position, const Vector2D size, const float _max, const float _current) {
	m_tInfo.fX = position.x;
	m_tInfo.fY = position.y;

	m_tInfo.fWidth = size.x;
	m_tInfo.fHeight = size.y;

	m_max = _max;
	m_current = _current;

	m_rate = m_current / m_max;

	Update_Rect();
}
