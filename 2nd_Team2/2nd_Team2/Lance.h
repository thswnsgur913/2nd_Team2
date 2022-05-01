#pragma once
#include "obj.h"
#include "Bullet.h"
#include "ScrollMgr.h"


class CLance :public CBullet
{
public:
	CLance();
	virtual ~CLance();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual	void CollisionEnter(CObj* _sour);
private:
	float m_Distance;
};