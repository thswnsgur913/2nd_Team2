#include "stdafx.h"
#include "MonBullet.h"

CMonBullet::CMonBullet() {
}

CMonBullet::~CMonBullet() {
	Release();
}

void CMonBullet::Initialize() {
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;

	m_fSpeed = 10.f;

	m_fJumpPower = 20.f;
	m_fJumpTime = 0.f;

	Update_Rect();
}

int CMonBullet::Update() {
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += m_tDir.fX * m_fSpeed;
	m_tInfo.fY -= m_fJumpPower * m_fJumpTime - 9.8f * m_fJumpTime * m_fJumpTime * 0.5f;
	m_fJumpTime += 0.1f;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonBullet::Late_Update()
{
	if (m_tRect.left < -100 || m_tRect.right > 10000 || m_tRect.top < -100 || m_tRect.bottom > WINCY + 100) {
		m_bDead = true;
	}
}

void CMonBullet::Render(HDC hdc) {
	Ellipse(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonBullet::Release()
{
}

void CMonBullet::CollisionEnter(CObj* _sour)
{
}