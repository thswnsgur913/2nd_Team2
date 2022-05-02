#include "stdafx.h"
#include "Bullet.h"

CBullet::CBullet() {
}

CBullet::~CBullet() {
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

