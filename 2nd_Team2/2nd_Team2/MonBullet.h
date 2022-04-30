#pragma once
#include "Bullet.h"
class CMonBullet :
	public CBullet
{
public:
	CMonBullet();
	virtual ~CMonBullet();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual	void CollisionEnter(CObj* _sour) override;

};

