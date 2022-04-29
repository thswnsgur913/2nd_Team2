#include "stdafx.h"
#include "Bullet.h"
#include "Monster.h"


CBullet::CBullet() {
}

CBullet::~CBullet() {
	Release();
}

void CBullet::Initialize() {
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;

	m_fSpeed = 10.f;
	 
	Update_Rect();

	m_bThrow = true;
	m_fThrowPower = 20.f;
	m_fThrowTime = 0.f;
}

int CBullet::Update() {
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += m_tDir.fX * m_fSpeed;
	m_tInfo.fY += m_tDir.fY * m_fSpeed;
	m_tInfo.fX += m_fSpeed;

	Throw();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::Late_Update() {
	if (m_tRect.left < -100 || m_tRect.right > WINCX + 100 || m_tRect.top < -100 || m_tRect.bottom > WINCY + 100) {
		m_bDead = true;
	}
}

void CBullet::Render(HDC hdc) {
	HBRUSH brush;
	HPEN pen;
	pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);

	Rectangle(hdc, m_tRect.left - 50, m_tRect.top, m_tRect.right - 50, m_tRect.bottom - 50);

	DeleteObject(pen);
	DeleteObject(brush);

	pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	brush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);

	Rectangle(hdc, m_tRect.left-80, m_tRect.top-40, m_tRect.right-20, m_tRect.bottom - 100);

	DeleteObject(pen);
	DeleteObject(brush);

	//Ellipse(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release() {
}

void CBullet::CollisionEnter(CObj* _sour) {
	CMonster* collisionMonster = dynamic_cast<CMonster*>(_sour);

	if (collisionMonster && m_eBulletType == PLAYER_BULLET && !collisionMonster->GetDead()) {
		collisionMonster->Hit();
		m_bDead = true;

	}
}

BULLET_TYPE CBullet::GetType() const
{
	if (this)
	{
		return m_eBulletType;
	}
	else
	{
		return BULLET_END;
	}
}

void CBullet::SetType(BULLET_TYPE eType)
{
	m_eBulletType = eType;
}

void CBullet::Throw()
{
	float		fY = 500.f;

	if (m_bThrow)
	{
		m_tInfo.fY -= m_fThrowPower * m_fThrowTime - 9.8f * m_fThrowTime * m_fThrowTime * 0.5f;
		m_fThrowTime += 0.2f;

		if (fY < m_tInfo.fY)
		{
			m_bThrow = false;
			m_fThrowTime = 0.f;
			//m_tInfo.fY = fY;
			m_bDead = true;
		}
	}
}
