#include "stdafx.h"
#include "MovePlatform.h"


CMovePlatform::CMovePlatform()
{
}


CMovePlatform::~CMovePlatform()
{
}

void CMovePlatform::Initialize() {
	m_tInfo.fWidth = 120.f;
	m_tInfo.fHeight = 50.f;
	m_tInfo.fColWidth = 120.f;
	m_tInfo.fColHeight = 50.f;

	m_fSpeed = 3.f;

	m_tDir = { 0, 1 };
}

int CMovePlatform::Update() {
	if (m_bDead)
		return OBJ_DEAD;

	if (m_tRect.left < m_area.left || m_tRect.top < m_area.top  ||
		m_tRect.right > m_area.right || m_tRect.bottom > m_area.bottom) {
		m_tDir.x *= -1;
		m_tDir.y *= -1;
	}

	m_tInfo.fX += m_tDir.x * m_fSpeed;
	m_tInfo.fY += m_tDir.y * m_fSpeed;

	Update_Rect();

	return OBJ_NOEVENT;

}

void CMovePlatform::Late_Update() {
	if (m_targetObj && m_targetObj->GetIsGround()) {
		INFO targetInfo = m_targetObj->Get_Info();
		m_targetObj->Set_pos(targetInfo.fX + (m_tDir.x * m_fSpeed), targetInfo.fY + (m_tDir.y * m_fSpeed));
	}
	else {
		m_targetObj = nullptr;
	}

	Update_Rect();
}

void CMovePlatform::Render(HDC hDC) {
	Rectangle(hDC, m_tScrollRect.left, m_tScrollRect.top, m_tScrollRect.right, m_tScrollRect.bottom);
}

void CMovePlatform::Release() {
}

void CMovePlatform::CollisionEnter(CObj* _sour) {
	if (_sour->Get_Rect().bottom > m_tRect.top) {
		_sour->PlatEnter(m_tRect.top);
		m_targetObj = _sour;
	}
}
