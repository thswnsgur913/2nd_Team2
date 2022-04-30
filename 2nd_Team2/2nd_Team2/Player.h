#pragma once
#include "Obj.h"
#include "ScrollMgr.h"
#include "Bullet.h"
#include "Hammer.h"
#include "Monster.h"
#include "Effect.h"
#include "AbstractFactory.h"
#include "KeyMgr.h"
#include "ObjManager.h"
#include "LinePlat.h"

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
	STAT&	Get_Stat(void) { return m_tPstat; }
	void    Set_line(CLinePlat* Line) { m_Line = Line; }

private:
	void KeyInput();
	void Jumping();
	void		OffSet(void);

private:
	list<CObj*>* m_bulletList; // 총알 리스트
	list<CObj*>* m_MonsterList; // 몬스터 리스트

	STAT		            m_tPstat; //플레이어 스테이터스
	CLinePlat*              m_Line;
};

