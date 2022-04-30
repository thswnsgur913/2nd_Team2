#pragma once
#include "Obj.h"
#include "ScrollMgr.h"

class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual	void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual	void CollisionEnter(CObj* _sour);

public:

private:
	void KeyInput();
	void		OffSet(void);

private:
	list<CObj*>* m_bulletList; // 총알 리스트
	list<CObj*>* m_MonsterList; // 몬스터 리스트
};

