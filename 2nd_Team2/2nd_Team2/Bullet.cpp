#include "stdafx.h"
#include "Bullet.h"



CBullet::CBullet() {
}

CBullet::~CBullet() {
	Release();
}

void CBullet::Initialize() {}

int CBullet::Update() {
	return 0;
}

void CBullet::Late_Update() 
{

}

void CBullet::Render(HDC hdc) {
	
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

