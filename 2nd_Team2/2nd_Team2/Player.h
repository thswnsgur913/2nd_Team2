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

private:
	void KeyInput();
	void Jumping();
	void		OffSet(void);

private:
	list<CObj*>* m_bulletList; // �Ѿ� ����Ʈ
	list<CObj*>* m_MonsterList; // ���� ����Ʈ

	bool					m_bJump;		// ���� ���� Ȯ��
	float					m_fJumpPower;	// ���� ��
	float					m_fJumpTime;	// ���� �� ���� �ð�
	bool                    m_Dir; //�̵� ���� Ȯ��

	STAT		            m_tPstat; //�÷��̾� �������ͽ�

};

