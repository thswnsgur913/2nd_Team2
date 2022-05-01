#pragma once
#include "Obj.h"
#include "Monster.h"
#include "KeyMgr.h"
class CBullet : public CObj
{
public:
	CBullet();
	virtual ~CBullet();
public:
	virtual void Initialize() PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() PURE;
	virtual	void CollisionEnter(CObj* _sour) PURE;

public:
	BULLET_TYPE GetType() const;
	void SetType(BULLET_TYPE eType);
	void SetDirection(float _x, float _y) { m_tDir.fX = _x, m_tDir.fY = _y; };

protected:
	INFO m_tDir;
	BULLET_TYPE m_eBulletType;

};

