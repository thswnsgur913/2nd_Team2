#include "stdafx.h"
#include "Bullet.h"



CBullet::CBullet() {
}

CBullet::~CBullet() {
	Release();
}

void CBullet::Initialize() {
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;

	m_fSpeed = 10.f;

	m_fJumpPower = 20.f;
	m_fJumpTime = 0.f;
	 
	Update_Rect();
}

int CBullet::Update() {
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += m_tDir.fX * m_fSpeed;
	m_tInfo.fY -= m_fJumpPower * m_fJumpTime - 9.8f * m_fJumpTime * m_fJumpTime * 0.5f;
	m_fJumpTime += 0.1f;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::Late_Update() 
{

}

void CBullet::Render(HDC hdc) {
	Ellipse(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release() 
{
}

void CBullet::CollisionEnter(CObj* _sour) 
{
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

