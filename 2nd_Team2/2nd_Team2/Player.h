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
	void PlatEnter(float); // 플랫폼 충돌
	void PlatEnterX(float); // 수직 라인 플랫폼 충돌
	void PlatEnterX2(float);

private:
	void KeyInput();
	void Jumping();
	void OffSet(void);
	void Drop(void);


private:
	list<CObj*>* m_bulletList; // 총알 리스트
	list<CObj*>* m_MonsterList; // 몬스터 리스트

	bool					m_bJump;		// 점프 상태 확인
	float					m_fJumpPower;	// 점프 힘
	float					m_fJumpTime;	// 점프 중 진행 시간
	bool                    m_Dir; //이동 방향 확인

	STAT		            m_tPstat; //플레이어 스테이터스
	CLinePlat*              m_Line;
	int                     m_iStage;// 플레이어가 존재하는 스테이지.
	//bool                    m_bDrop;//플레이어가 자유낙하 하는지 판단.
};

